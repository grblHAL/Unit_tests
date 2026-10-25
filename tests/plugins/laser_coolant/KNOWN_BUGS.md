# Known defects and scope

Eleven selected original coolant cases pass with no runtime allowances. Source
Plugins_laser26934c6c9607e0b5ba4a711516a60d4657bf142c and
COREb01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged.

Real CORE ioports/crossbar claims digital/analog input providers. Pin advertises
both Change and Falling modes explicitly (separate capability bits). Original
EEPROM/CRC stores valid default settings via plugin restore before load; this
does not validate erased/corrupted storage recovery. Original restore clears
timing/temperature fields but does not initialize port fields after failed reads;
review intended port-default contract before defining a default-recovery test.

Tests cover confirmed startup, timeout with flood off/mist preserved, delayed
shutoff, cancellation, reset immediate shutoff, lost-input alarm while on,
ignored loss while off/pending shutdown, claimed-input provider failure, options/
realtime hook chaining and virtual sensor callbacks. Virtual parameter registry
is an observed boundary storing original callbacks, not actual NGC parsing.
Scheduler explicitly dispatches registered delayed callback, not wall-clock time.

Temperature reporting and automatic alarm flag can_monitor stays false in this
source; temperature features are documented WIP upstream. No private flag is set
and no whole thermal-protection success or confirmed defect allowance is claimed.
No analog-bank-only configuration is executed without a valid port contract.
Native parser/controller jobs, actual coolant flow/electrical IRQs, thermal
response, driver timing and physical safety remain unverified.
