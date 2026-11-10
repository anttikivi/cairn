/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <stddef.h>

#include <crstr.h>
#include <crtest.h>

static int
test_crsnlen(void)
{
    struct cr_test status;
    char buf_1[] = {'a', 'b', 'c'};

    crtinit(&status, "str/crsnlen");

    CR_EXPECT_SIZE_EQ(&status, 0, crsnlen(0, 256));
    CR_EXPECT_SIZE_EQ(&status, 0, crsnlen("", 256));
    CR_EXPECT_SIZE_EQ(&status, 0, crsnlen("Hello, World!", 0));
    CR_EXPECT_SIZE_EQ(&status, 13, crsnlen("Hello, World!", 256));
    CR_EXPECT_SIZE_EQ(&status, 13,
                      crsnlen("Hello, World!", sizeof("Hello, World!")));
    CR_EXPECT_SIZE_EQ(&status, 10, crsnlen("Hello, World!", 10));
    CR_EXPECT_SIZE_EQ(&status, 13, crsnlen("Hello, World!\0\0\0", 256));
    CR_EXPECT_SIZE_EQ(
        &status, 13,
        crsnlen("Hello, World!\0\0\0", sizeof("Hello, World!\0\0\0")));
    CR_EXPECT_SIZE_EQ(&status, 3, crsnlen(buf_1, sizeof(buf_1)));

    return crtresult(&status);
}

static int
test_crsncmp(void)
{
    struct cr_test status;
    char buf_1[] = {'a', 'b', 'c'};
    char buf_2[] = {'a', 'b', 'c', 'd'};
    char high[] = "\x80";
    char low[] = "\x7f";

    crtinit(&status, "str/crsncmp");

    CR_EXPECT_INT_EQ(&status, 0, crsncmp(NULL, 0, NULL, 256));
    CR_EXPECT_INT_EQ(&status, 0, crsncmp(NULL, 256, NULL, 256));
    CR_EXPECT_INT_EQ(&status, 0, crsncmp("", 0, "", 256));
    CR_EXPECT_INT_EQ(&status, 0, crsncmp("", 256, "", 256));
    CR_EXPECT_INT_EQ(&status, 0, crsncmp("", sizeof(""), "", sizeof("")));
    CR_EXPECT_INT_LT(&status, 0, crsncmp(NULL, 0, "a", sizeof("a")));
    CR_EXPECT_INT_GT(&status, 0, crsncmp("a", sizeof("a"), NULL, 0));
    CR_EXPECT_INT_EQ(&status, 0,
                     crsncmp("Hello, World!", sizeof("Hello, World!"),
                             "Hello, World!", sizeof("Hello, World!")));
    CR_EXPECT_INT_LT(&status, 0,
                     crsncmp("Hello,", sizeof("Hello,"), "Hello, World!",
                             sizeof("Hello, World!")));
    CR_EXPECT_INT_GT(&status, 0,
                     crsncmp("Hello, World!", sizeof("Hello, World!"),
                             "Hello, ", sizeof("Hello, ")));
    CR_EXPECT_INT_EQ(&status, 0,
                     crsncmp("Hello, World!", 256, "Hello, World!", 256));
    CR_EXPECT_INT_EQ(&status, 0,
                     crsncmp("Hello, World!\0\0\0",
                             sizeof("Hello, World!\0\0\0"), "Hello, World!",
                             sizeof("Hello, World!")));
    CR_EXPECT_INT_LT(
        &status, 0,
        crsncmp("Hello, World!", 3, "Hello, World!", sizeof("Hello, World!")));
    CR_EXPECT_INT_LT(&status, 0,
                     crsncmp("abc", sizeof("abc"), "bbc", sizeof("bbc")));
    CR_EXPECT_INT_LT(&status, 0,
                     crsncmp("abc", sizeof("abc"), "adc", sizeof("adc")));
    CR_EXPECT_INT_LT(&status, 0, crsncmp("a", 0, "a", 1));
    CR_EXPECT_INT_GT(&status, 0, crsncmp("a", 1, "a", 0));
    CR_EXPECT_INT_EQ(&status, 0,
                     crsncmp(buf_1, sizeof(buf_1), "abc", sizeof("abc")));
    CR_EXPECT_INT_EQ(
        &status, 0,
        crsncmp(buf_1, sizeof(buf_1), "abc\0\0", sizeof("abc\0\0")));
    CR_EXPECT_INT_GT(&status, 0,
                     crsncmp(buf_1, sizeof(buf_1), "ab", sizeof("ab")));
    CR_EXPECT_INT_LT(&status, 0,
                     crsncmp(buf_1, sizeof(buf_1), buf_2, sizeof(buf_2)));
    CR_EXPECT_INT_EQ(&status, 0, crsncmp(buf_1, sizeof(buf_1), buf_2, 3));
    CR_EXPECT_INT_GT(&status, 0, crsncmp(high, sizeof(high), low, sizeof(low)));
    CR_EXPECT_INT_LT(&status, 0, crsncmp(low, sizeof(low), high, sizeof(high)));

    return crtresult(&status);
}

int
main(void)
{
    int result = test_crsnlen();

    if (result == EXIT_SUCCESS)
    {
        result = test_crsncmp();
    }

    return result;
}
