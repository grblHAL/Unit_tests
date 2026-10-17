# Repository working instructions

## Objective and delivery

Current work is coverage-batch-29, 22 new cases, 3,423 total. Full
batch29-delivery-results.xml passes in 44.87 s; strict summary and all 44 helpers
pass, eight expected failures, no sanitizer allowances. Terje source is still
clean/latest ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216 at the second live fetch.
Eight VFD cases, four G10 L0 reload cases, seven queued arc/G93 rejection/control
cases, one G93/G33 encoder case and two actual VFD-default boot cases are included.
Boot registers PWM during driver_init and VFD during driver_setup; it proves the
unused PWM is initialized off before VFD configuration, with saved/locked ranges.
No new core defects or allowances in batch29. Commit/push/dispatch this checkpoint
and continue coverage-batch-30 while hosted CI runs.
Batch27 run38986131807 and batch28 run38986684127 are fully green. Exact batch28
coverage: 16,714/17,630 lines (94.80%), 11,297/13,648 branches (82.77%),
harness eb44ea97c96493fe1acfd11a57987fd6bc367402/source ad57c78/core filter.
PR19 remains open at last check. No later PR has been claimed ready.
Potential next public gap: closing a claimed auxiliary UART with an associated
VFS file; success must close the file, failed release must retain ownership.
Do not force unavailable OpenDrain settings or the already documented unreachable
EEPROM warning counter; those are not coverage targets via private calls.

Frozen batch 24 starts from batch 23 7398414.
Nine new G95 cases pass full sanitizer/strict checks (3,370 total, 54.66 s),
all 44 helpers, ten expected failures and two documented recovering warnings.
Physical timer/step measurements verify RPM up/down changes, feed override,
G94 transition, inch units, lathe radial feed, rapid and zero-RPM guards.
Freeze/push this module and continue on coverage-batch-25. Useful next gap:
public planner allocation fallback/retry with realistic constrained heap budgets.
Batch 23 hosted run 38869601270 is validating exact head 7398414 against 4ec1ae4.
Latest fully green hosted baseline remains batch 22 (94.52% lines / 82.34% branches).

Frozen batch 23 starts from batch 22 b59409f.
Ten new motion/message/synchronization cases bring the local suite to 3,361.
Four G33 parser-to-stepper cases pass: metric, inch pitch/endpoint, reverse
travel and reuse of modal pitch. Index feedback advances independently; timer
interrupts run only after each driver's wakeup. Full batch23-delivery passes in
59.47 s, strict summary and all 44 helpers pass. Freeze/push and continue on batch 24.
The earlier 3,357-case batch23-final
passes in 49.13 s, strict summary and all 44 helpers. Ten expected failures remain.
Two message cases pass behavior assertions
with one narrowly documented recovering callback-type diagnostic (manifest).
Four G92 cases check executing offsets and actual sender status across queued
changes/suspension, away from the ambiguous shared endpoint tick.
Batch 22 run 38867880603 is fully green: source, GCC, Clang, coverage and diagnosis.
Coverage is 94.52% lines / 82.34% branches. It verifies the
ordinary stop test is Linux leak-clean and the portable ownership bug is isolated.
Continue independent gaps on batch 23; do not call it a ready PR yet.

Frozen batch 22 starts from batch 21 d4dc212.
Eleven new cases bring the suite to 3,351. The earlier nine-case checkpoint
passed full sanitizers/strict checks (3,349 total, 45.15 s and all 44 helpers).
They cover sender $SED reboot notices/hidden settings, named tool pacing,
compatibility-2 tool-reference format, and lathe mode/unit reporting.
Macro typo recovery and independent paired PWM M73 restoration also pass.
Batch 21 run 38866070072 passed coverage at 94.45% lines / 82.18% branches,
but GCC and Clang found a 12-byte parser comment leak. Batch 22 isolates it
with a portable malloc/free lifetime regression and one linked known-bug
exception. The stop-message test now supplies its message via public mc_line,
independently checking planner cancellation without triggering the parser leak.
The valid Modbus no-callback/next-transaction workflow also passes.
Full 3,351-case batch22-final passes in 44.52 s, strict summary and all 44
helpers pass; ten expected failures. Freeze/push and continue on batch 23.
Require fresh hosted validation of these changes before presenting a ready PR.

Frozen batch 21 starts from batch 20 3be1df6.
Thirteen new cases cover boot spindle hooks, selection veto, sleep/status/reset,
sender message clearing, modal macro/CSS/cutter reports, modal snapshot hooks,
CAN startup reporting and discarded future messages/outputs on sender stop.
Full 3,340-case sanitizer/strict gate passes in 54.71 s with nine expected
failures and all 44 helpers (batch21-final). Freeze/push this checkpoint and
continue independent work on coverage-batch-22 while its hosted validation runs.
Batch 20 exact-head hosted run 38804109761 against core 4ec1ae4 passed all jobs:
16,619/17,624 lines (94.30%), 11,187/13,648 branches (81.97%). PR 19 remains open.
Batch 19 adds 15 cases / 3,312 total. Full ASan/UBSan, strict summary and 44 helper
checks pass in 58.09 s (batch19-delivery), nine expected failures. It is pushed;
exact-head hosted run 38799824879 is fully green: 94.18% lines / 81.85% branches.
Batch 20 now adds 15 cases / 3,327 total. Full sanitizer/strict gate and 44 helpers
passed the earlier 3,319-case checkpoint (54.68 s). New soft-limit tests exercise idle/active
alarms, status/reset, interrupted deceleration and coupled CoreXY motors.
Continue from the latest hosted report; lathe threading unit/diameter conversion
and remaining supported parser workflows are useful next areas.
Core is clean latest Terje 4ec1ae4 after its forced remote update. Two fixed
exceptions/entries (paired ramp cache and legacy $4 readback) are removed; their
unchanged regressions pass. New G76 inch P/E conversion regressions are narrowly
documented expected failures; metric/depth/diameter controls pass. Full 3,327-case
latest-source gate passed in 113.54 s with nine expected failures, strict summary
and 44 helper tests (batch20-latest-delivery). Exact-head hosted validation is
required before a ready PR. Uncertain driver-failure detail reporting
is a TODO policy question, not a new known-failure exception.

Frozen batches 15-18 all passed exact-head hosted source/GCC/Clang/coverage and
diagnosis. Latest measured baseline is batch 19 run 38799824879: 16,600/17,625
lines (94.18%) and 11,171/13,648 branches (81.85%), 3,312 cases. Batch 17 run
38795069102 measured 93.79% / 81.35%. Source-lock artifacts verify both revisions
and header-inclusive filters; full history/evidence lives in tests/PROGRESS.md.
PR 19 (batch 14) remains ready/open at last live check. Prefer its merge before
rebasing/presenting later batches without duplicate parent tests. Never merge PRs
automatically or commit/push master/main. Continue toward the full coverage goal.

DO/WHILE CONTINUE remains a maintainer question in TODO.md; its candidate is
unregistered. The separate WHILE false-condition regression is fixed on current
core and retained as an ordinary passing test. NO_SAFETY_DOOR_SUPPORT build
support is also a TODO question; keep its four candidates unregistered until
support status and missing setter/table guards are resolved.

Continue toward meaningful full grblHAL core coverage: every core module and
supported feature configuration, with line and branch coverage guiding the work.
Do not declare completion from a green suite, test count, or covered filenames.
Verify remaining source paths and configuration gaps. Do not exclude real code,
weaken assertions, or add artificial tests solely to inflate coverage.

- Keep responses short. Ask about genuinely unclear contracts; continue work
  that does not depend on the answer.
- Never add AI, ChatGPT or Codex attribution/branding to branches, commits or
  project artifacts.
- Commit meaningful batches of related tests with descriptive behavior-based
  messages. The earlier one-commit-per-test rule was revoked by the user.
  Keep unrelated changes out of the batch.
- Use separate maintainable case files, shared fixtures only where useful.
- Prefer larger delivery batches spanning related workflows/modules. Validate
  focused cases together, and run the full sanitizer suite and
  push/verify CI at substantial delivery boundaries rather than every few tests.
  Continue independent coverage work while CI runs; avoid repeated polling.
  A user instruction not to push overrides this workflow.
- Preserve unrelated work. Inspect status before edits, commits and delivery.
- Do not stop an explicitly authorized coverage run after routine batch reports.
  Keep the full objective intact; report blockers and measured limits honestly.

## Start or resume

Read [tests/PROGRESS.md](tests/PROGRESS.md), [ReadMe.md](ReadMe.md), and
[tests/KNOWN_BUGS.md](tests/KNOWN_BUGS.md). Inspect current Git status, tested core revision,
latest test outputs and CI. Progress snapshots can become stale; commands and
current files are authoritative. Keep `tests/PROGRESS.md` updated at delivery
boundaries with evidence, next work and any unfinished changes.

The repository root contains `CMakeLists.txt`, `ReadMe.md`, `tests/`, and the
ignored ordinary `core` checkout. Parent workspace scratch files are optional local conveniences,
not required project dependencies. Never assume a new machine has them.

## Write and validate tests

- Test original core source. Do not copy/reimplement production functions.
- Add `tests/cases/<module>/<behavior>.c` with `check.h` and `int main(void)`.
  CMake discovers cases automatically. CTest name is `<module>.<behavior>`;
  executable target is `test_<module>.<behavior>`.
- Reuse the most relevant fixture in `tests/support/`; read it first. Use
  `CHECK`/`NEAR` rather than C `assert`, so checks remain active in Release.
- Check a real contract and observable behavior, including boundaries/errors,
  state preservation and callback ordering. Do not mirror implementation details
  without asserting their externally meaningful result.
- Route new modules/configurations in `add_core_test()` and the host variants
  in `CMakeLists.txt` when needed. Feature compile definitions must be consistent
  between the test and the linked host core.
- Validate new cases as a focused batch before committing. Reconfigure when
  adding files or changing registrations. Build the relevant targets, then run
  a CTest regex covering the new behavior. Run the full sanitizer suite plus `scripts/summary.py` before
  pushing a batch. The summary can reject diagnostics even when CTest is green.
- Verify GCC and Clang sanitizer jobs and the coverage job after delivery. Avoid
  rapidly pushing consecutive batches that cancel an earlier running CI job.
- Use a separate coverage build. Merge feature variants with gcovr's
  `--merge-mode-functions=separate`. For a fresh measurement use a fresh build
  directory; old execution counts can inflate results.
- Do not edit shared fixture headers while another build compiles them. Keep
  Git index mutations sequential; inspect failures before rerunning generators.

Typical focused check after configuring `build-clang`:

```sh
cmake -S . -B build-clang
cmake --build build-clang --target test_gcode.css_cutting_move_plans_start_and_target_rpm
ctest --test-dir build-clang --output-on-failure -R '^gcode\.css_cutting_move_plans_start_and_target_rpm$'
```

Full commands, compiler prerequisites, core-update and cleanup instructions are
in the README. GNU-compatible Clang/GCC is required for the full suite; MSVC
skips many modules. Compile checks should preserve GNU language extensions;
strict C11 previously produced an unrelated Linux `ffs` declaration error.

## CI source selection

`tests.yml` calls `reusable-tests.yml`. No tracked submodules remain on this
branch. `ci/suites.json` defaults to upstream core master. Resolution locks both
source/dependency SHAs and the test harness SHA once per run; all jobs use them.
Upstream callers live in `ci/callers/`, with fork PR head selection and read-only
permissions. Plugin caller is a template until a real suite is registered.
Run `python -m unittest discover -s scripts -p 'test_*.py'` for helpers.
Never overwrite dirty source checkouts, pass inherited secrets to candidate jobs,
or claim upstream caller installation/hosted validation before verifying them.

## Core and known defects

The core is independently versioned and ignored here. Do not patch or push its
repository without authorization. Forking the test repository does not fork core.
Inspect its remote before delivery. Test source revisions independently using
CI inputs or local checkouts; never stage the core directory in this repository.

Before classifying a core defect, verify startup order, feature flags, buffer
sizes, callback signatures and the intended contract. Use a passing control
where possible. Inspect the exact failing assertion or diagnostic with verbose
CTest; an unrelated fixture crash is not proof of the alleged defect.

Preserve the correct expected result. Each confirmed outstanding defect needs:

- A focused regression and a dated entry in `tests/KNOWN_BUGS.md` with source,
  reproduction, test and precise cleanup links.
- For an assertion failure, a narrowly scoped expected-failure block in
  `tests/known_bugs.cmake` (`WILL_FAIL`, `known_bug`). Unexpected success must
  force cleanup rather than be accepted as ordinary success.
- For recovering sanitizer warnings, narrowly matched objects in
  `tests/known_sanitizer_diagnostics.json`; no global suppression. Some issues
  need several objects. Functional tests can pass while warning classification
  remains separate.
- For fatal sanitizer/compile failures, the existing specific diagnostic-wrapper
  pattern where appropriate; verify it recognizes only the intended defect.

When fixed, retain the case's correct assertions and remove its exceptions.
Replace special wrappers with normal executable/compile tests where applicable.
Delete the resolved section from `KNOWN_BUGS.md`; record fix date and revision
in the cleanup commit. Retain partial entries only for outstanding failures.
Reconfigure and run the full suite plus summary without the removed allowances.

Link core source directly to `https://github.com/grblHAL/core/blob/<commit>/...`
with verified line anchors. Relative `../core/file.c` links do not traverse the
GitHub submodule. Check remaining anchors after deleting exception blocks.

## Established contracts and fixture lessons

- NGC coordinate parameters use `gc_state.modal.units_imperial` (G20/G21 in the pinned core), not the `$13`
  serial display setting. Set modal units in those tests.
- MPG buffered commands may overwrite queued lines by design. Pendants must
  wait for the response before sending another command; this is not a bug.
- Register the primary spindle before settings initialization. Additional
  spindles must be registered by the end of `hal.driver_setup()`, before the
  spindle sanity check in `grbllib.c`. The earlier runtime enumeration complaint
  was withdrawn; do not reintroduce it as a known defect.
- Register PWM capability in the intended machine mode before parser startup.
  Switching fixture mode after registration can retain stale capabilities.
- With LATHE_UVW_OPTION, U is always an incremental diameter (half its value
  changes X radius); V/W increment Y/Z. These differ from six-axis UVW remapping.
- Constant RPM output does not require redundant PWM writes. Verify retained
  output state as well as update callbacks.
- Encoder feedback must remain measured input: output mocks must not overwrite
  it merely to mimic requested RPM.
- Parser errors deliberately discard pending tool actions and deferred offsets.
  Test that cleanup while verifying the current tool is not changed; do not
  classify loss of deferred state on an error as an unintended mutation.
- Hooks that the core captures during initialization must be installed before
  that initialization. Supply real connected/control/report callbacks when a
  tested path can emit reports.
- NVS APIs expecting `stored_line_t` need a full-size object, not a short string
  literal. Use `mpos_t` for machine steps instead of guessing its element type.
- Use metadata/public settings APIs and correct getter names/signatures.
  `setting_get_float_value(setting_get_details(id, NULL), 0)` is the float getter.
- Check-mode parser tests prove validation/modal behavior, not physical motion.
  Planner/stepper execution fixtures exercise real planning and emitted pulses,
  but do not establish hardware electrical timing.
- PID deadband and `p_max_error` are not implemented contracts in the pinned
  source. Zero sample rate needs an upstream-defined contract before assigning
  an expected result.

## Additional feature fixtures

- Jerk acceleration has standalone and G187-combined hosts. Initialize every
  moving axis jerk in motion fixtures; fixture defaults leave it zero. Tests
  must check planner limits and actual pulse/endpoint behavior independently.
- Spindle-synchronized planner data requires a valid `get_data` encoder callback,
  even when only testing the planner's jerk exclusion. Missing driver callbacks
  are fixture contract errors, not automatic evidence of a core defect.
- Rotation tests use the actual core rotate function and persisted coordinates.
  G91 omitted axes must represent zero incremental movement. The documented
  regression must retain that expectation; explicit-zero and absolute-motion
  control cases prevent accidentally treating the current defect as intended.

- Spindle-sync startup waits for two new encoder index pulses before waking the
  driver. A constant-feedback mock without elapsed-time/index progression hangs
  the fixture. `spindle_sync_motion_host.h` models both startup and running
  feedback from measured RPM/time independently of commanded displacement.
  Keep the missing-index alarm and stop/reset tests distinct from normal motion.

- `jog_motion_host.h` drives real $J system commands through planning, stepping
  and protocol completion. Jog G20/G91 settings apply to that command while
  preserving program modal units/distance. Rejected jogs must preserve position
  and avoid motor wakeup; clipped jogs must execute the actual clipped endpoint.
- Zero-length constant-power laser lines use buffer synchronization before
  applying output. Verify pulse completion and an empty planner from the output
  callback, not only the final requested power.

- `toolsetter_motion_host.h` runs actual G59.3/G30 tool-change positioning and
  semi-automatic probe workflows. Its Z contact sensor reads machine steps;
  XY pulse checks require retracted Z. Set the real work-envelope bounds before
  automatic probing, since probe travel is clipped for homed axes. Test both
  contact/release reference modes, existing-reference offsets and failure cleanup.
- Select substantial uncovered workflows from fresh line/branch evidence.
  Aggregate function coverage across variants before calling a function untouched;
  a zero-count record in one configuration can be covered in another.

- Plain G71/G72 roughing is pending implementation per the maintainer/user
  clarification, not a known failure. See `tests/TODO.md`; do not restore its
  old known-bug labels. Current tests verify rejection without movement. Update
  them to successful functionality when implementation lands and remove the TODO.
- Program flow is intentionally reset after parser pause/completion callbacks.
  To verify transient M0/M1/M2/M30 serial reporting, observe/report from the
  real callback before that reset; install required realtime callbacks.

## CI diagnosis maintenance

Concise reporting work belongs on `ci-actionable-reports`, separate from coverage
expansion. `report_stage.py` preserves command exit codes and full logs;
`ci_report.py` groups first-error/test findings across jobs; `changed_coverage.py`
warns on added executable C lines relative to the locked source merge base.
Warnings must not be described as proof that code has no tests. Missing diagnostic
artifacts or unexpected sanitizer output must never turn a failed job green.
Caller baseline refs/repositories and source PR bases resolve once in the lock.
Keep README instructions, not dated progress reports; record validation separately.

## Batch 3 coverage continuation

The user started batch 3 on 2026-10-13: coverage work now belongs on
`coverage-batch-3`, based on upstream master after PR #5 merged. The older
`initial-batch-part-2` instructions above describe previous work, not the current
branch. Use Terje's `terjeio/grblHAL_core` master as the candidate source and
record the exact tested SHA at each substantial batch. Do not pin the registry or
restore submodules. Keep production core untouched and validate resolved known
regressions before removing exceptions. Separate the proposed-fix documentation
PR #6 from coverage work.

## Batch 3 stopping point

The user requested a final coverage report and batch 3 PR on 2026-10-13.
This supersedes the earlier no-early-PR and unattended-continuation instructions.
Finish latest-Terje compatibility, current kinematics cases, known-exception
cleanup, coverage measurement and hosted validation. Open the PR, pause the
full-coverage goal, and stop. Resume coverage expansion only when asked.
The secondary-motor resolution warning/reset behavior is a possible improvement
in `tests/TODO.md`, not a confirmed defect or expected-failure allowance.

## Batch 4 coverage expansion

The user resumed coverage on 2026-10-14 and requested a new branch and separate
PR. `coverage-batch-4` starts from upstream `36e248d` after PR #7 merged.
This overrides the batch 3 pause. Use latest Terje core, verify fixed exceptions,
add meaningful tests from measured gaps, validate locally and in hosted CI,
then open the separate batch PR. Keep production core unchanged.

## Sustained coverage instruction (2026-10-14)

The user clarified that batch 4 must continue toward meaningful 100% core
coverage. PR #8 is a progress checkpoint, not completion or a stopping point.
Continue substantial test batches on `coverage-batch-4`; green CI, commits,
module completion and the existing PR do not authorize stopping or pausing.
Keep correct regressions and verified coverage/configuration evidence. Only
pause on a later explicit human request or report a concrete blocker. Earlier
batch-3 pause instructions are historical and superseded by this resumption.

## Batch 5 continuation

PRs #8 and #9 have merged. Continue on `coverage-batch-5`, preserving the
unmerged storage/filesystem continuation and debug tests from batch 4. The user
authorized temporary manual-only harness CI triggers in this next coverage PR;
keep reusable source callers available. Continue toward full meaningful coverage.

## Batch 6 continuation

PR #10 merged on 2026-10-14. Continue new coverage on `coverage-batch-6`,
based on upstream master `5019b8f`. PR #10's GCC/Clang/coverage/diagnosis run
38530893125 passed against Terje `39a69a22c72283ab186133b25fb89b8f5be35767`.
Keep manual-only harness triggers and reusable callers. Continue from fresh
coverage gaps; new PRs remain checkpoints toward full coverage.

## Batch 7 active continuation

PR #11 merged as upstream f58c92d after its final run 38535569786 passed.
Batch 7 is isolated on `coverage-batch-7` and includes that merged baseline.
The user requested a review boundary and cleanup of fully merged remote branches.
Keep unfinished AUX_SETTINGS_PULLUP cases/variant out of this delivery until the
live/load pull-mode contract is clarified. Read PROGRESS.md for exact validation
and branch cleanup evidence.
Continue meaningful coverage with Terje core, preserving verified assertions.

## Batch 8 local continuation

PR #12 (134 new cases) merged as upstream f5ba765 after final run
38581963519 passed every job.
New work is isolated on local-only coverage-batch-8, based on its merged
upstream baseline. Keep the pending
AUX_SETTINGS_PULLUP cases/variant out of delivery until the mode contract is
clarified. Revalidate the shared host default settings callback under the full
suite before delivery; it must match normal core startup, not mask real failures.
Continue meaningful full coverage from measured gaps without modifying core.

## Pullup consistency classification for PR #13

On 2026-10-14 the user explicitly authorized moving the pullup mismatch into
KNOWN_BUGS.md and adding its narrow expected-failure classification so PR #13
can become ready after validation. This supersedes the earlier instruction to
keep those cases out of delivery pending a mode choice. The consistency assertion
is unchanged; only its named case has an exception. The maintainer still chooses
no-pull versus pull-down, and mode-specific controls need review when fixed.
The full-coverage goal remains paused for the user's overnight break.

## Practical test-authoring guardrails (2026-10-14)

Prioritize supported machine workflows: motion endpoints and emitted pulses,
probing, limits, offsets, spindle/coolant control, reset/stop and persisted settings.
Coverage identifies gaps; an uncovered line alone does not justify a test or bug.
Keep the full-coverage objective, report unsupported/unreachable paths honestly,
and do not exclude source, invent private-entry calls or weaken expectations to
force a percentage.

Before writing a case, identify its agreed contract, valid startup/configuration,
public trigger and observable consequence. Prefer real parser/driver/core entry
points. Boundary and failure-injection tests remain useful, but explain why their
inputs/event order are valid and assign proportionate priority. Prioritize normal
workflows before speculative or low-impact robustness cases.

Before calling a result a defect, separate fixture mistakes, confirmed contract
violations, design questions and possible robustness improvements. Include passing
controls and a source-linked reproduction. State whether reproduction is only at
an API boundary, from a sender command sequence, or verified on hardware. Never
infer motor acceleration, safety severity or real-world frequency solely from a
mocked PWM transition. Human UI reproduction is not required for a valid queued
command ordering, but feasibility must be explained.

The maintainer settles unclear contracts. Correct or withdraw invalid assumptions;
use TODO for undecided behavior and low-priority policy work. Do not inflate the
repair backlog merely to increase coverage. Preserve known-failure exceptions
only for explicit documented expectations; clean them up when the chosen contract
is implemented. Keep small case files and validate substantial batches.

The user's request to resume revokes the earlier overnight pause instruction.

## Batch 9 continuation

The user resumed the goal with the practical authoring guardrails on 2026-10-14.
PR #13 is ready after final hosted validation; new work is isolated on local-only
coverage-batch-9. Preserve its parent until merged and avoid duplicate PR diffs.
Prioritize supported sender/machine workflows and explain valid triggers and
observable consequences. Do not infer mechanical effects from mocked outputs.
