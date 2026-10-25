# Known defects and test scope

No runtime defect is classified for this host-tested flash-copy configuration.
Original driver source 2f5bc4a06ecea3b1f78c1644623810f9b6416376 is unchanged.

The original flash.c executes against RAM-backed SDK flash calls. The host
preinclude intentionally satisfies the board driver.h guard while providing the
real CORE HAL types and only the SDK calls used by flash.c. SDK declarations,
XIP address mapping, IRQ operations and flash are simulations; this is not a
Pico SDK firmware build, physical flash, interrupt timing or multicore proof.
The source's fixed 2016KiB target offset is checked, not replaced in production.

Cases check erased reads, copied bytes, unchanged-write avoidance, padded page
rounding and readback-failure returns. The rounding case deliberately supplies a
512-byte source for500 configured bytes, respecting the SDK page transfer size;
it does not prove arbitrary unpadded caller buffers safe. Single-sector storage
sizes are exercised. Existing source notes that multicore synchronization is
required when both cores run; no test claims to resolve that hardware constraint.
Fixtures and this production source compile with strict warnings. No sanitizer
allowances or full-driver coverage claims.
