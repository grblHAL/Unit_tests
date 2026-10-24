# Known defects

## Spindle-link setting setter uses a different integer callback type - 2026-10-24

Source: grblHAL/Plugin_fans c5c3613c8d311b43427ec32d551a1e62a5a68531,
CORE b01f481072edecac33d5e40c25869359a5b3fa1f.

`fans.c:281` defines `set_spindle_link(setting_id_t, uint32_t)`. Its registered
Setting_NonCoreFn bitfield setting is called through CORE's
`setting_set_int_ptr(setting_id_t, uint_fast16_t)`, as confirmed by
`core/settings.h:1098` and the actual dispatch in `core/settings.c:3648`.
On Windows x64 Clang, uint_fast16_t is unsigned short; these function pointer
types differ. Linux x64 uses unsigned long and also differs from uint32_t.

`plugin_fans.spindle_delay` uses that public setter callback contract and then
checks linked output, 30-second scheduled delay, delayed shutdown and retention
of a manually enabled fan. Its output/state assertions pass; Clang UBSan reports
an incompatible function-pointer call at the exact setter invocation.

A named sanitizer-only Clang label and exact test/file/line/message manifest
retain visibility of this recovering diagnostic. GCC and coverage runs have no
required-diagnostic label. Unrelated diagnostics remain failures. A future Clang
run with no diagnostic fails classification until cleanup, rather than silently
keeping an obsolete allowance. Linux wording/behavior remains hosted-unverified.

Proposed upstream fix: use uint_fast16_t for the setter's integer argument to
match CORE's documented callback type. No production source or assertions were
changed. When fixed, retain the test, remove its Clang sanitizer property and
manifest entry, and delete this section after rerunning the suite and strict
summary. Do not replace the caller's cast with the plugin's incorrect signature.
