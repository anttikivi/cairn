/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include <cairn/semver.h>

#include <stddef.h>

#include <cairn/debug.h>

enum cairn_error
cairn_semver_parse(struct cairn_semver *out, char *s, struct cairn_buffer *msg)
{
    CAIRN_ASSERT(out != NULL);
    CAIRN_ASSERT(s != NULL);
    CAIRN_ASSERT(msg != NULL);

    (void)out;
    (void)s;
    (void)msg;

    return CAIRN_ERR_OK;
}
