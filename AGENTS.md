# Repository working instructions

## Objective and delivery

Continue toward meaningful full grblHAL core coverage: every core module and
supported feature configuration, with line and branch coverage guiding the work.
Do not declare completion from a green suite, test count, or covered filenames.
Verify remaining source paths and configuration gaps. Do not exclude real code,
weaken assertions, or add artificial tests solely to inflate coverage.

- Keep responses short. Ask about genuinely unclear contracts; continue work
  that does not depend on the answer.
- Never add AI, ChatGPT or Codex attribution/branding to branches, commits or
  project artifacts.
- Make one focused commit per new test, with a descriptive behavior-based name.
  Keep infrastructure and documentation changes in separate commits.
- Use separate maintainable case files, shared fixtures only where useful.
- Push at a completed module or logical batch boundary after validation when
  authorized. A user instruction not to push overrides this workflow.
- Preserve unrelated work. Inspect status before edits, commits and delivery.
- Do not stop an explicitly authorized coverage run after routine batch reports.
  Keep the full objective intact; report blockers and measured limits honestly.

## Start or resume

Read [tests/PROGRESS.md](tests/PROGRESS.md), [ReadMe.md](ReadMe.md), and
[tests/KNOWN_BUGS.md](tests/KNOWN_BUGS.md). Inspect current Git status, core pin,
latest test outputs and CI. Progress snapshots can become stale; commands and
current files are authoritative. Keep `tests/PROGRESS.md` updated at delivery
boundaries with evidence, next work and any unfinished changes.

The repository root contains `CMakeLists.txt`, `ReadMe.md`, `tests/`, and the
`core` submodule. Parent workspace scratch files are optional local conveniences,
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
- Validate the individual case before committing it. Reconfigure when adding
  files or changing registrations. Build the exact target, then run an anchored
  CTest regex. Run the full sanitizer suite plus `scripts/summary.py` before
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

## Core and known defects

The core is independently versioned. Do not patch it to make tests pass, change
its pin, or push from its directory unless the task explicitly authorizes that
work. Forking this test repository does not fork the submodule: inspect its
remote before any core delivery. Use published core commits for CI-fetchable
pins. Parent-repository PRs carry a pointer, not an upstream core push.

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

- NGC coordinate parameters use `gc_state.modal.units` (G20/G21), not the `$13`
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
