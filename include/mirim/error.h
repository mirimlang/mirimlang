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

#ifndef MIRIM_ERROR_H
#define MIRIM_ERROR_H

/**
 * Structure for Error
 */
typedef struct Error {
  /**
   * Error type
   */
  char  type;
  /**
   * Error message
   */
  char* message;
} Error;

Error*
mr_error_new(char type, const char* message);

/**
 * @brief      
 *
 * @param      error  The error
 */
void
mr_error_destroy(Error** error);

#endif