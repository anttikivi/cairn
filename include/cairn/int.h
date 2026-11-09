/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CAIRN_INT_H
#define CAIRN_INT_H

#include <cairn/config.h>

#include <limits.h>

#if CAIRN_USE_STDINT

#    include <stdint.h>

#    if defined(INT8_MAX) && defined(INT8_MIN)
#        define CAIRN_I8_MAX (INT8_MAX)
#        define CAIRN_I8_MIN (INT8_MIN)
typedef int8_t cairn_i8;
#    endif

#    if defined(UINT8_MAX)
#        define CAIRN_U8_MAX (UINT8_MAX)
typedef uint8_t cairn_u8;
#    endif

#    define CAIRN_LEAST_I8_MAX (INT_LEAST8_MAX)
#    define CAIRN_LEAST_I8_MIN (INT_LEAST8_MIN)
#    define CAIRN_LEAST_U8_MAX (UINT_LEAST8_MAX)

typedef int_least8_t cairn_least_i8;
typedef uint_least8_t cairn_least_u8;

#    if defined(INT16_MAX) && defined(INT16_MIN)
#        define CAIRN_I16_MAX (INT16_MAX)
#        define CAIRN_I16_MIN (INT16_MIN)
typedef int16_t cairn_i16;
#    endif

#    if defined(UINT16_MAX)
#        define CAIRN_U16_MAX (UINT16_MAX)
typedef uint16_t cairn_u16;
#    endif

#    define CAIRN_LEAST_I16_MAX (INT_LEAST16_MAX)
#    define CAIRN_LEAST_I16_MIN (INT_LEAST16_MIN)
#    define CAIRN_LEAST_U16_MAX (UINT_LEAST16_MAX)

typedef int_least16_t cairn_least_i16;
typedef uint_least16_t cairn_least_u16;

#    if defined(INT32_MAX) && defined(INT32_MIN)
#        define CAIRN_I32_MAX (INT32_MAX)
#        define CAIRN_I32_MIN (INT32_MIN)
typedef int32_t cairn_i32;
#    endif

#    if defined(UINT32_MAX)
#        define CAIRN_U32_MAX (UINT32_MAX)
typedef uint32_t cairn_u32;
#    endif

#    define CAIRN_LEAST_I32_MAX (INT_LEAST32_MAX)
#    define CAIRN_LEAST_I32_MIN (INT_LEAST32_MIN)
#    define CAIRN_LEAST_U32_MAX (UINT_LEAST32_MAX)

typedef int_least32_t cairn_least_i32;
typedef uint_least32_t cairn_least_u32;

#    if CAIRN_USE_INT64
#        if defined(INT64_MAX) && defined(INT64_MIN)
#            define CAIRN_I64_MAX (INT64_MAX)
#            define CAIRN_I64_MIN (INT64_MIN)
typedef int64_t cairn_i64;
#        endif

#        if defined(UINT64_MAX)
#            define CAIRN_U64_MAX (UINT64_MAX)
typedef uint64_t cairn_u64;
#        endif

#        define CAIRN_LEAST_I64_MAX (INT_LEAST64_MAX)
#        define CAIRN_LEAST_I64_MIN (INT_LEAST64_MIN)
#        define CAIRN_LEAST_U64_MAX (UINT_LEAST64_MAX)

typedef int_least64_t cairn_least_i64;
typedef uint_least64_t cairn_least_u64;
#    endif

#else

#    ifdef CAIRN_I8_TYPE
#        define CAIRN_I8_MAX (CAIRN_I8_TYPE_MAX)
#        define CAIRN_I8_MIN (CAIRN_I8_TYPE_MIN)
typedef CAIRN_I8_TYPE cairn_i8;
#    endif

#    ifdef CAIRN_U8_TYPE
#        define CAIRN_U8_MAX (CAIRN_U8_TYPE_MAX)
typedef CAIRN_U8_TYPE cairn_u8;
#    endif

#    define CAIRN_LEAST_I8_MAX (SCHAR_MAX)
#    define CAIRN_LEAST_I8_MIN (SCHAR_MIN)
#    define CAIRN_LEAST_U8_MAX (UCHAR_MAX)

typedef signed char cairn_least_i8;
typedef unsigned char cairn_least_u8;

#    ifdef CAIRN_I16_TYPE
#        define CAIRN_I16_MAX (CAIRN_I16_TYPE_MAX)
#        define CAIRN_I16_MIN (CAIRN_I16_TYPE_MIN)
typedef CAIRN_I16_TYPE cairn_i16;
#    endif

#    ifdef CAIRN_U16_TYPE
#        define CAIRN_U16_MAX (CAIRN_U16_TYPE_MAX)
typedef CAIRN_U16_TYPE cairn_u16;
#    endif

#    if SCHAR_MAX >= 32767 && SCHAR_MIN <= -32767
#        define CAIRN_LEAST_I16_MAX (SCHAR_MAX)
#        define CAIRN_LEAST_I16_MIN (SCHAR_MIN)
typedef signed char cairn_least_i16;
#    else
#        define CAIRN_LEAST_I16_MAX (SHRT_MAX)
#        define CAIRN_LEAST_I16_MIN (SHRT_MIN)
typedef short cairn_least_i16;
#    endif

#    if UCHAR_MAX >= 65535U
#        define CAIRN_LEAST_U16_MAX (UCHAR_MAX)
typedef unsigned char cairn_least_u16;
#    else
#        define CAIRN_LEAST_U16_MAX (USHRT_MAX)
typedef unsigned short cairn_least_u16;
#    endif

#    ifdef CAIRN_I32_TYPE
#        define CAIRN_I32_MAX (CAIRN_I32_TYPE_MAX)
#        define CAIRN_I32_MIN (CAIRN_I32_TYPE_MIN)
typedef CAIRN_I32_TYPE cairn_i32;
#    endif

#    ifdef CAIRN_U32_TYPE
#        define CAIRN_U32_MAX (CAIRN_U32_TYPE_MAX)
typedef CAIRN_U32_TYPE cairn_u32;
#    endif

#    if SCHAR_MAX >= 2147483647 && SCHAR_MIN <= -2147483647
#        define CAIRN_LEAST_I32_MAX (SCHAR_MAX)
#        define CAIRN_LEAST_I32_MIN (SCHAR_MIN)
typedef signed char cairn_least_i32;
#    elif SHRT_MAX >= 2147483647 && SHRT_MIN <= -2147483647
#        define CAIRN_LEAST_I32_MAX (SHRT_MAX)
#        define CAIRN_LEAST_I32_MIN (SHRT_MIN)
typedef short cairn_least_i32;
#    elif INT_MAX >= 2147483647 && INT_MIN <= -2147483647
#        define CAIRN_LEAST_I32_MAX (INT_MAX)
#        define CAIRN_LEAST_I32_MIN (INT_MIN)
typedef int cairn_least_i32;
#    else
#        define CAIRN_LEAST_I32_MAX (LONG_MAX)
#        define CAIRN_LEAST_I32_MIN (LONG_MIN)
typedef long cairn_least_i32;
#    endif

#    if UCHAR_MAX >= 4294967295U
#        define CAIRN_LEAST_U32_MAX (UCHAR_MAX)
typedef unsigned char cairn_least_u32;
#    elif USHRT_MAX >= 4294967295U
#        define CAIRN_LEAST_U32_MAX (USHRT_MAX)
typedef unsigned short cairn_least_u32;
#    elif UINT_MAX >= 4294967295U
#        define CAIRN_LEAST_U32_MAX (UINT_MAX)
typedef unsigned int cairn_least_u32;
#    else
#        define CAIRN_LEAST_U32_MAX (ULONG_MAX)
typedef unsigned long cairn_least_u32;
#    endif

#    if CAIRN_USE_INT64

#        ifdef CAIRN_I64_TYPE
#            define CAIRN_I64_MAX (CAIRN_I64_TYPE_MAX)
#            define CAIRN_I64_MIN (CAIRN_I64_TYPE_MIN)
typedef CAIRN_I64_TYPE cairn_i64;
#        endif

#        ifdef CAIRN_U64_TYPE
#            define CAIRN_U64_MAX (CAIRN_U64_TYPE_MAX)
typedef CAIRN_U64_TYPE cairn_u64;
#        endif

#        define CAIRN_LEAST_I64_MAX (CAIRN_LEAST_I64_TYPE_MAX)
#        define CAIRN_LEAST_I64_MIN (CAIRN_LEAST_I64_TYPE_MIN)
#        define CAIRN_LEAST_U64_MAX (CAIRN_LEAST_U64_TYPE_MAX)

typedef CAIRN_LEAST_I64_TYPE cairn_least_i64;
typedef CAIRN_LEAST_U64_TYPE cairn_least_u64;

#    endif

#endif

#endif
