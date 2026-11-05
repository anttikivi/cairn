/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CAIRN_BUFFER_H
#define CAIRN_BUFFER_H

#include <stddef.h>

#ifndef CAIRN_BUFFER_MAX_BYTES
#    include <cairn/units.h>
#    define CAIRN_BUFFER_MAX_BYTES CAIRN_KB(1U)
#endif

struct cairn_buffer
{
    char data[CAIRN_BUFFER_MAX_BYTES];
    size_t len;
};

void cairn_buffer_init(struct cairn_buffer *b);
void cairn_buffer_append_char(struct cairn_buffer *b, char c);
void cairn_buffer_append_str(struct cairn_buffer *b, const char *s);
void cairn_buffer_append_size(struct cairn_buffer *b, size_t d);
void cairn_buffer_append_int(struct cairn_buffer *b, int d);

#endif
