/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <crdbg.h>

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

#include <crbool.h>

#ifdef _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <windows.h>
#else
#    include <crint.h>
#    include <errno.h>
#    include <unistd.h>
#    ifndef CR_ERR_STDERR_FD
#        define CR_ERR_STDERR_FD (2)
#    endif
#endif

#ifndef CR_ASSERT_MSG_MAX_BYTES
#    define CR_ASSERT_MSG_MAX_BYTES (1024)
#endif

#if CR_ASSERT_MSG_MAX_BYTES < 1
#    error "maximum size for assert message cannot be less than one byte"
#endif

#ifndef CR_ASSERT_MAX_OUTPUT_RETRIES
#    define CR_ASSERT_MAX_OUTPUT_RETRIES (50U)
#endif

#ifndef _WIN32
#    if (CR_ASSERT_MAX_OUTPUT_RETRIES < 1) ||                                  \
        (CR_ASSERT_MAX_OUTPUT_RETRIES > CR_LEAST_U8_MAX)
#        error "assert output retry limit is outside the range"
#    endif
#endif

static void
appendd(unsigned int d, char *buf, size_t *len, size_t cap)
{
    char tmp[sizeof(unsigned int) * (size_t)CHAR_BIT];
    size_t i = 0U;
    unsigned int u = d;

    do
    {
        tmp[i] = (char)('0' + (u % 10U));
        i++;
        u /= 10U;
    } while (u > 0U);

    while ((i > 0U) && (*len < (cap - 1U)))
    {
        i--;
        buf[*len] = tmp[i];
        (*len)++;
    }
}

static void
appends(char *buf, size_t *len, size_t cap, const char *s)
{
    if (s != NULL)
    {
        size_t i = 0U;
        while ((s[i] != '\0') && (*len < (cap - 1U)))
        {
            buf[*len] = s[i];
            (*len)++;
            i++;
        }
    }
}

void
crdlog(const char *expr, const char *file, int line)
{
    char msg[CR_ASSERT_MSG_MAX_BYTES];
    size_t len = 0U;

    appends(msg, &len, sizeof(msg), "Assertion failed: ");
    appends(msg, &len, sizeof(msg), expr);
    appends(msg, &len, sizeof(msg), " (");
    appends(msg, &len, sizeof(msg), file);
    appends(msg, &len, sizeof(msg), ": ");
    appendd((unsigned int)line, msg, &len, sizeof(msg));
    appends(msg, &len, sizeof(msg), ")\n");

    msg[len] = '\0';

#ifdef _WIN32
    {
        HANDLE handle = GetStdHandle(STD_ERROR_HANDLE);
        if ((handle != NULL) && (handle != INVALID_HANDLE_VALUE))
        {
            DWORD written = 0U;
            crbool end = CR_FALSE;
            while ((written < (DWORD)len) && !end)
            {
                BOOL ok;
                DWORD w;
                size_t remaining = len - (size_t)written;
                DWORD to_write =
                    (remaining > 0xFFFFFFFFU) ? 0xFFFFFFFFU : (DWORD)remaining;

                ok = WriteFile(handle, &msg[written], to_write, &w, NULL);

                if ((ok == FALSE) || (w == 0U))
                {
                    end = CR_TRUE;
                }
                else
                {
                    written += w;
                }
            }
        }
    }
#else
    {
        size_t written = 0U;
        cr_least_u8 retries = 0U;
        crbool end = CR_FALSE;
        while ((written < len) && !end)
        {
            ssize_t ret = 0;
            errno = 0;
            ret = write(CR_ERR_STDERR_FD, &msg[written], len - written);
            if (ret <= 0)
            {
                /* POSIX write is an errno-setting function. */
                /* cppcheck-suppress-begin [misra-config, misra-c2012-22.10] */
                if ((errno == EINTR) || (errno == EAGAIN) ||
                    (errno == EWOULDBLOCK))
                {
                    /* cppcheck-suppress-end [misra-config, misra-c2012-22.10]
                     */
                    retries++;
                    if (retries >= CR_ASSERT_MAX_OUTPUT_RETRIES)
                    {
                        end = CR_TRUE;
                    }
                }
                else
                {
                    end = CR_TRUE;
                }
            }
            else
            {
                written += (size_t)ret;
                retries = 0U;
            }
        }
    }
#endif
}

void
crdbreak(void)
{
#if CR_BREAKPOINTS
#    if defined(__clang__)
    __builtin_debugtrap();
#    elif defined(_MSC_VER)
    DebugBreak();
#    endif
#endif
}

void
crdterm(void)
{
#if defined(__clang__) || defined(__GNUC__)
    __builtin_trap();
#else
    /* Deviation-001 */
    /* cppcheck-suppress misra-c2012-21.8 */
    abort();
#endif
}
