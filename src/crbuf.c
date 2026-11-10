/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <crbuf.h>

#include <stddef.h>

#include <crdbg.h>
#include <crstr.h>

void
crbinit(struct cr_buf *b)
{
    CR_ASSERT(b != NULL);
    b->len = 0;
    b->data[0] = '\0';
}

void
crbachar(struct cr_buf *b, char c)
{
    CR_ASSERT(b != NULL);

    if (b->len < (CR_BUF_MAX_BYTES - 1U))
    {
        b->data[b->len] = c;
        b->data[b->len + 1] = '\0';
        b->len++;
    }

    CR_ASSERT(b->len <= CR_BUF_MAX_BYTES);
    CR_ASSERT(crsnlen(b->data, CR_BUF_MAX_BYTES) <= b->len);
}

void
crbastr(struct cr_buf *b, const char *s)
{
    size_t i = 0;

    CR_ASSERT(b != NULL);
    CR_ASSERT(s != NULL);

    while ((s[i] != '\0') && (b->len < (CR_BUF_MAX_BYTES - 1U)))
    {
        b->data[b->len] = s[i];
        b->len++;
        i++;
    }

    b->data[b->len] = '\0';

    CR_ASSERT(b->len <= CR_BUF_MAX_BYTES);
    CR_ASSERT(crsnlen(b->data, CR_BUF_MAX_BYTES) <= b->len);
}

void
crbasize(struct cr_buf *b, size_t d)
{
    char tmp[32]; /* overkill */
    size_t i = 0U;
    size_t u = d;

    CR_ASSERT(b != NULL);

    do
    {
        tmp[i] = (char)('0' + (u % 10U));
        i++;
        u /= 10U;
    } while (u > 0U);

    while ((i > 0U) && (b->len < (CR_BUF_MAX_BYTES - 1U)))
    {
        i--;
        b->data[b->len] = tmp[i];
        b->len++;
    }

    b->data[b->len] = '\0';

    CR_ASSERT(b->len < CR_BUF_MAX_BYTES);
    CR_ASSERT(crsnlen(b->data, CR_BUF_MAX_BYTES) <= b->len);
}

void
crbaint(struct cr_buf *b, int d)
{
    char tmp[32]; /* overkill */
    size_t i = 0U;
    unsigned int u;

    CR_ASSERT(b != NULL);

    if (d < 0)
    {
        if (b->len < (CR_BUF_MAX_BYTES - 1U))
        {
            b->data[b->len] = '-';
            b->len++;
        }
        u = 0U - (unsigned int)d;
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

    while ((i > 0U) && (b->len < (CR_BUF_MAX_BYTES - 1U)))
    {
        i--;
        b->data[b->len] = tmp[i];
        b->len++;
    }

    b->data[b->len] = '\0';

    CR_ASSERT(b->len < CR_BUF_MAX_BYTES);
    CR_ASSERT(crsnlen(b->data, CR_BUF_MAX_BYTES) <= b->len);
}
