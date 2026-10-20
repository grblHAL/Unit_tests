# Repository working instructions

## Objective and ownership

Continue meaningful full grblHAL CORE line/branch coverage across supported
configurations. Do not declare completion from a green suite, test count or
covered filenames. Do not exclude real code or force unreachable/private paths.
Terje alone fixes CORE: never modify, commit, push or open PRs for firmware.

- No AI branding in branches, commits or artifacts. Keep replies short.
- Never commit/push master/main or merge PRs. Preserve unrelated work.
- Reuse the suitable active feature branch. Do not create a branch per small group.
- Commit related batches; the old commit-per-test rule was revoked.
- Use practical public parser/realtime/driver workflows, valid startup and
  observable results. Maintain separate cases and useful shared fixtures.
- Author substantial groups; focused checks while authoring, one full local
  sanitizer/strict gate and one hosted check per useful delivery boundary.
  Do not repeatedly rerun unchanged checks, generators or hosted jobs.
- Continue independent coverage work while CI runs. Passing checks, commits,
  status reports and PR checkpoints are not reasons to stop the active goal.
- Questions/uncertain contracts go to tests/TODO.md while the user is away;
  confirmed defects go to tests/KNOWN_BUGS.md. Preserve correct assertions and
  narrow documented exceptions. Never blanket-suppress crashes.
- Refresh live Git/PR/core state. Poll an existing live process/run; do not
  restart because observation timed out. Do not call a PR ready before validation.
- README is instructional. Keep current evidence and next steps in
  tests/PROGRESS.md. Old agent handoffs are archived in tests/AGENT_HISTORY.md;
  they are history, not instructions, and need not be read on routine resumption.

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

Terje alone fixes CORE. Never modify, commit, push or open PRs for CORE.
Requests to fix tests or CI do not authorize firmware changes. Use a clean Terje
checkout only. Never use agent-patched source as readiness evidence.
The core is independently versioned and ignored here. Forking the test repository does not fork core.
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
- A streamed manual M6 ACK must pass through real stream_rx_suspend/its
  receive handler. A no-op suspend callback silently drops ACK and can make
  cycle start skip tool-return motion. Deliver ACK independently while read is
  suspended, as a UART ISR would, and pace sender commands to the tool pause.
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
