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

#ifndef MIRIM_H
#define MIRIM_H

#include <mirim/core.h>
#include <mirim/io.h>
#include <mirim/error.h>
#include <mirim/scanner.h>
#include <stddef.h>

/**
 * @brief Parse file
 * @param filename
 * @param text
 * @param nchars
 * @param error
 */
void
mr_parsefile(const char *filename, char **text, long *nchars, Error** error);

#endif
