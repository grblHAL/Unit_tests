# CI design validation

2026-10-13, branch `ci-source-selection` (separate from paused coverage work).

- No gitlink or `.gitmodules` on this branch; source directories are ignored.
- Twenty CI helper tests pass, including fork PR resolution,
  independent plugin/core locking, unknown suites, dirty checkout preservation,
  path escape rejection and immutable fetch arguments. Reporting tests also
  verify custom suite manifests, rejection of unknown sanitizer warnings and
  plugin-only coverage inventories.
- `actionlint` passes both workflows and both caller templates.
- A fresh clone resolved/fetched upstream master at
  `ca26fc98f1b2171251c946ab91d5912b733efa78` without submodules.
- Representative parser and settings CRC tests passed under Windows Clang
  ASan/UBSan from that fresh ordinary checkout, with strict summary passing.
  This is a pipeline smoke check, not evidence that the complete suite passes
  against the newer core. Use the hosted GCC/Clang/coverage results for that.
- First hosted run: https://github.com/petervanderwalt/Unit_tests/actions/runs/38352941636
  Source resolution passed. GCC, Clang and coverage completed with build
  failures. All jobs correctly reached selected-source configuration/build.
- The full local fresh-checkout build reproduces errors in current core's
  `stepper2.h`: undeclared ceilf/sqrtf/fabsf/lroundf when included by secondary
  stepper fixtures. Representative parser/settings smoke tests pass, but the
  complete latest-core suite has not passed. This is a source/header integration
  failure exposed by selecting newer core, not grounds for excluding those tests.
  Core was not patched. Hosted annotations confirm build failures; hosted logs
  should be consulted before asserting every compiler failed for identical causes.
- Caller installation in upstream core/plugins remains Terje's deployment step.
  Plugin caller is a template until actual plugin fixtures/tests are registered.
- Existing historical core regressions may be fixed in current upstream, which
  intentionally produces cleanup failures rather than silently passing them.

README verification identified and corrected an extra positional diagnostics
argument in `run_suite.py`. `summary.py` now accepts explicit diagnostics,
source inventory and suite-name options; existing two-argument invocations
retain core defaults. Reusable jobs run all 20 helper/reporting regressions.
The original hosted run predates this reporting correction; its build failures
remain separate from the corrected summary invocation.

Actionable-reporting checks verify that changed known regressions link to the
recorded harness's known-bug file and give precise cleanup guidance, ordinary
failures give reproduction/contract-review guidance, and missing coverage files
are flagged without claiming they are newly added code. No changed-line coverage
comparison is implemented; that needs an explicit source baseline.

## Merged-PR follow-up: ci-core-compatibility

2026-10-13, based on upstream master `6a5dada` after PR #2 merged.
Failed upstream run 38354097113 logs confirmed `task_execute` linker failures
in standalone limits tests for GCC, Clang and coverage.

The follow-up supplies a fail-on-unexpected-call scheduler mock for isolated
limits cases, adapts the real scheduler wrapper to its old state/new wait API,
installs valid host foreground hooks, connects homing ISR simulation to both
hooks, and provides math declarations for secondary-stepper header consumers.
Modbus tests invoke the new public reset API where available and verify actual
transaction integrity rather than obsolete callback counts/version numbers.
Critical-alarm checks retain actual hard-limit/critical-lock assertions while
supporting callback-context changes. Timer fallback checks verify polling/output.

The finite-move regression now passes with exactly ten pulses/position ten.
Its expected-failure block and resolved bug entry were removed; assertions stay.
Fix verified in core `ca26fc98f1b2171251c946ab91d5912b733efa78` on 2026-10-13.
The unchanged Modbus null-descriptor defect was reconfirmed at line 1291; its
matcher accepts only verified lines 1225/1291 plus the original strict diagnostic.
Exception documentation anchors were rechecked after cleanup.

Full Windows Clang ASan/UBSan and strict summary: 2,242 tests, 2,141 clean passes,
46 passes with known sanitizer diagnostics, 55 known regressions reproduced,
zero unexpected failures, zero skipped. Evidence in local workspace scratch:
`ci-compatibility-verified-tests.log` / `ci-compatibility-verified-summary.log`.
Nine representative compatibility cases also passed on historical core 451a539.
CI helpers: 20 passing; workflow actionlint passes. Core source was not patched.
Hosted compiler/coverage validation for this follow-up is pending publication.

## Terje's October 13 fixes

Branch `ci-terje-fix-validation`, based on merged upstream harness `63323b5`,
was validated against `terjeio/grblHAL_core` revision
`4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa`. Core source was not patched.

- Full Windows Clang ASan/UBSan: **2,242 tests; 2,221 clean passes, 21 documented
  known regressions, zero unexpected failures, zero skipped**. Strict summary passes.
- 44 obsolete expected-failure registrations and all four recovering sanitizer
  manifest entries were removed. Five resolved diagnostic wrappers were deleted;
  compile and executable regressions now run normally.
- Tool callbacks support the new persistence flag. Fixtures model validated tool
  copies, cached tool reload, driver startup, foreground synchronized I/O, valid
  check-mode behavior, alarm callbacks and expanded status-report bits.
- Remaining VFS close and embedded seek memory defects were reproduced with
  strict diagnostic matching. Nine existing laser/tool cases expose two newly
  confirmed defects, documented with source and cleanup links in KNOWN_BUGS.md.
- CI helper tests: 24 passing, including rejection of unrelated sanitizer faults.
  Workflow actionlint passes.

Evidence: workspace scratch `terje-tests-verified.log`,
`terje-results-verified.xml`, `terje-summary-verified.log`. Hosted GCC, Clang sanitizers and
coverage all passed in [run 38367839505](https://github.com/petervanderwalt/Unit_tests/actions/runs/38367839505)
using harness `90c890d` and the same exact candidate source.
The default upstream core may not yet contain these fixes; older-source failures
are genuine regressions against the retained correct expectations.

## Upstream master confirmation

On 2026-10-13, [run 38369552031](https://github.com/grblHAL/Unit_tests/actions/runs/38369552031)
passed source resolution, GCC, Clang sanitizers and coverage on merged harness
`66b7d90c8b644d44fc2c3f2b0131f8f022255a98` against Terje's core
`4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa`. Both compiler logs report
2,242 tests and zero unexpected failures. This confirms the selected candidate,
not an untested default-core revision. PR #4 has merged and its fork branch was
removed; fork master is synchronized to this upstream harness revision.

## Concise diagnosis implementation

Branch `ci-actionable-reports` includes the instructional README cleanup. It
captures setup/build/test/classifier exit codes and full logs, groups matching
compiler findings in a final CI diagnosis, links exact locked source revisions,
and warns about added executable C lines not exercised relative to a locked base.
Source PRs lock their base automatically; caller push baselines and manual base
inputs are supported. Coverage warnings do not fail an otherwise successful run.

Local verification: 44 helper tests pass; workflow/caller actionlint passes.
A fresh full Clang sanitizer run against Terje's `4b128e6` passes all 2,242 cases
(2,221 clean, 21 known, zero unexpected failures). The new reporter accepts that
JUnit output. Replaying the actual failed run 38363912997 groups GCC/Clang callback
errors into one finding at `tests/support/g10_tool_host.h:25`. Real temporary Git
history tests verify changed-line selection, ignored historical gaps, merged
variant hits and separate unmeasured-file warnings. Hosted [run 38373299801](https://github.com/petervanderwalt/Unit_tests/actions/runs/38373299801)
passed source resolution, GCC, Clang, coverage and final CI diagnosis on harness
`f8b4d05` against Terje's `4b128e6` with baseline core `ca26fc9`. Its coverage
artifact reports nine warnings, including uncovered added executable lines and
an unmeasured changed `scara.c`; warnings did not fail the run. The concurrent
default-source run also produced concise structured test failures, confirming
failure reporting independently of the passing candidate. Subsequent parser
checks cover CMake reason/location, timeouts and namespaced HTTP errors; all
44 local helpers pass without changing the core/test assertions. No core source or unfinished coverage tests changed.

## Axis claiming contract and Modbus documentation correction

On 2026-10-13, Terje's remote master was checked directly with `git ls-remote`
and matched the tested `4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa` revision.
The axis claiming test now checks validated X-only returns zero, masks 3 and 2
claim only numeric Y, and a zero validation mask claims both present words.
Its known-bug entry and expected-failure registration were removed.
The full Clang sanitizer suite and strict summary pass: 2,242 tests, 2,222 clean
passes, 20 documented known regressions, zero unexpected failures/skips. All
44 helper tests pass.

The Modbus three-register regression was rerun and still observes `_value2=51`
instead of 34. Its surviving entry now links the reviewed handler at lines
1266/1271-1274 and describes the remaining third-value overwrite, rather than
the stale exactly-two-values condition. The core was not patched.

## Batch 3 coverage checkpoint

On 2026-10-13, `coverage-batch-3` tests Terje's
`e65020a8389b19d3c03277e02f34219e25800e6a` core without production-source edits.
The branch adds 48 new cases and restores/revalidates 12 archived parser cases.
Six fixed issues lose 13 obsolete expected-failure allowances; their assertions
remain. The M72 override-control defect is new; the archived unexpected-file-marker
error is still reproduced and its exception has been restored.

Full Windows Clang ASan/UBSan: 2,302 tests, 2,293 clean passes, nine known
regressions, zero unexpected failures/skips. Strict summary passes; all 40 Python
helper tests pass. Fresh Clang coverage build, followed by full tests and merged
feature variants: 85.9% lines (15,637/18,206), 91.7% functions (1,113/1,214),
72.1% branches (8,954/12,424). CAN covers all 61 executable lines and all measured
branches. Four fatal-memory wrappers explicitly skip in coverage mode and run
under sanitizers. Hosted GCC, Clang, coverage and diagnosis subsequently passed
on harness `bcafe18`, Terje source `e65020a`, baseline `4b128e`:
https://github.com/petervanderwalt/Unit_tests/actions/runs/38426592992

The next local reporting/parameter extension passes 2,340 sanitizer tests:
2,315 clean passes and 25 documented known regressions, zero unexpected
failures/skips. Strict summary and 40 Python helper tests pass. Hosted GCC, Clang, coverage and CI diagnosis pass on harness `31fd05b`,
Terje source `e65020a`, baseline `4b128e`:
https://github.com/petervanderwalt/Unit_tests/actions/runs/38430798382
Later modal/multiple-probe cases remain locally validated only. Its completed 2,337-test coverage
snapshot is 86.2% lines (15,689/18,206), 91.8% functions (1,114/1,214)
and 72.4% branches (8,997/12,424).


## Later batch 3 checkpoints

Hosted GCC, Clang, coverage and diagnosis passed harness `01a5df6` against Terje
core `e65020a`, baseline `4b128e`:
https://github.com/petervanderwalt/Unit_tests/actions/runs/38433324502

Its 2,363-case local merged coverage is 86.5% lines (15,757/18,206),
91.8% functions (1,115/1,214), 72.9% branches (9,061/12,424).
The next 35 cases pass local ASan/UBSan and strict summary: 2,398 tests,
2,369 clean passes, 29 known regressions, zero unexpected failures/skips.
Hosted validation and coverage refresh of these later cases remain pending.


Hosted GCC, Clang, coverage and diagnosis passed the 2,398-case batch on harness
`8e4392b`, Terje source `e65020a`, baseline `4b128e`:
https://github.com/petervanderwalt/Unit_tests/actions/runs/38435512145
Its GCC artifact reports 86.3% lines (14,919/17,282), 72.3% branches
(9,700/13,422). These denominators differ from Windows Clang instrumentation;
do not present the measurements as directly comparable.

The subsequent RS485-direction extension passes 2,404 local sanitizer tests:
2,374 clean and 30 known regressions, no unexpected failures/skips. All 47 Python
helpers pass, including strict Windows/Linux-form crash matcher tests. Actual
hosted execution of the new fatal-startup regression remains pending delivery.

## Batch 3 final local validation

Terje source `d216287a6cf1f9ec278a92ac403c30a8cf5fad3b`, baseline `e65020a`:
2,436 Clang ASan/UBSan cases, 2,410 clean passes and 26 known regressions,
zero unexpected failures/skips. Strict summary and all 51 Python helpers pass.
Fresh Windows Clang coverage: 87.8% lines (15,980/18,207),
93.9% functions (1,140/1,214), 73.8% branches (9,173/12,424).
The coverage suite explicitly skips only the remaining fatal RS485 startup
regression; ASan runs it. No real source exclusion was added.

Candidate hosted run is https://github.com/petervanderwalt/Unit_tests/actions/runs/38441824483
(harness `f615275`): source, GCC ASan/UBSan, Clang ASan/UBSan, coverage and
CI diagnosis all completed successfully. Hosted GCC coverage artifact:
87.2% lines (15,076/17,283), 72.8% branches (9,774/13,422).
The automatic default-source run 38441824898 failed against upstream core
`ca26fc9`, which does not contain Terje's reviewed fixes. The explicit candidate
run above is the latest-source validation; do not restore resolved exceptions
for compatibility with that older source.

## Interpreting Terje's batch-3 failure on the newer core

https://github.com/grblHAL/Unit_tests/actions/runs/38467440282 selected Terje
`50055a2` with upstream harness `36e248d` (batch 3). Its GCC diagnostic artifact
contains 24 failures: 15 `known_changed` findings from verified fixed regressions
whose exceptions were obsolete, and 9 ordinary failures from G5.1/G70 parsing
and named-motion parameter encoding. The artifact reports 2,436 cases,
2,401 clean passes, 11 reproduced known regressions and 24 failures.

Merged PR #8 removes those 15 obsolete exceptions and retains the nine correct
failing regressions with dated, explicit known-bug classification. This follow-up
adds the maintainer notes and clearer failure reporting. The same-source run
38514474774 passes GCC, Clang, coverage and diagnosis; it does not claim those
remaining firmware defects are fixed. Deferred analog/percent-status issues
remain labelled; diameter-mode offset conventions are tracked as a design review.

Standalone maintainer-follow-up run 38519491021 passed source, GCC/Clang
sanitizers, coverage and diagnosis: 2,436 cases, 2,416 clean passes, 20 labelled
known regressions, zero failures/skips. The reporting follow-up is verified
against the captured GCC artifact from run 38467440282: its summary now states
9 unexpected failures and 15 changed known-defect exceptions separately, and
shows all nine unexpected failures before the first changed-exception detail.
All 41 Python helpers pass, including the original-run ordering regression.
## Batch 4 RTCP and wall-plotter validation

Candidate run: https://github.com/petervanderwalt/Unit_tests/actions/runs/38514474774
Harness `5835fda`, Terje source `50055a283328c3f9726bbc8f22d20a801190c66e`,
comparison baseline `d216287a6cf1f9ec278a92ac403c30a8cf5fad3b`.
Source, GCC ASan/UBSan, Clang ASan/UBSan, coverage and CI diagnosis all passed.
Local full suite and strict summary: 2,453 cases, 2,433 clean passes and 20
known regressions; no unexpected failures/skips. All 40 Python helpers pass.

Fresh hosted GCC coverage: 87.1% lines (15,064/17,287),
72.8% branches (9,780/13,434). RTCP improves from 88.9% to 96.2% lines,
and 71.2% to 92.4% branches. Total denominators and exercised parser paths also
change with the selected core refactor; these totals are not a test-only delta.
Seventeen focused cases were added, fifteen fixed allowances removed, and
remaining motion-refactor failures are documented with correct expectations.
Production source and registry defaults are unchanged.

## Sustained batch 4 storage/filesystem checkpoint

On Terje `50055a2`, local Clang ASan/UBSan and strict summary pass 2,514 cases:
2,486 clean passes, 28 known regressions, zero unexpected failures/skips.
All 48 Python helpers pass. This adds 61 cases beyond the first batch-4 checkpoint:
26 storage, four buffered tools and 31 filesystem/path/resource cases.
The long-filename static-buffer fault has an exact local ASan reproducer and
wrapper; its real Linux diagnostic and directory realloc-failure leak behavior
still require hosted verification. No production source change or exclusion.
Maintainer compatibility/reporting follow-ups are separately reviewed in PR #9.

## Batch 5 latest-core validation

2026-10-14, Terje core `39a69a22c72283ab186133b25fb89b8f5be35767`, untouched.
Full Windows Clang ASan/UBSan and strict summary: 2,555 tests, 2,544 clean
passes, 11 documented known regressions, zero unexpected failures/skips.
All 51 Python helpers and both workflow actionlint checks pass.

102 new firmware cases cover NVS retries/default diagnostic maps, buffered tools,
filesystem routing/resource failures, debug UART/external hooks and parser
axis-command conflicts. Eighteen obsolete exceptions and four resolved bug
entries were removed after the same-source hosted run 38528865145 and local
ordinary regressions confirmed the fixes. Correct assertions remain.

Run 38521365384 verified the long-filename diagnostic matcher on Linux GCC and
Clang, and exposed the failed-directory-realloc leak. Its portable ownership
regression now reclaims leaked fixture memory before asserting and is narrowly
classified, preserving visibility of unrelated sanitizer failures.

Harness push/PR triggers are temporarily disabled by user request. Manual runs
accept owner/repo or a GitHub repository URL; reusable source callers remain.
Hosted validation for this final batch is pending delivery; no fresh coverage
percentage is claimed from the local sanitizer checks.

Hosted batch-5 run [38530893125](https://github.com/petervanderwalt/Unit_tests/actions/runs/38530893125)
passed source resolution, GCC/Clang ASan/UBSan, coverage and diagnosis on the
exact `39a69a2` candidate. It used the full GitHub repository URL input. GCC
coverage reports 87.9% lines (15,289/17,396), 73.7% branches. PR #10 merged.

## Batch 6 storage, stream and executing-mode checkpoint

Terje `39a69a22c72283ab186133b25fb89b8f5be35767`, production source unchanged.
63 new maintainable cases; full Windows Clang ASan/UBSan and strict summary pass
2,618 cases: 2,606 clean, twelve known regressions, zero failures/skips.
All 51 Python helpers and workflow actionlint pass. Hosted validation pending.

PLANNER_ADD_MOTION_MODE tests execute rapid/linear/arc motion with real planner
and stepper code. They verify endpoints, block mode retention, reports during
execution and realtime notification when executing mode changes independently
of parser state. A complete report fixture initialization is required; initial
fixture crashes were resolved without changing production code or classifying
those missing hooks as defects.

Storage initialization restores and persists valid checksums/startup lines/
coordinates/build info. Lookup priority controls expose one new stale absolute
miss result. Stream tests cover exact busy timeout, clock wrap, disconnected
callbacks, file reservation and accepted/rejected cycle-start reporting.
G70–G72 execution/reporting remains a maintainer design TODO, not a new defect.

Hosted run [38533918509](https://github.com/petervanderwalt/Unit_tests/actions/runs/38533918509)
passed GCC/Clang sanitizers, coverage and diagnosis for the first 63 batch-6
cases. GCC coverage: 88.1% lines (15,330/17,401), 74.1% branches. The subsequent
22 public homing cases pass full local ASan/UBSan and strict summary: 2,640 tests,
2,628 clean, twelve known regressions, zero failures/skips. These exercise actual
XYZ switch search/pulloff and safety rejection, plus manual references through
public ABC/UVW commands in eight-axis and remapped six-axis configurations.
No new source exclusions or production edits were made. Hosted revalidation of
the final 85-case batch is pending delivery.

## Batch 7 encoder, capabilities and PWM ramp checkpoint

Terje core `39a69a22c72283ab186133b25fb89b8f5be35767` remains unchanged and
matches remote master. Twenty-nine additional cases pass full Windows Clang
ASan/UBSan and strict summary: 2,669 tests, 2,657 clean, twelve known regressions,
zero failures/skips. All 51 Python helpers pass. Coverage/hosted validation of
this later checkpoint remains pending; no fresh percentage is claimed.

Encoder cases bind registered spindles, retain native callbacks on unbinding and
verify measured feedback independently of commanded speed. Capability cases use
real PWM precomputation and update active RPM/ramp/laser metadata. Ramp cases run
original ramp and dwell code, checking monotonic output, final PWM/state and short
wait behavior. No new exceptions, exclusions or core changes were added.

Final batch-6 run 38535569786 passed GCC/Clang, coverage and CI diagnosis;
PR #11 was marked ready after that completed verification.
