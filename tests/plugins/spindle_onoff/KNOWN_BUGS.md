# Known defects and scope

No runtime defects currently classified in the12 selected on/off and direction
cases. Source Plugins_spindle8a3ae47f5a218834da9c742424c3dd22c5629fdb and
COREb01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged.

Original onoff.c executes with actual CORE spindle registration/selection,
ioports/crossbar mapping/claims and EEPROM/CRC settings. Driver pin callbacks
capture physical port writes; no real motor, electrical timing or complete
controller/parser execution is claimed. Startup warning tasks execute at the
host scheduler boundary; scheduler deferral/order is not under test here.
Unsupported controller helpers fail immediately if entered.

Source warnings remain visible/nonfatal only for original firmware files;
fixture code is-Werror. The default set_port switch warning is source-only:
registered setting IDs exercise valid cases. No arbitrary setting IDs or
uninitialized-value runtime reproduction. No sanitizer diagnostic allowance.
PWM/offset/stepper/selection variants, target firmware builds and hardware
remain unverified. In-process save/load checks use the original EEPROM backend;
separate-process restart is not yet exercised by this suite.
