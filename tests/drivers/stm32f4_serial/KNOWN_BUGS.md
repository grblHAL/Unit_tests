# STM32F4 serial host scope - batch44

Twenty-one original-source cases compile serial.c with unchanged driver.h/main.h,
generic board map, original ST HAL/CMSIS device headers and current pinned CORE
stream/passthrough/VFS/formatting modules. Driver revision a6318ac92f079f49fab91687530f832997396edc;
CORE b01f481072edecac33d5e40c25869359a5b3fa1f. STM32F407xx generic-map primary
USART1 at GPIOA9/10 is selected through original board configuration. The
three-stream profile adds USART3 at GPIOB10/11 and USART6 at GPIOC6/7; those pins
are free in the selected generic map. This does not establish a full board build.

Normal registration/claim, GPIO/clock/IRQ requests, RX FIFO/full/wrap/cancel,
realtime dispatch, tool-ACK suspend/resume, binary/queued/flush TX, full-output
abort/recovery, blocking progress, parity/baud updates, RX-disable TX preservation
and release/reclaim execute. Native register offsets are mapped host RAM; GPIO
configuration/NVIC/clock-frequency and IRQ delivery are explicit host boundaries.
Data-register RX-read/TX-completion side effects are applied only at delivery
boundaries. No internal ring pointers, status tables or production state are set.

All21 pass the cumulative Windows Clang ASan/UBSan and strict gate, with no known
assertions or diagnostic allowances. SDK/header declarations are original and
included as system headers; original serial source only permits unused callback
arguments. Fixture code stays -Werror. A Windows-only ERROR macro is undefined
after loading Windows APIs so the original CMSIS enum keeps its native name.
No obsolete CORE API/type aliases, source copies, ARM instruction replacement or
firmware edit is used. Unsupported CORE paths fail fast in the host provider.

Primary-only and three-stream1/3/6 profiles are tested. Simultaneous traffic,
independent full/wrap/cancel, handlers, format/baud, RX mute/TX preservation,
release/reclaim and third-stream CORE suspend execute. Other original port mappings,
RS485/bit-band direction, physical errors/timing/IRQ races, full
controller jobs, ARM firmware linking and actual hardware remain untested.
The host native-width build is separate from existing32-bit flash tests.
First selected-source coverage324/345 lines93.9%,104/122 branches85.2%,53/57
functions. Unexecuted functions: serial1Write, serial1SuspendInput, serial2RxCancel
and serial2Write. Coverage includes only compiled serial.c configurations, not
SDK/whole-driver source. Full52-suite gate passes1159 cases; no full-driver claim.

## Local follow-up - batch45

Two ordinary cases add all-stream binary writes and secondary tool-ACK suspend
while the third stream is cancelled/reused. Together they execute the four
previously unexecuted public callback functions; no new coverage count is claimed
until a fresh report. All23 affected F4 sanitizer/strict cases pass1.54s after
extracting unchanged unused CORE fail-fast callbacks to serial_core_host.c.
Broader gate/updated coverage are pending; baseline report remains batch44.

## Fresh follow-up measurement - batch45

Both new cases are in the full53-suite1184 gate. F4 serial23 clean; updated
same-source/config coverage341/345 lines and108/122 branches,57/57 functions:
+17 lines/+4 branch outcomes from44. Selected missing lines are driver claim-guard
returns(standard CORE open filters claimed providers first) and third RX-disable.
No private flags are changed or guard lines excluded; broader configurations and
real hardware remain unvalidated.
