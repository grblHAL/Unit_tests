# Known defects and scope

Nine selected clone cases pass without runtime defect allowances. Original
Plugins_spindle8a3ae47f5a218834da9c742424c3dd22c5629fdb and
COREb01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged.

Driver PWM is initialized with real CORE spindle_precompute_pwm_values before
registration, and its configuration callback follows that public API. The
clone plugin owns its own conversion context as supplied by original code.
This is distinct from incompatible pwm.c activation: no missing plugin context
is fabricated here. Real CORE startup initialization is queued until after
original EEPROM settings load. Default secondary maximum is2000RPM, primary
10000RPM, both1000Hz at1MHz modeled timer clock.

Primary on maps to physical direction; clone on maps to physical enable. Tests
capture these driver-boundary states and real CORE computed PWM counts, stop
on selection change, settings conversion updates and rejected initialization
providers. No actual electrical pins, PWM timer/laser waveform, firmware link,
full parser/controller or machine safety behavior is validated.

The initial host assumed startup tasks only carried warnings; CORE schedules
secondary PWM initialization too. Bounded startup queue repairs that fixture
contract; all eight rerun clean/strict; the added laser-mode case also passes focused. No production edit, private context
injection or sanitizer allowance. Additional laser-mode variants, in-process metadata
refresh after range changes, target drivers and hardware remain open.

Laser-mode primary routing now checks direction capability, repeated selection
without rewrapping hooks and clone capability/output isolation. This checks
callback semantics only, not physical laser safety or electrical timing.
