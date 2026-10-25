# STM32H7 flash scope

Original sourcebfe5d4f6ec271cc9929336244c3b1c8e55d1d040 and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged. No expected assertion
or sanitizer allowances are registered for these valid storage cases.

The suite compiles original Src/flash.c and original Inc/flash.h in32-bit host
targets. H743 and H723 model definitions select actual source-supported32-byte
flash words. CMSIS headers show eight sectors for both and DUAL_BANK for H743;
HAL headers define BANK_2 only under DUAL_BANK. The simulated HAL validates bank2
for H743 and bank1 for H723, sector7 and actual32-bit DataAddress call semantics.
The source comment mentions16-byte writes but its header exposes only32 for these
models; no invented16-byte configuration is compiled.

Cases cover erased reads, whole-word copy/readback, unchanged suppression,
unlock/erase/first-word/second-word failure, retry and a36-byte source allocated
at its exact length. The source correctly pads the final flash word with zeros;
callbacks validate padding and bytes beyond the padded range stay erased. This
is valid short-tail behavior, not an attempted invalid-buffer reproduction.

Linker-style symbols provide a simulated storage region. Original pointer types,
code and header names remain unchanged. HAL signatures/constants are modelled
from the checked-out SDK headers; the actual SDK and ARM instructions are not
executed. Board linker reservations, cache behavior, physical programming and
alignment constraints and firmware integration remain. No whole-driver coverage
or board success claim is made.
