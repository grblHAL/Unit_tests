# Original ARM module compile checks

`scripts/check_arm_modules.py` compiles complete original files using their
original SDK/CMSIS headers and a locked CORE checkout. Generated `grbl/` headers
only forward to those CORE headers, matching `components.cmake`. No host hardware
fixture, SDK replacement function, copied algorithm or instruction alias is used.
The script verifies ELF32 little-endian ARM relocatable objects and preserves
compiler commands, warnings, source/object hashes and the full source lock.
It attempts each selected module even when another fails; any failure fails the job.

| Driver | Configuration | Original modules |
|---|---|---|
| STM32F1 | F103xB / Cortex-M3 | serial.c; full UART HAL |
| STM32F3 | F303xC / Cortex-M4 / FPv4-SP hard | serial.c; full UART HAL |
| STM32F4 | F407xx / Cortex-M4 / FPv4-SP hard | serial.c; full UART HAL |
| STM32F7 | F756xx / Cortex-M7 / FPv5-SP hard | serial.c; full UART HAL |
| STM32H7 | H743xx and H723xx / Cortex-M7 / FPv5-DP hard | serial.c; full UART HAL for each |
| LPC176x | Cortex-M3 | serial.c; SDK uart_17xx_40xx.c and iocon_17xx_40xx.c |

Batch48 local result (2026-10-25): all15 modules compiled with Arm GNU Toolchain
14.2.Rel1 / GCC14.2.1, CORE b01f481072edecac33d5e40c25869359a5b3fa1f.
The reusable script was run for every family after initial standalone probes.
LPC builds emitted18 unused-parameter warnings from original SDK headers;
STM32 builds emitted no warnings. This is compile evidence, not new unit cases
or measured source coverage. Hosted Ubuntu/toolchain installation is pending.

Locked driver revisions:

- F1 c22362352f6abeea94897bb0346ae8042cdf3210
- F3 9a40877b87b6fffbb475f753f0e12cc6c5126770
- F4 a6318ac92f079f49fab91687530f832997396edc
- F7 85e6e800b16fb1a46bc00b87b7015489b9d3ec93
- H7 bfe5d4f6ec271cc9929336244c3b1c8e55d1d040
- LPC ea6e9f78fa349e86fbd58a203760b614f513684a

Firmware linking, startup/vector tables, alternate boards and pin maps, execution
of ARM HAL routines, peripheral timing and physical controllers remain unchecked.
The H7 native tests still reuse only the original immutable prescaler declaration;
successful target compilation does not change that runtime boundary.

LPC serial runtime needs a faithful FIFO model or hardware. Its original RX IRQ
reads RBR in a loop until hardware clears LSR.RDR; plain RAM cannot supply that
side effect. TX can write THR repeatedly in one IRQ, so RAM retains only the last
byte. Do not execute a fake non-terminating RX loop or replace SDK accessors to
claim original UART behavior. No LPC serial runtime cases are registered here.

## Arduino Due probe remains unregistered

Original SAM3X8E2321092b02cbbdecf2eba2b168a74b085e573418 and Arduino SAM
SDK790ff2c852bf159787a9966bddee4d9f55352d15 were also probed with the same
compiler/CORE, original `core_cm3.h` and `syscalls.h`, Cortex-M3 and the supported
primary UART/secondary USART2 selection. The complete SDK `usart.c` compiled.
Original driver `serial.c` did not: Arduino's real `syscalls.h` includes newlib
`sys/stat.h`, whose `st_mtime` macro expands inside CORE's `vfs.h` structures
(lines79/191). GCC14 also rejects the already documented char-versus-uint8_t
secondary enqueue callback initialization at serial.c759.

This is evidence for that exact current compiler/header/source combination,
not a claim that every older Arduino toolchain or board build fails. No source
edit, callback cast, macro undefinition or header substitution was used. Do not
add SAM to the registered ARM job until a supported original-source build
contract is established. This failed driver probe is outside the15 passing
registered module checks. Native SAM fixture results retain their documented
header/CPU boundary and cannot establish target compilation.
