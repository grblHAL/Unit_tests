# PWM spindle activation proposals

Three scenarios in two direction variants remain unregistered after initial
activation failed at current original-source contract. They are not passing
runtime tests or coverage. Keep assertions; no production fix or fixture-side
context injection. Restore them to the active suite only after compatible
original plugin/CORE source establishes the PWM context contract.

Original Plugins_spindle pwm.c registers SpindleType_PWM with no context.pwm;
spindleConfig forwards pwm_config_t to a driver pin callback but never invokes
CORE spindle_precompute_pwm_values or binds a spindle_pwm_t. CORE
spindle_control.c122 dereferences context.pwm during activation. Ordinary
spindle_select(0) in the authoring run triggered null-context sanitizer failures
for all six activation scenarios. Do not reproduce the unsafe activation again
on these unchanged source pins. Record source findings rather than adding a
sanitizer allowance or fabricating the missing object in the driver fixture.

Provider rejection tests remain active; full PWM/controller support is blocked
on a compatible source contract, not established by those six cases.
