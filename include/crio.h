/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRIO_H
#define CRIO_H

#include <crerr.h>

/* Write the given byte array to the standard output. */
enum cr_err criout(const char *s);
/* Write the given byte array to the standard error output. */
enum cr_err crioerr(const char *s);

#endif
