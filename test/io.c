/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <stdlib.h>

#include <crbool.h>
#include <crerr.h>
#include <crio.h>
#include <crstr.h>

#ifdef _WIN32
#    include <windows.h>
#else
#    include <unistd.h>
#endif

int
main(int argc, char **argv) /* cppcheck-suppress misra-c2012-8.6 */
{
    int result = EXIT_SUCCESS;
    enum cr_err expected = CR_ERR_OK;
    enum cr_err err;
    const char *stream;
    const char *text = NULL;
    crbool to_stderr = CR_FALSE;

    if (argc != 4)
    {
        result = EXIT_FAILURE;
    }

    stream = argv[1];

    if ((result == EXIT_SUCCESS) &&
        (crsncmp(stream, 7, "stdout", sizeof("stdout")) != 0) &&
        (crsncmp(stream, 7, "stderr", sizeof("stderr")) != 0))
    {
        result = EXIT_FAILURE;
    }

    if (result == EXIT_SUCCESS)
    {
        if (crsncmp(stream, 7, "stderr", sizeof("stderr")) == 0)
        {
            to_stderr = CR_TRUE;
        }

        text = argv[3];

        if (crsncmp(argv[2], 8, "embed", sizeof("embed")) == 0)
        {
            /*
             * Override the given text and print a text with an embedded null
             * byte.
             */
            text = "abc\0def";
        }
        else if (crsncmp(argv[2], 10, "oversized", sizeof("oversized")) == 0)
        {
            expected = CR_ERR_IO_INPUT_OVERFLOW;
        }
        else if (crsncmp(argv[2], 15, "invalid-handle",
                         sizeof("invalid-handle")) == 0)
        {
            expected = CR_ERR_IO_WRITE_FAILED;
#ifdef _WIN32
            if (SetStdHandle(to_stderr ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE,
                             INVALID_HANDLE_VALUE) == FALSE)
            {
                result = EXIT_FAILURE;
            }
#else
            if (close(to_stderr ? 2 : 1) != 0)
            {
                result = EXIT_FAILURE;
            }
#endif
        }
        else if (crsncmp(argv[2], 5, "text", sizeof("text")) != 0)
        {
            result = EXIT_FAILURE;
        }
        else
        {
            ; /* no-op: argument is "text" */
        }
    }

    if (result == EXIT_SUCCESS)
    {
        /* False positive, crbool is essentially Boolean here. */
        /* cppcheck-suppress misra-c2012-14.4 */
        if (to_stderr)
        {
            err = crioerr(text);
        }
        else
        {
            err = criout(text);
        }

        if (err != expected)
        {
            result = EXIT_FAILURE;
        }
    }

    return result;
}
