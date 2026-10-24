# Known assertions - 2026-10-24

FlexGPIO source bc8dab40162b49718179bffe973c4533fc73436f, original flexgpio.c.
- a3_edge_callbacks: disabling a registered IRQ with IRQ_Mode_None/NULL clears the
  callback but returns false, so callers cannot observe successful deconfiguration.
  Correct true-result assertion remains. Other rising/falling/change controls pass.
- a3_pull_mode_rejection: PullMode_UpDown is outside the advertised pull-up capability;
  digital_in_cfg skips the unsupported operation but still returns true. Correct
  rejection assertion remains. Supported input configuration controls pass.
Remove only each resolved exact WILL_FAIL/known_bug label and its entry after repair.

# Scoped Clang callback diagnostics

Four cases invoke original digital_in_cfg/digital_out_cfg through public xbar.config.
CORE declares its parameter as the GNU transparent union xbar_cfg_ptr_t; the plugin
registers a specific member-pointer signature. Clang accepts that extension but its
function-type sanitizer reports the differing signatures at the call. This is
recorded separately from functional defects; it does not establish an exploitable
failure or a board malfunction. The exact test/file/line/function/type messages are
listed in known_sanitizer_diagnostics.json. Three assertions pass with diagnostics;
the pull-mode regression reproduces both an assertion failure and the diagnostic,
counted once. No sanitizer is disabled. Changed/missing/unrelated diagnostics make
the strict report fail. If callback/API compatibility changes, remove/update only
its resolved exact manifest entry and known_sanitizer_bug label after review.

# Scope

Seventeen original-source cases use real CORE driver-option/type declarations for
three-axis operation and a six-axis registration control. Public registered digital
bank descriptors are captured; full CORE ioports remapping/claim aggregation is not
executed. Host I2C packets, task delivery, MCU IRQ/claim callbacks, persistence and
alarm requests are explicit simulations. Public pin metadata/callbacks configure
supported operations; private state is untouched. Tests cover wire byte order,
inversion, input snapshots/edges/waits, failure alarms and pin enumeration. Original
assignment-condition and const-field initialization warnings remain visible under
narrow source-only warning rules; fixtures stay strict. Full-controller integration,
multiple port-bank offsets, no-IRQ configuration and physical expander timing remain.
