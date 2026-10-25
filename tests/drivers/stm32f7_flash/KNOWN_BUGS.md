# STM32F7 flash scope and regression

Original source85e6e800b16fb1a46bc00b87b7015489b9d3ec93 and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged.

## 2026-10-24: first halfword failure is overwritten by second success

`driver_stm32f7_flash.program_first_failure` supplies a valid aligned64-byte NVS
buffer and a HAL that reports HAL_ERROR for the first halfword write only. The
original function assigns the next successful write's status unconditionally,
continues the remaining writes and returns true although the first halfword
remains erased. The correct false return assertion is retained as one exact
WILL_FAIL/known_bug. A failure on a second halfword correctly stops and returns
false; unchanged/unlock/erase/read/write controls are separate passing cases.

Proposed source repair: issue the second halfword only after the first succeeds,
preserving the first failure status, as STM32F4's implementation does. No firmware
edit is made. When fixed upstream remove this exact expected-failure label and
resolved section, then run source-matched sanitizer/coverage checks.

The host uses -m32 and a compile-time pointer-width assertion. Linker-style
symbols point at writable simulated flash and sector1, matching the original
address-based contract without changing production pointer types. HAL calls,
flash bytes and errors are simulated; no actual STM32 SDK execution, ARM firmware
build or physical flash/cache/interrupt timing is established. The host HAL erase
structure models the F7 configuration without FLASH_OPTCR_nDBANK. NVS sizes are
word-aligned as CORE nvs_buffer_init requires. Lock-result semantics and additional
MCU/SDK configurations remain untested. No sanitizer allowance is registered.
