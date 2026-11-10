/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRINT_H
#define CRINT_H

#include <crcfg.h>

#include <limits.h>

/* These types and macro definitions are part of the public API. */
/* cppcheck-suppress-begin [misra-c2012-2.3, misra-c2012-2.5] */

#if CR_USE_STDINT

#    include <stdint.h>

#    if defined(INT8_MAX) && defined(INT8_MIN)
#        define CRI8_MAX (INT8_MAX)
#        define CRI8_MIN (INT8_MIN)
typedef int8_t cri8;
#    endif

#    if defined(UINT8_MAX)
#        define CRU8_MAX (UINT8_MAX)
typedef uint8_t cru8;
#    endif

#    define CR_LEAST_I8_MAX (INT_LEAST8_MAX)
#    define CR_LEAST_I8_MIN (INT_LEAST8_MIN)
#    define CR_LEAST_U8_MAX (UINT_LEAST8_MAX)

typedef int_least8_t cr_least_i8;
typedef uint_least8_t cr_least_u8;

#    if defined(INT16_MAX) && defined(INT16_MIN)
#        define CRI16_MAX (INT16_MAX)
#        define CRI16_MIN (INT16_MIN)
typedef int16_t cri16;
#    endif

#    if defined(UINT16_MAX)
#        define CRU16_MAX (UINT16_MAX)
typedef uint16_t cru16;
#    endif

#    define CR_LEAST_I16_MAX (INT_LEAST16_MAX)
#    define CR_LEAST_I16_MIN (INT_LEAST16_MIN)
#    define CR_LEAST_U16_MAX (UINT_LEAST16_MAX)

typedef int_least16_t cr_least_i16;
typedef uint_least16_t cr_least_u16;

#    if defined(INT32_MAX) && defined(INT32_MIN)
#        define CRI32_MAX (INT32_MAX)
#        define CRI32_MIN (INT32_MIN)
typedef int32_t cri32;
#    endif

#    if defined(UINT32_MAX)
#        define CRU32_MAX (UINT32_MAX)
typedef uint32_t cru32;
#    endif

#    define CR_LEAST_I32_MAX (INT_LEAST32_MAX)
#    define CR_LEAST_I32_MIN (INT_LEAST32_MIN)
#    define CR_LEAST_U32_MAX (UINT_LEAST32_MAX)

typedef int_least32_t cr_least_i32;
typedef uint_least32_t cr_least_u32;

#    if CR_USE_INT64
#        if defined(INT64_MAX) && defined(INT64_MIN)
#            define CRI64_MAX (INT64_MAX)
#            define CRI64_MIN (INT64_MIN)
typedef int64_t cri64;
#        endif

#        if defined(UINT64_MAX)
#            define CRU64_MAX (UINT64_MAX)
typedef uint64_t cru64;
#        endif

#        define CR_LEAST_I64_MAX (INT_LEAST64_MAX)
#        define CR_LEAST_I64_MIN (INT_LEAST64_MIN)
#        define CR_LEAST_U64_MAX (UINT_LEAST64_MAX)

typedef int_least64_t cr_least_i64;
typedef uint_least64_t cr_least_u64;
#    endif

#else

#    ifdef CR_I8_TYPE
#        define CRI8_MAX (CR_I8_TYPE_MAX)
#        define CRI8_MIN (CR_I8_TYPE_MIN)
typedef CR_I8_TYPE cri8;
#    endif

#    ifdef CR_U8_TYPE
#        define CRU8_MAX (CR_U8_TYPE_MAX)
typedef CR_U8_TYPE cru8;
#    endif

#    define CR_LEAST_I8_MAX (SCHAR_MAX)
#    define CR_LEAST_I8_MIN (SCHAR_MIN)
#    define CR_LEAST_U8_MAX (UCHAR_MAX)

typedef signed char cr_least_i8;
typedef unsigned char cr_least_u8;

#    ifdef CR_I16_TYPE
#        define CRI16_MAX (CR_I16_TYPE_MAX)
#        define CRI16_MIN (CR_I16_TYPE_MIN)
typedef CR_I16_TYPE cri16;
#    endif

#    ifdef CR_U16_TYPE
#        define CRU16_MAX (CR_U16_TYPE_MAX)
typedef CR_U16_TYPE cru16;
#    endif

#    if SCHAR_MAX >= 32767 && SCHAR_MIN <= -32767
#        define CR_LEAST_I16_MAX (SCHAR_MAX)
#        define CR_LEAST_I16_MIN (SCHAR_MIN)
typedef signed char cr_least_i16;
#    else
#        define CR_LEAST_I16_MAX (SHRT_MAX)
#        define CR_LEAST_I16_MIN (SHRT_MIN)
typedef short cr_least_i16;
#    endif

#    if UCHAR_MAX >= 65535U
#        define CR_LEAST_U16_MAX (UCHAR_MAX)
typedef unsigned char cr_least_u16;
#    else
#        define CR_LEAST_U16_MAX (USHRT_MAX)
typedef unsigned short cr_least_u16;
#    endif

#    ifdef CR_I32_TYPE
#        define CRI32_MAX (CR_I32_TYPE_MAX)
#        define CRI32_MIN (CR_I32_TYPE_MIN)
typedef CR_I32_TYPE cri32;
#    endif

#    ifdef CR_U32_TYPE
#        define CRU32_MAX (CR_U32_TYPE_MAX)
typedef CR_U32_TYPE cru32;
#    endif

#    if SCHAR_MAX >= 2147483647 && SCHAR_MIN <= -2147483647
#        define CR_LEAST_I32_MAX (SCHAR_MAX)
#        define CR_LEAST_I32_MIN (SCHAR_MIN)
typedef signed char cr_least_i32;
#    elif SHRT_MAX >= 2147483647 && SHRT_MIN <= -2147483647
#        define CR_LEAST_I32_MAX (SHRT_MAX)
#        define CR_LEAST_I32_MIN (SHRT_MIN)
typedef short cr_least_i32;
#    elif INT_MAX >= 2147483647 && INT_MIN <= -2147483647
#        define CR_LEAST_I32_MAX (INT_MAX)
#        define CR_LEAST_I32_MIN (INT_MIN)
typedef int cr_least_i32;
#    else
#        define CR_LEAST_I32_MAX (LONG_MAX)
#        define CR_LEAST_I32_MIN (LONG_MIN)
typedef long cr_least_i32;
#    endif

#    if UCHAR_MAX >= 4294967295U
#        define CR_LEAST_U32_MAX (UCHAR_MAX)
typedef unsigned char cr_least_u32;
#    elif USHRT_MAX >= 4294967295U
#        define CR_LEAST_U32_MAX (USHRT_MAX)
typedef unsigned short cr_least_u32;
#    elif UINT_MAX >= 4294967295U
#        define CR_LEAST_U32_MAX (UINT_MAX)
typedef unsigned int cr_least_u32;
#    else
#        define CR_LEAST_U32_MAX (ULONG_MAX)
typedef unsigned long cr_least_u32;
#    endif

#    if CR_USE_INT64

#        ifdef CR_I64_TYPE
#            define CRI64_MAX (CR_I64_TYPE_MAX)
#            define CRI64_MIN (CR_I64_TYPE_MIN)
typedef CR_I64_TYPE cri64;
#        endif

#        ifdef CR_U64_TYPE
#            define CRU64_MAX (CR_U64_TYPE_MAX)
typedef CR_U64_TYPE cru64;
#        endif

#        define CR_LEAST_I64_MAX (CR_LEAST_I64_TYPE_MAX)
#        define CR_LEAST_I64_MIN (CR_LEAST_I64_TYPE_MIN)
#        define CR_LEAST_U64_MAX (CR_LEAST_U64_TYPE_MAX)

typedef CR_LEAST_I64_TYPE cr_least_i64;
typedef CR_LEAST_U64_TYPE cr_least_u64;

#    endif

#endif

/* cppcheck-suppress-end [misra-c2012-2.3, misra-c2012-2.5] */

#endif
