# STM32F3 serial host scope - batch46 local

Ten original-source cases compile serial.c with original main/driver/generic-map
and ST F303xC HAL/CMSIS headers plus actual CORE stream/passthrough/VFS/formatting.
Driver9a40877b87b6fffbb475f753f0e12cc6c5126770 and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f. Native fixed USART3 is GPIOB10/11,
115200 baud only. No F4/F7 register or callback aliases are provided. Original
advertised callbacks are used; unavailable baud/format/binary-write/count/mute
callbacks are not invented. Binary bytes use the supported write_char API.

Initialization/clock/GPIO/IRQ requests, RX FIFO/wrap/full/cancel, realtime commands,
actual CORE tool-ACK suspend/resume, string/byte output, full/blocking TX recovery
and public fixed-baud/ownership guards execute. Initial unlabelled10-case ASan/
UBSan run0.60s has9 clean cases and the correct capacity assertion failure below.
Only that regression is then labelled and rechecked0.05s, with strict1 known,
zero unexpected/diagnostics. Full55-suite gate1206 passes strict:1139 clean+67 known, zero unexpected/skipped.
F3 selected serial93/93 lines,30/32 branches,14/14 functions; one configuration
only, not full SDK/driver coverage.

Hardware registers/data-register effects/IRQ delivery, PCLK36MHz, GPIO and NVIC
are host boundaries. Actual RCC enable bits and original SDK offsets execute.
Shared serial_core_host.c contains only unused CORE callbacks that fail fast;
CORE stream/VFS logic remains original. Actual ARM/controller/physical timing,
other configurations, RS485 and full-driver behavior remain untested.

## 2026-10-25: RX free-space report includes the reserved slot

Correct driver_stm32f3_serial.capacity asserts RX_BUFFER_SIZE-1 free initially,
zero with31 queued bytes and one after consuming a byte. Original serialRxFree
returns RX_BUFFER_SIZE-BUFCOUNT while its producer treats next_head==tail as
full; for the declared32-byte ring the usable capacity is31. The initial32-vs31
assertion fails before further input. Paired rx_wrap control verifies actual31
bytes are retained and the next input is dropped, without a memory fault.

Proposed maintainer repair: subtract the reserved slot in serialRxFree, matching
the producer and CORE stream contract. Keep the correct assertions. Remove only
this exact WILL_FAIL/known_bug label and this entry after original source is fixed
and the case passes. No firmware edit, sanitizer suppression or broad allowance.
