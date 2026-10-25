# Known defects

## Report-format host portability warnings - 2026-10-24

Source a752dc6cdaf193b039cae3495b279997d3ef8d48 uses `%ld` for uint32_t
hours/minutes at odometer.c173/179. Windows Clang reports argument type mismatch
(long versus unsigned int). The original source is retained. This source file
alone uses -Wno-error=format so the warnings remain visible while functional
host tests execute; fixtures keep -Werror. This is not a clean-Werror source
claim or an upstream fix. No runtime diagnostic is waived.

An upstream portable-format fix should use the matching uint32 format macro.
Afterward remove the source-specific warning-promotion exception and this entry.
