/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BASE_SEMVER_H
#define BASE_SEMVER_H

#include "buffer.h"
#include "error.h"
#include "int.h"

struct semver
{
    u32 major;
    u32 minor;
    u32 patch;
    const char *pre;
    const char *build;
};

enum error semver_parse(struct semver *out, char *s, struct buffer *msg);

#endif
