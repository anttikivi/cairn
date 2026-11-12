/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <stddef.h>

#include <crdef.h>
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
    const char high[] = "\x80";
    const char low[] = "\x7f";

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

static int
test_crsnterm(void)
{
    struct cr_test status;
    char unterminated[] = {'a', 'b', 'c'};
    char last[] = {'a', 'b', '\0'};

    crtinit(&status, "str/crsterm");

    CR_EXPECT_INT_EQ(&status, CR_FALSE, crsterm(NULL, 0));
    CR_EXPECT_INT_EQ(&status, CR_FALSE, crsterm(NULL, 256));
    CR_EXPECT_INT_EQ(&status, CR_FALSE, crsterm("", 0));
    CR_EXPECT_INT_EQ(&status, CR_FALSE, crsterm("abc", 0));
    CR_EXPECT_INT_EQ(&status, CR_TRUE, crsterm("", 1));
    CR_EXPECT_INT_EQ(&status, CR_TRUE, crsterm("", sizeof("")));
    CR_EXPECT_INT_EQ(&status, CR_FALSE, crsterm("abc", 3));
    CR_EXPECT_INT_EQ(&status, CR_TRUE, crsterm("abc", 4));
    CR_EXPECT_INT_EQ(&status, CR_TRUE, crsterm("abc", sizeof("abc")));
    CR_EXPECT_INT_EQ(&status, CR_TRUE, crsterm("abc", 256));
    CR_EXPECT_INT_EQ(&status, CR_TRUE, crsterm("ab\0cd", 3));
    CR_EXPECT_INT_EQ(&status, CR_FALSE, crsterm("ab\0cd", 2));
    CR_EXPECT_INT_EQ(&status, CR_FALSE,
                     crsterm(unterminated, sizeof(unterminated)));
    CR_EXPECT_INT_EQ(&status, CR_TRUE, crsterm(last, sizeof(last)));
    CR_EXPECT_INT_EQ(&status, CR_FALSE, crsterm(last, sizeof(last) - 1U));

    return crtresult(&status);
}

static int
test_crsnchr(void)
{
    struct cr_test status;
    const char hello[] = "Hello, World!";
    const char embedded[] = "ab\0cd";
    const char high[] = "a\x80"
                        "b";
    char unterminated[] = {'a', 'b', 'c'};

    crtinit(&status, "str/crsnchr");

    CR_EXPECT_INT_EQ(&status, 1, crsnchr(NULL, 'a', 0) == NULL);
    CR_EXPECT_INT_EQ(&status, 1, crsnchr(NULL, 'a', 256) == NULL);
    CR_EXPECT_INT_EQ(&status, 1, crsnchr(hello, 'H', 0) == NULL);
    CR_EXPECT_INT_EQ(&status, 1, crsnchr("", 'a', sizeof("")) == NULL);
    CR_EXPECT_INT_EQ(&status, 1, crsnchr(hello, 'H', sizeof(hello)) == hello);
    CR_EXPECT_INT_EQ(&status, 1,
                     crsnchr(hello, ',', sizeof(hello)) == (hello + 5));
    CR_EXPECT_INT_EQ(&status, 1,
                     crsnchr(hello, '!', sizeof(hello)) == (hello + 12));
    CR_EXPECT_INT_EQ(&status, 1,
                     crsnchr(hello, 'l', sizeof(hello)) == (hello + 2));
    CR_EXPECT_INT_EQ(&status, 1,
                     crsnchr(hello, 'o', sizeof(hello)) == (hello + 4));
    CR_EXPECT_INT_EQ(&status, 1, crsnchr(hello, 'z', sizeof(hello)) == NULL);
    CR_EXPECT_INT_EQ(&status, 1, crsnchr(hello, 'h', sizeof(hello)) == NULL);
    CR_EXPECT_INT_EQ(&status, 1, crsnchr(hello, '!', 12) == NULL);
    CR_EXPECT_INT_EQ(&status, 1, crsnchr(hello, '!', 13) == (hello + 12));
    CR_EXPECT_INT_EQ(&status, 1,
                     crsnchr(embedded, 'c', sizeof(embedded)) == NULL);
    CR_EXPECT_INT_EQ(
        &status, 1, crsnchr(embedded, 'b', sizeof(embedded)) == (embedded + 1));
    CR_EXPECT_INT_EQ(&status, 1, crsnchr(hello, '\0', sizeof(hello)) == NULL);
    CR_EXPECT_INT_EQ(&status, 1, crsnchr("", '\0', sizeof("")) == NULL);
    CR_EXPECT_INT_EQ(&status, 1,
                     crsnchr(unterminated, 'c', sizeof(unterminated)) ==
                         (unterminated + 2));
    CR_EXPECT_INT_EQ(&status, 1,
                     crsnchr(unterminated, 'd', sizeof(unterminated)) == NULL);
    CR_EXPECT_INT_EQ(&status, 1,
                     crsnchr(high, '\x80', sizeof(high)) == (high + 1));

    return crtresult(&status);
}

int
main(void) /* cppcheck-suppress misra-c2012-8.6 */
{
    int result = test_crsnlen();

    if (result == CR_EXIT_SUCCESS)
    {
        result = test_crsncmp();
    }

    if (result == CR_EXIT_SUCCESS)
    {
        result = test_crsnterm();
    }

    if (result == CR_EXIT_SUCCESS)
    {
        result = test_crsnchr();
    }

    return result;
}
