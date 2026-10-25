# STM32F1 serial host scope - batch46

Twelve original-source cases compile serial.c with unchanged main/driver/generic
map and ST F103xB HAL/CMSIS headers plus actual CORE stream/passthrough/VFS/
formatting. Driverc22362352f6abeea94897bb0346ae8042cdf3210 and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f. Primary USART1 is GPIOA9/10. Original
separate AF push-pull TX and input RX configuration calls are captured; no F3/F4
register/API aliases or source conversions. Supported baud/count/write_n/mute
callbacks execute, and no unavailable parity callback is invented.

Eleven ordinary ASan/UBSan cases pass in the initial12-case run0.78s: GPIO/clock/
IRQ requests, RX FIFO/full/wrap/cancel, realtime, actual CORE tool-ACK lifecycle,
binary/queued/flush/full/blocking TX recovery, RX mute preserving TX, public
ownership and baud updates. The remaining case correctly fails the count below.
Only that exact case gets WILL_FAIL/known_bug; no sanitizer allowance. Full55-suite gate1206 passes strict:1139 clean+67 known, zero unexpected/skipped.
F1 selected serial115/119 lines,33/40 branches,19/20 functions; serialRxCount and
other configurations remain unexecuted. This is not full SDK/driver coverage.

Register/IRQ/data-register side effects, GPIO/NVIC and PCLK36/72MHz are host
models; original native SDK addresses/RCC writes and CORE stream/VFS execute.
Shared serial_core_host.c only contains unused controller callbacks that fail
fast. No source edit or full firmware/controller/ARM/hardware claim. Other ports/
MCUs, RS485/remap, errors/timing and pending-baud queue semantics remain open.

## 2026-10-25: RX free-space report includes the reserved slot

Correct driver_stm32f1_serial.capacity asserts31 free for an empty32-byte ring,
zero at31 queued and one after a read. Original serialRxFree returns
RX_BUFFER_SIZE-BUFCOUNT while next_head==tail denotes producer full. Initial
32-vs31 assertion fails before further input. The paired normal rx_wrap case
verifies31 retained bytes and one dropped input, with no memory fault.

Proposed maintainer repair: subtract the reserved slot in serialRxFree. Preserve
the correct assertions. After source repair, remove only this exact WILL_FAIL/
known_bug label and dated entry once the case passes. No production edits,
sanitizer suppression, private-state changes or broad allowance are included.
