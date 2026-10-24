# Explicit legacy reference scope

Candidate grblHAL/PSoC5 c9d721259783ca578ee1b0c3f6111839610c26a4 pins CORE
070f80cc5c0d095ff63d5980795b5a15c5bb0202 in its grbl gitlink. README ends support
at CORE20250518. This suite explicitly selects that fixed original dependency,
not the current CORE checkout. Current CORE b01f481 rejects unchanged serial.c
read/write/realtime callback signatures in the recorded syntax check. No aliases,
function casts, header guards or production sources are changed to conceal that.
Reference results never count toward current-compatible suite/case totals.

Eight registered cases execute original serial.c/serial.h with actual legacy CORE types.
They cover normal initialization, ordered RX/realtime filtering, full-ring realtime
handling, repeated wrap, flush/cancel, string/binary TX and realtime-handler
replacement/restoration. The added lifecycle case passes focused ASan/UBSan and
strict checks; the prior seven-case reference checkpoint remains separate. Generated project.h is
absent from the repository; the test's project.h declares only the UART symbols
called by serial.c and binds them to bounded host FIFO/TX/IRQ callbacks. These are
explicit declaration-only hardware boundaries, not Cypress SDK headers or a
PSoC Creator/firmware build. UART_GetChar's0 terminator is respected; arbitrary
binary RX, real interrupt scheduling and UDB hardware are not established.
CORE stream_connected is a host predicate; suspend fails fast if reached. Actual
CORE stream/suspend, original board driver.c/NVS and physical UART remain untested.
Original CORE dependency/forwarder headers are system includes, preserving strict
fixture warnings without editing the legacy header's unused ffs definition.

# Known free-capacity assertion - 2026-10-25

free_capacity retains the correct empty-ring free space RX_BUFFER_SIZE-1. The
original ring reserves one slot to distinguish full/empty, but serialRxFree
returns RX_BUFFER_SIZE-serialRxCount, reporting32 for a31-byte usable ring here.
The separate normal capacity test accepts31 bytes, drops the next normal byte,
and still routes realtime input. This is a count/reporting defect; no unsafe
memory reproduction or sanitizer diagnostic allowance.

Proposed repair: subtract the reserved slot when reporting RX free capacity.
Remove only the exact free_capacity WILL_FAIL/known_bug label and this entry
when the correct assertion passes against original repaired source. No fix here.
