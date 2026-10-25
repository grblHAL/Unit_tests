# Known defects and scope

Original laser source 26934c6c9607e0b5ba4a711516a60d4657bf142c, CORE
b01f481072edecac33d5e40c25869359a5b3fa1f. No production source changes.

## Zero PWM update still requests a pulse

plugin_laser_ppi.pwm_zero registers/selects a valid laser through real CORE
spindle APIs, enables software PPI, applies positive PWM then zero PWM. The
original ppiUpdatePWM() always calls pulse_on while the software stepper hook is
active, including zero PWM. The correct assertion requires no additional pulse
callback on zero. It is named WILL_FAIL/known_bug. The RPM-off control suppresses
pulses correctly; normal software spacing and shutdown controls pass.

This proves the unexpected driver callback in a simulation, not emitted optical
energy on physical hardware. Proposed source repair: gate the pulse request on
an active positive output and retain the zero-output shutdown path. Keep the
assertion and remove the named property/entry after both controls pass. There is
no sanitizer allowance.

## Host boundaries

Actual CORE spindle registration/selection is compiled. Step events, pulse/PWM/
RPM driver callbacks and gc_laser_ppi_enable are simulated public boundaries.
The latter records requests and can model hardware delegation; it is not a full
CORE parser or planner test. Spacing checks tolerate one step of float threshold
quantization while requiring the pulse total and width. No FPU IRQ timing,
physical laser or complete laser-repository validation is claimed. Original
source warnings remain visible under -Wno-error; fixture warnings stay strict.
Coolant, overdrive, alternate/spindle-switch configurations remain inventory work.
