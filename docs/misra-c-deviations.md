# Deviations from the MISRA C:2025 Guidelines

Cairn aims to follow the MISRA C:2025 guidelines to produce C code that is safe.
This document contains the deviations from the guidelines and the rationales for
them.

## Deviation-001

### Rule

21.8 The Standard Library termination functions of `<stdlib.h>` shall not be
used

### Scope

Calling `abort()` in `crdterm()`, `src/crdbg.c`

### Rationale

The `abort` function is used in the implementation of the abnormal termination
function in the assertions provided by the library. Consumers of the library
must be able to perform a failing assertion without the code continuing
execution normally afterwards.

The other alternative considered for the fallback termination was an infinite
loop which was deemed unsuitable due to even more unpredictable side effects.

The assertions allow enabling supported debugging breakpoints before the
termination. Other termination functions are also preferred over `abort` when
they are available and the library has added support for using them.

## Deviation-002

### Rule

20.10 The `#` and `##` preprocessor operators should not be used

### Scope

The `#` preprocessor rule is used in `include/crdbg.h` and `include/crtest.h`

### Rationale

Both of the headers `include/crdbg.h` and `include/crtest.h` include
functionality that is meant only for debugging and testing, and the `#` is used
in those contexts only. It is used in cases where the program would need to
print the expression that caused the test or assertion to fail. The operator is
chosen instead of alternative solution, like constant string, to allow more
practical use and to ensure that the printed expression always matches the
expression that was tested.

## Deviation-003

### Rule

21.5 The standard _header file_ `<signal.h>` shall not be used

### Scope

Using the functionality of `<signal.h>` in `src/crproc.c`

### Rationale

`src/crproc.c` handles spawning child processes. `<signal.h>` is included and
used to handle setting signal masks for the spawned child processes.

Currently permitted symbols include `sigset_t`, `sigemptyset`, `sigaddset`,
`kill`, `SIGCHLD`, and `SIGPIPE`.
