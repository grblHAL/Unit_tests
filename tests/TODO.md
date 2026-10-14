# Pending core features and maintainer follow-ups

Pending implementation and design questions are separate from confirmed defects.
The deferred-defect section links to KNOWN_BUGS.md; their existing regressions
retain explicit expected-failure labels until fixed.

## Plain G71 and G72 lathe roughing

**Recorded:** 2026-10-12

**Status:** TODO - roughing geometry is pending; core parser dispatch is tested.

Terje's core `e65020a8389b19d3c03277e02f34219e25800e6a` now dispatches plain
G71/G72 to the roughing plugin interface with the correct motion code and
arguments. Tests capture that interface; they do not implement roughing geometry:

- [G71](cases/lathe_ngc/g71_passes_default_roughing_arguments_to_plugin.c)
- [G72](cases/lathe_ngc/g72_passes_default_roughing_arguments_to_plugin.c)

The existing G70 and fractional G71.1/G71.2/G72.1/G72.2 tests likewise exercise
parser/plugin interfaces using a capture handler.
The default [mc_lathe_cycle handler](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/motion_control.c#L806-L810)
also remains a placeholder.

When roughing geometry is implemented, add execution and endpoint tests against
that implementation, retain the parser/interface tests, and delete this TODO entry.

## Possible improvement: asymmetric ganging resolution validation

**Recorded:** 2026-10-13; reviewed with the user as an improvement, not a failure.

Writing an out-of-range secondary motor resolution through setting 103 currently
returns OK, then resets the value to the primary motor resolution and prints a
warning. The registered kinematics validator instead returns
`Status_SettingValueOutOfRange` without changing the previous secondary value.
The public lookup normalizes the axis setting ID and selects the generic axis
handler before the custom secondary-motor handler.

**Suggestion:** consider routing setting 103 to the registered kinematics validator
before the generic axis handler, so invalid writes return a clear error and preserve
the previous value. Keep the current warning/reset behavior until the maintainer
chooses that contract. The tests exercise the public valid write and the registered
validator independently; no expected-failure exception applies.

See [registered validator](cases/asymmetric_ganging/registered_resolution_validator_rejects_large_difference_without_mutating_motor.c)
and [public valid write](cases/asymmetric_ganging/resolution_setting_accepts_and_reports_small_motor_difference.c).

## Deferred confirmed defects

**Maintainer review:** 2026-10-14.

- [Fractional analog output](KNOWN_BUGS.md#analog-output-commands-truncate-fractional-values):
  Terje deferred implementation to a longer-term TODO list. Retain the correct
  fractional-value assertion and its linked exception; deferral is not a fix.
- [Unexpected file percent marker status](KNOWN_BUGS.md#unexpected-file-percent-marker-reports-success):
  Terje is wary of changing status semantics and deferred review. File-demarcation
  events currently bundle mass settings updates into one storage commit. Senders
  should demarcate bulk updates, especially with flash emulation: unbundled writes
  can each erase and rewrite the emulated EEPROM. Review status/event semantics
  together before changing the regression or implementation.

## Lathe diameter-mode conventions for reported offsets

**Maintainer review:** 2026-10-14; design question, not a newly confirmed failure.

Terje requested checking whether coordinate-style output in diameter mode should
apply special handling to tool offsets and other reported quantities. Define the
expected convention for each record before changing assertions. The dimensionless
G51 factor regressions already pass on Terje `50055a2`; their old exceptions and
known-bug entry were removed after direct verification. Do not reinstate that
fixed entry or treat the broader offset question as a confirmed defect.

Retain [inch-display factors](cases/report/scaling_parameter_report_keeps_dimensionless_factors_in_inches.c)
and [lathe factor reporting](cases/lathe_ngc/scaling_parameter_report_does_not_double_diameter_mode_factor.c).
Add offset-specific tests when the maintainer confirms the intended units/diameter
convention, and preserve existing coordinate and unit controls.

## G70–G72 execution and reporting contract

**Maintainer clarification:** 2026-10-14; design still undecided.

G70–G72 may not be motion modal states that should appear in reports. Their
implementation will trap motion commands emitted by the Q-word subprogram and
build a new subprogram for execution. Terje is considering a RAM file executed
through the parser, rather than direct `mc_line()` calls, because cutter
compensation is essential. Neither execution strategy is finalized.

Retain parser/plugin-dispatch tests. Do not add assertions that require G70–G72
to remain reported motion modes. The existing G70 modal-report and G70–G72 named
motion-parameter cases need review when the reporting contract is confirmed;
their current encoded values describe the present implementation, not a decision
about future cycle reporting. Add generated-subprogram execution, cutter-comp
and actual-motion reporting tests once the implementation and contract land.

## SCARA source integration and executable coverage

**Audited:** 2026-10-14 on Terje `39a69a22c72283ab186133b25fb89b8f5be35767`.

`kinematics/scara.c` is absent from core's CMake source list, and SCARA_ROBOT is
not included in core's automatic KINEMATICS_API selection. A syntax-only build
with both `SCARA_ROBOT=1` and `KINEMATICS_API=1` still fails at
[scara.c:319–321](https://github.com/terjeio/grblHAL_core/blob/39a69a22c72283ab186133b25fb89b8f5be35767/kinematics/scara.c#L319):
three setting definitions use undefined `Format_recimal` rather than
`Format_Decimal`. No production source was changed.

Resolve source integration and confirm SCARA support before claiming executable
coverage for this module. Then add host variants and independent geometric
controls, reachable/unreachable positions, segmentation, settings persistence
and homing tests. Current aggregate percentages do not prove SCARA is covered.

Reproduce the source audit with a GNU-compatible compiler:

```sh
clang -fsyntax-only -std=gnu11 -DSCARA_ROBOT=1 -DKINEMATICS_API=1 -Icore core/kinematics/scara.c
```

Path blending is separately marked experimental and unconditionally disabled
in `config.h`; do not silently patch that definition just to increase coverage.
