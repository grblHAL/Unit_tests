# STM32F3 flash scope and regression

Rechecked 2026-11-24: original sourcebff8acc49510cc74e14aaef721e15aeffd0df4f6
and COREa53a16a4d756f12a27006152ba3a99b5ec46b2c7 remain unchanged.

## 2026-10-24: first halfword programming error is overwritten

`driver_stm32f3_flash.program_first_failure` uses a valid word-aligned source
buffer and a HAL that fails only the first halfword. Original code unconditionally
issues the second call and overwrites status with its success, continues writes,
and returns true despite the first halfword remaining erased. The correct false
return and immediate-stop assertions are retained under one exact
WILL_FAIL/known_bug label. Paired second-halfword failures stop and return false.

Proposed source repair: preserve the first failed status and issue the second
halfword only when the first succeeds, as F4 does. No firmware changes are made.
After upstream repair remove only this exact expected-failure label and resolved
section, then rerun source-matched sanitizer/coverage checks. No sanitizer
allowance is registered.

The suite uses the actual F303xC HAL constants: flash base0x08000000, size register
0x1FFFF7CC and2KB pages. Process-local mappings provide those actual addresses;
Windows VirtualAlloc and Linux MAP_FIXED_NOREPLACE refuse occupied mappings.
Original FLASH_TARGET reads the simulated register and computes its address.
Separate128KB/256KB capacity cases validate the result independently as end-minus-
4KB. Full2KB-page, read/copy, unchanged, unlock/erase/program failure and retry
cases execute original Src/flash.c. Host SDK signatures/erase layout match the
checked-out headers; actual HAL/ARM instructions are not executed.

Source ignores unlock status; locked erase is modelled as a HAL error and lock
restoration remains required. No erased-memory or private state is fabricated to
force paths. Linux mappings, other device geometries, full controller allocation/
settings boot, physical flash/cache/IRQ timing and SDK/board builds remain
unverified. These are selected storage-module results, not whole-driver coverage.

The mock flash-size register uses owned uint16_t storage. Its former factory
address overlapped 32-bit Linux ASan shadow memory. Real flash mapping and
128/256 KiB geometry assertions are retained; no production register definition
is replaced.
