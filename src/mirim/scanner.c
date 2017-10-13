#include <mirim/scanner.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// Is lowercase letter?
#define IS_LLOW(cur) (cur >= 'a' && cur <= 'z')
// Is uppercase letter?
#define IS_LUPP(cur) (cur >= 'A' && cur <= 'Z')
// Is digit?
#define IS_DIG(cur) (cur >= '0' && cur <= '9')
// Is letter (uppercase or lowercase)?
#define IS_L(cur) IS_LLOW(cur) || IS_LUPP(cur)
// Is alphanumeric?
#define IS_A(cur) IS_L(cur) || IS_DIG(cur)

#define fillToken(ptokens, tokens, curToken, start2, end2, type) \
tokens[curToken].start = start2; \
tokens[curToken].end = end2; \
tokens[curToken].token = type; \
curToken++;\
if(curToken == maxTokens) { \
  maxTokens <<= 1; \
  *ptokens = realloc(tokens, sizeof(ScannerToken) * maxTokens); \
  tokens = *ptokens; \
}

#define startLexeme(p) lexemeStart = p;\
  lexemeEnd = p;

typedef enum State {
  ST_START,
  ST_ID,
  ST_LITERAL,
  ST_LITERAL_ESCAPING,
  ST_COMMENT_POSSIBLE,
  ST_COMMENT,
  ST_COMMENT_NEWLINE,
  ST_LINE_LEVEL,
  ST_TEXT
} State;

uint16_t
mr_scan(const char* text, ScannerToken** ptokens, Error** error) {
  char* pcur = (char*) text;
  char* lexemeStart = pcur;
  char* lexemeEnd = pcur;
  ScannerToken *tokens;
  uint16_t maxTokens = 32;
  uint16_t curToken = 0;
  uint16_t pos[2] = {0,0};
  char cur;
  char errText[48];
  uint8_t state = ST_LINE_LEVEL;
  uint8_t spaces[32];
  uint8_t curLevel = 0;
  uint8_t nspaces;
  uint8_t commentSpace;
  memset(spaces,0,32);

  if(*ptokens == NULL){
    *ptokens = malloc(sizeof(ScannerToken) * maxTokens);
    tokens = *ptokens;
  }

  /* Informal Shortcuts
   * \l = [a-z]  (lowercase letters)
   * \u = [A-Z]  (uppercase letters
   * \c = [\l\u] (letters)
   * \d = [0-9]  (numeric digits)
   * \a = [\L\d] (alphanumeric)
   * \i = [\a-]  (ID character-except 1st one which is \c)
   *
   *
   * States:
   * - 0: Start
   * - 1: ID
   * - 2: Literal
   * - 3: Literal Escaping
   * - 4: Possible comment (waiting next /)
   * - 5: Comment
   * - 6: Line level
   *
   * Recognizing ID:
   * |0|-\c->|1|--\i
   *    <-\I-   <-
   *
   * Recognizing Literals
   * |0|--"-->|2|--\-->|3|
   *    <-"---   <-"---
   *
   * Recognizing Equal symbol
   * |0|--=
   *    <--
   *
   * Recognizing Static Control symbol
   * |0|--+
   *    <--
   *
   * Recognizing Dynamic Control symbol
   * |0|--[-]
   *    <----
   *
   * Recognizing Comments
   * |0|---/-->|4|---/-->|5|
   *    <-TK_BLOCKCLOSE--
   *
   * Verifying level
   * |0|--\n->|6|-\s
   *    <-\S--   <--
   *
   * Recognizing Hash (e.g., for id attribute)
   * |0|--#
   *    <--
   *
   * Recognizing Dot (e.g., for class attribute)
   * |0|--.
   *    <--
   */
  do {
    cur = *pcur;

    if(cur == '\n'){
      pos[0]++;
      pos[1] = 0;
    } else {
      pos[1]++;
    }

    switch (state) {
    case ST_START:
      startLexeme(pcur)
      if(IS_L(cur)) {
        state = ST_ID;
      } else switch(cur){
        case '"': state = ST_LITERAL; break;
        case '/': state = ST_COMMENT_POSSIBLE; break;
        case '\n':
          state = ST_LINE_LEVEL;
          lexemeStart++;
          break;
        case '=':
          fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_OP_EQ);
          break;
        case '-':
          fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_DYNAMIC);
          break;
        case '+':
          fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_STATIC);
          break;
        case '#':
          fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_HASH);
        break;
        case '.':
          fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_DOT);
        break;
        case ':':
          state = ST_LINE_LEVEL;
          lexemeStart++;
        break;
        case '|':
          state = ST_TEXT;
          lexemeStart++;
        break;
        case ' ':break;
      default:
        sprintf(errText,"Unexpected character at position (%d,%d)", pos[0], pos[1]);
        *error = mr_error_new(errText);
        break;
      }
      break;
    case ST_ID:
      if(IS_A(cur) || cur == '-') {
      } else {
        pcur--;
        lexemeEnd = pcur;
        state = ST_START;
        fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_ID);
      }
      break;
    case ST_LITERAL:
      if(cur == '"'){
        state = ST_START;
        lexemeEnd=pcur;
        fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_LITERAL)
      } else if(cur == '\\'){
        // Go to literal escaping
        state = ST_LITERAL_ESCAPING;
      }
      break;
    case ST_LITERAL_ESCAPING:
      if(cur == '"'){
        state = ST_LITERAL;
      }
      break;
    case ST_COMMENT_POSSIBLE:
      if(cur == '/'){
        state = ST_COMMENT;
      }
      break;
    case ST_COMMENT:
      if(cur == '\n'){
        state = ST_COMMENT_NEWLINE;
        commentSpace = 0;
      }
      break;
    case ST_COMMENT_NEWLINE:
      if(cur == ' ') {
        commentSpace++;
      } else {
        if(spaces[curLevel] < commentSpace) {
          state = ST_COMMENT;
        } else {
          state = ST_START;
          pcur--;
          lexemeEnd = pcur;
          while(spaces[curLevel] > commentSpace){
            fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_BLOCKCLOSE);
            curLevel--;
          }
        }
      }
      break;
    case ST_LINE_LEVEL:
      if(cur == ' '){
      } else {
        lexemeEnd = pcur;
        // Number of spaces
        nspaces = lexemeEnd-lexemeStart;
        // Is it greater than currentLevel?
        if(nspaces > spaces[curLevel]){
          // Create a new block and store new space level
          spaces[++curLevel] = nspaces;
          // Emit a new TK_BLOCKOPEN
          fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_BLOCKOPEN);
        } else if(nspaces < spaces[curLevel]) {
          while(spaces[curLevel] > nspaces){
            fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_BLOCKCLOSE);
            curLevel--;
          }
        } else if(nspaces == spaces[curLevel]) {
          if(pcur != text){
            if(tokens[curToken-1].token != TK_BLOCKCLOSE){
              fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_NEWLINE);
            }
          }
        }
        state = ST_START;
        pcur--;
      }
      break;
    case ST_TEXT:
      if(cur == '\n') {
        fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_TEXT);
        state = ST_LINE_LEVEL;
        lexemeStart = pcur+1;
      }
      break;
    default:
      break;
    }
  } while(*(++pcur));
  while(curLevel > 0){
    fillToken(ptokens, tokens, curToken, lexemeStart, lexemeEnd, TK_BLOCKCLOSE);
    curLevel--;
  }
  *ptokens = realloc(tokens, sizeof(ScannerToken) * curToken); \
  return curToken;
}
