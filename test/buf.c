/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <limits.h>

#include <crbuf.h>
#include <crstr.h>
#include <crtest.h>

int
main(void)
{
    struct cr_test status;
    struct cr_buf buf;
    char filled[CR_BUF_MAX_BYTES];
    size_t i;
    size_t full_expected_len = (size_t)CR_BUF_MAX_BYTES;
    full_expected_len--;

    crtinit(&status, "buf");

    crbinit(&buf);

    CR_EXPECT_SIZE_EQ(&status, 0U, buf.len);
    CR_EXPECT_CHAR_EQ(&status, '\0', buf.data[0]);

    crbastr(&buf, "Hello");

    CR_EXPECT_SIZE_EQ(&status, 5U, buf.len);
    CR_EXPECT_INT_EQ(
        &status, 0,
        crsncmp("Hello", sizeof("Hello"), buf.data, sizeof(buf.data)));

    CR_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    crbachar(&buf, ',');

    CR_EXPECT_SIZE_EQ(&status, 6U, buf.len);
    CR_EXPECT_INT_EQ(
        &status, 0,
        crsncmp("Hello,", sizeof("Hello,"), buf.data, sizeof(buf.data)));
    CR_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    crbasize(&buf, (size_t)3U);

    CR_EXPECT_SIZE_EQ(&status, 7U, buf.len);
    CR_EXPECT_INT_EQ(
        &status, 0,
        crsncmp("Hello,3", sizeof("Hello,3"), buf.data, sizeof(buf.data)));
    CR_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    crbaint(&buf, (int)5);

    CR_EXPECT_SIZE_EQ(&status, 8U, buf.len);
    CR_EXPECT_INT_EQ(
        &status, 0,
        crsncmp("Hello,35", sizeof("Hello,35"), buf.data, sizeof(buf.data)));
    CR_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    crbinit(&buf);

    CR_EXPECT_SIZE_EQ(&status, 0U, buf.len);
    CR_EXPECT_CHAR_EQ(&status, '\0', buf.data[0]);

    for (i = 0U; i < CR_BUF_MAX_BYTES - 1U; i++)
    {
        filled[i] = 'x';
    }
    filled[CR_BUF_MAX_BYTES - 1U] = '\0';

    crbastr(&buf, filled);

    CR_EXPECT_SIZE_EQ(&status, full_expected_len, buf.len);
    CR_EXPECT_INT_EQ(
        &status, 0,
        crsncmp(filled, sizeof(filled), buf.data, sizeof(buf.data)));
    CR_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    crbastr(&buf, "ignored");

    CR_EXPECT_SIZE_EQ(&status, full_expected_len, buf.len);
    CR_EXPECT_INT_EQ(
        &status, 0,
        crsncmp(filled, sizeof(filled), buf.data, sizeof(buf.data)));
    CR_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    crbinit(&buf);
    crbaint(&buf, -42);

    CR_EXPECT_SIZE_EQ(&status, 3U, buf.len);
    CR_EXPECT_INT_EQ(&status, 0,
                     crsncmp("-42", sizeof("-42"), buf.data, sizeof(buf.data)));

#if INT_MIN == (-2147483647 - 1)
    crbinit(&buf);
    crbaint(&buf, INT_MIN);

    CR_EXPECT_INT_EQ(&status, 0,
                     crsncmp("-2147483648", sizeof("-2147483648"), buf.data,
                             sizeof(buf.data)));
#endif

    return crtresult(&status);
}
