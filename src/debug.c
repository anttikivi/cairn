/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "debug.h"

#ifndef NDEBUG

#    include <stddef.h>
#    include <stdlib.h>

#    include "bool.h"
#    include "int.h"

#    ifdef _WIN32
#        define WIN32_LEAN_AND_MEAN
#        include <windows.h>
#    else
#        include <errno.h>
#        include <unistd.h>
#        ifndef ERR_STDERR_FD
#            define ERR_STDERR_FD (2)
#        endif
#    endif

#    ifndef ASSERT_MSG_MAX_BYTES
#        define ASSERT_MSG_MAX_BYTES (1024)
#    endif

#    ifndef ASSERT_MAX_OUTPUT_RETRIES
#        define ASSERT_MAX_OUTPUT_RETRIES (50U)
#    endif

static void
appendd(char *buf, size_t *len, size_t cap, unsigned int d)
{
    char tmp[16];
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
    size_t i = 0U;
    if (s != NULL)
    {
        while ((s[i] != '\0') && (*len < (cap - 1U)))
        {
            buf[*len] = s[i];
            (*len)++;
            i++;
        }
    }
}

void
err_assert_failed(const char *expr, const char *file, int line)
{
    char msg[ASSERT_MSG_MAX_BYTES];
    size_t len = 0U;

    appends(msg, &len, sizeof(msg), "Assertion failed: ");
    appends(msg, &len, sizeof(msg), expr);
    appends(msg, &len, sizeof(msg), " (");
    appends(msg, &len, sizeof(msg), file);
    appends(msg, &len, sizeof(msg), ": ");
    appendd(msg, &len, sizeof(msg), (unsigned int)line);
    appends(msg, &len, sizeof(msg), ")\n");

    msg[len] = '\0';

#    ifdef _WIN32
    {
        HANDLE handle = GetStdHandle(STD_ERROR_HANDLE);
        DWORD written = 0U;
        if ((handle != NULL) && (handle != INVALID_HANDLE_VALUE))
        {
            bool end = false;
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
                    end = true;
                }
                else
                {
                    written += w;
                }
            }
        }
    }
#    else
    {
        size_t written = 0U;
        u8 retries = 0U;
        bool end = false;
        while ((written < len) && !end)
        {
            ssize_t ret = 0;
            errno = 0;
            ret = write(ERR_STDERR_FD, &msg[written], len - written);
            if (ret <= 0)
            {
                if ((errno == EINTR) || (errno == EAGAIN) ||
                    (errno == EWOULDBLOCK))
                {
                    retries++;
                    if (retries >= ASSERT_MAX_OUTPUT_RETRIES)
                    {
                        end = true;
                    }
                }
                else
                {
                    end = true;
                }
            }
            else
            {
                written += (size_t)ret;
                retries = 0U;
            }
        }
    }
#    endif

#    if defined(__GNUC__) || defined(__clang__)
    __builtin_trap();
#    elif defined(_MSC_VER)
    __debugbreak();
#    else
    *(volatile int *)0 = 0;
#    endif

    abort();
}

#endif
