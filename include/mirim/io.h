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

#ifndef MIRIM_IO_H
#define MIRIM_IO_H

#include <mirim/error.h>
/**
 * @brief Read contents of a file and return the number of chars
 * @param filename
 * @param nchars
 * @param error
 * @return
 */
char*
mr_readfile(const char* filename, long* nchars, Error** error);

#endif
