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
        'c_std=c99',
        'warning_level=3',
        'werror=true',
        'b_ndebug=if-release',
    ],
)

cc = meson.get_compiler('c')
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

src_paths = [
    'src/buffer.c',
    'src/debug.c',
    'src/io.c',
    'src/semver.c',
    'src/strings.c',
    'src/test.c',
]
header_paths = [
    'include/cairn/buffer.h',
    'include/cairn/debug.h',
    'include/cairn/error.h',
    'include/cairn/io.h',
    'include/cairn/semver.h',
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

clang_format = find_program('clang-format', required: false)
if clang_format.found()
    run_target('clang-format', command: [clang_format, '-i'] + fmt_paths)
    run_target(
        'clang-format-check',
        command: [clang_format, '--dry-run', '--Werror'] + fmt_paths,
    )
endif

clang_tidy = find_program('clang-tidy', required: false)
if clang_tidy.found()
    run_target(
        'clang-tidy',
        command: [clang_tidy, '-p', meson.project_build_root(), '--quiet'] + c_paths,
    )
endif

uvx = find_program('uvx', required: false)
if uvx.found()
    reuse = [uvx, '--from=reuse[charset-normalizer]', 'reuse', '--root', root]

    escapes_at = '\\@'.format() == '@'

    copyright = '--copyright=Antti Kivi <antti@anttikivi.com>'
    if escapes_at
        copyright = '--copyright=Antti Kivi <antti\\@anttikivi.com>'
    endif

    run_target(
        'reuse-annotate',
        command: reuse + [
            'annotate',
            copyright,
            '--license=LGPL-3.0-or-later',
            '--copyright-prefix=spdx-c',
            '--recursive',
            root / 'meson.build',
            root / 'meson_options.txt',
            root / 'include',
            root / 'src',
            root / 'test',
        ],
    )
    run_target('reuse-check', command: reuse + ['lint'])
endif

summary(
    {
        'clang-format': clang_format.found(),
        'clang-tidy': clang_tidy.found(),
        'uvx': uvx.found(),
    },
    section: 'Developer tools',
)
