/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include "test.h"

#include "../src/base/buffer.h"
#include "../src/base/io.h"

void
test_start(struct test_status *status, const char *name)
{
    status->name = name;
    status->failures = 0U;
    io_print_err("\n");
    io_print_err(name);
    io_print_err("\n");
}

int
test_result(struct test_status *status)
{
    int result = EXIT_SUCCESS;
    if (status->failures > 0)
    {
        io_print_err("failures in ");
        io_print_err(status->name);
        io_print_err("\n");
        result = EXIT_FAILURE;
    }
    else
    {
        io_print_err("all tests in ");
        io_print_err(status->name);
        io_print_err(" passed\n");
    }
    return result;
}

void
test_expect_char_eq(struct test_status *status, const char *file, int line,
                    const char *expr, char expected, char actual)
{
    if (expected != actual)
    {
        struct buffer buf;
        buffer_init(&buf);
        buffer_append_str(&buf, file);
        buffer_append_char(&buf, ':');
        buffer_append_int(&buf, line);
        buffer_append_str(&buf, ":  expected ");
        buffer_append_str(&buf, expr);
        buffer_append_str(&buf, " == ");
        if (expected == '\0')
        {
            buffer_append_str(&buf, "\\0");
        }
        else
        {
            buffer_append_char(&buf, expected);
        }
        buffer_append_str(&buf, ", got ");
        if (actual == '\0')
        {
            buffer_append_str(&buf, "\\0");
        }
        else
        {
            buffer_append_char(&buf, actual);
        }
        buffer_append_char(&buf, '\n');
        io_print_err(buf.data);
        status->failures++;
    }
}

void
test_expect_int_eq(struct test_status *status, const char *file, int line,
                   const char *expr, int expected, int actual)
{
    if (expected != actual)
    {
        struct buffer buf;
        buffer_init(&buf);
        buffer_append_str(&buf, file);
        buffer_append_char(&buf, ':');
        buffer_append_int(&buf, line);
        buffer_append_str(&buf, ":  expected ");
        buffer_append_str(&buf, expr);
        buffer_append_str(&buf, " == ");
        buffer_append_int(&buf, expected);
        buffer_append_str(&buf, ", got ");
        buffer_append_int(&buf, actual);
        buffer_append_char(&buf, '\n');
        io_print_err(buf.data);
        status->failures++;
    }
}

void
test_expect_int_ge(struct test_status *status, const char *file, int line,
                   const char *expr, int cmp, int actual)
{
    if (cmp > actual)
    {
        struct buffer buf;
        buffer_init(&buf);
        buffer_append_str(&buf, file);
        buffer_append_char(&buf, ':');
        buffer_append_int(&buf, line);
        buffer_append_str(&buf, ":  expected ");
        buffer_append_str(&buf, expr);
        buffer_append_str(&buf, " >= ");
        buffer_append_int(&buf, cmp);
        buffer_append_str(&buf, ", got ");
        buffer_append_int(&buf, actual);
        buffer_append_char(&buf, '\n');
        io_print_err(buf.data);
        status->failures++;
    }
}

void
test_expect_int_gt(struct test_status *status, const char *file, int line,
                   const char *expr, int cmp, int actual)
{
    if (cmp >= actual)
    {
        struct buffer buf;
        buffer_init(&buf);
        buffer_append_str(&buf, file);
        buffer_append_char(&buf, ':');
        buffer_append_int(&buf, line);
        buffer_append_str(&buf, ":  expected ");
        buffer_append_str(&buf, expr);
        buffer_append_str(&buf, " > ");
        buffer_append_int(&buf, cmp);
        buffer_append_str(&buf, ", got ");
        buffer_append_int(&buf, actual);
        buffer_append_char(&buf, '\n');
        io_print_err(buf.data);
        status->failures++;
    }
}

void
test_expect_int_le(struct test_status *status, const char *file, int line,
                   const char *expr, int cmp, int actual)
{
    if (cmp < actual)
    {
        struct buffer buf;
        buffer_init(&buf);
        buffer_append_str(&buf, file);
        buffer_append_char(&buf, ':');
        buffer_append_int(&buf, line);
        buffer_append_str(&buf, ":  expected ");
        buffer_append_str(&buf, expr);
        buffer_append_str(&buf, " <= ");
        buffer_append_int(&buf, cmp);
        buffer_append_str(&buf, ", got ");
        buffer_append_int(&buf, actual);
        buffer_append_char(&buf, '\n');
        io_print_err(buf.data);
        status->failures++;
    }
}

void
test_expect_int_lt(struct test_status *status, const char *file, int line,
                   const char *expr, int cmp, int actual)
{
    if (cmp <= actual)
    {
        struct buffer buf;
        buffer_init(&buf);
        buffer_append_str(&buf, file);
        buffer_append_char(&buf, ':');
        buffer_append_int(&buf, line);
        buffer_append_str(&buf, ":  expected ");
        buffer_append_str(&buf, expr);
        buffer_append_str(&buf, " < ");
        buffer_append_int(&buf, cmp);
        buffer_append_str(&buf, ", got ");
        buffer_append_int(&buf, actual);
        buffer_append_char(&buf, '\n');
        io_print_err(buf.data);
        status->failures++;
    }
}

void
test_expect_size_eq(struct test_status *status, const char *file, int line,
                    const char *expr, size_t expected, size_t actual)
{
    if (expected != actual)
    {
        struct buffer buf;
        buffer_init(&buf);
        buffer_append_str(&buf, file);
        buffer_append_char(&buf, ':');
        buffer_append_int(&buf, line);
        buffer_append_str(&buf, ":  expected ");
        buffer_append_str(&buf, expr);
        buffer_append_str(&buf, " == ");
        buffer_append_size(&buf, expected);
        buffer_append_str(&buf, ", got ");
        buffer_append_size(&buf, actual);
        buffer_append_char(&buf, '\n');
        io_print_err(buf.data);
        status->failures++;
    }
}
