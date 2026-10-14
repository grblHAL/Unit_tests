# Coverage progress and continuation handoff

Last verified: **2026-10-14**. Read this with the root `AGENTS.md` and README.
This is a snapshot, not proof that future checkouts or CI runs are unchanged.

## Batch 7 active work

`coverage-batch-7` continues toward full meaningful coverage. Core under test:
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
that contract is resolved. Hosted validation of the final checkpoint is pending.
