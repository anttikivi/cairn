/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRBUF_H
#define CRBUF_H

#include <stddef.h>

#ifndef CR_BUF_MAX_BYTES
#    include <crunit.h>
#    define CR_BUF_MAX_BYTES CR_KB((size_t)1U)
#endif

struct cr_buf
{
    char data[CR_BUF_MAX_BYTES];
    size_t len;
};

/*
 * Initialize or empty a buffer. This operation does not free any memory and
 * only sets the buffer's length to zero and its first character to a null byte.
 */
void crbinit(struct cr_buf *b);
/* Append character to the end of the buffer. */
void crbachar(struct cr_buf *b, char c);
/* Append character array to the end of the buffer. */
void crbastr(struct cr_buf *b, const char *s);
/* Append size_t to the end of the buffer. */
void crbasize(struct cr_buf *b, size_t d);
/* Append int to the end of the buffer. */
void crbaint(struct cr_buf *b, int d);

#endif
