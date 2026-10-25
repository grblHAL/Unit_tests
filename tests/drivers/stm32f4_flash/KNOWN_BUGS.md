# STM32F4 flash scope

Original sourcea6318ac92f079f49fab91687530f832997396edc and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged. No known assertion
or sanitizer allowance is registered for these storage cases.

Original Src/flash.c executes with a32-bit host target and linker-style storage/
sector symbols, not truncated64-bit host addresses or production patches. A
shared STM32 HAL fixture observes unlock/erase/halfword writes/lock and simulates
flash contents and errors. Cases cover read/copy, unchanged suppression, unlock
failure, one erase retry, exhausted erase failure, either halfword failure,
subsequent recovery and configured word-aligned sizes4/32/64/128. CORE
nvs_buffer_init explicitly rounds NVS size to a word boundary; unsupported odd
sizes are not manufactured. Assertions inspect byte results, programmed ranges
and restored lock state. Sector1 represents a linker-provided storage region.

This is a host storage suite, not an ARM firmware build, full SDK execution,
board flash validation or proof of physical interrupt/cache behavior. Lock-failure
return semantics and other STM32 modules/configurations remain to be covered.
