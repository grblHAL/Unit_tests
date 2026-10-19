# Current local recovery group - 2026-10-19

PR22 is READY, not merged: all five jobs passed run39245386515 at
 aa8097160bb572eb9e40f52c1d727b530cfc3c05 / core16c7dff3aa9614322cfc2b47a2109cc9196ccca4.
Both downloaded locks match full selection and the unchanged core/header filter.
Verified coverage16,997/17,652 lines96.29%;11,666/13,700 branches85.15%.
The pushed PR has85 new cases /3,777 total, seven known failures, no known UBSan.
README badges in this local continuation now link that verified report.

Sixteen further local cases extend dwell-stop recovery, queued quadratic-spline
rejections, corrupt work-offset recovery, malformed expressions, invalid macro
loop targets and physical XY toolsetter checks. One full local gate3794 cases
completed132.90s:3790 passed, three expression cases used the wrong (disabled)
module, and one mismatched named-SUB header candidate timed out. Expression
cases moved to ngc_expr with assertions unchanged; focused3/3 pass0.31s.
The uncertain SUB-header candidate is unregistered in proposals with TODO.
Consolidated full-run plus targeted-repair evidence has3793 cases /7 expected
failures and passes strict summary; raw original/repair XML and logs retained.
This is NOT a second all-tests execution. No core code or exclusions changed.

Commit this related group locally. Keep coverage-batch-69 and continue larger
batches; do not dispatch tiny CI follow-ups or alter ready PR22's head just for
this checkpoint. Before the next push refresh PR22 merge state. New questions
stay in TODO; never manufacture a macro-contract decision to make a case pass.
Next useful gap: command help follows publicly configured homing options, then
rank reachable regions using the newly downloaded39245386515 coverage report.

# Current combined batch69 delivery - 2026-10-19

Stay on coverage-batch-69; consolidate its work into existing PR22 rather than
creating another small PR. PR22 is draft pending exact updated-head hosted checks.
Core clean/latest fetched: 16c7dff3aa9614322cfc2b47a2109cc9196ccca4.
25 new cases beyond PR22's prior 3,752-case head: 3,777 registered now.
Coverage remains last measured 96.14% lines /84.91% branches (run39203585952,
9a06753/ad57c78); do not claim new-source coverage until its hosted report exists.

Validation: one full 3,776-case ASan/UBSan gate on ad57c78 passed134.99s plus
strict summary. A newly fetched core update required a shared-header rebuild.
Latest-core affected-module check: 524/526 passed18.84s; two allocation fixtures
still targeted malloc after upstream changed redirect contexts to calloc.
Added narrowly scoped calloc wrapping; repair/new-case check54/54 passed1.31s
with strict summary. JSON-close API test is skipped when source lacks that API.
No repeated full local suite; next complete gate is hosted GCC/Clang/coverage.

Removed 13 resolved WILL_FAIL allowances plus the resolved JSON sanitizer label/
manifest entry, and deleted their 11 resolved bug sections. Correct regression
assertions remain. Manual-tool door completion now checks observable safety-door
state rather than the obsolete queued-flag implementation. Seven documented
expected failures remain; no sanitizer diagnostic allowances remain.

Full boot confirms runtime $65=32 is supported despite clearing its saved flag
at initialization. Idle IRQ cases remain registered; uncommitted withdrawal was
reverted. New cases cover pauses, G97/CSS queue ordering, semicircle roundoff,
partial peck drilling, IPv4 provider success/failure, macro errors/recovery,
corrupt build-info recovery, pull-setting notification and JSON close ownership.
Next: push this cumulative checkpoint to PR22, one hosted run against16c7dff;
continue supported workflow gaps on the same working branch while it runs.

# Active efficiency policy - 2026-10-19

This policy supersedes historical per-case/per-module validation and delivery notes.
The user requests productive token use and realistic controller workflows.

- Stay on one feature branch for a substantial batch. No branch/CI checkpoint for
  every small module. Commit related work together; push at a useful review boundary.
- Read one coverage report per batch. Rank remaining executable regions by reachable
  lines per realistic workflow and reuse existing host fixtures. Work through the
  largest supported gaps first, rather than chasing individual uncovered branches.
- Prefer ordinary jobs, startup/settings changes, hold/resume, probing and realistic
  driver error handling with externally observable outcomes. Combine related paths
  in readable scenario tests; retain separate files for distinct behaviors.
- Before authoring, check existing cases and source contracts once. Do not duplicate
  already-covered assertions, manufacture invalid startup states, or force private
  paths just to increase a percentage.
- During authoring use source review. Build a substantial group together. Focused
  execution is for unresolved behavior/failures, not an automatic per-case ritual.
- Run the full local sanitizer suite and report checks ONCE at the pre-push boundary.
  Fix failures, rerun affected tests, and repeat broader checks only when the repair
  affects shared infrastructure or leaves suite-wide uncertainty. Do not rerun
  unchanged reporting helpers. Then push and use one hosted validation checkpoint.
- Record uncertain contracts and unfinished/unreachable regions in TODO with concise
  evidence, then move on. Never weaken assertions or exclude code to claim 100%.
- Report coverage gain and remaining reachable gaps at substantial checkpoints.
  The target remains meaningful full supported coverage; any residual unavailable
  implementation must be explained separately rather than consuming endless tests.

Immediate work: keep coverage-batch-69, finish its existing motion/settings cases,
then group the largest reachable gcode/settings/IO gaps from the latest report.
Latest verified hosted baseline: 16,954/17,634 lines (96.14%) and
11,588/13,648 branches (84.91%), core ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216.
Probe audit correction: full boot accepts public $65=32 and arms the watchable
probe guard. Existing idle IRQ cases remain registered. The contrary withdrawal
was never committed; a full-boot runtime-enable control is pending batch validation.

# Batch69 partial-peck group validated - 2026-10-19

Fifteen new cases total3,767 pass full ASan/UBSan56.80s and strict summary.
Latest four G73/G83 partial-final-peck cases pass0.46s: requested depth clips
last peck, chip-break/full retract remain distinct, G98 returns clearance and
three repeated holes retain common depth. Observer records emitted motor steps.
No new exceptions;20 known failures plusone known UBSan.51 helpers last4.112s.
PR22 CREATED and attached, frozen68 9a06753 with60cases: allfive hosted jobs
green39203585952; source/scope lockverifiedad57. Do not merge or extend itshead.
https://github.com/grblHAL/Unit_tests/pull/22
Continue related modules on69, focused authoring checks then cumulative gate
and useful push boundary. Current69work remains local until next checkpoint.

# Batch69 numeric arc controls - 2026-10-19

Eleven new cases now total3,763. Two added semicircle radius controls pass
focused2/2 in0.28s: float-roundoff radius still emits a curved path to exact
motor endpoint; beyond-tolerance radius rejects without dropping prior queuedcut.
Three CSS/G97 controls pass0.37s; six boot pause cases passed full3,758gate
56.47s. Next cumulative gate must cover these5addedcases before push/PR.
No new exceptions. Goal active. Keepwork on69 and commit coherent groups.
68 exacthead CI39203585952 lastsource/coveragepass, compilerjobs stillrunning.

# Batch69 continuing on the same branch - 2026-10-19

Nine new cases now total3,761. Latest three registered-encoder CSS->G97S400
cases pass focused3/3 in0.37s: radial and longitudinal queues finish before
mode/speed switch; same-block rapid remains queued and reaches new endpoint.
No new exceptions. Last full sanitizer/strict gate is3,758 before these3; next
substantial cumulative gate must include them. Six boot pause cases committed
01d9ac5; keep coherent modules here until next batch-ready checkpoint.
68 pushed9a06753, hosted39203585952 live lastseen; exact readiness required
before opening cumulative PR for its60cases. Continue while CI runs.

# Current batch69 pause-workflow checkpoint - 2026-10-19

Branch coverage-batch-69 starts pushed68 9a06753. Six new actual boot/serial
M0/M1/single-block/M60 cases total3,758 pass full ASan/UBSan56.47s and strict
summary; focused6/6 pass0.61s. First move ends at80steps before pause; four
held polls preserve position and ACK count; public cycle start allows second
move to160steps. Physical optional-stop input controls M1 only. Single-block
switch deassertion is a real control IRQ; M60 calls driver after completed motion.
No new exceptions;20 known failures plusone known UBSan.51 helpers pass4.112s.
Core unchangedcleanad57c78.66 run39203076490 and68 run39203585952 live lastseen;
64 fullygreen/locked96.08line84.81branch. Upstream unchangedb281f42;60newcases
through68 are next-PR candidate once its exact hosted checks finish. No PRcreated.
Keep next related modules on coverage-batch-69, commit coherent groups, and use
focused checks while authoring before the next substantial cumulative gate/push.
Do not create a branch/CI run for every small group. Continue while CI runs.

# Current batch68 idle-door checkpoint - 2026-10-19

Branch coverage-batch-68 starts local67 0b38941. Four new public setting/control
IRQ cases total3,752 pass full ASan/UBSan56.44s and strict summary;focused4/4
pass0.44s. Ignore-idle still shuts constant laser off immediately; closing does
not restart it. Normal spindle control preserves output by configured policy;
nonignored idle door enters suspension and disables laser without motion.
Initial laser fixture used M3 in G0, correctly yielding zero power. Corrected
setup to supported G1M3S500F100 without axis words; no defect/exception claimed.
20 known failures plusone known UBSan unchanged;51 helpers latestpass4.112s.
Hosted64 locksverified e0c6707/ad57/corefilter, fullygreen:
16,942/17,634 lines96.08%;11,575/13,648 branches84.81%. Badges refreshed.
66 run39203076490 live lastseen. Deliver local67+68 together and dispatch68.
Core unchangedcleanad57c78. PR20/21 merged; next PR only after latest exact CI.
Continue local boot pause work while CI runs.

# Current batch67 probe-interrupt checkpoint - 2026-10-19

Branch coverage-batch-67 starts pushed66 2c99b40. Three new real probe IRQ cases
total3,748 pass full ASan/UBSan56.93s and strict summary; focused3/3 pass0.34s.
Actual probe_add/legacy IRQ registration drives core control_interrupt_handler.
Public$65=32 protection and$6=1 inversion configure contact/release behavior;
idle events rearm guard, preserve polarity and do not request stop/reset/alarm.
No synthetic active probing state or private calls. No new exceptions.
20 known failures plusone scoped UBSan unchanged;51 helpers latestpass4.112s.
Core cleanad57c78. Hosted64 run39202050479 fullygreen at e0c6707.
65/66 pushed and cumulative66 dispatched; no isolated65run. Latest locked
parsed coverage58 95.99/84.69. Deliver this with next related command group.
PR20/21 merged; prepare next PR only after cumulative exact-head CIpasses.

# Current batch66 public-command checkpoint - 2026-10-19

Branch coverage-batch-66 starts local65 3448b44. Four new command cases total
3,745 pass full ASan/UBSan55.69s and strict summary; focused4/4 pass0.43s.
Public$RST=& restores registered numeric plugin storage, preserves core steps/mm
and requests reset. Help advertises driver reset only with registered provider.
$RTC query reads/formats driver time and propagates failed reads without output.
No new exceptions;20 known failures plusone scoped known UBSan.
51 helper checks latestpass4.112s unchanged. Core cleanlatestad57c78.
Hosted60 run39200502195,61 run39200605707 and62 run39201007431 allgreen.
64 run39202050479 inprogress lastseen; no isolated63run (coveredcumulatively).
Deliver local65+66 together and dispatch cumulative66. Latest verified locked
coverage58 95.99/84.69. PR20/21 merged; prepare new PR only after latest CIpasses.
Keep working while CI runs.

# Current batch65 expression checkpoint - 2026-10-19

Branch coverage-batch-65 starts pushed64 e0c6707. Six new parser/stepper cases
total3,741 pass full ASan/UBSan55.63s and strict summary;99 ngc_expr pass3.71s.
Computed parameter indices round within documented0.0001 integer tolerance,
including indirection. Out-of-tolerance index preserves previous assignment and
queuedcut; EXP overflow and MOD0 nonfinite feed reject without dropping valid
queuedmotion. No new exceptions;20 known failures plusone scoped known UBSan.
51 reporting helpers latestpass4.112s. Core freshfetch unchangedcleanad57c78.
63 and64 delivered together; only cumulative64 dispatched.60/61/62/64 status
refresh blocked by approval reviewer capacity; do not claim terminalsuccess.
Latest locked verified report58 95.99/84.69;59 hostedgreen. PR20/21 merged.
Commit this group; combine next local group for next hosted checkpoint. Keepgoing.

# Current batch64 optional-spindle hold checkpoint - 2026-10-19

Branch coverage-batch-64 starts local63 c63137f (push review timed out; not yet
delivered). Three new supported hold/resume cases total3,735 pass full
ASan/UBSan54.96s and strict summary; all120multi_spindle pass5.07s.
Settings-mapped startup now optionally leaves secondary disabled before gc_init;
default fixture still enables it. Primary-only hold/resume and held spindle
stop/restore avoid unused drivers; two-enabled control preserves both outputs.
No new core issues/exceptions:20 known failures plusone scoped known UBSan.
TODO records why separate getter-null fallback cannot occur with valid indices;
no source exclusions or private calls. Shared driver/stepper workflows retained.
51 helpers lastpass4.902s; timed-out rerun retried once and still pending review.
Deliver63+64 together and run cumulative hosted64 to avoid redundant small runs.
Core cleanad57c78; latest verified locked report58 95.99/84.69;59 hostedgreen.
60/61/62 need terminal checks. PR20/21 merged; no new PR. Keepgoing.

# Current batch63 held-spindle regression checkpoint - 2026-10-19

Branch coverage-batch-63 starts pushed62 33f97d1. Three new cases total3,732 pass
full ASan/UBSan55.79s and strict summary;59 state-machine cases pass2.52s.
One registered normal-PWM regression: after completed feed hold, override110%
calculates550 from500 but driver level remains500 and pendingflagclears. Idle
update/reset and held stop/restore/resume controls pass with same registered
driver. Initial minimal fixture reproduced5000->5500 too; confirmed with proper
spindle_register/standard-mode startup before classification.
Shared PWM fixture now observes both set_state and update_pwm outputs; callback
behavior unchanged. Correct assertion retained in one exact WILL_FAIL; dated
KNOWN_BUGS entry, source cause, proposed fix/removal guide; no sanitizer allowance.
20 known failures plusone known UBSan now. Core unchangedcleanad57c78.
51 helper checks lastpass4.902s; new rerun pending automatic approval review.
Hosted58/59 green;60 run39200502195,61 run39200605707 and62 dispatched need
terminal verification. Latest exact locked report58 95.99/84.69. Continue.

# Current batch62 rotated-arc checkpoint - 2026-10-19

Branch coverage-batch-62 starts pushed61 62c3f36. Five registered arc cases
total3,729 pass full ASan/UBSan55.83s and strict summary;22 rotation cases pass
1.09s. Public G10/G55 rotation tested with XY positive/negative quarter turns,
ZX/YZ helices and inch IJK conversion; exact physical endpoints/pulses checked.
Translated-origin candidate is unregistered in tests/proposals with TODO evidence:
core rotates work offset with target, yielding(-5,4) rather than proposed(2,5).
Terje must confirm rotation pivot; not a confirmed failure or new exception.
19 known failures plusone scoped known UBSan unchanged;core cleanad57c78.
Hosted58 run39199404867 locksverified1b6f00d/ad57/corefilter, fullygreen:
16,927/17,634 lines95.99%;11,558/13,648 branches84.69%. Badges refreshed.
Hosted59 run39199851892 green;60 run39200502195 and61 run39200605707 live.
51 helper checks lastpass4.902s unchanged. PR20/21 merged; continue after checkpoint.

# Current batch61 PWM checkpoint - 2026-10-19

Branch coverage-batch-61 starts60 bf98be2. Three new servo PWM conversion cases
total3,724 pass full ASan/UBSan55.42s and strict summary; focused all146ioports
pass5.41s.50Hz servo1-2ms range tested with hold-minimum, disabled-zero and
inverted-disabled policies. Active output allows one timer tick of float/floor
quantization; diagnostic log confirms1499/1999 and inverted18500/18000 at1MHz.
No core defect claimed or exception added.51 helper checks pass4.902s unchanged.
Batch60 successfully pushed/dispatched on retry. Hosted58 run39199404867 fully
green at1b6f00d;59 run39199851892 inprogress lastseen. Coverage download blocked
by approval-review capacity; latest parsed exact-source report56 95.93/84.63.
Core cleanlatestad57c78. PR20/21 merged; no new PR. Continue independent work.

# Current batch60 boot-backlash checkpoint - 2026-10-19

Branch coverage-batch-60 starts pushed59 8e58b0a. Eight new real boot/parser
stream cases total3,721 pass full ASan/UBSan56.18s and strict summary;51 helpers
pass4.902s. New boot_backlash module reuses existing host_core_backlash and normal
driver_init wrapper. No new core variant or production source changes.
Serial$160/$161/$162 configure0.1mm take-up;40moves refill planner. XYZ reversals
with both first directions and same-direction controls verify exact pulse counts,
physical/logical distinction and final origin. Focused8/8 pass0.87s.
19 known failures and one scoped known UBSan unchanged. No new issues claimed.
Hosted58 run39199404867 inprogress lastverified;59 dispatched. Latest status
query blocked by automatic approval review capacity; do not assume green.
Core cleanlatestad57c78. Latest verified coverage56 95.93/84.63.
PR20/21 merged; no new PR. Continue after checkpoint.

# Current batch59 program-end checkpoint - 2026-10-19

Branch coverage-batch-59 starts pushed58 1b6f00d. Nine new cases total3,713 pass
full ASan/UBSan56.20s and strict summary. Seven multi-spindle M2/M30 cases cover
public restore-overrides setting both policies, coolant/spindle shutdown, next
program speed and G55-to-saved-G54 reset. Two compatibility1 G92.1 cases verify
persisted offset erasure versus preservation under disabled persistence.
Focused7/7 pass0.58s plus2/2 pass0.33s. No new exceptions, core unchangedad57c78.
51 helper checks pass4.405s on unchanged reporting scripts; redundant rerun was
blocked by reviewer capacity. Hosted58 dispatched, status query pending.
PR20/21 merged; no new PR yet. Continue after useful validated module boundary.

# Batch58 completed local validation - 2026-10-19

Twelve new cases total3,704 pass full ASan/UBSan59.02s and strict summary.
Five macro-depth/tool-capacity cases plus seven actual-stepper radius arc cases:
inch conversion, positive/mirrored uniform scaling, CCW, helical allthreeplanes.
51 reporting checks passed4.405s before C-only arc additions; redundant rerun
blocked by approval reviewer capacity. No script changes or new exceptions.
Core cleanlatestad57c78. Commit/push this module boundary and continue.
PR20/21 merged; branch58 based b281f42. Verified hosted56 95.93/84.63, not
yet these12newcases. Fork cleanupdone51mergedremote,59mergedlocal.

# Current batch58 continuation - 2026-10-19

PR20 and21 are merged; branch coverage-batch-58 starts upstream b281f42.
Five new parser-facing macro depth/tool table capacity cases total3,697 pass
ASan/UBSan118.89s and strict summary;51 reporting checks pass4.405s.
Named recursion, nested G65, explicit RETURN and error recovery to sender tested.
No new exceptions;19 expected failures and one scoped known UBSan unchanged.
Fresh Terje fetch remains cleanad57c788e15fb4e5d8ef9c20ed50755ffa3d9216.
Hosted56 run39179095314 success; exact harness520e3db/source/filter lock verified:
16,916/17,634 lines95.93%;11,550/13,648 branches84.63%. Badges refreshed.
Cleanup completed59 merged local branches and51 merged origin branches; fork
retains onlymaster. Preserve other checked-out worktree and nonmergedlocal9.
These five cases are localvalidated, not yet hosted. Continue meaningful coverage.

# Current batch56 multi-spindle checkpoint - 2026-10-19

Branch coverage-batch-56 starts at pushed55 6ede665. Twelve new cases total3,692:
eight broadcast direction/capability/selector checks and four independent override
output checks through M48/M49/M51. Focused110/110 pass4.96s;51 helpers pass4.716s.
Initial override fixture failures were float rounding at8400 RPM against1e-5;
less than0.01 RPM tolerance passes, no core issue or exception added.
Full3,692 sanitizer/strict verification passes54.40s;19 known failures and one scoped known UBSan unchanged.
Hosted54 run39176480077 and55 run39176993923 both terminalsuccess. Latest parsed
coverage remains verified53 95.81% lines/84.46% branches. Core cleanad57c78.
PR20 remains frozen40; no merges. Continue after checkpoints.
# Coverage progress and continuation handoff

Last verified: **2026-10-16**. Read this with the root `AGENTS.md` and README.
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
G70�G72 reporting remains an undecided contract in TODO.

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

## Batch 10 machine masks and probe configuration

Fifteen further cases validate public step/enable polarity and limit inversion/
pullup masks with readback, persistent values and driver notifications; energized
motor masks update HAL immediately, can be cleared, and reject nonexistent axes
without touching the driver; rotary-excluded hard limits retain the correct
linear-axis mask through settings reload and clear exclusion when disabled;
combined probe inversion updates all advertised inputs; disconnection inversion
notifies the driver on change without redundant toggles or effects from reset
input inversion. All cases and full sanitizer/strict gate pass.

Full suite: 2,963 total, 2,950 clean, 13 documented expected failures,
zero unexpected failures/skips (42.38 s; build-asan/batch-10-config-full-results.xml).
Batch 10 adds 66 registered cases total. Core is unmodified at 683589b.
The 51-case hosted run 38660620756 has successful source and coverage jobs,
GCC/Clang still running. Its coverage is 15,997/17,437 lines (91.7417%) and
10,598/13,506 branches (78.4688%). Do not present pending jobs as passed or
attribute this measurement to the newer 66-case local checkpoint.

Commit this configuration checkpoint, then continue independent meaningful
public paths while current CI runs. Publish/dispatch only after that run ends.
Next useful integration: normal streamed G-code/jog execution through real boot
on existing CoreXY, polar and ganged variants. Use valid initial motor positions,
public driver callbacks and bounded foreground service; preserve the core's
initialization order. The full goal remains active. No new known exceptions.

## Batch 10 real streamed kinematics motion

Hosted run 38660620756 passed source/GCC/Clang/coverage/CI diagnosis for the
51-case checkpoint 8876065 on Terje 683589b. Its measured coverage remains
15,997/17,437 lines (91.7417%) and 10,598/13,506 branches (78.4688%).

Fourteen further cases now execute real grbl_enter, serial input, parser,
planner, timer ISR and driver pulses for CoreXY, asymmetric ganging, polar and
wall plotter. They verify Cartesian-to-motor translation for cuts/jogs, reverse
motor travel, preserved G20/G91 program modes during metric jogs, and valid
restored radius/cable references. Longer polar/wall cuts and wall jogs observe
a full planner and pulses before sender acknowledgement, then complete the
original commanded endpoint. Real startup uses 35 planner blocks, so distances
exceed that capacity rather than relying on the host's pre-start default.
Cable rounding allowances are explicit alongside exact motor-counter assertions.
No hardware contour/timing claims or private production calls.

The stream fixture uses the supported realtime exit only after motion wakes,
the sender acknowledgement is visible and the core returns idle with an empty
planner. This corrected an initial fixture exit before parsing the line.
A per-test read bound retains the old 1,000-read default and permits bounded
longer motion. All currently registered stream cases use one motion block;
future multiple-block tests must match all expected acknowledgements before
exiting, rather than counting an earlier command's acknowledgement.

Full local ASan/UBSan and strict summary pass: 2,977 total, 2,964 clean,
13 documented expected failures, zero unexpected failures/skips (42.24 s;
build-asan/batch-10-stream-full-results.xml). Batch 10 adds 80 cases total.
No scripts changed since 43 helper checks passed. Publish this motion commit
and the prior validated configuration commit together, then verify hosted while
continuing remaining public paths. Suggested next work: multi-block sender
completion and real RTCP/delta startup motion with physical geometry NVS;
retain realistic initial positions and independent geometric controls. Goal active.

## Batch 10 complete sender programs, RTCP and delta startup motion

Run 38662265998 passed source/GCC/Clang/coverage/CI diagnosis for the 80-case
checkpoint 986eabb on Terje 683589b. Measured coverage: 16,032/17,437 lines
(91.9424%) and 10,621/13,506 branches (78.6391%).

Twelve further registered cases pass: three complete multi-command programs,
six real streamed RTCP controls and three delta motions. The sender fixture
counts every standalone successful acknowledgement, accepting CRLF or LF
preceding plugin output while excluding prefixed startup acknowledgements.
It exits only after all commands acknowledge and motion drains. This corrected
a fixture parser that missed the acknowledgement after M852's LF-only diagnostic.

RTCP controls use physical geometry NVS, public setting writes, zero-center and
fixed 90-degree A/C configurations, disable/resync followed by an incremental
machine-frame move, and M852 measurement with default nonzero centers. The
zero-center expectation on unmeasured defaults was not classified as a bug.
A no-motion unregistered candidate and TODO ask whether direct M851 activation
must synchronize parser coordinates or requires the M852 sequence first.

Delta controls load symmetric physical/radian motor configuration before
kinematics initialization and execute vertical cut/jog and a longer segmented
cut. Independent rod geometry yields 5 equal motor steps for .5 mm and 98 for
10 mm; counter-derived Cartesian rounding allowance is explicit. The longer
cut observes a full planner and motion before acknowledgement. Source is
unmodified. No new known exceptions or regression assertion weakening.

Full local ASan/UBSan and strict summary: 2,989 total, 2,976 clean,
13 documented expected failures, zero unexpected failures/skips (45.39 s;
build-asan/batch-10-multi-kin-full-results.xml). Batch 10 adds 92 registered
cases total. Publish and dispatch this checkpoint, then continue remaining
supported paths from fresh coverage. Questions stay in TODO and proposals
unregistered. Goal active; no PR claimed ready without its hosted gate.

## Batch 10 expansion-bank routing and claims

Run 38663661728 passed all hosted jobs for 7802c99's 92-case checkpoint on
Terje 683589b. Coverage is 16,032/17,437 lines (91.9424%) and
10,628/13,506 branches (78.6910%). Those integration cases improved branches
but added no new aggregate lines: use the fresh uncovered paths/configurations
to guide subsequent work rather than repeating already covered integrations.

Seventeen new public I/O cases register native GPIO plus two digital expansion
banks and two analog banks. They verify bank-local dispatch, independent type
counts, timeout/mode propagation, remapping, claims and compacted free-port maps,
logical output events only for successful/unclaimed ports, retained native
routing, interrupt delivery with claimed/remapped handles, external digital
metadata and empty-bank rejection preserving existing dispatch. Mock callbacks
represent driver banks, not a real bus. Returned claim handles are used directly;
an initial assumption about their numeric positions was corrected before
classifying behavior. No new defect or known exception was added.

Analog input pin-base metadata differs from digital registration despite correct
current routing. A runtime inspection confirms the second analog bank's bases
are input=0/output=2. TODO records a possible bookkeeping improvement pending
actual supported driver usage; no speculative failing regression was registered.

Full ASan/UBSan and strict summary passed 3,006 cases: 2,993 clean,
13 documented expected failures, zero unexpected failures/skips (40.34 s;
build-asan/batch-10-banks-full-results.xml). Batch 10 adds 109 registered cases.
No scripts changed since 43 helper checks passed. Core remains unmodified.
Publish/validate this completed I/O module while continuing remaining gaps.
A likely next feature-combination gap is NGC modal/spindle snapshot restoration
with multiple settings-enabled spindles: existing multi-spindle host lacks NGC
expressions and ordinary snapshot cases do not drive these two-spindle hardware
restore branches. Verify current fixtures/contracts before adding that variant.
Full-coverage goal remains active; unresolved questions stay in TODO.

## Batch 10 modal restoration, jerk persistence and JSON strings

Hosted run 38665399234 passed all jobs for af1bcb3 on unchanged Terje
683589bd10bb1082825bfc7e9bcee6db102b9530. Coverage: 16,047/17,437 lines
(92.0284%) and 10,669/13,506 branches (78.9945%). Source HEAD was rechecked
and remains this revision; the ordinary ignored core checkout is clean.

Eleven separate multi-spindle cases use early registered, settings-enabled
basic spindles and real parser commands. They verify independent directions,
speeds and override policies through M70/M71/M72 and M73 scope exits,
nested caller restoration and selective hardware updates. NGC parameters
are already enabled by default: no extra expressions configuration or new
host library was necessary. RPM output assertions use a .01 RPM tolerance
for ordinary float multiplication, consistent with existing override tests.

Three jerk cases verify temporary overrides are restored before settings
persistence, unrelated saves retain original jerk, and a new permanent jerk
setting becomes the later restore baseline. Two lathe cases verify G7/G8
restoration and named parameter reporting. Four JSON cases verify control
character escaping, Windows paths, adjacent escapes and empty-string comma
handling. These test existing public contracts; no new expected failures.

Full local ASan/UBSan and strict summary passed the first sixteen additions:
3,022 total, 3,009 clean, 13 documented expected failures, zero unexpected
failures/skips, 112.36 s (build-asan/batch-10-restores-full-results.xml).
The four subsequently added JSON cases passed focused sanitizer and strict
summary checks (build-asan/batch-10-json-results.xml). Total now 3,026 cases;
batch 10 adds 129. Hosted GCC/Clang/coverage must validate the whole checkpoint
before any ready PR claim. Continue uncovered supported public paths while
that run executes; questions remain TODO, goal remains active.

## Batch 10 transport state, pendant reports and discoverable settings

Seventeen additional cases cover public Modbus ASCII/TCP availability/busy
state, reset propagation and RTU silence timing; MPG full/legacy status and
cycle-start commands; plugin help topic discovery/filtering; third serial
device registration; and command-driven coprocessor passthrough startup and
reset line states. Full status respects configured report fields. Complete
settings help uses a larger local output capture. The passthrough command
fixture supplies the USB connected callback needed by normal report output.
All three were fixture assumptions corrected without classifying core bugs.

Full local ASan/UBSan and strict summary: 3,043 total, 3,030 clean passes,
13 documented expected failures, zero unexpected failures/skips, 43.42 s
(build-asan/batch-10-discovery-full-results.xml). Batch 10 adds 146 cases.
No production changes or new exceptions. Also removed an extra trailing blank
line in the preceding jerk test; staged whitespace must pass before commit.
Hosted run 38667090574 validates the prior 129-case checkpoint (2dc9b68);
source/GCC/coverage passed at last check, Clang was running. Do not push and
cancel it. Continue file-stream callback coverage while it completes, then
publish this validated group and dispatch the complete checkpoint.

## Batch 10 rotary feed timing and file callback contracts

Run 38667090574 completed all jobs successfully for 2dc9b68: 16,073/17,437
lines (92.1776%) and 10,689/13,506 branches (79.1426%). The following
79ab9f5 checkpoint also passed all jobs in run 38668110778; its coverage
artifact is not yet retrieved. Terje HEAD remains clean/unmodified 683589b.

Nine new eight-axis cases configure rotary axes/options through public settings
then run G-code through planner and pulse callbacks. They check linear-distance
feed timing for mixed rotary moves, multiple rotary axes, inch feed reversion,
explicit inverse time, rapid motion, disabled-fix behavior and linear-only
controls. Assertions verify planned duration/rate and actual final motor counts.
Five file-stream cases check normal error/status suppression callbacks, ordered
file-end observers, report-handler reinitialization and offset/line reposition.
All use public entry points. No new defect classification or exception.

Full ASan/UBSan and strict summary passed: 3,057 total, 3,044 clean,
13 documented expected failures, zero unexpected failures/skips, 116.25 s
(build-asan/batch-10-rotary-file-full-results.xml). Batch 10 adds 160 cases.
Publish this checkpoint once the prior hosted run is terminal; continue
remaining supported paths, including spindle at-speed feedback timing.
The goal is active; questions remain TODO and no PR is yet claimed ready.

## Batch 10 spindle-ready feedback and macro-visible coolant

Six spindle-ready cases register a basic variable spindle with at-speed
feedback before parser initialization. Real M3/M4 commands check delayed ready
signals, zero configured startup delay, already-ready feedback, readiness at
the deadline and missing-feedback timeout. Successful notifications follow
feedback; timeout turns the driver off and raises Alarm_Spindle. The timeout
observer timestamps alarm entry before the normal 100 ms alarm-report delay;
an initial wall-clock assumption was corrected, without a new bug claim.

Full ASan/UBSan and strict summary passed 3,063 cases (3,050 clean,
13 documented expected failures, zero unexpected failures/skips), 101.18 s;
build-asan/batch-10-ready-full-results.xml. Three subsequent focused sanitizer
cases check named mist/flood parameters against real coolant driver state
through M7/M8/M9, and named version against firmware build identity. Their
strict summary passes (build-asan/batch-10-named-coolant-results.xml).
Now 3,066 registered cases: batch 10 adds 169. No new exceptions or source
changes. Hosted checkpoint 764c53c is run 38682688236; inspect terminal state
before pushing. Earlier run 38668110778 passed all jobs, covering
16,107/17,437 lines (92.3725%) and 10,723/13,506 branches (79.3943%).
Continue remaining supported paths and preserve the full goal. No PR has
been presented as ready. Source remains Terje 683589b.

## Batch 10 scheduler ordering, secondary motor limits and edited comments

Three scheduler cases exercise immediate follow-up FIFO ordering, independent
periodic callback deletion and the documented refusal to delete a running
systick callback from itself. Two secondary motor cases check configured rate
limits both at initial command and during acceleration. Their valid maximum
rate needs more than 1000 acceleration/deceleration steps; both bounded fixture
loops now allow 10000. A redundant zero-speed candidate was removed after
finding the existing registered case; assertions were not weakened.

Full local ASan/UBSan and strict summary passed 3,071 total, 3,058 clean,
13 documented expected failures, zero unexpected failures/skips (39.88 s;
build-asan/batch-10-tasks-motors-full-results.xml). Three subsequent focused
sanitizer/strict-summary cases edit serial comments with backspace, checking
preserved parenthesized printable realtime characters, reopening a comment by
deleting its closing parenthesis, and semicolon trailing-text preservation.
They complete real serial/planner/pulse execution with exact endpoints/output
(build-asan/batch-10-edited-comment-results.xml). Total 3,074, batch 10 +177.
No new exceptions or production changes. Hosted run 38682688236 completed all
jobs successfully for 764c53c; push this completed local checkpoint and validate
it while continuing remaining supported workflows. Goal active.

## Batch 10 optional parameter configuration and macro/resource contracts

A clean host variant compiles the documented NGC_PARAMETERS_ENABLE=0 and
NGC_EXPRESSIONS_ENABLE=0 configuration. Four cases exercise real linear motion,
G92 offsets, persisted G55 offsets and rejection of unavailable M70-M73 without
state changes. Three normal boot cases exercise driver startup, persisted modal
initialization and soft reset (including both welcome messages) without parameter
support. The README configuration inventory now includes this tested variant.

A file containing three subroutines verifies definition skipping, requested call
order and scope cleanup. Two expression cases verify default float-format reset
and numeric PRM rejection of registered text settings. Two narrow allocation
failure cases verify encoder registration/list recovery and JSON start/output
recovery under shared-heap exhaustion. Public APIs remain production-owned;
only those two executables wrap their allocator. No new exception or bug claim.

Full ASan/UBSan and strict summary: 3,083 total, 3,070 clean, 13 documented
expected failures, zero unexpected failures/skips, 39.09 s
(build-asan/batch-10-optional-params-full-results.xml). The three subsequently
added boot cases pass focused sanitizer/strict summary checks
(build-asan/batch-10-no-params-boot-results.xml). All 43 helper tests passed.
Now 3,086 registered cases: batch 10 adds 189. Terje HEAD was rechecked and
remains clean/unmodified 683589bd10bb1082825bfc7e9bcee6db102b9530.
Hosted run 38683576138 is still active for bb9e036's 3,074-case checkpoint;
do not push/cancel it. Last fully completed run 38682688236 covers
16,125/17,437 lines (92.4758%), 10,742/13,506 branches (79.5350%).
Continue supported configurations/public workflows; full coverage is not yet
achieved and the goal remains active. No batch 10 PR has been claimed ready.

## Batch 10 normal-boot G95 and interrupt fallback

Five serial G95 cases register the spindle and encoder data handlers during
driver initialization, set PPR in persisted settings and let real settings/driver
startup install synchronization support. No private synchronization-config helper
is called. Cases verify radial/longitudinal motion, inch feed conversion, arcs,
return to G94, macro-visible mode/report fields and exact motor endpoints.
G95 uses RPM feedback without angular phase locking; no physical timing claim.
A sixth case checks unsupported default IRQ claims fail without calling a plugin.

The first complete sanitizer summary caught a diagnostic that CTest's exit code
alone missed: the boot motion fixture had zero arc tolerance. It now persists
.002 mm (core's DEFAULT_ARC_TOLERANCE) before reload. With valid configuration,
the strict full sanitizer summary passes 3,091 total, 3,078 clean,
13 documented expected failures, zero unexpected failures/skips, 39.35 s
(build-asan/batch-10-boot-feed-full-results.xml). IRQ fallback then passed focused
sanitizer/strict summary (build-asan/batch-10-irq-results.xml). There are now
3,092 cases: batch 10 adds 195. No new known exception or production change.

Hosted run 38683576138 passed all jobs for bb9e036, covering 16,152/17,437 lines
(92.6306%) and 10,763/13,506 branches (79.6905%). Commit/push the queued complete
checkpoint and dispatch hosted validation; continue independently while it runs.
Source HEAD was rechecked clean at Terje 683589b. The full goal remains active;
questions stay TODO and no batch 10 PR is yet claimed ready.

## Batch 10 realtime state reports and metadata recovery

Ten report cases verify real feed-hold deceleration/completion, jog-to-idle,
safety-door parking state, busy-to-idle WCO/override refresh scheduling,
normalized numbered setting names and alarm/error catalog fallback/retry when
the sorting allocation fails. States come from actual motion/realtime workflows.
Report fixtures finish report_init and use the controller's persistent tracking
state with its broadcast writer; initial incomplete report setup and mismatched
tracking assumptions were corrected without claiming core defects.

Full local ASan/UBSan and strict summary pass 3,102 total: 3,089 clean,
13 documented expected failures, zero unexpected failures/skips, 39.60 s
(build-asan/batch-10-report-final-results.xml). All 43 helper checks pass.
Batch 10 now adds 205 cases in maintainable separate files. No new exceptions
or production changes in this report group. Upstream master was freshly fetched
and remains 9e2e20f, so the branch still has a clean unchanged delivery base.

Run 38684803384 validates 03a4396's 3,092-case checkpoint. Source/coverage were
successful at last check while GCC/Clang were active. Do not push and cancel
that healthy run. Once terminal, publish/dispatch this complete checkpoint and
verify all jobs before claiming a PR ready. Continue independent work while it
runs. Full line/branch coverage is not yet achieved; keep the goal active.

## Batch 10 delivery freeze / batch 11 preparation

Batch 10 is frozen at fdf6483: 205 new cases, 3,102 total, local full
ASan/UBSan + strict summary and 43 helper checks passed. It was pushed after
03a4396's hosted run 38684803384 completed successfully. That run measured
16,173/17,438 C-source lines (92.7457%) and 10,791/13,514 branches (79.8505%).
A manual hosted run was dispatched for fdf6483. Inspect its exact head and all
required jobs before opening a ready batch 10 PR; do not merge it.

Further work is isolated on coverage-batch-11 from fdf6483. Do not duplicate
batch 10's PR diff while it awaits merge. Core is unchanged Terje 683589b.
A separate local header-inclusive coverage measurement is running in
build-local-coverage with LLVM Clang, ENABLE_COVERAGE=ON, sanitizers off,
gcovr 8.4 from ../coverage-python, filter core/.*\.[ch]$. Old gcda files were
cleared inside that verified build directory before execution. Its output paths
are ../batch-10-header-coverage-{build,tests,report}.log and
../batch-10-header-coverage.xml. This is independent evidence, not a CI change.
The existing .c-only report omits header bodies and un-emitted optional helpers;
TODO records the follow-up. Keep the full goal active and continue meaningful
public workflow coverage, using the new header inventory when available.


## Batch 10 validated delivery / batch 11 first checkpoint

PR #16 delivers frozen batch 10 at fdf6483. Hosted run 38686040614 passed
source, GCC, Clang, coverage and diagnosis. It measured 16,198/17,438 C-source
lines (92.89%) and 10,831/13,514 branches (80.15%) against unchanged Terje
683589bd10bb1082825bfc7e9bcee6db102b9530. Do not merge the PR automatically.

The independent local Clang header-inclusive baseline completed: 17,252/18,708
lines (92.22%), 10,200/12,810 branches (79.63%), 1,215/1,258 functions.
This uses a different compiler and scope from hosted GCC; the denominators are
not directly comparable. Fresh profiles came from all 3,102 batch 10 cases.
One stale retired target's gcno was removed inside the verified build directory;
no source was excluded and no reporter errors were ignored. Evidence:
../batch-10-header-coverage.xml and matching build/tests/report logs.

Batch 11 adds ten passing cases: independent primary/secondary motor bit banks,
fault-axis lookup and input classification, plus a seven-axis XYZABCU host.
Seven-axis cases check each/all axis word projections, rejection of unrelated
arguments, exact linear and arc endpoints, modal inch conversion and persisted
U work offsets without other motor pulses. Core source is unchanged.
Full ASan/UBSan plus strict summary passed 3,112 cases: 3,099 clean, thirteen
expected failures, zero unexpected failures/skips, 39.62 seconds. Evidence:
build-asan/batch-11-first-full-results.xml. No new exception or bug claim.
Continue through supported header/configuration gaps; stepper2 ramp transitions
are next to inspect through public motor APIs. Keep batch 11 separate from #16.


## Batch 11 latest-core compatibility and motor transitions

Terje master advanced to feebef26222111f11c7a3b3b0156d023aa786937 on
2026-10-15. The ignored ordinary core checkout is clean at that revision.
The first full rebuild/run of 3,115 cases exposed five fixed expected failures
and one changed control-input mode expectation. Direct sanitizer execution of
the unchanged backlash-clear, WHILE/CONTINUE, allocated cwd and both startup-slot
retry regressions returned zero. Their five WILL_FAIL blocks and resolved bug/
startup TODO entries were removed. Allocated cwd now uses the original ordinary
caller-owned pointer test without allocation/linker wrappers.

Core now explicitly selects PullMode_Down for disabled control-input pullups;
the debounce-preservation control follows this changed public behavior. This
is separate from the still-reproducing auxiliary live/load pullup inconsistency.
Version-only failed storage writes remain a deferred-policy expected failure.
The new double-increment warning counter is recorded as source-review evidence
in TODO pending reproduction/policy, without a speculative failing test.

Nine new secondary-motor cases cover speed changes during acceleration, stopping
during speed reduction, repeated speed requests, finite millimeter rounding and
negative position, early finite stop, two independent motors, zero finite distance
and reverse restart after completion. Three passed focused ASan/UBSan on 683589b;
all nine pass the full latest-core gate in build-asan/batch-11-cleanup-results.xml.
Suite totals 3,121: 3,113 clean passes, eight retained expected failures, zero
unexpected failures/skips or sanitizer diagnostics. Full gate and strict summary
passed in 41.62 seconds. All 43 helper checks pass. Publish this substantial
checkpoint for hosted GCC/Clang/coverage while continuing independent coverage.


## Batch 11 startup option and probe-connection coverage

Seven additional cases pass focused ASan/UBSan and strict summaries on Terje
feebef2: SD-only, LittleFS-only and combined filesystem option metadata after
normal boot, plus four probe-connection boot combinations. The driver supplies
normal probe state/toggle callbacks; real grbl_enter/startup tasks reconcile the
connection input and avoid redundant toggles. No private core call, source patch,
new known exception or defect claim. Evidence: build-asan/batch-11-filesystem-
results.xml and build-asan/batch-11-probe-results.xml. Total 3,128 cases.

Terje confirmed PullMode_Down for the control-input debounce regression; a
source comment explains that board drivers handle processor/protection limits.
TODO records his future protected-input setting availability follow-up.
Hosted run 38692359893 validates a65ac73's 3,121-case checkpoint against feebef2;
it was still in progress when this local startup group finished. Do not push
and cancel that healthy run; inspect all jobs before publishing another checkpoint.


## Batch 11 spindle override command coverage

Three focused sanitizer/strict-summary cases pass: M49 disables feed/primary
speed override while preserving the secondary policy; M48 reenables primary
while retaining a separately disabled secondary; M51 with omitted P reenables
secondary without changing disabled feed/primary policy. Total 3,131 cases.
Evidence: build-asan/batch-11-overrides-results.xml. No new known exception.
Standalone $-1 override candidates failed at parser validation and were removed;
do not bypass parser validation just to execute dormant all-spindle branches.


## Batch 11 active fixture rotation before cutting

Two cases pass focused sanitizer/strict summary on feebef2: change active G54
rotation from 90 to 180 degrees at the origin, or clear it before the first cut.
G10 setting commands emit no motor pulses; the following real cut reaches exact
physical/system endpoints with unchanged Z. Configuration commands use the parser
directly; the shared queue helper is for motion blocks only. No core defect or
exception. Evidence: build-asan/batch-11-rotation-results.xml. Total 3,133 cases.


## Batch 11 complete local delivery gate

Three I/O driver-notification cases verify configuration-before-callback ordering,
unchanged input values avoid reconfiguration while retaining notification, output
inversion preserves open drain, and settings-load notification follows all port
configuration. Focused sanitizer/strict summary passed.

The complete 3,136-case suite passed ASan/UBSan and strict summary: 3,128 clean,
eight documented expected failures, no unexpected failures/skips/diagnostics,
48.57 seconds (build-asan/batch-11-module-results.xml). This batch adds 34 cases
and removes five fixed exceptions against unmodified Terje feebef2. All 43 helper
checks passed earlier in this checkpoint. PR #16 is now merged; upstream master
3034d4d was freshly fetched. Rebase the batch onto it, publish after the active
healthy hosted run is terminal, and validate the final head before a ready PR.


## Separate CI header-reporting follow-up

ci-header-coverage is based on merged batch 11 / upstream fb9086d. It changes
only report scope, changed-code assessment, its regression and README instructions.
Core suite filter includes executable .c/.h bodies; changed-code Git diffs include
headers. A real-Git regression failed before the assessor fix and now verifies
uncovered added inline lines and absent changed headers with actionable guidance,
while ignoring old gaps and comments. All 44 helper checks pass. Manual triggers,
reusable callers and core source remain unchanged. Hosted validation is required
before a ready PR. Batch 12 test development is preserved separately at ae1f708
on origin/coverage-batch-12, with 42 new cases / 3,178 total and full local gate.

This follows the observed Windows LLVM long-path profile omission. Use Linux
hosted totals for authoritative measurements, and keep scope/configuration limits
explicit. Header bodies absent from emitted code remain an inventory follow-up;
this change alone does not establish whole-core coverage.
## Batch 11 frozen final head / batch 12 continuation

Final batch 11 head ae0eaa7 is rebased on upstream 3034d4d; its tree is identical
to the fully locally validated pre-rebase checkpoint. Source/GCC/Clang/coverage/
diagnosis all passed earlier checkpoint a65ac73 in run 38692359893. Its GCC
C-source measurement: 16,197/17,440 lines, 10,838/13,518 branches. Final run
38693498958 now validates all 34 new cases and the exception cleanup on ae0eaa7.
Do not claim a ready PR until every final job passes. User explicitly wants this
batch's PR. Open/attach it when ready; do not merge. New work is isolated on
coverage-batch-12 based on ae0eaa7, so it cannot delay or cancel batch 11 delivery.
Core remains clean Terje feebef2. Continue toward meaningful full coverage.


## Batch 12 Modbus device responses and driver integration

Six new cases pass focused ASan/UBSan and strict summary against clean feebef2:
valid device exception frames preserve their code and appear in sender stats;
settings load applies the driver's advertised serial framing; claimed UART pins
receive driver diagnostic labels; custom inter-transaction silence delays queued
transmission, and restoring defaults releases it under the normal scheduler.
These use public transport/settings/driver workflows, valid CRC-framed responses
and mock clock service; they do not claim physical UART timing performance.

The RTU fixture accepts an optional driver serial-format callback, default NULL
for existing cases. All 35 Modbus cases pass after the fixture change. Evidence:
build-asan/batch-12-transport-results.xml and strict summary log. Total 3,142 cases,
six beyond frozen batch 11; no new known exception/production change. Questions
remain TODO; batch 11's PR still awaits final hosted run 38693498958.


Two further Modbus cases pass focused sanitizer/strict summary: after no reply,
the sender's $MODBUSSTATS command distinguishes never-connected from previously
responsive devices and reports one timeout. Evidence: build-asan/batch-12-status-
results.xml. Batch 12 now adds eight cases, total 3,144; no new exception.


## Batch 12 independent secondary motor service

Three cases pass focused sanitizer/strict summary: slow finite feed emits no
pulse before its deadline and reaches two steps; changing one continuously
serviced motor's speed preserves the other rate; stopping one motor lets the
other continue stepping. Both motors are serviced through public APIs with a
shared simulated clock, and aggregate pulses match independent positions. No
physical pulse-frequency claim, private state access or new exception.
Evidence: build-asan/batch-12-pair-results.xml. Batch 12 adds eleven cases,
total 3,147. Core remains clean feebef2. Full local checkpoint is next after the
next related module; batch 11 PR still awaits final hosted jobs.


## Batch 12 modal-macro error cleanup

Two additional cases pass focused sanitizer/strict summary: parser errors clear
pending G66 registration before later motion; a G66.1 callback error releases
modal arguments and restores the caller's local parameter scope. The ordinary
G66/G66.1 controls also pass. Re-registration syntax is uncertain (status 21),
so that candidate is unregistered under proposals with evidence in TODO, not
classified as a defect. Total 3,149 cases, thirteen beyond batch 11. Evidence:
build-asan/batch-12-modal-results.xml. Run the full local gate at this checkpoint.


## Batch 12 full checkpoint and parser-driven manual tool changes

The first full local checkpoint passed ASan/UBSan + strict summary: 3,149 cases,
3,141 clean, eight expected failures, zero unexpected failures/skips/diagnostics,
43.53 seconds (build-asan/batch-12-first-full-results.xml). Core remote HEAD was
rechecked at unchanged feebef2. Batch 11 is now ready PR #17: all final run
38693498958 jobs passed, exact harness ae0eaa7 and core feebef2 verified from
source-lock. Final C-source coverage is 16,232/17,440 lines (93.07%) and
10,863/13,518 branches (80.36%). Do not merge PR #17 automatically.

Three parser-driven manual M6 cases now pass with all 56 tool-change cases:
require homed tool axis, block new motion while pending, and acknowledge through
the normal sender/realtime path to apply the tool and release later motion.
The shared manual interface setup was factored without changing old behavior,
and supplies the normal non-null tool-completion callback. The first completion
candidate omitted realtime service/callback setup; the fixture was corrected,
not classified as a core bug or suppressed. Evidence: build-asan/batch-12-m6-
results.xml and strict summary. Total 3,152; batch 12 adds sixteen cases.


## Batch 12 persisted offsets through manual acknowledgement

The preceding 3,152-case full sanitizer/strict-summary gate passed: 3,144 clean,
eight expected failures, zero unexpected failures/skips/diagnostics, 45.54 s
(build-asan/batch-12-m6-full-results.xml). All 43 helper checks pass.
The acknowledgement test now executes the following X cut to its exact 80-step
physical/system endpoint with unchanged Y/Z, also passing focused strict checks.

Three further cases combine the existing four-tool host configuration with normal
settings initialization, persistent tool writes, parser M6 and actual manual
acknowledgement. They verify deferred G43, explicit alternate H offsets and H0
selecting the pending tool. Following Z cuts reach exact -240/-160 endpoints.
No tool table data is reimplemented, no core source is modified, and no new
exception was added. Evidence: build-asan/batch-12-manual-table-results.xml and
strict summary. Total 3,155, nineteen new cases in batch 12.


## Batch 12 RGB inline driver utilities

Nine header-only cases pass ASan/UBSan and strict summary: GRB byte order,
full-intensity round trip, independent channel masks, known low/high waveform
symbols, zero intensity, half-intensity conversion and normal driver capability
classification. Tests invoke the original inline definitions in rgb.h, with
adequately sized real encoded buffers. The rgb_clear index convention remains a
TODO question, without a forced boundary failure. CMake supports this header-only
module without inventing a production .c file or pulling in host controller code.

Evidence: build-asan/batch-12-rgb-results.xml. Total 3,164; batch 12 adds 28 cases.
These header bodies are outside hosted .c-only percentages; do not claim a .c
coverage increase from them. Refresh independent header-inclusive measurement
against current clean feebef2 using a rebuilt build-local-coverage and fresh gcda
profiles. Keep the tested source/compiled case scope explicit if work continues.


## Batch 12 public motion-extension hooks

The 3,164-case full sanitizer/strict-summary checkpoint passed: 3,156 clean,
eight expected failures, no unexpected failures/skips/diagnostics, 56.16 s
(build-asan/batch-12-header-full-results.xml). Header-inclusive baseline build
is active in session 46072, logs ../batch-12-header-coverage-{configure,build,
tests,report}.log, output ../batch-12-header-coverage.xml. It was configured at
5172863 for 3,164 cases with clean feebef2; later additions are new independent
files/fixtures, outside that frozen build's case inventory. Existing compiled
case/fixture/core sources remain unchanged. Do not rerun the build or clear its
profiles while the command is active.

Eight additional cases pass focused sanitizer/strict summaries in the existing
cutter-enabled configuration: pre-execution hook receives normalized inch targets
before modal commit; rejected/consumed blocks avoid normal planning; implicit
axis-only motion sets the hook's motion flag. Public line/arc hooks delegate
validated targets/feed/plane/turn direction to original core planners, and driver
rejections propagate without parser position or planner updates. No compensated
geometry is reimplemented or claimed. Evidence: build-asan/batch-12-pre-execute-
results.xml and batch-12-motion-extension-results.xml. Total 3,172; batch 12 adds
36 cases. No new confirmed bug or exception. Run the full gate and publish a
useful module checkpoint while continuing coverage; PR #17 remains separate.


## Batch 12 nested file calls and modal restoration

Six normal file-stream cases pass focused ASan/UBSan and strict summaries:
nested calls preserve each caller's local arguments; bounded recursion returns
cleanly; exceeding the call limit unwinds scopes; M73 restores units/distance/
plane/feed through actual and nested file returns; M71 disarms restoration.
Files are read/repositioned through the production stream/parser path, with no
manual call-stack manipulation. Evidence: build-asan/batch-12-nested-results.xml
and batch-12-file-modal-results.xml. Total 3,178; batch 12 adds 42 cases.

The preceding full 3,172-case gate passed sanitizer/strict summary: 3,164 clean,
eight expected failures, zero unexpected failures/skips/diagnostics, 65.67 s
(build-asan/batch-12-extension-full-results.xml). The independent 3,164-case
header-inclusive run finished all tests successfully (122.62 s) and its gcovr
report remains active in session 46072. Do not discard profiles or ignore errors.
Full current gate and first batch 12 hosted checkpoint are next.


## Batch 12 publish gate / local coverage collection finding

Full current ASan/UBSan and strict summary passed 3,178 cases: 3,170 clean,
eight expected failures, zero unexpected failures/skips/diagnostics, 48.57 s
(build-asan/batch-12-publish-results.xml). All 43 helper checks pass. Core remote
HEAD was rechecked at clean feebef2. Publish this 42-case useful checkpoint for
hosted validation while continuing coverage; do not present a ready PR before
its exact head passes all required jobs or duplicate unmerged parent PR #17.

Header-inclusive session 46072 completed without reporter errors for its frozen
3,164-case inventory, but its 17,319/18,815 lines (92.05%) and 10,254/12,856
branches (79.76%) are NOT authoritative: executed long-path test objects have
missing gcda files. RGB helpers show zero despite all nine cases passing. A
short GCOV_PREFIX/STRIP=99 rerun of the same byte-mask executable writes a valid
212-byte profile; original path length is 262. TODO and README document the
Windows LLVM collection limitation and separate Linux header-reporting follow-up.
Earlier local header baseline may also be incomplete. Do not equate absent
profiles with absent tests or use these totals as the goal's completion metric.
Hosted Linux batch 11 C-source totals remain 93.07%/80.36% pending batch 12 CI.


PR #17 was independently verified merged as fb9086d. Batch 12 rebased cleanly
onto that merged parent; its tree was identical to the locally validated
pre-rebase checkpoint except subsequent handoff documentation. Publish the
42-case checkpoint now. Never commit/push master or merge PRs automatically.


## Batch 12 first hosted checkpoint and continued eight-axis coverage

Published ae1f708 (42 new / 3,178 total) passed every required hosted job in
run 38698553119: source, GCC, Clang, coverage and diagnosis. Coverage artifact
confirms 3,178 tests, zero failures/skips, 16,258/17,440 C-source lines (93.22%)
and 10,909/13,518 branches (80.70%) against feebef2. Core remote HEAD remains
unchanged. This is a useful checkpoint, not completion of the full goal.

A separate ci-header-coverage branch at 09a15fa is pushed and validating in
run 38698910578 from merged upstream fb9086d. It includes executable header
bodies in Linux coverage and adds headers to changed-code Git diffs. Its new
real-Git regression failed before the assessor fix; all 44 helper checks now
pass. README explains scope/configuration limits. Keep this CI change out of
the test batch, inspect all required jobs before opening/attaching a ready PR,
and do not cancel either healthy hosted run with another push. Then continue
batch 12 independently; resolve future README/PROGRESS overlaps by retaining
both the header-reporting instructions and test progress, without duplicate text.

Three additional eight-axis cases pass focused sanitizer/strict summary:
G30.1 records completed positions for all motors; persisted U/V offsets produce
exact selected-axis endpoints; G30 returns A/V directly to its saved point while
unselected XYZ/BC/U motors stay still. The initial mixed case incorrectly assumed
G28's rotary shortcut applied to G30. Core computes that shortcut only for G28;
the case now follows G30's direct-coordinate behavior with ordinary bounded
travel, without raising fixture bounds or classifying a defect. Evidence:
build-asan/batch-12-eight-return-results.xml. Total 3,181; batch 12 adds 45 cases.


## Batch 12 runtime legacy compatibility configurations

Two host variants now execute COMPATIBILITY_LEVEL=2 and 10 rather than relying
only on report syntax checks. Ten focused cases pass sanitizer/strict summary:
nine clean, one narrow documented expected failure. They cover standard versus
extended coordinates, HOME/report extensions, axis-mask versus boolean setting
metadata, metric/absolute soft reset, legacy banner and tool reset.

Legacy protocol does not accept the host CMD_EXIT byte. Its boot fixture now
captures completion at the public stream-read boundary with setjmp/longjmp;
normal core startup/reset runs, and no unsupported exit command is injected.
The first read-limit failures were that fixture assumption, not core faults.
Level 2's coordinate enum explicitly supports six work systems; config.h's
wording is a TODO documentation clarification, not a missing-feature failure.

A genuine level-10 sender readback defect reproduces after normal boot:
$4=0 acknowledges successfully, but $4 reports $4=1. Verified setter/getter links,
correct unchanged query assertion, proposed getter fix and exact exception
removal instructions are in KNOWN_BUGS.md. Only that named case is WILL_FAIL;
no sanitizer exception or production patch. Other modes/settings controls pass.
Evidence: build-asan/batch-12-compat-results.xml and strict summary.
Total 3,191; batch 12 adds 55 cases, with nine expected failures across the suite.
Full current sanitizer gate is required before publishing this delivery checkpoint.

Separate CI reporting PR #18 is ready at 09a15fa: all run 38698910578 jobs passed,
source lock confirms feebef2/header filter, 3,136 cases zero unexpected failures/
skips, and all 44 helper checks pass. It is independent of batch 12. The report
contains exercised headers, and its expanded-scope baseline is 16,257/17,473
lines (93.04%), 10,902/13,560 branches (80.40%). Do not compare that smaller
3,136-case baseline directly with batch 12's 3,178-case C-only measurement.
No PR was merged automatically. Keep the full goal active.


## Batch 12 final 55-case delivery freeze

Full ASan/UBSan plus strict summary passed 3,191 cases: 3,182 clean, nine
explicit expected failures, zero unexpected failures/skips/diagnostics, 46.62 s
(build-asan/batch-12-final-results.xml). All 43 helper checks in this test branch
pass freshly; the separate reporting branch has its additional 44th check.
Production core remains clean feebef2, still remote HEAD at this checkpoint.

Freeze the 55 new cases as coverage-batch-12's delivery. Publish and validate
its exact final head against feebef2 before a ready PR. PR #18 is independently
ready/open for CI header reporting; prefer merging that upstream before final
batch-12 rebase/PR to avoid overlapping README/PROGRESS edits. Do not merge any
PR automatically or stop coverage while waiting. New test work continues on
coverage-batch-13 from this freeze; keep it separate so it cannot delay batch 12.


## Batch 13 continuation and legacy input configuration

Batch 12 is frozen/pushed at 4a224d4 (55 new / 3,191 total). Its final hosted
run is 38701989145 against unchanged feebef2. Verify all required jobs before
its ready PR, and keep the separate ready reporting PR #18 out of that test
diff until it merges. Do not cancel healthy validation with another push.

New work is local coverage-batch-13 from that freeze. Five added cases pass
focused ASan/UBSan and strict summary, using normal legacy boot with XYZ limit
capabilities and valid persisted homing cycles/rates: hard-limit enable/disable
dispatches to the driver, inversion reads back correctly, homing applies compile
defaults, and disabling homing clears previously enabled soft limits. A stream
observer proves the soft limit was actually enabled before disabling; all
positive input programs must have no error responses. Two existing reset cases
now also prove G20/G91 was active before reset, preventing default-state-only
false confidence. No core change, new defect or exception.

Evidence: build-asan/batch-13-legacy-limits-results.xml (eight cases pass including
existing controls) and strict summary. Total 3,196; batch 13 adds five cases.
Continue meaningful public workflow coverage while the frozen delivery validates.


## Batch 13 remapped axis-word projection

Three original-inline helper cases pass focused ASan/UBSan and strict summary:
each of eight XYZABCUV axis words maps to its exact motor bit, each XYZUVW word
maps to its remapped bit, and unconfigured ABC/feed arguments are ignored in
the UVW layout. No parser/private-state bypass is used; this is the public pure
parameter-word conversion helper. The Linux header report identified its
non-3/non-7-axis branch as a remaining gap; verify the next hosted measurement
rather than assuming a percentage gain. Evidence: build-asan/batch-13-axis-words-
results.xml. Total 3,199; batch 13 adds eight cases, no new exception.

## PR 18 combined delivery, 2026-10-15

At the user's request, PR 18 now includes the frozen 55-case batch 12 and
8-case batch 13 alongside header coverage reporting. This supersedes the earlier
separate-delivery plan. Combined local ASan/UBSan and strict summary pass all
3,199 cases (nine documented expected failures), with all 44 helper checks passing.
Evidence: build-asan/pr18-combined-results.xml and parent pr18-combined logs.
Core is clean feebef26222111f11c7a3b3b0156d023aa786937, verified remote HEAD.
Frozen batch 12 also passed all hosted gates in run 38701989145.
Push this combined head and validate hosted GCC/Clang/coverage before calling
this expanded PR ready. Continue new coverage separately; do not merge PRs.

## Batch 14 asymmetric analog expansion workflows

New work continues on coverage-batch-14 from combined PR 18 head 9c7099d.
Six new cases exercise input-only/output-only analog expansion boards and unequal
bank sizes through public driver registration, reads/writes, claiming, remapping,
pin lookup and descriptions. Direction-specific callback bounds now enforce each
bank's declared counts; existing symmetric fixtures retain their original defaults.
All 139 I/O cases pass focused sanitizers and strict summary. Full ASan/UBSan
and strict summary pass 3,205 cases (nine documented expected failures), 44.61 s:
build-asan/batch14-checkpoint-results.xml and parent batch14-full logs.
No production edits, new defect classification or new exception.

PR 18 now includes all prior 63 cases at user request, pushed at 9c7099d.
Combined hosted run 38735673645 is still validating; verify all gates before
claiming the expanded PR ready. Do not push this separate batch onto its branch
and cancel that validation. Next: use its Linux header-inclusive report to guide
remaining public workflow/configuration gaps. Core remains clean Terje feebef2.
The goal tool reports usageLimited despite reset; local work remains authorized.

## Batch 14 sender-driven metadata storage

Five more normal-boot sender cases pass ASan/UBSan and strict summary:
$DWNGRD sets and persists the downgrade flag/build marker, a second command
restores the current build (observer proves the first transition occurred),
and an argument is rejected without changing saved version data. $I writes
and reads custom build information; oversized input reports error 3 and retains
the previous value. Assertions inspect the physical NVS adapter after ordinary
shutdown/flush, with checksums, rather than the freed RAM buffer. Initial failures
were a test lifecycle mistake reading that freed buffer, corrected without any
production changes or exception. Evidence: build-asan/batch14-sender-results.xml.
Total 3,210 cases; batch 14 adds eleven cases. A fresh full gate is required
before publishing this enlarged batch.

PR 18 is merged upstream at e6edb45; its exact premerge head 9c7099d passed all
hosted jobs in run 38735673645. Authoritative header-inclusive coverage there:
16,401/17,604 lines (93.17%), 10,998/13,632 branches (80.68%), 3,199 cases.
These percentages do not yet include batch 14. Rebase this branch onto freshly
fetched upstream master before its eventual PR and preserve this work.

## Batch 14 capability help and mixed-axis report units

Four new public $HELP COMMANDS cases pass sanitizer/strict checks: physical board
switches suppress software toggle help, RTC help follows capability, encoder
commands appear only with matching callbacks (without calling them), and reset
help describes tool data only when a table is configured. Three eight-axis report
cases verify realtime, probe and home coordinates convert linear XYZUV to inches
while preserving ABC degrees, independent of G21 input mode. Home reporting also
preserves the selected homed mask. A shared mixed-axis report fixture avoids
copying setup across cases. Focus evidence: batch14-help-results.xml (seven
including existing controls), batch14-mixed-report-results.xml (three).
Total 3,217; batch 14 adds eighteen cases. No new core changes or exceptions.

## Batch 14 full publish checkpoint

Rebased onto merged upstream e6edb45. Full ASan/UBSan and strict summary pass
3,217 cases (3,208 clean, nine documented expected failures, no unexpected
failures/skips/diagnostics), 53.75 s. All 44 Python helper checks pass. Evidence:
build-asan/batch14-delivery-results.xml and parent batch14-delivery logs.
Core checkout remains clean feebef2 and remote HEAD is unchanged. TODO records
unsupported public wall-plotter homing as a coverage limitation, with no artificial
private-path tests, source exclusion or defect classification.

Publish this exact checkpoint for Linux GCC/Clang/header-inclusive coverage.
Inspect all required jobs and source lock, record measured percentages, and only
then create/attach a ready PR. Continue independent new work on a fresh branch
while CI runs; do not cancel healthy validation by pushing more to this branch.

## Batch 15 continuation: extended-axis settings and configuration review

New local coverage-batch-15 starts from pushed batch 14 b286d22. Its exact hosted
run 38745457196 is live; source passed, GCC/Clang/coverage still running at this
checkpoint. Do not cancel that run or present batch 14 as PR-ready prematurely.

Four additional eight-axis cases pass focused ASan/UBSan and strict summary:
U locate/V search homing rates persist independently of X; changing V travel
invalidates only V's high homed bit and persists the new magnitude; writing the
same V travel retains all homed bits. Evidence: build-asan/batch15-eight-settings-
results.xml. Total 3,221; batch 15 adds four registered cases, no exceptions.

NO_SAFETY_DOOR_SUPPORT=1 was explored as a missing configuration. Its settings
translation unit fails to compile because two excluded setters remain referenced
in the setting table. Support status needs maintainer confirmation, so TODO
contains exact revision/diagnostics/reproduction and four candidate tests remain
unregistered under tests/proposals. The host variant was removed from CMake;
no source patch or broad compiler exception was added. Do not claim runtime
coverage for those candidates. Continue independent supported workflows.

## Batch 15 configurable long macro labels

Added an NGC host variant with the supported NGC_MAX_PARAM_LENGTH=80 override
and expressions enabled consistently for core and tests. Three parser-driven
cases exercise long filenames requiring allocated lookup paths, the configured
80-character boundary, successful return/EOF cleanup, missing-file error handling
and caller-argument restoration. The shared static-macro backend now accepts a
configured name, retaining fixture as its default. Ten named-macro controls pass
focused sanitizer/strict checks, including the seven existing short-name cases.
The first candidate on the default build correctly rejected its over-30-character
label; this was a test configuration error, not a core bug. The explicit variant
now tests the valid extended configuration. README lists the added variant.

Full current ASan/UBSan and strict summary pass 3,224 cases (nine documented
expected failures), 53.24 s; all 44 helper checks pass. Evidence:
build-asan/batch15-checkpoint-results.xml and parent batch15-checkpoint logs.
Batch 15 adds seven registered cases; no new exceptions or production edits.

Batch 14 run 38745457196 coverage job succeeded. Its downloaded coverage artifact
confirms 3,217 cases, zero failures/skips, 16,413/17,604 lines (93.23%) and
11,013/13,632 branches (80.79%). GCC/Clang were still running at the last check;
verify their completion and diagnosis before opening/attaching its ready PR.
This measurement does not include batch 15. Continue independent coverage work.

## Batch 15 alternate G51 configuration and extended-name boundaries

The supported MACH3_SCALING=0 variant now has six separate cases: scaling about
a supplied center or the current position, independent I/J/K incremental factors,
G50 cancellation, rejection of a center-only command without factors, and a real
planned/stepped XY cut reaching 3/4 mm with exactly 240/320 emitted pulses.
These exercise the production alternate branch; no scaling implementation is
copied into the host. README lists the variant. Two additional 80-character-name
cases cover named assignment/expression lookup and reject an oversized assignment
without overwriting its valid prefix; normal parsing still works afterward.

All eleven alternate-scaling/extended-name cases pass focused ASan/UBSan and
strict summary (build-asan/batch15-configurations-results.xml). Total 3,232;
batch 15 adds fifteen registered cases. The last full gate was 3,224; run a fresh
full sanitizer/strict/helper checkpoint before pushing this enlarged batch.
Core remains unmodified feebef2. No new failure exception.

Batch 14 exact head b286d22 passed every hosted job, including source, GCC, Clang,
coverage and diagnosis, in run 38745457196. Ready PR 19 was created and attached:
https://github.com/grblHAL/Unit_tests/pull/19 . It has not been merged by the agent.
Keep batch 15 separate, inspect fresh upstream/PR state before eventual delivery,
and continue toward the full goal. Next use hosted coverage to measure gains of
the newly configured executable branches; do not infer gains from test counts.

## Batch 15 sender restore commands

Five normal-boot sender cases pass sanitizer/strict checks: $RST=$ resets a
previously observed custom setting and its saved record; $RST=# clears a
previously observed G54 offset in physical storage; $RST=* clears seeded startup
and custom build-info records and restores global settings. Invalid selectors
and check-mode restore requests preserve the custom setting and return errors.
Physical-storage reads after ordinary shutdown verify checksums and contents;
no read through a freed RAM buffer. The tests do not assume a query queued
behind a reset-producing command survives input flushing. Initial query/banner
expectations were fixture sequencing assumptions and were corrected without a
production patch or defect exception. Evidence: batch15-restore-results.xml.
Total 3,237; batch 15 adds twenty cases. Prior full 3,232-case ASan/UBSan and
strict gate passed in 48.23 s, with 44 helper checks; run the enlarged full gate
before publishing. Core remains clean feebef2.

## Batch 15 full delivery freeze

Full ASan/UBSan and strict summary pass 3,237 cases: 3,228 clean plus nine
documented expected failures, zero unexpected failures/skips/diagnostics,
48.96 s. All 44 helper checks pass. Evidence: build-asan/batch15-delivery-results.xml
and parent batch15-delivery logs. Core remains clean latest feebef2.
Freeze/push this 20-case delivery and run hosted Linux source/GCC/Clang/coverage/
diagnosis. PR 19 remains ready/open; prefer its merge before rebasing/opening
batch 15's ready PR, never merge automatically. Continue new work separately on
coverage-batch-16; normal-boot probe protection is a remaining public workflow gap.

## Batch 16 startup capability controls

New work is local coverage-batch-16 from frozen/pushed batch 15 4bccb2d.
Batch 15 passed all 3,237 local sanitizer/strict checks and 44 helpers; hosted
validation was dispatched against unchanged feebef2. Inspect the exact run head,
source lock and all jobs before presenting its ready PR. PR 19 remains open.

Two startup controls pass focused ASan/UBSan and strict summary: a disabled
probe-protection setting leaves normal parser commands usable, and normal
settings initialization clears the currently unavailable saved protection flag.
Investigating the expected enabled-protection startup alarm showed an explicit
#if 0 / unconditional Off in settings.c, not an alarm-handling defect. TODO records
that reachability limit; two enabled-feature candidates remain unregistered.
Do not turn the flag back on after initialization merely to cover private paths.
Evidence: build-asan/batch16-protection-results.xml. Total 3,239, two new cases;
no new exception or core patch. Continue other reachable public workflows.

## Batch 16 sender setting-query coverage

Eight new cases pass focused ASan/UBSan and strict summary. Default sender
commands $$=100 and $+=110 show only the requested axis setting with its units;
$$/$+ show current configured axis values; malformed/unavailable IDs return
errors without output. Legacy levels 2 and 10 each verify $$ hides available
extended planner-block setting $398 until $+ is requested, and $10 writes only
the legacy low bits while preserving/persisting the remaining report flags.
The first listing candidates used unavailable E-stop/compile-excluded G92
settings; they were corrected to the unconditional planner-block setting after
checking capability/compile guards, without changing core or declaring defects.
Evidence: batch16-metadata-results.xml (four), batch16-legacy-query-results.xml
(four). Total 3,247; batch 16 adds ten cases. Full current gate is required before
publishing this batch; no new failures/exceptions or source modifications.

## Batch 16 controller-information sender routes

Three new public command cases pass focused sanitizer/strict checks: normal boot
$I+ reports configured driver/board information; $SPINDLES/$SPINDLESH report a
spindle registered during driver initialization; $SED=100 returns only the selected
axis-setting description. The spindle test reuses the existing startup fixture;
its optional second-spindle helper is now inline so single-spindle users compile
without suppressing unused-function diagnostics. All three existing multi-spindle
startup controls pass too (batch16-information-results.xml, six cases).

Initial assumptions were corrected: the unconfigured boot host has no registered
physical spindle and its emulated-only storage does not advertise a physical NVS
medium. The test now installs the real driver callbacks/metadata at startup and
does not invent storage hardware. No core fault/exception or source change.
Total 3,250; batch 16 adds thirteen cases. Run the full gate for this shared-fixture
checkpoint before publishing, and keep the separate batch 15 hosted run intact.

## Batch 16 realtime plugin notifications

Three cases pass focused ASan/UBSan and strict summary: explicit and legacy
cycle-start bytes each deliver one control notification and one plugin start
notification with execution queued; optional-stop/single-block toggle callbacks
observe the updated flags on both transitions. Assertions concern delivered
signals, counts and visible state, not an undocumented relative callback order.
Evidence: batch16-realtime-results.xml. Total 3,253; batch 16 adds sixteen cases.

The previous 3,250-case full checkpoint passed ASan/UBSan and strict summary
with nine documented expected failures, no unexpected failures/skips/diagnostics,
48.70 s; all 44 helper checks passed (batch16-checkpoint-results.xml and logs).
Run the enlarged full gate before publishing. Keep batch 15 4bccb2d/run
38748405818 undisturbed; new batch 16 work remains separate.

## Batch 15 hosted validation complete

Every run 38748405818 job passed: source, GCC, Clang, coverage and diagnosis.
Downloaded source lock confirms harness 4bccb2d242d6d2a282e3bd4ed3c815d860f34550,
clean Terje feebef26222111f11c7a3b3b0156d023aa786937 and header-inclusive
core/.*\\.[ch]$ filter. Coverage results confirm 3,237 cases, zero failures/skips:
16,454/17,625 lines (93.36%), 11,047/13,648 branches (80.94%). Added variants
also increase the emitted-code denominator; do not compare raw missing counts
without that scope change. Artifacts: parent batch15-hosted-coverage-core.zip and
batch15-hosted-source-lock-core.zip.

PR 19 remains open at this live check. Batch 15 is validated/frozen; prefer
rebasing after PR 19 merges before opening its ready PR, avoiding duplicated
parent tests in the review. Never merge automatically. New coverage continues
independently on batch 16 with no need to wait. Full coverage is not achieved.

## Batch 16 accessory overrides and serial editing

Five more cases pass focused sanitizers/strict summary. Extra-low rapid override
uses 5% while retaining a 110% feed override and resets rapid independently.
Combined flood/mist toggles notify the plugin once with updated modal/driver
state; a cancelling toggle pair produces no write or notification. Serial Delete
corrects a build-info string before sender query/persistent save; Backspace after
a closed comment preserves and executes the following edited axis word, with
exact 80/240 X/Y pulses. Evidence: batch16-accessory-results.xml (three),
batch16-edit-results.xml (two). No new core defects or exceptions.
Total 3,258; batch 16 adds 21 cases. Run full current sanitizer/strict/helper gate
before publishing this module checkpoint. Batch 15 is independently validated;
PR 19 remains its parent delivery dependency until merged.

## Batch 16 full delivery freeze

All 3,258 cases pass full ASan/UBSan and strict summary (3,249 clean plus nine
explicit expected failures, no unexpected failures/skips/diagnostics), 51.21 s.
All 44 helper checks pass. Evidence: build-asan/batch16-delivery-results.xml and
parent batch16-delivery logs. No new core defects/exceptions or production edits.
Freeze/push this 21-case delivery and validate exact-head Linux GCC/Clang/coverage/
diagnosis against feebef2. Keep validated parent deliveries intact; PR 19 remains
open at the last check. New work continues separately on coverage-batch-17.
A reachable next gap is runtime critical motor-fault/E-stop feedback and reset
blocking while the physical input remains asserted, using the public realtime
alarm/control interfaces and existing critical-loop fixture, not private calls.

## Batch 17 critical physical-fault reset handling

New local coverage-batch-17 starts from frozen/pushed batch 16 20f02eb.
Two new cases drive the public realtime alarm interface with asserted motor-fault
or E-stop input. They request reset while the physical input is still asserted,
prove the critical loop executes another foreground turn, then clear the driver
input and verify abort/reset can complete with the correct reported alarm.
The existing critical-loop fixture now accepts an alarm and physical control state;
its default hard-limit behavior remains unchanged. All seven critical-loop cases
pass focused ASan/UBSan and strict summary (batch17-critical-results.xml).
These are core control-state checks, not claims about physical safety circuitry.
Total 3,260; batch 17 adds two cases, no new exceptions or source changes.

Batch 16 passed full local sanitizer/strict/44 helper gate and was dispatched for
exact-head hosted validation against clean feebef2. Check its live run before a
ready PR. Batch 15 is already hosted-green; PR 19 (batch 14) remains open at last
check. Preserve these deliveries and continue independent supported workflows.

## Batch 17 status reporting during critical lock

Two more cases pass focused ASan/UBSan and strict summary. A normal realtime
status request reports the locked position before reset; a full report remains
available while the E-stop input is asserted. The observer verifies report receipt
before releasing the input, reset remains blocked until release, and no axis
pulses occur. The fixture now waits for requested status output before resetting
and provides the coolant-state callback required by a full report. An initial
sanitizer failure was that omitted host callback, corrected without a core patch
or failure exception. All nine critical-loop cases pass (batch17-status-results.xml).
Total 3,262; batch 17 adds four cases. Full current gate remains required at the
next substantial checkpoint before publishing this shared-fixture change.

## Batch 17 reset-task lifecycle and batch 16 hosted evidence

Two normal-boot soft-reset cases pass focused ASan/UBSan and strict summary:
three registered plugin reset tasks run once in FIFO order across two resets,
and task_raise_alarm runs after reset and blocks following G91 with the requested
homing-required alarm. Registration happens after cold boot through task_run_on_reset;
no private scheduler entry point or fabricated boot state is used. The alarm's
wire code is 11; an initial guessed code 14 was corrected from alarms.h.
Evidence: batch17-reset-task-results.xml. Total 3,264; batch 17 adds six cases.

Batch 16 run 38751060993 passed source, GCC, Clang, coverage and diagnosis.
Downloaded source lock confirms harness 20f02ebfc77ef7123bee2496d65eb5c8405d0f1b,
core feebef26222111f11c7a3b3b0156d023aa786937 and emitted-header filter. Coverage
artifact confirms 3,258 cases with zero failures/skips, 16,487/17,625 lines
(93.54%), 11,068/13,648 branches (81.10%). Parent artifacts are
batch16-hosted-coverage-core.zip and batch16-hosted-source-lock-core.zip.
Core remote HEAD is still feebef2. These percentages do not include batch 17.
Run the current full local gate after critical-loop fixture changes. Preserve
validated batches 15/16; do not duplicate their parent PR 19 tests in new reviews.

## Batch 17 router homing accessory shutdown and initial status

Two normal-startup cases execute M3S5000, M8 and $HX with a registered spindle,
valid homing setup and real simulated switch/pulse feedback. An input observer
proves spindle/coolant were on before homing; pulse callbacks verify both driver
and modal outputs are off before every emitted step. X completes 110 pulses,
other axes remain still, and X gets its correct homed reference. With continuous
homing reports disabled, the initial Home status must arrive before motor pulses.
The fixture deliberately allows that pre-motion report delay; shutdown is checked
at the driver pulse boundary rather than every transient HOMING state.

The second case exposed a host timing mistake: boot_homing_foreground called the
ISR before the mock timer was armed. It now follows public driver wake/go_idle
callbacks and invokes interrupts only while the timer runs. No core change or
new defect classification. All thirteen ordinary boot homing controls pass focused
ASan/UBSan and strict summary (batch17-router-home-results.xml).
Total 3,266; batch 17 adds eight cases. Full gate required after this timer-fixture
change. The previous 3,264-case full sanitizer/strict gate passed in 63.28 s, with
nine expected failures and all 44 helper checks passing (batch17-checkpoint logs).

A third router/homing case now verifies dedicated home inputs separately from a
limit input that becomes asserted during travel and remains asserted. Homing
reaches the expected X pulse/reference endpoint, but completion reports failure
and sender error 45 because the final limit check remains engaged. The input is
supplied through the driver getter and normal homing callbacks; no private state
branch is forced. Focused sanitizer/strict summary passes (batch17-home-limit-
results.xml). Total 3,267; batch 17 adds nine cases. Prior full 3,266-case gate
passed sanitizer/strict checks in 61.87 s with nine expected failures and all
44 helpers passing (batch17-homing-checkpoint-results.xml). Revalidate the full
enlarged batch before eventual push. Core remains clean feebef2.

## Batch 17 reset offset and parking policies

Four normal-startup sender workflows cover reset retention. Two select G55,
set G92, and switch to incremental mode before reset; one also applies G43.1.
The $676 policy selects whether G55/tool mode is retained or G54 is restored,
while G92 remains and distance mode returns to absolute. Pre-reset observers
prove the requested offsets were active before the reset was consumed.
Two further cases configure parking's initial enabled/disabled policy, reverse
it with M56, and verify both parser and system overrides return to that initial
policy after soft reset. No simulated door motion or hardware claim is involved.

All four pass focused ASan/UBSan and strict summaries (batch17-offset-results.xml
and batch17-parking-results.xml). Full 3,269-case gate before the last two parking
cases passed in 131.32 s, with nine expected failures, strict summary and all 44
helper checks passing (batch17-reset-checkpoint logs/results). Total now 3,271,
13 new cases in batch 17. Run the enlarged full gate at the delivery boundary.
Core remote HEAD still feebef2 and PR 19 remains open at this check. Hosted batch
16 remains the measured baseline: 93.54% lines and 81.10% branches; no claim of
coverage increase is made for the unmeasured local additions. Persistent full
coverage goal was absent and has been recreated as active with the same guardrails.

## Batch 17 feature settings/report delivery checkpoint

Six further cases exercise eight-axis settings file completion: linear rates above
the driver's frequency limit are clamped while a configured rotary axis retains
its angular rate; linear rates exactly at or below the limit remain unchanged.
Backlash readback checks independent X/Y compensation through the public settings
API. Build reports advertise selected variable-speed spindle, enabled homing and
the cutter-compensation/lathe-UVW feature build. These check host configuration and
parser/report contracts, not physical driver performance or cutter geometry.

Focused six-case sanitizer/strict checks pass (batch17-feature-report-results.xml).
Full delivery gate now passes all 3,277 cases in 52.86 s, nine labelled expected
failures, strict summary and 44 helper tests (batch17-delivery logs/results).
Batch 17 adds 19 cases. Latest clean Terje core is still feebef2. Freeze this
checkpoint for hosted source/GCC/Clang/coverage/diagnosis and continue new work on
coverage-batch-18; do not treat the local pass as a new coverage percentage or
present a ready PR before the hosted gate completes.

## Batch 18 cutter parser contracts

Batch 17 frozen/pushed at 90b4ce9721e1e998dd453522362c0cd6ef6a808c; hosted run
38795069102 validates that exact head against clean Terje feebef2. Source selection
passed; compiler and coverage jobs are live at last check. New work is on
coverage-batch-18 and will not cancel that run.

Eight new cases use the existing accepting compensation-extension fixture (it
captures configuration, does not implement cutter geometry). Active G41/G42 rejects
G28/G30, canned drilling, probing, tool changes and tool-table geometry writes.
Assertions check no motion is queued, relevant tool/parser state remains intact,
and neither probe input sampling nor stream suspension starts on rejected blocks.
A positive control permits a G10 L2 work-offset write without changing cutter
radius/side. M2 cancels compensation, notifies the extension and emits program-end
feedback. Its host explicitly installs the normal report entry points/connection;
tool-change validation supplies the required no-ATC callback. Initial missing
fixture callbacks were corrected, not classified as core faults.
All 42 cutter cases pass ASan/UBSan and strict summary in 2.04 s
(batch18-cutter-results.xml). Total 3,285; full enlarged gate remains pending.

## Batch 17 hosted validation complete

All source/GCC/Clang/coverage/CI-diagnosis jobs passed run 38795069102 for frozen
90b4ce9721e1e998dd453522362c0cd6ef6a808c against Terje feebef2. Downloaded coverage
and source-lock artifacts confirm the exact harness/core revisions and the
header-inclusive core filter. Verified result: 16,530/17,625 lines (93.79%) and
11,103/13,648 branches (81.35%), 3,277 cases. Compared with batch 16 this adds 43
covered lines and 35 branches; denominators remain unchanged. Local artifacts:
../batch17-hosted-coverage-core.zip and ../batch17-hosted-source-lock-core.zip.
PR 19 remains open; do not merge it automatically or duplicate parent tests in
new PRs. These hosted percentages exclude local batch 18.

## Batch 18 tool geometry, arcs and homing notifications

Five lathe tool-table parser cases exercise G10 L1 orientation/angles, partial
radius updates retaining other geometry, inch length conversion without angle
conversion, and invalid fractional/above-nine orientations preserving saved data.
Three G20 IJK helical arcs in XY/XZ/YZ reach exact physical and logical motor
endpoints (254 steps in arc axes, 127 in the helical axis). Two rejected IJK arcs
exercise gross and relative radius mismatch limits while preserving and executing
the previously queued straight move without extra pulses.

Full 3,295-case ASan/UBSan gate plus strict summary and 44 helper checks passes
in 54.01 s (batch18-checkpoint logs/results). Two additional normal-startup homing
cases now pass focused sanitizer/strict checks: an actual realtime status request
during motor travel is answered before approach ends, and the extension receives
seek/pulloff/locate/pulloff modes with configured rates. Final X position/pulse
counts are checked in both. Total 3,297 / 20 new in batch 18. Full final gate
required before publishing this enlarged checkpoint; no new core exceptions.

Batch 18 final local gate passed all 3,297 cases in 62.04 s, nine expected
failures, strict summary and 44 helper checks (batch18-delivery logs/results).
Freeze/publish this head for exact-source Linux validation and continue independent
work on coverage-batch-19. Keep PR sequencing separate: PR 19 is still open at
the most recent live check; do not merge it or recreate its changes as a new PR.

## Batch 19 sender and extension protocol workflows

Batch 18 frozen/pushed at 7ce619699ba6dcee6b65bfedab0b7a8e5aa077d1; exact-head
hosted run 38796868694 is live against Terje feebef2. Source selection passed at
last check; GCC/Clang/coverage continue. New work is on coverage-batch-19.

Six new cases cover realtime parser-mode requests, deferred tool-offset reporting
with parser reporting enabled by $10, alarm-locked percent-delimited settings
uploads that still reject G-code, legacy feed hold/cycle-start with exact resumed
motor endpoint, and plugin bracket commands (case/spacing, returned errors and
alarm lock). These are real parser/protocol workflows, not flag-only assertions.
The TLO case uses normal CMD_STATUS_REPORT: full-status takes a separate report
path that does not schedule parser-change output. A normal query/empty line lets
the deferred report run before the host's synthetic exit. No core defect or
fixture change resulted from correcting that initial test assumption.
Focused ASan/UBSan and strict summaries pass (batch19-sender, batch19-plugin
results/logs). Total 3,303. Full enlarged gate remains pending.

## Batch 18 hosted validation complete

All source/GCC/Clang/coverage/CI-diagnosis jobs passed run 38796868694 for frozen
7ce619699ba6dcee6b65bfedab0b7a8e5aa077d1 against Terje feebef2. Downloaded artifacts
verify the exact harness/core source lock and header-inclusive filter. Coverage:
16,566/17,625 lines (93.99%), 11,135/13,648 branches (81.59%), 3,297 tests with
zero unexpected failures/skips. This adds 36 lines and 32 branches versus batch
17 without changing denominators. Artifacts are ../batch18-hosted-coverage-core.zip
and ../batch18-hosted-source-lock-core.zip. Core remote HEAD still feebef2.

## Batch 19 plugin settings, saved stream cleanup and fault diagnostics

Four registered plugin text-setting cases cover exact maximum length, oversized
rejection, clearing an optional string and masked password placeholder rejection.
They check stored/read-back text, owner save-before-change callbacks, and unchanged
other fields; they test core metadata plumbing, not the separate Plugins project.
One manual tool-change case uses core stream_rx_suspend/ack to back up pending
motion bytes, then sends stop. Both visible and restored buffers are discarded,
handlers return, no steps execute, and the driver cancel marker remains readable.

Public machine-mode changes on a registered laser-capable PWM descriptor select
lathe diameter programming with G7, then clear it when switching back to laser.
Normal boot homing also covers equal locate rates/different seek rates splitting
axes correctly, and an unbounded rotary A axis finding its switch and reference.
The USB failure case uses public DTR events: no diagnostics for dropped DTR or an
unrelated UART; matching USB DTR delays the generic self-test message, then emits
retained startup warnings in order while suppressing ordinary startup tasks.
The intentionally nonreturning fault loop is observed before the host exits.
Private incompatible-driver formatter reachability is recorded as a TODO question;
no forced private call, new defect exception or core patch is added.

Focused sanitizer/strict gates pass for every addition. Full 3,311-case checkpoint
passed in 63.95 s, then the final 3,312-case gate passed in 58.09 s, both with
nine expected failures, strict summary and all 44 helper checks. Evidence uses
batch19-{checkpoint,delivery} logs/results plus plugin-text/tool-stop/mode/homing/
usb-fault focused results. Batch 19 adds 15 cases. Freeze/publish for exact-head
Linux validation; continue independent work without treating the passing gate as
goal completion. Hosted batch 18 remains the measured coverage baseline.

## Batch 20 auxiliary-axis arc limits

Batch 19 is frozen/pushed at ca66c4d288c464050c5c238210d3c2f2c6295c52; exact-head
hosted run 38799824879 remains live against Terje feebef2. PR 19 (batch 14) is
still open at this check. New work is on coverage-batch-20.

Two eight-axis cases use a valid virtual already-homed A-axis setup with A-only
soft limits. An XY arc interpolating A completes all requested motor endpoints
through the actual checker/planner/stepper; XYZ limits are not imposed. A public
arc-checker case rejects A endpoints beyond either wall and accepts both exact
boundaries with XYZ checking disabled. No private geometry helper is invoked and
no core source/filter/exception changes are made. Focused ASan/UBSan and strict
summary pass (batch20-aux-arc-results.xml). Total 3,314; full enlarged gate pending.

Next useful area: ordinary soft-limit violations through public motion/protocol
workflows, including controlled stopping during an active move. Read the current
critical-event/hold fixtures before introducing a host observer; do not force
private loops or skip alarm/reset behavior to inflate coverage. Latest authoritative
coverage remains batch 18: 93.99% lines / 81.59% branches. Keep working while the
specific batch 19 hosted run is live; do not restart it because observation times out.

## Batch 19 hosted validation complete

All source/GCC/Clang/coverage/CI-diagnosis jobs passed run 38799824879 for frozen
ca66c4d288c464050c5c238210d3c2f2c6295c52 against Terje feebef2. Coverage and
source-lock artifacts verify exact revisions and the header-inclusive filter.
Result: 16,600/17,625 lines (94.18%), 11,171/13,648 branches (81.85%), 3,312 cases,
zero unexpected failures/skips. Compared with batch 18: +34 lines and +36 branches,
unchanged denominators. Artifacts: ../batch19-hosted-coverage-core.zip and
../batch19-hosted-source-lock-core.zip. Local batch 20 is not in these percentages.

## Batch 20 soft-limit alarm and controlled-stop workflows

Five additional cases use the real public motion/protocol/state-machine paths
on a valid virtual homed machine. An idle violation emits no steps and enters
soft-limit alarm; an active violation decelerates queued motion before the first
endpoint without setting position-lost. Both answer a public status request in
the critical loop, then accept an explicit reset. Driver reset notifications are
checked separately for automatic alarm shutdown and the sender reset. A reset
during deceleration retains the motion-abort alarm and position-lost status,
rather than overwriting them with soft-limit alarm. Two CoreXY variants validate
Cartesian limits and stopping of both coupled motors without position loss.
Assertions concern simulated output/state, not physical stopping distances.

The new shared fixture observes alarm entry and supplies normal HAL callbacks;
it never directly changes private alarm/hold state. Core source remains untouched.
All focused cases pass sanitizer/strict checks (batch20-soft-limit and
batch20-corexy-soft results). Full 3,319-case checkpoint passed in 54.68 s, strict
summary, nine expected failures and all 44 helper tests (batch20-soft-checkpoint
logs/results). Batch 20 adds seven cases so far; continue before delivery.

## Batch 20 G76 unit conversions and latest-core refresh

Five new parser-to-thread-plan captures check metric pitch, diameter/radius depths,
inch radial depths/Z endpoint, inch pitch and inch exit-taper length. Matched
programmed/measured spindle RPM is 2000 with Z max feed 5000 mm/min, so both correct
and current pitch values fit the configured feed capability. Inch pass counts may
include a float-rounding finishing pass; geometry checks assert cut depths and
endpoints rather than an incidental exact pass count.

Two assertions reproduce real G20 unit errors: P0.05 reaches the planner as 0.05
instead of 1.27 mm/rev; E0.125 leaves 0.125 rather than 3.175 mm of exit taper.
LinuxCNC's G76 length-unit reference and inch threading sample confirm the contract.
Correct assertions are retained in two separate, narrow expected-failure cases,
linked with cleanup instructions and proposed fixes in KNOWN_BUGS.md. No sanitizer
allowance or core patch. Metric/diameter/inch-depth controls pass.

Full 3,324-case gate on prior feebef2 passed in 62.92 s, strict summary/44 helpers,
11 expected failures (the previous nine plus these two). Before delivery, live
source refresh found Terje force-updated master to
4ec1ae44b857a70d2f9298344feac4b43ed0eb6b (62f25d4 plus type-mismatch fix).
After the old run completed, the clean ignored core checkout was updated; no
tracked source pin/submodule or production edits were introduced.

The unchanged paired-primary-stop and compatibility-10 $4 sender regressions now
exit successfully. Their obsolete WILL_FAIL blocks and bug entries are deleted.
G76 failures remain reproduced on 4ec1ae4 with updated exact-source links.
Three paired PWM cases further check concurrent up/down override ramps, retargeting
the primary without disturbing secondary progress, and stopping one while the other
reaches its target. RPM targets are independently checked within 0.01 RPM, then PWM
is checked at that accepted floating-point target to respect hardware quantization.
All 19 related focused cases pass sanitizer/strict checks with two G76 expected
failures (batch20-latest-focused-results.xml).

Total 3,327 / 15 new in batch 20; nine expected failures remain after removing two
fixed exceptions and adding two new regressions. Full latest-source gate is live
as batch20-latest-delivery. Do not present a ready delivery before it completes
and the frozen head passes hosted source/GCC/Clang/coverage/diagnosis.

Batch 20 latest-source full gate now passes all 3,327 cases in 113.54 s, strict
summary, nine expected failures and all 44 helper checks (batch20-latest-delivery
logs/results). Core 4ec1ae4 is clean. The paired-ramp and legacy enable-readback
regressions are ordinary passes; G76 P/E failures remain narrowly documented.
Freeze/push this 15-case checkpoint, validate its exact head against 4ec1ae4 on
hosted GCC/Clang/coverage, and continue new work on coverage-batch-21 while it runs.
The latest measured percentages (94.18% lines / 81.85% branches) still describe
batch 19 on prior feebef2; compare raw denominators when the updated-core report
arrives. Do not count source changes as test-only coverage improvement.

## Batch 21 startup spindle hooks, sleep recovery and sender message clearing

Branch coverage-batch-21 starts at frozen/pushed batch 20 3be1df6. Core remains
clean detached Terje 4ec1ae44b857a70d2f9298344feac4b43ed0eb6b. Batch 20 exact-head
hosted run 38804109761 has passed source selection; GCC/Clang/coverage are still
running at this check. Latest completed coverage remains batch 19, not batch 21.

Six new separate cases bring the local suite to 3,333. Spindles are registered
in driver initialization, before setup finishes. Tests check mutable selection
capabilities before the selected notification, vetoed selection retaining the
self-test fault loop, programmed callbacks preceding start/stop driver commands,
and repeated M3 with a new speed notifying without a direction change.
Sleep recovery uses actual $SLP, status and reset commands, then verifies the
warm parser defaults and retained unlock alarm. The simulated sender must stay
connected while reset is pending; suppressing its synthetic EOF exit fixes the
initial host-only failure. No production workaround was needed.
A reporting API case checks that Message_None clears a sender's G-code message,
program-end feedback does not, and clearing remains valid without a hook.
The startup five pass focused ASan/UBSan and strict summary (0.35 s). The complete
3,333-case sanitizer/strict/helper checkpoint is batch21-checkpoint, currently
running. Continue independent gaps after recording its result; do not present
this small checkpoint as completion of the full coverage objective.

Batch 21 checkpoint completed: all 3,333 cases pass (nine documented expected
failures), 50.46 s, strict summary and all 44 helper tests pass. Batch 20 hosted
run 38804109761 is now fully green (source, GCC, Clang, coverage, CI diagnosis).
Artifacts verify harness 3be1df626d0c1d1b8834f549b8c3de84ae5a2d90, core
4ec1ae44b857a70d2f9298344feac4b43ed0eb6b, core C/header filter. Measured coverage:
16,619/17,624 lines (94.30%) and 11,187/13,648 branches (81.97%). The denominator
changed with the core refresh; this is not solely a test gain from batch 19.
On 2026-10-16 live refresh, Terje master remains 4ec1ae4; PR 19 remains open.
Continue report/parser and supported feature gaps on batch 21; no ready PR yet.

Batch 21 now adds 13 cases / 3,340 total. Seven further cases check deferred
G66/G67 reporting without executing the macro, dynamic cutter-compensation
reporting and completed G40 cancel, CAN advertisement only after successful
driver startup, G96/G97 surface-speed/RPM reporting, M70 replacement/M71 hook
lifecycle, and sender stop discarding future motion messages and synchronized
outputs. All focused checks pass; no core edits or new exceptions.
The CSS reporting test initially omitted report_init (formatter setup), and the
modal feed test used an unnecessarily rounded imperial decimal. Proper report
initialization and exactly representable F10 inches/min (254 mm/min) fixed these
host/assertion issues before delivery. Do not classify them as core failures.
Full batch21-final passes 3,340 cases in 54.71 s with nine expected failures;
strict summary and all 44 helpers pass. Earlier 3,338 gate passed in 104.12 s.
Freeze/push this checkpoint, verify exact-head hosted GCC/Clang/coverage against
4ec1ae4, and continue work on coverage-batch-22. PR 19 remains open; do not merge.
Latest measured coverage is still batch 20 (94.30% lines / 81.97% branches).

## Batch 22 sender descriptions and tool/lathe reports

Branch coverage-batch-22 starts from pushed/frozen d4dc212195c0789f210f211986580fc72e18b86b.
Batch 21 run 38866070072 is validating that exact head against clean core 4ec1ae4;
source passed, compiler/coverage jobs are still running at last check.
Seven new cases / 3,347 total pass focused sanitizers and strict summaries:
- $SED=1001 includes a reboot note after a registered plugin description,
  starts the note without escaped blank lines when no description exists,
  and emits nothing for hidden settings.
- Named tool coordinate rows preserve names and optional pockets, with each
  5 ms driver pacing call following its completed row.
- Compatibility 2 keeps the documented fixture placeholder in TLR@ output.
- Actual mode-setting changes enable/clear the LATHE build capability token.
- G7 coordinate reports double X once; serial inches convert once and preserve
  G21 parser mode and the stored millimeter fixture coordinates.
Evidence: batch22-setting-description-results.xml (0.36 s),
batch22-tool-report-results.xml (0.27 s), batch22-lathe-report-results.xml (0.36 s),
matching strict summary logs. Core unmodified, no new exceptions or TODOs.
Continue independent source/configuration gaps before the next full delivery gate.

Batch 22 now adds nine cases / 3,349 total. A compact table-driven parser case
rejects incomplete/misspelled O-code keywords, preserving parameters, alarm and
planner state, and proves a valid IF block still works afterward. A paired PWM
case uses M73 inside a public macro call scope, stops both spindles, then checks
that return restores each saved direction/RPM with independent monotonic hardware
ramps capped at its own target. Focused sanitizer/strict checks pass for both.
The full batch22-checkpoint passes all 3,349 cases in 45.15 s with nine known
expected failures, strict summary and all 44 helper tests. No core changes.

Batch 21 hosted run 38866070072 coverage passed: 16,645/17,624 lines (94.45%) and
11,216/13,648 branches (82.18%). Artifacts verify d4dc212195c0789f210f211986580fc72e18b86b,
core 4ec1ae44b857a70d2f9298344feac4b43ed0eb6b and the core C/header filter. Hosted
coverage JUnit has 3,340 cases, zero failures/skips. Source also passed; GCC/Clang
remain in progress at last check. Verify their completion before any ready PR.

## Batch 21 hosted leak diagnosis and batch 22 isolated regression

Hosted run 38866070072 finished: source/coverage pass, GCC/Clang/diagnosis fail.
Both compiler artifacts report the same direct 12-byte LeakSanitizer allocation
from gc_normalize_block (gcode.c:1146), reached by the new sender-stop message
case. The parser duplicates that comment into plan_data.message (4104-4105)
but does not release its original local message. Planner reset frees the copy.
Windows ASan lacks this Linux leak detection; local clean results did not prove
leak freedom. Hosted coverage percentages remain valid but the run is not green.

A new portable ownership case observes real malloc/free calls only during a
normal message-bearing parser move and subsequent public planner reset. It
requires zero outstanding bytes regardless of the number of allocations. Raw
local reproduction leaves 12 bytes and fails its correct assertion. A single
WILL_FAIL entry and dated KNOWN_BUGS.md entry record the defect, source links,
proposed ownership cleanup and removal instructions. No sanitizer allowance.
The observer's linker options remain part of the permanent regression.
The existing sender-stop test now queues a plugin-supplied heap message through
public mc_line and verifies accepted planner ownership before the same sender
stop path. This keeps cancellation assertions ordinary and independent of the
parser allocation defect. Both old Linux failure artifacts are saved in parent
batch21-hosted-results-core-{gcc,clang}.zip.

One more Modbus case confirms a valid async request with NULL callbacks accepts
its reply and releases the bus for the next callback-bearing transaction.
Batch 22 now adds 11 / 3,351 total, ten expected failures. Focused checks pass;
full batch22-final is running. Keep core 4ec1ae4 unmodified. Push a validated
checkpoint and verify Linux GCC/Clang/coverage before a ready PR; do not rerun
unchanged batch 21 and expect its leak failure to disappear.

Batch22-final completed: 3,351 cases pass, ten documented expected failures,
44.52 s, strict summary and all 44 helpers pass. Core remains clean 4ec1ae4.
Freeze/push this checkpoint, dispatch exact-source hosted validation, then work
on coverage-batch-23 while it runs. The lifetime regression is an expected
failure; the ordinary sender-stop case must pass under Linux LeakSanitizer.

## Batch 23 motion-message execution and realtime coordinate offsets

Branch coverage-batch-23 starts from pushed b59409f1b666e3a89b2a7d9b177261a3f7692fd3.
Core remains clean Terje 4ec1ae4. Batch 22 run 38867880603 source/coverage passed;
GCC/Clang remain running at last check. Its exact-head artifacts verify harness,
core and C/header filter. Coverage: 16,659/17,624 lines (94.52%), 11,238/13,648
branches (82.34%). This does not include local batch 23.

Six new separate motion cases / 3,357 total:
- A plugin-supplied message stays queued until its own move executes, is delivered
  once, and is consumed by its plugin UI handler. Two queued messages preserve
  move order and physical move boundaries.
- Clang detects the core's explicit char-pointer-to-void-pointer callback cast
  when those foreground messages run. Behavior assertions pass. A dated known
  portability entry links the exact scheduler invocation and callback definition,
  gives a typed-adapter proposal, and documents the single exact manifest match.
  Do not describe this as a demonstrated controller crash. No WILL_FAIL is added.
- Queued G92 changes and G92.2 suspension keep the executing block's offset until
  the next block starts. Actual status samples at physical X0.5/X1.5 verify WPos
  and WCO together, and the block transition requests one forced WCO report.
  The shared endpoint is deliberately not assigned to either block prematurely:
  its last step can occur before the next segment loads. Initial boundary-only
  assertion failures were corrected as test timing assumptions, not core bugs.

Focused evidence: batch23-message-results.xml (0.35 s, two precisely classified
recovering diagnostics), batch23-wco-results.xml (0.27 s), batch23-status-results.xml
(0.44 s). Earlier full 3,353-case gate passed in 45.12 s, strict summary and all 44
helpers, ten expected failures and two known recovering diagnostics. Full expanded
3,357-case batch23-final is running. No core edits; continue meaningful supported
workflows, not private-state forcing or arbitrary tiny-buffer exercises.

Batch23-final completed: all 3,357 cases pass in 49.13 s, strict summary and all
44 helpers pass. Ten expected failures plus two ordinary assertion-passing cases
with the narrowly classified recovering callback-type warning. Core remains clean.
Batch 23 is local; continue more supported motion/configuration gaps before its
next substantial push/hosted boundary. First verify batch 22 hosted compiler
completion; do not confuse its passed coverage job with a green overall run.

Batch 22 run 38867880603 is now fully green: source, GCC, Clang, coverage and CI
diagnosis. The ordinary stop-message case passes Linux leak checks; the isolated
portable ownership regression reproduces the documented failure as intended.
Terje master refreshed on 2026-10-16 remains 4ec1ae4; local core is unmodified.

Four new G33 parser-to-stepper cases bring batch 23 to ten new / 3,361 total.
The encoder model turns independently of tool travel, acquiring indices before
the simulated driver wakes. Timer interrupts run only between its wake/idle HAL
callbacks, including repeated synchronized moves. Cases check metric Z1/K1,
G20 Z0.1/K0.05 (2.54 mm endpoint rounds to 203 steps, pitch 1.27 mm/rev), negative
Z travel with positive pitch, and a following G33 reusing its prior K value.
Metric restores prior override policy; all cases check physical step outcomes.
Focused sanitizer/strict checks pass (batch23-sync-results.xml, 0.39 s). No new
exceptions. Full batch23-delivery is running; freeze/push only after completion.

Batch23-delivery completed: 3,361 cases pass in 59.47 s, strict summary and all
44 helpers pass. Ten expected failures and two narrowly classified recovering
callback-type warnings; no unexpected diagnostics. Freeze/push this ten-case
checkpoint, dispatch exact-head hosted validation against 4ec1ae4, then continue
on coverage-batch-24. Parser-driven G95 with measured encoder RPM (including
changes during motion) is a useful next gap beyond direct planner-only coverage.

## Batch 24 G95 parser motion continuation

Current branch coverage-batch-24 starts at pushed/frozen batch 23
7398414136b859ba15c00a9f48e85d211e1e1e04. Hosted run 38869601270 is validating
that exact head against 4ec1ae4; still in progress. Latest fully green baseline
remains batch 22 run 38867880603 (94.52% lines / 82.34% branches).
One new uncommitted case brings the local suite to 3,362:
spindle_sync.parser_g95_executes_feed_per_revolution_without_index_wait.
Its real G95/G1 parser block executes 80 Z steps using measured RPM, retains the
normal pulse handler, and never requests angular/index feedback. Focused ASan/
UBSan and strict summary pass (batch24-g95-results.xml, 0.22 s).
Continue the module before a commit/push/full-gate boundary. Useful next work is
G95 response to changing measured RPM during motion. Advance engine_ticks from
actual HAL timer periods, not arbitrary ISR counts, and use realistic acceleration
so the selected feed can be reached before sampling. Keep feedback independent
of requested axis travel. Do not force private planner/stepper state to reach a
coverage branch. No live local build/test process remains at this checkpoint.

Batch 24 G95 module completed: nine new / 3,370 total. The virtual clock derives
elapsed milliseconds from real HAL timer periods (1 MHz driver timer), not an
arbitrary number of ISR calls. Encoder angular feedback advances independently
of axis displacement. External RPM changes are injected at elapsed-time events.
The public Z acceleration setting is 100 mm/s^2 so cruise sampling is meaningful.
Measured physical step/time windows (2 mm each) show:
- 100 -> 200 RPM: 100.053 -> 200.321 mm/min at F1 mm/rev.
- 200 -> 100 RPM: 200.321 -> 100.053 mm/min.
- 50% feed override: 50 -> 100.053 mm/min across the same RPM increase.
- Queued G95/G94: 100.053 -> 150 mm/min; G94 ignores a later zero-RPM reading.
All preserve exact 800-step Z endpoints. Separate cases check constant feed,
inch F/endpoint conversion (203 steps for 2.54 mm), lathe radial feed without
index acquisition, G0 with zero RPM, and G95 zero-RPM alarm without driver wake.
All focused sanitizer/strict checks pass. No new exceptions or core edits.

Full batch24-final: 3,370 cases pass in 54.66 s, strict summary and 44 helpers
pass; 3,358 clean, ten expected regressions and two previously documented
recovering callback-type warnings. Earlier eight-case gate passed in 52.08 s.
Batch 23 coverage artifact validates 7398414136b859ba15c00a9f48e85d211e1e1e04,
core 4ec1ae4 and core C/header filter: 16,664/17,624 lines (94.55%),
11,244/13,648 branches (82.39%). Hosted GCC/Clang are still running at last check;
coverage is passed, but do not call the overall run green yet.
Terje master was freshly fetched and remains 4ec1ae4.

Freeze/push batch 24 and validate its exact head; continue on batch 25 with public
planner allocation fallback and retry under plausible constrained MCU heap
budgets. Verify usable capacity/motion and clean retry, rather than asserting
one particular internal decrement sequence or forcing private static state.

## Batch 25 planner heap fallback and override observers

Branch coverage-batch-25 starts from pushed ea7cdd675648041e6c29c6d94289435383d1bf50.
Exact-head batch 24 hosted run 38871019194 is in progress against 4ec1ae4. Batch 23
run 38869601270 is now fully green (source/GCC/Clang/coverage/diagnosis), with
16,664/17,624 lines (94.55%) and 11,244/13,648 branches (82.39%). PR 19 remains
open at this live check; continue independent work and do not merge it.

Six new cases / 3,376 total:
- Request 256 or 64 planner blocks with allocator ceilings corresponding to 128
  or 48 usable blocks. These model the largest contiguous allocation available,
  not total MCU RAM. Assert reduced capacity fits the ceiling, fill every usable
  slot with real planner lines, verify full detection, then clear/reuse capacity.
  Do not assert one particular fallback decrement sequence.
- At the valid normal 35-block setting, an allocation failure returns false;
  restoring allocator availability permits a clean successful public retry.
- Normal controller boot under the larger ceiling reports the reduced-capacity
  warning, keeps the configured request, and responds to the sender's $G query.
- Individual feed and rapid override changes notify the matching observer once,
  apply the expected nominal rate, and do not re-notify on unchanged repeats.
Focused sanitizer/strict evidence: batch25-boot-results.xml (four, 0.35 s) and
batch25-override-results.xml (two, 0.30 s). No core edits or new allowances.
Two source-review questions are in TODO.md: complete planner exhaustion handling
at startup, and whether combined feed/rapid changes need two observer events.
Neither is registered as a confirmed failure or an enforced new policy.
Full batch25-checkpoint is running. Continue remaining supported planner/motion
paths before another substantial push boundary; keep the current goal active.

Batch25-checkpoint completed: all 3,376 cases pass in 53.02 s, strict summary
and all 44 helpers pass. Ten expected regressions and two previously documented
recovering callback warnings; zero unexpected diagnostics. This six-case planner
checkpoint is local-only; continue on batch 25 before its next delivery boundary.
Core 4ec1ae4 remains clean; no live local build/test process remains.

Batch 25 adds three further public-workflow controls: partial planner-ring reuse
with FIFO order, plugin feed metadata normalization, and CSS RPM clamping at a
small positive radius. The nine-case batch totals 3,379 cases. Full
batch25-delivery-results.xml passed in 59.72 s against clean 4ec1ae4, with strict
summary and all 44 helpers passing (ten expected failures, two known warnings).

2026-10-17 refresh: batch 24 run 38871019194 completed successfully. Its exact
coverage is 16,682/17,624 lines (94.66%) and 11,252/13,648 branches (82.44%).
Terje master advanced to ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216. Full rebuild
and verification of message ownership/callback and G76 exception cleanup are
in progress; the old-source pass does not establish latest-source readiness.

Latest-core verification complete: all 3,379 cases passed in 105.00 s, strict
summary and all 44 helpers passed. Source ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216
remains clean. Removed three fixed WILL_FAIL exceptions (G76 inch pitch, G76
inch taper, parser-message ownership), the one callback sanitizer manifest entry,
and their three bug sections. All original correct assertions and allocation
instrumentation remain. Seven expected failures remain; no diagnostic allowances.
Freeze/push batch 25 and continue independent work on batch 26 during hosted CI.
The untracked curve-stop fixture is a proposal, not part of this verified total.

Batch 26: eleven sender stop/hold cases, 3,390 total. Six stop cases cover CW/CCW,
helical and multiturn arcs, cubic and quadratic splines. Five hold cases cover
arc, helical arc, inch arc and both spline forms. They prove planner-full and
first-line generation at injection, exercise protocol_main_loop and actual step
interrupts, verify parser/physical alignment after stop, unchanged position during
32 paused foreground iterations, resumed endpoint and subsequent relative move.
Focused batch26-curve-results.xml: eleven passing, 0.68 s. Full
batch26-checkpoint-results.xml: all 3,390 pass, 45.12 s; strict summary and all
44 helpers pass. Seven expected failures, zero unexpected sanitizer diagnostics.
The initial hold-fixture CMD_EXIT crash was a missing coolant shutdown callback,
corrected in the fixture; it was not a core defect. Clean source ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216.
Batch25 exact-head hosted run 38985300867 is validating a1eaed8; do not call green
until all jobs complete. Freeze/push batch26 and continue batch27 while CI runs.

Batch27: five new drilling cases, 3,395 total. Actual sender stop/hold through
protocol_main_loop covers G81 repeated holes, G73 chip break and G83 peck drilling.
Fixtures now use segmented_* names because the same public streaming machinery
covers curves and drilling. All eleven previous curve controls are revalidated.
G83 hold/resume completes all holes and the following relative move. During
peck dwell the planner may legitimately be empty; the fixture now waits for the
follow-up motion to start and finish rather than treating a synchronization gap
as program completion. Long peck programs have a larger bounded service budget.

New known defect, dated 2026-10-17: G83 stop restores actual Z=-0.25 mm, then the
cycle changes parser Z to R=1 mm after cancellation. Following G91G1X1F100
unexpectedly moves Z to +1 mm. Source-linked reproduction/proposal and single
exception cleanup are in KNOWN_BUGS.md. Correct parser/physical assertions remain;
no core edits or sanitizer allowances. G73/G81 stop and G83 hold are controls.
Focused batch27-segmented-results.xml: 16 cases, 0.92 s. Full
batch27-checkpoint-results.xml: 3,395 pass, 46.83 s; strict summary and 44 helpers
pass, eight expected failures, zero unexpected diagnostics.

Hosted batch25 run 38985300867 source/GCC/coverage pass, Clang pending. Coverage
artifact verified harness a1eaed84aa9c9d9c9eaf5ee97102fa1d0aeec4e9 and source
ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216, core/.*\.[ch]$ filter:
16,697/17,630 lines (94.71%), 11,270/13,648 branches (82.58%). Source changed the
denominator from batch24. Batch26 run 38985624501 source/coverage pass, compilers
pending. Freeze/push27, continue28 while checking hosted completion at useful
intervals. PR19 still open; no new ready PR has been claimed.

Batch28: six fast-motion cases, 3,401 total. Public axis settings configure
15,000 mm/min maxima and 200 mm/s^2 acceleration; programmed 12,000 mm/min moves
reach cruise. Timer periods over a 60 mm X pulse window verify feed (1% allowance)
for linear/coordinated motion; round-trip pulse totals and origin are exact.
Two sender override cases drop to 10% at X147 across ten short collinear CAM
segments, measure 1,200 mm/min over X260..280 (2% allowance), and optionally
restore 100%. A fast hold case spans short blocks and resumes to the exact endpoint.
No motor physics or physical missed-step claim is made. The initial prequeue
timeout was fixture capacity misuse; twelve blocks now fit the checked planner.
Focused batch28-fast-results.xml: six pass, 0.44 s. Full
batch28-checkpoint-results.xml: 3,401 pass in 45.25 s; strict summary and all
44 helpers pass, eight expected failures, no unexpected diagnostics.

Hosted batch25 run38985300867 and batch26 run38985624501 are fully green,
including source/GCC/Clang/coverage/diagnosis. Batch26 artifacts verify exact
011a464df07c7532ea643400bf8c2a2950210ea6/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216
and core/.*\.[ch]$ filter: 16,705/17,630 lines (94.75%), 11,283/13,648 branches
(82.67%). Batch27 run38986131807 is still pending. Push28/dispatch, continue29
with supported VFD CSS callbacks while CI runs. No new PR claimed ready.

Batch29 local VFD checkpoint: eight cases, 3,409 total, full
batch29-checkpoint-results.xml passes in 44.90 s, strict summary and all 44 helpers
pass. Eight expected failures, no sanitizer allowances. VFD drivers register
before gc_init and use real G0 positioning for initial radius. CSS inward/outward,
RPM clamp, diameter interpretation, axial constant speed and G97 are observed
through both RPM/state callbacks and actual pulses. Sender override/reset and
M5 preserve correct RPM/off behavior without PWM. No physical VFD/bus test claim.

Fixture corrections: normal cold-start tool initialization and coordinate records
are required; public acceleration/feed keep logs bounded. Fixed-speed assertions
observe live RPM during pulses rather than demanding a particular callback count.
A disabled VFD may harmlessly receive zero RPM again. No new defects/allowances.
Keep batch29 local while extending another public parser/driver workflow before
the next push. Candidate: G10 L0 tool-table reload and transactional rejection.

Batch29 expanded delivery: 22 new cases, 3,423 total. Four G10 L0 cases verify
backend success/offset refresh, error preservation and later retry, missing
backend and rejection before callback with a tool loaded through M61. Seven
arc/G93 cases preserve and execute an earlier queued move after bad radius/plane/
turn-count or missing inverse-time feed; a rapid control needs no F under G93.
G93/G33 uses encoder pitch, restores overrides and leaves a later G1 requiring F.
Two real boot cases register PWM during init and VFD during setup, initialize
the unused PWM off before VFD configuration and preserve saved/locked RPM ranges.
These supplement the eight previously verified VFD motion/override cases.

Full batch29-delivery-results.xml: 3,423 pass, 44.87 s; strict summary and all
44 helpers pass, eight expected failures and no sanitizer allowances. Source
ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216 is clean and still latest at a second
live fetch. No new faults or exceptions.

Batch27 run38986131807 and batch28 run38986684127 are fully green, all five jobs.
Batch27 coverage: 16,709/17,630 lines (94.78%), 11,290/13,648 branches (82.72%).
Batch28 coverage: 16,714/17,630 lines (94.80%), 11,297/13,648 branches (82.77%).
Artifacts verify exact 7ee98e1d55afd45161ebf6bd8bd5dc78b73042ec /
eb44ea97c96493fe1acfd11a57987fd6bc367402 respectively, source ad57c78 and the
core/.*\.[ch]$ filter. Push/dispatch29; continue30 with public stream/VFS ownership
while CI runs. The EEPROM double-increment warning question already exists in
TODO; do not duplicate it or force its unreachable warning via private state.

Batch30: twenty new cases, 3,443 total. UART close verifies file closure after
successful release and ownership retention across a failed release/retry. Five
MPG cases cover active/inactive realtime toggle, handler registration, no previous
handler on disable and protected registered-stream disconnect. Inactive top-bit
commands are consumed without taking control; an initial false-drop expectation
was corrected against the public dispatcher contract, not classified as a defect.
Four real protocol file cases cover CRLF, missing final LF, empty file and parser
error/EOF status with restored sender queries. A boot integration queues plugin
commands through alarm rejection, $G, $X and successful G20/G91 recovery.

Eight G76 cases use a driver registered before parser initialization, public M3
and G0 positioning and independent encoder rotation. They count emitted radial/
axial pulses and clearance for external/internal cuts, reverse Z, two spring
passes, inch pitch/depth, diameter mode and entry/exit tapers. Sender stop during
the first cut discards later/spring passes and preserves an X-only relative
restart. No physical cutting or hardware timing claim. The shared stop fixture
accepts a service hook for encoder-index acquisition; all prior stop controls pass.
Focused thread suite eight passes, 0.58 s. Full batch30-delivery-results.xml:
3,443 pass, 45.15 s; strict summary and 44 helpers pass, eight expected failures
and zero unexpected diagnostics. No core changes or new allowances.

Hosted batch29 run38987951245 is fully green: source/GCC/Clang/coverage/diagnosis.
Artifacts verify harness 1aa39e0dd924915c96f33d3b448f916deab3c006, clean source
ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216 and core/.*\.[ch]$ filter. Coverage:
16,747/17,630 lines (94.99%), 11,327/13,648 branches (82.99%). Push/dispatch30 and
continue31 with supported cold-boot coordinate recovery while CI runs.

Batch31 in progress: seven boot record cases bring the suite to 3,450. Full
batch31-checkpoint-results.xml passes in 47.41 s, strict summary and all 44 helpers
pass (eight expected failures). Four additional loaded input-configuration cases
pass focused sanitizer/strict checks, bringing the current total to 3,454.

Cold boot cases inject one driver read failure for G54, persisted G92 or either
startup script record. They verify an error, zero/empty recovery of just the bad
record and preservation/execution of healthy neighbors. Valid G54/G92 controls
observe loaded WCO callbacks; volatile G92 ignores but does not delete saved data.
Fixture corrections were lifecycle/timing: grbl_enter frees NVS on return, so
records are captured before the sender query; startup execution is deferred, so
the observer waits for the actual read failure rather than consuming it itself.
These sanitizer failures were fixture mistakes, not core defects.

Four loaded input tests observe FeedHold inversion/debounce priority, Probe and
MotorFault inversion/debounce, and MPG select pull-up request. No assertion about
processor/protection electrical behavior or disabled-pullup contract is added.
Focused batch31-input-config-results.xml: four pass, 0.42 s. Full expanded gate
and commit still pending. Current work is uncommitted on batch31; source unchanged.
Batch30 exact4047920 run38989130871 is validating while local work continues.

Batch31 delivery: nineteen new cases, 3,462 total. Seven boot-record and four
loaded input cases are joined by five fast jerk cases (linear/coordinated/return,
override and hold) and three jerk/profile combinations (linear/coordinated/return
with profile change). Public settings configure jerk at 1,000 mm/s^3 and 400 mm
axis travel. P5 is 20%, P1 restores 100%; reduced-profile moves use 5,000 mm/min
so the timer window is at cruise. An initial P10 command was an invalid fixture
assumption and was corrected to supported P1. Jerk deceleration needs more travel
than the ordinary control; its reduced-feed sample now spans X280..290 rather
than the still-decelerating X260..280. Both require 1,200 mm/min within 2%, and all
original endpoint/pulse assertions remain. Shared hold checks were factored into
fast_short_hold_host.h; all ordinary and jerk controls are revalidated.

Full batch31-delivery-results.xml: 3,462 pass in 46.22 s, strict summary and all
44 helpers pass. Eight expected failures, zero unexpected diagnostics, no new
core bugs/allowances or core edits. Freeze/push31 and continue32 while CI runs.

Batch30 run38989130871 source/GCC/Clang/coverage pass, diagnosis pending. Coverage
artifacts verify exact4047920c8a5acaec84c322c3e9b7bd27f3757079 and source
ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216 with core/.*\.[ch]$ filter:
16,761/17,630 lines (95.07%), 11,344/13,648 branches (83.12%). Last fully green
run remains batch29 until that final diagnosis is verified. Next supported gaps:
build-report capability advertisement, actual M60 pause reporting and allocator
fallback for a complete settings listing. Leave unreachable/private paths alone.


## Batch 32 reporting checkpoint - 2026-10-17

Seven new cases total 3,469. Public build reports advertise REBOOT only with
a driver handler and PPI only with its driver capability; reporting never invokes
the reboot handler. M60 is observed during the actual parser pause callback.
Two plugin registries verify later-group lookup and unknown-topic exhaustion.
Two correct settings-list selection regressions reproduce the allocation fallback
omitting normal visibility/availability and legacy-only filters. Ordinary
allocation controls pass. Narrow WILL_FAIL entries and dated source evidence,
proposal and cleanup are in KNOWN_BUGS.md; no sanitizer allowances or core edits.

Full batch32-delivery-results.xml: 3,469 pass in 46.49 s, ten expected failures,
strict summary and all 44 helpers pass. Source remains clean Terje
ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216. Freeze/push and dispatch exact-source CI.

Batch31 run38990060016 passed every job. Downloaded source lock and coverage
verify harness46c984e4283b777ad8ed29c5d44c0d9667a389e5 / ad57c78 and
core/.*\.[ch]$ filter: 16,772/17,630 lines (95.13%),
11,362/13,648 branches (83.25%). Batch30 run38989130871 diagnosis also succeeded.
PR19 remains open on live check; subsequent batches remain cumulative branches.


Batch33 local continuation from pushed8c0f688: two real parser spindle-start
wait cases pass focused sanitizers (0.25 s, batch33-spindle-results.xml).
A sender reset at100 ms aborts before1000 ms feedback, turns the spindle off,
notifies driver reset/coolant stop and emits no at-speed event or timeout alarm.
A sender status request during the wait is answered before600 ms readiness,
then startup finishes normally. Required reset HAL callbacks were supplied after
an initial fixture-only null callback; no core issue or exception was registered.
Cases remain uncommitted pending a larger module checkpoint/full checks.

Batch33 spindle checkpoint: full3,471-case ASan/UBSan suite and strict summary
pass in46.00 s (batch33-checkpoint-results.xml). Two further computed O-label
cases pass normal file parsing: IF/ELSE label expression matching and WHILE
rewind using a parameter label with a literal matching ENDWHILE. Focused
batch33-computed-label-results.xml passes0.25 s. Current total3,473; final full
gate and larger batch checkpoint remain pending. Hosted batch32 exact8c0f688
run39017513432 is still in progress at last live check. Core fetch confirms
ad57c78 remains latest and clean. No additional exceptions or core modifications.


Batch33 delivery: six new cases,3,475 total. Common mill header resets a prior
G20/G91/G18/G93/G99 state before a metric linear move; no header pulses, then
exact800X/400Y pulses. G91.1 arc with absolute endpoints produces80X/80Y pulses.
Full batch33-delivery-results.xml passes46.56 s; strict summary and all44 helpers
pass, ten existing expected failures, no new exceptions/diagnostics/core edits.
Freeze/push/dispatch33 and continue34 with normal laser hold/resume workflows,
using registered driver and public realtime commands. Hosted32 remains running.


## Batch34 laser hold and safety-door workflows -2026-10-17

Seven separate cases total3,482. Registered PWM laser drivers use real parser,
stepper and realtime commands. M3/M4 hold-disable options verify output off while
stationary and restored powered completion; disabling that option intentionally
retains M3 constant power while M4 reaches zero PWM when motion stops. A50%
spindle override while held leaves output off and limits resumed PWM to250.
All20 mm cuts finish exactly1,600X pulses with no position loss.

Safety-door tests configure valid homed Z=-10 mm and parking enabled; both M3
and M4 disable laser output without any Z parking pulses. An open door blocks
cycle start; closing alone remains suspended; explicit start finishes the powered
cut. Shared ordinary parking setup was factored, preserving its existing behavior.
The five-case3,480 gate passed46.40 s and strict summary;44 helpers passed the
four-case checkpoint. Final3,482 sanitizer/strict/helper gate runs as session99799,
batch34-final-results.xml and parentlogs. No new exceptions or core modifications.

Hosted32 run39017513432 fully passes source/GCC/Clang/coverage/diagnosis. Artifacts
verify8c0f688de5ff612a4a12e639113fd55893bf3c4a/ad57c78 and core/.*\.[ch]$:
16,781/17,630 lines95.18%,11,373/13,648 branches83.33%. Hosted33 exact8282b95
run39017951972 remains in progress. Continue beyond these module checkpoints.

Final gate initially found the stronger constant-laser powered-resume check
failing with implicit fixture hold flags. Door fixtures now explicitly configure
Setting_HoldActions=3 and declare the door capability before execution. Both
focused cases pass with actual restored PWM and enabled driver state. No assertion
was removed: initial power, stationary off, powered resume, exact pulses/no Z
parking remain required. No core defect was registered. The earlier verbose
check without LLVM runtime PATH failed to launch; rerun with PATH passed. Final
full gate restarted after fixture changes as session88025; poll that live handle.

Batch34 final:3,482 pass in46.13 s (batch34-final-results.xml), strict summary
and all44 helpers pass. Ten existing expected failures; no allowances/core edits.
All seven laser cases and existing ordinary parking cases pass after shared
configuration extraction. The session88025 process completed successfully.
Freeze/push/dispatch34 and continue35. Useful next supported workflow: a plugin
WCO-saved observer installed before tc_init, actual G10 while manually changing
a tool, then public completion/resume. Avoid overwriting captured hooks.


## Batch35 WCO observer and manual tool completion -2026-10-17

Five new cases total3,487. Public WCO observer is installed before tc_init; real
G10 updates notify it, repeated init keeps one notification, saving G55 leaves
a current-G54 touch-off wait blocked, and saving G54 releases it. A changed Z
work offset causes an actual160-pulse return to Z=-2 mm; the initial timeout
was a missing fixture realtime step service, fixed before interpreting results.

A full open-door manual-completion sequence reaches Idle with old parser tool0
and zero tool-changed notifications after explicit close/resume, while closed-door
T3M6/control selects3 and notifies once. No motion occurs in the door case.
Correct assertions retained; one dated KNOWN_BUGS entry, exact verified source
links, proposal and narrow WILL_FAIL block added. No core edits or sanitizer
allowances. Final full gate session77678 is running, batch35-delivery-results.xml
and parentlogs. Latest core fetch confirms clean ad57c78 remains latest.

Batch33 run39017951972 passes all hosted jobs; artifacts verify
8282b95a6b5422aa092b481a6ca75706ed269b72/ad57c78 and core/.*\.[ch]$ filter:
16,789/17,630 lines95.23%,11,378/13,648 branches83.37%. Batch34 run39018542932
remains in progress at last check. Continue substantive coverage after this gate.

Batch35 delivery: full3,487 pass in46.89 s, strict summary and44 helpers pass.
Eleven documented expected failures, no sanitizer allowances. Session77678
completed successfully. Freeze/push/dispatch35 and continue independent work.


## Batch36 supported parser/tool-axis configurations -2026-10-17

Twelve new cases total3,499. Compatibility2 rejects fixture-only manual/automatic
modes while retaining manual handlers, then accepts Ignore/Manual transitions.
Parameter-disabled O-word overflow/fraction/negative errors preserve modal state
and an already queued move, verified by actual80X pulses. Two G66.1 following
block cases update existing X, retain omitted Y, avoid axis motion and clean
arguments/local scope after callback error. Reissuing an already active G66.1
was an invalid modal-group fixture; the intended plain X20 following block works.
Six-case checkpoint:3,493 full sanitizer/strict pass46.02 s,44 helpers pass.

Three documented TOOL_LENGTH_OFFSET_AXIS host variants (X/Y/Z) add six cases:
correct-axis G43.1 and wrong-axis rejection, offset-to-physical240-pulse move,
and manual tool retract/return despite G18 plane selection. All six pass focused
0.45 s. Both test and core receive consistent feature definitions; README lists
the configurations. Final3,499 sanitizer/strict/helper gate is live session24395,
batch36-final-results.xml and parentlogs. No new core edits/exceptions/allowances.
Latest fetch confirms clean ad57c78 remains latest.

Hosted34 run39018542932 passes all jobs; artifacts verify
caa7509c776e2948c3620329592b6934a72a6c85/ad57c78 and core/.*\.[ch]$:
16,792/17,630 lines95.25%,11,386/13,648 branches83.43%. Hosted35
run39018951320 remains in progress. New fixed-axis code can increase the
coverage denominator; do not compare percentages without recording counts.

Batch36 delivery: full3,499 pass46.23 s, strict summary and all44 helpers pass,
11 existing expected failures. Session24395 completed successfully. Freeze/push
and dispatch exact-source CI; continue37 with sender interruption during real
G30/toolsetter positioning. Preserve stopped coordinates and callback ownership.


## Batch37 real boot/reset tool-positioning continuation -2026-10-17

Two registered cases total3,501. Full real homing establishes a raw physical
counter-to-machine-coordinate mapping before G0 X-2 Y-3 Z-1. Reset during an
ordinary move retains tool0 after restart. Reset during initial M6/G30 retract,
before XY travel to the fixture, leaves tool3 selected after normal warm init.
Correct tool0 expectation retained with dated KNOWN_BUGS evidence/control/
proposal/cleanup and one WILL_FAIL; no core edits or sanitizer allowances.

The initial direct-parser fixture observed intermediate state and was superseded
by full boot. Initial boot reset fired too early until the homed coordinate frame
was calibrated; those early results are not the reproduction. Restart observation
requires the second startup greeting; host CMD_EXIT cleanup is excluded from
reset counts. Full registered3,501 checkpoint passed46.04 s and strict summary.

Mock boot receive now routes through a selected driver realtime handler, default
unchanged, allowing actual manual ACK/cycle-start trapping. A separate streamed
manual completion candidate selects tool3 and restores handlers but fails its
correct prior-Z return assertion (entry-1, final-0.125). It is unregistered in
candidates and TODO pending sender/suspension/task review. No exception assigned
to that unresolved behavior. Final3,501 full gate after mock routing extension
is live session99866, batch37-final-results.xml and parentlogs. Uncommitted work.

Hosted35 run39018951320 fully green verifies63aa882329a04b3397a744cf94644108dbe1a16f
and ad57c78 with core/.*\.[ch]$:16,794/17,630 lines95.26%,
11,392/13,648 branches83.47%. Hosted36 run39019490072 is still running.
PR19 remains open; latest core fetch unchanged/clean. Continue coverage work.

Batch37 registered gate completed:3,501 pass49.44 s, strict summary and all44
helpers pass,12 documented expected failures. Session99866 completed. Work
remains local/uncommitted while investigating the streamed restoration candidate.

Batch36 run39019490072 fully green: exact4dab01a510964c9563f2ff346b96544553970c08
and ad57c78 source lock, core/.*\.[ch]$ filter. Coverage16,810/17,634 lines
95.33%,11,405/13,648 branches83.57%; fixed-axis configurations add4 denominator
lines. Continue reviewing the candidate without weakening its position assertion.


Batch37 fixture investigation resolved: streamed tool ACK is handled by core
stream_rx_suspend/await_toolchange_ack, not default protocol dispatch. A no-op
suspend callback dropped ACK, so direct cycle start bypassed return motion.
The fixture now uses the real RX suspension interface and delivers ACK via the
selected receive handler independently while hal.stream.read is paused. Sender
commands are paced to tool pause; G30 reference settings wait for return.

Original prior-Z assertion passes unchanged. Candidate is restored as ordinary
case and its temporary TODO removed. Three normal completion controls pass0.36 s:
manual return, intentional no-return and G30 return/touch-off, each checking tool3,
physical positions, restored handler/RX state. Five registered new cases total
3,504. Separate reset-during-M6 regression remains one documented expected
failure, with ordinary reset and completed G30 controls linked in KNOWN_BUGS.
Final full gate runs session50785, batch37-delivery-results.xml and parentlogs.
No core edits or sanitizer allowances. Added repository lesson for ACK routing.

Batch37 delivery: full3,504 pass46.58 s, strict summary and44 helpers pass,
12 documented expected failures. Session50785 completed. Latest core fetch
confirms clean ad57c78 remains latest. Freeze/push/dispatch37 and continue38.


## Batch38 parser rejection, driver waits and macro M arguments -2026-10-17

Fourteen new cases total3,518. Ten rejected programming commands preserve
prior modal state, planner buffer and execution of the queued80X-pulse move:
milling G7/G96, unavailable M7/M62/M66/M67, disabled M56, G28.2/G33.2 fractions
and conflicting G10/G33 axis commands. All ten focused pass0.64 s.

Registered torch capability bypasses start/stop spindle delay and feedback waits;
a driver lacking feedback instead waits its configured400 ms without polling.
Driver capabilities are set before registration; existing feedback controls keep
their default fixture behavior. Two focused pass0.29 s. Twelve-case checkpoint
passes full3,516/46.96 s, strict summary and44 helpers.

M3/M8 before G65 become local macro argument13 without enabling spindle/coolant;
callback-error cleanup restores parent argument99 and call scope. Both focused
pass0.29 s. No new defects/allowances/core changes. Final3,518 gate runs as
session60112, batch38-delivery-results.xml and parentlogs. Hosted37 exact77d91aa
run39020604172 is still in progress. Continue beyond the validation checkpoint.

Batch38 delivery:3,518 full sanitizer/strict pass46.97 s,44 helpers pass,
12 unchanged expected failures. Session60112 completed. Freeze/push/dispatch38
and continue39. Next inspect registered ports made unavailable by normal plugin
claims, rather than force private states or unsupported laser-only configurations.


## Batch39 public I/O ownership and parser availability -2026-10-17

Ten new cases total3,528. Real driver registration plus public plugin claims
reserve digital/analog inputs/outputs. With no unclaimed ports G-code rejects
without disturbing an already queued80X-pulse move; plugin operations still reach
the original pins. With one claim, G-code index0 maps to physical1 and plugin
access remains physical0; reserved indexes reject with no output callbacks.
Analog invalid-port status is currently RPM-specific; this ownership test checks
rejection and no driver write rather than fixing that incidental diagnostic.
Integer values avoid the existing fractional-output defect and keep its regression.

Separate input banks remain independently usable for M66, and synchronized digital
plus analog outputs wait until motion before reaching the remaining ports.
All ten focused cases pass0.57 s. Initial claims mistakenly retried aux0; the
fixture now supplies auxiliary IDs0/1 and uses returned mapped handles. Shared
queued-motion rejection checks were factored without removing any assertions.
No new core defects, exceptions, allowances or source edits. Full gate live
session85317, batch39-delivery-results.xml and parentlogs. Hosted37
run39020604172 and38 run39020997626 remain in progress at latest check.

Batch39 delivery: full3,528 pass47.53 s, strict summary and44 helpers pass;
12 existing known failures. Session85317 completed. Latest fetch confirms clean
ad57c78 remains latest. Freeze/push/dispatch39 and continue40 from fresh gaps.


## Batch40 delta real homing and sender cancellation - 2026-10-17

PR19 merged upstream df09798. Hosted39 run39021372475 is fully successful at
a8b573a/ad57c78; downloaded source lock and coverage verify 16,832/17,634 lines
(95.45%) and11,435/13,648 branches (83.79%). README badges link to that report
and clearly describe manually refreshed snapshots. Latest fetched Terje remains
clean ad57c78. Four new cases exercise real delta homing switch cycles, deferred
cuboid-top reposition, and ordinary sender jog cancellation before/after ACK.
Refill-time cancellation stops at98 pulses (~10mm), but parser retains50mm
target; after-ACK control synchronizes correctly. One narrow documented known
regression, correct assertion retained, no core modification or sanitizer allowance.
Initial10mm request could finish within buffered deceleration; use50mm and actual
forward-transformed joint counters, not an immediate-stop assumption. Both normal
realtime and delay callbacks advance driver IRQs. Full gate pending.

Batch40 delivery:3,532 full sanitizer cases pass53.06s, strict summary passes;
13 labelled known failures. All44 helper tests pass3.254s outside sandbox after
temporary-directory permission failures there. No core edits. Push/hosted gate
next, then ready cumulative PR after exact-head GCC/Clang/coverage/diagnosis.


## Batch41 configured delta geometry during real homing - 2026-10-17

Four new cases total3,536. Settings are applied through settings_store_setting
during normal driver setup: home angle30 degrees, motor travel30 degrees,
base-to-floor350mm and forearm330mm. Real homing completes with all three
switches. Analytic symmetric rod geometry independently checks home coordinates;
travel/floor options shrink the finite ordered workspace without changing home.
All four focused cases pass0.42s. No new bug, exception or core change.
Batch40 d795985 pushed, exact-core hosted39040996935 confirmed in progress.
Full41 validation pending; do not present it as ready.

Batch41 delivery: full3,536 sanitizer/strict pass113.71s,44 helpers pass.
13 existing known failures; no new defects or allowances. Push41 and continue42.
Hosted40 exactd795985 run39040996935 remains live at last check.


## Batch42 CoreXY startup homing policy and switch feedback - 2026-10-17

Three new full-boot cases total3,539. Configured combinedXY cycle rejects $H
with HomingFail before wake/pulses. Supported separate Z/X/Y cycles home all
axes with actual ISR pulses and carriage switches from (A+B)/2,(A-B)/2.
A single $HX uses both coupled motors, leavesZ stationary and retains the
homing-required lock for remaining axes. Parser position is independently
checked against joint sums/differences. Initial homing-required alarm is normal,
not an erroneous no-alarms assumption. All three focused pass0.34s.
Discarded $HXY candidate because that sender command is unsupported; no bug
registered for it and no attempt to force the private combined-mask branch.
No source changes, new exceptions or defects. Full validation pending.
Hosted40 run39040996935 and41 run39041409247 are still live.

Batch42 delivery: full3,539 sanitizer/strict pass52.02s;44 helper tests pass.
13 unchanged known failures. Push/dispatch42 and continue43. Hosted40 has source,
GCC and coverage successful; Clang test still in progress at latest check.


## Batch43 Z backlash and probe-following motion - 2026-10-17

Six new cases total3,545. Public per-axis settings configure compensation. Z
reversal/continuation and negative-first travel check both motor pulses and
logical endpoints; XYZ diagonal uses independent8/4/10-pulse take-up. Two real
G38.2 probe/contact cases verify short forward follow-up adds no false reversal
and reverse follow-up adds exactly8 take-up pulses. This exercises backlash
position synchronization after probe abort removes its remaining queued target.
All six focused pass0.57s. No new defects, exceptions or core changes.
Full43 gate pending. Initial generated double constants corrected to float under
strict Clang warnings.

Hosted40 exactd795985/ad57c78 run39040996935 fully passed all jobs. Artifact
verification:16,841/17,634 lines95.50%;11,439/13,648 branches83.81%, core filter.
PR20 opened only after that full hosted gate: https://github.com/grblHAL/Unit_tests/pull/20
It contains315 new cases since upstream master/merged19. Frozen at40;41/42 and
current43 remain separate continuing work. Do not merge PR20. Hosted41
run39041409247 remains in progress at last check.

Batch43 delivery: full3,545 sanitizer/strict pass53.39s;44 helpers pass.
13 existing known failures. Hosted41 exactc0d76b8/ad57c78 run39041409247 is fully
green; downloaded lock/filter/coverage verify16,846/17,634 lines95.53% and
11,444/13,648 branches83.85%. PR20 remains frozen at40. Push43 and continue44.


## Batch44 held spindle plugin notification ordering - 2026-10-17

Five new cases total3,550. PWM spindle registered before parser initialization
and used in standard machine mode; no registered spindle pointer mutation.
A real20mm move is held, stopped/restored via ordinary realtime overrides.
Plugin programmed callbacks precede hardware changes, override callbacks see
completed hardware state, and resume notification precedes any resumed steps.
Two queued toggles produce neither false notifications nor hardware writes;
stop during deceleration notifies only after completed hold. Exact1600-pulse
endpoint is retained on resume. All five focused pass0.51s. No new defects,
exceptions, allowances or source changes. Full44 gate pending.

Batch44 delivery: full3,550 sanitizer/strict pass52.42s and44 helpers pass.
13 unchanged known failures, no core edits. Push/dispatch44; continue45 with
independent primary/MPG report consumption using public reporting APIs.
Report_ClearAll returns early for primary only; do not force the unreachable
zero-value MPG observer path just for coverage or call it a defect.


## Batch45 independent primary and MPG report consumption - 2026-10-17

Four new cases total3,554. Normal realtime requests consume primary and directed
pendant reports in both orders after public feed override110% or G10 offsetX12.
Both receive the new value even when the other report was already consumed.
Primary replies broadcast to connected streams; pendant requests stay local and
do not take primary input control. Initial fixture incorrectly expected primary
replies to bypass pendant; corrected to documented broadcast behavior, not a bug.
All four focused pass0.38s. No new defects, exceptions or core edits.
The internal MPG zero-flags branch is unreachable from Report_ClearAll's early
return; do not force it just to improve counts. Full45 validation pending.
Hosted42 run39041825459 fully successful, downloaded artifacts pending extraction.
Hosted43 run39042209299 and44 run39042584724 still in progress at last check.

Batch45 reporting checkpoint:3,554 sanitizer/strict pass51.98s. Commit locally
then extend the same feature branch with more module groups before another
full hosted run, reducing repeated CI/push overhead. Keep focused checks while
authoring and full sanitizer/helpers at the larger delivery checkpoint.
Hosted42 verified5d336fc/ad57c78:16,851/17,634 lines95.56%,11,451/13,648
branches83.90%. PR20 remains frozen and ready at40.


Batch45 numeric settings extension:16 additional cases,3,570 total (20 since44).
Registered plugin types cover decimal, axis masks,8/16/32-bit integers and bool,
full-width accepted values, overflow/invalid-mask rejection, no save/notify on
failure, saved-before-notification order, and selective core/driver restore.
Two correct regressions expose read_uint incorrectly rejecting valid ten-digit
values ending6-9: publicplugin2000000009 and minimaldirect1000000006/4294967289.
2000000005 andUINT32_MAX controls pass;UINT32_MAX+1 rejects properly.
One dated KNOWN_BUGS entry with exactsourceanchor and pre-multiplication overflow
proposal; two named WILL_FAIL blocks,15 total labelled failures. No source
modification or sanitizer allowance. Owner restore saves its own defaults before
on_changed, matching the registered contract. All15 numeric focused cases pass
expected classifications0.92s; direct uint group also verified. Combined full
checkpoint next before one push/hosted run for the20 new cases.

Batch45 combined delivery:3,570 sanitizer/strict pass52.65s,44 helpers pass3.348s;
15 labelled known failures. Fresh core fetch confirms cleanad57c78 latest.
Hosted43 exact65856dc/ad57c78 run39042209299 fullygreen, artifactlock/filter
verified16,854/17,634 lines95.58%,11,454/13,648 branches83.92%. Hosted44
run39042584724 now reports queued at latest snapshot (samehandle, not terminal).
Push combined20case checkpoint, continue next branch with parser comment and
optional-block workflows; do not force private/unreachable paths.


## Batch46 parser normalization and modal restoration - 2026-10-17

17 new cases total3,587. Public plugin G-code executes/skips optional blocks via
normal$B setting, preserves semicolons inside comments and queued motion after
plugin comment rejection. Three distinct M98 subroutine positions survive repeat
registration. G65 passes positive/negative/inch-mode U/V/W as raw local macro
arguments, restores caller values and queues no motion. Registered PWM lathe
controls restore G96/G97, G7/G8 reporting, stopped or CCW spindle state and RPM;
repeated unchanged diameter restore adds no false status flag. Cutter snapshot
restores a changed radius with same compensation side after ordinaryG40/re-enable.
M6 message comments precede driverchange and remain visible for an already fitted
tool without repeating the change. All17 focused pass, no new core defect or
exception. The $B fixture initially missed mandatory is_connected callback; fixed
fixture, not a bug. Source-only CSS S/D saved-state scope question is in TODO,
unregistered pending Terje; mode controls pass without claiming that contract.
No core edits or sanitizer allowances. Full46 gate pending; preserve PR20 frozen40.
Latest fully verified hosted43 is95.58% lines83.92% branches.

Batch46 delivery:3,587 sanitizer/strict pass53.37s;44 helpers pass3.764s.
15 unchanged known failures, no new exceptions. Also corrected a stale comment
in backend_close.h: currentvfs_close caches metadata before backend close and
no longer has the oldUAF; KNOWN_BUGS correctly has no such entry. Helper remains
for isolated backend testing, not as a required workaround. Comment-only edit
does not change compiled behavior. Next exercise nested realRAM file streams
through ordinaryvfs_close, rather than inherit that stale assumption.


## Batch47 nested real RAM stream integration - 2026-10-17

Five new cases total3,592 pass focused0.45s. Realfs_ram/vfs opens three distinct
files throughstream_redirect_read; tests unwindLIFO, preserve parent line/position,
restore original serial reader, route errors/EOF to active owner and chain previous
EOF observer in order, preserve parents after missing child/reposition. Ordinary
vfs_close is used throughout, no backend bypass/wrapper. Temporary RAM files
are deleted after readers close. Initial fixture expectedgc_state.file_run, but
stream_set_file does notset it; corrected to publicstream_is_file rather than
force that separate parser/program flag. No bug/exception from that assumption.
Next extend with actualprotocol/G65 loader workflows on the same real RAM files,
focused checks first, full checkpoint after a substantial combined group.
PR20 remains frozen at40; current47 starts at pushed46 c3755d9.


## Batch47 nested macro protocol checkpoint - 2026-10-18

Twelve new cases total3,599. Five real RAM stream cases plus seven actual G65
protocol cases cover LIFO readers, missing child, EOF/error ownership, reposition,
local numeric/named scope preservation, automatic M73 modal restore, error
suppression and normal serial-query recovery. CR/LF/mixed controls distinguish
one reproducible line-diagnostic defect: CRLF main/child report4/4 instead of3/3
when pending caller LF survives asynchronous G65 return. Leaf reports2 correctly;
ordinary LF and CR callers report3/3/2. Commands/modal results succeed. Correct
regression retained with one dated known-bug entry, proposal and named WILL_FAIL;
no sanitizer allowance or production source edit.16 known failures now.
Focused14/14 pass0.76s including two existing controls;44 helpers pass3.473s.
Full3,599 sanitizer/strict gate running; do not claim completion before checking.

Fresh fetched Terje remains cleanad57c788e15fb4e5d8ef9c20ed50755ffa3d9216.
PR20 still open/unmerged. Hosted46 run39044600759 passed alljobs, source lock
matchesc3755d929a42e7f7b3a11098d848e777f6809e14 andad57; corefilter unchanged.
coverage.xml:16,871/17,634 lines95.67%,11,471/13,648 branches84.05%.
Artifacts saved beside checkout asrun-39044600759-{coverage-core,source-lock-core}.zip.

Batch47 delivery gate: all3,599 ASan/UBSan cases and strict diagnosis pass112.60s;
44 Python helpers pass3.473s.16 labelled known failures, zero unexpected failures.


## Batch48 Modbus recovery and embedded asset integration - 2026-10-18

Twelve new cases total3,611: eight public modbus_message workflows cover timeout
and exception recovery, stale-response clearing, optional callback, rejected
transport recovery, packed-bit order across words, maximum register read, and
write frame-size rejection followed by valid full-frame write. Four embedded VFS
cases cover mount-root stat, independent readers/peer close/reopen, appending a
list without disrupting an open reader/directory order, and opening a valid asset
in an appended list. Ordinary vfs_close throughout, no backend wrappers.

Confirmed appended-list lookup bug: find_file retains exhausted first-list index
when moving to next list. With firstlist2 entries, secondlist3, opening its first
entry returnsNULL. Original secondlist1 reproduces ASan global-buffer-overflow
at fs_embedded.c:58 (batch48-embedded-focused.log). Committed legitimate longer
list retains correct assertions without relying on UB, so non-ASan coverage is
deterministic too. Dated known entry, reset-index proposal, one named WILL_FAIL;
17 total expected failures, no sanitizer allowances or production core edits.

Focused46/46 pass1.98s;44 helpers pass3.695s. Full sanitizer/strict gate running,
see batch48-tests.log. Latestcore unchangedad57c78, PR20 remains open/frozen40.
Batch47 pushedbdd8da0dc004706895d06a3878615352690517cd; hosted39081516464 running.
Latest fully verified46 coverage95.67% lines84.05% branches.

Batch48 delivery:3,611 ASan/UBSan cases and strict summary pass52.48s;
44 helpers pass3.695s.17 labelled known failures, zero unexpected failures.


## Batch49 O-code through real RAM protocol - 2026-10-18

Eleven new cases total3,622 run actualprotocol_main_loop over real RAM files:
nested repeats, WHILE/REPEAT CONTINUE, ordinary DO/WHILE, conditional BREAK,
nested loop BREAK, false WHILE/zero REPEAT skip G65 loaders, IF/ELSEIF selection,
nested subroutine local arguments, early RETURN/value flags and M73 restoration.
They validate final parameters and normalEOF/serial$G recovery with no motion.
DO/WHILE CONTINUE remains undecided TODO and unregistered as requested.

Extracted shared protocol initialization in ram_macro_protocol_host.h rather than
duplicate the driver/file setup. Bounded control polling detects runaway file loops.
Existing seven nested G65 protocol cases still pass with the refactor. Focused18/18
pass0.86s, including the one already labelled CRLF diagnostic regression.
44 reporting helpers pass3.623s. Full3,622 sanitizer/strict gate running;17 existing
known failures, no new exceptions or production-source modifications.
Batch48 pushed8792adb5c451042ed58ca9e5a3bf2ba9207e30bf, hosted39081807991 running.
Batch47 run39081516464 also running at latest check. PR20 remains open/frozen40.

Batch49 delivery gate:3,622 ASan/UBSan cases and strict summary pass52.40s;
44 helpers pass3.623s.17 unchanged labelled known failures, no unexpected failures.


## Batch50 file-resource failure and lifecycle integration - 2026-10-18

Twelve new cases total3,634. Four file redirects reject backend-handle or redirect-
context allocation at root/nested depth, assert all partial allocations freed,
original serial/parent reader preserved with parent line/position, then retry and
read successfully. Four embedded asset resource cases cover failed file open,
either directory allocation and failed appended-list allocation followed by retry;
existing directory remains available. A reusable tracked malloc/free probe avoids
duplicated instrumentation, is enabled only around public operations, and disabled
before shutdown/gcov allocations. Link wrapping is scoped to the allocation cases.

Four lifecycle cases cover repeated report-handler initialization through nested
owners, closing all then opening a fresh RAM session, EOF forwarding without a
local handler, and empty asynchronous G65 leaf scope return/caller continuation.
Ordinary VFS/stream APIs used throughout, no production source edits.17 existing
known failures unchanged. Focused30/30 pass1.57s,44 helpers pass3.723s.
Full3,634 sanitizer/strict gate running in batch50-tests.log.
Batch49 pushed746d5b46219ec3d990a6ed24c0a38b4ee9e57fd6; hosted39081992616 running.
Earlier47 run39081516464 and48 run39081807991 still running at prior check.

Batch50 delivery gate:3,634 ASan/UBSan cases and strict summary pass53.03s;
44 helpers pass3.723s.17 unchanged known failures, no unexpected failures.
Hosted47 run39081516464 fullygreen, lock matchesbdd8da0/ad57 and corefilter.
Coverage16,879/17,634 lines95.72%;11,489/13,648 branches84.18%.
Downloaded coverage/source-lock artifacts beside checkout.48/49 still live.


## Batch51 named embedded macros through real file protocol - 2026-10-18

Twelve new cases total3,646. Real read-only embedded .macro assets are located
by the core and called from a real RAM root file throughprotocol_main_loop.
Cases cover EOF and empty files, early RETURN/ENDSUB values and tail skipping,
repeat independent opens, M73 restoration, M71 disarm, nested local/modal scopes,
message output, and one/two named-file parser-error unwinds suppressing caller
commands and restoring the serial sender. Ordinary vfs_close and core named-file
handlers are exercised, replacing neither backend operations nor lifetime logic.

Shared RAM root fixture supports an optional asset registration callback and
expected root error status. Initial fixture required exactlyone root error callback;
actual named-error propagation legitimately revisits that observer (observedtwo).
Corrected the new fixture to require observed correct error, EOF status, restored
scope and correct final parameters. No core bug was inferred from that callback
count. Existing G65 and RAM-loop controls also pass after helper changes.
Focused31/31 pass1.78s,44 helpers pass3.637s. Full3,646 sanitizer/strict running.
17 existing known failures unchanged, no production edits or new allowances.
Batch50 pushed427a0a5; hosteddispatch done, obtainrun ID.47 fullyverifiedgreen,
48/49 still live at previous check. Latest verifiedcoverage95.72/84.18.

Batch51 delivery gate:3,646 ASan/UBSan cases and strict summary pass53.00s;
44 helpers pass3.637s.17 unchanged known failures, no unexpected failures.


## Batch52 JSON boundaries and mandatory diagnostic cleanup - 2026-10-18

Ten new cases total3,656 cover unterminated/malformed members without callbacks,
callback-driven search across mixed fields, absent-target/early-stop behavior,
INT32_MAX/zero, UTF8 preservation with ASCII escaping, nested array/object separator
restoration and INT32_MIN output. This remains the core's basic callback parser;
no general JSON-validator contract is imposed. Focused26/26 pass1.81s.

INT32_MIN emits the correct text but UBSan reports signed negation atstream_json.c228.
One dated known entry proposes unsigned magnitude arithmetic; no production edit.
Correct output assertions remain normal passes, not WILL_FAIL. The test/source/
line/message-scoped manifest allows only this recovering diagnostic; SAN-only
known_sanitizer_bug label requires the diagnostic to remain present until cleanup.
Both summary and CI diagnosis now flag a missing diagnostic as changed known
exception, retaining actual assertion failures/different diagnostics for review.
Without SAN label, coverage is an ordinary clean output test. README explains
removing label+manifest together.17 expected failures plusone recovering diagnostic.

Six meaningful reporting tests cover match, wrong test, changed diagnostic,
actual assertion failure, obsolete diagnostic and noninstrumented case. All50
helpers pass4.465s. Full3,656 sanitizer/strict gate running in batch52-tests.log.
Batch51 pusheda13c4be; dispatchdone, obtainrun ID. Core remainscleanad57c78.
PR20 open/frozen40; later batches remain separate continuing work.

Batch52 delivery gate:3,656 ASan/UBSan cases and strict summary pass53.62s;
3,638 clean,17 expected failures,one known recovering diagnostic, zero unexpected.
50 helpers pass4.465s. Actual CI classifier also yieldszero findings/18 known.
Hosted48 run39081807991 and49 run39081992616 fullygreen, source/filter/harness
locks verified.48:16,883/17,634 lines95.74%,11,495/13,648 branches84.22%.
49:16,883/17,634 lines95.74%,11,497/13,648 branches84.24%.
README snapshot badges refreshed to fullygreen49, both links changed together.
Hosted50 run39082275393 and51 run39082526178 still running at latest check.


## Batch53 hosted compatibility repair - 2026-10-19

Fresh live state: clean branchcoverage-batch-53 starts at pushed52 3b62d3c;
core fetched lateststillad57c788e15fb4e5d8ef9c20ed50755ffa3d9216, PR20 open.
Previous goal turn made concrete progress through52; continue full objective.

Hosted50 run39082275393 and51 run39082526178 failed GCC+coverage compilation:
heap_more in embedded_allocation_host.h is unused in cases that do not append.
Their Clang jobs passed and source jobs passed. Moved heap_second/heap_more
into only the append test; no assertion or production-source change.
Hosted52 run39082907285 failed source helpers: new sanitizer-expectation fixture
inherited GITHUB_STEP_SUMMARY, so it wrote to parent Actions summary instead of
captured stdout. Now remove that variable and GITHUB_ACTIONS only in the fixture
subprocess environment, matching existing reporting-test isolation. Added a
regression that injects those parent variables and verifies no parent file write.
All51 helpers pass4.186s under simulated Actions variables. These are harness
compatibility defects, not core regressions; three failed runs remain failed.
Full3,656 local sanitizer/strict gate running in batch53-tests.log (handle84410).
Downloaded report-core artifacts beside checkout contain exact failure evidence.
Latest fully verified hosted49 remains95.74% lines84.24% branches.

Batch53 delivery gate:3,656 ASan/UBSan cases and strict summary pass117.74s;
51 helpers pass4.186s with inherited Actions variables injected.17 expected
failures plusone scoped known UBSan diagnostic; zero unexpected failures/skips.


## Batch54 sender and pendant status independence - 2026-10-19

Twelve new cases total3,668 verify pending G55/G54 coordinate-system selection,
inch-display WCO, M8 flood/M7 mist/M9 off state reach both independently tracked
streams regardless of which requests first. Public G-code/settings commands and
registered MPG transport are used with complete driver coolant callbacks. Inch
status formatting correctly follows$13; no NGC parameter unit contract is changed.
Expected fields are checked to delimiter boundaries, including empty accessory
field when coolant is off. Primary replies broadcast as designed; directed MPG
replies remain quiet on primary, and control stays with the primary stream.
No motion/private state forcing and no new defects/exceptions.

Focused12/12 pass0.80s,51 helpers pass4.652s. Full3,668 sanitizer/strict gate
running in batch54-tests.log (handle35509).17 existing expected failures andone
recovering known UBSan remain. Hosted repair53 run39176095263 sourcejob passed;
GCC/Clang/coverage running.53 headf3fe1d1c9c5726a743953a4400cf4537335ded1d.
Corecleanad57c78, PR20 open/frozen40, latestverifiedcoverage49 95.74/84.24.
Next useful area: real embedded named-macro recursion and repeated-return lifetime
through core file handles, using ordinary bounded programs and existing helpers.

Batch54 delivery gate:3,668 ASan/UBSan cases and strict summary pass54.37s;
51 helpers pass4.652s.17 expected failures plusone known UBSan, zero unexpected.


## Batch55 named recursion and settings readback - 2026-10-19

Twelve new cases total3,680. Eight real embedded named-file programs cover
bounded recursion, repeated reopening, numeric caller preservation, M73 frames,
looped child calls, error unwind and expression-valued RETURN/ENDSUB. Four
settings cases query both registered getter and actual $id output for E-stop
unlock, supported control inversion and subroutine options under advertised SD/
littlefs capabilities, including persistent reload. They test availability/readback;
actual macro file execution is covered separately, not storage board drivers.

Two genuine return-expression regressions: callee#1=3 returns[#1+10] whilecaller
has#1=99. Observed109, correct13. Both paths pop scope before expressionevaluation.
All four invocations, restored caller and return-present controls pass before the
correct result assertion fails. Primary LinuxCNC O-code scope/return documentation
supports this contract. One datedknownentry withcodefixproposal/two namedWILL_FAIL
blocks;19 total expected failures plusone existing recoveringUBSan. No coreedits.
Six remaining recursion cases and four readback cases pass normally. Initial
query fixture lacked report_init_fns/mandatoryhal.control.get_state; completed
fixture before classification; those crashes were notcoredefects.

Focused12/12 pass0.80s includingtwo labelled regressions;51 helpers pass4.721s.
Full3,680 sanitizer/strict running inbatch55-tests.log (handle77056). Next commit
only after terminal result.54 pushedf74d3d3, hosteddispatchdone obtainID.
Hosted53 run39176095263 sourcepassed, GCC/Clang/coverage lastinprogress.
Core remainscleanad57c78, PR20 open/frozen40, latestverified49 95.74/84.24.

Batch55 delivery gate:3,680 ASan/UBSan cases and strict summary pass54.56s;
51 helpers pass4.721s.19 expected failures plusone scoped known UBSan, no unexpected.
Hosted53 repair run39176095263 fullygreen includingGCC/Clang/coverage/diagnosis.
Source lockmatchesf3fe1d1c9c5726a743953a4400cf4537335ded1d/ad57 andcorefilter.
Coverage16,895/17,634 lines95.81%;11,527/13,648 branches84.46%.
Artifacts beside checkout; README snapshots refreshed to thisverifiedrun.
Hosted54 run39176480077 still live. Earlier50-52 failures are notrerun/relabeled;
53 cumulative checkpoint validates their fixes. PR20 remains open/frozen40.
