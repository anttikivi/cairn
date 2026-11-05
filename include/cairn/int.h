/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BASE_INT_H
#define BASE_INT_H

#include <limits.h>

/* Enforce 8-bit byte assumption */
#if CHAR_BIT != 8
#    error "target system must have 8-bit chars"
#endif

/* 8-bit fixed-width integer types */

#if UCHAR_MAX == 0xffU
typedef signed char i8;
typedef unsigned char u8;
#else
#    error "no 8-bit integer type found"
#endif

/* 32-bit fixed-width integer types */

#if UINT_MAX == 0xffffffffU
typedef signed int i32;
typedef unsigned int u32;
#elif ULONG_MAX == 0xffffffffUL
typedef signed long i32;
typedef unsigned long u32;
#else
#    error "no 32-bit integer type found"
#endif

#endif
