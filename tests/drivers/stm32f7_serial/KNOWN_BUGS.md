# STM32F7 serial host scope - batch45

Twenty-three cases compile unchanged serial.c with original main/driver/generic-map,
ST HAL/CMSIS F756 device headers and current pinned CORE stream/passthrough/VFS/
formatting modules. Driver85e6e800b16fb1a46bc00b87b7015489b9d3ec93 and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f. Generic primary port32 is USART3 at
GPIOD8/9. Original generic map fixes secondary USART6 GPIOC6/7; the
three-stream profile adds supported third USART1 GPIOA9/10. No board header is
overridden. No F4 register alias or source conversion is used: F7 ISR/RDR/TDR and
M0 parity declarations are native. F7 uses separate clock/IRQ/register provider.

Registration, GPIO/clock/IRQ requests, RX FIFO/full/wrap/cancel, realtime, real
CORE tool-ACK suspend/resume, binary/queued/flush/full/blocking TX, baud/parity,
RX mute preserving TX and release/reclaim execute. Three-stream profiles add
independent traffic/handlers and binary/queue/full/format/ownership/cancellation/
CORE tool-ACK workflows. All23 pass cumulative Clang ASan/UBSan and strict. Shared serial_core_host.c contains only the unchanged fail-fast unused
CORE callbacks extracted from the F4 fixture; both families link actual CORE
stream/VFS code and retain separate hardware providers. Affected F423 plus F711
cases originally passed34/34 strict; final F423+F723 pass46/46 strict, zero
known/unexpected/skipped.

Mapped hardware registers, data-register side effects, CPU IRQ delivery, GPIO/
NVIC and PCLK54/108MHz values are models. Actual RCC enable writes execute; no
physical baud, GPIO, IRQ race or board operation is established. Host Windows
ERROR/LPTR macros are undefined after loading Windows APIs so native CMSIS enum/
register names remain original. SDK files and production CORE/driver are untouched;
no function casts, ARM instruction replacements or obsolete-type aliases.

Primary-claim and three-stream3/6/1 profiles are tested. Other mappings/MCUs,
RS485, third RX-disable, provider claim guards and error IRQ states remain.
F7 baud-change queue/interrupt contract remains source-only.
Source changes baud by resetting RX/TX head/tail; do not equate this to complete
pending-IRQ cleanup without a supported contract. Full ARM firmware/controller/
hardware scope remain open. First selected serial coverage353/357 lines and
108/122 branches,57/57 functions; no SDK/whole-driver coverage claim. Full53-suite
gate1184 passes. No known exceptions or production source edits.
