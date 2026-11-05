/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include "../../src/base/buffer.h"
#include "../../src/base/strings.h"
#include "../test.h"

int
main(void)
{
    struct test_status status;
    struct buffer buf;
    char full[BUFFER_MAX_BYTES];
    size_t i;

    test_start(&status, "base/buffer");

    buffer_init(&buf);

    EXPECT_SIZE_EQ(&status, 0U, buf.len);
    EXPECT_CHAR_EQ(&status, '\0', buf.data[0]);

    buffer_append_str(&buf, "Hello");

    EXPECT_SIZE_EQ(&status, 5U, buf.len);
    EXPECT_INT_EQ(
        &status, 0,
        str_ncmp("Hello", sizeof("Hello"), buf.data, sizeof(buf.data)));
    EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    buffer_append_char(&buf, ',');

    EXPECT_SIZE_EQ(&status, 6U, buf.len);
    EXPECT_INT_EQ(
        &status, 0,
        str_ncmp("Hello,", sizeof("Hello,"), buf.data, sizeof(buf.data)));
    EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    buffer_append_size(&buf, (size_t)3U);

    EXPECT_SIZE_EQ(&status, 7U, buf.len);
    EXPECT_INT_EQ(
        &status, 0,
        str_ncmp("Hello,3", sizeof("Hello,3"), buf.data, sizeof(buf.data)));
    EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    buffer_append_int(&buf, (int)5);

    EXPECT_SIZE_EQ(&status, 8U, buf.len);
    EXPECT_INT_EQ(
        &status, 0,
        str_ncmp("Hello,35", sizeof("Hello,35"), buf.data, sizeof(buf.data)));
    EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    buffer_init(&buf);

    EXPECT_SIZE_EQ(&status, 0U, buf.len);
    EXPECT_CHAR_EQ(&status, '\0', buf.data[0]);

    for (i = 0U; i < BUFFER_MAX_BYTES - 1U; i++)
    {
        full[i] = 'x';
    }
    full[BUFFER_MAX_BYTES - 1U] = '\0';

    buffer_append_str(&buf, full);

    EXPECT_SIZE_EQ(&status, BUFFER_MAX_BYTES - 1U, buf.len);
    EXPECT_INT_EQ(&status, 0,
                  str_ncmp(full, sizeof(full), buf.data, sizeof(buf.data)));
    EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    buffer_append_str(&buf, "ignored");

    EXPECT_SIZE_EQ(&status, BUFFER_MAX_BYTES - 1U, buf.len);
    EXPECT_INT_EQ(&status, 0,
                  str_ncmp(full, sizeof(full), buf.data, sizeof(buf.data)));
    EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    return test_result(&status);
}
