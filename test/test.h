/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <stdlib.h>

struct test_status
{
    const char *name;
    size_t failures;
};

void test_start(struct test_status *status, const char *name);
int test_result(struct test_status *status);
void test_expect_char_eq(struct test_status *status, const char *file, int line,
                         const char *expr, char expected, char actual);
void test_expect_int_eq(struct test_status *status, const char *file, int line,
                        const char *expr, int expected, int actual);
void test_expect_int_ge(struct test_status *status, const char *file, int line,
                        const char *expr, int cmp, int actual);
void test_expect_int_gt(struct test_status *status, const char *file, int line,
                        const char *expr, int cmp, int actual);
void test_expect_int_le(struct test_status *status, const char *file, int line,
                        const char *expr, int cmp, int actual);
void test_expect_int_lt(struct test_status *status, const char *file, int line,
                        const char *expr, int cmp, int actual);
void test_expect_size_eq(struct test_status *status, const char *file, int line,
                         const char *expr, size_t expected, size_t actual);

#define EXPECT_CHAR_EQ(test, expected, actual)                                 \
    test_expect_char_eq((test), __FILE__, __LINE__, #actual, (char)(expected), \
                        (char)(actual))
#define EXPECT_INT_EQ(test, expected, actual)                                  \
    test_expect_int_eq((test), __FILE__, __LINE__, #actual, (int)(expected),   \
                       (int)(actual))
#define EXPECT_INT_GE(test, cmp, actual)                                       \
    test_expect_int_ge((test), __FILE__, __LINE__, #actual, (int)(cmp),        \
                       (int)(actual))
#define EXPECT_INT_GT(test, cmp, actual)                                       \
    test_expect_int_gt((test), __FILE__, __LINE__, #actual, (int)(cmp),        \
                       (int)(actual))
#define EXPECT_INT_LE(test, cmp, actual)                                       \
    test_expect_int_le((test), __FILE__, __LINE__, #actual, (int)(cmp),        \
                       (int)(actual))
#define EXPECT_INT_LT(test, cmp, actual)                                       \
    test_expect_int_lt((test), __FILE__, __LINE__, #actual, (int)(cmp),        \
                       (int)(actual))

#define EXPECT_SIZE_EQ(test, expected, actual)                                 \
    test_expect_size_eq((test), __FILE__, __LINE__, #actual,                   \
                        (size_t)(expected), (size_t)(actual))

#endif
