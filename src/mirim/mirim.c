#include <mirim/mirim.h>
#include <stdio.h>

void
mr_parsefile(const char *filename, char** text, long *nchars, Error** error){
  // Read file
  *text = mr_readfile(filename, nchars, error);
  if(error != NULL && *error != NULL){
    return;
  }

  // Generate tokens
  ScannerToken* tokens = NULL;
  uint16_t ntokens = mr_scan(*text, &tokens, error);
  if(error != NULL && *error != NULL){
    return;
  } else {
    printf("%d tokens", ntokens);
    uint16_t i;
    for(i = 0; i < ntokens; i++){
      switch(tokens[i].token){
        case TK_ID: printf("ID ");break;
        case TK_BLOCKOPEN: printf("BLOCKOPEN\n");break;
        case TK_BLOCKCLOSE: printf("BLOCKCLOSE\n");break;
        case TK_OP_EQ: printf("= ");break;
        case TK_DOT: printf(".");break;
        case TK_HASH: printf("#");break;
        case TK_STATIC: printf("+ ");break;
        case TK_DYNAMIC: printf("- ");break;
        case TK_NEWLINE: printf("\n");break;
        case TK_LITERAL: printf("LITERAL ");break;
        case TK_TEXT: printf("TEXT ");break;
      }
    }
  }

  // Parse the tokens
//  mr_parse(tokens, error);
  if(error != NULL && *error != NULL){

  }
}

