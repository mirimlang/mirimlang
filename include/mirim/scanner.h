/*
 * Copyright (C) 2017-2018 Arandu Academy - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 *
 * This file is part of project Mirim
 *
 * Written by:
 *   Anderson Tavares <acmt@outlook.com>
 */

#ifndef MIRIM_SCANNER_H
#define MIRIM_SCANNER_H

#include <mirim/error.h>
#include <stdint.h>



/**
 * @brief Tokens to be sent to the parser
 */
typedef enum TokenType {
  TK_ID,
  TK_NEWLINE,
  TK_BLOCKOPEN,
  TK_BLOCKCLOSE,
  TK_OP_EQ,
  TK_LITERAL,
  TK_STATIC,
  TK_DYNAMIC,
  TK_HASH,
  TK_DOT,
  TK_TEXT
} TokenType;

typedef struct ScannerToken {
  TokenType token;
  char* start;
  char* end;
} ScannerToken;


uint16_t
mr_scan(const char* text, ScannerToken **ptokens, Error** error);


#endif
