/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <cairn/buffer.h>
#include <cairn/strings.h>
#include <cairn/test.h>

int
main(void)
{
    struct cairn_test_status status;
    struct cairn_buffer buf;
    char full[CAIRN_BUFFER_MAX_BYTES];
    size_t i;

    cairn_test_start(&status, "buffer");

    cairn_buffer_init(&buf);

    CAIRN_EXPECT_SIZE_EQ(&status, 0U, buf.len);
    CAIRN_EXPECT_CHAR_EQ(&status, '\0', buf.data[0]);

    cairn_buffer_append_str(&buf, "Hello");

    CAIRN_EXPECT_SIZE_EQ(&status, 5U, buf.len);
    CAIRN_EXPECT_INT_EQ(
        &status, 0,
        cairn_str_ncmp("Hello", sizeof("Hello"), buf.data, sizeof(buf.data)));
    CAIRN_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    cairn_buffer_append_char(&buf, ',');

    CAIRN_EXPECT_SIZE_EQ(&status, 6U, buf.len);
    CAIRN_EXPECT_INT_EQ(
        &status, 0,
        cairn_str_ncmp("Hello,", sizeof("Hello,"), buf.data, sizeof(buf.data)));
    CAIRN_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    cairn_buffer_append_size(&buf, (size_t)3U);

    CAIRN_EXPECT_SIZE_EQ(&status, 7U, buf.len);
    CAIRN_EXPECT_INT_EQ(&status, 0,
                        cairn_str_ncmp("Hello,3", sizeof("Hello,3"), buf.data,
                                       sizeof(buf.data)));
    CAIRN_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    cairn_buffer_append_int(&buf, (int)5);

    CAIRN_EXPECT_SIZE_EQ(&status, 8U, buf.len);
    CAIRN_EXPECT_INT_EQ(&status, 0,
                        cairn_str_ncmp("Hello,35", sizeof("Hello,35"), buf.data,
                                       sizeof(buf.data)));
    CAIRN_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    cairn_buffer_init(&buf);

    CAIRN_EXPECT_SIZE_EQ(&status, 0U, buf.len);
    CAIRN_EXPECT_CHAR_EQ(&status, '\0', buf.data[0]);

    for (i = 0U; i < CAIRN_BUFFER_MAX_BYTES - 1U; i++)
    {
        full[i] = 'x';
    }
    full[CAIRN_BUFFER_MAX_BYTES - 1U] = '\0';

    cairn_buffer_append_str(&buf, full);

    CAIRN_EXPECT_SIZE_EQ(&status, CAIRN_BUFFER_MAX_BYTES - 1U, buf.len);
    CAIRN_EXPECT_INT_EQ(
        &status, 0,
        cairn_str_ncmp(full, sizeof(full), buf.data, sizeof(buf.data)));
    CAIRN_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    cairn_buffer_append_str(&buf, "ignored");

    CAIRN_EXPECT_SIZE_EQ(&status, CAIRN_BUFFER_MAX_BYTES - 1U, buf.len);
    CAIRN_EXPECT_INT_EQ(
        &status, 0,
        cairn_str_ncmp(full, sizeof(full), buf.data, sizeof(buf.data)));
    CAIRN_EXPECT_CHAR_EQ(&status, '\0', buf.data[buf.len]);

    return cairn_test_result(&status);
}
