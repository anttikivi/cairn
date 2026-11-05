/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <stddef.h>

#include <cairn/strings.h>
#include <cairn/test.h>

static int
test_str_nlen(void)
{
    struct cairn_test_status status;
    char buf_1[] = {'a', 'b', 'c'};

    cairn_test_start(&status, "strings/str_nlen");

    CAIRN_EXPECT_SIZE_EQ(&status, 0, cairn_str_nlen(0, 256));
    CAIRN_EXPECT_SIZE_EQ(&status, 0, cairn_str_nlen("", 256));
    CAIRN_EXPECT_SIZE_EQ(&status, 0, cairn_str_nlen("Hello, World!", 0));
    CAIRN_EXPECT_SIZE_EQ(&status, 13, cairn_str_nlen("Hello, World!", 256));
    CAIRN_EXPECT_SIZE_EQ(
        &status, 13, cairn_str_nlen("Hello, World!", sizeof("Hello, World!")));
    CAIRN_EXPECT_SIZE_EQ(&status, 10, cairn_str_nlen("Hello, World!", 10));
    CAIRN_EXPECT_SIZE_EQ(&status, 13,
                         cairn_str_nlen("Hello, World!\0\0\0", 256));
    CAIRN_EXPECT_SIZE_EQ(
        &status, 13,
        cairn_str_nlen("Hello, World!\0\0\0", sizeof("Hello, World!\0\0\0")));
    CAIRN_EXPECT_SIZE_EQ(&status, 3, cairn_str_nlen(buf_1, sizeof(buf_1)));

    return cairn_test_result(&status);
}

static int
test_str_ncmp(void)
{
    struct cairn_test_status status;
    char buf_1[] = {'a', 'b', 'c'};
    char buf_2[] = {'a', 'b', 'c', 'd'};
    char high[] = {(char)0x80, '\0'};
    char low[] = {(char)0x7f, '\0'};

    cairn_test_start(&status, "strings/str_ncmp");

    CAIRN_EXPECT_INT_EQ(&status, 0, cairn_str_ncmp(NULL, 0, NULL, 256));
    CAIRN_EXPECT_INT_EQ(&status, 0, cairn_str_ncmp(NULL, 256, NULL, 256));
    CAIRN_EXPECT_INT_EQ(&status, 0, cairn_str_ncmp("", 0, "", 256));
    CAIRN_EXPECT_INT_EQ(&status, 0, cairn_str_ncmp("", 256, "", 256));
    CAIRN_EXPECT_INT_EQ(&status, 0,
                        cairn_str_ncmp("", sizeof(""), "", sizeof("")));
    CAIRN_EXPECT_INT_LT(&status, 0, cairn_str_ncmp(NULL, 0, "a", sizeof("a")));
    CAIRN_EXPECT_INT_GT(&status, 0, cairn_str_ncmp("a", sizeof("a"), NULL, 0));
    CAIRN_EXPECT_INT_EQ(&status, 0,
                        cairn_str_ncmp("Hello, World!", sizeof("Hello, World!"),
                                       "Hello, World!",
                                       sizeof("Hello, World!")));
    CAIRN_EXPECT_INT_LT(&status, 0,
                        cairn_str_ncmp("Hello,", sizeof("Hello,"),
                                       "Hello, World!",
                                       sizeof("Hello, World!")));
    CAIRN_EXPECT_INT_GT(&status, 0,
                        cairn_str_ncmp("Hello, World!", sizeof("Hello, World!"),
                                       "Hello, ", sizeof("Hello, ")));
    CAIRN_EXPECT_INT_EQ(
        &status, 0, cairn_str_ncmp("Hello, World!", 256, "Hello, World!", 256));
    CAIRN_EXPECT_INT_EQ(
        &status, 0,
        cairn_str_ncmp("Hello, World!\0\0\0", sizeof("Hello, World!\0\0\0"),
                       "Hello, World!", sizeof("Hello, World!")));
    CAIRN_EXPECT_INT_LT(&status, 0,
                        cairn_str_ncmp("Hello, World!", 3, "Hello, World!",
                                       sizeof("Hello, World!")));
    CAIRN_EXPECT_INT_LT(
        &status, 0, cairn_str_ncmp("abc", sizeof("abc"), "bbc", sizeof("bbc")));
    CAIRN_EXPECT_INT_LT(
        &status, 0, cairn_str_ncmp("abc", sizeof("abc"), "adc", sizeof("adc")));
    CAIRN_EXPECT_INT_LT(&status, 0, cairn_str_ncmp("a", 0, "a", 1));
    CAIRN_EXPECT_INT_GT(&status, 0, cairn_str_ncmp("a", 1, "a", 0));
    CAIRN_EXPECT_INT_EQ(
        &status, 0, cairn_str_ncmp(buf_1, sizeof(buf_1), "abc", sizeof("abc")));
    CAIRN_EXPECT_INT_EQ(
        &status, 0,
        cairn_str_ncmp(buf_1, sizeof(buf_1), "abc\0\0", sizeof("abc\0\0")));
    CAIRN_EXPECT_INT_GT(
        &status, 0, cairn_str_ncmp(buf_1, sizeof(buf_1), "ab", sizeof("ab")));
    CAIRN_EXPECT_INT_LT(
        &status, 0, cairn_str_ncmp(buf_1, sizeof(buf_1), buf_2, sizeof(buf_2)));
    CAIRN_EXPECT_INT_EQ(&status, 0,
                        cairn_str_ncmp(buf_1, sizeof(buf_1), buf_2, 3));
    CAIRN_EXPECT_INT_GT(&status, 0,
                        cairn_str_ncmp(high, sizeof(high), low, sizeof(low)));
    CAIRN_EXPECT_INT_LT(&status, 0,
                        cairn_str_ncmp(low, sizeof(low), high, sizeof(high)));

    return cairn_test_result(&status);
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
