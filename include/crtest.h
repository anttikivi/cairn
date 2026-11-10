/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRTEST_H
#define CRTEST_H

#include <stdlib.h>

struct cr_test
{
    const char *name;
    size_t failures;
};

/* Initialize the test object and print the test name. */
void crtinit(struct cr_test *status, const char *name);
/*
 * Return the applicable program return code for the given test run and print
 * the final failure status.
 */
int crtresult(const struct cr_test *status);

/* Test if a char is equal to the expected value. */
void crtceq(struct cr_test *status, const char *file, int line,
            const char *expr, char expected, char actual);
/* Test if an int is equal to the expected value. */
void crtieq(struct cr_test *status, const char *file, int line,
            const char *expr, int expected, int actual);
/* Test if an int is greater than or equal to the expected value. */
void crtige(struct cr_test *status, const char *file, int line,
            const char *expr, int cmp, int actual);
/* Test if an int is greater than the expected value. */
void crtigt(struct cr_test *status, const char *file, int line,
            const char *expr, int cmp, int actual);
/* Test if an int is less than or equal to the expected value. */
void crtile(struct cr_test *status, const char *file, int line,
            const char *expr, int cmp, int actual);
/* Test if an int is less than the expected value. */
void crtilt(struct cr_test *status, const char *file, int line,
            const char *expr, int cmp, int actual);
/* Test if a size_t is equal to the expected value. */
void crtseq(struct cr_test *status, const char *file, int line,
            const char *expr, size_t expected, size_t actual);

/* These macro definitions are part of the public API. */
/* cppcheck-suppress-begin misra-c2012-2.5 */

/* Deviation-002 */
/* cppcheck-suppress-begin misra-c2012-20.10 */
#define CR_EXPECT_CHAR_EQ(test, expected, actual)                              \
    crtceq((test), __FILE__, __LINE__, #actual, (char)(expected),              \
           (char)(actual))
#define CR_EXPECT_INT_EQ(test, expected, actual)                               \
    crtieq((test), __FILE__, __LINE__, #actual, (int)(expected), (int)(actual))
#define CR_EXPECT_INT_GE(test, cmp, actual)                                    \
    crtige((test), __FILE__, __LINE__, #actual, (int)(cmp), (int)(actual))
#define CR_EXPECT_INT_GT(test, cmp, actual)                                    \
    crtigt((test), __FILE__, __LINE__, #actual, (int)(cmp), (int)(actual))
#define CR_EXPECT_INT_LE(test, cmp, actual)                                    \
    crtile((test), __FILE__, __LINE__, #actual, (int)(cmp), (int)(actual))
#define CR_EXPECT_INT_LT(test, cmp, actual)                                    \
    crtilt((test), __FILE__, __LINE__, #actual, (int)(cmp), (int)(actual))

#define CR_EXPECT_SIZE_EQ(test, expected, actual)                              \
    crtseq((test), __FILE__, __LINE__, #actual, (expected), (actual))
/* cppcheck-suppress-end misra-c2012-20.10 */
/* cppcheck-suppress-end misra-c2012-2.5 */

#endif
