/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BASE_BOOL_H
#define BASE_BOOL_H

#if !defined(__bool_true_false_are_defined) && !defined(bool)
typedef unsigned char bool;
#    ifndef false
#        define false ((bool)0)
#    endif
#    ifndef true
#        define true ((bool)1)
#    endif
#    ifndef __bool_true_false_are_defined
#        define __bool_true_false_are_defined 1
#    endif
#endif

#endif
