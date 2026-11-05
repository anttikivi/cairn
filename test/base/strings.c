/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stddef.h>

#include "../../src/base/strings.h"
#include "../test.h"

static int
test_str_nlen(void)
{
    struct test_status status;
    char buf_1[] = {'a', 'b', 'c'};

    test_start(&status, "base/strings/str_nlen");

    EXPECT_SIZE_EQ(&status, 0, str_nlen(0, 256));
    EXPECT_SIZE_EQ(&status, 0, str_nlen("", 256));
    EXPECT_SIZE_EQ(&status, 0, str_nlen("Hello, World!", 0));
    EXPECT_SIZE_EQ(&status, 13, str_nlen("Hello, World!", 256));
    EXPECT_SIZE_EQ(&status, 13,
                   str_nlen("Hello, World!", sizeof("Hello, World!")));
    EXPECT_SIZE_EQ(&status, 10, str_nlen("Hello, World!", 10));
    EXPECT_SIZE_EQ(&status, 13, str_nlen("Hello, World!\0\0\0", 256));
    EXPECT_SIZE_EQ(
        &status, 13,
        str_nlen("Hello, World!\0\0\0", sizeof("Hello, World!\0\0\0")));
    EXPECT_SIZE_EQ(&status, 3, str_nlen(buf_1, sizeof(buf_1)));

    return test_result(&status);
}

static int
test_str_ncmp(void)
{
    struct test_status status;
    char buf_1[] = {'a', 'b', 'c'};
    char buf_2[] = {'a', 'b', 'c', 'd'};
    char high[] = {(char)0x80, '\0'};
    char low[] = {(char)0x7f, '\0'};

    test_start(&status, "base/strings/str_ncmp");

    EXPECT_INT_EQ(&status, 0, str_ncmp(NULL, 0, NULL, 256));
    EXPECT_INT_EQ(&status, 0, str_ncmp(NULL, 256, NULL, 256));
    EXPECT_INT_EQ(&status, 0, str_ncmp("", 0, "", 256));
    EXPECT_INT_EQ(&status, 0, str_ncmp("", 256, "", 256));
    EXPECT_INT_EQ(&status, 0, str_ncmp("", sizeof(""), "", sizeof("")));
    EXPECT_INT_LT(&status, 0, str_ncmp(NULL, 0, "a", sizeof("a")));
    EXPECT_INT_GT(&status, 0, str_ncmp("a", sizeof("a"), NULL, 0));
    EXPECT_INT_EQ(&status, 0,
                  str_ncmp("Hello, World!", sizeof("Hello, World!"),
                           "Hello, World!", sizeof("Hello, World!")));
    EXPECT_INT_LT(&status, 0,
                  str_ncmp("Hello,", sizeof("Hello,"), "Hello, World!",
                           sizeof("Hello, World!")));
    EXPECT_INT_GT(&status, 0,
                  str_ncmp("Hello, World!", sizeof("Hello, World!"), "Hello, ",
                           sizeof("Hello, ")));
    EXPECT_INT_EQ(&status, 0,
                  str_ncmp("Hello, World!", 256, "Hello, World!", 256));
    EXPECT_INT_EQ(&status, 0,
                  str_ncmp("Hello, World!\0\0\0", sizeof("Hello, World!\0\0\0"),
                           "Hello, World!", sizeof("Hello, World!")));
    EXPECT_INT_LT(
        &status, 0,
        str_ncmp("Hello, World!", 3, "Hello, World!", sizeof("Hello, World!")));
    EXPECT_INT_LT(&status, 0,
                  str_ncmp("abc", sizeof("abc"), "bbc", sizeof("bbc")));
    EXPECT_INT_LT(&status, 0,
                  str_ncmp("abc", sizeof("abc"), "adc", sizeof("adc")));
    EXPECT_INT_LT(&status, 0, str_ncmp("a", 0, "a", 1));
    EXPECT_INT_GT(&status, 0, str_ncmp("a", 1, "a", 0));
    EXPECT_INT_EQ(&status, 0,
                  str_ncmp(buf_1, sizeof(buf_1), "abc", sizeof("abc")));
    EXPECT_INT_EQ(&status, 0,
                  str_ncmp(buf_1, sizeof(buf_1), "abc\0\0", sizeof("abc\0\0")));
    EXPECT_INT_GT(&status, 0,
                  str_ncmp(buf_1, sizeof(buf_1), "ab", sizeof("ab")));
    EXPECT_INT_LT(&status, 0,
                  str_ncmp(buf_1, sizeof(buf_1), buf_2, sizeof(buf_2)));
    EXPECT_INT_EQ(&status, 0, str_ncmp(buf_1, sizeof(buf_1), buf_2, 3));
    EXPECT_INT_GT(&status, 0, str_ncmp(high, sizeof(high), low, sizeof(low)));
    EXPECT_INT_LT(&status, 0, str_ncmp(low, sizeof(low), high, sizeof(high)));

    return test_result(&status);
}

int
main(void)
{
    int result = test_str_nlen();

    if (result == EXIT_SUCCESS)
    {
        result = test_str_ncmp();
    }

    return result;
}
