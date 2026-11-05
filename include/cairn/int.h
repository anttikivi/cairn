/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CAIRN_INT_H
#define CAIRN_INT_H

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)

#    include <stdint.h>

typedef int8_t cairn_i8;
typedef uint8_t cairn_u8;
typedef int32_t cairn_i32;
typedef uint32_t cairn_u32;

#else

#    include <limits.h>

/* Enforce 8-bit byte assumption */
#    if CHAR_BIT != 8
#        error "target system must have 8-bit chars"
#    endif

/* 8-bit fixed-width integer types */

#    if UCHAR_MAX == 0xffU
typedef signed char cairn_i8;
typedef unsigned char cairn_u8;
#    else
#        error "no 8-bit integer type found"
#    endif

/* 32-bit fixed-width integer types */

#    if UINT_MAX == 0xffffffffU
typedef signed int cairn_i32;
typedef unsigned int cairn_u32;
#    elif ULONG_MAX == 0xffffffffUL
typedef signed long cairn_i32;
typedef unsigned long cairn_u32;
#    else
#        error "no 32-bit integer type found"
#    endif

#endif

#endif
