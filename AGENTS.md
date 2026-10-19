# Current batch69 filesystem checkpoint - 2026-10-19

PR22 is merged upstream at20f186f; its exact head aa80971 is an ancestor.
Branch coverage-batch-69 now contains51 additional cases /3,828 registered.
Six filesystem cases cover multiple visible mounts with hidden RAM omitted,
early directory-close/reopen, current-drive format returning to its canonical
root, and RAM writer metadata/buffer/growth allocation failures with safe
cleanup and a subsequent successful job. Core remains unmodified16c7dff.

One full local sanitizer gate ran3,828 in126.92s. Three fixture expectations
were corrected from public contracts: hidden RAM mounts reject unlink, so
consume/close the temporary reader; vfs_getcwd canonicalizes /store/ to /store.
Focused six-case repair gate passed0.37s with strict summary. Consolidated
full+repair evidence is retained separately; no second full local run.
Nine documented expected failures remain; no sanitizer allowances.

Hosted previous checkpoint39286594112 at b677af0 has source+coverage successful;
GCC/Clang still queued when checked. Both downloaded locks match harness,core,
full selection and header coverage filter. Measured17,041/17,652 lines96.54%;
11,707/13,700 branches85.45%. Do not describe entire run as green until all five
jobs finish. Prior fully verified run39249281186 remains96.49%/85.34%.

Merge fresh upstream (normal ancestry, no squash replay needed), push this
checkpoint and validate hosted exact head before presenting next PR as ready.
Continue normal Modbus transport/error/recovery workflows independently.

# Current batch69 startup/macro checkpoint - 2026-10-19

Branch coverage-batch-69 continues; ready PR22 remains open at aa80971.
Hosted69 run39249281186 has all five jobs successful at de32a80/core16c7dff.
Downloaded locks match harness/source, full test selection and unchanged header
coverage filter. Verified17,033/17,652 lines96.49%;11,691/13,700 branches85.34%.
README badges now link this verified report. Core latest fresh-fetch16c7dff clean.

Fifteen additional cases plus startup fixture integration are ready locally:
45 beyond PR22 /3,822 total. New normal boots cover compatibility2/10 default
recovery, released EStop/reset, changed homing lock/reset, no-table G10L0 and
existing UART/external DEBUGOUT variants. Existing debug libraries reused;
no new production configuration or core patch. G66.1 no-motion argument blocks,
nested G65 scope, incomplete threading inputs and custom I/O handler delegation
are covered. Default I/O configuration control remains unchanged/passing.

One full local gate3,823 ran59.97s. Four arc callback candidates and one nested
arc-scope candidate assumed G66 supports arcs, while source triggers onlyG0/G1.
They are unregistered proposals pending Terje, documented in TODO; no exceptions.
The nested linear scope case now explicitly specifies G65 L1 and uses the
established fixture arguments5/7. The I/O callback is a configuration delegate,
not an observer; a separate passing delegation case preserves the default test.

Confirmed one new bug: armed G66 skips explicit G65 validation. Omitted L passes
repeat0 rather than1, and missing P dispatches macro0 instead of error26. Two
focused regression assertions remain correct, narrowly marked WILL_FAIL; dated
KNOWN_BUGS entry includes passing controls, source link, proposed guard fix and
removal instructions. Nine total expected failures; no sanitizer allowances.
Focused new/repair/control gate19/19 passed0.74s plus strict summary. Consolidated
full-run plus focused-repair evidence3,822 also passes strict summary; raw XML/logs
retained. No second full local run. Reporting scripts unchanged.

Push this useful checkpoint on the same branch and dispatch one hosted run.
Do not change ready PR22 or open an overlapping upstream PR while it is open.
Continue local VFS workflows next (multiple mounted child directories, formatting
current drive). Source audit notes explain private/dead handlers in TODO; no
coverage exclusions or forced private execution. Refresh PR22 merge state before
preparing the next PR, preserving all work if a squash rebase is needed.

# Current batch69 controller-options checkpoint - 2026-10-19

Keep coverage-batch-69 for continuing work. PR22 remains OPEN/READY at aa80971;
all five hosted jobs39245386515 passed and locks confirm16c7dff/core/header filter.
Latest measured coverage96.29% lines /85.15% branches; new local cases are not
included in that measurement yet. Core fresh-fetch still16c7dff, clean.

Thirty cases beyond PR22 are now validated locally:16 in81c2041 plus14 here.
Registered total3,807; seven expected failures, no sanitizer allowances.
The controller-options full gate executed3,808 tests in58.34s:3,807 passed and
a proposed axis-free G38 rejection returnedOK rather than26. Its contract is
uncertain (possibly intentional modal-only selection), so its unchanged assertion
is unregistered in proposals and evidence is in TODO. This was not suppressed
or changed into an assumed positive contract. Reconfigure confirms3,807 registered.
Consolidated full-run evidence without that unregistered proposal passes strict
summary; raw original failure XML/log and the targeted diagnostic are retained.
No second full local execution. Earlier recovery group used one full gate plus
three focused expression-configuration repairs. Reporting scripts unchanged.

New14 cover GPIO spindle inversion metadata after normal boot, publicly configured
homing help, probe target rejection/retry, real fixed-X/Y/Z probe references,
startup-query storage recovery, parameter queries and compatibility2 offsets.
Probe fixture defaults stillX; fixed-axis cases select their actual sensor axis.
Unused header helper is inline; no core changes. G76 main-taper implementation
scope and obsolete private settings-dispatch paths are documented in TODO.

Push combined30-case continuation on coverage-batch-69 and run one hosted gate.
Do not alter ready PR22 or create a duplicate upstream PR containing its85cases.
Refresh its merge state before preparing the next PR; continue local work while
CI runs. If PR22 is squash-merged, rebase only commits after aa80971 onto refreshed
upstream master, preserving all uncommitted work before the rebase.

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
# Current batch55 recursion/settings checkpoint - 2026-10-19

Branch coverage-batch-55 starts at pushed54 f74d3d3. Twelve new cases total3,680
pass focused0.80s;51 helpers pass4.721s. Full3,680 sanitizer/strict passes54.56s;51 helpers pass4.721s.19 expected failures
plusone known UBSan now: RETURN/ENDSUB evaluate local expression after pop, so
caller#1=99 yields109 insteadcallee#1=3 result13. Two correct named regressions,
datedknownentry/proposal, no sanitizer allowance. LinuxCNC scope/return docschecked.
Settings query fixture now initializes report handlers and mandatorycontrol reader;
initial missing-callback crashes were fixture errors, not corebugs. No coreedits.
Hosted53 run39176095263 fullygreen, locksverified95.81/84.46.54 run39176480077 live.
PR20 open40, latestfullyverified49 95.74/84.24. Keepgoingaftercheckpoints.

# Current batch54 status-report checkpoint - 2026-10-19

Branch coverage-batch-54 starts at pushed53 f3fe1d1. Twelve new sender/pendant cases
total3,668 pass focused0.80s;51 helpers pass4.652s. Full3,668 sanitizer/strict passes54.37s;51 helpers pass4.652s.
G55/G54, inch WCO via$13, M8/M7/M9 use supported public commands and driver states;
primary broadcast and directed pendant semantics preserved, exact fields checked.
No new core defect/exception.17 expected failures plusone known UBSan unchanged.
Hosted53 run39176095263 sourcepassed, GCC/Clang/coverage inprogress. PR20 open40.
Latest fully verified hosted49 remains95.74/84.24. Do not call50-52 hostedgreen.

# Current batch53 hosted compatibility repair - 2026-10-19

Branch coverage-batch-53 starts at pushed52 3b62d3c. No new C cases yet.
Actual hosted50/51 GCC+coverage builds failed on unused shared heap_more (Clang
passed); moved append-only declarations into that case. Hosted52 source helpers
failed because new reporting tests inherited GITHUB_STEP_SUMMARY; isolated fixture
environment and added explicit parent-Actions regression.51 helpers pass4.186s
with simulated GitHub environment. Full3,656 sanitizer/strict passes117.74s;51 helpers pass simulatedCI4.186s. No assertions weakened.
Core freshfetchstillcleanad57c78; PR20 open/frozen40. Latest green49 is95.74/84.24.
Do not call50/51/52 hostedgreen; allthree are terminalfailure as described.

# Current batch52 checkpoint

Branch coverage-batch-52 starts at pushed51 a13c4be. Ten JSON helper cases total3,656;
focused26/26 pass1.81s.50 Python helpers pass4.465s, six new cases prove scoped
known-diagnostic matching, obsolete-exception cleanup, unrelated failure rejection
and no diagnostic required without sanitizer label. Full3,656 sanitizer/strict passes53.62s; actual CI classifier also passes.17 expected failures plusone known recovering UBSan.
Correct INT32_MIN JSON output passes but signednegation atstream_json.c228 isUB.
Dated KNOWN_BUGS entry/proposal; scoped manifest and SAN-only known_sanitizer_bug
label force reporting red when diagnostic disappears. Keep assertions; cleanup both.
README explains cleanup. Core cleanad57c78; PR20 open/frozen40.
Hosted48/49 verifiedgreen;49 coverage95.74/84.24, badges refreshed tothat run.50/51 pending.

# Current batch51 checkpoint

Branch coverage-batch-51 starts at pushed50 427a0a5. Twelve real embedded named
macro/protocol cases total3,646; focused31/31 pass1.78s,44 helpers pass3.637s.
Full3,646 sanitizer/strict passes53.00s.
Named error propagation can revisit root observer; require correct error/status
and state restoration, not an invented exactly-once callback rule.17 known failures
unchanged, no new core defects/exceptions. Core cleanlatestad57c78.
Hosted47 verifiedgreen95.72/84.18;48/49/50 need terminal checks. PR20 open/frozen40.

# Current batch50 checkpoint

Branch coverage-batch-50 starts at pushed49 746d5b4. Twelve new file resource/lifecycle
cases total3,634; focused30/30 pass1.57s,44 helpers pass3.723s. Full3,634 sanitizer/strict passes53.03s. No new known exceptions.
Tracked malloc/free probe is enabled only around supported public operations;
never inject into coverage shutdown. Actual embedded backend used for open retry.
Core cleanlatestad57c78; PR20 open/frozen40. Hosted47 verifiedgreen95.72/84.18;48/49 still need terminal checks.

# Current batch49 checkpoint

Branch coverage-batch-49 starts at pushed48 8792adb (Modbus module d295c8e).
Eleven real-RAM O-code protocol cases total3,622; focused18/18 pass0.86s.
44 helpers pass3.623s. Full3,622 sanitizer/strict passes52.40s.17 known failures unchanged. Do not test/resolve
DO-WHILE CONTINUE contract pending Terje. Common RAM fixture setup extracted,
existing seven G65 cases included focused and full gates. No core changes.
Hosted47 run39081516464 and48 run39081807991 in_progress lastseen; verify later.
PR20 remains open/frozen40. Latest verified46 coverage95.67/84.05.

# Current batch48 checkpoint

Branch coverage-batch-48 starts at pushed47 bdd8da0. Twelve new cases total3,611:
eight Modbus transaction recovery/frame boundaries, four embedded file integration.
Focused46/46 pass1.98s, helpers44 pass3.695s. Full3,611 sanitizer/strict passes52.48s.17 labelled known failures now.
Appended embedded lookup carries index across lists, skips valid assets; shorter
list also ASan-overreads. Correct regression uses legitimate longer second list
for deterministic no-UB failure; one named WILL_FAIL, no sanitizer allowance.
Core cleanlatestad57c78. Hosted47 run39081516464 in_progresslast. PR20 stillopen40.

# Current batch47 checkpoint

Branch coverage-batch-47 starts at pushed46 c3755d9. Twelve nested real-RAM
stream/protocol cases total3,599; focused14/14 pass including two older controls.
One real CRLF caller line-number defect is documented with one named expected
failure. LF/CR/mixed controls pass; no motion failure claimed. Full3,599 sanitizer/strict gate passes112.60s; helpers44 pass3.473s. Core untouchedlatestad57c78.
Hosted46 run39044600759 fullygreen, exactharness/source/filter verified:
16,871/17,634 lines95.67%;11,471/13,648 branches84.05%.
PR20 remains OPEN/unmerged frozen40. Continue coverage after useful checkpoint.

# Current batch46 delivery handoff

Branch coverage-batch-46 starts at pushed45 b60ded4 (plus352a94a reportinggroup).
17 new parser/modal cases pass full3,587 sanitizer/strict53.37s and44 helpers.
15 existing known failures; no new defects/allowances. CSS S/D snapshot scope
question source-only in TODO, do not register without maintainer contract.
Latest hosted43 verified95.58/83.92;44 run39042584724 queued lastseen and45
dispatched, obtain ID/status. PR20 frozen fullygreen40; no merge authorized.
Core cleanad57c78 remains latest. See newest PROGRESS and finish validation.

# Current batch45 combined delivery checkpoint

Branch coverage-batch-45 has committed MPG group352a94a plus16 numeric/parser
cases ready for full gate (3,570 total,20 added since44). One new documented
unsigned-parser defect has2 named correct regressions;15 known failures total.
No core edits/allowances. See newest PROGRESS. Run full sanitizer/strict/helpers
passed52.65s with44 helpers; commit/push one combined checkpoint. PR20 remains ready/frozen at40.
Core cleanad57c78; verify hosted43/44 and latestcore while full gate runs.

# Continue batch45 as a substantial combined delivery

Four MPG/report cases pass full3,554 sanitizer/strict51.98s. Commit module group
locally, keep extending branch coverage-batch-45 before push/hosted gate rather
than CI for every few cases. Next registered numeric plugin setting writes.
Focused checks while authoring; full sanitizer/helpers at substantial checkpoint.
PR20 open/frozen verified40. Hosted42 green95.56/83.90;43/44 still to verify.

# Current batch45 handoff

Branch coverage-batch-45 starts at pushed44 fda9a93. Four independent primary/MPG
report-consumption cases pass focused; full gate pending. Preserve intentional
primary broadcast and pendant-directed output behavior. See newest PROGRESS.
PR20 open/frozen40;42 hosted green,43 run39042209299 and44 run39042584724 live.
Core clean ad57c78. Next useful gap: registered numeric plugin setting writes.

# Current batch44 handoff

Branch coverage-batch-44 begins at pushed43 65856dc. Five registered PWM
spindle hold/plugin-order cases pass full3,550 sanitizer/strict and44 helpers. See newest
PROGRESS. PR20 frozen at verified40; later work separate. Hosted41 fully green
95.53/83.85;42 run39041825459 and43 dispatched remain to verify. Core cleanad57c78.

# Current batch43 handoff

Branch coverage-batch-43 begins at pushed42 5d336fc. Six backlash/probe cases
pass full3,545 sanitizer/strict and44 helpers. PR20 now open at fully green40 d795985.
Do not merge;41/42/43 remain separate later work. Hosted41 run39041409247 live
at latest check;42 dispatched, obtain run ID. Verified40 coverage95.50/83.81.
Core clean ad57c78. See newest PROGRESS and preserve correct assertions.

# Current batch42 handoff

Branch coverage-batch-42 begins at pushed41 c0d76b8. Three CoreXY real-boot
homing cases pass full3,539 sanitizer/strict and44 helpers. See latest PROGRESS. Both40
run39040996935 and41 run39041409247 live; await completed exact-head hosted
checks before ready PR. Core clean ad57c78. No new defects/allowances in42.

# Current batch41 handoff

Branch coverage-batch-41 starts at pushed40 d795985. Four configured geometry
real homing cases pass full3,536 sanitizer/strict and44 helpers. Hosted40 run39040996935
is live. PR19 merged; cumulative ready PR awaits exact40 hosted gate.
See latest PROGRESS for evidence. Core remains clean ad57c78.

# Current handoff

Branch coverage-batch-40 retains all cumulative work through39. PR19 merged.
Four delta real-boot cases added; full3,532 sanitizer/strict and44 helpers pass. See newest PROGRESS
entry and named known-bug entry for refill-time jog parser-position mismatch.
README snapshot badges now verified from successful hosted39 (95.45/83.79).
Do not report PR ready until full local/hosted validation. Continue goal.

# Repository working instructions

## Objective and delivery

Current branch coverage-batch-39 starts at pushed batch38 f88713e.
Ten new I/O ownership cases total3,528. Driver ports are registered and claimed
through public APIs before commands. All-claimed banks reject G-code without
losing queued80-pulse motion; plugin operations still reach original pins.
Partial claims remap G-code to remaining physical port1 while plugin retains0;
reserved indexes reject without output. Analog rejection checks error/non-output,
not the current incidental RPM-specific status label. Input bank isolation and
mixed synchronized output timing also pass. Integer analog values avoid the
separate documented fractional-value defect; its assertions remain unchanged.
Initial fixture retried aux0 twice; fixed to claim aux0 and aux1. API consumes
an auxiliary number and returns the mapped number to use afterwards.
Shared queued rejection helper factors existing assertions without removal.
All ten focused pass0.57 s. Full batch39-delivery-results.xml passes3,528 in47.53 s; strict summary and44
helpers pass. Session85317 completed. Freeze/push/dispatch39 and continue40.
No core changes, new defects, exceptions or allowances. Hosted37 run39020604172
and38 run39020997626 remain in progress at latest check; latest fully green
batch36 is95.33%/83.57%. Continue independent work while hosted CI runs.

Current branch coverage-batch-38 starts at pushed batch37 77d91aa.
Fourteen new cases total3,518. Ten public parser rejections verify unavailable
I/O/mist, mill-versus-lathe modes, disabled parking override and invalid fractions/
axis-command conflicts preserve modal state and an existing80-pulse move.
Two registered driver-capability cases cover torch start/stop bypass and400 ms
startup delay without feedback polling. Capabilities assigned before registration,
never by modifying spindle_get pointers. Existing feedback helper retains defaults.
Two G65 M-word cases prove M3/M8 preceding G65 become local argument13 without
spindle/coolant activation; callback failure restores parent99 and scope.
No new core defects, exceptions or source changes. Earlier3,516 full checkpoint
passed46.96 s/strict/44 helpers. Full batch38-delivery-results.xml passes3,518 in46.97 s, strict summary and44
helpers pass. Session60112 completed. Freeze/push/dispatch38 and continue39.
Useful next area: ports advertised by driver but unavailable after plugin claims;
use real registration/claim APIs and preserve normal I/O positive controls.
Batch37 exact77d91aa run39020604172 is in progress at last check. Latest fully
green batch36 is95.33% lines/83.57% branches. Latest fetched core remains clean
ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216. Continue substantial coverage work.

Current branch coverage-batch-37 starts at pushed batch36 4dab01a.
Five full-boot cases total3,504. Ordinary reset retains tool0; resetting during
M6/G30 retract preserves stopped position but selects uncompleted tool3 after
warm init. One narrow dated known-bug entry/exception preserves correct tool0.
Normal streamed manual, no-return and G30 return/touch-off controls all pass,
with tool3, actual return positions, original handler and RX suspension released.
The earlier unresolved restoration candidate is now an ordinary test: its mock
needed real stream_rx_suspend and independently delivered tool ACK while read
is paused. TODO removed; no exception for that fixture mistake. Sender waits
for the actual tool pause and for G30 return before sending reference settings.
Real homing calibrates raw motor counters; restart observation requires second
startup greeting. Exclude host CMD_EXIT cleanup from reset counts. Never classify
intermediate pre-init parser state as a restart result.
Full earlier3,501 gate passed49.44 s/strict/44 helpers. Full batch37-delivery-results.xml passes3,504 in46.58 s; strict summary and44
helpers pass. Freeze/push/dispatch37 and continue38. Source unmodified, no
sanitizer allowances;12 known failures. Session50785 completed.
Batch36 run39019490072 fully green verifies4dab01a510964c9563f2ff346b96544553970c08/ad57c78,
16,810/17,634 lines95.33%,11,405/13,648 branches83.57%. PR19 remains open.
Latest fetched core ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216 is clean.

Current branch coverage-batch-36 starts at pushed batch35 63aa882.
Twelve new cases total3,499. Six fixed XYZ tool-offset cases exercise three
new documented TOOL_LENGTH_OFFSET_AXIS variants: correct G43.1 axis, wrong-axis
rejection, actual offset motion, and manual retract/return under G18. CMake
links matching host/test definitions. README configuration list is updated.
Other cases cover compatibility2 rejected fixture modes with handlers preserved,
three parameter-disabled O-number rejection paths preserving queued motor motion,
and G66.1 following-block argument update/error cleanup. Repeating G66.1 was an
invalid modal-group fixture; plain X20 is the intended implicit following block.
No core edits, exceptions or allowances added. Six-case earlier full checkpoint
passed3,493/46.02 s with strict summary and44 helpers; six fixed-axis cases pass
focused0.45 s. Final batch36-final-results.xml passes3,499 in46.23 s; strict summary and
all44 helpers pass. Freeze/push/dispatch36 and continue37. Useful next workflow:
public sender reset/stop during actual G30/toolsetter positioning; verify stopped
position and restored driver/stream handlers, not a forced private abort flag. Latest fetch confirms clean
ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216 remains latest.
Batch34 run39018542932 fully green verifiescaa7509c776e2948c3620329592b6934a72a6c85/ad57c78,
16,792/17,630 lines95.25%,11,386/13,648 branches83.43%. Batch35
run39018951320 remains in progress at last check. Continue independent coverage.

Current branch coverage-batch-35 starts at pushed batch34 caa7509.
Five new tool-change cases total3,487. Observer is installed before tc_init;
real G10 saves notify once, unrelated G55 does not release touch-off wait,
current G54 does, and repeated init does not wrap again. Actual negative-Z
return motion is serviced by the public realtime hook; initial timeout was an
unserviced fixture move, not core failure. Safety-door completion reproduces
lost pending tool: T3M6/current-G10/open door/ack/start/close/start reaches Idle
with parser tool0 and no changed callback, versus tool3/one callback closed-door.
Correct regression remains, one dated known-bug exception/proposal/cleanup added.
No core changes or sanitizer allowance. Full batch35-delivery-results.xml passes46.89 s; strict summary and all44
helpers pass,11 documented expected failures. Freeze/push/dispatch35, continue36.
Latest fetch confirms clean ad57c78 remains latest. Batch33 run39017951972 fully
passes all jobs; artifacts verify8282b95a6b5422aa092b481a6ca75706ed269b72/ad57c78
and header-inclusive filter:16,789/17,630 lines95.23%,11,378/13,648 branches83.37%.
Batch34 run39018542932 was in progress at last check. Continue beyond checkpoint.

Batch34 is validated from pushed batch33 8282b95. Seven laser cases total3,482.
Full batch34-final-results.xml passes46.13 s; strict summary and all44 helpers
pass, ten existing expected failures, no sanitizer allowances/core modifications.
Public hold actions cover M3/M4 disabled/on, stationary zero power, resumed pulses
and50% sender override while held. Door cases use explicit HoldActions3, declared
door capability and valid homed Z/parking setup; laser suppresses Z parking,
blocks open-door start, requires explicit start after closing and resumes power.
Initial implicit-zero fixture flags caused missing restoration; explicit valid
configuration fixes that fixture. No core defect or exception was registered.
Drivers registered before gc_init. Shared ordinary parking setup remains fully
tested. Freeze/push/dispatch34, continue35 with supported tool-change workflows.
Next useful gap: preserve a plugin WCO-saved observer through tc_init and real
G10 during manual tool change; install observer before tc_init, not afterwards.
Batch32 run39017513432 fully green verifies8c0f688/ad57c78,16,781/17,630 lines
95.18%,11,373/13,648 branches83.33%. Batch33 exact8282b95 run39017951972 is
still in progress at last live check. Never call hosted validation green early.

Batch33 is validated from pushed batch32 8c0f688. Six new cases total3,475.
Full batch33-delivery-results.xml passes in46.56 s, strict summary and all44
helpers pass; ten existing expected failures and no sanitizer allowances.
Cases cover sender reset/status during spindle feedback wait, computed O-label
branch/loop execution, common mill header reset and G91.1 arc motor pulses.
No new core defects/exceptions. Core clean latest ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216.
Freeze/push/dispatch33, then continue34 with supported laser hold/resume workflows.
Use registered driver fixture laser_stepper_host.h and public realtime commands;
do not modify spindle_get pointers or force private restoration flags.
Batch32 run39017513432 is still in progress at last live check, source passed.

Current work is coverage-batch-32 from pushed batch31 46c984e.
Seven new reporting cases total 3,469. Full batch32-delivery-results.xml passes
in 46.49 s; strict summary and all 44 helpers pass. Ten documented expected
failures, no sanitizer allowances. Core is clean ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216.
Build capabilities, actual M60 pause reporting and multi-plugin help are ordinary
passes. Two narrow allocation-fallback regressions retain correct visibility and
legacy-only selection assertions; evidence/proposal/cleanup are in KNOWN_BUGS.md.
No core modifications. Freeze/push/dispatch32, continue independent coverage gaps.
Batch31 run38990060016 is fully green, artifacts verify exact46c984e4283b777ad8ed29c5d44c0d9667a389e5
and ad57c78 with header-inclusive core filter: 16,772/17,630 lines (95.13%),
11,362/13,648 branches (83.25%). Batch30 diagnosis also passed.
PR19 remains open on the latest live check; do not call later PRs ready before
required hosted validation or merge PRs yourself.

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
