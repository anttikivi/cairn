/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "io.h"

#include <stddef.h>

#include "debug.h"
#include "error.h"
#include "int.h"

#ifndef IO_MAX_OUTPUT_BYTES
#    define IO_MAX_OUTPUT_BYTES (4096U)
#endif

#ifndef IO_MAX_OUTPUT_RETRIES
#    define IO_MAX_OUTPUT_RETRIES (100U)
#endif

#if IO_MAX_OUTPUT_RETRIES > UCHAR_MAX
#    error                                                                     \
        "value of IO_MAX_OUTPUT_RETRIES is greater than the maximum of uint8_t"
#endif

#ifdef _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <windows.h>
#else
#    include "int.h"
#    include <errno.h>
#    include <unistd.h>
#    ifndef VERSOLVE_STDOUT_FD
#        define VERSOLVE_STDOUT_FD (1)
#    endif
#    ifndef VERSOLVE_STDERR_FD
#        define VERSOLVE_STDERR_FD (2)
#    endif
#endif

#ifdef _WIN32
static enum error
win32_write_all(DWORD handle_id, const char *s)
{
    enum error result = ERR_OK;
    HANDLE handle;
    size_t len = 0U;
    DWORD written = 0U;

    if (s == NULL)
    {
        result = ERR_IO_INVALID;
    }

    if (result == ERR_OK)
    {
        handle = GetStdHandle(handle_id);
        if ((handle == NULL) || (handle == INVALID_HANDLE_VALUE))
        {
            result = ERR_IO_WRITE_FAILED;
        }
    }

    if (result == ERR_OK)
    {
        while ((len < IO_MAX_OUTPUT_BYTES) && s[len] != '\0')
        {
            len++;
        }
    }

    if ((result == ERR_OK) && (len == (size_t)IO_MAX_OUTPUT_BYTES) &&
        (s[len] != '\0'))
    {
        result = ERR_IO_INVALID;
    }

    while ((written < (DWORD)len) && (result == ERR_OK))
    {
        BOOL ok;
        DWORD w;
        size_t remaining = len - (size_t)written;
        DWORD to_write =
            (remaining > 0xFFFFFFFFU) ? 0xFFFFFFFFU : (DWORD)remaining;

        ok = WriteFile(handle, &s[written], to_write, &w, NULL);

        if ((ok == FALSE) || (w == 0U))
        {
            result = ERR_IO_WRITE_FAILED;
        }
        else
        {
            written += w;
        }
    }

    return result;
}
#else
static enum error
posix_write_all(int fd, const char *s)
{
    enum error result = ERR_OK;
    size_t len = 0U;
    size_t written = 0U;
    u8 retries = 0U;

    if (s == NULL)
    {
        result = ERR_IO_INVALID;
    }

    if (result == ERR_OK)
    {
        while ((len < IO_MAX_OUTPUT_BYTES) && s[len] != '\0')
        {
            len++;
        }
    }

    if ((result == ERR_OK) && (len == (size_t)IO_MAX_OUTPUT_BYTES) &&
        (s[len] != '\0'))
    {
        result = ERR_IO_INVALID;
    }

    while ((written < len) && (result == ERR_OK))
    {
        ssize_t ret = 0;
        errno = 0;
        ret = write(fd, &s[written], len - written);
        if (ret <= 0)
        {
            if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
            {
                retries++;
                if (retries >= IO_MAX_OUTPUT_RETRIES)
                {
                    result = ERR_IO_WRITE_FAILED;
                }
            }
            else
            {
                result = ERR_IO_WRITE_FAILED;
            }
        }
        else
        {
            written += (size_t)ret;
            retries = 0U;
        }
    }

    return result;
}
#endif

enum error
io_print_out(const char *s)
{
    ASSERT(s != NULL);
#ifdef _WIN32
    return win32_write_all(STD_OUTPUT_HANDLE, s);
#else
    return posix_write_all(VERSOLVE_STDOUT_FD, s);
#endif
}

enum error
io_print_err(const char *s)
{
    ASSERT(s != NULL);
#ifdef _WIN32
    return win32_write_all(STD_ERROR_HANDLE, s);
#else
    return posix_write_all(VERSOLVE_STDERR_FD, s);
#endif
}
