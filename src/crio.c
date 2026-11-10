/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <crio.h>

#include <limits.h>
#include <stddef.h>

#include <crdbg.h>
#include <crerr.h>
#include <crint.h>

#ifndef CR_IO_MAX_OUTPUT_BYTES
#    define CR_IO_MAX_OUTPUT_BYTES (4096U)
#endif

#ifndef CR_IO_MAX_OUTPUT_RETRIES
#    define CR_IO_MAX_OUTPUT_RETRIES (100U)
#endif

#if CR_IO_MAX_OUTPUT_RETRIES > UCHAR_MAX
#    error                                                                     \
        "value of CR_IO_MAX_OUTPUT_RETRIES is greater than the maximum of unsigned char"
#endif

#ifdef _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <windows.h>
#else
#    include <errno.h>
#    include <unistd.h>
#    ifndef CR_STDOUT_FD
#        define CR_STDOUT_FD (1)
#    endif
#    ifndef CR_STDERR_FD
#        define CR_STDERR_FD (2)
#    endif
#endif

#ifdef _WIN32
static enum cr_err
win32_write_all(DWORD handle_id, const char *s)
{
    enum cr_err result = CR_ERR_OK;
    HANDLE handle = NULL;
    size_t len = 0U;
    DWORD written = 0U;

    if (s == NULL)
    {
        result = CR_ERR_IO_NULL_STRING;
    }

    if (result == CR_ERR_OK)
    {
        handle = GetStdHandle(handle_id);
        if ((handle == NULL) || (handle == INVALID_HANDLE_VALUE))
        {
            result = CR_ERR_IO_WRITE_FAILED;
        }
    }

    if (result == CR_ERR_OK)
    {
        while ((len < CR_IO_MAX_OUTPUT_BYTES) && s[len] != '\0')
        {
            len++;
        }
    }

    if ((result == CR_ERR_OK) && (len == (size_t)CR_IO_MAX_OUTPUT_BYTES) &&
        (s[len] != '\0'))
    {
        result = CR_ERR_IO_INPUT_OVERFLOW;
    }

    while ((written < (DWORD)len) && (result == CR_ERR_OK))
    {
        BOOL ok;
        DWORD w;
        size_t remaining = len - (size_t)written;
        DWORD to_write =
            (remaining > 0xFFFFFFFFU) ? 0xFFFFFFFFU : (DWORD)remaining;

        ok = WriteFile(handle, &s[written], to_write, &w, NULL);

        if ((ok == FALSE) || (w == 0U))
        {
            result = CR_ERR_IO_WRITE_FAILED;
        }
        else
        {
            written += w;
        }
    }

    return result;
}
#else
static enum cr_err
posix_write_all(int fd, const char *s)
{
    enum cr_err result = CR_ERR_OK;
    size_t len = 0U;
    size_t written = 0U;
    cr_least_u8 retries = 0U;

    if (s == NULL)
    {
        result = CR_ERR_IO_NULL_STRING;
    }

    if (result == CR_ERR_OK)
    {
        while ((len < CR_IO_MAX_OUTPUT_BYTES) && s[len] != '\0')
        {
            len++;
        }
    }

    if ((result == CR_ERR_OK) && (len == (size_t)CR_IO_MAX_OUTPUT_BYTES) &&
        (s[len] != '\0'))
    {
        result = CR_ERR_IO_INPUT_OVERFLOW;
    }

    while ((written < len) && (result == CR_ERR_OK))
    {
        ssize_t ret = 0;
        errno = 0;
        ret = write(fd, &s[written], len - written);
        if (ret <= 0)
        {
            if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
            {
                retries++;
                if (retries >= CR_IO_MAX_OUTPUT_RETRIES)
                {
                    result = CR_ERR_IO_WRITE_FAILED;
                }
            }
            else
            {
                result = CR_ERR_IO_WRITE_FAILED;
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

enum cr_err
criout(const char *s)
{
    CR_ASSERT(s != NULL);
#ifdef _WIN32
    return win32_write_all(STD_OUTPUT_HANDLE, s);
#else
    return posix_write_all(CR_STDOUT_FD, s);
#endif
}

enum cr_err
crioerr(const char *s)
{
    CR_ASSERT(s != NULL);
#ifdef _WIN32
    return win32_write_all(STD_ERROR_HANDLE, s);
#else
    return posix_write_all(CR_STDERR_FD, s);
#endif
}
