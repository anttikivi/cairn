/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CAIRN_DEBUG_H
#define CAIRN_DEBUG_H

#ifndef NDEBUG
#    define CAIRN_ASSERT(condition)                                            \
        do                                                                     \
        {                                                                      \
            if (!(condition))                                                  \
            {                                                                  \
                cairn_err_assert_failed(#condition, __FILE__, __LINE__);       \
            }                                                                  \
        } while (0 != 0)
#else
#    define CAIRN_ASSERT(condition) ((void)0)
#endif

void cairn_err_assert_failed(const char *expr, const char *file, int line);

#endif
