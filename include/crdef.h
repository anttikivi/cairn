/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRDEF_H
#define CRDEF_H

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#    define CR_NORETURN _Noreturn
#elif defined(__GNUC__) || defined(__clang__)
#    define CR_NORETURN __attribute__((__noreturn__))
#elif defined(_MSC_VER)
#    define CR_NORETURN __declspec(noreturn)
#else
#    define CR_NORETURN
#endif

#define CR_EXIT_SUCCESS 0
#define CR_EXIT_FAILURE 1

#endif
