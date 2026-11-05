/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BASE_IO_H
#define BASE_IO_H

#include "error.h"

enum error io_print_out(const char *s);
enum error io_print_err(const char *s);

#endif
