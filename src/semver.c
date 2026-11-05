/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "semver.h"

#include <stddef.h>

#include "debug.h"

enum error
semver_parse(struct semver *out, char *s, struct buffer *msg)
{
    ASSERT(out != NULL);
    ASSERT(s != NULL);
    ASSERT(msg != NULL);

    return ERR_OK;
}
