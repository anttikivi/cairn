/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <cairn/test.h>

#include <cairn/buffer.h>
#include <cairn/io.h>

void
cairn_test_start(struct cairn_test_status *status, const char *name)
{
    status->name = name;
    status->failures = 0U;
    cairn_io_print_err("\n");
    cairn_io_print_err(name);
    cairn_io_print_err("\n");
}

int
cairn_test_result(struct cairn_test_status *status)
{
    int result = EXIT_SUCCESS;
    if (status->failures > 0)
    {
        cairn_io_print_err("failures in ");
        cairn_io_print_err(status->name);
        cairn_io_print_err("\n");
        result = EXIT_FAILURE;
    }
    else
    {
        cairn_io_print_err("all tests in ");
        cairn_io_print_err(status->name);
        cairn_io_print_err(" passed\n");
    }
    return result;
}

void
cairn_test_expect_char_eq(struct cairn_test_status *status, const char *file,
                          int line, const char *expr, char expected,
                          char actual)
{
    if (expected != actual)
    {
        struct cairn_buffer buf;
        cairn_buffer_init(&buf);
        cairn_buffer_append_str(&buf, file);
        cairn_buffer_append_char(&buf, ':');
        cairn_buffer_append_int(&buf, line);
        cairn_buffer_append_str(&buf, ":  expected ");
        cairn_buffer_append_str(&buf, expr);
        cairn_buffer_append_str(&buf, " == ");
        if (expected == '\0')
        {
            cairn_buffer_append_str(&buf, "\\0");
        }
        else
        {
            cairn_buffer_append_char(&buf, expected);
        }
        cairn_buffer_append_str(&buf, ", got ");
        if (actual == '\0')
        {
            cairn_buffer_append_str(&buf, "\\0");
        }
        else
        {
            cairn_buffer_append_char(&buf, actual);
        }
        cairn_buffer_append_char(&buf, '\n');
        cairn_io_print_err(buf.data);
        status->failures++;
    }
}

void
cairn_test_expect_int_eq(struct cairn_test_status *status, const char *file,
                         int line, const char *expr, int expected, int actual)
{
    if (expected != actual)
    {
        struct cairn_buffer buf;
        cairn_buffer_init(&buf);
        cairn_buffer_append_str(&buf, file);
        cairn_buffer_append_char(&buf, ':');
        cairn_buffer_append_int(&buf, line);
        cairn_buffer_append_str(&buf, ":  expected ");
        cairn_buffer_append_str(&buf, expr);
        cairn_buffer_append_str(&buf, " == ");
        cairn_buffer_append_int(&buf, expected);
        cairn_buffer_append_str(&buf, ", got ");
        cairn_buffer_append_int(&buf, actual);
        cairn_buffer_append_char(&buf, '\n');
        cairn_io_print_err(buf.data);
        status->failures++;
    }
}

void
cairn_test_expect_int_ge(struct cairn_test_status *status, const char *file,
                         int line, const char *expr, int cmp, int actual)
{
    if (cmp > actual)
    {
        struct cairn_buffer buf;
        cairn_buffer_init(&buf);
        cairn_buffer_append_str(&buf, file);
        cairn_buffer_append_char(&buf, ':');
        cairn_buffer_append_int(&buf, line);
        cairn_buffer_append_str(&buf, ":  expected ");
        cairn_buffer_append_str(&buf, expr);
        cairn_buffer_append_str(&buf, " >= ");
        cairn_buffer_append_int(&buf, cmp);
        cairn_buffer_append_str(&buf, ", got ");
        cairn_buffer_append_int(&buf, actual);
        cairn_buffer_append_char(&buf, '\n');
        cairn_io_print_err(buf.data);
        status->failures++;
    }
}

void
cairn_test_expect_int_gt(struct cairn_test_status *status, const char *file,
                         int line, const char *expr, int cmp, int actual)
{
    if (cmp >= actual)
    {
        struct cairn_buffer buf;
        cairn_buffer_init(&buf);
        cairn_buffer_append_str(&buf, file);
        cairn_buffer_append_char(&buf, ':');
        cairn_buffer_append_int(&buf, line);
        cairn_buffer_append_str(&buf, ":  expected ");
        cairn_buffer_append_str(&buf, expr);
        cairn_buffer_append_str(&buf, " > ");
        cairn_buffer_append_int(&buf, cmp);
        cairn_buffer_append_str(&buf, ", got ");
        cairn_buffer_append_int(&buf, actual);
        cairn_buffer_append_char(&buf, '\n');
        cairn_io_print_err(buf.data);
        status->failures++;
    }
}

void
cairn_test_expect_int_le(struct cairn_test_status *status, const char *file,
                         int line, const char *expr, int cmp, int actual)
{
    if (cmp < actual)
    {
        struct cairn_buffer buf;
        cairn_buffer_init(&buf);
        cairn_buffer_append_str(&buf, file);
        cairn_buffer_append_char(&buf, ':');
        cairn_buffer_append_int(&buf, line);
        cairn_buffer_append_str(&buf, ":  expected ");
        cairn_buffer_append_str(&buf, expr);
        cairn_buffer_append_str(&buf, " <= ");
        cairn_buffer_append_int(&buf, cmp);
        cairn_buffer_append_str(&buf, ", got ");
        cairn_buffer_append_int(&buf, actual);
        cairn_buffer_append_char(&buf, '\n');
        cairn_io_print_err(buf.data);
        status->failures++;
    }
}

void
cairn_test_expect_int_lt(struct cairn_test_status *status, const char *file,
                         int line, const char *expr, int cmp, int actual)
{
    if (cmp <= actual)
    {
        struct cairn_buffer buf;
        cairn_buffer_init(&buf);
        cairn_buffer_append_str(&buf, file);
        cairn_buffer_append_char(&buf, ':');
        cairn_buffer_append_int(&buf, line);
        cairn_buffer_append_str(&buf, ":  expected ");
        cairn_buffer_append_str(&buf, expr);
        cairn_buffer_append_str(&buf, " < ");
        cairn_buffer_append_int(&buf, cmp);
        cairn_buffer_append_str(&buf, ", got ");
        cairn_buffer_append_int(&buf, actual);
        cairn_buffer_append_char(&buf, '\n');
        cairn_io_print_err(buf.data);
        status->failures++;
    }
}

void
cairn_test_expect_size_eq(struct cairn_test_status *status, const char *file,
                          int line, const char *expr, size_t expected,
                          size_t actual)
{
    if (expected != actual)
    {
        struct cairn_buffer buf;
        cairn_buffer_init(&buf);
        cairn_buffer_append_str(&buf, file);
        cairn_buffer_append_char(&buf, ':');
        cairn_buffer_append_int(&buf, line);
        cairn_buffer_append_str(&buf, ":  expected ");
        cairn_buffer_append_str(&buf, expr);
        cairn_buffer_append_str(&buf, " == ");
        cairn_buffer_append_size(&buf, expected);
        cairn_buffer_append_str(&buf, ", got ");
        cairn_buffer_append_size(&buf, actual);
        cairn_buffer_append_char(&buf, '\n');
        cairn_io_print_err(buf.data);
        status->failures++;
    }
}
