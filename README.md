# Cairn

[![builds.sr.ht status](https://builds.sr.ht/~anttikivi/cairn.svg)](https://builds.sr.ht/~anttikivi/cairn?)

`cairn` is a C utility library that provides useful functions. It also replaces
some C standard library functionality with alternatives that aim to be useful in
projects that follow the MISRA C guidelines.

## Getting Started

`cairn` is only distributed as source code.

### Prerequisites

- C99-compatible compiler toolchain
- [Meson](https://mesonbuild.com/) or [muon](https://muon.build/)
- A compatible build backend like Ninja or muon's built-in samurai

To build `cairn` or to participate in its development, you need to configure the
build environment first.

### Configuring

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
[`clang-tidy`](https://clang.llvm.org/extra/clang-tidy/) and
[`clang-format`](https://clang.llvm.org/docs/ClangFormat.html) respectively.
Additionally, the project is [REUSE-compliant](https://reuse.software/) and uses
the [REUSE tool](https://reuse.readthedocs.io/en/stable/index.html) to add the
appropriate license headers and check for compliance. For the moment, the REUSE
tool is run via [`uvx`](https://docs.astral.sh/uv/).

The tools can be run using Ninja, if using Meson, or samurai, if using muon.

Ninja:

```sh
ninja -C build/debug clang-format
ninja -C build/debug clang-format-check
ninja -C build/debug clang-tidy
ninja -C build/debug reuse-annotate
ninja -C build/debug reuse-check
```

samurai:

```sh
muon -C build/debug samu clang-format
muon -C build/debug samu clang-format-check
muon -C build/debug samu clang-tidy
muon -C build/debug samu reuse-annotate
muon -C build/debug samu reuse-check
```

## License

© 2026 Antti Kivi

`cairn` is licensed under the
[GNU Lesser General Public License v3.0 or later](https://www.gnu.org/licenses/lgpl-3.0.html).
