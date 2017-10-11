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
#include <mirim/error.h>

/**
 * @brief Parse file
 * @param filename
 * @param error
 */
void
parseFile(const char *filename, Error** error);

/**
 * @brief Scan text
 * @param text
 */
void
scan(const char* text, Error** error);

#endif
