/*
 * SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef CRPLAT_H
#define CRPLAT_H

#if defined(__APPLE__) && defined(__MACH__)

#    include <TargetConditionals.h>

#    if defined(TARGET_OS_OSX) && TARGET_OS_OSX
#        define CR_PLAT_POSIX 1
#    else
#        error "unsupported Apple platform"
#    endif

#elif defined(__linux__) && !defined(__ANDROID__)

#    define CR_PLAT_POSIX 1

#elif defined(_WIN32)

#    define CR_PLAT_WINDOWS 1

#else

#    error "unsupported platform"

#endif

#ifndef CR_PLAT_POSIX
#    define CR_PLAT_POSIX 0
#endif

#ifndef CR_PLAT_WINDOWS
#    define CR_PLAT_WINDOWS 0
#endif

#endif
