# Explicit TI shared serial reference scope

Nine cases execute original TI_SimpleLink_shared/base/serial.c at
6adcc848946fe69075f6ed062afa31f11c5a4c97 with fixed CORE070f80cc5c0d095ff63d5980795b5a15c5bb0202
and TivaWare header mirrorc23bf8ba7a82b20421aa04d4df3f77501c5883ea. The current
CORE b01f481 syntax check rejects the unchanged historical callbacks. No type
alias, source/header edit or automatic fallback conceals that incompatibility.
Fixed reference results stay outside the42 current-compatible suite totals.

This is the shared module's TM4C1294/Tiva primary UART0 configuration with actual
original driver/board/SDK declarations. It is not the archived TM4C1294 parent's
shared3e7873 pin or an MSP432E SDK/parent firmware build. The latter parent pins
this6adcc candidate but uses different SDK headers. Original serial.h's fixed
primary/backchannel is retained. Secondary UART7, RTS and whole board/NVS remain.

The existing TM4C UART SDK fixture is reused with explicit historical protocol
signature and UART-base metadata branches, preserving strict callbacks in both
builds. Registration is captured, not actual CORE stream/claim execution; public
serialInit rejects unsupported baud and duplicate claim. Suspension fails fast if
reached. RX FIFO/wrap/cancel, realtime handling at full capacity, queued TX,
backpressure/recovery and RX mute with pending TX execute through registered IRQ
and public stream callbacks. No private ring state, opaque handles or source
functions are copied. Default RX1024/TX512 sizes are used unchanged.

All9 assertions pass with no expected failures or sanitizer diagnostic allowance.
Fresh selected-source coverage92/108 lines,31/42 branches,10/15 functions describes
only this configuration. Native hardware UART/GPIO/clock/FIFO calls are simulated;
actual electrical timing, SDK linking, CPU IRQ scheduling and parent startup are
not established. Preserve SDK-only dependencies as nonselectable sources.
