# Scope and remaining work

Thirteen four-axis cases execute the original homing-acceleration plugin with
real CORE types and captured public settings/NVS/override callbacks. Assertions
check requested axis/value, restoration sequencing, zero/failed overrides,
success/failed homing completion, persistent values, rotary units and hook
chaining. The host models the documented axis-setting family and records
settings_override_acceleration requests; it does not execute settings.c or prove
planner acceleration or actual motor motion. No plugin private state is changed.

No known runtime assertion/diagnostic exception. Full settings parser, real
settings override backup, jerk variants and complete homing integration remain.
Source review: onSettingsChanged uses a NULL saved unit hook as its installation
sentinel. If CORE supplies no prior unit hook, a later settings change can save
its own wrapper. Do not force a recursive callback/stack failure; resolve hook
ownership contract before a safe public lifecycle regression is added.
