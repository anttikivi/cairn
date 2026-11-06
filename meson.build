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

include = include_directories('include')
src = files(
    'src/buffer.c',
    'src/debug.c',
    'src/io.c',
    'src/semver.c',
    'src/strings.c',
    'src/test.c',
)

lib = static_library(
    'cairn',
    src,
    include_directories: include,
    install: true,
)
dep = declare_dependency(include_directories: include, link_with: lib)
meson.override_dependency('cairn', dep)

install_subdir('include/cairn', install_dir: get_option('includedir'))

import('pkgconfig').generate(lib, name: 'cairn')

if get_option('tests')
    foreach name : ['buffer', 'strings']
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

uvx = find_program('uvx', required: get_option('uvx'))

if uvx.found()
    root = meson.project_source_root()
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
