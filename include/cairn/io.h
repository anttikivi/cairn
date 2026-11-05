/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CAIRN_IO_H
#define CAIRN_IO_H

#include <cairn/error.h>

enum cairn_error cairn_io_print_out(const char *s);
enum cairn_error cairn_io_print_err(const char *s);

#endif
