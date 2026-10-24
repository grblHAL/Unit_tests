# Known defects

## MCP4725 reports successful output after failed I2C send - 2026-10-25

Source: Plugins_misc265711922037cab6b6e47a9560ef11da3a6e5f83,
CORE b01f481072edecac33d5e40c25869359a5b3fa1f.

`mcp4725_analog_out` stores the result of i2c_send in `ok`, and only updates
`a_out` when that send succeeds. Its final return instead checks the port range,
so a valid-port hardware transfer failure returns true. CORE ioports.h documents
analog_out_ptr as returning false on failure.

`plugins_misc.dac_send_failure` uses the registered analog_out callback: write100,
fail write200, verify retained100, recover write300, then assert the failed
transaction returned false. Retain that correct assertion under its exact
WILL_FAIL/known_bug label. No sanitizer allowance or production edits.

Proposed upstream repair: return the accumulated `ok` result, retaining invalid
port rejection and cached-value update only on successful send. Once repaired,
remove only this test's WILL_FAIL/known_bug property and this entry, rerun the
suite and strict classification, and retain all behavior assertions.
