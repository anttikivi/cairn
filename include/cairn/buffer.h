/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BASE_BUFFER_H
#define BASE_BUFFER_H

#include <stddef.h>

#ifndef BUFFER_MAX_BYTES
#    include "units.h"
#    define BUFFER_MAX_BYTES KB(1U)
#endif

struct buffer
{
    char data[BUFFER_MAX_BYTES];
    size_t len;
};

void buffer_init(struct buffer *b);
void buffer_append_char(struct buffer *b, char c);
void buffer_append_str(struct buffer *b, const char *s);
void buffer_append_size(struct buffer *b, size_t d);
void buffer_append_int(struct buffer *b, int d);

#endif
