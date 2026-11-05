/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BASE_DEBUG_H
#define BASE_DEBUG_H

#if defined(__GNUC__) || defined(__clang__)
#    define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#    define UNLIKELY(x) (x)
#endif

#ifndef NDEBUG
void err_assert_failed(const char *expr, const char *file, int line);
#    define ASSERT(condition)                                                  \
        do                                                                     \
        {                                                                      \
            if (UNLIKELY(!(condition)))                                        \
            {                                                                  \
                err_assert_failed(#condition, __FILE__, __LINE__);             \
            }                                                                  \
        } while (0)
#else
#    define ASSERT(condition) ((void)0)
#endif

#endif
