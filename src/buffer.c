/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <cairn/buffer.h>

#include <stddef.h>

#include <cairn/bool.h>
#include <cairn/debug.h>
#include <cairn/strings.h>

#ifndef CAIRN_BUFFER_ALLOW_APPEND_INT
#    define CAIRN_BUFFER_ALLOW_APPEND_INT (0)
#endif

void
cairn_buffer_init(struct cairn_buffer *b)
{
    CAIRN_ASSERT(b != NULL);
    b->len = 0;
    b->data[0] = '\0';
}

void
cairn_buffer_append_char(struct cairn_buffer *b, char c)
{
    CAIRN_ASSERT(b != NULL);

    if (b->len < (CAIRN_BUFFER_MAX_BYTES - 1U))
    {
        b->data[b->len] = c;
        b->data[b->len + 1] = '\0';
        b->len++;
    }

    CAIRN_ASSERT(b->len <= CAIRN_BUFFER_MAX_BYTES);
    CAIRN_ASSERT(cairn_str_nlen(b->data, CAIRN_BUFFER_MAX_BYTES) <= b->len);
}

void
cairn_buffer_append_str(struct cairn_buffer *b, const char *s)
{
    size_t i = 0;

    CAIRN_ASSERT(b != NULL);
    CAIRN_ASSERT(s != NULL);

    while ((s[i] != '\0') && (b->len < (CAIRN_BUFFER_MAX_BYTES - 1U)))
    {
        b->data[b->len] = s[i];
        b->len++;
        i++;
    }

    b->data[b->len] = '\0';

    CAIRN_ASSERT(b->len <= CAIRN_BUFFER_MAX_BYTES);
    CAIRN_ASSERT(cairn_str_nlen(b->data, CAIRN_BUFFER_MAX_BYTES) <= b->len);
}

void
cairn_buffer_append_size(struct cairn_buffer *b, size_t d)
{
    char tmp[32]; /* overkill */
    size_t i = 0U;
    size_t u = d;

    CAIRN_ASSERT(b != NULL);

    do
    {
        tmp[i] = (char)('0' + (u % 10U));
        i++;
        u /= 10U;
    } while (u > 0U);

    while ((i > 0U) && (b->len < (CAIRN_BUFFER_MAX_BYTES - 1U)))
    {
        i--;
        b->data[b->len] = tmp[i];
        b->len++;
    }

    b->data[b->len] = '\0';

    CAIRN_ASSERT(b->len < CAIRN_BUFFER_MAX_BYTES);
    CAIRN_ASSERT(cairn_str_nlen(b->data, CAIRN_BUFFER_MAX_BYTES) <= b->len);
}

void
cairn_buffer_append_int(struct cairn_buffer *b, int d)
{
    char tmp[32]; /* overkill */
    size_t i = 0U;
    unsigned int u;

#if !CAIRN_BUFFER_ALLOW_APPEND_INT
    CAIRN_ASSERT(CAIRN_FALSE);
#endif

    CAIRN_ASSERT(b != NULL);

    if (d < 0)
    {
        if (b->len < (CAIRN_BUFFER_MAX_BYTES - 1U))
        {
            b->data[b->len] = '-';
            b->len++;
        }
        u = (unsigned int)-d;
    }
    else
    {
        u = (unsigned int)d;
    }

    do
    {
        tmp[i] = (char)('0' + (u % 10U));
        i++;
        u /= 10U;
    } while (u > 0U);

    while ((i > 0U) && (b->len < (CAIRN_BUFFER_MAX_BYTES - 1U)))
    {
        i--;
        b->data[b->len] = tmp[i];
        b->len++;
    }

    b->data[b->len] = '\0';

    CAIRN_ASSERT(b->len < CAIRN_BUFFER_MAX_BYTES);
    CAIRN_ASSERT(cairn_str_nlen(b->data, CAIRN_BUFFER_MAX_BYTES) <= b->len);
}
