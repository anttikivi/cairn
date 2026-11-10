/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CAIRN_STRINGS_H
#define CAIRN_STRINGS_H

#include <stddef.h>

#if defined(_WIN32)
#    define WIN32_LEAN_AND_MEAN
#    include <windows.h>
#else
#    include <unistd.h>
#endif

/*
 * Return the length of the given null-terminated byte string up to n bytes and
 * up to and not including the null character.
 */
size_t cairn_str_nlen(const char *s, size_t n);

/*
 * Compare two null-terminated byte string lexicographically. Characters
 * following the null character are ignored. The parameters n and m are
 * the maximum number of characters to compare from l and r, respectively.
 * Essentially they should be the buffer sizes if the goal is to check whether
 * the to strings are equal.
 */
int cairn_str_ncmp(const char *l, size_t n, const char *r, size_t m);

#endif
