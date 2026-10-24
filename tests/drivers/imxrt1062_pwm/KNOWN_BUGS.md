# iMXRT1062 PWM scope

Original driverd1f8d1ed904242ee08b0a5583e78f490afd9ae93, CORE
b01f481072edecac33d5e40c25869359a5b3fa1f and Teensy SDK headers
7f107ee0a309f3813ed13f0d8f615497eca2ee49 remain unchanged. No assertion or
sanitizer allowances are registered for these valid PWM cases.

Original pwm.c, pwm.h, driver.h and generic board maps execute/compile with
actual SDK imxrt.h register structures/constants. Teensy4.0/4.1/MicroMod source
configurations are separate targets. The host maps only its own peripheral
memory and simulates pin-mux lookup plus F_BUS_ACTUAL. IRQ/cache ARM inline paths
are not called. No copied decoder or production/header guard replacement is used.

Thirty-six registered cases cover valid/unavailable/duplicate claims, up to five registered pins,
FlexPWM X/A/B output, all four clock gates, QuadTimer programming, inversion,
zero/full register duty values and source-specific board routing. Prescaler/
period, mux and compare/output-enable write images are checked. Nine further
batch21-validated cases reconfigure claimed handles and test independent FlexPWM
submodules plus three independent QuadTimer channels across all three models.
They preserve unrelated compare/control images and check polarity reset back to
normal; shared A/B submodule ownership is still outside this validated group. Register memory
does not emulate real timer progression or every write-one hardware effect;
physical frequency, edge timing, fault clearing and full board startup are not
established. pwm_enable currently returns true without configuring hardware.

SDK peripheral addresses are constants below4GB; native-width host pointers do
not truncate arbitrary RAM pointers. Original source pointer-cast/partial-table
warnings remain visible under -Wno-error; fixture code stays strict. Actual SDK
headers are system includes, not patched. No real Teensy firmware build is claimed.

Remaining contracts: unsupported type0 config/out paths are not publicly reachable
because claim rejects those pins; do not forge opaque handles. The five-slot claim
array has no visible bound check, so ownership/capacity contract needs review;
no sixth claim or memory-safety reproduction is attempted. Shared FlexPWM channel
polarity/compare preservation on reconfiguration needs a supported multi-output
board contract review: per-port ioports_analog settings call pwm_config, which
currently rewrites whole submodule fields. This is source-review TODO, not a
classified failure or excluded implementation.
