/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <crtest.h>

#include <crbuf.h>
#include <crio.h>

/*
 * TODO: See if failing to print the test output should affect the test results.
 */

void
crtinit(struct cr_test *status, const char *name)
{
    status->name = name;
    status->failures = 0U;
    (void)crioerr("\n");
    (void)crioerr(name);
    (void)crioerr("\n");
}

int
crtresult(const struct cr_test *status)
{
    int result = EXIT_SUCCESS;
    if (status->failures > 0U)
    {
        (void)crioerr("failures in ");
        (void)crioerr(status->name);
        (void)crioerr("\n");
        result = EXIT_FAILURE;
    }
    else
    {
        (void)crioerr("all tests in ");
        (void)crioerr(status->name);
        (void)crioerr(" passed\n");
    }
    return result;
}

/* These functions are part of the public API. */
/* cppcheck-suppress-begin [misra-c2012-8.7, unusedFunction] */

void
crtceq(struct cr_test *status, const char *file, int line, const char *expr,
       char expected, char actual)
{
    if (expected != actual)
    {
        struct cr_buf buf;
        crbinit(&buf);
        crbastr(&buf, file);
        crbachar(&buf, ':');
        crbaint(&buf, line);
        crbastr(&buf, ":  expected ");
        crbastr(&buf, expr);
        crbastr(&buf, " == ");
        if (expected == '\0')
        {
            crbastr(&buf, "\\0");
        }
        else
        {
            crbachar(&buf, expected);
        }
        crbastr(&buf, ", got ");
        if (actual == '\0')
        {
            crbastr(&buf, "\\0");
        }
        else
        {
            crbachar(&buf, actual);
        }
        crbachar(&buf, '\n');
        (void)crioerr(buf.data);
        status->failures++;
    }
}

void
crtieq(struct cr_test *status, const char *file, int line, const char *expr,
       int expected, int actual)
{
    if (expected != actual)
    {
        struct cr_buf buf;
        crbinit(&buf);
        crbastr(&buf, file);
        crbachar(&buf, ':');
        crbaint(&buf, line);
        crbastr(&buf, ":  expected ");
        crbastr(&buf, expr);
        crbastr(&buf, " == ");
        crbaint(&buf, expected);
        crbastr(&buf, ", got ");
        crbaint(&buf, actual);
        crbachar(&buf, '\n');
        (void)crioerr(buf.data);
        status->failures++;
    }
}

void
crtige(struct cr_test *status, const char *file, int line, const char *expr,
       int cmp, int actual)
{
    if (cmp > actual)
    {
        struct cr_buf buf;
        crbinit(&buf);
        crbastr(&buf, file);
        crbachar(&buf, ':');
        crbaint(&buf, line);
        crbastr(&buf, ":  expected ");
        crbastr(&buf, expr);
        crbastr(&buf, " >= ");
        crbaint(&buf, cmp);
        crbastr(&buf, ", got ");
        crbaint(&buf, actual);
        crbachar(&buf, '\n');
        (void)crioerr(buf.data);
        status->failures++;
    }
}

void
crtigt(struct cr_test *status, const char *file, int line, const char *expr,
       int cmp, int actual)
{
    if (cmp >= actual)
    {
        struct cr_buf buf;
        crbinit(&buf);
        crbastr(&buf, file);
        crbachar(&buf, ':');
        crbaint(&buf, line);
        crbastr(&buf, ":  expected ");
        crbastr(&buf, expr);
        crbastr(&buf, " > ");
        crbaint(&buf, cmp);
        crbastr(&buf, ", got ");
        crbaint(&buf, actual);
        crbachar(&buf, '\n');
        (void)crioerr(buf.data);
        status->failures++;
    }
}

void
crtile(struct cr_test *status, const char *file, int line, const char *expr,
       int cmp, int actual)
{
    if (cmp < actual)
    {
        struct cr_buf buf;
        crbinit(&buf);
        crbastr(&buf, file);
        crbachar(&buf, ':');
        crbaint(&buf, line);
        crbastr(&buf, ":  expected ");
        crbastr(&buf, expr);
        crbastr(&buf, " <= ");
        crbaint(&buf, cmp);
        crbastr(&buf, ", got ");
        crbaint(&buf, actual);
        crbachar(&buf, '\n');
        (void)crioerr(buf.data);
        status->failures++;
    }
}

void
crtilt(struct cr_test *status, const char *file, int line, const char *expr,
       int cmp, int actual)
{
    if (cmp <= actual)
    {
        struct cr_buf buf;
        crbinit(&buf);
        crbastr(&buf, file);
        crbachar(&buf, ':');
        crbaint(&buf, line);
        crbastr(&buf, ":  expected ");
        crbastr(&buf, expr);
        crbastr(&buf, " < ");
        crbaint(&buf, cmp);
        crbastr(&buf, ", got ");
        crbaint(&buf, actual);
        crbachar(&buf, '\n');
        (void)crioerr(buf.data);
        status->failures++;
    }
}

void
crtseq(struct cr_test *status, const char *file, int line, const char *expr,
       size_t expected, size_t actual)
{
    if (expected != actual)
    {
        struct cr_buf buf;
        crbinit(&buf);
        crbastr(&buf, file);
        crbachar(&buf, ':');
        crbaint(&buf, line);
        crbastr(&buf, ":  expected ");
        crbastr(&buf, expr);
        crbastr(&buf, " == ");
        crbasize(&buf, expected);
        crbastr(&buf, ", got ");
        crbasize(&buf, actual);
        crbachar(&buf, '\n');
        (void)crioerr(buf.data);
        status->failures++;
    }
}

/* cppcheck-suppress-end [misra-c2012-8.7, unusedFunction] */
