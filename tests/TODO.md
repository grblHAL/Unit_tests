# Pending core features and maintainer follow-ups

Pending implementation and design questions are separate from confirmed defects.
The deferred-defect section links to KNOWN_BUGS.md; their existing regressions
retain explicit expected-failure labels until fixed.

## Storage write-failure policy

**Maintainer disposition:** 2026-10-14, low priority; policy/design follow-up.

Terje notes that failures of flash-emulated EEPROM may be permanent, and a
simulator failure may instead involve a write-protected backing file. The driver
reports the operation's failure and identifies the storage type. A driver may
retry internally, but the **core decides the response to a reported failure**.
Neither a failed write nor this TODO implies that the user needs a new board.

Decide how the core reports failure, retains unsaved data and permits recovery,
accounting for physical EEPROM, flash emulation and simulator storage. Retry
count, timing and any alarm are undecided; five attempts is not an agreed rule.
Existing coordinate/global/build-info/driver retry controls provide comparisons,
not a universal retry policy for every storage backend.

The observations below are retained as reproductions and review options, rather
than urgent confirmed-bug entries. Existing expected-failure tests remain visible
until the maintainer chooses and implements the contract. Their `known_bug`
CTest label tracks the current exception; it does not assign priority. Revisit
pending-state and retry assertions against that chosen contract before cleanup.

### Review the new EEPROM warning counter

**Recorded:** 2026-10-15, Terje `feebef26222111f11c7a3b3b0156d023aa786937`.
The new EEPROM failure branch increments `retries` twice per failed sync
(`retries++` followed by `if(++retries == 5)`). Starting at zero, the counter
visits even values, so it does not reach the warning threshold of five before
integer wraparound. This is source-review evidence, pending a focused public
storage workflow reproduction and the maintainer's warning/retry policy.
Do not turn an assumed five-attempt policy into a registered failing test.

### Version-only pending state after a failed write

**Observation recorded:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

Write the settings version byte through buffered `hal.nvs.memcpy_to_nvs()`, then
reject its first physical write. The version flag correctly remains true, but
[the aggregate dirty calculation at nvs_buffer.c:379](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/nvs_buffer.c#L379)
omits `settings_dirty.version` and makes `is_dirty` false when no other record is
pending. Later syncs return immediately without retrying the version byte.

**Regression:** [failed version sync](cases/nvs_buffer/failed_version_only_write_remains_pending_for_retry.c).
**Passing control:** [successful version sync](cases/nvs_buffer/version_only_successful_sync_clears_pending_write.c).
Both exercise the public buffer-write API without manually changing dirty flags.

**Earlier implementation option (not applied; subject to the chosen policy):** Include the pending version
flag in the aggregate dirty expression. Preserve per-record success/failure flags.

**After implementing the agreed contract:** remove the version retry block in
[known_bugs.cmake](known_bugs.cmake), retain correct assertions and the control,
run storage/version cases and full sanitizers, then delete this TODO observation.
No sanitizer allowance applies.

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

## Removed SCARA source

Terje's `683589bd10bb1082825bfc7e9bcee6db102b9530` removes
`kinematics/scara.c`. The earlier source-integration and compile observations
on `39a69a2` are historical, so there is no current SCARA module to add to
the executable coverage inventory. Reassess support and tests if SCARA returns.

Path blending is separately marked experimental and unconditionally disabled
in `config.h`; do not change that definition solely to increase coverage.

## DO/WHILE CONTINUE contract

**Observation recorded:** 2026-10-14, Terje `39a69a2`; the user requested leaving this for Terje to comment on.

CONTINUE in a DO/WHILE loop currently rewinds directly to the body at
[ngc_flowctrl.c:611-612](https://github.com/terjeio/grblHAL_core/blob/39a69a22c72283ab186133b25fb89b8f5be35767/ngc_flowctrl.c#L611).
A finite counter loop with CONTINUE before its trailing WHILE never evaluates
that condition and repeats until the host read bound. Ordinary DO/WHILE and
CONTINUE with a later explicit BREAK have passing streamed-parser controls.

LinuxCNC O-code CONTINUE evaluates the loop condition. Confirm whether that
contract is intended here or whether restarting the body is a deliberate
difference. A bounded, no-motion [candidate regression](proposals/do_continue_rechecks_trailing_condition_and_skips_remaining_body.c)
is retained for review, outside the registered case set until intent is settled;
there is no expected-failure exception or source exclusion for this proposal.
Its correct resolution requires either implementing the chosen loop semantics
or documenting the deliberate difference, then reviewing the candidate assertion.

## Disabled auxiliary-output open-drain and timezone registrations

**Coverage inventory:** 2026-10-15, Terje `683589b`.

The auxiliary open-drain setter/getter exists, but its public setting registration
is commented out at [ioports.c:1449](https://github.com/terjeio/grblHAL_core/blob/683589bd10bb1082825bfc7e9bcee6db102b9530/ioports.c#L1449).
The ordinary public setting-disabled regression remains. The timezone setting
registration is likewise commented out at [settings.c:2503](https://github.com/terjeio/grblHAL_core/blob/683589bd10bb1082825bfc7e9bcee6db102b9530/settings.c#L2503).
These observations are not new core defects. Confirm supported exposure before
adding executable setting-update cases. Do not call the private setters or
modify production registrations merely to fill uncovered lines. If enabled
upstream, add public configuration, readback, persistence and driver-effect tests.

## Partial manual reference for ganged motors

**Contract question recorded:** 2026-10-15, Terje `683589b`; leave for maintainer review.

With persisted manual-homing mode, no homing phases and force-set-origin enabled,
real startup restoring XYZ/A motor counters {160, -240, 320, -240}, then `$HY`,
sets Y to zero but retains the secondary A counter at -240. X/Z are retained,
Y is marked referenced and no driver pulses occur. Both asymmetric ganging and
auto-square reproduce this result. Normal full startup homing and single-X
controls pass.

Should partial manual referencing of logical Y also zero its ganged secondary
counter, or should these configurations require referencing all axes? The
[kinematics position hook, lines 200-205](https://github.com/terjeio/grblHAL_core/blob/683589bd10bb1082825bfc7e9bcee6db102b9530/kinematics/asymmetric_ganging.c#L200-L205)
updates the secondary counter only when force-set-origin is disabled. The manual
homing path forwards the requested Y mask without the secondary bit. Confirm
supported use and intended semantics before calling this a defect.

The [candidate test](proposals/manual_ganged_y_reference_resets_both_motor_coordinates.c)
is unregistered pending that decision. Its fixture expects N_AXIS=4 and a ganging
or auto-square boot variant. No exception, source exclusion or production patch
was added. The ordinary startup homing tests remain registered.

## RTCP activation and measurement sequence

**Contract question recorded:** 2026-10-15, Terje `683589b`.

With default nonzero A/C center offsets and zero motor counters, public M851
changes the current RTCP coordinates to approximately (-113.660, -158.700,
186.540), while the parser's cached XYZ remains (0, 0, 0). A no-motion
[candidate frame check](proposals/rtcp_activation_updates_parser_frame_before_following_commands.c)
observes this after the sender acknowledgements, before another command or
motor pulse. It is unregistered, with no expected-failure allowance.

The [normal measured-frame control](cases/boot_rtcp/streamed_calibrated_default_geometry_keeps_incremental_move_local.c)
passes: M852 then M851 followed by a small incremental cut produces the intended
20/40/10 motor counters using those same default centers. Zero-centered and
fixed-angle streamed RTCP controls also pass.

Is M852 mandatory before enabling RTCP with nonzero center offsets? If so,
confirm/document that sequence and consider guidance for omitted measurement.
If direct activation is supported, should the parser coordinate cache be
resynchronized when the frame changes? The [M-code handler at lines 420-436](https://github.com/terjeio/grblHAL_core/blob/683589bd10bb1082825bfc7e9bcee6db102b9530/kinematics/rtcp_ac.c#L420-L436)
resynchronizes on M850 but not M851. This remains a workflow/contract question,
not a confirmed core defect. No production patch or source exclusion was added.

## Analog expansion pin-base bookkeeping

**Possible improvement / usage review:** 2026-10-15, Terje `683589b`.

Two external analog banks with two inputs and outputs each register and route
ADC/DAC calls correctly. A host inspection after public registration reports
bank 0 input/output pin bases 0/0, bank 1 bases 0/2. Digital expansion banks
advance both direction-specific bases consistently. In [ioports.c:1080-1087](https://github.com/terjeio/grblHAL_core/blob/683589bd10bb1082825bfc7e9bcee6db102b9530/ioports.c#L1080-L1087),
the input branch writes `out.pin_base` rather than `in.pin_base`.

Confirm whether supported analog expansion drivers use this input metadata
before classifying a user-visible defect. If the intended contract matches the
digital registration, assign the computed input base to `in.pin_base`, keeping
output and input counts independent, and add driver-facing metadata tests with
unequal bank sizes. Current routing/claim/IRQ tests pass; no known-failure label,
production change or source exclusion was added for this observation.

## Coverage inventory: inline/header implementations

**Recorded:** 2026-10-15, test branch coverage-batch-10, core Terje 683589b.

The core suite's coverage_filter in [ci/suites.json](../ci/suites.json) and
README local gcovr example include only core .c files. Current percentages
therefore do not account for executable inline/header bodies such as
stepper2.h profile functions, even when tests exercise them. This is a reporting
scope limitation, not evidence that those bodies are tested completely.

Keep this separate from the test batch's CI changes. A CI reporting follow-up
should include instrumented core headers and inventory supported conditional
code/inline bodies that are not emitted in the chosen builds. Retain the
source-file inventory and meaningful behavior assertions; do not exclude
uncovered code or equate 100% of the existing .c report with full core coverage.
An independent local header-inclusive measurement can guide further test work
without changing manual triggers or reusable callers.
