/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRERR_H
#define CRERR_H

enum cr_err
{
    CR_ERR_OK,
    CR_ERR_ARGS_INVALID,
    CR_ERR_IO_WRITE_FAILED,
    CR_ERR_IO_NULL_STRING,
    CR_ERR_IO_INPUT_OVERFLOW
};

#endif
