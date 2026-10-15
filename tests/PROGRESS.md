# Coverage progress and continuation handoff

Last verified: **2026-10-14**. Read this with the root `AGENTS.md` and README.
This is a snapshot, not proof that future checkouts or CI runs are unchanged.

## Batch 8 local continuation

PR #12 merged as upstream f5ba765 after run 38581963519 passed every job.
New coverage belongs on local-only coverage-batch-8, based on that merged
baseline. The completed 134-case parent batch is already upstream.
The fully merged coverage-batch-7 remote branch was also deleted after PR #12
merged. GitHub currently contains only master; batch 8 remains local-only.

Batch 8 now contains 33 committed cases before the optional pullup work.
Eight public settings cases pass focused sanitizer checks: probe flag readback,
encoder-dependent spindle tolerance, dedicated home-input inversion availability,
and fifth/sixth homing phase masks. Four public backlash-setting cases verify
live enable, distance changes, fresh zero and clearing existing compensation.
The clear regression reproduces stale compensation after its setting reads zero;
see KNOWN_BUGS.md and known_bugs.cmake. Core source is unchanged.

The default host settings callback now matches the core's initialized no-op,
installed before parser hooks capture it. The initial new backlash crashes came
from a missing fixture callback, and were fixed before checking emitted pulses.
The full working suite contains 2,794 cases: 2,777 clean passes, sixteen known
regressions reproduced, one ordinary pullup consistency failure, zero skips.
No other sanitizer diagnostic or failure occurred after the shared fixture change.
The backlash regression records 88 X pulses versus the correct 80 after clearing
its setting. A clean committed-only delivery run has not yet been made for batch 8. The separate eight pullup cases/variant
remain uncommitted with one ordinary failure pending mode clarification.

The settings audit found disconnected availability branches: safety-door delay
and auto-report metadata have NULL availability callbacks, and timezone metadata
is commented out. Do not manufacture calls to private predicates just to count
those branches as covered. Test supported public behavior; preserve these source
coverage gaps and review unreachable code separately with the maintainer.

## Batch 7 review checkpoint

`coverage-batch-7` is the completed 134-case PR #12 review checkpoint. Core under test:
Terje 39a69a22c72283ab186133b25fb89b8f5be35767, production source untouched.
Hosted checkpoint 38577228353 (5d76de0) passed GCC/Clang/coverage/diagnosis.
Fresh GCC coverage: 89.2% lines (15,526/17,401), 75.3% branches
(10,138/13,464). grbllib startup/scheduler coverage is now 82.7% lines
and 68.7% branches. Later local additions have not refreshed these measurements.

102 new cases since batch 6: I/O registration, encoder/capability/ramp behavior,
stream lifecycle/allocation controls, kinematics hooks, fallback filesystem metadata,
startup homing-switch wiring and automatic status-report scheduling. The latest full local
ASan/UBSan and strict summary passes 2,742 cases: 2,727 clean, fifteen known,
zero unexpected failures/skips. All 56 Python helpers pass.

New wall-plotter regression: after initialized/started setup with valid cable
lengths, a junction-deviation update resets Y from 18,500 to 16,000. Initialization
and RTCP setting controls pass; the entry/exception preserves the correct result.

Hosted run 38573081867 exposed allocation-fixture interference with gcov runtime
allocations at process exit. Observation/injection is now disabled after each
connection operation. Four targeted tests pass in ASan and a fresh instrumented
coverage build; the fatal case skips in coverage as documented. This fix changes
fixtures only, not the core assertion/exception. The earlier Linux GCC/Clang jobs passed the diagnostic matcher. Corrected
checkpoint 52f726c run 38575541143 passed coverage: 88.9% lines
(15,473/17,401), 75.0% branches (10,101/13,464). Its GCC/Clang jobs
and diagnosis all passed. The subsequent 26 filesystem/startup cases
also passed hosted run 38577228353. Do not claim a fresh
coverage percentage from the local sanitizer checks.

PR #11 merged as upstream f58c92d. Batch 7 includes that baseline; its PR
contains only the subsequent 134 tests. Keep the full-coverage goal active and continue
from real remaining gaps after hosted verification.


## Uncommitted I/O continuation

Eight executable AUX_SETTINGS_PULLUP cases and its host variant are being
validated. Seven pass; live/load pullup-disable consistency fails because live
configuration chooses PullMode_Down and loaded configuration chooses PullMode_None.
This remains an ordinary failing test, with no new exception or known-bug entry.
The intended mode is awaiting human clarification. Automatic approval review
rejected changing mode assertions and adding an exception without that contract.
Keep these changes isolated from delivery until clarified.

Five independent input/output inversion controls pass focused sanitizer checks:
clearing masks, repeated values and PWM/servo exclusion. The full delivered
checkpoint remains 2,742 cases; do not call the pending working tree fully green.

Two IRQ callback controls and six scheduler deadline/cancellation/startup controls
also pass. The current full working-tree run has 2,763 cases: 2,747 clean passes,
fifteen known regressions and exactly one unresolved pull-mode consistency failure.
No sanitizer diagnostic was introduced. There are 134 committed cases since batch 6,
plus the eight uncommitted pullup cases/variant. The fixture preserves the core
default IRQ callback across mocked driver initialization; all 68 boot tests pass.

Eight further motion cases pass all 65 motion-control tests and strict diagnostic
summary: clockwise/counterclockwise two-turn circles, a two-turn helix, geometry
and one-time travel-limit callbacks in all planes, plus disabled-limit bypass.
The callback fixture enables actual soft limits/homing and a valid envelope;
otherwise the parser intentionally marks targets prevalidated. Independent
step pulses and physical endpoints verify execution, not just parser acceptance.
The current configured suite contains 2,771 cases; a new full run has not yet been
performed after these eight additions. The unresolved pull-mode failure remains
ordinary and uncommitted.

## Batch 6 active work

PR #10 merged; new coverage belongs on `coverage-batch-6` based on `5019b8f`.
Hosted run 38530893125 passed GCC/Clang ASan/UBSan, coverage and diagnosis on
Terje `39a69a22c72283ab186133b25fb89b8f5be35767`. Fresh GCC coverage:
87.9% lines (15,289/17,396), 73.7% branches. The core remains untouched.

The first 63 new cases are validated: eight storage initialization, fourteen VFS lookup/
default-backend, nine drive-format/free-space, twenty-one stream-state/reporting,
ten executing-motion-mode and one weak-debug-hook case. The absolute-miss stale
filename regression has a narrow known exception and passing controls.

Full Windows Clang ASan/UBSan and strict summary pass 2,618 cases: 2,606 clean
passes, twelve known regressions, zero unexpected failures/skips. All 51 Python
helpers and workflow actionlint pass. Hosted run 38533918509 passed GCC/Clang/coverage/diagnosis for that 63-case
checkpoint; fresh GCC coverage is 88.1% lines (15,330/17,401), 74.1% branches.
A further 22 public homing cases pass full local validation: 2,640 tests,
2,628 clean, twelve known regressions, zero unexpected failures/skips.
G70–G72 reporting remains an undecided contract in TODO.

## Batch 5 continuation

PRs #8 and #9 have merged. `coverage-batch-5` retains the 61 storage,
filesystem and tool cases that followed the merged batch-4 checkpoint, plus
new debug feature variants and parser error-path tests. Core remains unmodified.

The 50055a2 checkpoint passed 2,541 Windows sanitizer cases: 2,512 clean,
29 known regressions, zero unexpected failures/skips. Linux GCC/Clang from run
38521365384 exposed a failed-realloc directory leak. Its regression now checks
ownership portably, reclaims a leaked fixture allocation before asserting, and
has a dated narrow exception. The long-filename wrapper was accepted by both
hosted sanitizer jobs; unrelated leak diagnostics correctly failed classification.

The user requested temporary manual-only harness CI and support for both
owner/repo and GitHub repository URLs. Reusable callers remain available.
All 51 Python helpers and workflow actionlint pass locally.

Latest Terje core has advanced to 39a69a22c72283ab186133b25fb89b8f5be35767.
Full Windows Clang ASan/UBSan and strict summary pass: 2,555 tests, 2,544
clean passes, 11 documented known regressions, zero unexpected failures/skips.
Eighteen verified fixed parser/override exceptions and four resolved bug entries
were removed; assertions remain. The batch adds 102 cases over merged master.
Hosted GCC/Clang and coverage validation is pending publication.


## Batch 4 RTCP and wall-plotter extension

The user resumed coverage on a new branch and requested a separate PR.
`coverage-batch-4` starts from upstream `36e248d`, after PR #7 merged.
Current reviewed core is Terje `50055a283328c3f9726bbc8f22d20a801190c66e`;
production source is untouched and source-registry defaults remain unchanged.

Seventeen separate new cases cover RTCP command delegation/synchronization,
unknown-command behavior, settings persistence and corrupt-read recovery,
segment-length bounds, consecutive rotary endpoints, the thousand-segment cap,
axis-counter preservation, and wall-plotter width changes, Z interpolation,
short moves and restart after cancellation. All 36 RTCP/wall-plotter cases pass.

Full local Clang ASan/UBSan and strict summary: **2,453 tests, 2,433 clean passes,
20 documented known regressions, zero unexpected failures/skips**.
Fifteen verified fixed regressions lose their exceptions, and the final fatal
RS485 wrapper and its matcher tests are deleted; it is now an ordinary test.
All 40 remaining Python helpers pass. Existing G5.1 and G70 parser tests caught fresh
motion-enum refactor defects; ordinary named-motion values are now scaled twice.
Correct assertions remain, with dated source/reproduction/cleanup entries.

Fresh hosted GCC coverage is **87.1% lines (15,064/17,287), 72.8% branches
(9,780/13,434)**. RTCP improves from 88.9% to **96.2% lines**, and from 71.2%
to **92.4% branches**. Overall source totals also reflect the new motion-enum
refactor and its earlier parser exits; do not present old-source totals as a
like-for-like test-only comparison. The previous batch's measurements below are
historical, not new-source coverage.

Hosted candidate run: https://github.com/petervanderwalt/Unit_tests/actions/runs/38514474774
(harness `5835fda`, Terje `50055a2`, baseline `d216287`). **Source, GCC ASan/UBSan, Clang ASan/UBSan, coverage and CI diagnosis all passed.**
After delivery, continue from refreshed line/branch evidence if requested.

## Batch 3 final stopping point

The user requested closing batch 3 with a PR and stopping coverage expansion.
Latest reviewed source: Terje core `d216287a6cf1f9ec278a92ac403c30a8cf5fad3b`,
comparison baseline `e65020a8389b19d3c03277e02f34219e25800e6a`.

Full local Clang ASan/UBSan and strict summary: **2,436 tests, 2,410 clean passes,
26 documented known regressions, zero unexpected failures/skips**. All **51**
Python helper tests pass. Fresh Windows Clang coverage: **87.8% lines
(15,980/18,207), 93.9% functions (1,140/1,214), 73.8% branches (9,173/12,424)**.
Coverage has one explicit skip for the outstanding fatal RS485 startup regression;
the sanitizer suite executes it through its narrow diagnostic wrapper.

The final 32 cases exercise CoreXY travel conversion, coupled-axis homing,
feed scaling, ganging and auto-square counter preservation, reporting and resolution
callbacks. Z-only homing still resets the unrelated secondary ganged Y counter;
two regressions and a proposed guard are documented in KNOWN_BUGS.md.
Public ganging resolution warning/reset behavior is a **possible improvement**
in TODO.md, not an expected failure.

Laser assertions use planner block conditions after the parser refactor.
Delta rejection, RTCP endpoint and four named-macro lifetime regressions now pass
directly; their obsolete exceptions and two diagnostic wrappers are removed.
Earlier resolved entries stay deleted, with correct regression assertions retained.
Upstream PR #6 documentation is merged; its remaining analog-output proposal is
preserved. Source/file/exception links were rechecked after cleanup.

Hosted candidate validation (harness `f615275`, latest Terje source above):
https://github.com/petervanderwalt/Unit_tests/actions/runs/38441824483
**Completed: source, GCC ASan/UBSan, Clang ASan/UBSan, coverage and diagnosis all
passed.** Hosted GCC coverage is **87.2% lines (15,076/17,283) / 72.8% branches
(9,774/13,422)**. Its platform/compiler denominator differs from local Clang. Default upstream core `ca26fc9` lacks these Terje fixes,
so default-source runs are separate compatibility evidence, not the candidate run.
Production source and registry defaults remain unchanged.

Resume full coverage only on a new user request. Inspect fresh per-file/function
and branch evidence rather than treating this snapshot or a green suite as full
coverage. Historical checkpoints below describe earlier states.

## Batch 3 RS485 direction checkpoint

Six further separate RTU cases pass full Clang ASan/UBSan and strict summary:
**2,404 tests, 2,374 clean passes, 30 documented known regressions, no unexpected
failures/skips**. All 47 Python helper tests pass. Three cases verify explicit
first/last auxiliary direction pins and automatic selection through real
request/reply exchanges. A fourth verifies invalid-pin rejection/self-test alarm;
a fifth proves serial-owned direction works without auxiliary outputs.

The sixth reproduces a startup crash when no auxiliary outputs exist. Its exact
fault address/source/regression-origin matcher is linked from KNOWN_BUGS.md with
proposed guard and complete exception cleanup instructions. It skips only without
sanitizers; coverage now has five fatal-memory wrapper skips. The RTU fixture
initializes alarm reporting for negative startup tests and permits optional pin
description clearing. Core source is unchanged. Hosted validation of the new
wrapper is the next delivery check; do not claim its Linux matcher validated yet.

Hosted GCC, Clang, coverage and diagnosis passed the preceding 2,398-case batch:
https://github.com/petervanderwalt/Unit_tests/actions/runs/38435512145
(harness `8e4392b`, Terje core `e65020a`, baseline `4b128e`). Its GCC coverage
artifact measures **86.3% lines (14,919/17,282), 72.3% branches (9,700/13,422)**.
Keep this separate from Windows Clang's latest 2,363-case 86.5%/72.9% measurement:
compiler instrumentation and platform branches have different denominators.
Use a consistent compiler/source configuration when comparing progress.

Next: validate the new crash wrapper in both hosted compilers, then continue
remaining kinematic, parser and motion gaps. Goal stays active.

## Batch 3 allocation, reporting and motor-power checkpoint

Thirty-five further focused cases pass full Clang ASan/UBSan and strict summary:
**2,398 tests, 2,369 clean passes, 29 documented known regressions, no unexpected
failures/skips**. New cases cover string allocation failure/recovery and size
boundaries, integer-reader boundaries/cursor preservation, byte-size formatting,
spindle pulse/encoder capability reports, modal report requests, scheduled motor
release/cancellation/enable delay/homing, and the default virtual root filesystem.
No new known-bug allowances were required. The allocation fixture wraps only
`realloc` in the three specific failure tests; production functions remain linked.

The completed 2,363-case measurement is **86.5% lines (15,757/18,206),
91.8% functions (1,115/1,214), 72.9% branches (9,061/12,424)**. Later 35 cases
have not yet been merged into a refreshed measurement. Four fatal-memory wrappers
skip only in coverage mode and run under sanitizers.

Hosted GCC, Clang, coverage and diagnosis all passed the preceding checkpoint:
https://github.com/petervanderwalt/Unit_tests/actions/runs/38433324502
(harness `01a5df6`, Terje core `e65020a`, baseline `4b128e`). Next inspect the
Modbus RTU auxiliary RS485-direction path, remaining kinematic callbacks and
parser/motion configuration gaps. Goal remains active; do not modify core source.

## Batch 3 parser startup and cutter restoration

Eleven further cases pass full sanitizers and strict summary: **2,363 tests,
2,334 clean passes, 29 known regressions, no unexpected failures/skips**.
They cover direct compensation restoration (side/radius and cancellation), cold
saved-tool restoration with and without a tool table, unavailable-tool fallback,
persistence disabled, warm stop versus reset, saved G92 versus volatile G92 and
parser-init callback ordering. No new exceptions or production core changes.
Latest coverage remains the 2,337-case measurement below; 26 later cases are not
yet included. Refresh coverage at the next substantial boundary and continue
remaining parser/motion/configuration gaps.

## Batch 3 modal and multiple-probe extension

Twelve further cases pass full Windows Clang ASan/UBSan validation:
**2,352 tests, 2,323 clean passes, 29 documented known regressions, no unexpected
failures/skips**; strict summary passes. New cases cover dynamic/static cutter
compensation parameter values, lathe diameter/radius mode, runtime tool selection
and pocket identity, UVW offsets, rotary-unit preservation, three-input probe
state aggregation and extended realtime probe/release indicators.

Four new regression cases document cancelled dynamic compensation reporting 401,
aggregate probe reads changing the selected probe and aggregate reads ignoring
independent toolsetter inversion. Correct assertions and passing controls remain;
no production core edits. Latest measured coverage remains the 2,337-case snapshot
below; these twelve subsequent cases and the three later spindle cases are not
included in that measurement.

Hosted GCC, Clang, coverage and diagnosis passed for the preceding pushed
2,340-case checkpoint:
https://github.com/petervanderwalt/Unit_tests/actions/runs/38430798382
(harness `31fd05b`, Terje source `e65020a`, baseline `4b128e`). Continue parser, motion and configuration gaps. Deliver further substantial
batches without pushing after every few cases. These extensions belong on the same coverage branch; goal is active.

## Batch 3 reporting and parameter checkpoint

Branch `coverage-batch-3`, unchanged Terje core `e65020a8389b19d3c03277e02f34219e25800e6a`.
The reporting/parameter extension adds 38 separate cases: real cycle/probe status,
plugin settings channel availability, lathe modal text, dimensionless scaling
reports, string reallocation preservation, persisted inactive work offsets,
coordinate-system parameters, setting metadata and numerical motion parameters.
Full Clang ASan/UBSan: **2,340 tests, 2,315 clean passes, 25 documented known
regressions, zero unexpected failures/skips**. Strict summary and all 40 Python
helper tests pass. Newly reproduced report/parameter defects and cleanup guidance
are in KNOWN_BUGS.md; original expected correct assertions remain.

The earlier 2,302-test checkpoint passed hosted GCC, Clang, coverage and diagnosis:
https://github.com/petervanderwalt/Unit_tests/actions/runs/38426592992
(harness `bcafe18`, source `e65020a`). The first hosted attempt found a Linux
printf type mismatch in test diagnostics; portable casts fixed it before this
successful run. This hosted result does not validate later unpushed cases.

Latest completed coverage snapshot, at 2,337 tests: **86.2% lines
(15,689/18,206), 91.8% functions (1,114/1,214), 72.4% branches
(8,997/12,424)**. Three subsequent spindle listing cases pass focused and full sanitizer
validation and are not included in that measurement. Next examine spindle capability reports,
then remaining parser/motion gaps. Goal remains active.

## Batch 3: Terje core and modal/storage/filesystem paths

Current coverage branch: `coverage-batch-3`, based on upstream master after PR #5
merged. Candidate source: `terjeio/grblHAL_core` master resolved to
`e65020a8389b19d3c03277e02f34219e25800e6a` on 2026-10-13. The ordinary ignored
core checkout was updated without production-source edits; no default registry
pin or submodule was introduced.

Added 48 new focused cases and restored/revalidated 12 archived parser cases.
New coverage includes nested automatic modal restoration, M71 cancellation,
spindle/coolant/feed behavior, tool persistence failure and volatile/no-storage
writes, embedded seek bounds/recovery, CAN settings/queue/fallback behavior,
polar path segmentation/angle continuity/cancellation, lathe tool geometry,
numbered tool/scaling/work parameters, and the new virtual-parameter API including
allocation failure. The two preserved unfinished modal cases are corrected and
included; G93 saves an explicit per-block F word. VFS close verifies close-before-
notification ordering and the correct filesystem pointer. Plain G71/G72 tests
verify plugin dispatch; roughing geometry stays TODO.

Terje fixed six documented issues: century leap, VFS close, embedded seek,
three-register Modbus, dynamic laser power and empty tool identities. Thirteen
obsolete allowances, their resolved entries and two obsolete diagnostic wrappers
were removed. Embedded macro return now matches only the outstanding subroutine
callback lifetime defect. Correct regression assertions remain.

New confirmed M72 override-control regression and its passing direct-restore
control are in KNOWN_BUGS.md. The archived unexpected-file-marker defect is also
restored and reconfirmed. Full Windows Clang ASan/UBSan run: **2,302 tests,
2,293 clean passes, nine known regressions, zero unexpected failures/skips**;
strict summary passes. All 40 remaining Python helper tests pass. Fresh coverage includes every new case: **85.9% lines (15,637/18,206),
91.7% functions (1,113/1,214), 72.1% branches (8,954/12,424)**. CAN reaches
all 61 executable lines and all measured branches. Polar reaches 125/136 lines;
remaining gaps are its unfinished homing/limit callbacks. Coverage-mode tests
pass with four explicitly skipped fatal-memory regressions that require ASan;
the sanitizer run executes and classifies all four. No sources are excluded to
inflate coverage. Old snapshots below use older source revisions.

Next: use the fresh coverage gaps to expand realtime reporting and repeated/plugin
settings reports, then additional parser/motion paths. The 12 archived parser
cases have been restored; the verified Git bundle remains under
`../branch-cleanup-backup-20261013/unit-tests-all-branches.bundle` for recovery.
Do not restore obsolete fixture/exception changes wholesale. Coverage work is
active on this branch; the CI/source-update sections below are historical.

## October 13 compatibility follow-up

Earlier CI/source-update work paused coverage expansion. Its
follow-up branch was `ci-terje-fix-validation`, based on merged upstream `63323b5`.
It tests Terje's core `4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa` without changing
core source. Tool callback, check-mode, task startup and settings fixtures are
adapted. Resolved exceptions and bug entries are removed; correct assertions stay.
Remaining core regressions are documented in KNOWN_BUGS.md. See ci/VALIDATION.md
for the final verification result: 2,242 tests, 2,221 clean passes and 21
documented known regressions; zero unexpected failures under Windows Clang sanitizers.
Hosted GCC, Clang and coverage passed in run 38367839505 on harness `90c890d`. The coverage percentages below remain historical;
this compatibility run does not establish a new coverage percentage.
The two untracked modal-restore coverage cases remain unfinished and unstaged.

## Current delivery preference

The user revoked one-commit-per-test on 2026-10-12. Keep separate maintainable
case files, but commit meaningful related test batches. Focused checks precede
batch commits; full sanitizer/summary and CI checks happen at substantial push
boundaries. Do useful coverage work while CI runs rather than repeatedly polling.

## Current baseline

- Repository: https://github.com/petervanderwalt/Unit_tests, branch `master`.
- Latest verified committed/pushed revision: `d7c588316ae697213001164b1c411c3b8051c544` (prior delivery).
- Core pin: `451a539c6ed0f00499b8b48258f9aa7971fac384` from
  https://github.com/grblHAL/core. Core has not been patched locally.
- Full Windows Clang ASan/UBSan run: **2,219 tests**; **2,117 clean passes**,
  **46 passes with known sanitizer diagnostics**, **56 known regressions**,
  **0 unexpected failures**, **0 skipped**. The summary check passed too.
- Latest verified GitHub Actions run:
  https://github.com/petervanderwalt/Unit_tests/actions/runs/38290580195
  at `d7c5883`, all three jobs completed successfully. CI platform/compiler diagnostic counts
  can differ; inspect actual results instead of assuming Windows totals.
- Latest fresh merged coverage at the `b670a6f` code snapshot / 2,164 tests:
  **82.4% lines (14,985/18,178)**, **86.6% functions (1,041/1,202)**,
  **69.4% branches (8,586/12,365)** across 52 core C source files.
  Source denominators stayed unchanged. Built in a new directory to avoid old
  execution counts; merge completed with exit 0. Logs/output:
  `filesystem-fresh-coverage-summary.log`, `filesystem-fresh-coverage.json`.
  The newer 22 probe/I/O/NGC, 17 Modbus and 16 secondary-stepper tests are not included in this measurement.
- New batch through `6e7cebe`: ten probe tests exercise registered IRQ callbacks,
  latching/inversion, protection signals, fallback polling, connection events,
  per-probe trigger queries and interrupt teardown/rearm order; five I/O cases
  cover legacy assignment contracts, explicit-claim capabilities and settings
  readback; seven numbered NGC parameter cases cover probe coordinates/results,
  M66, stored G28/G30, work-system selection and G92 suspend/restore.
  Full sanitizer/strict summary passed at 2,186 cases:
  `probe-io-ngc-tests.log` and `probe-io-ngc-summary.log`.
  Missing-pin fixture corrected in `16f904f`: index 255 was invalid; the test
  now models a driver returning no pin for valid port 0. No exception added.
  G92 restoration explicitly disables volatile G92 storage in its fixture.
- Modbus RTU expanded by seventeen cases through `637bd4e`: queue flush preserves
  active transactions, resets chain driver hooks and clean up abort callbacks,
  stream readiness, baud/timeout persistence, synchronous timeout/CRC retries
  and exhaustion, serial framing, statistics/reset command, plugin reporting,
  unavailable format and blocking-event asynchronous dispatch. Full sanitizer
  and strict summary passed at 2,203 cases: `modbus-expanded-tests.log` and
  `modbus-expanded-summary.log`. The RTU blocking fixture bounds realtime polls
  and injects bytes through the actual stream; it does not emulate the protocol.
  RTU hooks are installed before initialization and reporting has an explicit
  connected-stream callback. Next substantial module: stepper2 reset, stop and
  motor callbacks, preserving existing correct known finite-motion regression.
- Secondary stepper batch through `45f77f5` adds sixteen cases: reset/stop,
  delayed foreground callbacks, settings reconfiguration, initialization failure,
  continuous speed/reverse motion, actual captured timer IRQ/rearm/stop and
  polling fallback, plus five eight-axis spindle-binding/metadata cases.
  Full sanitizer and strict summary passed at 2,219 cases:
  `secondary-expanded-tests.log` and `secondary-expanded-summary.log`.
  Explicit acceleration 36,000 is used for bounded continuous-motion tests;
  the generic host's 100 setting requires thousands of steps to reach cruise.
  The original correct finite-move overshoot regression is unchanged.
  Timer callbacks simulate IRQ delivery through captured HAL configuration,
  without duplicating motor state transitions. Next: auto-squaring homing
  pull-off workflows via `limits_pull_off()` and the existing homing fixture.
- Fresh largest remaining gaps: gcode 501 lines, settings 211, report 172,
  Modbus RTU 144, stepper2 139, motion control 128, machine limits 125,
  NGC flow control 123. Untouched functions are aggregated across variants.
  Next: auto-squaring homing pull-off and remaining limit workflows; Modbus has
  since received the batch above. Existing RTU fixture's reset
  callback must be non-NULL before RTU wraps it. No active coverage process.
- Expanded filesystem batch through `b670a6f` adds seven embedded filesystem
  tests (directory/list registration, hidden file visibility, storage totals,
  relative reads and read-only mutation protection) and six device tests
  (receive counts/EOF, claim retry/reuse, independent UART/Bluetooth ownership,
  registration prerequisites and unsupported directory operations).
  Full sanitizers plus strict summary passed at 2,164 cases:
  `filesystem-expanded-tests.log` and `filesystem-expanded-summary.log`.
- RAM filesystem batch adds nine separately committed tests through `9064721`:
  rename content preservation/errors, truncate-to-zero, open-handle deletion,
  directory enumeration/EOF, storage accounting after head/middle deletion,
  driver memory reporting, empty reset callback chaining, and flat-directory
  rejection. Full sanitizer and strict summary passed: `ram-final-tests.log`
  and `ram-final-summary.log`. RAM deletion tests explicitly make the mount
  visible because the default hidden mount rejects public mutations.
  Populated reset confirmed a stale-list use-after-free: regression `6d25ee7`
  and narrow wrapper/docs `2769903` retain safe reset/reuse assertions. Details
  and exact cleanup are in KNOWN_BUGS.md. Full sanitizer and strict summary
  passed at 2,151 cases: `ram-reset-full-tests.log` and
  `ram-reset-full-summary.log`. Prior pushed batch CI run `38287310214` at
  `f930f38` completed successfully in all three jobs.
- The prior delivery added 17 `acceleration_profiles` cases through `9501ee1`:
  G187 P1-P5 scaling of actual planned moves, validation, initialization,
  program-end resets, same-block selection and preservation of queued moves.
  Full sanitizer suite and strict summary passed; evidence:
  `acceleration-summary.log` and `acceleration-tests.log`.
- Rejected G187 commands change modal acceleration before unused-word validation.
  Two correct regressions demonstrate changed state and slower following motion;
  dated source links and exact cleanup instructions are in KNOWN_BUGS.md.
- The cutter-compensation delivery passed all three CI jobs at `3941003`.
- The jerk delivery added 23 cases through `2448c9d`: jerk ramp regimes and
  boundaries, axis limits, jog/system/synchronized exclusions, real stepper
  pulse endpoints, settings conversion/initialization/overrides, hold/resume
  and jerk combined with G187 profiles. Full sanitizers and strict summary
  passed: `jerk-feature-tests.log` and `jerk-feature-summary.log`.
  Two negative-motion tests reproduce the existing documented gcode.c numeric
  cast diagnostic; no new exception or weakened assertion was added.
- The rotation delivery added 15 rotation cases through `0f611a8`: XY/ZX/YZ
  plane transformations, normal-axis preservation, angle direction/zero,
  G53, actual motor pulses, persisted G10 rotation, reports/NGC parameters,
  absolute omitted axes and incremental explicit-zero controls.
  Full sanitizers and strict summary passed: `rotation-feature-tests.log`
  and `rotation-feature-summary.log`.
- A confirmed rotation defect adds unwanted movement for omitted incremental
  axes: after a 90-degree G55 move to local X3/Y4, G91 X2 reaches machine
  X=-8/Y=5 instead of X=-4/Y=5. Actual driver pulse regression independently
  confirms 640 instead of 320 negative X pulses. Exact cleanup links and
  dated source anchors are in KNOWN_BUGS.md; correct assertions are preserved.
- The spindle-sync delivery added 16 spindle-sync cases through `c587f8c`: encoder
  capability/PPR, settings hook forwarding and real initialization, synchronized
  Z pulse endpoints, handler reset/normal-block restoration, G95 bypass,
  two-index startup, missing-index/zero-RPM alarms, stop/reset before wakeup,
  and cruising angular feedback with configured PID. Full sanitizers and strict
  summary passed: `spindle-sync-feature-tests.log` and
  `spindle-sync-feature-summary.log`; all 16 additions passed cleanly.
- The jog/laser delivery added 14 motion-control cases through `8abf6ff`:
  real jog commands/driver pulses, temporary inch/incremental modal settings,
  feed-override suppression, queued targets, zero distance, soft-limit rejection
  and clipping; coincident M3/M4/off/nonlaser/check-mode behavior and a power
  update proven to occur only after the queued move emits all 80 X pulses.
  Full sanitizers and strict summary passed: `jog-laser-tests.log` and
  `jog-laser-summary.log`. The two negative-jog cases reproduce the existing
  documented numeric-cast diagnostic; no new exception was introduced.
- The prior delivery added 19 settings cases through `6285797`: per-axis homing
  rates/availability, auto-square offsets/availability, acceleration/travel
  conversion, persistent reload and probe/limit/parking/PWM option readback.
- Eight toolsetter workflow cases through `e03837d` exercise G59.3 positioning,
  G30 return, actual seek/locate/release probing, first/existing reference,
  travel clipping, failure cleanup and restore options. A pulse callback
  verifies XY motion occurs at retracted Z. Tool-change baseline before this
  batch was 202/343 lines (58.9%); the completed refresh measured 284/343 (82.8%).
- Full sanitizer suite and strict summary passed for all 2,132 cases:
  `settings-toolsetter-tests.log`, `settings-toolsetter-summary.log`.
- Current delivery adds nine modal-report tests through `eb3d407`: actual
  M0/M1/M2/M30 callbacks, override-disable states and actual pending manual M6.
  The parser resets program flow after callbacks, so reporting is observed
  from the real callback before that intentional reset.
- User clarified that plain G71/G72 is pending implementation, not a failure.
  Its entry moved from KNOWN_BUGS.md to TODO.md (linked in README). Both cases
  now pass by checking current rejection, no plugin dispatch and no position
  change; their expected-failure labels are removed. Fractional controls remain.
- Full suite plus strict summary passed after this correction:
  `modal-report-todo-tests.log` and `modal-report-todo-summary.log`.
- No coverage process remains active; session 51685 completed successfully.
  Temporary root `.gcov` files must not be committed or removed during a merge.
- The five value-helper and four initial file tool cases were delivered at
  `8f74f64` and passed CI. The combined host has NGC expressions and N_TOOLS=4.
- The 14 restore/probe-getter cases were delivered at `5470584` and passed CI.
- The nine feedback/soft-limit cases were delivered at `746fa1a` and passed CI.
- The 18 report cases were delivered at `4850815` and passed CI.
- The 16 protocol cases were delivered at `a4293fb` and passed CI.

The handoff documents were committed and pushed as `e88cceb`; the earlier
no-push restriction was lifted by the user's explicit commit/push request.
The full coverage goal was explicitly re-established on 2026-10-12.

## Next work

1. Read the completed settings/toolsetter coverage refresh before selecting new gaps. Prior measured gaps: settings 240 executable lines, motion control 152,
   G-code 521, report 187. Protocol is now below
   150 uncovered lines. Read the JSON for exact remaining line/branch targets.
   Current settings ranges worth inspecting include 1032-1038 (now covered by
   new soft-limit tests), 3050-3056 (plugin restore callbacks, now exercised), 1728-1733 (probe
   inversion getters, now exercised), and numeric/string formatting paths
   (decimal/string/IP callback paths now have tests too).
2. Combined NGC/tool-table file execution now checks M61 deferred-offset
   application, explicit G43/G49 precedence and no pending offset. Candidate
   M6 deferred offsets, M61 completion and validation cleanup now have tests.
   LATHE_UVW_OPTION with NGC expressions is now compiled and tested under
   `lathe_ngc`. `lathe_cycle_capture_host.h` captures a plugin replacement
   interface; it deliberately does not implement roughing geometry.
   CUTTER_COMP_ENABLE is now compiled with a configuration-capturing weak
   plugin replacement. It verifies core parsing/state and transfer of parameters,
   not compensated geometry. Further candidates: tool D0/current-tool radius,
   pre-execution hooks, cancellation modes and compound motion restrictions.
   ENABLE_ACCELERATION_PROFILES=1 and ENABLE_JERK_ACCELERATION=1 now have
   standalone and combined host configurations. Remaining candidates include
   jerk feed overrides/queued transitions, more rotation offset/arc contracts, and
   additional spindle-sync PID disturbance/timer-bound and threading execution contracts.
   SPINDLE_SYNC_ENABLE now has a measured-feedback execution host. ENABLE_PATH_BLENDING is explicitly unfinished in config.h;
   do not invent a supported contract for it.
   Use `ngc_tool_file_host.h`; settings initialization must install a valid
   settings-changed callback before reinitializing the parser.

   CSS inward travel, nonzero start, G92 offsets, alternative plane and stopped/
   zero-speed rejection have passing tests. Remaining candidates include tool
   offsets, RPM mode transitions and coordinated queue behavior. Read parser
   synchronization before assuming multiple CSS moves remain queued.
3. Investigate whether consecutive queued CSS blocks can overwrite another
   block's interpolation data. `planner.c` copies `spindle_t`, which contains a
   pointer to CSS data; it writes target/delta RPM through that pointer. This is
   **only a hypothesis**, not a confirmed bug. Parser synchronization may drain
   the queue. Establish a valid startup/control and reproducible contract before
   adding any exception or known-bug entry.
4. Use fresh gaps to tackle the large remaining sources and configurations.
   From the latest coverage snapshot, uncovered executable lines included:
   `gcode.c` 466, `settings.c` 261, `report.c` 190,
   `motion_control.c` 152. These are starting hints, not current measurements.
5. Expand supported feature configurations where source guards remain uncovered.
   Preserve genuine hardware/contract limitations explicitly; do not silently
   redefine 100% as whichever configuration is easiest to cover.

## Recent work already completed

- Delay settings: spindle on/off conversion, minimum/maximum limits, coolant
  capability, at-speed tolerance and filesystem-dependent subroutine options.
- MPG settings: baud selection mapping, invalid selection, driver rejection and
  capability gating using the runtime registered stream.
- CSS planner: start/target/delta RPM, zero and negative radius and RPM clamping.
- CSS real stepper: outward movement reduces PWM monotonically, negative radius
  retains maximum output, axial movement at zero radius retains maximum output;
  emitted axis steps are checked.
- Laser parser/stepper, delta API/homing/limits, tool table, settings-file hooks,
  program completion, thread planning and system metadata batches were delivered.
- All 24 Markdown core source links in `KNOWN_BUGS.md` now use the pinned upstream
  revision instead of broken relative submodule paths.
- README now explains core pin updates, exact exception cleanup, keeping tests
  and deleting resolved known-bug sections.

Useful fixtures for continuing:

- `tests/support/laser_program_host.h`: `prepare_pwm_program_mode(mode, check)`
  initializes a real registered PWM spindle before parser startup. Laser wrapper
  remains available; output state and PWM calls are captured.
- `tests/support/laser_stepper_host.h`: `prepare_pwm_stepper_mode(mode)` plus
  `execute_motion_program()` from `motion_program_host.h` executes real segments
  and captures axis pulses. Avoid assuming unchanged PWM triggers a new write.
- `tests/support/css_host.h`: check-mode CSS parser fixture; its output callback
  expects spindle off, so it is unsuitable for real running CSS output tests.
- `sync_parser_host.h` / `thread_plan_host.h`: measured encoder feedback and
  actual threading planner capture, with check-mode versus execution differences.
- `settings_file_host.h`, `parser_settings_host.h`, `mpg_settings_host.h`,
  `system_metadata_host.h`, `delta_api_host.h`: read startup sequencing before
  reuse. CMake specifies feature routing and linker wrappers where required.

Known issues and all removal details are maintained in `tests/KNOWN_BUGS.md`,
`tests/known_bugs.cmake`, and `tests/known_sanitizer_diagnostics.json`. Do not
maintain a second defect inventory here. Recent CSS negative G-code tests can
produce the existing narrow number-conversion diagnostic; inspect the summary
rather than treating those as clean sanitizer passes.

## Local environment used for the verified runs

These paths are machine-specific conveniences, not portable requirements:

- Workspace: `C:/Users/User/Documents/Codex/2026-10-08/https-github-com-petervanderwalt-unit-tests`
- Repository: `<workspace>/work/Unit_tests`
- Python: `C:/Python313/python.exe`
- LLVM tools: `<workspace>/work/toolchain/llvm-mingw-20261006-ucrt-x86_64/bin`
- Builds in the repository: `build-clang` (focused unsanitized cases),
  `build-asan` (full sanitizers), `build-local-coverage` (Clang coverage).
- Prepend LLVM `bin` to PowerShell `PATH` for sanitizer DLL loading.
- Local scratch scripts include `<workspace>/work/case_builder.py` (writes,
  validates and commits one case), `list_coverage_gaps.py`, and batch generators.
  They are outside Git, optional, and must be inspected before execution.
  A new agent can write cases manually with the checked-in workflow instead.
- Evidence files in scratch: `secondary-expanded-summary.log` (latest sanitizer results), `modbus-expanded-summary.log`, `probe-io-ngc-summary.log`, `filesystem-expanded-summary.log`, `ram-reset-full-summary.log`, `ram-final-summary.log`, `modal-report-todo-summary.log`, `settings-toolsetter-summary.log`, `jog-laser-summary.log`, `spindle-sync-feature-summary.log`, `rotation-feature-summary.log`, `jerk-feature-summary.log`, `acceleration-summary.log`, `cutter-feature-summary.log`, `lathe-feature-summary.log`, `ngc-file-change-summary.log`, `ngc-tools-values-summary.log`, `settings-owners-summary.log`, `feedback-soft-limits-summary.log`, `report-fields-summary.log`, `protocol-lock-summary.log`, `css-execution-summary.log`,
  `css-execution-tests.log`, `delta-laser-coverage-report.log`,
  `local-core-coverage-latest.json`. Rebuild/retest if these are missing or stale.
- Local gcovr 8.4 was installed under `<workspace>/work/coverage-python`; an
  ordinary `python -m pip install gcovr==8.4` is the portable README alternative.

For the existing Windows sanitizer build:

```powershell
$env:PATH = (Resolve-Path '../../work/toolchain/llvm-mingw-20261006-ucrt-x86_64/bin').Path + ';' + $env:PATH
cmake -S . -B build-asan
cmake --build build-asan --parallel 6
ctest --test-dir build-asan --parallel 6 --output-on-failure --output-junit results.xml
C:/Python313/python.exe scripts/summary.py tests build-asan/results.xml
```

Check each command's exit status before continuing or committing. Capture CMake
output with `*> logfile` to include stderr warnings. Windows Clang coverage used
`--gcov-executable 'llvm-cov gcov'` with the compiler directory on PATH; the
space-separated absolute Windows executable path caused parsing trouble locally.
Never remove coverage data while a merge runs. A merge can take several minutes;
continue independent work without changing headers under an active build.

The user requested pausing coverage after batch 3 delivery. No scheduled background continuation was configured. A fresh chat should read
these files, verify current state, and be explicitly asked to resume the full
coverage objective; do not assume deleting a chat schedules future execution.

## Review boundary requested by the user

On 2026-10-14 the user requested PR preparation and cleanup of branches proven
merged upstream. Finish the eleven expression cases (comparison boundaries,
operator-name rejection, signed expressions, invalid parameters and literal
format preservation) and validate the completed commits independently of the
eight uncommitted pullup cases. The mode clarification remains pending; do not
publish a new exception or describe that working tree as fully green.

Fork master 331414d has no unique commits relative to freshly fetched upstream
master 5019b8f. PR #11 remains open; packaging the next checkpoint separately or
as a combined replacement is awaiting the user's preference. Only delete remote
branches whose current tips are verified ancestors of upstream master.

## Completed batch 7 delivery validation

Clean committed checkout c5040a6 passed all 2,774 Windows Clang ASan/UBSan
cases and strict diagnostic summary: 2,759 clean, fifteen known regressions,
zero unexpected failures or skips. The upstream merge into 658d128 changes no
file contents. All 56 helper tests and actionlint pass. Source under test remains
Terje 39a69a22c72283ab186133b25fb89b8f5be35767, unchanged.

PR #11 merged; batch 7 is based on upstream f58c92d. Eight remote branches
whose current tips were verified ancestors of upstream master were deleted:
ci-actionable-reports, core-maintainer-followup, coverage-batch-3 through -6,
docs-current-ci-status and docs-known-bug-fixes. Fork master contains no unique
commits; no duplicate PR is required. Remote master and coverage-batch-7 remain.

The eight pullup cases and their optional host variant remain uncommitted and
outside this delivery, with one visible consistency failure pending human
clarification. Do not add an exception or alter the pull-mode expectations until
that contract is resolved. Hosted validation of final checkpoint 305f34f passed every job in run
38581963519. Fresh GCC coverage is 89.5% lines (15,568/17,401) and
75.6% branches (10,180/13,464). PR #12 is ready for review.

## Batch 8 reporting continuation

Eleven new realtime accessory/tool reporting cases pass: flood, mist, combined
coolant, clockwise/counterclockwise spindle, combined spindle/coolant, cleared
outputs, encoder error capability gating and distinct tool/tool-change fields.
They use the real report renderer and driver feedback callbacks, with explicit
report flags. Keep the full-coverage goal active; do not treat this module check
as complete coverage or publish a new percentage without fresh instrumentation.

## Batch 8 parameter and modal report expansion

Ten more cases pass all 219 report tests and strict diagnostic summary: parameter
extension ordering, early/partial/transient coordinate-read failure, G43.1/G49,
G92/G92.1, G51/G50 and M7/M8/M9 combinations. The modal tests execute real
parser commands in check mode and then call the real report renderer. Coordinate
fault injection starts after fixture initialization, uses the original NVS reader
for all nonfailed reads and verifies that failed reports stop before extension
callbacks. Correct assertions and existing known allowances are unchanged.

The completed committed suite now contains 2,807 cases; the working tree adds
eight pending pullup cases. These ten additions have been module-validated;
full committed-only sanitizer/hosted coverage validation remains for the next
substantial delivery boundary. Do not call the working suite fully green while
the ordinary pullup consistency failure remains unresolved.

## End-of-day snapshot, 2026-10-14

The user requested saving current work and a PR, then stopping until tomorrow.
The full-coverage goal is paused. Batch 8 has 33 completed new cases plus eight
unfinished AUX_SETTINGS_PULLUP cases saved in a separate WIP commit. Assertions
and exceptions for the unresolved pull-mode contract have not been changed.

This snapshot is for draft review, not a passing delivery. The live/load pullup
consistency case remains an ordinary failing test: live selects PullMode_Down,
loaded configuration selects PullMode_None. Resolve that contract with the human
before adjusting expectations or introducing an exception. Seven other pullup
controls pass but their mode-specific expectations also require that review.

Last full working-tree check before reporting expansion: 2,794 cases, 2,777 clean,
sixteen expected regressions and the one ordinary pullup failure. All 219 report
cases pass after the subsequent 21 additions; a latest full 2,815-case run and
clean GCC/Clang/coverage delivery remain outstanding. Keep core unchanged.

## Pullup issue classification authorized for PR #13

On 2026-10-14 the user requested documenting the pullup inconsistency as a known
issue and allowing the PR to merge after validation. Its live/load agreement
assertion is unchanged. Only that named case receives WILL_FAIL/known_bug; the
seven controls remain ordinary tests. The dated known-bug entry includes exact
source anchors, the unresolved mode choice and cleanup of mode-specific controls.
The full-coverage goal stays paused; this work completes the requested PR fix.
Full local ASan/UBSan and strict summary passed all 2,815 cases: 2,798 clean,
seventeen known regressions reproduced, zero unexpected failures/skips.
Hosted GCC/Clang/coverage validation of this classified checkpoint is pending.

## Revised goal and resumed authoring approach

Continue toward meaningful 100% grblHAL core line/branch coverage against Terje's
latest source, prioritizing supported machine workflows and observable effects.
Use coverage as gap evidence, then verify valid startup, public triggers, intended
contracts and practical consequences. Distinguish confirmed defects from fixture
errors, design questions and low-priority robustness work. Ask the maintainer when
intent is unclear; correct invalid tests. Keep core unchanged, assertions honest,
case files maintainable, and deliver substantial validated PR checkpoints.

The user requested resuming on 2026-10-14 with these guardrails. The available goal
tools cannot edit an existing objective or resume a paused goal; its stored status
still requires the user's goal control. Work may resume under the direct request.
PR #13's final run 38604749142 passed against harness 0e5034b and Terje 39a69a2;
its known pullup consistency assertion is unchanged and is narrowly classified.

## Batch 9 practical workflow continuation

PR #13 passed final hosted run 38604749142 and is ready for review. The authoring
guardrails/revised goal text were committed as a00c3bd. The user confirmed resuming
the goal. New cases belong on local-only coverage-batch-9, based on PR #13; do not
publish a duplicate PR while that parent remains unmerged.

Three secondary-spindle status cases execute supported sender commands M3/M4/M5
with $1 selection, using registered/settings-mapped spindles and the real parser,
spindle control and status renderer. Driver outputs and emitted status fields are
checked together. Stopping the secondary clears its RPM/direction report while
the primary remains on. These test practical multi-spindle workflows; they do not
claim hardware speed/timing evidence. Focused cases and the multi-spindle module
pass under sanitizers with strict diagnostic classification.

## Batch 9 secondary-spindle overrides

Three additional cases verify adjusted RPM and the secondary spindle's own
percentage, independence from primary overrides, and zero RPM after M5 while
retaining the selected override. They use supported parser commands and the
public spindle override API; they make no physical timing claims. All 67
multi-spindle cases pass under ASan/UBSan and the strict diagnostic summary.

The resumed goal is verified active. Final batch-8 hosted coverage is 15,641 of
17,402 lines (89.9%) and 10,239 of 13,464 branches (76.0%). These are the last
hosted baseline figures, not a measurement of the new local batch. Next work is
real stream-driven jog cancellation, including the driver's ASCII_CAN contract;
do not replace that stream path with a direct motion-cancel flag injection.

## Batch 9 sender jog cancellation

Four cases execute queued $J commands through protocol_main_loop and a driver
stream mock. The realtime jog-cancel command flushes input and inserts ASCII_CAN,
as required by the driver interface; the normal reader/state machine performs
controlled deceleration and planner/parser resynchronization. Real stepper ISR
calls produce counted pulses. Checks cover discarded queued motion, a subsequent
1 mm jog from the actual stopped position, reverse travel, and preservation of
program G20/G91 modes. Both initial jogs are verified queued before cancellation.
No exact deceleration time or mechanical safety claim is inferred from the host.

All four focused cases and all 69 motion-control cases pass under ASan/UBSan with
strict diagnostic classification. Evidence: build-asan/batch-9-jog-results.xml
and build-asan/batch-9-motion-results.xml. No core changes or new known defects.
The last hosted baseline has protocol at 82.0% lines/71.0% branches and state
machine at 83.2%/63.0%; these workflow cases address their cancellation lifecycle.
Batch 9 now contains ten new cases; full-suite/hosted measurement remains due at
its substantial delivery boundary. Continue from remaining state/motion gaps.

## Batch 9 held-spindle workflows

Seven additional state-machine cases use M3S5000, a real planned 20 mm move,
feed hold, realtime spindle-stop toggles and cycle start. Driver callbacks log
state/RPM and physical pulse position. They verify stopping retains programmed
state/queued motion, a second toggle restores without moving, cycle start honors
the restore setting, a stop requested during deceleration waits until hold is
complete, running-cut stop overrides are ignored, and two queued toggles cancel.
The public suspend manager is serviced as in the core's suspend loop; no private
entry points or direct override flag injection are used. Missing stream connection
callback in the initial fixture was corrected; it was not a core defect.

All 32 state-machine cases pass under ASan/UBSan with strict summary classification
(build-asan/batch-9-state-results.xml). Batch 9 now has 17 new cases. Continue
practical state/motion coverage, with a full-suite check at this local checkpoint.

## Batch 9 automatic sleep during pauses

Five new cases enable sleep, command M8 through the real parser and use planned
motion/realtime hold or safety-door events. A mock clock advances the actual core
scheduler. Sleep is requested after a completed feed hold or an open-door stopped
pause, never during hold deceleration or a closed-door pause awaiting resume.
New sender input cancels the timeout, with a later scheduler advance confirming
that the removed timeout does not fire. Pulse counts remain unchanged while
sleep is considered. All 11 sleep cases pass under sanitizers and strict summary
(build-asan/batch-9-sleep-results.xml). These address previously uncovered normal
hold/door branches in sleep.c; allocator failure remains a lower-priority gap.

The preceding 17-case checkpoint passed the full suite: 2,832 total, 2,815 clean,
17 documented regressions, no unexpected failures/skips (90.51 s), with strict
summary clean. The five subsequent sleep cases have focused validation; the
current 2,837-case suite still needs full/hosted validation at delivery. Batch 9
now has 22 new cases, local only. PR #13 remains open/ready; its head is a00c3bd.
Terje master is still 39a69a2, freshly verified. Next measured gaps include
state-machine accessory restore, supported tool-change workflows and crossbar
port capability mappings. Continue substantial coverage work before another PR.

## Batch 9 crossbar mappings

Six additional cases cover auxiliary limit/home/fault/enable signal mappings,
grouped enables, remapped UVW identities, rejection of unconfigured ABC functions
and secondary XYZ motor identity. They use the production public crossbar API in
existing eight-axis, UVW and base builds. All 50 crossbar/eight-axis/UVW cases pass
under sanitizers and strict summary (build-asan/batch-9-mapping-results.xml).
These exercise previously uncovered enabled-feature branches without changing
core or adding artificial private entry points.

## Batch 9 manual workpiece touch-off

Four $TPW cases execute the public system command after manual tool-change
acknowledgement, with registered probe input, real probe cycles and emitted pulses.
A prior reference-tool touch-off is modeled in the fixture. Cases cover double
touch-off compensation and explicit resume, fast contact-release probing, missing
contact preserving the pending change/offset, and G30 requiring return before
probing. The existing tool-change motion fixture ensures XY movement occurs only
at the retracted Z position. No hardware timing/mechanical claim is made.

Focused cases and the complete tool-change module pass under ASan/UBSan with
strict summary (build-asan/batch-9-tool-results.xml). Batch 9 now adds 32 cases;
perform full validation and a hosted checkpoint before publishing further work.

## Batch 9 first hosted checkpoint

Full ASan/UBSan suite and strict diagnostics passed: 2,847 total, 2,830 clean,
17 documented regressions reproduced, zero unexpected failures/skips (39.86 s).
Evidence: build-asan/batch-9-checkpoint-results.xml. This checkpoint adds 32 cases
against unchanged Terje 39a69a2. Push coverage-batch-9 and dispatch manual GCC,
Clang and coverage validation; continue independent local work while it runs.
PR #13 is still the unmerged parent, so do not open a duplicate PR containing it.

## Batch 9 toolsetter probe-selection lifecycle

Four further cases register separate hand-probe and fixture-probe inputs and a
valid driver/plugin toolsetter callback. Only the fixture input can trigger. The
real probe selector and tool-change workflows must select it for touch-off, then
restore the hand probe after automatic success, automatic missing contact,
manual fixture resume or a realtime reset during an acknowledged fixture change.
Reset also restores stream/control handlers without extra motion or position loss.
The fixture initially assumed cleanup always names the new tool; inspection showed
failed change cleanup correctly names the still-current tool. That fixture-only
assumption was removed; no known bug or core change was introduced.

All 53 tool-change cases pass under ASan/UBSan and strict summary
(build-asan/batch-9-hook-results.xml). Batch 9 now adds 36 cases. Its first 32-case
checkpoint is pushed as 011afe0; manual GCC/Clang/coverage run 38621381358 is
confirmed in progress. These four follow-up cases remain local until that run
finishes and another substantial validation checkpoint is appropriate. Do not
push repeatedly and cancel the running CI. PR #13 remains the unmerged parent.
Next: inspect fresh hosted coverage when available and continue remaining real
state/motion/tool-change and enabled-configuration gaps; full coverage is incomplete.

## Batch 9 hold accessory settings

Seven further cases exercise flood/mist overrides across hold/resume with
restoration enabled/disabled, reduced spindle RPM during completed hold, ordinary
hold leaving output unchanged, and a queued RPM override applied on resume after
reduced-speed hold. They command accessories through the parser and realtime
interface, log driver output transitions at actual pulse positions, and finish
the original 20 mm move without changing programmed RPM or losing position.
The coolant fixture's missing flood capability was corrected before classifying
results; no core defect was inferred from that setup error.

## Batch 9 powered safety-door parking

Four additional cases command spindle/flood before a real move and safety-door
parking. They verify accessory shutdown after the initial pullout, optional
coolant retention, restoration at the waypoint before plunge, and re-parking when
a real control_interrupt_handler door event arrives during spindle startup delay.
The original fixture was split into preparation/start helpers so accessories can
be initialized before queueing; original motion behavior is retained. A serialized
sender door command is not substituted for the physical reopen event, and the
fixture explicitly advertises the door signal capability required by the ISR.
No mechanical timing/severity claims or new core bugs are inferred.

All 43 state-machine cases pass under ASan/UBSan and strict summary
(build-asan/batch-9-powered-parking-results.xml). Batch 9 now has 47 new cases:
32 pushed in the running checkpoint and 15 subsequent local cases. The updated
2,862-case suite still needs full validation before the next push. Continue from
fresh hosted coverage when available; PR #13 remains the unmerged parent.

## Batch 9 hosted coverage and second checkpoint

Run 38621381358 passed source, GCC, Clang, coverage and CI diagnosis for harness
011afe0 against Terje 39a69a2. Fresh artifact coverage is 15,747/17,402 lines
(90.4896%) and 10,323/13,464 branches (76.6711%). Compared with batch 8 this adds
106 covered lines and 84 branches. Crossbar reaches 100% lines/91.7% branches;
sleep reaches 96.8%/83.3%, tool change 92.2%/67.1%, and state machine 88.7%/69.7%.
These measurements cover the first 32 cases, not the following 15 local cases.

The current 47-case batch checkpoint also passes the full sanitizer suite and
strict summary: 2,862 total, 2,845 clean, 17 known regressions, no unexpected
failures/skips (41.90 s; build-asan/batch-9-second-checkpoint-results.xml). Push
this completed state/motion checkpoint and run hosted validation, then continue
independent gaps. PR #13 remains open, verified from GitHub; do not merge it or
publish a duplicate upstream diff. Core remains unchanged.

## Batch 9 remaining crossbar controls

Four local follow-up cases cover dedicated-home configurations avoiding limit
fallback, servo PWM not being advertised as ADC resolution, non-UART bus groups
having no UART description, and AC-remapped motor enable/fault/limit identities.
They target the fresh crossbar branch gaps and real advertised configurations.
All 42 crossbar/RTCP cases pass under sanitizers and strict summary
(build-asan/batch-9-crossbar-controls-results.xml). Batch 9 now adds 51 cases.

The 47-case checkpoint was pushed as b583c96 and a second hosted run dispatched
only after the preceding run completed successfully. Keep these four follow-up
cases local while that run executes. The last hosted coverage remains 90.5%
lines/76.7% branches for 011afe0. New coverage is not assumed until its fresh
artifact is read. Continue the remaining measured gaps; full coverage is not done.

## Batch 9 sender spindle overrides

Five new cases use properly registered spindles, real M3S5000 and public realtime
spindle override bytes. They verify coarse/fine decreases, fine increase, resetting
a prior percentage, and ordered queued adjustments/reset producing one final
driver update. Programmed RPM remains 5000 while driver output changes. All 72
multi-spindle cases pass under ASan/UBSan and strict summary
(build-asan/batch-9-sender-spindle-results.xml). These address uncovered protocol
spindle-override switch branches without changing core.

## Batch 9 program stop lifecycle

Three new cases execute the public Ctrl-Y/CMD_STOP realtime path while real
queued motion is running or held. A host timer advances actual stepper ISR work
inside the core stop loop. Stop flushes pending planned moves/override commands,
resynchronizes parser position to emitted pulses, turns off spindle/coolant and
resets driver state. Stopping from completed hold adds no pulses. Checks distinguish
sys.cancel from abort/reset and retain valid machine position. CMD_STOP is marked
experimental in core; these test its implemented API behavior without inferring
mechanical emergency-stop suitability or changing that designation.

All 72 motion-control cases pass under ASan/UBSan and strict summary
(build-asan/batch-9-program-stop-results.xml). Batch 9 now adds 59 cases; twelve
are local follow-ups after the 47-case b583c96 hosted checkpoint. Continue remaining
measured program/state gaps while run 38623364651 finishes; avoid cancelling it.

## Batch 9 streamed macro continuation

Five registered cases read real stream bytes, honor production file rewinds and
pass normalized blocks to gc_execute_block. Ordinary WHILE/DO loops and true
WHILE CONTINUE/DO body rewind followed by a nested BREAK are passing controls.
The WHILE false-condition CONTINUE case executes a skipped assignment, then
returns error 81 at ENDWHILE. Its correct assertions are retained with one narrow
known-failure exception, a dated/source-pinned bug report and proposed cleanup.
All 60 flow-control cases pass strict classification: 59 clean, one documented
regression reproduced. Stream/control allocations are cleaned up before bounds
failure. No core changes or sanitizer suppressions.

The separate DO/WHILE CONTINUE behavior repeats without evaluating the trailing
condition. The user explicitly requested a TODO for Terje to comment on. Its
candidate is in tests/proposals, unregistered pending that contract; no test is
weakened or source excluded. Source line links were checked against current core:
DO rewind at 611-612; false WHILE frame removal at 622-627.

Batch 9 now adds 64 registered tests plus that pending proposal. Full current
2,879-case validation is due before another push. Run 38623364651 passed every
job for b583c96 (47 cases), with fresh coverage 15,772/17,402 lines (90.6333%) and
10,368/13,464 branches (77.0053%). Follow-up tests remain local. Continue actual
remaining branches; PR #13 is still the unmerged parent at last verification.

## Batch 9 third validated checkpoint

Full current ASan/UBSan suite and strict summary passed: 2,879 cases, 2,861 clean,
18 documented regressions reproduced, zero unexpected failures/skips (37.99 s).
Evidence: build-asan/batch-9-third-checkpoint-results.xml. The added WHILE
regression is narrowly expected; DO/WHILE intent stays in TODO/proposals exactly
as the user requested, pending Terje's comment. No core changes.

The preceding 47-case hosted run also passed every job. Fresh module coverage is
state machine 91.2% lines/73.6% branches, tool change 95.1%/73.1%, protocol
84.6%/74.3%; overall 90.6%/77.0%. Push this completed 64-case checkpoint and
request hosted validation; continue other source gaps while it runs. Do not
merge PR #13 or duplicate its upstream diff while it remains open.

## Batch 9 spline conversion and validation

Nine local cases cover cubic/quadratic splines in inch units and independent X/Y
scaling, connected cubic continuation without IJ, and rejection of non-XY planes,
third axes or missing control words before any motion is queued. A pulse fixture
samples a known point from independent closed-form Bezier coordinates, as well as
checking endpoints/monotonic pulse totals. This checks control-point conversions
rather than relying solely on the endpoint. Flattening/pulse rounding allowance
is explicit; no physical contour accuracy claim is made. Normal foreground timer
servicing lets larger curves fill and drain the real planner without hangs.

## Batch 9 explicit G-code probe selection

Six further cases register default/toolsetter/second probe inputs with distinct
contact positions, advertise their real HAL capabilities and execute G38 blocks
through the parser. They verify the input active at probe start, contact latch,
restoration of the previous selection, no switching for an already selected
input, rejection before motion when capability is absent, and restoration after
a no-error missed-contact probe. Real probe cycles and motor pulses are used.
The fixture's initial callback signature mismatch was corrected, not treated as
a core fault. No new failures or core changes.

Focused cases and the complete parser/motion modules pass under ASan/UBSan and
strict diagnostics (build-asan/batch-9-parser-motion-results.xml). Batch 9 now
adds 79 registered tests plus the pending DO/WHILE proposal. The 64-case hosted
run is 38625823913; these fifteen follow-ups stay local while it runs. Continue
freshly measured parser/startup/configuration gaps and perform full validation
at the next substantial checkpoint. Last measured overall coverage is 90.6%/77.0%.

## Batch 9 startup-failure task isolation

Three additional boot cases invoke real grbl_enter with driver init, setup or
pulse-delay capability failure. Valid driver/plugin callbacks queue startup,
delayed and systick work during initialization. The normal startup fault path
must discard these tasks and stay in the self-test alarm with no queued motion.
A host observer verifies three scheduler turns, advances mock time and terminates
the test only after checking state/callback counts. It does not make the core's
intentional infinite fault loop return or call private functions. A default-off
boot fixture option supplies no sender input instead of issuing CMD_EXIT.
Original startup case behavior remains unchanged.

All boot variants pass ASan/UBSan and strict summary
(build-asan/batch-9-boot-fault-results.xml). Batch 9 now adds 82 registered tests
plus the pending DO/WHILE proposal. Eighteen follow-ups after 7ed2f01 remain local;
run 38625823913 validates its 64-case checkpoint. Full current 2,897-case suite
is due before another push. Continue remaining parser/feature/startup gaps from
fresh coverage. No new bug classifications or production-core edits in this work.

## Batch 9 fourth validated checkpoint

The full 2,897-case ASan/UBSan suite and strict summary passed: 2,879 clean,
18 documented regressions, zero unexpected failures/skips (38.28 s), including
the shared boot-fixture change. Evidence: build-asan/batch-9-fourth-checkpoint-results.xml.
The root working instructions now state the active batch-9 branch/resumed goal
and protect the user's DO/WHILE TODO/proposal from accidental registration.

Run 38625823913 passed every job for 7ed2f01 against Terje 39a69a2. Fresh coverage
is 15,816/17,402 lines (90.8861%) and 10,417/13,464 branches (77.3693%). Crossbar
is 100% lines/97.9% branches, flow control 87.4%/67.2%, protocol 88.3%/76.6%.
This covers 64 cases; the current 82-case checkpoint needs hosted measurement.
Push this completed parser/startup batch and continue the next measured gaps.
Suggested next integration work: normal grbl_enter startup for existing wall,
delta, polar, AC and ganged kinematics variants, using original source and valid
HAL callbacks. Do not force private startup handlers or classify intentional
fatal loops as bugs. PR #13 remains the unmerged parent at latest verification.

## Batch 9 latest-core transition and known-fix cleanup

Terje master advanced from 39a69a2 through a7f17b8 to 683589b while this checkpoint
was being delivered. The ignored core checkout is now clean at 683589b, original
source unchanged. The first full run identified seven known regressions now
passing: pending-override spindle stop, auxiliary stream allocation, long VFS
filename lookup, failed mount return/event, exact root buffer sizing, absolute
lookup miss and unrelated wall-plotter settings. Their exceptions and bug entries
are removed; correct C regression assertions remain as ordinary tests. The two
obsolete fatal-diagnostic wrappers and their matcher tests are deleted, and both
cases run directly in sanitized and coverage configurations. Python checks now
pass all 43 remaining helper tests.

One ordinary fault-injection test was adapted from the old malloc call to current
realloc(NULL, size), retaining the same chdir failure/root-fallback expectations.
The existing allocated-root getcwd regression exposed a newly introduced defect:
vfs_getcwd(NULL, 0) constructs a buffer but returns NULL. Its correct expectation
is retained, with a narrowly documented expected failure and a test-only observer
reclaiming the lost buffer before assertion, rather than a sanitizer suppression.
See KNOWN_BUGS.md for exact source anchors and cleanup of that observer/wrapper.
DO/WHILE stays in the user's TODO/proposal; no classification changed there.

Affected modules pass all 166 cases with strict classification. Full latest-core
ASan/UBSan suite also passes: 2,897 total, 2,885 clean, 12 documented regressions,
zero unexpected failures/skips (42.39 s; build-asan/batch-9-latest-core-final-results.xml).
The prior 82-case push acaf9af/39a69a2 is a baseline validation run; this cleanup
needs a separate hosted run on 683589b once that run completes. Coverage 90.9%/
77.4% describes 39a69a2, not this changed core. Continue newest core coverage,
including real settings-enabled multi-spindle ramp independence and normal boot
of existing kinematics variants. PR #13 remains the unmerged parent.

## Batch 9 wrap-up (2026-10-14)

The final 82-case checkpoint passed every hosted job against Terje `39a69a2`
(run 38628319147). Merged feature-variant coverage for that revision is
15,872/17,402 lines (91.2079%) and 10,465/13,464 branches (77.7258%).
These figures precede the latest-core cleanup and must not be attributed to
`683589b`.

Terje `683589b` fixes seven documented regressions. Their exceptions and
entries were removed while the assertions stayed. One newly exposed VFS
`getcwd(NULL, 0)` defect has a narrow expected-failure entry. Full local
ASan/UBSan: 2,897 cases, 2,885 clean, 12 documented expected failures,
zero unexpected failures/skips; 43 script checks pass. The SCARA source was
removed upstream, so its old integration note is now historical in TODO.md.

This batch is ready after hosted GCC, Clang and coverage validation of the
latest-core cleanup. Parent PR #13 was open at this checkpoint; avoid a
cumulative duplicate PR. Once #13 merges, rebase/merge its upstream base and
open the batch-9 PR with only this batch's changes. Continue the full-coverage
goal in a separate subsequent branch. The DO/WHILE CONTINUE proposal awaits
Terje's contract decision.

## Batch 10 overnight restart and first checkpoint (2026-10-15)

The scheduled 02:00 Johannesburg restart created a new active full-coverage
goal. PRs #13, #14 and #15 have merged. Batch 10 starts on coverage-batch-10
from upstream 9e2e20f. Terje's latest core is still clean at 683589b. Batch 9's
final hosted run 38632387393 passed source/GCC/Clang/coverage/CI diagnosis;
coverage on 683589b was 15,900/17,437 lines (91.1854%) and 10,497/13,506
branches (77.7210%). Earlier open-parent/pending-run notes are historical.

Thirteen new cases: nine call real grbl_enter for wall, delta, polar, ganging,
auto-square and RTCP startup; three verify independent Cartesian restoration
from motor positions. Delta/RTCP advertise physical NVS for stored geometry;
the initial delta null-hook failure was a fixture configuration error, not a
core defect. RTCP uses its supported M850 command. Four paired-PWM parser
cases register both spindles before gc_init, map the secondary through settings,
and use the original PWM calculator/configured ramp flags. Start routing,
primary stop without secondary use and secondary stop isolation pass. A primary
stop after starting the higher-speed secondary reproduces an output increase:
the secondary lookup shadows the pointer returned from _get_ramp and overwrites
the primary cached speed. Correct assertions remain with one narrow known
exception and SHA/line-linked report. No physical speed/frequency claim.

Focused boot/spindle validation and strict summary pass. Full local ASan/UBSan:
2,910 cases, 2,897 clean, 13 documented expected failures, zero unexpected
failures/skips (39.20 s; build-asan/batch-10-first-full-results.xml). All 43
script checks pass. No production source changes. Commit/push this coherent
startup/PWM checkpoint, then hosted validation while continuing measured gaps.
Questions go to TODO and DO/WHILE remains unregistered. Greatest remaining
aggregate line gaps include gcode, settings, motion_control, report and ioports;
inspect the uncovered public paths and existing controls before authoring.

## Batch 10 settings, mixed laser and parser/output follow-up

Hosted run 38658180242 passed every job for d2d1d02 against Terje 683589b.
Its first 13 new cases measured 15,915/17,437 lines (91.2714%) and
10,518/13,506 branches (77.8765%). Core remains unmodified and clean.

Twenty-five additional cases now pass: six RGB strip-length configuration,
capability, persistence and rejected-input cases; four mixed primary ordinary
PWM/secondary laser parser cases; seven public comment/message normalization
and execution cases; five rejected-command cases preserving position, units
and dynamic tool offset; three real motion-synchronized digital/analog output
lists. Message output is reached via public gc_execute_block, not an undeclared
internal helper. Mixed laser fixtures use real PWM precomputation and driver
flags before registration, with the primary laser capability disabled.
Analog fixture logging observes callbacks without limiting their execution.

Disabled open-drain/timezone public registrations are recorded as coverage
inventory in TODO, not bugs or manufactured private-call tests. No new core
exceptions were added in these follow-ups. Batch 10 now adds 38 cases total.

Full local ASan/UBSan and strict summary: 2,935 total, 2,922 clean,
13 documented expected failures, zero unexpected failures/skips (39.66 s;
build-asan/batch-10-delivery-results.xml). Earlier 43 script checks remain
valid: no script changes. Commit/push this checkpoint and dispatch hosted
validation on the same core SHA, then continue independent measured gaps.
No PR is ready until hosted gates pass. Full-coverage goal remains active.

## Batch 10 extended-axis arcs and startup-to-homing integration

Run 38659450581 passed every hosted job for the 38-case checkpoint 3c1a352
against Terje 683589b. Coverage: 15,948/17,437 lines (91.4607%) and
10,559/13,506 branches (78.1801%). Source checkout remains clean/unmodified.

Thirteen further registered cases pass: seven original planner/stepper arc
executions with eight-axis or remapped UVW extra-axis travel; one real boot
single-primary auto-square homing rejection; five startup-to-homing controls,
including ordinary and ganged X homing, independent all-axis switches, release
of stored startup modal code after all axes home, and continued locking after
only X homes. Extra-axis pulse observation proves interpolation occurs during
the arc, with signed endpoints and monotonic auxiliary pulse counts checked.
No physical contour-accuracy claim. The shared boot driver wrapper now preserves
core's default homing feed callback; stored homing configuration loads before
settings-dependent cached values initialize. Earlier missing-callback/NaN
failures and the ganging rejection expectation were fixture/contract errors,
not core bug entries.

Partial manual Y reference on ganging/auto-square with force-set-origin leaves
the secondary motor counter unchanged. Both manually built unregistered
candidates confirm {160, 0, 320, -240}, homed mask 2, zero wakes. It remains a
contract question in TODO with an unregistered proposal, no exception. The
ordinary homing fixture has no proposal-specific behavior.

Full local ASan/UBSan plus strict summary passed 2,948 cases: 2,935 clean,
13 documented expected failures, zero unexpected failures/skips (41.01 s;
build-asan/batch-10-arc-home-full-results.xml). Batch 10 adds 51 registered
cases total. No scripts changed since 43 helper checks passed. Publish this
arc/startup checkpoint and validate hosted while continuing meaningful gaps.
The full-coverage goal remains active, with unresolved questions in TODO.
