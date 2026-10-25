# STM32H7 serial host scope - batch47

Twenty-four cases compile unchanged serial.c and original H743/H723 ST HAL/CMSIS,
main/driver/generic-map headers with actual CORE stream/passthrough/VFS/formatting.
Driverbfe5d4f6ec271cc9929336244c3b1c8e55d1d040; CORE
b01f481072edecac33d5e40c25869359a5b3fa1f. H743 tests claim primary USART3 D8/9
and original secondary USART6 C6/7 plus supported third USART1 A9/10. Native H7
USART6 uses AF7, not the F7 SDK's AF8. H723 has one native initialization case;
other H723 stream workflows are not claimed as tested.

All24 pass Windows Clang ASan/UBSan and strict1.19s, with no known assertions or
diagnostic allowances. GPIO/RCC/IRQ requests, native FIFO-disabled RX/TX status,
independent stream handlers/traffic, full/wrap/cancel, binary/flush/full/blocking
TX, format/baud, RX mute/TX preservation, ownership and CORE tool-ACK execute.
Registers at original SDK addresses, GPIO/NVIC, IRQ/data-register effects and
PCLK120MHz are models; no physical FIFO timing, board/ARM/controller proof.

## SDK prescaler data boundary

The driver uses UART_DIV_SAMPLING16 with the SDK's extern UARTPrescTable. Compiling
the full UART HAL unit natively fails on ARM-only __LDREXW/__STREXW routines;
no declarations, instruction replacements or function aliases hide that boundary.
CMake reads exactly one original immutable UARTPrescTable data declaration from
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c and compiles it verbatim in a generated
data-only unit. It fails configuration if the declaration contract changes, tracks
that source as a configure dependency, and preserves unchanged generated timestamps.
No driver/SDK function or algorithm is extracted/copied/replaced. Actual macro
calculation and native driver BRR writes execute;1042 at115200 is verified.
The original ARM UART HAL routines remain uncompiled/unexecuted by this host suite.
No SDK source coverage or full SDK compatibility claim is made.

Other MCU/workflow variants, remaps/RS485, source primary-USART6 AF8 declarations
versus the current SDK AF7 name, pending-baud queue/IRQ lifecycle, real hardware
FIFO/errors/timing and full controller/ARM builds remain. No private queue flags
or empty-queue IRQ path is forced. Full56-suite1230 gate passes(1163 clean+67
known). First selected serial353/357 lines,108/122 branches,57/57 functions;
no full SDK/driver/configuration coverage claim. SDK data equality is recorded
against original line229 and candidate SHA, with no handwritten replacement table.
