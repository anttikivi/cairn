/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CAIRN_TEST_H
#define CAIRN_TEST_H

#include <stdlib.h>

struct cairn_test_status
{
    const char *name;
    size_t failures;
};

void cairn_test_start(struct cairn_test_status *status, const char *name);
int cairn_test_result(struct cairn_test_status *status);
void cairn_test_expect_char_eq(struct cairn_test_status *status,
                               const char *file, int line, const char *expr,
                               char expected, char actual);
void cairn_test_expect_int_eq(struct cairn_test_status *status,
                              const char *file, int line, const char *expr,
                              int expected, int actual);
void cairn_test_expect_int_ge(struct cairn_test_status *status,
                              const char *file, int line, const char *expr,
                              int cmp, int actual);
void cairn_test_expect_int_gt(struct cairn_test_status *status,
                              const char *file, int line, const char *expr,
                              int cmp, int actual);
void cairn_test_expect_int_le(struct cairn_test_status *status,
                              const char *file, int line, const char *expr,
                              int cmp, int actual);
void cairn_test_expect_int_lt(struct cairn_test_status *status,
                              const char *file, int line, const char *expr,
                              int cmp, int actual);
void cairn_test_expect_size_eq(struct cairn_test_status *status,
                               const char *file, int line, const char *expr,
                               size_t expected, size_t actual);

#define CAIRN_EXPECT_CHAR_EQ(test, expected, actual)                           \
    cairn_test_expect_char_eq((test), __FILE__, __LINE__, #actual,             \
                              (char)(expected), (char)(actual))
#define CAIRN_EXPECT_INT_EQ(test, expected, actual)                            \
    cairn_test_expect_int_eq((test), __FILE__, __LINE__, #actual,              \
                             (int)(expected), (int)(actual))
#define CAIRN_EXPECT_INT_GE(test, cmp, actual)                                 \
    cairn_test_expect_int_ge((test), __FILE__, __LINE__, #actual, (int)(cmp),  \
                             (int)(actual))
#define CAIRN_EXPECT_INT_GT(test, cmp, actual)                                 \
    cairn_test_expect_int_gt((test), __FILE__, __LINE__, #actual, (int)(cmp),  \
                             (int)(actual))
#define CAIRN_EXPECT_INT_LE(test, cmp, actual)                                 \
    cairn_test_expect_int_le((test), __FILE__, __LINE__, #actual, (int)(cmp),  \
                             (int)(actual))
#define CAIRN_EXPECT_INT_LT(test, cmp, actual)                                 \
    cairn_test_expect_int_lt((test), __FILE__, __LINE__, #actual, (int)(cmp),  \
                             (int)(actual))

#define CAIRN_EXPECT_SIZE_EQ(test, expected, actual)                           \
    cairn_test_expect_size_eq((test), __FILE__, __LINE__, #actual,             \
                              (size_t)(expected), (size_t)(actual))

#endif
