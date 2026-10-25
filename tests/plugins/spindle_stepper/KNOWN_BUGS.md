# Known defects and scope

Fifteen selected polling/timer-boundary cases pass without known runtime exceptions. Original
Plugins_spindle8a3ae47f5a218834da9c742424c3dd22c5629fdb and
COREb01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged.

Original plugin and actual CORE stepper2/spindle registry execute on four-axis
configuration, A motor200 steps/revolution,600RPM maximum and configured
acceleration. Driver callbacks capture actual engine-emitted axis/direction
pulse masks, motor claims and enable state. Clock advances10ms per read, so it
undersamples some requested step periods: physical rate/timing is not validated.
RPM assertions check engine-calculated requested periods, not wall-time output.
Do not infer actual hardware timer accuracy, step pulse waveform or motor speed.

Bounded polling and delayed-stop callback dispatch allow public start/stop,
reversal, counters/speed, enable-mask retention, axis claims, rotary setting
conversion and soft reset scenarios. No private motor/profile mutation or
mocked st2 algorithm. Settings save is observed at the platform boundary;
no EEPROM or full firmware/parser integration is claimed. Local driver.h only
forwards the real grbl/hal.h layout used by original plugin includes.

Timer32 and16-bit fallback callbacks execute actual CORE engine; rejected
timer allocation falls back to polling or warns with no clock. Stop halts timer
callbacks, restart after stop reverses direction. Integer/fractional steps/rev
position sync uses captured pulse totals and observed planner sync/coordinate
conversion boundaries. This is not real planner/IRQ timing or electrical output.

Live timer-backed direction reversal needs independently delivered asynchronous
interrupts during the plugin's blocking stop loop; the synchronous event model
does not exercise that path. Fractional rotary mode, counter reset/angle,
units/descriptions and native controller jobs remain open. Unused settings
metadata helpers fail immediately; no silent fallback. No source edits, ABI casts or sanitizer allowances.
