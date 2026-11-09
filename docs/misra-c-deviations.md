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
