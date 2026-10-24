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

## PCA9654E descriptor callbacks use bank-offset pin numbers as device bits - 2026-10-25

Source: Plugins_misc265711922037cab6b6e47a9560ef11da3a6e5f83,
CORE b01f481072edecac33d5e40c25869359a5b3fa1f.

CORE ioports_add_digital assigns out.pin_base from preceding output banks.
PCA get_pin_info adds that base to its returned descriptor's pin number. Both
`digital_out_state` and `digital_out_ll` subsequently use that adjusted pin as
a local eight-bit register bit, despite descriptor id remaining device-local.
The bank's digital_out callback uses original aux_out entries and works normally.

Two exact correct regressions model preceding two-output registration at the
public ioports_add_digital boundary, following CORE's assignment contract:
- bank_offset_read: ordinary output0 writes device bit0, but its descriptor
  returns0 rather than1 because it reads bit2.
- bank_offset_write: descriptor0 writes device bit2 (4) rather than bit0 (1).

Only valid port0 is used; shifts are bounded to bit2. No invalid IDs, private
state injection, production edit or sanitizer allowance. Zero-base descriptor
controls pass. Registration is modeled here, not full CORE aggregation execution.

Proposed upstream repair: resolve the local pin using descriptor id in callback
implementations, retaining global descriptor metadata. Remove these two exact
WILL_FAIL/known_bug entries only after the unchanged correct assertions pass,
rerun strict classification and retain zero/nonzero-base controls.

## MCP23017 calls opposite-direction edge handlers - 2026-10-25

Source: Plugins_misc265711922037cab6b6e47a9560ef11da3a6e5f83,
CORE b01f481072edecac33d5e40c25869359a5b3fa1f.

The registered IRQ handler queues original mcp23017_irq, which reads INTF/INTCAP.
For rising/falling-only registrations it correctly clears an opposite-level flag,
but then calls the saved callback unconditionally inside the original flagged
branch. The filtered event is therefore still delivered to consumers.

Four correct irq_rising/irq_falling cases cover both mixed ENABLE1 (8-bit) and
input-only ENABLE3 (16-bit). Each first accepts a matching event, then delivers
an opposite captured level for the same enabled pin and asserts the callback
count remains1. Actual count2 fails at the final correct assertion. Distinct
routing/empty-flag/detach controls pass. These use only public registration and
the driver's captured IRQ callback plus bounded deferred execution, with valid
flag bits. No private state or invalid indexes are injected.

Retain the four exact WILL_FAIL/known_bug labels without sanitizer allowances.
Proposed repair: invoke a callback only when its flag remains set after direction
filtering, preserving event-bit/wait handling and callback user-port mapping.
After repair, retain assertions, remove those four exact properties and this
entry, then rerun both configurations plus strict reporting. No source edits here.

## BLTouch D validation checks the S value for integer format - 2026-10-25

Source Plugins_misc265711922037cab6b6e47a9560ef11da3a6e5f83, CORE b01f481.
The Probe_Deploy D branch calls isintf(values.s) before checking values.d range.
D0.5 with absent S therefore returns Status_OK instead of BadNumberFormat.
`plugins_misc.bltouch_fractional_d` retains the correct rejection assertion under
one exact WILL_FAIL/known_bug label; invalid input is never executed. No sanitizer
allowance. Fix the checked value upstream, then retain the test and remove its
exact property and this entry. No production change here.

S/D/H options work when the host reproduces CORE's consumed-word restoration
(gcode.c2349-2355/4494). Cleared validation flags alone are not execution flags;
do not classify a missing-restoration fixture failure as a plugin defect.
