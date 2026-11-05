/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "buffer.h"

#include <stddef.h>

#include "bool.h"
#include "debug.h"
#include "strings.h"

#ifndef BUFFER_ALLOW_APPEND_INT
#    define BUFFER_ALLOW_APPEND_INT (0)
#endif

void
buffer_init(struct buffer *b)
{
    ASSERT(b != NULL);
    b->len = 0;
    b->data[0] = '\0';
}

void
buffer_append_char(struct buffer *b, char c)
{
    ASSERT(b != NULL);

    if (b->len < (BUFFER_MAX_BYTES - 1U))
    {
        b->data[b->len] = c;
        b->data[b->len + 1] = '\0';
        b->len++;
    }

    ASSERT(b->len <= BUFFER_MAX_BYTES);
    ASSERT(str_nlen(b->data, BUFFER_MAX_BYTES) <= b->len);
}

void
buffer_append_str(struct buffer *b, const char *s)
{
    size_t i = 0;

    ASSERT(b != NULL);
    ASSERT(s != NULL);

    while ((s[i] != '\0') && (b->len < (BUFFER_MAX_BYTES - 1U)))
    {
        b->data[b->len] = s[i];
        b->len++;
        i++;
    }

    b->data[b->len] = '\0';

    ASSERT(b->len <= BUFFER_MAX_BYTES);
    ASSERT(str_nlen(b->data, BUFFER_MAX_BYTES) <= b->len);
}

void
buffer_append_size(struct buffer *b, size_t d)
{
    char tmp[32]; /* overkill */
    size_t i = 0U;
    size_t u = d;

    ASSERT(b != NULL);

    do
    {
        tmp[i] = (char)('0' + (u % 10U));
        i++;
        u /= 10U;
    } while (u > 0U);

    while ((i > 0U) && (b->len < (BUFFER_MAX_BYTES - 1U)))
    {
        i--;
        b->data[b->len] = tmp[i];
        b->len++;
    }

    b->data[b->len] = '\0';

    ASSERT(b->len < BUFFER_MAX_BYTES);
    ASSERT(str_nlen(b->data, BUFFER_MAX_BYTES) <= b->len);
}

void
buffer_append_int(struct buffer *b, int d)
{
    char tmp[32]; /* overkill */
    size_t i = 0U;
    unsigned int u;

#if !BUFFER_ALLOW_APPEND_INT
    ASSERT(false);
#endif

    ASSERT(b != NULL);

    if (d < 0)
    {
        if (b->len < (BUFFER_MAX_BYTES - 1U))
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

    while ((i > 0U) && (b->len < (BUFFER_MAX_BYTES - 1U)))
    {
        i--;
        b->data[b->len] = tmp[i];
        b->len++;
    }

    b->data[b->len] = '\0';

    ASSERT(b->len < BUFFER_MAX_BYTES);
    ASSERT(str_nlen(b->data, BUFFER_MAX_BYTES) <= b->len);
}
