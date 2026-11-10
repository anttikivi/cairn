/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRSTR_H
#define CRSTR_H

#include <stddef.h>

/*
 * Return the length of the given null-terminated byte string up to n bytes and
 * up to and not including the null character.
 */
size_t crsnlen(const char *s, size_t n);

/*
 * Compare two null-terminated byte strings lexicographically. Characters
 * following the null character are ignored. The parameters n and m are
 * the maximum number of characters to compare from l and r, respectively.
 * Essentially they should be the buffer sizes if the goal is to check whether
 * the two strings are equal.
 */
int crsncmp(const char *l, size_t n, const char *r, size_t m);

#endif
