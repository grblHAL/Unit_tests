# Source incompatibility and test scope

Only six provider-rejection scenarios execute: no analog bank, non-PWM-capable
analog output, and absent storage, each direction compile variant. Actual CORE
spindle settings/ports and EEPROM execute; no private PWM context is supplied.
These passing cases do not establish working PWM activation or motor control.

Source pins:Plugins_spindle8a3ae47f5a218834da9c742424c3dd22c5629fdb;
COREb01f481072edecac33d5e40c25869359a5b3fa1f. Original pwm.c declares
SpindleType_PWM without context.pwm and neither initialization nor config fills
it. CORE activation dereferences context.pwm at spindle_control.c122. Initial
authoring activation produced null-context sanitizer failures in six scenarios;
those are now unregistered proposals, not known runtime allowances. Do not
rerun unsafe activation on unchanged sources. Original sources remain untouched.

Driver PWM callback models supplied configuration without inventing missing CORE
state. Full target/controller validation and hardware remain pending compatible
source changes. Original warning policy and existing Windows CRT compatibility
header match other suites. No aliases/casts alter firmware API contracts.
