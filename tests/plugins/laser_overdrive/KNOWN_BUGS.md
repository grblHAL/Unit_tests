# Known defects and scope

Eight selected original co2.c cases pass without known runtime allowances.
Original Plugins_laser26934c6c9607e0b5ba4a711516a60d4657bf142c and
COREb01f481072edecac33d5e40c25869359a5b3fa1f remain unchanged.

Driver PWM context is produced by actual CORE precompute/update-caps APIs, not
injected into plugin state. CORE registers PWM and basic spindles; original
selected/settings/M-code/reset/program-end hooks execute. Commands restore
consumed words like native CORE dispatch. Real CORE compute_value calculates
base PWM and overdrive/clamping; no copied conversion model.

Tests cover finite nonnegative percentages, negative/NaN/missing P validation,
laser/RPM-control availability, nonlaser selection, settings capability changes,
reset/program-end cleanup and previous hook chaining, including no selection.
Only validated supported commands execute. Full native parser jobs, electrical
laser power response, tube/PSU response time and physical engraving remain
unverified. No percentage-overflow or unsafe conversion reproduction is used.

Runtime driver reconfiguration uses driver-owned metadata and public CORE caps
update, not mutation of returned registry pointers. Unsupported settings/port
paths fail immediately at boundaries. Original warnings remain visible/nonfatal;
fixture-Werror and strict diagnostics apply. No source edit, ABI cast or
sanitizer diagnostic allowance. Inactive-spindle overdrive retention policy,
other configurations and hardware remain open.
