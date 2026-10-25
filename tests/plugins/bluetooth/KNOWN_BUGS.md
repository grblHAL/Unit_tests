# Bluetooth HC-05 source scope and regressions

Original source3fc40665af6d49250f09fec665ec267a988ee148 and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged. The suite compiles
actual HC-05 plugin plus CORE stream registry/selection, I/O registration and
EEPROM/CRC. UART transport, IRQ provider, module replies and ticks are simulated.
No HC-05 hardware/radio link or full protocol execution is established.

## 2026-10-24: default highest STATE pin is rejected during settings load

`plugin_bluetooth.default_state_pin` retains the correct assertion that erased
settings with a capable free STATE input start normal AT configuration. Factory
restore selects the highest free pin (aux1 in this two-pin fixture). In
hc05_settings_load, `state_port >= d_in.port_max` changes it to unassigned because
CORE defines port_max as the highest valid index, not a count. Therefore no setup
or AT commands run. This also disables a manually saved highest-numbered pin.
The lower-pin controls explicitly select aux0 through the registered setting
before saving/loading; they pass configuration and stream switching.

Proposed firmware repair: reject only indexes greater than port_max, consistent
with CORE _get_value/_claim. Firmware is not changed here. After a maintainer
fix, remove only this test's WILL_FAIL/known_bug and resolved section, then rerun
fresh source-matched sanitizer/coverage checks.

## 2026-10-24: connection already high at boot reports disconnected

`plugin_bluetooth.initially_connected` loads enabled settings using a valid lower
STATE pin and boots with its input high. Public startup correctly selects the
Bluetooth stream and emits the welcome message, but `hal.stream.is_connected()`
is false. hc05_setup stores the input into a local `is_connected` variable and
never updates the file-static `connected` used by that callback. Only a later
IRQ edge updates it. Paired low-at-boot then connect/disconnect IRQ controls pass.

Proposed firmware repair: initialize the connection predicate from the startup
input as well as later IRQ edges. Remove the exact WILL_FAIL/known_bug and this
section after the original implementation is fixed; retain the correct assertion.

Configuration tests cover all four AT command stages, rejection, timeout, device
name, baud/handler restoration, manual enable, missing dependencies, claimed-pin
rejection, port settings, reports and fresh-process EEPROM restart. Getter checks
mask only the defined enable bit. Restore clears that bit but leaves reserved
bits from invalid storage; the wider Format_Bool value contract is a TODO rather
than a claimed new defect. Shared MPG mode and IRQ-provider failure notification
remain untested; neither serial streams nor CORE sources are replaced or patched.
Original warnings stay visible under -Wno-error; fixtures remain strict. No new
sanitizer allowance or whole-plugin/hardware coverage claim.
