# SPDX-FileCopyrightText: (C) 2026 Antti Kivi <antti@anttikivi.com>
#
# SPDX-License-Identifier: LGPL-3.0-or-later

project(
    'cairn',
    'c',
    version: '0.1.0-dev',
    license: 'LGPL-3.0-or-later',
    meson_version: '>= 1.0.0',
    default_options: [
        'c_std=c89',
        'warning_level=3',
        'werror=true',
        'b_ndebug=if-release',
    ],
)

if get_option('c_std') == 'none'
    error('cairn requires explicit C standard')
endif

cc = meson.get_compiler('c')
cfg = configuration_data()

project_arguments = []

if cc.get_argument_syntax() == 'gcc'
    project_arguments += cc.get_supported_arguments(
        '-Wshadow',
        '-Wundef',
        '-Wunused',
        '-Wnull-dereference',
        '-Wredundant-decls',
        '-Wconversion',
        '-Wsign-conversion',
        '-Wdouble-promotion',
        '-Wcast-align',
        '-Wcast-qual',
        '-Wwrite-strings',
        '-Wstrict-prototypes',
        '-Wmissing-prototypes',
        '-Wmissing-declarations',
        '-Wdeclaration-after-statement',
        '-Wold-style-definition',
        '-Wformat=2',
        '-Wvla',
        '-Wformat-overflow=2',
        '-Wformat-truncation=2',
        '-Wlogical-op',
        '-Wduplicated-cond',
        '-Wduplicated-branches',
        '-Wrestrict',
        '-Wjump-misses-init',
        '-Wstack-usage=8192',
        '-Wdocumentation',
    )
endif

add_project_arguments(project_arguments, language: 'c')

check_arguments = project_arguments

warning_level = get_option('warning_level')
werror = get_option('werror')

if cc.get_argument_syntax() == 'msvc'
    if warning_level == '1'
        check_arguments += cc.get_supported_arguments('/W2')
    elif warning_level == '2'
        check_arguments += cc.get_supported_arguments('/W3')
    elif warning_level == '3'
        check_arguments += cc.get_supported_arguments('/W4')
    elif warning_level == 'everything'
        check_arguments += cc.get_supported_arguments('/Wall')
    endif
    if werror
        check_arguments += cc.get_supported_arguments('/WX')
    endif
else
    if warning_level == '1'
        check_arguments += cc.get_supported_arguments('-Wall')
    elif warning_level == '2'
        check_arguments += cc.get_supported_arguments('-Wall', '-Wextra')
    elif warning_level == '3'
        check_arguments += cc.get_supported_arguments(
            '-Wall',
            '-Wextra',
            '-Wpedantic',
        )
    elif warning_level == 'everything'
        check_arguments += cc.get_supported_arguments(
            '-Wall',
            '-Wextra',
            '-Wpedantic',
            '-Weverything',
        )
    endif
    if werror
        check_arguments += cc.get_supported_arguments('-Werror')
    endif
endif

# Check by compilation instead of checking the C standard variable to account
# for GNU etc.
c99_or_later = cc.compiles(
    '''
#ifndef __STDC_VERSION__
#   error "not C99 or later"
#elif __STDC_VERSION__ < 199901L
#   error "not C99 or later"
#endif

int main(void)
{
    return 0;
}
  ''',
    args: check_arguments,
    name: 'selected C standard is C99 or later',
)

stdint = get_option('stdint')
stdbool = get_option('stdbool')
int64 = get_option('int64')

use_stdint = stdint.enabled() or (stdint.auto() and c99_or_later)
use_stdbool = stdbool.enabled() or (stdbool.auto() and c99_or_later)
use_int64 = false

if use_stdint
    have_stdint = cc.compiles(
        '''
#include <stdint.h>

#if !defined(INT_LEAST8_MIN) || !defined(INT_LEAST8_MAX) || !defined(UINT_LEAST8_MAX)
#    error "missing 8-bit limits"
#endif

#if !defined(INT_LEAST16_MIN) || !defined(INT_LEAST16_MAX) || !defined(UINT_LEAST16_MAX)
#    error "missing 16-bit limits"
#endif

#if !defined(INT_LEAST32_MIN) || !defined(INT_LEAST32_MAX) || !defined(UINT_LEAST32_MAX)
#    error "missing 32-bit limits"
#endif

typedef int_least8_t probe_i8;
typedef uint_least8_t probe_u8;
typedef int_least16_t probe_i16;
typedef uint_least16_t probe_u16;
typedef int_least32_t probe_i32;
typedef uint_least32_t probe_u32;

int main(void)
{
    return 0;
}
    ''',
        args: check_arguments,
        name: 'least-width integer types from stdint.h',
    )
    if not have_stdint
        error(
            'requested stdint.h is not available',
        )
    endif

    if not int64.disabled()
        use_int64 = cc.compiles(
            '''
#include <stdint.h>

#if !defined(INT_LEAST64_MIN) || !defined(INT_LEAST64_MAX) || !defined(UINT_LEAST64_MAX)
#    error "missing 64-bit limits"
#endif

typedef int_least64_t probe_i64;
typedef uint_least64_t probe_u64;

int main(void)
{
    return 0;
}
    ''',
            args: check_arguments,
            name: '64-bit least-width integer types from stdint.h',
        )
    endif
else
    int_candidates = [
        ['I', 'signed char', 'SCHAR_MIN', 'SCHAR_MAX'],
        ['I', 'short', 'SHRT_MIN', 'SHRT_MAX'],
        ['I', 'int', 'INT_MIN', 'INT_MAX'],
        ['I', 'long', 'LONG_MIN', 'LONG_MAX'],
        ['U', 'unsigned char', '', 'UCHAR_MAX'],
        ['U', 'unsigned short', '', 'USHRT_MAX'],
        ['U', 'unsigned int', '', 'UINT_MAX'],
        ['U', 'unsigned long', '', 'ULONG_MAX'],
    ]

    have_long_long = cc.compiles(
        '''
#include <limits.h>

#if !defined(LLONG_MIN) || !defined(LLONG_MAX) || !defined(ULLONG_MAX)
#    error "missing long long limits"
#endif

typedef long long probe_signed;
typedef unsigned long long probe_unsigned;

int main(void)
{
    return 0;
}
        ''',
        args: check_arguments,
        name: 'long long types and limits',
    )
    if have_long_long
        int_candidates += [
            ['I', 'long long', 'LLONG_MIN', 'LLONG_MAX'],
            ['U', 'unsigned long long', '', 'ULLONG_MAX'],
        ]
    endif

    if not int64.disabled()
        have_least_i64 = false
        have_least_u64 = false

        foreach signedness : ['I', 'U']
            foreach candidate : int_candidates
                if candidate[0] != signedness
                    continue
                endif

                if signedness == 'I'
                    range_check = '''
#if @0@ < 9223372036854775807 || @1@ > (-9223372036854775807)
#    error "insufficient signed range"
#endif
'''.format(candidate[3], candidate[2])
                else
                    range_check = '''
#if @0@ < 18446744073709551615U
#    error "insufficient unsigned range"
#endif
'''.format(candidate[3])
                endif

                int_supported = cc.compiles(
                    '''
#include <limits.h>

@0@

typedef @1@ probe_type;

int main(void)
{
    return 0;
}
'''.format(range_check, candidate[1]),
                    args: check_arguments,
                    name: 'at least 64-bit @0@'.format(candidate[1]),
                )

                if int_supported
                    prefix = 'CR_LEAST_@0@64_TYPE'.format(signedness)

                    cfg.set(prefix, candidate[1])
                    cfg.set(prefix + '_MAX', candidate[3])

                    if signedness == 'I'
                        cfg.set(prefix + '_MIN', candidate[2])
                        have_least_i64 = true
                    else
                        have_least_u64 = true
                    endif

                    break
                endif
            endforeach
        endforeach

        use_int64 = have_least_i64 and have_least_u64
    endif
endif

if int64.enabled() and not use_int64
    error('no support for integers that are at least 64 bits wide')
endif

if not use_stdint
    int_widths = [
        [8, '127', '255U'],
        [16, '32767', '65535U'],
        [32, '2147483647L', '4294967295UL'],
    ]

    if use_int64
        int_widths += [[64, '9223372036854775807', '18446744073709551615U']]
    endif

    foreach width : int_widths
        foreach signedness : ['I', 'U']
            foreach candidate : int_candidates
                if candidate[0] != signedness
                    continue
                endif

                if signedness == 'I'
                    range_check = '''
#if @0@ != @2@ || @1@ != (-@2@ - 1)
#    error "incorrect signed range"
#endif
'''.format(candidate[3], candidate[2], width[1])
                else
                    range_check = '''
#if @0@ != @1@
#    error "incorrect unsigned range"
#endif
'''.format(candidate[3], width[2])
                endif

                int_supported = cc.compiles(
                    '''
#include <limits.h>

@0@

typedef char check_storage[(sizeof(@1@) * CHAR_BIT == @2@) ? 1 : -1];

int main(void)
{
    return 0;
}
'''.format(range_check, candidate[1], width[0]),
                    args: check_arguments,
                    name: 'exactly @0@-bit @1@'.format(
                        width[0],
                        candidate[1],
                    ),
                )

                if int_supported
                    prefix = 'CR_@0@@1@_TYPE'.format(
                        signedness,
                        width[0],
                    )

                    cfg.set(prefix, candidate[1])
                    cfg.set(prefix + '_MAX', candidate[3])

                    if signedness == 'I'
                        cfg.set(prefix + '_MIN', candidate[2])
                    endif

                    break
                endif
            endforeach
        endforeach
    endforeach
endif

if use_stdbool
    have_stdbool = cc.compiles(
        '''
#include <stdbool.h>

int main(void)
{
    bool b = true;
    return b == false;
}
    ''',
        args: check_arguments,
        name: 'stdbool.h support',
    )
    if not have_stdbool
        error('requested stdbool.h is not available')
    endif
endif

if use_stdbool
    bool_type = 'bool'
else
    have_builtin_bool = cc.compiles(
        '''
typedef _Bool probe_bool;

int main(void)
{
    probe_bool b = (0 != 0);
    return b ? 1 : 0;
}
        ''',
        args: check_arguments,
        name: 'builtin _Bool type support',
    )
    if have_builtin_bool
        bool_type = '_Bool'
    else
        bool_type = 'unsigned char'
    endif
endif

cfg.set('CR_BOOL_TYPE', bool_type)
cfg.set10('CR_BREAKPOINTS', get_option('breakpoints'))
cfg.set10('CR_USE_STDINT', use_stdint)
cfg.set10('CR_USE_STDBOOL', use_stdbool)
cfg.set10('CR_USE_INT64', use_int64)

subdir('include' / 'cairn')

cfg_summary = {
    'C standard': get_option('c_std'),
    'stdint.h': use_stdint,
    'stdbool.h': use_stdbool,
    '64-bit ints': use_int64,
    'boolean type': bool_type,
}

src_paths = [
    'src/buffer.c',
    'src/crdbg.c',
    'src/io.c',
    'src/strings.c',
    'src/test.c',
]
header_paths = [
    'include/cairn/buffer.h',
    'include/cairn/crdbg.h',
    'include/cairn/crbool.h',
    'include/cairn/crint.h',
    'include/cairn/error.h',
    'include/cairn/io.h',
    'include/cairn/strings.h',
    'include/cairn/test.h',
    'include/cairn/units.h',
]
test_names = ['buffer', 'strings']
test_paths = []
foreach name : test_names
    test_paths += 'test' / (name + '.c')
endforeach

include = include_directories('include')

lib = static_library(
    'cairn',
    files(src_paths),
    include_directories: include,
    install: true,
)
dep = declare_dependency(include_directories: include, link_with: lib)
meson.override_dependency('cairn', dep)

install_subdir('include/cairn', install_dir: get_option('includedir'))

import('pkgconfig').generate(lib, name: 'cairn')

if get_option('tests')
    foreach name : test_names
        test(
            name,
            executable(
                'test_' + name,
                'test' / (name + '.c'),
                dependencies: dep,
            ),
        )
    endforeach
endif

root = meson.project_source_root()

c_paths = []
foreach path : src_paths + test_paths
    c_paths += root / path
endforeach

fmt_paths = c_paths
foreach path : header_paths
    fmt_paths += root / path
endforeach

tools_summary = {}

clang_format = find_program('clang-format', required: false)
if clang_format.found()
    tools_summary += {'clang-format': clang_format}

    run_target('clang-format', command: [clang_format, '-i'] + fmt_paths)
    run_target(
        'clang-format-check',
        command: [clang_format, '--dry-run', '--Werror'] + fmt_paths,
    )
else
    tools_summary += {'clang-format': clang_format.found()}
endif

platform_summary = {}

clang_tidy = find_program('clang-tidy', required: false)
if clang_tidy.found()
    tools_summary += {'clang-tidy': clang_tidy}
    clang_tidy_env = environment()

    if host_machine.system() == 'darwin' and not meson.is_cross_build()
        xcrun = find_program('xcrun')
        macosx_sdk_path = run_command(
            xcrun,
            '--sdk',
            'macosx',
            '--show-sdk-path',
            check: true,
        ).stdout().strip()

        platform_summary += {'macOS SDK': macosx_sdk_path}
        clang_tidy_env.set('SDKROOT', macosx_sdk_path)
    endif

    run_target(
        'clang-tidy',
        command: [clang_tidy, '-p', meson.project_build_root(), '--quiet'] + c_paths,
        env: clang_tidy_env,
    )
else
    tools_summary += {'clang-tidy': clang_tidy.found()}
endif

cppcheck = find_program('cppcheck', required: false)
if cppcheck.found()
    tools_summary += {'cppcheck': cppcheck}

    misra_config = configuration_data()
    misra_config.set(
        'RULE_TEXTS',
        (root / 'tools' / 'misra-c-2012.txt').replace('\\', '/'),
    )
    configure_file(
        input: root / 'tools' / 'misra.json.in',
        output: 'misra.json',
        configuration: misra_config,
    )

    cppcheck_args = [
        '--project=' + (
            meson.project_build_root() / 'compile_commands.json'
        ),
        '--std=' + get_option('c_std'),
        '--enable=all',
        '--suppress=missingIncludeSystem',
        '--inline-suppr',
        '--inconclusive',
        '--check-level=exhaustive',
        '--error-exitcode=1',
        '--library=' + (root / 'tools' / 'cppcheck-library.xml'),
        '--addon=' + (meson.current_build_dir() / 'misra.json'),
        '--checkers-report=' + (
            meson.project_build_root() / 'cppcheck-checkers.txt'
        ),
    ]

    # TODO: Add more granular checking of the libraries in use.
    if host_machine.system() == 'windows'
        cppcheck_args += ['--library=windows']
    else
        cppcheck_args += ['--library=posix']
    endif

    run_target(
        'cppcheck',
        command: [cppcheck] + cppcheck_args,
    )
else
    tools_summary += {'cppcheck': cppcheck.found()}
endif

uvx = find_program('uvx', required: false)
if uvx.found()
    tools_summary += {'uvx': uvx}

    reuse = [uvx, '--from=reuse[charset-normalizer]', 'reuse', '--root', root]

    escapes_at = '\\@'.format() == '@'

    copyright = '--copyright=Antti Kivi <antti@anttikivi.com>'
    if escapes_at
        copyright = '--copyright=Antti Kivi <antti\\@anttikivi.com>'
    endif

    reuse_annotate = reuse + [
        'annotate',
        copyright,
        '--license=LGPL-3.0-or-later',
        '--copyright-prefix=spdx-c',
    ]

    reuse_annotate_sources = run_target(
        'reuse-annotate-sources',
        command: reuse_annotate + [
            '--skip-unrecognised',
            '--recursive',
            root / '.builds',
            root / '.github',
            root / 'meson.build',
            root / 'meson_options.txt',
            root / 'include',
            root / 'src',
            root / 'test',
        ],
    )
    reuse_annotate_templates = run_target(
        'reuse-annotate-templates',
        command: reuse_annotate + [
            '--style=c',
            '--multi-line',
            root / 'include' / 'cairn' / 'config.h.in',
        ],
    )
    alias_target(
        'reuse-annotate',
        reuse_annotate_sources,
        reuse_annotate_templates,
    )
    run_target('reuse-check', command: reuse + ['lint'])
else
    tools_summary += {'uvx': uvx.found()}
endif

summary(cfg_summary, section: 'library configuration')

if platform_summary != {}
    summary(platform_summary, section: 'platform')
endif

summary(tools_summary, section: 'developer tools')
