/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CR_DEBUG_H
#define CR_DEBUG_H

#include <cairn/crbool.h>
#include <cairn/crdef.h>

#ifndef NDEBUG
#    define CR_ASSERT(condition)                                               \
        do                                                                     \
        {                                                                      \
            if (!(condition))                                                  \
            {                                                                  \
                crdlog(#condition, __FILE__, __LINE__);                        \
                crdbreak();                                                    \
                crdterm();                                                     \
            }                                                                  \
        } while (CR_FALSE)
#else
#    define CR_ASSERT(condition) ((void)0)
#endif

/* Print or log the assertion error, if possible. */
void crdlog(const char *expr, const char *file, int line);
/* Invoke a debugger breakpoint, if possible. */
void crdbreak(void);
/* Terminate the program execution after a failed assertion. */
CR_NORETURN void crdterm(void);

#endif
