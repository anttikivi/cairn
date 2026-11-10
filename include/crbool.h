/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRBOOL_H
#define CRBOOL_H

#include <cairn/crcfg.h>

#if CR_USE_STDBOOL
#    include <stdbool.h>
#endif

typedef CR_BOOL_TYPE crbool;

#if CR_USE_STDBOOL
#    define CR_FALSE false
#    define CR_TRUE  true
#else
#    define CR_FALSE (0)
#    define CR_TRUE  (1)
#endif

#endif
