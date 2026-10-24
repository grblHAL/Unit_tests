# SAM3X8E serial scope and regressions

Original driver2321092b02cbbdecf2eba2b168a74b085e573418, CORE
b01f481072edecac33d5e40c25869359a5b3fa1f and Arduino SAM SDK
790ff2c852bf159787a9966bddee4d9f55352d15 remain unchanged. Original serial.c,
serial.h/driver.h/generic map, actual Arduino/device register headers and real
CORE stream registration/claim/status/suspend logic are compiled. Clocks, CPU
NVIC and registered IRQ delivery are host callbacks. Mapped peripheral memory
uses real SDK offsets; write-one interrupt enable/disable commands update the
simulated mask at explicit hardware boundaries. No private ring state is changed.

## 2026-10-24: disable_rx does not disable receive interrupts

Four correct cases cover primary/secondary under primary UART(-1) and USART1
configurations. disable_rx(true) writes IER with bits cleared, but IER enables
one bits; it cannot disable existing interrupts. IDR is the required disable
command. The provider applies SDK IER/IDR semantics, so RXRDY remains enabled and
the correct mask assertion fails. Re-enable and normal RX/IRQ controls pass.
Proposed firmware repair: write the RX/error bits to IDR on disable, keep IER on
enable. Remove the four exact WILL_FAIL/known_bug labels only after source repair.

## 2026-10-24: secondary enqueue routes to primary and has wrong signature

Both secondary_realtime cases register different public handlers for each stream.
The secondary enqueue callback calls enqueue_realtime_command (primary), rather
than enqueue_realtime_command2. The correct secondary-handler assertion remains
under exact WILL_FAIL/known_bug. Actual received secondary IRQ bytes correctly
reach the secondary handler in the paired controls.

The callback also takes char while CORE's callback type takes uint8_t. Clang
rejects that initializer by default; only the original source gets a narrow
-Wno-error=incompatible-function-pointer-types rule so its warning remains visible.
The typed public call produces one recovering function-type UBSan diagnostic per
case. Exact caller file/line/function/type manifest entries and Clang-sanitizer
labels require that diagnostic; unrelated or missing diagnostics fail reporting.
No function cast or production/CORE type alias masks the mismatch. These cases
are known assertion regressions with diagnostics, not clean assertion passes.

Proposed source repair: use uint8_t and the secondary handler. If only one part
is fixed, reporting must fail and prompt appropriate label/manifest cleanup;
retain the correct assertion. GCC/coverage do not require Clang's function check.

## 2026-10-24: primary USART pin mux retains TX peripheral-B selection

p1_pinmux starts with external PIO mux bits set, then claims the UART through
CORE. The secondary USART clears its RX/TX selection while retaining unrelated
pins. Primary USART1 uses `&= ~(1<<RX) | (1<<TX)`, retaining TX's B-selection bit.
The correct peripheral-A assertion fails. Proposed repair: complement the OR of
both masks, as the secondary implementation does. Retain the exact expected
regression until fixed; no private driver state is injected.

Other cases cover FIFO/wrap/full/cancel, realtime IRQ handling, direct/queued/
blocked TX with recovery, baud/parity, claim/release/reclaim, secondary flush and
real CORE tool-ACK suspend/restore. Buffer size32 is an explicit supported
power-of-two test configuration. Primary ports-1/1 and secondary USART2 are tested.
SERIAL_PORT0 source preprocessing appears to omit its status entry while getters
index instances; no memory-safety failure is reproduced or compatible alias added.
Other port/format options, real ISR scheduling/baud timing, full controller jobs
and Arduino/ARM firmware builds remain untested. Unused CORE paths fail fast.

Windows-only host declarations avoid unused SDK/Windows GetTickCount/Sleep name
collisions. Actual SDK headers remain original. All fixture code stays -Werror;
original source warnings remain visible. No board/hardware or whole-driver
coverage claim is made.
