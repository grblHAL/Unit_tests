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

### Startup-line pending state after a failed write

**Observation recorded:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

Write startup slot 0 or 1 through `settings_write_startup_line()`, then have the
physical EEPROM handler reject its first write. RAM accepted the new command,
but `nvs_buffer_sync_physical()` clears the slot's pending bit
[before attempting the physical write at nvs_buffer.c:345](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/nvs_buffer.c#L345).
The pending mask and aggregate dirty flag both become zero. Subsequent syncs
therefore never retry the command, and physical storage retains the old text.
Coordinate, global, build-info and driver writes retain their dirty flag on
failure and have passing retry controls.

**Regressions:** [slot 0](cases/nvs_buffer/startup_slot_0_failed_sync_remains_pending_for_retry.c)
and [slot 1](cases/nvs_buffer/startup_slot_1_failed_sync_remains_pending_for_retry.c).
Separate `startup_slot_*_sync_preserves_text_and_checksum` cases verify successful
persistence and CRCs without an injected failure.

**Earlier implementation option (not applied; subject to the chosen policy):** Remove the unconditional
pre-write clear; clear that slot only after the physical handler reports success.
Leave failed slots dirty so another idle sync can retry them.

**After implementing the agreed contract:** remove the two startup retry blocks in
[known_bugs.cmake](known_bugs.cmake), keep all assertions, run storage/startup
cases and full sanitizers, then delete this TODO observation. No sanitizer allowance applies.

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
