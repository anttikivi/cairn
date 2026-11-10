# Cairn

[![builds.sr.ht status](https://builds.sr.ht/~anttikivi/cairn.svg)](https://builds.sr.ht/~anttikivi/cairn?)

`cairn` is a C utility library that provides useful functions. It also replaces
some C standard library functionality with alternatives that aim to be useful in
projects that follow the MISRA C guidelines.

## Getting Started

Cairn is only distributed as source code.

### Prerequisites

- C compiler toolchain

To build Cairn or to participate in its development, you need to configure the
build environment first.

While not a hard requirement, a build system could prove useful. Cairn has
pre-defined configuration for [Meson](https://mesonbuild.com/) that also works
with [muon](https://muon.build/). If using Meson or muon, you might also need a
compatible build backend like [Ninja](https://ninja-build.org/) or muon's
built-in samurai.

### Configuring

The easiest way to configure Cairn is to use the provided Meson configuration.
Configuring creates the files necessary to build the project and run the various
tools on it. It also generates `compile_commands.json` for different tools to
use. For different build types (e.g. `release`) replace `debug` in commands with
the desired build type.

To configure with Meson:

```sh
meson setup build/debug -Dbuildtype=debug
```

With muon:

```sh
muon setup -Dbuildtype=debug build/debug
```

If you want to build Cairn without the build system, you need to provide the
configuration header `crcfg.h` yourself. You can find the template that Meson
uses for this file in `src/crcfg.h.in`. Most of the definitions must be given in
the file. The only exception to this are the `CR_IN_TYPE*` and `CR_UN_TYPE*`
macros (e.g. `CR_I8_TYPE*` AND `CR_U8_TYPE*`). Those should only be defined if
the platform can supply the matching _exact-width_ integer types.

If a feature (e.g. 64-bit integers) is enabled, the compilation assumes that it
is available. The C code doesn't perform additional checks to see if that's
true.

You can find the explanations with examples for the definitions in the header
below:

```c
#ifndef CRCFG_H
#define CRCFG_H

/*
 * Whether to enable debugger breakpoints in debugging functions where
 * applicable.
 */
#define CR_BREAKPOINTS 0

/* Whether to use stdint.h for Cairn's integer type definitions. */
#define CR_USE_STDINT 0
/* Whether to use stdbool.h for Cairn's Boolean type definitions. */
#define CR_USE_STDBOOL 0
/* Whether to enable 64-bit integer types. */
#mesondefine CR_USE_INT64

/* The type to use for Cairn's Boolean type definition. */
#define CR_BOOL_TYPE unsigned char
/*
 * Whether the type used for Cairn's Boolean type definitions is the built-in
 * _Bool type.
 */
#define CR_USE_BUILTIN_BOOL 0

/* The type to use for Cairn's 8-bit exact-width signed integer type. */
#define CR_I8_TYPE signed char
/* The maximum value of Cairn's 8-bit exact-width signed integer type. */
#define CR_I8_TYPE_MAX SCHAR_MAX
/* The minimum value of Cairn's 8-bit exact-width signed integer type. */
#define CR_I8_TYPE_MIN SCHAR_MIN

/* The type to use for Cairn's 8-bit exact-width unsigned integer type. */
#define CR_U8_TYPE unsigned char
/* The maximum value of Cairn's 8-bit exact-width unsigned integer type. */
#define CR_U8_TYPE_MAX UCHAR_MAX

/* The rest of these definitions work like the 8-bit examples. */

#define CR_I16_TYPE short
#define CR_I16_TYPE_MAX SHRT_MAX
#define CR_I16_TYPE_MIN SHRT_MIN

#define CR_U16_TYPE unsigned short
#define CR_U16_TYPE_MAX USHRT_MAX

#define CR_I32_TYPE int
#define CR_I32_TYPE_MAX INT_MAX
#define CR_I32_TYPE_MIN INT_MIN

#define CR_U32_TYPE unsigned int
#define CR_U32_TYPE_MAX UINT_MAX

#define CR_I64_TYPE long
#define CR_I64_TYPE_MAX LONG_MAX
#define CR_I64_TYPE_MIN LONG_MIN

#define CR_U64_TYPE unsigned long
#define CR_U64_TYPE_MAX ULONG_MAX

/*
 * If the platform supports 64-bit integers, you must supply the values for
 * the integer types that are at least 64-bits, as they are normally resolved
 * via the build system.
 */

#define CR_LEAST_I64_TYPE long
#define CR_LEAST_I64_TYPE_MAX LONG_MAX
#define CR_LEAST_I64_TYPE_MIN LONG_MIN

#define CR_LEAST_U64_TYPE unsigned long
#define CR_LEAST_U64_TYPE_MAX ULONG_MAX

#endif
```

### Building

Meson:

```sh
meson compile -C build/debug
```

muon's samurai:

```sh
muon -C build/debug samu
```

Ninja:

```sh
ninja -C build/debug
```

### Running Tests

Please note that running the full test suite requires
[Python](https://www.python.org/).

Meson:

```sh
meson test -C build/debug
```

muon:

```sh
muon -C build/debug test
```

### Development Tools

For linting and formatting, `cairn` uses
[`clang-tidy`](https://clang.llvm.org/extra/clang-tidy/),
[`clang-format`](https://clang.llvm.org/docs/ClangFormat.html), and
[Cppcheck](https://cppcheck.sourceforge.io/). Additionally, the project is
[REUSE-compliant](https://reuse.software/) and uses the
[REUSE tool](https://reuse.readthedocs.io/en/stable/index.html) to add the
appropriate license headers and check for compliance. For the moment, the REUSE
tool is run via [`uvx`](https://docs.astral.sh/uv/).

The tools can be run using Ninja, if using Meson, or samurai, if using muon.

Ninja:

```sh
ninja -C build/debug clang-format
ninja -C build/debug clang-format-check
ninja -C build/debug clang-tidy
ninja -C build/debug cppcheck
ninja -C build/debug reuse-annotate
ninja -C build/debug reuse-check
```

samurai:

```sh
muon -C build/debug samu clang-format
muon -C build/debug samu clang-format-check
muon -C build/debug samu clang-tidy
muon -C build/debug samu cppcheck
muon -C build/debug samu reuse-annotate
muon -C build/debug samu reuse-check
```

## License

© 2026 Antti Kivi

`cairn` is licensed under the
[GNU Lesser General Public License v3.0 or later](https://www.gnu.org/licenses/lgpl-3.0.html).

### Third-party Components

`tools/misra-c-2012.txt` contains the MISRA C:2012 guideline headlines for
Cppcheck
[provided by the MISRA Consortium Limited](https://gitlab.com/MISRA/MISRA-C/MISRA-C-2012/tools/).
It is licensed under the
[Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International](https://creativecommons.org/licenses/by-nc-nd/4.0/)
license. See `LICENSES/CC-BY-NC-ND-4.0.txt` for more information.
