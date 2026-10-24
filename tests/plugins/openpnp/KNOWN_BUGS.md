# Known defects

## M42 accepts a fractional digital output port - 2026-10-24

Source: grblHAL/Plugin_OpenPNP 76dbbc1420dd9773b1008a21f9d97b266f564bc9,
CORE b01f481072edecac33d5e40c25869359a5b3fa1f.

`plugin_openpnp.fractional_output_port` supplies M42 P0.5 S1 to the public
validator and requires rejection before any output. The validator instead
returns Status_OK: it checks P <= 255 and the uint8_t-converted port against
the count, without the integer check used by the plugin's input-port validator.
The same fractional value therefore addresses digital port0 if execution follows.

The correct rejection assertion fails under Windows Clang ASan/UBSan, with no
sanitizer diagnostic. One named WILL_FAIL/known_bug property retains the
regression. Proposed upstream fix: validate that output P is an integer in range
before converting it, preserving valid port commands. No production source or
assertion was changed. Retain the test and remove its property and this entry
when upstream fixes the validation and the suite/strict summary pass.
