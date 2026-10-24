# Known defects

Source: grblHAL/Plugin_encoder b3e31df20edd9e03a7535a1df9ef9a0f4445a24b,
CORE b01f481072edecac33d5e40c25869359a5b3fa1f. Confirmed 2026-10-24 with
Windows Clang ASan/UBSan, using actual CORE encoder registration/enumeration
and actual EEPROM-backed settings storage. No production sources were edited.

## Low rapid transitions enqueue percentages instead of realtime commands

`plugin_encoder.rapid_extra_low` starts at the valid25% rapid state and rotates
the registered universal encoder downward. It observes byte5; the correct
request is CMD_OVERRIDE_RAPID_EXTRA_LOW (0x98). `rapid_return_low` starts at
valid5% and rotates upward, observing byte25 instead of CMD_OVERRIDE_RAPID_LOW
(0x97). Source encoder.c455/460 sends RAPID_OVERRIDE_* values instead of their
CMD_OVERRIDE_RAPID_* counterparts. Medium and spindle controls pass.

Keep both correct command-byte assertions. Each has named WILL_FAIL/known_bug
properties. Remove those properties and this entry after the upstream command
mapping fix passes the suite and strict summary.

## Encoder enumeration stops after the first candidate

CORE encoders_enumerate() stops when its callback returns true. The plugin's
encoder_claim() always returns true. `multiple_encoders` registers two normal
encoders through the real CORE API and observes only one claim; `skip_spindle`
registers a spindle-capable encoder before an eligible normal encoder and
observes zero claims. Neither test calls the private callback or forces a
second claim. Both correct registration/ownership assertions remain named
WILL_FAIL/known_bug regressions.

An upstream fix must continue enumeration appropriately AND use the current
per-encoder settings slot: source currently assigns through global enc->settings
before binding enc[n_encoder]. Do not accept a different crash after a partial
fix as reproduction of the current assertion failure; unknown sanitizer output
still fails strict classification. Keep tests and remove their individual
properties/this entry only when actual correct behavior passes.

## Host compiler portability warnings

The original source has visible format/enum/sign/unused diagnostics. Its source
file follows the main harness's production-code -Wno-error policy; host fixtures
remain -Werror. Warnings are retained in build logs, not hidden or fixed in source.
A passing host run is not a clean-Werror compiler claim. No sanitizer diagnostic
allowance is added for this suite.

MPG modes are not force-enabled: registered radio choices expose modes0-3 and
CORE rejects higher choices. A supported persisted/migration route for modes4+
has not been established. Velocity propagation and live mode rebinding remain
source-review questions in COMPONENT_TODO, not fabricated startup tests.
