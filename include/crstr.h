/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRSTR_H
#define CRSTR_H

#include <stddef.h>

#include <crbool.h>

/*
 * Return the length of the given null-terminated byte string up to n bytes and
 * up to and not including the null character.
 */
size_t crsnlen(const char *s, size_t n);

/*
 * Compare two possibly null-terminated byte strings lexicographically.
 * Characters following the null character are ignored. The parameters n and m
 * are the maximum number of characters to compare from l and r, respectively.
 * Essentially they should be the buffer sizes of l and r if the goal is to
 * check whether the two strings are equal.
 *
 * The return value is negative if l appears before r in lexicographical order
 * and positive the other way around. It is zero if l and r compare equal.
 */
int crsncmp(const char *l, size_t n, const char *r, size_t m);

/*
 * Check if the given byte array is properly null-terminated within the given
 * limit. Returns CR_FALSE if no null terminator is found or if n is 0 or s is
 * NULL.
 */
crbool crsterm(const char *s, size_t n);

/*
 * Find the first occurrence c from s in the null-terminated byte string
 * pointed to by s if c is not \0. Scans up to n characters. Returns a
 * null pointer if the character is not found. Also returns a null pointer if s
 * is NULL or n is 0.
 *
 * To find the position of the null terminator, use `crsnlen`.
 */
const char *crsnchr(const char *s, const char c, size_t n);

#endif
