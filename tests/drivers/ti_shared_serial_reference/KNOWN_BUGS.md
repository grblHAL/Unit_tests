# Explicit TI shared serial reference scope

Seventeen registered cases execute original TI_SimpleLink_shared/base/serial.c at
6adcc848946fe69075f6ed062afa31f11c5a4c97 with fixed CORE070f80cc5c0d095ff63d5980795b5a15c5bb0202
and TivaWare header mirrorc23bf8ba7a82b20421aa04d4df3f77501c5883ea. The current
CORE b01f481 syntax check rejects the unchanged historical callbacks. No type
alias, source/header edit or automatic fallback conceals that incompatibility.
Fixed reference results stay outside the42 current-compatible suite totals.

This is the shared module's TM4C1294/Tiva primary UART0 and optional UART7
configuration with actual
original driver/board/SDK declarations. It is not the archived TM4C1294 parent's
shared3e7873 pin or an MSP432E SDK/parent firmware build. The latter parent pins
this6adcc candidate but uses different SDK headers. Original serial.h's fixed
primary/backchannel is retained. UART7 is RX-only and its tests explicitly call
the public disable_rx(false) API; startup RX-enable intent remains unclassified.
RTS and whole board/NVS remain.

The existing TM4C UART SDK fixture is reused with explicit historical protocol
signature and UART-base metadata branches, preserving strict callbacks in both
builds. Fifteen cases capture registration; public serialInit rejects unsupported baud and
duplicate claim. Two dedicated signed/unsigned-char cases instead link original
legacy CORE stream.c and execute real registration/open/connect/suspend/restore.
The unsigned control passes; the signed portability regression is below. The
capture-only suspend boundary still fails fast if reached. RX FIFO/wrap/cancel, realtime handling at full capacity, queued TX,
backpressure/recovery and RX mute with pending TX execute through registered IRQ
and public stream callbacks. No private ring state, opaque handles or source
functions are copied. Default RX1024/TX512 sizes are used unchanged.

The delivered nine-case checkpoint passed cleanly. The affected17-case reference
gate now has15 clean +2 exact known assertions (signed-char ACK and secondary
metadata), with no unexpected failure or diagnostic allowance. Four secondary
behavior controls pass.
Last delivered batch23 primary-only coverage92/108 lines,31/42 branches and
10/15 functions is historical; no updated dual-port percentage is claimed. Native hardware UART/GPIO/clock/FIFO calls are simulated;
actual electrical timing, SDK linking, CPU IRQ scheduling and parent startup are
not established. Preserve SDK-only dependencies as nonselectable sources.

# Signed-character tool acknowledgement - 2026-10-25

stream_suspend_signed retains the correct one-acknowledgement assertion. Original
legacy CORE stream.c await_toolchange_ack takes char and compares c to
CMD_TOOL_ACK0xA3. Under explicit -fsigned-char that byte becomes negative, so the
comparison never matches:0 acknowledgements and input remains suspended. The
identical -funsigned-char case accepts the byte, reads post-ack input and restores
the original queued line through actual CORE backup/restore. No function cast or
type alias changes the original API. This is a compiler-character portability
regression, not evidence about an unspecified MCU compiler default or hardware.

A firmware fix must preserve incoming byte semantics when comparing the command;
retain the signed test and paired unsigned control. Remove only the exact signed
WILL_FAIL/known_bug and this entry once the correct assertion passes against
repaired original source. No diagnostic allowance or CORE edit here. Full protocol,
actual task scheduling and hardware delivery remain boundaries.

# Secondary descriptor instance - 2026-10-25

secondary_metadata retains the correct instance1 assertion. The original serial[]
registry advertises instance1 and claims serial2Init, but serial2Init's static
io_stream_t omits .instance, leaving0. Registry instance=1 and returned instance=0
are observed without indexing private arrays or forcing a memory failure. Correct
assertion is retained under one exact WILL_FAIL/known_bug. This is descriptor
identity evidence, not an observed hardware routing incident.

Paired RX-only capability, separate FIFO/flush/cancel/wrap, full-ring realtime,
handler replacement/public enqueue and interrupt mute/re-enable controls execute
through UART7's registered SDK IRQ callback. The bounded fixture keeps per-UART
mask/input/handler state and rejects unsupported secondary TX. Original SDK pin,
clock and register constants are retained. No test injects a disabled IRQ.

Proposed source repair: give the secondary descriptor instance1 to match its
registered property. Remove only the exact secondary_metadata expectation and
this entry when the unchanged correct assertion passes against repaired source.
No firmware fix or sanitizer exception here. Initial interrupt enablement requires
its own contract review; these controls explicitly request enable through public
API rather than invent an automatic-startup assertion.
