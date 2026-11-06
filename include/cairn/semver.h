/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CAIRN_SEMVER_H
#define CAIRN_SEMVER_H

#include <stdint.h>

#include <cairn/buffer.h>
#include <cairn/error.h>

struct cairn_semver
{
    uint32_t major;
    uint32_t minor;
    uint32_t patch;
    const char *pre;
    const char *build;
};

enum cairn_error cairn_semver_parse(struct cairn_semver *out, char *s,
                                    struct cairn_buffer *msg);

#endif
