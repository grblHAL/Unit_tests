# Current checkpoint - 2026-10-25

Coverage expansion STOPPED at the user's request on2026-10-25.
Final draft PR31: https://github.com/grblHAL/Unit_tests/pull/31
Full supported coverage has not been proved. Do not resume without a new request. Never edit
CORE or merge PRs. Basic actual-use regressions only; Ponytail full and explicit
RTK. Passing gates or PR checkpoints do not complete this goal.

Active checkout:
C:/Users/User/Documents/Codex/2026-10-08/https-github-com-petervanderwalt-unit-tests/work/Unit_tests

## Current Git and delivery boundary

- Branch coverage-batch-75 is delivered in final draft PR31. The last measured
  hosted head is ed5b142; later closeout, exact diagnostic data and four locally
  validated workflows are included in the PR. No matcher change.
- CORE clean, HEAD and freshly fetched origin/master both
  b01f481072edecac33d5e40c25869359a5b3fa1f.
- PR28 merged. PR30 is open, ready, unmerged at59b3ad9f9198d9973cc03b7af983c1d9899abc2d:
  https://github.com/grblHAL/Unit_tests/pull/30
  Its exact run40111349496 passed all five jobs. Keep its head unchanged.
- README badges remain that fully green run:98.50% lines/92.48% branches.
  No PR75 readiness claim: the completed Clang matrix failed as described below.
- Preserve/exclude unrelated changes: .github/workflows/reusable-tests.yml,
  .gitignore, scripts/ci_report.py, the legacy optional-description ioports case,
  and drivers/. No CORE edits, merge or unrelated staging performed.

## Existing hosted run: do not redispatch

Run40121790962, exact harnessed5b142 / COREb01f481:
https://github.com/petervanderwalt/Unit_tests/actions/runs/40121790962
One dispatch after duplicate-head/hourly-ceiling checks; one prior run in the
hour. Saved build-asan/batch75-modal-dispatch.json. No active local runner.

Run COMPLETED FAILURE: source, GCC and coverage PASSED; Clang and results
summary FAILED. No active hosted job remains. Do not redispatch this head or
retry merely for diagnostic data. The failed matrix is not a readiness checkpoint.

Downloaded evidence under build-asan/hosted40121790962:
- source-lock-core and report-core-source locks match the exact harness/source/
  core/.*\.[ch]$ filter. Helpers/resolve stages exit0; no findings.85 hosted
  helper checks pass4.841s. Machine proof: verified-source.json.
- coverage-core and report-core-coverage locks match. All seven stages exit0;
  no findings.4,504 total/4,480 clean/24 known/zero failed or skipped.
- GCC report/result locks match ed5b142/b01f481; all five stages exit0 and no
  findings.4,504 total/4,479 clean/25 known/zero failed/skipped. Saved
  report-core-gcc, results-core-gcc and verified-gcc.json.
- Coverage17,491/17,757 lines98.50%;12,836/13,852 outcomes92.67%.
  Raw remaining:266 lines and1,016 branch outcomes. No exclusions.
- Same-source cf41105 comparison: eight new outcomes, zero new/lost lines and
  no lost outcomes. Both inventories reconciled; all266 missing line keys match.
  Machine proof: verified-comparison.json.

## Delivered functional group and measured gains

Six workflows since cf41105 are included in ed5b142:
- Native full-probe status flags show all registered inputs and selected probe2
  without an idle-protection marker. Gain: report1594.
- Feed-only M70/M72 in the existing cutter build restores feed without configuring
  disabled compensation. Gains: gcode541/542.
- Primary-only spindle M70/M72 restores feed120, nominal3000RPM, override120%
  and actual3600RPM without unused-driver calls. Gains: gcode511/4381.
- Physical E-stop still permits $I identification while locked; release/reset/
  explicit unlock and $G remain functional. Gain: system627.
- Background USB DTR leaves the active Telnet sender and its realtime handler
  intact, with no stray welcome banner. Gain: stream327.
- Normal sleep request from forced startup alarm reaches its allowed guard
  (system576), but CORE leaves the state Alarm. Correct Sleep assertion remains
  under one exact WILL_FAIL/known_bug and a dated KNOWN_BUGS entry. Public
  unlock-before-sleep control passes; no sanitizer allowance or private setup.

One full cumulative local ASan/UBSan gate:4,504 cases pass62.62s. Strict summary:
4,478 clean/25 known regressions/one known diagnostic/zero failed or skipped.
Saved batch75-modal-delivery-{build,tests,summary}.log and results.xml. This is
not a reason to rerun unchanged helpers or another full gate for a few cases.

## Current Clang failure and exact saved-evidence handling

Clang locks match ed5b142/b01f481. Fetch/configure/build stages pass; test/classify
fail on only the three existing tapping cases.4,504 total/4,476 clean/25 known/
3 failed/zero skipped. Actual saved indices are30 (eight-axis),28 (recursive),31
(unsupported fallback), all gcode485:32/const27/macro_arguments_push followed by
ASan global-buffer-overflow. Do not mistake diagnostic column32 for the index.
All six new workflows classify as expected: five clean plus alarm-sleep known bug.

Three local exact test/index entries pass saved-output production/first1024
replay; changed index/source/table/function, absent and zero-exit controls reject.
No matcher/assertion/flag/padding/wildcard/range change. Dated KNOWN_BUGS addendum.
Evidence hosted40121790962/{report-core-clang,results-core-clang,verified-clang.json,
verified-new-workflows.json,verified-exact-diagnostic-replay.json}. No CI retry for
these entries alone; post-fatal assertions remain unvalidated.

## Final user-requested closeout

No further authoring or coverage chasing. Added COVERAGE_CLOSEOUT.md summarizing
unfinished/deferred features, disabled/unrouted paths, unresolved contracts and
all remaining evidence limits. The remaining1,016 branch outcomes are not all
proved impossible. Latest measured coverage stays98.50% lines/92.67% branches.
Four local workflows since ed5b142 include the probe-selector status case: actual
G65P5Q1 selects the registered toolsetter and reports ID1 once via ordinary status,
without a protection event or movement. Focused sanitizer/strict pass0.30s.
Saved probe-selector-status-{build,summary}.log and results.xml. No new allowance.
Final cumulative local ASan/UBSan4,508 gate passes152.20s; strict classification:
4,482 clean/25 known regressions/one known diagnostic/zero failed or skipped.
Saved final-closeout-{build,tests,summary}.log and final-closeout-results.xml.
Closeout pushed and final draft PR31 created/attached, with the failed hosted
matrix stated. Coverage work is stopped. No additional hosted run or coverage
expansion is requested. Do not call full supported coverage achieved.

## Further local laser-off positioning hold/resume workflow

Added state_machine/laser_off_positioning_hold_resume_preserves_zero_output_until_explicit_m3.c.
A normal G1X20M5S500 positioning move is held with the public hold-action setting0.
Four held polls retain position and zero output. Resume finishes all1,600 X pulses
with the driver off/zero at every step-service call and every recorded PWM update.
A later explicit G1X21M3S500 cut powers the actual driver and reaches1,680 pulses,
proving the preceding zero-output checks are not an inactive fixture.

Uses existing registered PWM/stepper/hold fixtures and public hold/cycle-start
commands. Initial control observation watched only PWM updates; constant-power
set_state output is now included through the existing driver-level observer.
No CORE defect, new allowance, host variant or private-state injection.
Focused ASan/UBSan and strict1/1 pass0.28s; saved laser-off-hold-{build,summary}.log
and laser-off-hold-results.xml. Expected target: spindle_control888's state.on
false arm in native hold restoration. No measured gain claimed. Outside the
full4,504 gate/ed5b142 report. Accumulate with the two other local workflows;
no small full-run/hosted cycle or diagnostic-only dispatch.

## Further local queued work-offset reporting workflow

Added report/queued_g92_transition_reports_forced_work_offset_with_feed_override.c.
An ordinary X20 cut remains queued while G92X0 and the next X5 cut are parsed
with offset synchronization disabled. Before transition, status reports the first
move's WCO0. At the real stepper block transition, a public110% feed override and
ordinary status request report both Ov110 and forced WCO20; the next report does
not repeat WCO. Both moves complete at2,000 physical X pulses / machine25mm,
with G92 offset20 and no dropped motion. Public st_get_offset_id only observes
the transition; no report flag or private state is injected.

Focused ASan/UBSan and strict1/1 pass0.27s; saved queued-g92-status-{build,summary}.log
and queued-g92-status-results.xml. Targets report1498's ForceWCO arm via its native
stepper512 producer, plus corresponding work-offset refresh outcomes. No new
allowance or measured coverage claim. Outside the full4,504 gate/ed5b142 report.
Accumulate with the permanent-idle-lock sender reset before a substantial gate.

## Further local ordinary reset workflow

Added boot/sender_reset_with_permanent_idle_lock_stops_step_timer_before_restart.c.
The existing actual-homing/positioning/reset fixture now also covers a machine
configured with permanent motor idle lock ($1=255). A normal sender reset during
queued positioning stops the real step timer before the public on_reset observer
runs, keeps enable output asserted at that instant and queues the normal release
delay. Captured motor pulses/positions remain unchanged through warm restart;
parser position remains synchronized and $G answers. No motion-state injection,
new host variant or allowance. The reset observer chains the installed callback.

Focused ASan/UBSan and strict1/1 pass0.35s; saved idle-locked-reset-{build,summary}.log
and idle-locked-reset-results.xml. Expected target: stepper267 pending-alarm arm
under permanent idle lock. No measured gain claimed. Outside the full4,504 gate
and ed5b142 hosted measurement. Accumulate independent useful workflows before
another full gate/push/CI; do not dispatch for this case or diagnostic data alone.

## Existing tapping diagnostics and previous failed matrix

Previous40118321363/cf41105 passed coverage98.50%/92.61% and GCC but failed
Clang on the existing recursive tapping index29, gcode485:32, const27-entry
table, macro_arguments_push; followed by ASan global-buffer-overflow.
The exact saved diagnostic entry is included in ed5b142. Production runner and
first1024 replay accept that actual evidence; changed index/source/table/function,
absent diagnostics and zero exits reject. No matcher/assertion weakening, ranges
or wildcards. Earlier clean exits still reject; unchanged source does not prove
resolution. Post-fatal assertions remain unvalidated.
Evidence: hosted40118321363/verified-exact-diagnostic-replay.json and dated
KNOWN_BUGS addendum. Never dispatch just to collect another signature.

## Only if the user explicitly resumes coverage

1. Current compiler/coverage evidence is complete and reconciled. Keep badges
   and PR30 at the fully green head. Commit the coherent evidence/data group;
   do not push/dispatch a signature-only checkpoint. Resume independent ordinary
   coverage work before the next substantial delivery boundary.
2. Continue supported line gaps before more branch permutations. Both recent
   measured groups added useful distinct branch behavior but no lines. Do not
   repeat settled audits or manufacture private states to fill the denominator.
3. Keep Modbus42/69 switch-default proof and fs_ram fresh-allocation/exclusive-
   reference/live-owner proof from the inventory; no invented transport, stale
   handle or multiple-owner fixture. Stream614 ClearAll returns before its
   observer; state819 changes handler before its restoring flag. Existing native
   controls remain. Maintainer-deferred G76 taper and polar/wall homing stay TODO.
4. Accumulate meaningful work on this branch; one full gate/hosted checkpoint at
   a substantial delivery boundary. Prepare the next PR only from verified live
   Git/PR ancestry and compiler evidence. Never merge PRs.

# Archived detailed checkpoint - 2026-10-24 (superseded by TOP)

Full objective remains meaningful supported CORE line AND branch coverage.
Goal ACTIVE; never edit CORE or merge PRs. Use Ponytail full and explicit RTK.
Work in C:/Users/User/Documents/Codex/2026-10-08/https-github-com-petervanderwalt-unit-tests/work/Unit_tests.

Branch coverage-batch-75 has validated local followups; pushed origin/coverage-batch-75
remains atd05945e968eab3e3684ebbfcb0cffef5a1ae4218.
PR30/origin74 remain at validated59b3ad9f9198d9973cc03b7af983c1d9899abc2d. PR28 is merged. PR30 is READY FOR REVIEW at this exact pushed head:
https://github.com/grblHAL/Unit_tests/pull/30
PR30 is exact-head validated and marked ready via GitHub; no merge performed. All eight cases and exact diagnostic
entries below are included in its current pushed head.
Exact-head hosted40111349496 COMPLETED SUCCESS against COREb01f481:
https://github.com/petervanderwalt/Unit_tests/actions/runs/40111349496
Do not redispatch. All five source/GCC/Clang/coverage/summary jobs passed.
Continue independent supported workflows; full coverage goal remains ACTIVE.
CORE clean at b01f481072edecac33d5e40c25869359a5b3fa1f; latest fetched Terje ref
matches. Do not switch/modify source without a deliberate compatibility pass.

## Batch75 hosted checkpoint and continuing work

Exact-head run40114356917 COMPLETED FAILURE on d05945e/COREb01f481:
https://github.com/petervanderwalt/Unit_tests/actions/runs/40114356917
Dispatch accepted2026-10-24T17:03:06Z after checking duplicate heads and the
three-per-hour ceiling (one prior run in that hour). Saved
build-asan/batch75-dispatch.json. Do not redispatch on observation timeout.
Coverage now PASSED and downloaded; both artifact/report locks verified exact
d05945e/COREb01f481/filter core/.*\.[ch]$, allseven stages exit0/no findings.
4,498 total/4,475 clean/23 known/zero fail/skip. New locked counts:
17,491/17,757 lines98.50%;12,820/13,852 branch outcomes92.55%.
266 missing lines/1,032 missing outcomes. Same-source40111349496 comparison:
zero new/lost lines; +9 branches/no loss. Exact gains gcode122(two)/4622,
ioports1214/1256/1316, motion_control1028, ngc_params753, report1581. These
match all six actual-use regressions. Both inventories reconciled; exact raw
line keys unchanged266. Saved build-asan/hosted40114356917 coverage/report
artifacts and verified-comparison.json. GCC PASSED; exact report lock verified d05945e/b01f481, allstages0/no findings.
GCC4,498 total/4,474 clean/24 known/zero failed or skipped. Saved
report-core-gcc. Clang/Results summary FAILED; badges stay on
fully green40111349496 and PR30 stays unchanged. Never report this matrix
green before exact compiler evidence. Local full4,498 passed63.51s.

Further authoring, outside pushed/measured head: existing spindle_control/
pwm_laser_overdrive_adds_and_clamps_duty.c now also disables overdrive via
its public callback, checks the flag/percentage clear and normal running/off
PWM conversion. Targets spindle_control1043's documented zero-percent branch.
No new case/helper/exception. Focused ASan/UBSan and strict summary PASSED1/1
in0.28s, saved build-asan/laser-overdrive-disable-{build,summary}.log and
laser-overdrive-disable-results.xml. This extension is local/uncommitted and
outside d05945e/full4,498 gate. Accumulate the next group before any full gate/CI.

Terminal Clang evidence: exact d05945e/b01f481 artifact lock verified; test/
classify stages fail.4,498 total/4,471 clean/24 known/3 failed/0 skipped.
All six newly authored workflows individually pass without any known-failure
labels (verified-new-workflows.json). The failures are the existing tapping
regressions: eight-axis index28, unsupported fallback index30, and recursive
case exit0/no diagnostic. The actual XML/logs identify indices28/30, not the
report summary's source-column32 text. Existing strict wrapper correctly rejects
the absent recursive diagnostic. No new behavior defect or blanket allowance.

Two local exact test/index entries for actually recorded28/30 pass production
runner replay and compact first1024 evidence. Changed index/source/table/function
and zero-exit diagnostic output reject; the actual saved recursive clean output
still rejects. Matcher implementation and assertions unchanged. Dated KNOWN_BUGS
addendum; saved report-core-clang/results-core-clang artifacts and
verified-exact-diagnostic-replay.json. These manifest additions are outside
pushed d05945e. Do not rerun CI for them alone; recursive case remains a strict
red outcome until the underlying fault/exception is correctly resolved.

Independent basic work: full-boot program_end_reenables_parking_for_next_cut_
after_public_m56_disable.c uses public settings/$HZ/G0/M56/M2, physical door IRQ,
Z retract/restore and next-cut completion. No synthetic homed/position state.
Focused ASan/UBSan and strict summary PASSED1/1 in0.27s; logs/XML are
program-end-parking-{build,summary}.log and program-end-parking-results.xml.
$41=5 is enabled/override-control/initially-active; initial fixture used3,
which correctly normalizes to7 (initially disabled), so fixture was corrected.
No CORE defect. Public $HZ establishes actual homed Z; M56P0 disables parking,
M2 restores active policy, door IRQ during next cut causes640-step retract,
four parked polls and640-step restore, then exact160-step X endpoint. No
synthetic homed/position state. Expected missing branch gcode5104; no measured
gain for this local case or PWM extension until next cumulative checkpoint.
One new case only; no full gate/hosted run for these followups alone.

Current branch-route refinement (no new tests/count changes): Modbus42/69's
three supported RTU/ASCII/TCP switch cases are all covered. The missing outcomes
are switch defaults in source-block1, not omitted optional callbacks. is_up
true/false counts108/2 and busy callback present/absent28/4; existing reset and
ASCII cases already exercise omission. Both inventory rows now carry specific
current evidence so this review is not repeated. No invented transport case.

## Cumulative followup validation in progress

Six independent ordinary workflows since d05945e are now accumulated: physical
M2 parking reset, actual-homing reset policy, unchanged persistent G92 save,
PWM overdrive disable, compatibility2 extended-coordinate query and tool-only
modal notification. Two exact saved diagnostic entries also have production
replay proof; recursive clean exit still rejects. No matcher code changes.

New compat_2 case extension: public G59.3 selection remains unsupported while
$#=5381 returns its compatibility placeholder0; previously saved G54 values,
active coordinate system and machine position stay intact. Target ngc_params319.
New report/realtime_tool_only_change_requests_modal_notification_without_repeated_events:
public $10=512 and M61Q7, one tool callback and one modal notification, sender
modal reportT7, no duplicate notification on unchanged report/no motion. Target
report1636. Both focused sanitizer checks pass. Tool-report fixture needed its
normal mandatory on_tool_changed observer and state_machine.h; no CORE defect
or new allowance. No private tool-id assignment or new host variant.

Fresh CORE fetch still b01f481 clean; PR30 remains open/ready/unmerged59b3ad9.
One cumulative local ASan/UBSan/strict gate is now running before next push.
Use build-asan/batch75-followup-delivery-{build,tests,summary}.log and results.xml.
Do not start a competing runner or repeat unchanged helper checks. No new
coverage attribution until its exact-source hosted report.

## Continuing local ordinary workflows

Extended existing gcode/m2_persistent_g92_updates_changed_saved_offset.c:
a later M30 with the unchanged persistent G92 offset must not produce another
coordinate-save notification, while the offset and second completion remain
correct. Focused ASan/UBSan and strict1/1 pass0.29s, saved
build-asan/persistent-offset-repeat-{build,summary}.log and
persistent-offset-repeat-results.xml. No new case/exception; target gcode5122
(equal saved/runtime offset). No new hosted measurement or full-gate claim.

Added boot/keep_homed_reset_option_preserves_actual_homing_after_sender_cancels_cut.c.
Public $22/$44 configure real Z homing, $676=14 disables clearing homed status
when position is lost. $HZ establishes the axis before a real feed; sender reset
cancels before endpoint, warm restart retains configured Z status, $X unlocks,
$G responds, and physical pulses/software counters remain stable thereafter.
The local service respects the driver's timer-running state. No synthetic
homed mask/position/reset flags. Focused ASan/UBSan and strict1/1 pass0.28s,
saved keep-homed-motion-reset-{build,summary}.log and results.xml. Expected
missing branch grbllib459 (keep option evaluated during reset after motion).

Fixture corrections: public Z cycle must be configured, since reset filters
homed axes against configured cycles; reset during motion promises no mechanical
position accuracy, so assertions verify stable stopped software/physical counters
separately; idle/nonabort checks run before the host-only CMD_EXIT, which itself
requests shutdown. No firmware defect or new allowance. Current CTest listing
verifies4,500 registered; latest full gate remains4,498 before these two new
boot cases and later existing-case extensions. No tiny full gate/CI.

Current fs_ram branch review completed once for103/140/146/148/153. Fresh
metadata is calloc-zeroed; open rejects nonzero refs before the sole increment;
valid owners are0/1 refs; unlink callers retain live linked owners. False arms
need altered allocator semantics, impossible multiple owners or stale handles.
Existing exclusive-open and list-deletion cases already cover actual lifetimes.
Five inventory rows now have specific current-source evidence, retaining all
raw outcomes. No fabricated file, stale handle or duplicate multiple-reader test.

## New coverage evidence and ongoing authoring

Hosted40111349496 coverage PASSED, exact harness59b3ad9/COREb01f481/filter
verified in both artifact locks, allseven stages exit0/no findings:
17,491/17,757 lines98.50%;12,811/13,852 branches92.48%.
266 missing lines/1,041 missing outcomes. +10 outcomes/zero new or lost lines
against40107107939; no lost branches. Exact sites: gcode286/5142,
machine_limits331/332, protocol757, spindle_control1416/1436, stepper2 425/429/435.
Coverage4,492 total/4,469 clean/23 known/0 failed/skipped. Inventories reconciled;
line inventory exact266 keys unchanged. Saved build-asan/hosted40111349496
coverage/report artifacts and verified-comparison.json. GCC/Clang/Results summary now PASSED; all five jobs completed successfully.
Both compiler report locks verified exact59b3ad9/b01f481; allstages exit0, nofindings.
Clang4,492/4,465clean/27known; GCC4,492/4,468clean/24known; zerofail/skip.
All eight new cases individually pass Clang. Existing exact tapping diagnostics
reproduce29/27/28; post-crash assertions remain unvalidated. Saved compiler reports,
Clang XML/logs and verified-new-workflows.json. README badges updated to this
fully green run. PR30 validated at exacthead and marked ready for review; never merge.

## Batch75 cumulative delivery validation

Six added actual-use cases pass one cumulative full ASan/UBSan/strict gate:
4,498 total in63.51s;4,473 clean/24 known regressions/1 known diagnostic/
zero failed or skipped. Logs/XML: build-asan/batch75-delivery-{build,tests,summary}.log
and batch75-delivery-results.xml. No unchanged helper rerun. Pushed d05945e; one exact-source hosted checkpoint is running above.
Do not redispatch74 or75. Gains are now measured in the successful coverage job above; compilers pending.
PR30 stays ready at59b3ad9. The first four cases are local828e4ff:
- homing/named_homed_state_tracks_individual_switch_homing_without_combined_cycle:
  public individual-axis configuration/no combined cycle; $HX/$HY/$HZ physically
  finish70/110/150steps. Named and sender |H completion/masks track0/1/3/7;
  completion becomes true only after Z. Normal foreground servicing between commands.
- eight_axis/absolute_g28_rotary_return_keeps_intermediate_move_with_wrap_enabled:
  public rotary/wrap settings and G28.1 saveA10; actual move toA90, then
  G90G28A0 travels100degrees through the intermediate point to saved10. It does
  not substitute the relative-mode shortest-angle shortcut. Other axes stay still.
  Initial270degree setup exceeded the shared fixture's cumulative poll budget;
  shorter90degree setup exercises the same distinct absolute-return contract.
- gcode/dynamic_laser_spline_job_powers_both_curve_types_and_blanks_rapid:
  real registered PWM driver/stepper execute cubic and quadratic cuts; both
  produce powered motor steps at exact endpoints. Following rapidX3 adds no
  powered steps; M5 shuts off. No fixture-private motion state injection.
- motion_control/unhomed_manual_probe_keeps_hand_probe_without_toolsetter_selection:
  public G38.2Z1F100 before homing with installed provider; no toolsetter callback,
  contact latched40steps, physical axis decelerates before requested80, logical/
  physical/pulse counts agree; probe disarmed and no alarm. Initial assertion
  wrongly equated contact latch and stopped position; corrected to normal
  deceleration contract. No CORE defect/allowance.

Two additional normal dedicated-pin save cases pass focused2/2 sanitizer/strict
in assigned-pin-save-results.xml (0.34s): assigned_probe_save_keeps_auxiliary_
inversion_and_persists_probe_configuration and assigned_coolant_save_preserves_
auxiliary_inversion_and_persists_open_drain. Public assignment removes the
pin from generic inversion ownership; driver save retains neighbor mask2,
persists dedicated probe inversion/pullup or coolant open-drain, then clears
those options without changing the neighbor. NVS bytes are read back. Output
assignment does not perform claim remapping; direct aux1 still reaches pin1.
Expected new branch targets ioports1214/1256; no new CORE defect/exception.
Fresh CORE fetch remainsb01f481 clean. PR30 live open/ready/mergeable at59b3ad9;
no merge performed. Keep its validated head unchanged; successor75 is local.

Saved individual CTest XMLs are combined without rerunning into
build-asan/batch74-followup-focused-results.xml; strict summary passes4clean,
zero failures/skips. No new coverage claim, exception or unchanged helper rerun.
Expected new branch targets: gcode122/4622, ngc_params753, report1581,
motion_control1028. Gains require next cumulative hosted report.
Current stream_file73 review is now specific native reader/file-pairing proof:
read installs both at160; close209-214 restores both. Only those two native
stream_set_file callers exist. External NULL-file/retained-reader meaning is
unestablished; no private stale-reader invocation added. Raw line remains.
All existing unrelated workflow/reporting/driver scaffold edits remain excluded.

## Prior batch74 local delivery validation

Eight later actual-use workflows (listed below) now pass one cumulative full
ASan/UBSan/strict gate:4,492 cases in63.97s,4,467 clean/24 known regressions/
1 known diagnostic/0 failed/skipped. Logs/XML are
build-asan/batch74-controller-workflows-{build,tests,summary}.log and
batch74-controller-workflows-results.xml. No unchanged helper rerun.
New exact diagnostic entries also pass saved production replay/first1024 and
changed/absent/clean-exit negative controls. CORE fresh fetch stillb01f481 clean.
Committed/pushed59b3ad9; one exact-head hosted checkpoint completed successfully as recorded above.
Unrelated edits excluded.

## Prior hosted result (superseded by successful40111349496 above)

Run40107107939 COMPLETED FAILURE on49b18b0/COREb01f481:
https://github.com/petervanderwalt/Unit_tests/actions/runs/40107107939
Source/GCC/coverage PASSED; Clang/Results summary FAILED. Do not redispatch it.
Coverage artifact AND report locks match harness/source/filter core/.*\.[ch]$;
allseven coverage stages exit0, no findings. Coverage4,484 total/4,461 clean/
23 known/0 failed/skipped. All nine newly authored workflows individually pass
on Clang, verified against saved XML (verified-new-workflows.json).

17,491/17,757 lines98.50%;12,801/13,852 branch outcomes92.41%.
266 raw missing lines/1,051 missing outcomes. Against same-source40103625282:
zero new/lost lines; +10 outcomes/no loss. Exact gains:
gcode2998; delta761/907; report395/1480/1498; settings2163(three)/2260.
Both inventories/GAPS reconciled, retaining dispositions and function/block IDs.
The nonblocking MPos case passed but added no outcome; the missing synchronized
opposite path is now covered by a later local functional case, unmeasured.
Badges remain on fully green40074304720; this failed matrix is not green.
Evidence: build-asan/hosted40107107939/{coverage-core,report-core-coverage,
report-core-clang,results-core-clang}, verified-comparison.json and last-status.json.

Previous49b18b0 local full ASan/UBSan/strict gate PASSED4,484 in148.53s:
4,459 clean/24 known regressions/1 known diagnostic/0 failed/skipped.
Logs/XML: build-asan/batch74-normal-workflows-{build,tests,summary}.log and
batch74-normal-workflows-results.xml.17 matcher helpers previously passed;
matcher implementation is unchanged. No active local runner. New exact-head run is listed above.

## Prior Clang tapping fault and current exact entries

Clang4,484 total/4,457 clean/25 known/2 failed. Eight-axis handoff now reports
index29, unsupported fallback index27; recursive index27 matches. All identify
const27-entry table, gcode.c485:32 and macro_arguments_push top frame followed
by ASan global-buffer-overflow. Earlier runs also show different indices or a
clean executable exit without a diagnostic, so the source fault varies by build.

Two additional exact test/index entries recognize these actual saved
outputs. Production runner replay/first1024 checks pass; different indices/source,
absent diagnostics and zero-exit diagnostic output reject. No range/wildcard or
matcher implementation change. KNOWN_BUGS addendum records the evidence. Keep
all correct assertions; post-crash paths remain unvalidated on Clang. No CORE edit.
Do not force padding/private state or weaken assertions for a repeatable fault.

## Current pushed actual-use group (after49b18b0)

- homing.autosquare_minimum_tolerance_allows_normal_switch_separation:
  public1%/min2mm/max5mm permits normal0.5mm switch gap; motors release at70/110
  steps, successful home/no reset. Targets machine_limits332 minimum clamp.
- homing.autosquare_maximum_tolerance_stops_before_second_switch:
  public20%/min0.1mm/max0.25mm stops before second switch; expected approach alarm,
  no homed flag. Targets machine_limits331 maximum clamp.
- protocol.mist_override_during_real_jog_is_ignored_until_a_new_idle_request:
  real $J=G91X1F100 reaches80 X pulses; mist ignored during Jog with no deferred
  toggle, fresh Idle request works and M9 clears it. Targets protocol757.
- motion_control.synchronized_machine_position_report_uses_offset_after_prior_cut_completes:
  public $10=289 drains prior80-pulse cut before G92, reports MPos1/WCO1, then
  next actual cut reaches160 X pulses. Targets gcode286 synchronized path.
- stepper2.timer_driven_finite_reversal_keeps_step_count_and_direction:
  actual timer callback executes20 reverse then30 forward steps;50 pulses,
  signed endpoint10, two timer stops, no optional stopped callback. Targets
  inlined stepper2425/429 outcomes; no private motor/profile access.
- gcode.check_mode_prescan_suppresses_program_end_feedback_until_option_is_disabled:
  public prescan setting and $C/M2 complete verification without runtime end
  feedback or physical motion; disabling option restores one ProgramEnd message
  on next M2 while keeping verification mode/no output. Targets gcode5142.
- multi_spindle.secondary_pwm_settings_retry_after_output_expansion_preserves_base_ports:
  a digital-only board declines optional PWM settings without NVS allocation or
  changing its base output. One registered PWM expansion then permits settings
  allocation, correct default ports and saved6000 RPM reload. Targets spindle1436.
- multi_spindle.secondary_pwm_single_enable_port_leaves_direction_unassigned:
  registered enable0/PWM0 board restores valid defaults with no direction pin;
  public getter reports direction -1, and configuration writes no output.
  Targets spindle1416. Both PWM cases sanitizer/strict pass0.10s together in
  secondary-pwm-normal-ports-results.xml. Eight cases form the current
  pushed group; the cumulative full4,492 gate passes63.97s.
Both pass focused sanitizer/strict0.07s each: timer-finite-reversal-results.xml
and check-mode-prescan-end-results.xml in build-asan. These two were validated before the later PWM cases.
Earlier four focused sanitizer/strict checks pass: autosquare pair0.12s, jog0.07s,
synchronized MPos0.07s. XML: autosquare-tolerances-results.xml,
jog-mist-override-results.xml and mpos-synchronized-offset-results.xml in build-asan.
No new CORE defect/exception or measured coverage gain for these cases.
Full4,492 sanitizer/strict gate passes63.97s; committed/pushed59b3ad9 with
one hosted measurement now running. No CORE edits or new defect assertions.

## Current-source line gap proof (no artificial tests)

Aggregated function counts across all variants in the saved report identify12
wholly unexecuted functions (artifact aggregated-unexecuted-functions.json).
Current b01 source proof upgrades nine historical line annotations without
changing covered counts or excluding source:
- report_driver_error: driver.ok failure sets SelftestFailed/schedules callback,
  leaves driver_started false, and native startup filtering discards that
  non-warning callback. Existing failed-driver and USB-warning boot tests already
  validate the ordinary route; no private task invocation is legitimate.
- output_help: HELP prefix returns directly to report_help before the table;
  that private table wrapper has no native command-string path.
Do not repeat these source checks or add direct private calls to inflate lines.
Remaining function entries retain their existing TODO/implementation/guard scope;
this is not a universal completion claim. Raw266 missing lines remain unchanged.

## Preserve and continue

Unrelated concurrent changes: .github/workflows/reusable-tests.yml, .gitignore,
scripts/ci_report.py, untracked drivers/, and phantom M on
tests/cases/ioports/legacy_registration_allows_missing_optional_description_callback.c.
Inspect live status and preserve these; do not stage them with coverage work.
Continue distinct basic controller workflows on74; accumulate another useful
batch before one cumulative gate/push/hosted measurement. Do not chase duplicate
assertions or dummy values. Retain raw denominators for source invariants.
Maintainer TODO remains G76 main taper, all polar/wall homing and zero locate
feed homing; named macro files must prescan before execution.
Passing tests/commits/PR checkpoints do not complete or stop the full goal.
Historical sections below are evidence only and never override this checkpoint.

## Full-boot servo/GPIO settings ownership - 2026-10-24

Second local workflow after pushed8b189a9 registers a mixed digital bank with
one driver-owned servo PWM mode and one ordinary output. Normal driver_setup
receives CORE's true ioinit_pending state and dispatches the settings-change
hook; the test never sets that private flag. Saved inversion/open-drain apply
to the ordinary output while the servo callback remains untouched. Subsequent
public ioport_claim and digital PWM configuration reach that same servo pin
at50Hz, proving it remains usable. Sender report completes without error.
Focused ASan/UBSan and strict summary pass0.07s; no new defect or allowance.

This targets ioports1625's servo exclusion during settings load. It does not
claim allthree remaining outcomes at that compound site are covered. Initial
fixture missed the driver's setup notification and the PWM API's required
claim/capability; both were repaired through normal driver/public API paths.
Two new local workflow files now await a substantial next-batch gate. No
full gate, push or extra hosted run for this small group; keep40093560650 as
the sole hosted checkpoint for8b189a9.

## Y-only toolsetter restoration - 2026-10-24

One new local case after pushed8b189a9 targets tool_change140's missing true
outcome when X already matches but Y needs restoring. Automatic toolsetter
G59.3 is atX2/Y1 while the original point isX2/Y3. Real probing establishes
the reference; restore returns to original XYZ with320 Y pulses and zero X
pulses. Existing pulse observer requires Z=0 on every lateral step. Probe
contact/reference, command/control handler restoration and a public same-tool
request confirm completion without repeating motion. Focused ASan/UBSan and
strict summary pass0.10s, no new defect or allowance.

G30 manual change was unsuitable for this specific target: its initial
acknowledgement returns XY before touch-off, so it does not leave Y different
at restore. The case uses the normal automatic toolsetter path instead. No
manual-only observer contract is imposed on the HAL-level automatic workflow.
No cumulative gate/push/hosted dispatch for this single addition; contribution
to current residual coverage is unmeasured.

Existing hosted40093560650 was checked once during this work: exact8b189a9,
source job success; GCC/Clang/coverage job handles remained in_progress. Do not
restart or redispatch based on a later observation timeout. Continue useful
independent authoring and inspect this same run at a useful checkpoint.

## Four forced pointer outcomes and NVS owner contract - 2026-10-24

Independent post-push review checked current source against retained JSON.
stream_file96/124/164 missing block2/branch3 outcomes and spindle_control594
_get_ramp block3/branch5 each test a pointer assignment after guarding that
same pointer nonnull, without an intervening call. Updated exact CSV statuses
and COVERAGE_GAPS explanation: four forced operands, no exclusions, no new
percentage/coverage claim and no private mutation or synthetic race test.

NVS162's remaining source-pointer equality is a distinct owner-contract
question: copying advances source before comparison with driver mirror base.
Public RAM-location metadata alone does not authorize assuming in-place
provider-save semantics. TODO records the need for an actual caller/contract,
not a confirmed defect or universal dead-code claim. Continue other supported
workflow gaps; do not repeatedly rediscover these four structural outcomes.
No additional build, full suite, push or hosted dispatch for this audit.

## Cumulative delivery gate - 2026-10-24

Single accumulated build and full ASan/UBSan gate passes4,472/4,472 cases in
147.61s at COREb01f481, ten new workflows across nine modules. Strict counts:
4,447 clean passes,24 known regressions and1 known sanitizer diagnostic;
zero failed or skipped.
Strict summary is build-asan/batch74-cumulative-summary.md; raw result is
build-asan/batch74-cumulative-results.xml. All source files unchanged during
execution; CORE remains clean.83 helper tests previously passed on unchanged
reporting code; they were not rerun redundantly.

The production fatal runner also recognizes the actual saved Linux-Clang fault
and its first1024 output characters, returning its exact deliberate1. Linux
execution of that CMake-specific launcher still needs the hosted checkpoint.
This local full gate does not change failed hosted40082861198 or coverage
percentages. Committed/pushed8b189a9 and dispatched sole exact-source run40093560650;
frozenPR28 remains untouched. Continue independent work while it runs. No full-gate repetition absent a shared change or unresolved failure.

## Extension/G66 integration and live PR checkpoint - 2026-10-24

GitHub API freshly verifies PR28 is OPEN/non-draft, mergeable=true/state clean,
head a9f355c35717006f497754d1acc421cf5b141670 on coverage-batch-73. Allfive
exact-head checks (source/GCC/Clang/coverage/CI diagnosis) completed success.
No merge or PR update was performed. Newer batch74 work remains separate.

New cutter-comp-enabled scenario installs a public motion-extension filter
with real foreground step generation and modal macro callback. Rejected G1/G0
queue no motion and invoke no macro; parser errors normally clear G66, so the
sender explicitly rearms before accepted retries. Accepted feed/rapid each
invoke exactly once with the stored argument and correct local scope. The
callback observes accepted logical target/queued motion; physical completion
is checked at public synchronization boundaries, not inside the parser loader
callback. Caller1 restores99, G67 stops subsequent invocation, and the final
move reaches240 pulses/physical/logical X steps with Y/Z stationary.
Focused ASan/UBSan passes0.09s, no new CORE defect or allowance. Earlier fixture
assumptions about error retention and callback physical completion were corrected.

This exercises a distinct supported configuration interaction at gcode4762/4778.
Its contribution to repeated JSON function/source-block identities is still
unmeasured; do not claim that all six missing outcomes are now covered. No
extra full gate or hosted dispatch for this single case. Continue the batch.

## Interrupted spindle reduction and optional PWM startup - 2026-10-24

New sender CMD_RESET during an8000->2000 RPM ramp reaches the previously
missing aborted-deceleration outcome at spindle_control733. Hardware is off
before driver reset notification; no final2000 target write occurs and30 later
scheduler advances produce no PWM restart. Correct timing measures completed
reset dispatch, not command enqueue. Focused ASan/UBSan passes0.07s.

Full boot registers two PWM drivers with valid precomputed PWM contexts and
no optional config callback. Additional PWM's startup task initializes it off
exactly once before the primary M3S3000 job; M5/report succeed, secondary stays
disabled and isolated. This targets spindle_init63's missing NULL-config arm:
its extra-PWM startup caller is supported even though the direct unused-primary
caller checks config first. Focused ASan/UBSan passes0.07s. Initial fixture
omitted required PWM context and assumed serial reads followed startup; both
fixture mistakes were corrected, with no CORE issue/allowance claimed.

No new full gate, push or hosted run. Both branch gains await the next
substantial cumulative measurement; no additional raw line gain is claimed.

## Public O CALL final-argument inheritance regression - 2026-10-24

CORE remains cleanb01f481; remote Terje master verified at the same revision.
New real-RAM/protocol scenario calls a subroutine with all30 arguments, then29.
Full30 control receives29/30; the29 call receives argument29 correctly. Both
restore caller1=99/29=72/30=73 and execute the following root statement with
scope back at0. Only the correct omitted-argument30 inheritance assertion fails.
LinuxCNC O-call documentation explicitly requires omitted locals to inherit
calling-context values; link and exact source cause are in KNOWN_BUGS.

ngc_flowctrl754-760 increments param_id to30 after29 supplied arguments, then
`param_id < 30` skips initialization of params[29]. No private state, prescan
policy change or required corrupt value. Correct assertion retained, one exact
WILL_FAIL/known_bug, dated bug entry, no sanitizer suppression/CORE edits.
Raw call-argument-boundary-raw-results.xml is red; classified sanitizer check
and strict summary pass0.06s with exactly this known regression. Pending future
coverage measurement of branches754/759; no claimed new lines or full gate.

## Supported shared-switch homing and exhausted RTU storage - 2026-10-24

Two new public configuration workflows target existing missing branch outcomes,
not new raw line regions. Shared end-of-travel switches start clear and use
CORE's own limit-to-home adapter; full boot $HX completes110 physical X pulses,
ends at70 physical steps/-10 logical steps, releases the switch and leaves Y/Z
stationary. This covers the previously missing clear-input decision at
motion_control870; focused ASan/UBSan passes0.05s.

Existing plugins reserve available NVS through nvs_alloc before Modbus startup.
Transport initialization then fails with Alarm_SelftestFailed, preserves the
existing reserved address/size, registers neither its API nor baud settings,
preserves the report handler and transmits no frames across20 foreground polls.
This targets modbus_rtu592's failed-storage operand; focused ASan/UBSan passes
0.05s. No new defects or allowances. Coverage gain is unmeasured. No full gate,
push or hosted run was dispatched for these additions.

# Verified residual-audit measurement and compound setup reset - 2026-10-24

Frozen2d8b8d0 hosted40074304720 is fullygreen: allfive jobs passed, both artifact
source locks match harness/CORE2e165a1/filter, allseven coverage stages exit0.
4453cases:4427clean/26known/0failed/skipped.17483/17756lines98.46% and
12737/13834branch outcomes92.07%. Exact hit-set comparison with40070163310:
new machine_limits269 and delta320-321, no lost lines; seven branch outcomes.
Residual CSV now exactly matches the latest273 missing source/line pairs.
Badges and measurement references updated; newer local cases are excluded.

Measurement corrected a source-only assumption: the earlier idle G76 preparation
reset does not cover715. A distinct implemented Q29 compound setup queues its
initial rapid, then the next public foreground poll requests reset before the
first radial approach. New focused ASan/UBSan passes0.15s: queued setup observed,
zero pulses/sync starts/position loss and no later motion. No private flags or
invented IRQ interleaving. Targets715; next cumulative measurement must prove it.
New local delta manual-reference/soft-limit cases remain outside this frozen
report, with1clean control and3correct known regressions classified. No additional
full gate/push/hosted dispatch for the new local cases. Full objective active.

# Manual-first delta control and false soft-limit cut - 2026-10-24

Reference A before real XYZ homing to avoid the separate post-XYZ manual reference
bug. Positive control reaches X100/Z-300/A-1 with $20 enabled; published cuboid
maxX1 proves non-cuboid path, physical pulse-derived/logical motor counters agree.
Targets643. A normal1mm Z cut with limits off succeeds, then enabling$20 falsely
alarms on the next valid1mm cut with stationary A0. Auxiliary checker wrongly
forwards delta motor-frame false to the original Cartesian checker. One new exact
WILL_FAIL, correct first-cut/no-alarm/second-cut assertions, dated KNOWN_BUGS;
no CORE changes or sanitizer allowance. Raw strengthened control shows7acks,
XYZpulse0=108/98 and soft_limit1 before the correct assertion fails.
Four-case classified ASan/UBSan plus strict summary passes0.55s:1clean control,
3known regressions,0unexpected failures/skips. No full gate/push/new hosted run.
These new local cases follow frozen2d8b8d0; retain its sole run40074304720.

# Public manual A reference and delta coordinate defect - 2026-10-24

New shared full-boot fixture homes XYZ with actual switches, enables manual
homing via$22, then uses$HA for A. No sys.homed/coordinate injection. Physical
XYZ do not move, but stored XYZ change0->-6steps at1000steps/rad. Correct
coordinate-preservation regression retained. The independent$20/jog sequence
rejects A999 correctly but also rejects in-range A-1 (fiveacks instead of six,
no A pulses); its correct retry/endpoint assertions remain. Both have exact
WILL_FAIL and one dated KNOWN_BUGS entry; no sanitizer allowance or CORE edit.
Raw evidence: delta-manual-a74-{raw,retry-raw}-results.xml. Classified2/2 and
strict summary pass0.38s: two known regressions reproduced, no failures/skips.
Targets delta619-620; cumulative measurement pending.643 still needs a valid
outside-cuboid auxiliary traversal after reference/retry behavior is repaired.
No full gate/push/new hosted dispatch for these local cases. Prior checkpoint
2d8b8d0 has its single hosted run40074304720; do not duplicate it.

# Residual line audit and supported pre-motion/error cutoffs - 2026-10-24

Branch coverage-batch-74, parent dcd124c2. CORE2e165a1 remains unchanged and clean.
The276-row source/line CSV exactly matches both hosted40068761972 and40070163310
coverage XML sets. Each gap has a disposition and evidence; historical proofs,
provider contracts, unavailable implementations and fixture preconditions remain
separate. No exclusions or invented private states. Two remaining alarm caller
paths have no demonstrated public trigger; this is not a universal dead-code proof.

Four new cases plus one existing-case extension are cumulatively validated:
- Full boot reset during the normal100ms pre-homing report delay: no driver
  wake/pulses/displacement/homed axes, empty planner, $G responds after reset.
  Focused ASan/UBSan0.05s; targets machine_limits269.
- Registered encoder-spindle G76 preparation reset: no first radial move,
  pulses, sync starts or pending cut; spindle/coolant off, position retained.
  Focused ASan/UBSan0.08s; targets motion_control715.
- Full boot delta move between reachable(-250,0,-150)/(250,0,-150) endpoints
  crosses an unreachable interior. Real motors stop nearX=-164.857; finite pose,
  preserved height, motor counters, opposite endpoint and five terminal command
  responses checked. Final ASan/UBSan0.10s; targets delta320-321. Response/error
  policy is separate TODO, not silently-successful geometry blessed by the test.
- Registered two-spindle M5$-1M61/M6 tool callbacks stop both outputs before the
  changer runs; addressed restart preserves independent drivers. ASan/UBSan0.06s.
- Existing VFS size/allocation/retry case adds successful bounded allocating CWD,
  verifies /store/jobs and frees ownership. ASan/UBSan0.09s.
No new defect allowances, CORE changes, shared-fixture or reporting-script edits.
Cumulative4453 ASan/UBSan gate passes179.29s; strict summary4424clean,
2knownSAN,27knownregressions,0failed/skipped. Evidence:
build-asan/residual-audit74-{results.xml,tests.log,summary.log}. Source/pinned
CORE unchanged. No reporting-helper rerun because reporting scripts are unchanged.
This validates the accumulated audit checkpoint, not a measured line increase.

Latest existing hosted40070163310 is completed: allfive jobs green, both source
locks match dcd124c2/CORE2e165a1/filter, allseven coverage stages exit0. Coverage
4449cases:4423clean/26known/0failed/skipped.17480/17756lines98.45%,12730/13834
branch outcomes92.02%; nine more outcomes and identical covered-line set versus
40068761972. Badges and measured inventory now reference this verified report.
Full local gate completed once at the end of the276-line audit; hosted coverage
measurement is the next checkpoint. No per-case coverage profiles were added.

User productivity correction is in AGENTS: no per-case profiles, automatic tiny
batch full gates or CI cadence; accumulate supported work without padding a quota.
Earlier isolated broadcast trace predates that correction and was not repeated.
User decision: G76 X-word main taper stays on TODO; no geometry regression or
allowance while implementation scope remains unresolved. Full coverage goal active.

# Conditional recovery, blocking CRC, rotary return and PWM reset - 2026-10-24

Branch coverage-batch-74, parent0fb0967fc1681c4d4b6aca7ff2c59361533dddeb.
CORE remains clean/latest2e165a1ac4c74be8e68971972c6577775d856b05 after fetch.
PR28 still open/unmerged/frozen a9f355c; do not merge or overlap it.

Seven new cases span four modules:
- ngc_flowctrl: IF/ELSEIF/REPEAT/DO-WHILE expression DivideByZero returns the
  exact error, suppresses body/tail writes, closes/unwinds actual RAM file,
  restores sender, then accepts $G and a fresh IF/assignment/ENDIF plus $G.
  DO body executes exactlyonce. Compatibility0 intentionally latches errors;
  public $G precedes recovery G-code. Four normal cases pass under sanitizers.
- modbus_rtu confirmed defect: no-retry blocking CRC-corrupt response returns
  false and calls one error observer, but code0(NoException) instead of254(CRC).
  Next valid request recovers with expected address/function/data bytes. Correct
  final CRC assertion retained in one exact WILL_FAIL; dated KNOWN_BUGS entry.
  Existing asynchronous CRC and blocking retry controls pass. No sanitizer
  allowance or lockup/data-acceptance claim. Separate undocumented blocking
  callback rx_length0 recorded in TODO, not promoted to a confirmed defect.
- eight_axis: public rotary/wrap settings, actual moveA30/G28.1 save/moveA90.
  G91G28A0 returns60degrees (4800steps); requested G28A10 preserves10forward/
  70back (6400steps). Physical/system/parser end at30, other seven axes stay0.
- multi_spindle: registered PWM driver starts rising, public CMD_RESET requested
  during native ramp; actual reset processing quenches output and calls driver
  reset once. All PWM writes from observed quench onward remain0; optional
  secondary untouched. No invented arrival-time guarantee: one write can precede
  processing of the queued reset. No private flags or spindle-pointer mutations.

Full4449 ASan/UBSan gate passes58.88s; strict report4420clean/2knownSAN/
27knownregressions/0failed/skipped. Evidence build-asan/driver-recovery74-delivery-
{results.xml,tests.log,summary.log}. No CORE/shared-fixture/reporting-script edits;
no redundant unchanged Python-helper rerun. Fresh isolated LLVM branch proofs
retained for conditional errors486/497/542/585, rotary4626/4660 and ramp729/743/815;
no new aggregate percentage inferred from those profiles.

Verified hosted40068761972 allfive jobs green, exact0fb0967/2e165a1/filter locks,
7stages exit0. 17480/17756lines98.45%,12721/13834branches91.95%; +12outcomes vs
40066895627, identical line hit sets/denominators. Raw276lines/1113outcomes remain.
Badges and inventory now reference that report. This successor needs one exact-
head hosted checkpoint. Preserve unrelated ioports phantom M. Continue the full
supported-coverage goal; gates, commits and PR checkpoints are not completion.

# Conditional jobs, deferred offsets and primary-only program end - 2026-10-24

Branch coverage-batch-74, parent51d3a6e55e6070b86526eab5bfed239382c501fa.
CORE clean/latest2e165a1ac4c74be8e68971972c6577775d856b05 after freshfetch.
PR28 remains open/unmerged/frozen a9f355c; do not overlap it or merge.

Seven new cases plus two existing-case improvements span four modules:
- multi_spindle: optional secondary disabled before startup; M2 stops primary
  and restores100% override, next M3 runs nominal4000RPM, M30 stops it again.
  No secondary/auxiliary output calls; modal optional slot staysNULL. Existing
  variable-speed driver fixture reused; on/off-only fixture was inappropriate.
- gcode: T1M6G43 without H defers offsets while waiting, then native sender
  cycle-start acknowledgement applies2/3/4mm. Existing explicit-H control now
  uses public cycle start/realtime instead of directly clearing a parser flag.
- gcode confirmed regression: T0M6G43 selects tool0 after the same acknowledgement
  but leaves prior2/3/4mm offsets, despite a verified zero table entry. G49
  recovery clears them. Correct final assertions retained in one exact WILL_FAIL
  and dated KNOWN_BUGS entry; no sanitizer allowance or physical hazard claim.
  Source4310 stores pending0; completion996 only applies pending values>0.
- ngc_flowctrl: false ELSEIF chains select ELSE/later true branch; native RAM
  file/protocol/stepper emits exactly160 X steps and only chosen parameter writes.
  False outer IF skips nested DO/REPEAT/WHILE/IF bodies then emits80 X steps.
- ngc_flowctrl: condition1/#100 becomes invalid after first iteration; ENDWHILE
  and CONTINUE separately report DivideByZero, skip the remaining file, unwind
  and restore sender $G. Intentional fixture CMD_EXIT is accounted for.
- ioports: existing off-duty case now checks inverted25% idle749ticks plus
  minimum/midpoint/maximum899/499/99ticks for a valid1000tick PWM period.

Full4442 ASan/UBSan gate passes58.76s; strict report4414clean/2knownSAN/
26knownregressions/0failed/skipped. Evidence build-asan/conditional-tool74-delivery-
{results.xml,tests.log,summary.log}. No CORE/shared-fixture/reporting-script edits.
No redundant unchanged Python-helper rerun. Isolated local branch proofs retained
for conditional selection/skips, omitted-H deferral and optional spindle slots;
these do not establish a new aggregate hosted percentage.

Last verified hosted40066895627: allfive jobs green, exact51d3a6e/2e165a1 locks,
7coverage stages exit0;17480/17756lines98.45%,12709/13834branches91.87%.
Gain over40064204492 is10outcomes, identical covered-line sets/denominators.
Badges and gap inventory refreshed to that verified report. This successor needs
one exact-head hosted checkpoint. Preserve unrelated ioports phantom M.
Continue full supported coverage; passing gates/commits are not completion.

# Public workflow recovery batch - 2026-10-24

Branch coverage-batch-74, parent f1879ab83df4cf623a9a4b8a98043ea672e0fa77.
CORE remains clean/latest2e165a1ac4c74be8e68971972c6577775d856b05 after fresh
fetch. PR28 is still open/unmerged at a9f355c; do not merge or overlap it.

Seven new cases plus two existing-case extensions span six modules:
- ngc_expr: malformed named RHS and computed index preserve values and queued
  motion; corrected assignments and following cut execute to160 steps.
- gcode: documented OpenPNP M201.3 drains queued motion before plugin execution,
  preserves claimed axis values without moving them; integer form rejects.
- motion_control: registered probe rejects G38.6 without touching queued motion,
  then valid G38.2 detects actual120-step contact and completes once.
- motion_control: a100mm G5 inflection checks independent Bezier samples/extrema,
  both Y reversals, exact pulse totals and physical/parser endpoint.
- motion_control: inverse-time G80/rapid, rejected G80X2 and F-less G1 retain
  queue/modes; corrected feed command finishes160 steps. Isolated LLVM trace
  confirms both outcomes at gcode.c2415, not an aggregate GCC gain claim.
- lathe_ngc: optional pre-execution hook observes native metric jog while prior
  inch/incremental program modes/feed remain intact; exactly80 steps finish.
- ngc_params: actual percent-delimited RAM file finishes80 steps, reports end,
  closes/restores sender and answers $G with no optional completion observer.
  Isolated trace confirms callback-absent side at gcode.c1324.
- Existing cutter_comp check-mode rejection now includes G40/T2M6 recovery.
  Persistent tool-table G43 covers omitted H with pending/current tool selection.
  These are explicitly check-mode cases, not physical tool-change claims.

Full ASan/UBSan4435-case gate passes60.19s; strict reporting passes. Evidence:
build-asan/public-workflows74-delivery-{results.xml,tests.log,summary.log}.
Known25 expected failures and2 recovering sanitizer cases unchanged; no CORE,
shared fixture, CMake, reporting script or allowance changes. No redundant
unchanged reporting-helper rerun. Valueless integer-L plugin contract remains
in TODO; no invented behavior test. Preserve unrelated ioports phantom M.

Last verified hosted40064204492 is98.45% lines/91.80% branches, source/harness
locks verified, allfivejobs green. Badges/docs refreshed to that report.
This successor needs one hosted exact-head measurement; no new percentage yet.
Continue the full supported-coverage goal; passing this gate is not completion.

# Driver/parser allocation recovery batch - 2026-10-24

Five new cases pass one cumulative ASan/UBSan gate: 4,428/4,428 in 58.84s.
Strict summary: 4,401 clean, two existing recovering sanitizer cases, 25 known
regressions, zero unexpected failures/skips. Artifacts:
build-asan/driver-parser-allocation74-delivery-{build.log,tests.log,results.xml,summary.log}.
Fresh CORE fetch remains clean2e165a1. PR28 stays open/unmerged at frozena9f355c.

Secondary PWM refresh uses the configured pointer retained by the driver's real
config callback, not the identity-less registration descriptor or an active HAL
getter mutation. Range/off value/ramp policy changes and restoration affect only
the secondary slot; actual M3/M5 timing/output and both other drivers are checked.
Grouped plugin slot settings use a valid normalizer/iterator/function-backed
provider; public stores swap driver selections and native selectors independently
route three speeds/directions plus directed/broadcast stop.

M98 prescan rejects exactly one record calloc, propagates OutOfMemory, clears
cached positions while retaining the file/root value, then retries and clears
multiple records through public parser initialization. Named-tool realloc failure
retains sender MSG text and correct tool selection; normal retry reports the
proper name before the driver's change callback. Exact target wrappers reuse
existing malloc/calloc/realloc helpers.

Synchronized M62 output-node malloc failure incorrectly returns Status_OK.
Correct rejection assertion is retained after prior-cut ownership/no-premature-
activity/retry/exact160-step controls. One exact WILL_FAIL and dated KNOWN_BUGS
entry describe ignored add_output_command return and cleanup. No error enum,
rollback requirement, physical hazard or sanitizer suppression invented.

TODO/COVERAGE_GAPS record bounded literal-local getter and dominated Modbus
response ternary outcomes; reachable compound-condition failures remain in scope.
No fabricated getters, source changes or exclusions. No helper-script changes.

Run40062567963 is fully green at exactb29713965f96eebb0a754b83b2f864534c0a85c4;
both locks, CORE/filter and seven coverage stages verified. Badges/current raw
inventory now show 17,480/17,756 lines98.45%,12,693/13,834 outcomes91.75%.
276 missing lines/1,141 missing outcomes. Exact covered-line sets are unchanged
against40061404353, with six more outcomes (spindle_control+1,stream+5).
4,423 coverage cases:4,400 clean,23 known,zero unexpected failures/skips.
This new batch requires its own hosted measurement; the full goal is incomplete.

# Laser door policy and stream/startup batch - 2026-10-24

Five new cases on coverage-batch-74 pass one cumulative ASan/UBSan gate:
4,423/4,423 in 59.06s. Strict summary: 4,397 clean, two existing recovering
sanitizer cases, 24 documented regressions, zero unexpected failures/skips.
Artifacts: build-asan/laser-stream-startup74-delivery-{build.log,tests.log,
results.xml,summary.log}. No CORE edits or source exclusions.

Two M3/M4 laser jobs with public $63=2 reproduce failed enable restoration after
real safety-door stop/close/resume. All 1,600 X steps finish, but driver enable
stays off. Matched $63=3 controls pass. Correct final assertions remain; only the
two exact cases have WILL_FAIL/known_bug. Dated KNOWN_BUGS entry records raw
2-pass/2-fail evidence, driver output, source cause and cleanup. No diagnostic
suppression or premature-enable fix. Existing helper defaults and safety checks
remain; it now accepts a public hold-policy argument.

Three ordinary stream scenarios pass: base USB without optional connection
status retains output through network handoff/reconnect; USB and UART instance0
remain distinct; Bluetooth/WebSocket clients connected during actual driver_init
receive no premature welcome, then one startup welcome and successful $G reply.
No fabricated startup flags or registered-provider identity mutation.

Isolated no-sanitizer source proof: laser-stream-branch-proof74/{proof.json,
stream-conditions.json}. Successful stream/boot cases and exact laser failures
confirmed. LLVM places USB/UART condition branches at265-266; lookup-loop264's
exhaustion outcome remains absent. Do not infer portable aggregate branch counts.

Prior run40061404353 is fully green at exact4a252c70e769cbdd71cd7be68b8dbd987f548c79:
both source locks, CORE2e165a1/filter and seven coverage stages verified.
17,480/17,756 lines (98.45%), 12,687/13,834 outcomes (91.71%); 276 missing lines
and 1,147 missing outcomes. Against40060050917, identical covered-line sets and
seven more outcomes (motion_control+1, report+2, spindle_control+4).
4,418 coverage cases: 4,397 clean, 21 known, zero unexpected failures/skips.
Badges and gap inventory now reference that verified checkpoint. This new batch
requires its own hosted measurement; passing local tests are not goal completion.

# Three-spindle/probe/help batch cumulative delivery - 2026-10-24

Three new cases and two existing-case extensions pass one full ASan/UBSan gate:
4,418/4,418 in58.53s. Strict classification:4,394 clean,2 known recovering
sanitizer cases,22 documented expected regressions,0 unexpected failures/skips.
Added three-active-spindle configuration; public drivers exercise every outcome
of the ramp-list traversal. Extended allocation recovery also rejects the next
ramp allocation during an actual override, verifies immediate correct PWM/no
stale tasks, then successful independent primary/secondary ramps on retry.
Public probe failure/$X/retry and optional plugin help providers are included.
No CORE edits or new allowances. Artifacts:
build-asan/three-spindle-probe-help74-delivery-{build.log,tests.log,results.xml,summary.log}.
Keep the measured badges at fully green2f0b74b/run40060050917 until this batch
has its own exact-source hosted coverage and compiler result.

# Fully verified2f0b74b coverage checkpoint - 2026-10-24

Run40060050917 completed success; all five source/GCC/Clang/coverage/Results
summary jobs passed. Both exact harness/core/filter locks and seven successful
coverage stages were verified.17,480/17,756 lines98.45%,12,680/13,834 branch
outcomes91.66%;276 missing lines/1,154 missing outcomes. Compared to40056914079,
covered-line sets are identical and six additional outcomes are covered (four
report outcomes, two grbllib outcomes). Coverage4,415 cases:4,394 clean,21 known,
zero unexpected failures/skips. Badges, current raw inventory and measured
KNOWN_BUGS paragraph now point to this fully green checkpoint.
Local three-spindle, no-observer probe recovery and optional help-provider work
remains separate. No completion claim or CORE/source exclusion changes.

# Completed coverage job at2f0b74b; compiler validation pending - 2026-10-24

Run40060050917 coverage and GCC jobs pass; Clang remains running at inspection.
Both artifact locks match harness2f0b74b630cb7b1b4e27e4f6a00c0e15c7864061,
CORE2e165a1 and the core source filter. Exactly seven coverage stages exit0.
Measured17,480/17,756 lines98.45%,12,680/13,834 outcomes91.66%: +6 outcomes
with identical covered-line sets against40056914079.4,415 cases,4,394 clean,
21 known,0 failed/skipped. Keep success badges at the last fully green run
until all jobs complete; this is a completed coverage job, not all-check success.

Local next-batch proof: three-spindle-branch-proof74/proof.json shows all six
outcomes at spindle_control.c594 exercised by registered drivers, including list
traversal and context reuse. ASan/UBSan and isolated no-sanitizer case pass.
No claim of aggregate next-batch gain until its own hosted report exists.

# Three simultaneous PWM spindle ramp contexts - 2026-10-24

Added supported N_SPINDLE=3/N_SYS_SPINDLE=3 host configuration and one registered
public-driver scenario. Three PWM drivers map through registered slot settings;
M3/M4 start distinct speeds/directions. Two rounds of independent overrides reach
each bounded RPM target with exact driver PWM, retain programmed RPM/direction,
and stop scheduling updates after completion. M5$-1 stops all three. This reaches
the native ramp-list traversal beyond the existing two-active-slot fixture.
Focused ASan/UBSan passes0.11s. Initial exact PWM expectation used independently
rounded RPM; corrected comparison to CORE's returned target, separately bounded
within0.01 RPM of the requested percentage, preserving exact PWM assertions.
No defect, CORE edit or exception. README lists the added supported configuration.
CMake adds one host target/module, reusing existing driver registration utilities.
Next cumulative gate must include this configuration and local probe/help cases.

# Default probe observer alarm recovery - 2026-10-24

Added one public probe-motion scenario with no plugin completion observer.
Initial contact raises Alarm_ProbeFailInitial, disarms the probe and emits no
motor steps. After releasing the modeled contact, public $X clears the alarm;
a retry detects contact at40 steps, completes without observer calls and leaves
no queued move or armed probe. Focused ASan/UBSan passes0.05s. This targets the
verified missing absent-observer outcome at motion_control.c1056 without changing
CORE or suppressing a failure. Local next-batch work; no full gate/CI repeat.

# Optional plugin help providers - 2026-10-24

One new registered scenario puts a valid settings-only plugin (no group table)
between two providers with help groups. Lookup reaches the later provider;
unknown-topic lookup exhausts the chain and emits only N/A. Extended the existing
Commands topic case through installed/absent/reinstalled optional reporter, with
exact output and callback counts. Focused ASan/UBSan passes0.07s/0.06s.
Targets report.c396 optional-group guard and382 optional-command callback.
No CORE edits or new exceptions. These local successors are outside hosted
run40060050917; keep accumulating useful cases before another full gate/dispatch.

# Delivered report branches locally confirmed - 2026-10-24

Pushed 2f0b74b630cb7b1b4e27e4f6a00c0e15c7864061; exact-head hosted
run40060050917 is active (source job succeeded; compiler/coverage jobs running
at inspection). No duplicate dispatch. PR28 is open, unmerged and unchanged at
a9f355c35717006f497754d1acc421cf5b141670. Fresh CORE fetch remains2e165a1.
Isolated no-sanitizer LLVM profiles from the three delivered report cases show
both outcomes at report.c901 (sender connection),970 (homing init lock),1044
(probe selector) and1049 (disconnect input). Proof:
build-asan/public-report-branch-proof74/proof.json. These confirm target paths;
do not convert local branch IDs into a hosted aggregate percentage.

# Public startup/report batch cumulative gate - 2026-10-24

One new optional-release boot scenario and seven existing-case extensions are
ready for delivery on coverage-batch-74. Full ASan/UBSan: 4,415/4,415 pass in
58.78s; strict summary passes with existing 22 known failures and two recovering
sanitizer cases, zero unexpected failures/skips. No CORE or shared fixture edits,
no new exceptions. Artifacts: build-asan/public-startup-reports74-delivery-*
(build/test logs, results XML, strict summary). Verified coverage badges remain
pinned to fully green bb5a6f8/run40056914079 until this batch is measured.

# Sender reconnect and basic-probe capability reports - 2026-10-24

Extended two existing reporting scenarios. Startup-command output is suppressed
while disconnected; reconnect reports the correct error and the following success.
Probe capability reports now alternate selectable three-probe and ordinary
single-probe drivers, checking absent selector/disconnect tokens without stale
capabilities and retaining NOPROBE absence for a working basic probe. Focused
ASan/UBSan 2/2 passed (0.31s total). These target verified missing conditions at
report.c901/1044/1049; aggregate gains await the next cumulative hosted batch.
No CORE changes, new exceptions or duplicate case registrations.

# Live public automatic-report controls - 2026-10-24

Three existing timer scenarios now use public settings storage and realtime
sender toggle commands instead of assigning report interval/enable fields.
The interval-change and disabled-chain checks run in the live boot read observer,
before NVS shutdown, and retain deadline/rearm/no-report assertions plus a
successful following $G query and normal driver release. Pause/resume uses the
sender toggle in both directions. Focused ASan/UBSan 3/3 passed (0.35s total).
Initial post-shutdown persistence attempts hit freed host NVS; corrected the test
lifecycle, no CORE defect or allowance claimed. No shared fixture changes.

# Homing capability follows public startup-lock changes - 2026-10-24

Extended the existing enabled-homing report case through public $22 values
1 -> 5 -> 1 and public first-phase XYZ homing configuration. HOME remains
advertised throughout; the legacy OPT L flag disappears with initialization
lock and returns when unlocked. Assertions inspect only the OPT flag field.
Focused ASan/UBSan case passed (0.05s). No CORE edits or new exceptions.
This local successor is not included in the verified 98.45%/91.61% report.

# Verifiedbb5a6f8; optional callbacks and resolved startup observation - 2026-10-24

Hosted40056914079 passes all five jobs at exactbb5a6f8cccfb70daec25fab3f6b443bda44f111b.
Both locks match CORE2e165a1 and the core filter; seven coverage stages exit0.
Measured17,480/17,756 lines98.45%,12,674/13,834 outcomes91.61%: net+14 against
40054135733 with identical covered-line set.4,414 hosted cases:4,393 clean,
21 known,0 failed/skipped. Badges/measurement/gap table refreshed locally.

Local successor: one new missing-release-handler boot scenario and one extended
failed-init case. No release handler means native Ctrl-C restarts the parser;
second $G works, one setup and no release calls, saved $10 survives. A bounded
observer ends that intentionally persistent controller after assertions.
Failed init without step-enable retains original alarm/setup/exit expectations.
Focused sanitizer cases pass0.06/0.07s; grouped non-sanitized2/2 passes0.11s.
optional-release-enable-proof74/proof.json shows both outcomes at grbllib194/513.
Last full gate remains4,414;4,415 registered. No tiny new gate/CI or allowance.

The separate failed-init $G stall is resolved as expected policy, not a bug.
Bundled LLDB attached to the spawned query process shows the intentional
permanent task_execute_on_startup fault loop at grbllib882, entered at the
protocol realtime checkpoint before command dispatch. Generic $G allow_blocking
does not bypass failed startup. Incorrect query-success proposal removed; TODO
now records source/runtime evidence. Temporary probes restored and passing
registered case rebuilt/verified. No CORE edit, unknown timeout acceptance or
unsupported IRQ assumption. Existing permanent-fault observers cover this state.

New native ordering audit accounts for raw stepper1093: true fast-cancel flag
writer leaves pl_block NULL, and the next preparation pass returns early or
clears the flag while loading before the guard. No IRQ caller reenters native
preparation. Existing real cancellation checks retained; no injected state.
See TODO/COVERAGE_GAPS. No measured percentage or denominator was changed.

Continue independent supported gaps on74. Preserve unrelated byte-identical
legacy-description status and frozen/open PR28; never merge. Goal active.

# Native callbacks, sender reports and U/V/W reversals - 2026-10-24

Branch coverage-batch-74 has five new scenarios and five existing-case extensions.
Full ASan/UBSan4,414-case delivery gate passes60.65s; strict summary:4,390 clean,
2 recovering known-sanitizer cases,22 reproduced known regressions,0 failed/skipped.
No new allowances, shared fixture edits or CORE changes. Fresh origin/upstream/
CORE fetch confirms clean/latest2e165a1ac4c74be8e68971972c6577775d856b05.

New supported workflows:
- Native unknown G65 without an external fallback rejects while preserving
  root#24=99 and queued80-pulse motion; built-in P3 then succeeds.
- Real boot captures a driver macro before parser initialization. Custom N42/P100
  dispatches once; built-in P3 stays native. Caller scope and $G query recover.
  Ordinary operation comment is accepted without a prior optional observer.
- ABORT message allocation fails exactly once; the exception still reports.
  $G clears COMPATIBILITY_LEVEL0's error latch before retry. Retry prints one
  message and the same exception; a final query works without an alarm.
- Normal0x80 status queries after M8/M9 flush native coolant-change flags and
  report override/accessory state in order; final driver/parser coolant is off.
- Driver release callback returns true once for another parser pass, then false
  to exit. Two welcome/query passes preserve $10=64, reset G91/F200 to G90/F0,
  and require only one hardware setup.

Extensions retain existing assertions: both M72 lathe scenarios check emitted
G7/G8; tool-table reports cover random ATC's zero and negative entries while
retaining names,pockets and pacing; active base UART refuses close/reclaim and
keeps its handler. U/V/W mapping now executes a reversing job with independent
physical minima -80/-160/-240,320/640/960 pulses and all final coordinates0;
XYZ never move. Exact negative W update is reached through ordinary G-code.

Gate artifacts: build-asan/batch74-native-observers-delivery-{build.log,tests.log,
results.xml,summary.log}. Focused cases and grouped profiles passed during
construction. Source proofs: native-macro-chain-proof74,report-ownership-proof74,
native-coolant-status-proof74,reversal-restart-proof74 under build-asan. Profiles
are separated by host variant. LLVM emits no branch rows on G7/G8 or W direction;
those outcomes remain runtime assertions. No local aggregate gain is claimed.

Source audits in TODO/COVERAGE_GAPS retain raw branches: registered setting
owners require save callbacks; imperial formatter's nine native selector calls
all pass position=true, while scaling explicitly uses metric(false).

Latest fully verified hosted baseline40054135733 at8a8bea3 remains98.45% lines /
91.51% branches,17,480/17,756 and12,660/13,834. All five jobs and both source locks
verified; seven coverage stages exit0. This successor is not yet measured.
Deliver one cumulative checkpoint and keep working; no repeated full gate or
unchanged helper runs. Preserve unrelated legacy-description status and frozen
PR28; do not create an overlapping master PR or merge anything. Goal active.

# Cumulative controller workflow gate - 2026-10-24

Full ASan/UBSan4,409-case gate passes58.13s; strict summary:4,385 clean,
2 recovering known-sanitizer cases,22 reproduced known regressions,0 failures
or skips. Source remains clean2e165a1 after fresh CORE fetch. Local branch74
contains six new cases plus three existing-case extensions. No repeated full gate.

Artifacts: build-asan/batch74-controller-workflows-delivery-{build.log,tests.log,
results.xml,summary.log}. Separate modal-drilling profile proves both call-level
outcomes at gcode.c1534 and4780, with local plunge/retract suppression at4764:
build-asan/modal-drilling-proof74/proof.json. Existing560/800-pulse whole-job
checks were strengthened with all five actual hole positions and retract endpoints;
that affected case passes its final focused sanitizer/strict check in0.06s. No fixture/CORE edit.
Hosted aggregate remains98.45% lines/91.46% branches at8b9dea0 until new exact-head
measurement. Prepare one cumulative delivery and preserve frozen PR28.

# Modal drilling through actual stepper output - 2026-10-24

New motion-control scenario executes a synchronous registered drilling macro with
M73 local modal restoration, plunge and retract. Two G66-triggered positions and
three G66.1 argument-driven positions finish with exactly five calls,560 X pulses,
800 Z pulses, Z back at0 and caller X7. Local G0/G1 moves do not recursively call
the parent modal macro; G67 stops future calls and the caller remains absolute.
G66.1 uses declared X block arguments and macro-side positioning; the initial
undeclared-X setup rejected correctly and was repaired without a CORE allowance.
Focused ASan/UBSan passes1/1 in0.07s. No CORE or shared fixture change.

Current accumulated batch: six new scenarios plus three extensions across I/O,
settings migration, USB reconnect, named-file errors and actual drilling motion.
The32-channel diagnostic retains exact case/source/line/index/type scope while
accepting GCC's typedef spacing and Clang's alias rendering. Seven classifier
self-checks accept these renderings and reject wrong index,type,line or case.
Preparing one cumulative sanitizer/strict gate; no new hosted run dispatched yet.

# Accumulated workflow source proof - 2026-10-24

Built all eight current successor scenarios together in the existing non-sanitized
coverage build, including the supported32-channel variant. Per-variant isolated
CTest groups pass6/6 standard,1/1 full-bank and1/1 long-name. The standard group
includes the one documented expected metadata regression. Separate profile
prefixes prevent cross-configuration counter mixing.

Evidence: build-asan/successor-workflows-proof74/proof.json and each variant's
results.xml/tests.log. Profiles show remap rejection and identical-remap arms,
PWM frequency and16-bit-period limits, recent-build migration bypasses and both
USB startup-warning queue arms. The long-name warning's abbreviated suffix is
verified by its assertion; this compiler emits no branch rows on that expression.
No aggregate coverage gain is inferred from these local profiles. Full sanitizer
suite and one hosted cumulative checkpoint remain deferred while the batch grows.

# Maximum-length named-file error recovery - 2026-10-24

Added one real embedded-file protocol scenario in the existing80-character name
configuration. A complete matching SUB/ENDSUB file is prescanned before its body
runs; G999 then reports the unsupported-command error. The body receives local
argument12, the caller regains99, and both remaining body/caller assignments
are suppressed. The warning abbreviates its maximum-length filename and the
normal sender $G query still completes. Focused ASan/UBSan1/1 passes0.07s;
no new allowance, fixture edit or CORE edit. Targets ngc_flowctrl.c442's existing
bounded warning branch. Successor cumulative validation/hosted measurement pending.

# Verified hosted checkpoint - 2026-10-24

Run40050621444 at8b9dea07341282c2e0e8cf35c2171e07ac394e45 completed all five
jobs successfully. Both artifact locks match CORE2e165a1 and the core filter;
exactly seven coverage stages exit0. Measured17,480/17,756 lines98.45% and
12,652/13,834 branch outcomes91.46%, eight more outcomes than40049122187.
4,403 cases:4,383 clean,20 known,0 failed/skipped. Successor local work is not
included. Isolated32-channel and ownership-metadata classifications subsequently
pass strict reporting:one recovering sanitizer case,one expected regression.
Full cumulative successor validation is pending; CORE remains untouched.

# Supported full I/O bank and ownership metadata - 2026-10-24

Added the supported 32-input/32-output host variant. Public registration,
P31 naming, input sampling, output routing and free-port queries retain correct
assertions. Registration reproduces signed shift31 at ioports.c994/1007;
free-port enumeration reproduces map[32] at696. Exact recovering diagnostics
are scoped to this case; no WILL_FAIL or CORE edits.

Isolated ownership metadata using the ordinary two-output fixture: claiming
physical1 remains exclusive and routes both outputs correctly, but a pin-info
lookup clears its claimed bit. Correct final assertion has one narrow WILL_FAIL
and dated KNOWN_BUGS entry. The two-output cached free count remains correct;
no lost exclusivity or wrong output is claimed. Raw focused evidence is
batch74-io32-isolation-raw-results.xml. Full cumulative validation is pending.

# USB reconnect repeats failed-startup diagnostic without replaying warnings - 2026-10-24

Extended existing usb_connection_reports_failed_selftest_then_retained_startup_warnings.
Original wrong-device/deasserted events,50ms delay, warning FIFO and discarded
plugin task checks remain. After first successful diagnostic, real public USB
line-state disconnect/reconnect queues a second delayed POS-failure message.
Both retained warnings appear exactly once; controller remains selftest-alarmed,
not driver-started, with no plugin callback execution or driver release.
Targets grbllib.c209 empty retained-warning queue on a normal reconnect rather
than manually clearing private startup tasks. Focused ASan/UBSan1/1 passes0.07s.
No CORE/shared fixture edit, allowance or additional case-count padding.
Current successor: two new scenarios plus three related workflow extensions
across I/O, settings migration and startup diagnostics. Cumulative gate pending.

# Recent-build settings upgrade preserves custom pendant transport - 2026-10-24

Added settings.recent_build_upgrade_preserves_custom_pendant_baud_and_spindle_values.
Registered pendant selects460800 via public baud setting. Persisted260904 build
reload upgrades version to current and saves it, keeps custom baud3 and notifies
actual driver at460800. Existing millisecond coolant delay50 and distinct spindle/
PWM tolerances1/4.5 remain unchanged, rather than reapplying250102 conversions.
Live NVS read confirms current build/baud; second settings_init retains values
and correct driver baud. Targets settings.c3858/3883 later-build migration arms
through valid saved schema and ordinary initialization. Focused ASan/UBSan1/1
passes0.07s. No shared fixture/CORE edits or allowances. Two new cases plus two
extensions now accumulate across I/O and upgrade workflows; full gate pending.

# Remap reapplication/ownership and timer period limits retain normal routing - 2026-10-24

Extended existing output_remap_swaps_physical_pins: repeat the identical public
remap and retain original physical routes; claim physical0 then reject remapping
onto its claimed destination; owned and remaining outputs still toggle physical0/
physical1 correctly, input bank unchanged. Targets ioports.c1038 no-op and1036
claimed-destination rejection. Focused ASan/UBSan1/1 passes0.07s.

Extended existing PWM frequency rejection/retry case with10Hz at1MHz, requiring
100000ticks beyond UINT16_MAX; it correctly rejects.50Hz accepts20000ticks and
exact duty conversion, then original1kHz retry checks remain. Targets ioports.c1154
long-period rejection, preserving practical supported-frequency controls and the
maintainer-confirmed rejection contract. Focused sanitizer1/1 passes0.04s.
No new case-count padding, CORE edits or allowances. Current successor has one
new mode-select scenario plus two extensions; keep batching independent work.

# MPG mode-select assignment reserves only its actual input - 2026-10-24

Added ioports.assigned_mpg_select_reserves_input_without_neighbor_reroute.
Public ioport_set_function assigns real Input_MPGSelect through existing driver
assignment fixture. Driver called once, function recorded, no unrelated control
signal capability added. Pin0 stops being generally claimable; pin1 remains
available, claims successfully and its immediate sample routes to physical1.
Output bank remains untouched. Targets ioports.c415 legitimate non-control,
non-probe/motor-fault input assignment rather than invalid function values.
Focused ASan/UBSan passes1/1 in0.05s. No shared fixture/CORE edits or allowance.
First local successor after pushed8b9dea0; hosted40050621444 covers the prior
substantial group. Continue independent modules without isolated full gate/run.

# Reporting/resource/I/O cumulative gate passed - 2026-10-24

Five new cases plus one retained-assertion extension pass one full4403-case
ASan/UBSan gate60.42s after rebuilding all shared spindle-fixture consumers.
Strict summary:4381clean/1exact recovering UBSan/21known regressions/0unexpected
failed/skipped. Correct ramp cancellation assertion remains one exact known bug;
no broad sanitizer allowance. No unchanged reporting helper reruns.
Fresh CORE fetch remains clean2e165a1. Priord8c3986 run40049122187 all five jobs
passed; exact locks/seven stages0 support98.45%lines/91.40%branches. Badges and
measured paragraph updated only after terminal success. New coverage pending.
PR28 remains open/unmerged at frozena9f355c; do not merge or create overlapping
master PR. Deliver substantial group on existing74 with one guarded hosted run;
continue independent coverage. No completion claim from this passing checkpoint.

# Configuration claim retry extended; grouped profiles verify current targets - 2026-10-24

Existing ioports.driver_claim_failure_preserves_ownership_and_allows_routed_retry
now routes its failed claim and successful retry through ioports_cfg.claim.
All original driver-count, unchanged ownership/description, mapped pin and output
assertions retained. Focused sanitizer1/1 passes0.06s, no new quota case.

Built all five new workflows plus extension together for isolated profiles,
separated by actual core variant. Ordinary cases return0; documented secondary
start defect returns1 at the exact retained target assertion. Proof retained at
build-asan/reporting-io-spindle-proof74/{proof.json,host_core,host_core_multi_spindle}.
Observed targets: broadcast285 suppression and ordinary delivery; single-port518
termination; configuration531 driver claim failure and retry; secondary enable192
failure/success; ramp596 allocation failure and712 startup fallback. Override627
allocation-failure arm is NOT exercised and remains unclaimed. No aggregate
percentage inferred from these local profiles or cross-compiler branch IDs.
No CORE edits/new allowances. Cumulative shared-fixture gate remains pending.

# Single-relay configuration searches stop at zero and retain ownership - 2026-10-24

Added ioports.single_output_configuration_stops_search_and_restores_named_relay.
Real registered one-output bank produces n_ports1/port_max0. Initial search finds0;
next-from0 stops unassigned rather than wrapping. A saved relay description still
finds0 at that boundary; claim succeeds, second claimant rejects without output,
and original owner's on/off commands reach physical pin0. No input bank exists.
Targets ioports.c518 single-port termination arm through actual registered count.
Focused ASan/UBSan passes1/1 in0.05s. Post-claim search expectation was corrected:
ioport_find_free explicitly permits claimed-port lookup; exclusivity is tested
via claim rejection instead. No invented defect/allowance or CORE change.
Five local successor workflows now span reporting, spindle recovery/resources,
a confirmed ordinary ramp defect and I/O configuration. Cumulative gate pending.

# d8c3986 coverage gains verified while compiler jobs run - 2026-10-24

Run40049122187 completed coverage job, both exact harness/CORE2e165a1/filter
locks verified, exactly seven stages0.4398hosted:4379clean/19known/0failed/skips.
17480/17756lines98.45%,12644/13834outcomes91.40%; +8outcomes against7d0dff6,
identical covered-line set and denominator. Updated measured gap inventory to
276lines/1190outcomes with per-source counts. Source passed; GCC/Clang still
in_progress at actual API inspection, so prior successful badges remain.
Four local successor cases (including new correct ramp-cancellation regression)
are not in this measurement. No duplicate workflow or completion claim.

# Confirmed secondary start cancels primary's pending override ramp - 2026-10-24

Registered normal PWM primary runs6000; public120% override advances to observed
intermediate PWM660. Ordinary secondary M3S8000 then leaves primary660 instead
of computed719 after ten deadlines, although primary target state remains120%/
about7200. Later125% override recovers correctly and secondary stays8000.
No race/saturation/private pointer mutation or measured shaft-speed claim.
Source spindle_ramp's wildcard task_delete removes the first matching task,
which belongs to primary. Correct captured-target assertion remains after
passing recovery controls. Raw sanitizer0.07s failure has no diagnostic.
Dated KNOWN_BUGS cause/repair/cleanup entry plus one exact WILL_FAIL/known_bug.
Classified focused group/strict summary:2clean/1known/0failed/skipped,0.17s;
retarget and stop isolation remain passing. No CORE/sanitizer allowance changes.
Expected regressions now21 on Windows plus unchanged1recovering UBSan.
Four local scenarios continue independently; confirmed defects are not blockers.

# Secondary PWM ramp allocation failure falls back and later ramps recover - 2026-10-24

Added multi_spindle.secondary_ramp_allocation_failure_applies_output_and_allows_override_retry.
Two precomputed/registered normal PWM drivers start through public G-code. One
scoped heap rejection occurs only during secondary M3S8000; exactly one allocation
fails. Command succeeds with requested secondary output, primary6000 output-call
count unchanged. After allocation resumes, independent primary120%/secondary80%
overrides both ramp through multiple outputs to7200/6400 and stop scheduling
updates after completion. No artificial scheduler fill, private ramp mutation or
registered-pointer edits. Targets spindle_control.c596 allocation failure and
normal startup fallback before successful ramp allocation retry.
Focused ASan/UBSan passes1/1 in0.06s. Exact case linker wrapping reuses existing
tracked allocation fixture; no new helper/library or allowance. Three local
successor scenarios now accumulate; broad shared-fixture rebuild stays pending
until the next substantial cumulative gate. CORE remains untouched.

# Failed secondary initialization leaves slot free and primary output intact - 2026-10-24

Added multi_spindle.failed_secondary_configuration_leaves_slot_free_and_primary_running.
Real registered driver config reads simulated hardware availability, without
mutating any registered pointer. Primary M3S3000 remains running and receives
no extra output call when secondary enable fails. Slot1 stays disabled/NULL.
After hardware recovery the same public enable returns slot1; M4S4200$1 and
M5$1 affect only secondary, preserving primary3000 and its output-call count.
Targets spindle_control.c192 failed activation of a free slot. Fixture's default
availability remains true. New case plus independent-state and slot-capacity
controls pass focused ASan/UBSan3/3 in0.15s. Full affected-module rebuild remains
part of next cumulative gate; do not claim full successor validation yet.
No CORE edits or allowances. Two local successor workflows now span reporting
and spindle recovery while hosted40049122187 covers the delivered prior batch.

# Reboot-configured pendant auto reports remain independent of broadcasts - 2026-10-24

Added boot.pendant_autoreports_continue_while_primary_broadcasts_skip_pendant.
Registers actual primary/pendant streams before boot, applies public703=100 in
setup, and lets native startup initialize mpg_auto_reporting. Two scheduled
pendant idle reports arrive through foreground timers. A normal write_all
broadcast reaches primary output but leaves pendant buffer unchanged; primary
keeps input ownership, no takeover/errors/alarm. No internal report flag forced.
Targets stream.c285's configured-MPG broadcast exclusion while preserving its
own periodic-report positive control. Focused ASan/UBSan passes1/1 in0.06s.
No CORE/shared fixture edit or new exception. First local successor after
pushedd8c3986; hosted40049122187 covers the prior six-workflow group only.
Continue supported cross-module work rather than another small full gate/run.

# Reset/handover cumulative gate passed; prior checkpoint fully green - 2026-10-24

Six new workflows pass the one full4398-case ASan/UBSan gate in58.36s.
Strict summary:4377clean/1exact recovering UBSan/20known regressions/0unexpected
failures/skips. New null-console restoration regression keeps correct assertions
and one exact expected failure; no sanitizer allowance. Shared PWM fixture's
three controls also passed focused. Fresh CORE fetch remains clean2e165a1.
Prior7d0dff6 run40047406632 all five jobs completed success; verified source/filter
locks and seven stages0 support98.45%lines/91.34%branches. Badges and measured
paragraph now point to that fully green report. New source coverage is pending.
Deliver the six-workflow group on existing74 with one exact-source hosted run;
no merge, completion claim or per-case hosted dispatch. Continue next batch.

# Selected VFD boots normally when unused PWM configuration fails - 2026-10-24

Added boot_multi_spindle.vfd_default_boot_continues_when_unused_pwm_configuration_fails.
Existing mixed-driver fixture now supports a genuine driver config false result.
Unused PWM is configured with saved range but receives no state/output call on
failure; selected VFD still configures, remains default, emits normal off output
and accepts $G with valid started/no-alarm startup. Both prior saved/locked-range
success controls remain unchanged by default. Three affected ASan/UBSan cases
pass3/3 in0.18s. Targets spindle_control.c63 failed unselected-PWM init arm.
No CORE edits or new allowance. Small shared fixture change verified against
all its three consumers. Six successor workflows ready for one cumulative gate.

# Confirmed null-console pendant release restoration defect - 2026-10-24

Public network-only base -> network connect/disconnect -> registered serial
pendant takeover/release reproduces success with sys.mpg_mode cleared but all
five restoration observations false: reader/writer/stream-mode/RX/handler.
Normal network reconnection/output succeeds before the final correct restoration
assertions fail. Raw ASan/UBSan failure0.06s has no sanitizer diagnostic.
Source stream.c847 treats a valid saved null-console type as no backup and skips
restoration. Dated KNOWN_BUGS entry includes bounded impact, source, repair and
cleanup guidance. One exact WILL_FAIL/known_bug retains all assertions; focused
classified gate/strict summary passes1known/0unexpected/0skipped in0.05s.
No CORE change, broad allowance or motion hazard claim. Expected regressions
now20 on Windows, plus unchanged1recovering UBSan. Five local successor cases
continue independently; this confirmed defect is not a blocker or completion.

# Reset/pendant group isolated profiles verify intended source paths - 2026-10-24

Extended active-pendant boot scenario with a repeated public enable(true) while
already active: returns false, preserves live read/handler/RX ownership, then
normal Ctrl-X/$G still succeeds. Focused sanitizer passes1/1 in0.06s.
Built and ran all four local scenarios together into one fresh isolated GCOV
prefix. Proof at build-asan/reset-pendant-native-proof74/{proof.json,*.gcov}.
ATC496 executes both arms; unlock-policy502 reaches the disabled-requirement
short circuit; pendant716 reaches active-cycle input; enable823 reaches the
unchanged-mode early return. Native active-MPG506 line executes but this Windows
compiler emits no branch rows there; do not invent cross-compiler branch gain.
Initial profile lookup used grbllib.c rather than its existing task_host.c wrapper;
corrected collector read already-generated data, no rerun or source mutation.
Aggregate gain remains pending a substantial successor gate/report. No new
exceptions, shared fixture edits, duplicate hosted runs or completion claim.

# Pendant start buttons during a real running cut preserve exact endpoint - 2026-10-24

Added boot.pendant_cycle_start_during_running_cut_preserves_motion_and_start_report.
Normal serial G1X2F100 drives actual stepper pulses. After8 pulses, registered
passive pendant handler receives modern and legacy cycle-start commands while
native state is CYCLE and a real planner block exists. Both queue normal start
without idle-start report flag or input takeover. Original cut finishes exactly
160 X pulses/steps, no Y/Z motion, one expected command ack, no alarm/errors.
Targets stream.c716 nonidle arm (prior report5/6), without forced controller
state or a fake suspended job. Focused ASan/UBSan passes1/1 in0.07s.
No CORE/shared fixture edits or allowances. Four local workflows now accumulate;
no per-module full gate or hosted dispatch. Full supported goal remains active.

# 7d0dff6 coverage gains verified; compiler jobs still active - 2026-10-24

Run40047406632 coverage job success, exact harness/CORE2e165a1/filter locks in
both artifacts, exactly seven stages0.4392hosted:4374clean/18known/0failed/skips.
17480/17756lines98.45%,12636/13834outcomes91.34%; +9outcomes againsted8dc71,
identical covered-line set/no lost lines. Measured system175/365/389, rotary306,
spindle101/539 and persistent tool235 now fully covered; pendant716 rises4/6->5/6.
Updated raw inventory276lines/1198outcomes and per-source counts. Source passed;
GCC/Clang in_progress at API inspection, so retain previous all-green badges.
Three new local reset scenarios target other startup branches outside this report.
No duplicate run or completion claim. Existing ATC driver-error case already
covers failed M6 preserving current tool; do not duplicate it for case count.

# Released E-stop reset honors disabled unlock requirement - 2026-10-24

Added boot.cleared_estop_reset_without_unlock_requirement_accepts_sender_commands.
Public Setting_UnlockAfterEStop484=0 is explicitly documented in settings.c2698
as disabling the requirement for $X after reset of a cleared E-stop. Initial
hardware E-stop raises real E-stop state; release then Ctrl-X returns idle with
no alarm, G91/$G succeed without $X, and all positions remain0. The opposite
require-unlock case remains unchanged. Targets grbllib.c502 policy short-circuit.
Focused ASan/UBSan passes1/1 in0.06s. Initial inverse-name interpretation was
wrong and corrected against the description/config.h contract, not documented
as a defect or given WILL_FAIL. No CORE/shared fixture edits or allowances.
Three local successor workflows now accumulate while prior hosted batch runs.

# Active pendant survives real Ctrl-X and receives full reset status - 2026-10-24

Added boot.active_pendant_retains_control_and_full_status_after_warm_reset.
Driver registers real serial pendant plus handlers; public stream_mpg_enable
performs takeover before Ctrl-X. No internal mpg_mode/state assignment. After
reset, pendant retains input, realtime handler and enabled RX; it receives $G
and full status including MPG1/WCS/tool/firmware fields with no errors/alarm.
Targets grbllib.c506 active-MPG reset report arm, previously only inactive arm
measured. Focused ASan/UBSan passes1/1 in0.07s. Override/WCO field assumptions
were corrected to the fixture's enabled report mask, not classified as a defect.
No CORE/shared fixture changes or allowances. Two local successor cases remain
outside hosted7d0dff6 run40047406632. Continue batching without tiny full gates.

# Driver ATC handler survives startup and a native warm reset - 2026-10-24

Added boot.automatic_toolchanger_handler_survives_boot_and_warm_reset.
Driver registers ATC capability/change callback before initialization. Serial
T3M6 completes on the native callback; Ctrl-X warm reset then T4M6 uses the same
handler. Driver-installed tool and parser tool agree at3 before reset and4 after;
manual-change flag stays clear, final idle/no alarm/no error. Exactly two changes,
one driver setup/release. This targets grbllib.c496 automatic-changer startup arm,
previously absent from the measured report, through ordinary driver lifecycle.
Focused ASan/UBSan passes1/1 in0.06s. No CORE/shared fixture edits or exceptions.
This is the first successor after pushed7d0dff6; hosted40047406632 covers that
prior batch only. Preserve batch pacing and keep authoring while it runs.

# Controls/recovery cumulative sanitizer gate passed - 2026-10-24

Six new scenarios plus one existing pendant extension pass the single complete
4392-case ASan/UBSan gate in58.50s. Strict summary succeeds with existing19
known regressions and one exact recovering UBSan; no unexpected failures/skips.
No new allowances, CORE/shared fixture edits or unchanged helper-test reruns.
Fresh upstream CORE fetch remains2e165a1 and checkout is clean. New cases cover
native sender controls, physical M0 resume, configured rotary homing, spindle
failure/retry/cached activation, automatic null fallback and repeated file-tool
persistence. Isolated branch evidence distinguishes controls from new targets.
Deliver cumulative checkpoint on existing74; one exact-source hosted report
next, no isolated module runs. Current measured coverage remains ed8dc71's
98.45%lines/91.28%branches until successor artifact locks and stages are verified.

# Pendant denied-command recovery also routes feed hold correctly - 2026-10-24

Extended existing stream.mpg_buffered_gcode_denied_without_control_takeover,
retaining G20 rejection/non-takeover checks. Pendant realtime feed hold queues
EXEC_FEED_HOLD without EXEC_CYCLE_START or a visible cycle-start report flag.
Following $13 query returns normal value/ack only to pendant; primary input
and output ownership remain unchanged. This targets stream.c716's accepted
non-cycle-start command arm through normal pendant input, without fake motion
state or another quota case. Focused ASan/UBSan passes1/1 in0.06s.
Six new scenarios plus one extension now span boot control, physical resume,
rotary homing, spindle recovery/fallback, file tool persistence and pendant I/O.
No CORE/shared fixture edits, new allowances or per-module hosted runs.

# Repeated file tool selection preserves persistent NVS without duplicate save - 2026-10-24

Added boot_ngc native embedded macro with matched SUB/ENDSUB and two M61Q7
commands, called from serial O<toolrepeat>CALL then restored sender $G. Public
persistence setting enabled during setup. Chained tool/NVS observers see both
native tool-change notifications but exactly one global settings write; live
NVS read confirms persistent tool7, final parser/settings remain7 with no alarm.
Targets grbllib.c235 unchanged-tool branch through file parser's normal forced
selection, not direct invocation of the core-only gc_tool_changed helper.
Focused ASan/UBSan passes1/1 in0.06s. Initial post-shutdown NVS read was a test
lifetime error; moved read before controller exit with assertions retained.
No CORE changes or sanitizer exception. Six successor scenarios now accumulate.

# Native failed-default startup creates one safe null fallback - 2026-10-24

Added full boot with two real driver descriptors registered before initialization.
Configured primary returns false; normal grbllib startup scans the nonempty
catalog and adds null spindle2. Secondary remains unconfigured. M3S500 is
observed on the null driver, M5 turns it off, no physical driver output occurs.
Normal listing completes without errors; driver startup/idle/alarm state valid.
Repeated public spindle_add_null returns2 with count3, preserving catalog.
Targets spindle_control.c539 scan exhaustion, previously one missing outcome,
through its native startup caller rather than manufactured registry state.
Focused ASan/UBSan passes1/1 in0.06s. No CORE/shared fixture edits or exception.
Successor now accumulates five scenarios; full gate/hosted report still pending.

# ed8dc71 fully green; displayed coverage refreshed - 2026-10-24

Actual API run40044741403 completed success at00:37:46UTC; all five source,
GCC, Clang, coverage and Results summary jobs completed success. Prior exact
artifact/source/filter locks, seven stages0 and coverage counts remain verified:
17480/17756lines98.45%,12627/13834outcomes91.28%, no lost covered lines.
README badges and KNOWN_BUGS measured paragraph now point to this successful
checkpoint; gap inventory removes stale pending-GCC wording. Four successor
scenario files remain local and outside this measurement. No full rerun or
new hosted dispatch for documentation. Full objective remains active.

# Corrected rotary and spindle activation coverage evidence - 2026-10-24

Ran the corrected rotary and spindle scenarios with existing coverage binaries
into fresh isolated prefixes. machine_limits.c306 configured negative travel arm
executes once. spindle_control.c101 executes both initialized and uninitialized
arms in one realistic fail/retry/switch-back lifecycle;102 handles both optional
config absence and supplied driver configuration. Proof and gcov sources retained
at build-asan/rotary-spindle-native-proof74. Prior measured306/101 each have one
missing outcome; compiler branch IDs are not compared across compilers and no
aggregate percentage is inferred. The superseded zero-travel duplicate remains
removed. Existing partial RTU reply case already covers truncated exception,
normal-function and wrong-address headers plus recovery; no duplicate added.
No CORE edits, new exceptions, full gate or hosted dispatch for this evidence.

# Configured-travel rotary replacement passes - 2026-10-24

Replacement homing_command_eight.rotary_configured_travel_homes_selected_axis
passes focused ASan/UBSan1/1 in0.06s. Public A travel360 persists as-360; $HA
contacts and pulls off to physical70/logical-10, only A moves and becomes homed.
The removed zero-travel duplicate is not registered or counted as added work.
Existing full-boot zero-travel controls remain unchanged. No CORE edits/allowance.

# Registered spindle configuration failure, retry and cached reactivation - 2026-10-24

Added one scenario with two drivers defined before registration. Primary config
fails once: selection rejects, no output callback occurs, no default is enabled.
Retry succeeds; repeated selection does not reconfigure. Normal M3S1200/M5
reaches driver output. Selecting an alternate driver without optional config and
switching back preserves the primary successful configuration count at2, targeting
spindle_control.c101 cached activation arm (prior report one missing outcome).
Focused ASan/UBSan passes1/1 in0.05s. Initial fixture omitted cold-start/tool
initialization; aligned with existing fixture and retained all assertions. That
setup crash is not a CORE defect and has no exception. No shared fixture edits.
Four scenarios now accumulate across sender/physical input, rotary homing and
spindle lifecycle. No repetitive full gate or hosted dispatch for this addition.

# Rotary search case corrected against existing boot coverage - 2026-10-24

Existing boot_eight.rotary_axis_without_travel_limit_homes_using_switch_feedback
already covers the zero-travel/full-turn fallback. Removed the duplicate local
zero-travel case; its earlier passing result was no new coverage. Replacement
uses public rotary and A travel360 writes, covering the configured-travel side
of machine_limits.c306. Keep switch/pulloff/reference and axis-isolation checks.
This corrects the previous coverage-target assumption; raw percentages unchanged.

# ed8dc71 coverage job verified; overall workflow still running - 2026-10-24

Run40044741403 exact harness/CORE2e165a1/filter locks match both artifacts;
exactly seven coverage stages exit0.4386 cases:4368clean/18known/0failed/skipped.
17480/17756lines98.45%,12627/13834outcomes91.28%; eight additional outcomes
against05603c7, identical covered-line set/no lost lines. Updated measured gap
inventory to276lines/1207outcomes, including per-source branch counts.
Source/Clang/coverage passed; GCC in_progress at actual API inspection, so
README success badges retain prior all-five-green checkpoint. Do not confuse
this complete coverage job with overall workflow success. Existing run reused;
no duplicate dispatch. Two local boot additions remain outside this measurement.

# Isolated coverage confirms native sender/physical-start branch execution - 2026-10-24

Built both new boot scenarios with existing no-sanitizer coverage configuration
and ran them into a fresh isolated GCOV prefix. system.c175 absent cycle-start
callback executes once;365/389 absent control observer each execute twice.
These three conditions each have one missing outcome in verified05603c7 XML;
the cases assert their callbacks are naturally NULL throughout the workflow.
Block-delete377 also executes twice but its prior condition was already fully
covered, so it is a behavioral control rather than claimed new branch gain.
Raw local proof: build-asan/sender-native-branch-proof74/{system.c.gcov,proof.json}.
No aggregate percentage claimed from isolated profiles or compiler branch IDs.
No CORE changes, exceptions, full gate or hosted dispatch for this proof.

# Physical cycle start resumes a real M0 pause without observers - 2026-10-24

Added a full-boot streamed two-move job with M0 between moves. Registered driver
advertises cycle-start capability; its actual control IRQ asserts then releases
the input after four complete-hold polls. Both optional plugin callbacks remain
naturally NULL. First move stays at80 pulses throughout the pause; input resumes
the second move to160 exact X pulses with no Y/Z motion, errors or alarm.
Focused ASan/UBSan passes1/1 in0.05s. This exercises system.c175's absent cycle
observer through a supported physical input, rather than a private callback.
No CORE/shared fixture edits, new exceptions or redundant full/hosted run.
Two new boot scenarios now accumulate locally for the next substantial batch.

# Native sender toggles without plugin observer - 2026-10-24

Added one full-boot serial scenario using native $S/$O/$B commands with no
control observer or hardware switch capabilities. Single-block and optional-stop
flags toggle and restore; block delete skips /G91 while enabled, then accepts
/G91 after disabling it. Parser queries remain usable, no errors/alarm occur.
Targets optional observer arms in system.c365/377/389 without removing an
installed callback. Focused ASan/UBSan passes1/1 in0.07s; no CORE/fixture edits,
new defect or allowance. Accumulate a substantial successor before full gate.
Existing ed8dc71 hosted run40044741403 remains in_progress at live inspection;
coverage artifact not yet published, so no new aggregate percentage claimed.

# Door/sleep/UVW cumulative gate passed; prior checkpoint fully verified - 2026-10-24

Current five new cases/two extensions pass full4386-case ASan/UBSan58.67s and
strict summary:4366clean/1exact recovering UBSan/19known regressions/0unexpected
failed/skipped. Correct W/X and U/V inversion assertions remain in two exact
expected failures under one confirmed mapping issue. No CORE/shared fixture
edits or sanitizer allowance added; unchanged reporting helpers not rerun.

Prior05603c7 run40042658660 is fullygreen, all five jobs success, exact harness/
CORE2e165a1/filter locks and seven stages0 verified.4381hosted:4365clean/16known/
0failed/skipped.17480/17756lines98.45%,12619/13834outcomes91.22%; +8outcomes
with identical covered-line set against6d566e0. Updated successful badges/current
inventory276raw lines/1215outcomes. Current successor coverage remains pending.
Full supported-coverage objective remains active; no merge or completion claim.

# Confirmed U/V inversion also ignores remapped axis bits - 2026-10-24

Added the independent registered U/V pair in supported UVW6 configuration.
Public inversion masks8 and16 and normal driver setting notifications each
produce two configuration callbacks, but both physical input inversions stay0.
Correct U-only(1,0) and V-only(0,1) assertions retained. Raw ASan/UBSan output
records U-only=(0,0)/V-only=(0,0), no sanitizer diagnostic. Source helper uses
fixed ordinal6/7 rather than configured axis3/4, complementing W's X alias.

Expanded one dated KNOWN_BUGS mapping entry with both reproducers. Each exact
case has WILL_FAIL/known_bug; grouped pair/strict check passes2known/0unexpected/
0skipped,0.09s test time. No broad allowance or CORE edit. Total expected
regressions becomes19, preventing an incomplete W-only repair from passing.

Substantial successor now has five new cases/two extensions across physical
door/sleep, legacy I/O, provider metadata and eight-axis/UVW mappings. All
focused checks complete; cumulative gate and source-matched coverage pending.
Do not dispatch isolated per-defect runs or treat these known failures as blockers.

# Confirmed W motor-fault inversion aliases X in supported UVW configuration - 2026-10-24

Added registered-input/public-setting reproduction in host_core_uvw (N_AXIS6,
ABC->UVW). W/X fault functions are assigned before registration, driver caps
advertised, and public inversion stores followed by normal driver notification
configure both physical inputs. X-only inversion incorrectly sets W inverted;
W-only inversion incorrectly clears it. X controls/callback counts pass. Raw
ASan/UBSan group logs X-only=1/W-only=0 and the correct W assertion fails.

Retained both correct independent-axis assertions, one exact WILL_FAIL/known_bug
and dated KNOWN_BUGS entry with cause/fix/removal guide. Labelled focused run and
strict summary pass1known/0unexpected/0skipped,0.05s. No sanitizer allowance or
CORE edit. Total known regressions becomes18. No alarm/motion failure claimed.

Also extended existing eight-axis grouped mapping with Input_Probe -> no axis
mask, covering its configuration-specific non-axis control. That case passed
raw grouped check0.07s. Keep with door/sleep, legacy I/O and metadata successor
work; no per-case full gate or hosted dispatch. Defect remains nonblocking.

# Legacy driver-owned claim count and provider rejection validated together - 2026-10-24

Added a one-relay legacy driver registered through ioports_add with its own
HAL pin-info/claim/output handlers. Claim callback decrements the driver-owned
legacy available count. Public ioport_claim must not decrement it twice; require
zero count (no unsigned wrap), claimed ownership and correct relay on/off through
the returned port. No modern handler is replaced after registration and no
private mapping/state is forced. Targets ioports336's changed-count arm.

Grouped ASan/UBSan passes this and pending multi-setting early rejection/retry
extension (2/2,0.12s test time). Current successor: physical door/no-retract sleep,
legacy I/O claim and provider-table validation. No new allowance, CORE/shared
fixture edit, full gate or hosted dispatch; aggregate coverage still pending.

# Source-reviewed early rejection of multi-setting provider table - 2026-10-24

Extended the existing public metadata rejection/recovery control with missing
required value in the last of two setting descriptors. Reverse iteration must
reject immediately, publish neither setting nor group and invoke no persistence
or setter; restoring the value retains the original successful registration and
ordered report controls. Targets settings2760's idx-nonzero/error loop exit.
No new invalid enum, native controller state or direct private callback.

Confirmed settings2759 requires function getters before registration, so no
missing-getter reporting fixture was added. The small table extension is source
reviewed and awaits grouped execution with the physical-door/sleep successor
cases. No new case/exception, shared fixture/CORE edit or full/hosted run.

# Sleep above parking target disables kept coolant without Z motion - 2026-10-24

Added public $62=1/$SLP workflow with registered normal PWM spindle and actual
G0 to Z home above parking target. With keep-coolant policy enabled and M3/M8
active, require real sleep feedback/state, spindle and coolant off, no extra Z
pulses or XY movement, empty planner and no system motion. Wrap and chain the
normal feedback reporter, retaining the Sleeping text assertion. ASan/UBSan
passes0.05s. Targets the no-retract sleep accessory policy at state_machine589.

Initial message-only failure came from parking fixture's deliberate no-output
feedback callback; restoring report_init_fns after parking setup resolves it.
Shutdown/no-motion assertions were unchanged and no CORE defect was claimed.
Keep with physical-door counterpart for substantial successor batch; no new
exception, shared fixture/CORE edit, full gate or hosted dispatch.

# Physical-door no-retract coverage evidence corrects target assumption - 2026-10-24

Fresh physical-door-no-retract-proof74 confirms the new registered-spindle case
executes state_machine550/589. The intended extra678 outcome is NOT reached:
no parking motion means the restore-motion handler is bypassed. Corrected the
prior source-target note; no678 gain is claimed. Profile/result retains this
unexecuted line explicitly. Public physical-door/coolant/no-Z/resume assertions
still pass. This changes the next search:678 needs separate ownership review,
not another already-above-target geometry. No full or hosted run was started.

Fetched upstream CORE refs: origin/HEAD remains2e165a1, same clean working
checkout. No dependency switch or CORE edit. Continue independent successor
work;05603c7's existing hosted checkpoint handle remains40042658660.

# Physical door above parking target keeps coolant and resumes without Z motion - 2026-10-24

Added ordinary no-retract door workflow with a properly registered normal PWM
spindle. Move Z from fixture position to home using actual G0, start powered X
cut with M3/M8, raise physical door IRQ and require spindle off/coolant retained
by policy, stopped cut and no extra Z pulses. Close/resume completes exact X20
endpoint with spindle/coolant restored and unchanged Z pulse count. No registered
spindle pointer mutation or forced parking internals. ASan/UBSan passes0.07s.
Targets state_machine550/589 no-retract accessory conditions.

Initial fixture used CMD_SAFETY_DOOR helper, which deliberately sets is_parking
and turns coolant off. Corrected to native control_interrupt_handler physical
input routing; retained intended physical-door assertions. No CORE defect or
allowance inferred. This successor case is separate from pushed05603c7/live
hosted40042658660; keep accumulating before full/hosted validation.

# RTC/backlash/RTU/I/O cumulative gate passed - 2026-10-24

Three new cases/five extensions pass the full4381-case ASan/UBSan gate58.16s.
Strict summary:4363clean/1exact recovering UBSan/17documented regressions/
0unexpected failed/skipped. Correct read-only RTC write rejection is retained
in one exact expected failure; no sanitizer allowance added. Includes actual
homing-direction/backlash pulses, repeated unlock startup safety, normal RTU
write without observer, dedicated timeout retries, native no-group help, absent
output claim/retry and empty descriptor fallback. CORE unchangedclean2e165a1.
No unchanged helper reruns or repeated full gate. Deliver this coherent batch;
its coverage awaits a new source-matched checkpoint, prior fully green6d566e0
remains98.45%lines/91.16%branches. Full supported-coverage goal remains active.

# 6d566e0 hosted checkpoint fully verified - 2026-10-24

Run40041178250 terminalsuccess, all five source/GCC/Clang/coverage/Results
summary jobs success on exact6d566e0/CORE2e165a1/filter. Both locks and exactly
seven stages0 verified.4378hosted:4363clean/15known/0failed/skipped.
17480/17756lines98.45%,12611/13834outcomes91.16%; +13outcomes with identical
covered-line set against80db252. Updated success badges/current snapshot and
remaining inventory276lines/1223outcomes. New local RTC/backlash/RTU/I/O batch
is separate; its cumulative gate is running. Full goal remains active; no CORE
edit, merge or duplicate hosted dispatch.

# Source-reviewed help traversal of native Modbus settings without groups - 2026-10-24

Extend the initialized RTU option-report case with public $HELP missingdevice.
The actual native Modbus settings provider registers settings but no separate
group metadata. Require exact N/A output with transport still up and no frame
transmission; retain the original option observer/plugin identification checks.
Targets report396's absent provider-groups condition through real registration,
not a fabricated metadata pointer. Source-reviewed only; awaits grouped execution.
No new case, wrapper, exception, shared fixture, CORE edit or full/hosted run.

# Confirmed read-only RTC write acknowledgement defect, nonblocking - 2026-10-24

New public-command regression uses a valid RTC-capable driver with documented
optional setter absent and working getter. Both before/after $RTC queries return
the original time, but $RTC=<different time> returns0/Status_OK. Keep the correct
non-success assertion; raw ASan/UBSan check fails only there, no diagnostic.
Exact WILL_FAIL/known_bug added for this one case, dated KNOWN_BUGS entry links
source/cause and removal guide. Focused labelled check and strict summary pass:
1known regression/0unexpected failures/skips,0.05s test time. No CORE edits or
sanitizer allowance. Total expected regressions becomes17 (previous16).

Continue independent work: current batch has three new cases/four extensions
across RTC/system, real boot/backlash, Modbus and I/O. Aggregate source coverage
and cumulative gate remain pending; this defect does not block the goal.

# Reversed homing direction initializes real backlash take-up - 2026-10-24

Added actual boot/serial $23=1 then $160=0.1, negative1mm and positive1mm X job.
Require176 motor pulses (160 travel plus two8-step take-ups), physical/logical
origin restored, parser X0 and no Y/Z pulses. Public setting writes initialize
compensation using the reversed homing direction; no private direction bits or
planner state forced. Targets motion_control59's opposite initialization arm.

Grouped ASan/UBSan passes this and the pending repeated-$X startup safety
extension (2/2,0.13s test time). Stored G91 remains unexecuted after both unlocks,
controller idle/G90 with no errors. Current batch: two new cases and four
extensions across I/O/RTU/boot/backlash. No new allowances, CORE/shared fixture
edits, full gate or hosted dispatch. Aggregate gain awaits cumulative coverage.

# Source-reviewed repeated unlock preserves blocked startup program - 2026-10-24

Extend existing forced-initial-alarm full-boot control with stored startup G91
and two consecutive $X commands before $G. Require idle/unlocked, unchanged G90
mode and no command errors. The first unlock must not execute stored startup;
the repeated idle unlock likewise remains harmless. Targets system451's idle
arm through normal serial commands. Source-reviewed only; awaits grouped
execution with the current I/O/RTU batch. No new case, exception, fixture or
CORE change, full or hosted run.

# Blocking register write succeeds without optional reply observer - 2026-10-24

Added normal Modbus function6 register10/value0x1234 write, with an exception
handler but no on_rx_packet observer. UART fixture echoes the actual transmitted
eight-byte frame including generated CRC. Blocking send returns success with no
observer/exception calls, then the next ordinary read delivers its expected
payload. Uses existing blocking scheduler and public modbus_send; no private
packet/state mutation. ASan/UBSan passes0.07s. Targets modbus_rtu302's absent
reply-observer arm. Keep with the I/O and dedicated-timeout retry extensions;
no new exception, shared fixture/CORE edit, full or hosted run.

# Dedicated RTU timeout survives retry exhaustion and next reply recovers - 2026-10-24

Extended the existing dedicated-timeout scenario after its original timeout/
success controls. Two configured retries produce three unanswered transmissions;
only the dedicated timeout callback fires once at final exhaustion, with no
exception callback or fabricated reply. A later complete reply succeeds with
correct payload. This reaches final-retry callback restoration at modbus_rtu312
using normal modbus_send, scheduler and UART fixture, not private packet state.

Grouped ASan/UBSan check passes all three current extensions (0.19s test time):
RTU retry recovery, absent-output-bank claim followed by registration/retry, and
empty saved-description capability selection. No new case, allowance, shared
fixture or CORE change. Keep accumulating across modules before a full/hosted
gate; measured coverage remains the prior locked report, not these extensions.

# Source-reviewed absent-bank claim retry and empty description fallback - 2026-10-24

Extend the existing input-only -> output expansion discovery case: attempt a
public output claim before the bank exists, require NULL/unassigned with input
availability and driver outputs unchanged, then retain normal registration/
discovery/claim/output success. This exercises get_info's absent ports path
through ioport_claim rather than private entry points (ioports270/272).

Extend the saved-description fallback case with an empty string: PWM capability
filter still selects physical0; no filter selects highest free physical1. Both
remain unclaimed. Targets _get_next515's empty-but-nonnull descriptor condition.
These two small source-reviewed extensions await grouped build/execution; no
claim that the previous full4378 gate includes them. No new case, wrapper,
exception, CORE edit, full or hosted run. Existing6d566e0 hosted40041178250 was
verified live with source passed and GCC/Clang/coverage running at resume.

# Boot/pendant/I/O cumulative delivery gate passed - 2026-10-24

Five new scenarios and three extensions pass the full4378-case ASan/UBSan gate
in58.27s. Strict summary:4361clean/1exact recovering UBSan/16known regressions/
0unexpected failed/skipped. Includes physical probe connection without toggle,
spindle-only automatic sleep, pendant allocation recovery and receive-only alarm
handover, output discovery after input-only registration, blank-line handling,
optional registration observer absence and UART identity capability isolation.
No new defect allowance/shared fixture/CORE changes. Unchanged reporting helpers
were not rerun. Current measured hosted80db252 remains98.45%/91.07%; this
successor batch awaits its own source-matched hosted measurement. Preserve the
unrelated empty-diff legacy-registration status entry outside the commit.

# 80db252 hosted checkpoint fully green - 2026-10-24

Run40039209481 is terminalsuccess on exact80db252/CORE2e165a1. All five
source/GCC/Clang/coverage/Results summary jobs passed; both source/filter locks
and exactly seven coverage stages0 verified. Updated success badges and current
snapshot to98.45%lines/91.07%branches (17480/17756,12598/13834). Corrected the
stale277 missing-line note to276 and kept NULL-path VFS contracts unclassified,
separate from the two bounded native routing guards. No exclusions or CORE edit.
Local successor boot/stream/I/O batch is separate and its cumulative gate is
running; this successful checkpoint does not complete the full coverage goal.

# Output configuration discovers bank added after input-only registration - 2026-10-24

Added an I/O initialization-order scenario using public digital bank registration.
Register input-only hardware, query output configuration and require zero ports/
no callbacks. Add the actual output bank, retry discovery, claim an expansion
relay and drive its original physical pin on/off. Input availability stays2 and
one output remains unclaimed. No private count/mapping mutation. Targets
ioports_cfg549's zero-availability arm followed by successful discovery.

Grouped ASan/UBSan execution passes this and the previously authored registered
UART identity isolation extension (2/2,0.09s test time). The latter rejects
capability lookup for another transport/instance without claiming resources,
then retains normal registered claim/close controls. No new exception, CORE or
shared-fixture edit. Five new cases/three extensions now accumulate across
boot/probe/sleep/stream/I/O since80db252; cumulative coverage remains pending.

# 80db252 measured gain verified; Clang still running - 2026-10-24

Existing run40039209481 source/GCC/coverage passed, Clang in progress. GCC's
exact known diagnostic classification now passes. Both artifact source locks
match80db252/CORE2e165a1/filter; exactly seven coverage stages exit0.4373hosted:
4358clean/15known/0failed/skipped.17480/17756lines98.45%,12598/13834outcomes91.07%.
Same-source comparison againsta432 adds12outcomes with identical covered-line
sets. Refreshed inventory:276raw missing lines/1236outcomes. Success badges
stay pinned to prior fully green run; no completion/readiness claim.

Local successor boot probe/spindle sleep and pendant buffering/registration/
receive-only/capability tests remain separate from this measurement. No duplicate
run, full gate, CORE change or merge. Continue cross-module authoring.

# Receive-only pendant takes/returns control while alarm remains locked - 2026-10-24

Added public homing-required alarm -> receive-only pendant enable/disable
workflow. Require input handover/reset and RX ownership changes, primary writer
preserved throughout, no pendant output and alarm unchanged. Public alarm API
sets the state; no flags/private pointers are forced. Grouped ASan/UBSan check
passes this case and the pending no-observer registration/description extension
(2/2,0.09s test time). Targets stream803/837 and740 respectively.

Source-reviewed existing registered-UART flag lookup extension: same instance on
Bluetooth and different Serial instance both return zero capabilities without
claim/release calls, then retain all original claim/close assertions. This new
extension awaits grouped execution; no earlier pass is attributed to it. Keep
all successor work together; no full/hosted run or CORE edit/new allowance.

# Pendant connection allocation failure preserves primary and allows retry - 2026-10-24

Added a registered pendant failure/retry scenario using existing exact stream
allocator instrumentation. Reject its one connection-node allocation, require
false/no registration notification and intact primary read/write/broadcast. Retry
registers once; both broadcasts work and a foreground modal query is directed
to the pendant without changing primary output or taking control. ASan/UBSan
passes0.07s. Targets stream.c751's rejected connection arm; no new wrapper,
configuration, exception or CORE/shared fixture edit.

Also source-reviewed the existing receive-only UART description case with its
optional on_mpg_registered observer absent before registration; require the pin
description and primary reader while notification count stays zero (stream740).
This small extension awaits grouped build/execution at the next batch boundary;
do not claim the earlier focused pass covered it. No full/hosted run started.

# Pendant blank lines acknowledge without replaying a prior query - 2026-10-24

Extended mpg_buffered_commands_wait_for_response after its existing $13/$G
queries. Two separate empty LF lines each wait for foreground processing and
produce exactly one ok with no stale modal/setting output. A subsequent $13
query still returns its exact value/ack, primary input remains selected and MPG
control stays off. Covers ordinary empty-input and repeated-same-EOL behavior
in stream.c651/702 while preserving response-before-next-command ordering.
Focused ASan/UBSan passes0.06s. No new case/exception, shared fixture or CORE
edit. Aggregate gain awaits the cumulative report; keep with probe and spindle
sleep successor work rather than dispatching another small hosted checkpoint.

# Registered spindle alone triggers automatic sleep and switches off - 2026-10-24

Added a full boot public $62=1/M3S5000 scenario with the existing registered
spindle fixture, no coolant and idle-lock255. Advance the scheduler only after
normal M3 output is observed; require native STATE_SLEEP, spindle off, motors
disabled, no coolant activation/error and no planner motion. Uses normal driver
registration/selection and protocol loop; no modal state assignment. Focused
ASan/UBSan passes0.07s. Targets sleep.c78's spindle-powered condition, distinct
from existing coolant-only timeouts. No aggregate gain claimed until measurement.
Keep with physical-probe successor work while80db252's hosted checkpoint runs;
no new full gate, hosted dispatch, exception or CORE/shared fixture change.

# Residual planner RPM-refresh ownership reviewed - 2026-10-24

Reviewed the one measured planner outcome still missing on CORE2e165a1:
changed-RPM refresh finding an empty planner. Native scheduling uses a live block;
completion cancels the callback before block discard, idle/reset cancels pending
tasks, and reset has no foreground task execution between planner/stepper reset.
Recorded bounded exact-source evidence in TODO, keeping the outcome included and
external getter/plugin behavior unclaimed. No private orphan-block test, source
exclusion or completion claim. Local physical-probe connection case remains
validated successor work; prior80db252 hosted handle stays40039209481.

# Physical probe connection input without optional toggle callback - 2026-10-24

Added a full grbl_enter boot case for the documented HAL optional callback.
Driver setup reports probe connection directly from its physical control input
and has no connected_toggle handler. Actual disconnect/reconnect control IRQs
queue and execute normal foreground connection events; driver state follows the
physical input, no alarm/abort is introduced, and subsequent G91 parses normally.
No live handler is removed or probe private state forced. ASan/UBSan passes0.06s.
This targets probe_connected_event235's missing optional-handler arm through its
native system.c caller. Aggregate gain awaits cumulative measurement, not claimed
from source alone. Keep successor work separate from pushed80db252/live hosted
40039209481; no new full gate or hosted dispatch for this individual case.

# Cumulative NVS/probe/tool-change sanitizer gate passed - 2026-10-24

Six new tool-change workflows plus existing NVS allocation cleanup/reuse and
probe IRQ-disable recovery extensions pass the full4373-case ASan/UBSan gate
in58.37s. Strict summary passes with one exact recovering UBSan and16 known
regressions; no unexpected failures/skips. CORE2e165a1 remains clean.

Existing hosted a432e12 run40036375055 is terminal failure: source/Clang/coverage
passed, GCC test stage passed but classification rejected its same absent-W
shift255 diagnostic because GCC spells the type 'long unsigned int'. The old
matcher accepted only 'unsigned long'. Expand only that exact type alternative;
retain exact case/source177/exponent255/32-or64-bit constraints and correct
assertions. Thirteen affected reporting tests pass2.072s, including actual GCC
spelling and rejection of another source/line/exponent. No C rebuild/full gate
needed after this manifest-only reporting repair. Six new cases remain locally
validated, not included in the98.45%/90.98% measured a432 coverage checkpoint.

# Z-only manual tool change skips configured G30 traverse - 2026-10-24

Added a supported manual mode scenario using the existing fixture's ordinary
Z-only homing state. Enable G30 change position at X4/Y5/Z-0.5 and require the
full-XYZ homing guard to skip that traverse: zero XY pulses, Z retracts80steps
to home, planner empties and tool remains pending/uncompleted. Acknowledge the
change and verify handler installation at that event. Initial test expected the
handler before acknowledgement; corrected the fixture ordering, not CORE.
Focused ASan/UBSan passes0.07s. The source target is tool_change497's full-homing
condition; no aggregate coverage gain claimed before cumulative measurement.
Six new tool-change cases now accumulate with NVS/probe recovery extensions.
No new exception, CORE edit, full gate or hosted dispatch.

# Automatic contact reset and deep-plate retract scenarios - 2026-10-24

Added two distinct existing-fixture workflows. Automatic toolsetter reset after
first contact prevents retract/second pass and reference establishment, restores
the hand probe and stream/control handlers and never completes/restarts the job.
A normal manual touch-off with plate at -6mm establishes its measured dynamic
offset and retracts4mm, remaining below home rather than taking the home clamp.
Both focused ASan/UBSan checks pass0.14s total. Fresh touch-group-proof74 has
separate automatic-reset/deep-plate profiles for tool_change326/331 and644/647.
No CORE/shared fixture changes, new allowances, full gate or hosted dispatch.
Five new tool-change cases now accumulate with NVS/probe recovery changes.

# Reset after first workpiece touch-off prevents retract and second probe - 2026-10-24

Added public $TPW/reset scenario with existing motion and probe fixtures. Chain
the tool-change completion observer after first successful contact, enqueue real
CMD_RESET and require no subsequent Z pulse or second probe. Reset chains once,
clears pending tool change, restores stream/control handlers, leaves XY fixed
and never marks the tool complete or requests cycle start. No IRQ timing or
private state assignment. ASan/UBSan passes0.07s. Fresh touch-reset-proof74
records rejected retract and short-circuited second probe at tool_change633/639.
No new exception or CORE edit; accumulate with NVS/probe/contact-loss scenarios.
No full gate or hosted dispatch for this individual addition.

# Automatic toolsetter second-pass contact loss cleans up without reference - 2026-10-24

Added the automatic counterpart through actual cycle-start, registered toolsetter
selection and motion. First contact succeeds; the public completion observer
removes contact for the slow second pass. Require ProbeFailContact, no reference
or dynamic offset, restored hand probe/control/stream handlers, empty planner
and no cycle-start. The observer remains installed. ASan/UBSan passes0.05s;
fresh auto-second-contact-loss-proof74 records the second-probe result and
reference-gate evidence at tool_change331/334; the reference notification at338
remains unexecuted in this failure scenario. No new allowance or CORE edit.
Keep with manual second-contact, NVS and probe recovery for cumulative delivery;
no full-suite or hosted run just for this addition.

# Workpiece touch-off loses contact on slow second pass - 2026-10-24

Added a public $TPW scenario using the existing motion/probe fixture. The first
contact succeeds; a chained public completion observer removes the plate before
retraction/slow probing. The second pass reaches its travel without contact,
returns ToolError and prompts retry. Tool-change suspension remains installed,
no cycle-start is requested, XY stays fixed and the planner drains. Preserve the
existing tool-change observer; no private state or CORE edit. Focused ASan/UBSan
passes0.07s; fresh second-contact-loss-proof74 records tool_change639/650
branch evidence. No defect allowance, full gate or hosted dispatch. Accumulate
with NVS and probe IRQ recovery before cumulative validation.

# a432e12 completed coverage measurement; GCC remains live - 2026-10-24

Inspected existing run40036375055: source/Clang/coverage passed, GCC in progress.
Downloaded both coverage artifacts, verified exact harness a432e12/CORE2e165a1/
core filter and exactly seven stages exit0. Coverage4367:4352clean/15known/
0failed/skipped.17480/17756 lines98.45%,12586/13834 outcomes90.98%.
Same-source comparison adds seven outcomes; no added/lost lines. Refreshed raw
remaining inventory to276 lines/1248 outcomes. Success badges stay on the prior
fully green checkpoint. Local NVS/probe extensions remain separate, no duplicate
hosted run or full-suite gate. The full supported-coverage goal remains active.

# Probe disconnect IRQ rejection and recovery - 2026-10-24

Extended the existing public protection connection scenario: reject driver IRQ
removal, retain reported armed/guarded state while disconnected, reconnect with
registration restored, then successfully disconnect and clear the guard. No
private state assignment or timing assumption. Focused ASan/UBSan passes0.06s.
Fresh probe-disable-recovery-proof74 records both driver-result outcomes at
probe.c57 (counts1/2); the unguarded short-circuit is absent in this isolated
scenario. Hosted baseline has three of four outcomes; exact aggregate gain
awaits cumulative measurement. No new defect, allowance, CORE edit, full gate
or hosted dispatch. Keep with cumulative NVS work.

# Existing buffered allocation preserves saved information without reallocating - 2026-10-24

Further extended existing NVS allocation recovery case after successful retry.
Write build information through settings API, arm the existing allocator rejection
fixture, call nvs_buffer_alloc again and require success with rejection still
unused. Readback validates saved information; normal final cleanup retained.
No private pointer assignment or double-free. ASan/UBSan passes0.05s. Fresh
nvs-allocation-reuse-proof74 shows both outcomes at229 (existing allocation)
and243 (unallocated cleanup from previous extension). No CORE/shared fixture
edit, new case/allowance/full gate or hosted dispatch. Keep with successor work.

# Buffered NVS cleanup after failed allocation and successful retry - 2026-10-24

Extended existing buffer_allocation_failure_can_retry_without_changing_storage_handlers.
After one ordinary allocation failure, call public nvs_buffer_free while no
buffer exists, verify physical type/handlers/get_physical remain unchanged,
then retain existing successful allocation/emulation initialization and final
allocated cleanup. Native grbllib exit518 calls cleanup unconditionally, so
this models valid failed-allocation cleanup rather than double-free or private
pointer mutation. ASan/UBSan passes0.07s; fresh unallocated-nvs-cleanup-proof74
executes both nvs_buffer243 outcomes, previously1/2. No CORE/helper edit,
new case/exception/full gate or hosted run. Current measured fully-green
f6da420 remains98.45%lines/90.93%branches; this is local successor work.

# Exactf6da420 hosted checkpoint fully verified - 2026-10-24

Run40034582551 terminalsuccess, all five source/GCC/Clang/coverage/Results
summary jobs success on exactf6da420/CORE2e165a1. Both locks/filter and exactly
seven stages0 verified.4365hosted:4350clean/15known/0failed/skipped.
17480/17756lines98.45%,12579/13834outcomes90.93%; +1line/+12outcomes
and no lost lines on same source. Regenerated per-source missing counts and
line lists:276raw lines/1255outcomes; refreshed success badges/current snapshot.
New covered motion_control1122 is real parking-abort recovery. Newer a432e12
run40036375055 is separate; never attribute its changes to this result. Full
supported-coverage goal remains active; no CORE edit, merge or duplicate run.

# Named/probe/homing cumulative delivery gate passed - 2026-10-24

Two new cases and six extended cases cover public absent-axis named/G92
queries, captured probe coordinate-record recovery, legacy multi-probe optional
helper absence, real manual-homing named status, named-variable allocation
recovery and the confirmed eight-axis absent-W conversion UB. Reused existing
configurations/fixtures; added one exact malloc wrapper target, one exact
san-only label/diagnostic manifest entry and dated KNOWN_BUGS. Correct value
assertions retained; no CORE/shared fixture edit or broad suppression.

Full build and ASan/UBSan4367 passes140.63s. Strict summary passes:
4350clean/1exact known recovering diagnostic/16known regressions/0failed/skipped.
Evidence batch74-named-probe-homing-delivery-{build.log,tests.log,results.xml,summary.log}
in build-asan. Unchanged Python reporting helper suite not rerun. CORE clean2e165a1.

Previous pushedf6da420 coverage job40034582551 verifies17480/17756lines98.45%,
12579/13834outcomes90.93%, +1line/+12outcomes/no lost lines versusbc84ad2.
New line is motion_control1122, parking abort return from the real coolant-delay
RESET workflow. Clang still live at last refresh: retain fully-greenbc84ad2
badges and do not claim terminal success. Current new batch needs its own
exact-head hosted validation at an allowed checkpoint; full goal stays active.

# Exactf6da420 coverage job verified, compiler completion pending - 2026-10-24

Run40034582551 coverage artifacts now available: exactf6da4204fd226b105b743a5f36f16b00db77d086/
CORE2e165a1 and filter locks verified; exactly seven stages all0.4365hosted
cases4350clean/15known/0failed/skipped.17480/17756lines98.45%,
12579/13834outcomes90.93%, same-source+1line/+12outcomes and no lost covered
lines versus40032608243. Source/coverage/GCC passed; Clang still live, so
keep overall-success badges pinned to fully greenbc84ad2. No duplicate run.
Current local named/probe/homing/allocator batch and exact absent-axis UBSan
regression are outside this measured head; their cumulative local gate is live
in process session33195. Do not restart on observation timeouts.

# Named-variable allocation recovery preserves existing values - 2026-10-24

Added named_allocation_failure_preserves_existing_value_and_allows_retry.
Public named setter creates _kept12.5; one scoped malloc rejection prevents
_pending creation while existing value stays unchanged. Lookup confirms failed
name absent. Updating _kept13.5 under the same allocator pressure succeeds
without another malloc; restoring allocator allows _pending42 and preserves
_kept13.5. Reused malloc_failure_host with one exact target wrapper addition.
ASan/UBSan passes0.05s. Fresh named-allocation-recovery-proof74 shows all four
ngc_params902 outcomes versus previous3/4. No CORE/shared fixture edit, new
exception or full/hosted dispatch. Keep with the independent successor batch
including correct absent-W sanitizer regression and real homing/probe queries.

# Manual-homing public named parameters with no switch cycle - 2026-10-24

Extended existing real manual_homing_status_uses_all_axes_when_no_switch_cycle_is_configured.
Public homing mode41, empty switch-cycle settings, actual move and $H remain
unchanged. Before/after homing now query _homed_state and _homed_axes through
normal named lookup in addition to existing |H status-field assertions. They
agree on0 before and1/allaxes after; actual pulse counts, positions and no
homing driver motion assertions retained. ASan/UBSan passes0.07s. Fresh
manual-homed-parameters-proof74 verifies manual-mode OR arm at ngc_params753
with zero switch mask/no single-axis flag, previously missing. No forced homed
bits, CORE/helper edit, new case/allowance or full/hosted dispatch. Keep with
local named/probe/G92 and eight-axis sanitizer regression successor batch.

# Legacy multiple-probe driver without optional individual-state helper - 2026-10-24

Extended existing named_probe_parameters_report_unavailable_capabilities. HAL
documents is_triggered as optional. Retain primary/absent-provider controls;
legacy selector now supports default/probe2/toolsetter and shared current-state
reader reports selected identity/contact. Advertise secondary capabilities with
that functioning selector, select each through HAL, and verify _active_probe
tracks selection while _probe2_state/_toolsetter_state return-1 without optional
individual-state helper. No malformed advertised-only provider or removed live
callback. ASan/UBSan passes0.07s. Fresh legacy-multiple-probe-proof74 records
missing helper short circuits at ngc_params741/745. No CORE/shared fixture edit,
new exception/case/full gate or hosted dispatch. Continue local successor work.

Existing40034582551 verified live jobs: source success; Clang120690895139 and
GCC120690895267 building, coverage120690895250 testing. Missing artifacts
were premature observation, not terminal failure; no duplicate/restart.

# Confirmed absent-W inch-conversion UBSan defect - 2026-10-24

New eight_axis.absent_named_w_position_in_inches_returns_zero uses actual
N_AXIS8, G21/G20 and unconditional native _abs_w/_w names. Metric and inch
zero assertions pass, but inch conversion at ngc_params177 shifts by255
(the absent-axis map marker) in the rotary-mask check. Raw ASan/UBSan output
reproduces exact shift exponent255/32-bit unsigned-long diagnostic, no assertion
failure. No invalid enum, axis-map forcing or private call. Dated KNOWN_BUGS
entry describes source cause, bounded observed consequence and upstream cleanup.

Added only this test's sanitizer-only known_sanitizer_bug label and exact
source177/message manifest entry (32/64-bit native unsigned-long widths).
Affected CTest passes0.11s; strict summary0: one passed with known sanitizer
diagnostic,0failed/skipped. Correct numerical assertions retained, no WILL_FAIL
or blanket crash suppression. Fixed diagnostics require removing this exact
allowance. No CORE/shared fixture edits or full/hosted run; continue independent
coverage work. Existing pushedf6da420/40034582551 stays separate.

# G92 absent-axis numbered query - 2026-10-24

Extended existing G92 apply/suspend/restore case with public A5214/W5219
queries on the real three-axis configuration. Both return0 while the restored
X offset remains covered by original8 assertion. ASan/UBSan passes0.08s;
fresh absent-g92-axis-proof74 executes both outcomes at ngc_params344,
previously1/2. No private state added, CORE/helper edit, new case or allowance.
Current successor named/probe/G92 changes remain outside f6da420. Single
refresh of existing40034582551 confirmed in_progress but coverage artifacts
not yet published; fetch helper stopped on missing lock, not a firmware/CI
failure. Do not restart or duplicate the live run. No new full/hosted gate.

# Named absent-axis positions and corrected registry assumption - 2026-10-24

Source inventory confirms current ngc_named_ro_param registers _abs_a through
_abs_w unconditionally, and by-ID dispatch handles each valid entry. Earlier
progress wording that called these names conditionally registered was wrong;
corrected that sentence. Extended existing metric/inch absolute-position cases
through ordinary name lookup: absent A/W return0 while real X remains25.4mm
or1inch. No invented names, enum forcing or axis-map mutation. Both ASan/UBSan
pass0.06/0.07s. Same-source named-absent-axis-proof74 records both outcomes
at ngc_params193, previously1/2: one new supported outcome. No CORE/helper
edit, exception, extra cases or full/hosted run. Keep with captured-probe
recovery as successor work outside pushedf6da420.

# Captured probe parameter recovers inactive coordinate record - 2026-10-24

Extended existing numbered_probe_coordinates_read_original_inactive_work_system.
Read captured G55 probe position while G54 active, corrupt stored G55 via the
NVS byte API, and require public5061 to return0 on the failed coordinate read.
Capture ID/800-step position and active G54 offset1 remain unchanged. Readback
validates repaired G55 zero record; next query returns machine10 relative to
that repaired zero, not active G54. Rewriting saved G55 offset4 restores probe
result6. Original assertion retained. ASan/UBSan passes0.07s; isolated
probe-coordinate-recovery-proof74 records ngc_params211 read-error arm,
previously missing. No CORE/helper edit, new allowance or new case. Keep as
successor work outside pushedf6da420/queued40034582551; no full/hosted run.

# Parameter/storage/realtime-reset cumulative gate passed - 2026-10-24

One new safety-door coolant-delay RESET case and seven strengthened existing
I/O/regex/numeric/NGC/rotation cases cover unlabelled-port lookup, literal
setting-prefix matching, startup separator compaction, absent-axis positions,
G28/G30 independent CRC recovery and ordinary/rotated G55 recovery. Public
workflows and existing configurations reused; no CORE/shared fixture edit,
new allowance or source exclusion. Full ASan/UBSan4365 passes58.92s; strict
summary4349clean/16known/0recovering diagnostics/0failed/skipped. Evidence
batch74-parameter-reset-delivery-{build.log,tests.log,results.xml,summary.log}
in build-asan. Unchanged Python helpers not rerun. CORE remains clean2e165a1.

Previous exactbc84ad2 run40032608243 now all five jobs terminalsuccess; locks
and exactly seven coverage stages0 verified. Refreshed badges/current inventory
to17479/17756lines98.44%,12567/13834outcomes90.84%,277raw lines/1267outcomes.
This new parameter/reset batch is outside that measurement until its hosted
report. Full supported objective stays active; no merge or overlapping PR.

# G55 parameter CRC recovery in ordinary and rotation builds - 2026-10-24

Extended two existing cases. Ordinary inactive G55 query repairs bad CRC to
zero, validates the repaired record, preserves active G54 and accepts a later
rewrite. Rotation build reads both stored X and rotation, returns0 for absent
A, repairs bad G55 CRC when queried through rotation5250, validates zero data
and reads restored rotation after rewrite. Original assertions retained. Both
ASan/UBSan pass0.07s each. Separate work-system-recovery-proof74 profiles
show all outcomes at ngc_params325 ordinary,322/323 rotation; old report had
3/4,2/4,1/2 respectively: four missing supported outcomes now exercised.
No private maps or enum forcing, CORE/helper edit, extra cases or allowances.
Keep with I/O/regex/reset/numeric/numbered-home successor batch; no repeated
full gate or new hosted run for this small extension.

# Numbered G28/G30 queries repair corrupt records independently - 2026-10-24

Extended numbered_home_parameters_read_distinct_g28_and_g30_records. Preserve
normal saved/home/absent-axis controls, corrupt one stored record byte via NVS
driver API, query its public numbered parameter and require0 recovery. A fresh
coordinate read validates the repaired CRC/zero data; the other saved home
record is unchanged. Public write restores the original values and subsequent
query succeeds. Repeat independently for G30. Existing storage recovery policy
is exercised, not a new invented failure rule. ASan/UBSan passes0.07s; fresh
home-parameter-recovery-proof74 covers all four outcomes at286 and298 versus
previous3/4 each: two newly exercised read-error outcomes. No CORE/helper
edit, extra case, allowance or full/hosted run. Existing hosted40032608243
source/coverage/GCC succeeded; Clang live at last single refresh. Keep local
parameter/I/O/regex/reset/numeric changes as one successor batch.

# Portable numbered work-position reads for absent axes - 2026-10-24

Extended existing numbered_work_position_combines_offsets_and_tracks_modal_units.
Keep ordinary X work/tool/local offset and inch conversion assertions; read
public numbered A5423 and W5428 on the actual three-axis configuration before
and after G20. Both supported numbered IDs return zero without indexing an
absent physical axis. No invented named registry entries, axis-map changes or
private enum calls. ASan/UBSan passes0.07s. Fresh absent-axis-position-proof74
shows both ngc_params200 outcomes (previous1/2): numbered work_position calls
_relative_pos for all nine exposed slots, the named registry is also unconditional in current CORE; its absent-axis
absolute fallback is covered by the subsequent named-parameter extension. No CORE/helper edit, allowance or full/hosted run;
keep with local I/O/regex/reset/numeric successor batch.

# Exactbc84ad2 coverage job and startup separator compaction - 2026-10-24

Existing run40032608243 coverage job passed with exactbc84ad2a29792c6dcc7349d4e5b6dd3c5a89f4c7/
CORE2e165a1 locks/filter verified in both artifacts; exactly seven stages0.
4364hosted:4349clean/15known/0failed/skipped.17479/17756lines98.44%,
12567/13834outcomes90.84%, net+16outcomes/identical denominators and no
lost covered lines versus40029656398. Overall run still in_progress; retain
fully green5f3e17f badges until all jobs finish. No duplicate run.

Extended existing nuts_bolts.uppercase_compaction with a space-separated
startup command list using literal | separator. Compaction returns same buffer,
uppercases G-code words and retains separator exactly: G1X2|G1X3. Public
utility assertion, not a claim of a new native strcaps caller. ASan/UBSan
passes0.10s. Isolated startup-compaction-proof74 covers all four conditional
outcomes at442 versus previous3/4. No CORE/helper edit or exception; local
successor I/O/regex/reset/compaction work remains outside hostedbc84ad2.

# Realtime RESET during safety-door coolant restart delay - 2026-10-24

Added state_machine.reset_during_coolant_restore_delay_prevents_plunge_and_cut_resume.
Start real queued X cut with M8, park after door event, close door and request
cycle start. Driver delay service delivers public RESET during100ms coolant
restore. Protocol sets abort and notifies driver once; X stays at its interrupted
position and Z stays at restore waypoint-640, never plunging to original-800.
No private state forcing or spindle descriptor mutation. ASan/UBSan passes0.06s;
isolated coolant-restore-reset-proof74 records the protocol-false short circuit
in delay_sec at nuts_bolts333, absent from previous3/4 outcome coverage.

Initial fixture lacked mandatory driver_reset callback; repaired locally. Reset
flag is consumed normally, so assert abort/driver notification rather than flag
persistence. This fixture stops at realtime abort and does not execute grbl_enter
warm initialization; it cannot assert coolant shutdown during that later phase.
Removed that premature output assumption, not a firmware regression assertion.
No CORE/shared fixture changes, known-bug allowance or full/hosted run. Keep
with successor I/O/regex work for a substantial cumulative batch.

# Literal setting-prefix dollar in public regex - 2026-10-24

Extended existing regex.literal_metacharacters with ^$110=.*$ matching the
actual setting-record form $110=500.000. It rejects different setting111 and
a prefixed non-record line. Dollar inside the pattern is literal; final dollar
remains the end anchor. Original literal plus/question-mark controls retained.
ASan/UBSan passes0.08s; isolated settings-regex-proof74 covers all four
conditional outcomes at regex34 versus previous3/4: last measured regex
outcome now exercised. This is the public utility contract, not a claim that
a native CORE parser currently uses this regex filter. No CORE/helper edit,
new case, allowance, full gate or hosted dispatch. Keep with successor I/O
lookup work outside pendingbc84ad2/40032608243.

# Public unlabelled output lookup covers optional description - 2026-10-24

Extended existing ioports.find_output_by_description using its valid modern
driver. Keep description callback and original assertions. Public
ioport_set_description clears output1's optional xbar description with NULL;
public get_info confirms absent label. Reverse description searches skip that
port, still find output0's label and reject missing text; numeric lookup still
finds output1 and both outputs remain unclaimed. No direct descriptor mutation,
legacy claiming capability invention or absent modern setter callback. Previous
withdrawn legacy exploration remains withdrawn. ASan/UBSan passes0.06s.
Fresh unlabelled-port-proof74 covers all four Clang conditional outcomes at227;
exact hosted GCC report previously had5/6 total (including its additional call
outcomes). The missing NULL-description short circuit is now exercised; do not
compare raw GCC/Clang branch identities. Initial proof parser assumed every
following row was a branch; fixed to parse branch rows only. No CORE/helper
edit, allowance or full/hosted run. Successor work outside pendingbc84ad2.

# Search/report/rotary cumulative delivery gate passed - 2026-10-24

Two new cases and four strengthened existing cases cover literal punctuation
search/restart, analog-only unclaimed-port catalogs, legacy probe full/extended
reports, real rotary homing followed by an unlimited-axis jog, and primary
hard-limit IRQ behavior with rotary exclusions enabled. Existing configurations
and callbacks reused; no CORE/shared fixture edits, exceptions or exclusions.

Full build and ASan/UBSan4364-case gate passed76.85s; strict summary0:
4348clean,16known,0recovering diagnostics,0failed/skipped. Evidence
batch74-search-report-rotary-delivery-{build.log,tests.log,results.xml,summary.log}
in build-asan. Fresh CORE fetch unchangedclean2e165a1. Isolated profiles show
new supported outcomes; hosted aggregate gain remains unmeasured. Current
badges/snapshot are exact fully green5f3e17f/run40029656398, not this new batch.
PR28 remains open/frozena9f355c; no overlapping PR or merge. Keep full goal
active after delivery and continue independent work while hosted checks run.

# Remaining stream lookup fallback reviewed - 2026-10-24

Traced all four native connection_is_up call sites. Serial candidate insertion
precedes lookup; disconnect selects a retained predecessor. Network handoff
queries the selected hal.stream, whose callback is normalized on successful
selection. Recorded bounded native-caller TODO for terminal fallback277; no
live callback clearing, mismatched private identity or speculative defect test.
Existing next-batch string/report/homing/limit work remains local and validated
by isolated proofs. No CORE edit, duplicate CI, full suite or percentage gain
claimed from this review. Current fully green checkpoint remains40029656398.

# Hard-limit positive control under rotary exclusion - 2026-10-24

Extended existing eight_axis.hard_limits_skip_only_configured_rotary_axes_when_requested.
Retain public rotary/hard-limit setting, rejected/ignored rotary events and all
unchanged-state assertions. Then issue a real X limit interrupt under the same
mask: last event becomes X, EXEC_RESET is requested, Alarm_HardLimit is queued
and idle position remains trusted. Added mandatory driver control reader and
explicit public idle precondition (shared parser fixture starts in check mode).
ASan/UBSan passes0.07s; isolated rotary-limit-control-proof74 shows both
mask-gate outcomes at machine_limits93, previously1/2. No CORE/shared fixture
edit, allowance, extra case or new full/hosted run. Keep in cross-module local
search/report/motion successor batch, outside fully green5f3e17f.

# Exact5f3e17f checkpoint fully verified - 2026-10-24

Run40029656398 completed success, all five source/GCC/Clang/coverage/Results
summary jobs terminalsuccess. Exact harness5f3e17fd7fc5a4722e9a9ff1a05d682d88dc5e37,
CORE2e165a1ac4c74be8e68971972c6577775d856b05 and filter locks already
verified in both artifacts; exactly seven coverage stages all0.4362hosted
cases4347clean/15known/0failed/skipped.17479/17756lines98.44%,
12551/13834outcomes90.73%, net+15outcomes/no lost lines on same source.
Refreshed README badges and current gap/known-bug snapshot, keeping old audits
pinned. Current local string/analog catalog/legacy probe/unlimited rotary jog
work remains outside this head and needs cumulative validation. No duplicate
CI dispatch or merge; full supported objective remains active.

# Real homed unlimited rotary-axis jog - 2026-10-24

Added boot_eight.homed_rotary_axis_without_travel_limit_accepts_jog. Configure
A as rotary, travel0, A-only homing cycle and jog-soft-limits enabled; actual
serial $HA then $J=G91A20F100 emits230 homing pulses plus exactly1600 jog
pulses. Physical endpoint1790, system1590steps and parser19.875 agree with
the homing reference. Other axes emit no pulses; sender reports no errors.
No forced homed bits or private limits call. Fixture now observes actual jog
start/finish before allowing EOF exit and services jog timer interrupts. Initial
all-axis homing lock correctly rejected jog; initial premature EOF generated
reset alarm. Both were fixture mistakes, not CORE defects. Normal bounded
polling guards retained; ASan/UBSan passes0.07s. Isolated
unlimited-rotary-jog-proof74 records machine_limits864 homed travel0 skip.
No CORE/shared fixture edit, exception or new full/hosted run; next-batch case
remains outside pushed5f3e17f.

# Current residual inventory refreshed from exact coverage job - 2026-10-24

Recomputed every per-source missing outcome count from40029656398 XML; totals
277raw missing lines/1283outcomes agree with17756-17479 and13834-12551.
Updated COVERAGE_GAPS top/table to exact5f3e17f/CORE2e165a1 measurement, with
explicit overall/GCC pending status; preserved historical pinned audit sections.
One live status refresh: source, Clang and coverage terminalsuccess; GCC still
in_progress. No badge change, duplicate dispatch or claim of full overall pass.
Existing local successor search/catalog/probe cases remain outside this report.

# Legacy probe full-status compatibility - 2026-10-24

Extended existing realtime_probe_trigger_is_reported_as_pin_state. Preserve
normal query assertion, then issue full status with a legacy driver callback
and no registered multi-probe inputs. Triggered probe reports exactly P; after
release a held control input reports exactly H, with no stale I/J/K markers.
Acquired multi-probe flag stays false. ASan/UBSan passes0.07s, no CORE/helper
edit or exception. Isolated legacy-probe-full-proof74 records current1443
branch outcomes; full status evaluates the inner unacquired-provider arm.
Added subsequent extended query as well: exact H marker remains and acquired
stays false. Fresh legacy-probe-extended-proof74 verifies the missing outer
1443 extended-and-unacquired false outcome (branch5 taken1). Initial full-only
profile bypassed that outer condition; it was not evidence of this new outcome.
Keep with local string-search and analog-only ownership cases for cumulative
validation, outside pushed5f3e17f. No full gate/hosted dispatch for this case.

# Exact pushed checkpoint coverage job verified - 2026-10-24

Existing run40029656398 coverage artifacts downloaded for exact harness
5f3e17fd7fc5a4722e9a9ff1a05d682d88dc5e37 and CORE
2e165a1ac4c74be8e68971972c6577775d856b05. Both source locks and
core/.*\.[ch]$ filter match; exactly seven stages all exit0. Coverage job
counts4362:4347clean,15known,0failed/skipped. Measured17479/17756 lines
98.44%,12551/13834 outcomes90.73%. Against same-source40024613962, net+15
covered outcomes with identical denominator and no newly lost/covered lines.
Coverage result is verified; overall run still in_progress at inspection.
Do not call all jobs green or refresh success badges until terminal compiler
and Results summary checks. No duplicate dispatch. Later local string-search
and analog-only catalog cases are outside this pushed head/report.

# Analog-only bank build report tracks public plugin claims - 2026-10-23

Added report.build_info_tracks_analog_only_bank_as_plugin_claims_ports. Real
analog driver registration advertises AUX IO0,0,2,2; claiming each physical
input through ioport_claim changes report to0,0,0,2; claiming both outputs
removes AUX IO entirely. No analog output or PWM configuration occurs during
reporting/claiming. Reused existing analog driver callbacks and build-info
initialization. Initial fixture omitted required ATC reader and retried physical
port0 twice; repaired to existing build fixture and physical ports0/1. Neither
was a CORE defect; no exception/assertion weakening. ASan/UBSan passes0.08s.
Isolated analog-catalog-proof74 covers6/8 outcomes at report1193 versus5/8
hosted40024613962, proving at least one new outcome; exact union awaits hosted
aggregation. Keep with local search cases for substantial next batch. No CORE
edit, full suite or new hosted dispatch.

# Independent motor metadata contract review while CI runs - 2026-10-23

Actual run40029656398 remains in_progress on exact5f3e17f: source success,
coverage/GCC/Clang live. No duplicate run or restart. Continued source/case
review of secondary motor metadata; existing tests already cover initial rotary
option, axis mappings and optional prior providers. Remaining runtime rotary
transition lacks a native registered option setter: only enum/field and three
stepper2 reads exist in current CORE. Recorded bounded plugin-contract TODO
instead of changing private state to force wrapper conditions. Existing local
string-search improvements remain next-batch work with conservative minimum
nine source-matched additional outcomes. No CORE edits or new test allowance.

# Literal punctuation in public string search - 2026-10-23

Extended existing bounded and unbounded case-insensitive search cases with
Spindle {rpx} {RPM} labels. Literal braces survive case folding, wrong closing
punctuation does not match, a partial-match restart finds the second label,
and bounded matching stops at the requested five-byte prefix. Prior assertions
remain. Both ASan/UBSan cases pass0.09s each, no CORE/helper change or new case.

Separate isolated profiles in label-search-proof74 exercise10/10 outcomes at
strutils68,104,113 and9/10 at76. Exact old hosted40024613962 had8/10,7/10,
7/10 and8/10 respectively: at least nine additional previously missing outcomes
are now exercised. Old XML lacks per-outcome identities, so do not claim an
exact union count for76 until hosted aggregation. No percentage/badge change.

Pushed cumulative checkpoint5f3e17fd7fc5a4722e9a9ff1a05d682d88dc5e37 has
actual hosted handle40029656398, queued when captured; never duplicate it.
These new string cases are local successor work, outside that measured head.
Full supported objective remains active.

# Provider/pendant/spindle/RTU/device cumulative gate passed - 2026-10-23

Six new cases and five strengthened existing cases span zero-port providers,
pendant modal/report hooks and input/output handoff, spindle registration
capacity/retry, asynchronous CRC/timeout recovery, sender statistics resets,
device registration allocation recovery, drained reads and failed-open recovery.
Reused host configurations/fixtures; only two exact calloc wrapper targets added.
One new confirmed failed-open reservation regression retains correct assertion
with a narrow WILL_FAIL and dated KNOWN_BUGS evidence. No CORE changes.

Full build and cumulative ASan/UBSan gate passed4362 in69.17s. Strict summary
passed:4346clean,16known,0recovering diagnostics,0failed/skipped. Evidence:
batch74-provider-rtu-device-delivery-{build.log,tests.log,results.xml,summary.log}
in build-asan. No unchanged Python helper rerun. Fresh CORE fetch remains
2e165a1ac4c74be8e68971972c6577775d856b05, clean. Exact source-matched isolated
profiles record the intended new outcomes; hosted gain still unmeasured.
Latest complete report40024613962 remains98.44%lines/90.62%branches.
Full supported-coverage objective remains active after this delivery checkpoint.

# Confirmed device failed-open reservation leak - 2026-10-23

Public device open claims UART2, then one scoped file-wrapper calloc failure
returns NULL. Allocation recovery cannot reopen UART2: passthru was set before
allocation and remains reserved. Separate UART3 opens/writes/closes correctly;
exact allocation/claim counts and final correct retry assertion establish cause.
Raw ASan/UBSan reaches final retry != NULL failure with no sanitizer diagnostic.
Added dated KNOWN_BUGS explanation/fix/removal guidance and one exact WILL_FAIL
known_bug allowance. Three-case affected group passes with that one expected
failure,0.32s total. Isolated device-open-recovery-proof74 confirms both
allocation outcomes at122 and exact raw failure; adds one missing outcome
versus hosted40024613962. Initial proof referred to127; corrected against
the actual generated profile before recording this result. No CORE edit or
blanket suppression. Defect is nonblocking; cumulative provider/pendant/
spindle/RTU/device batch still needs its one full delivery gate.

# Device registration recovery and drained UART read - 2026-10-23

Added fs_device.registration_allocation_failure_preserves_existing_uart_and_allows_retry:
one scoped calloc failure rejects a second device without claiming it; existing
UART still opens/writes/closes; retry registers the new UART and it opens/writes/
closes normally. Reused calloc_failure_host and added only this exact target
to its link wrapper list. Extended existing read_byte_count with an extra read
after draining the UART: returns0, does not call the driver reader again, and
preserves the destination sentinel. Both ASan/UBSan cases pass0.05s each.
Grouped isolated device-lifecycle-proof74 shows both outcomes at fs_device47
and150, two missing outcomes versus hosted40024613962. No CORE/shared fixture
edit or new exception. Keep with local pendant/spindle/RTU batch; no repeated
full gate or hosted run. Current whole-objective completion remains unproven.

# Sender statistics lowercase reset - 2026-10-23

Extended existing statistics_reset_reports_then_clears_counters with a second
real RTU transaction that receives a bad CRC, followed by $MODBUSSTATS=r.
The lowercase command reports TX1/CRC1 before clearing; a subsequent query
reports both0. Original uppercase success/reset controls retained. Public sender
dispatch preserves argument case, so this exercises a distinct supported path.
ASan/UBSan passes0.07s; isolated rtu-stats-reset-proof74 verifies the lowercase
condition at547, missing from exact hosted40024613962. No CORE/helper changes,
new case, exception, full suite or hosted dispatch. Keep cumulative local batch.

# RTU unobserved error recovery coverage - 2026-10-23

Added corrupt_crc_without_exception_observer_releases_bus_for_next_reply.
Two ordinary received frames independently corrupt low/high CRC bytes; no
optional exception callback is installed. Neither reaches the packet observer,
sender statistics show two CRC errors and zero timeouts, and a following
valid reply completes with exact payload. ASan/UBSan passes0.05s. Isolated
rtu-crc-optional-proof74 shows all four comparison outcomes at214 and absent
exception observer at218: two additional outcomes versus hosted40024613962.

Extended existing callback-free transaction case with an actual missing reply
between its successful unobserved and observed requests. Normal scheduler ticks
expire the timeout, bus becomes idle, no callbacks fire, and the following
valid observed reply succeeds. ASan/UBSan passes0.07s; isolated
rtu-unobserved-timeout-proof74 confirms line182 executes its missing absent
timeout-hook outcome. Existing successful lifecycle assertions retained; count
updated from two to three actual requests. No CORE/shared fixture edits or
new allowances, no full gate/hosted dispatch. Keep with provider/pendant/spindle
registration work for cumulative delivery; hosted percentages remain unchanged.

# Spindle name rejection/retry adds supported settings outcome - 2026-10-23

Added multi_spindle.oversized_driver_name_rejects_registration_without_consuming_id.
Public driver registration rejects a 100-character name without consuming ID1
or altering the primary registration. A shorter retry receives ID1; public
selector metadata is exactly primary,secondary and both driver configs activate
successfully. ASan/UBSan passes0.08s. Isolated spindle-name-proof74 executes
settings.c3701 both ways (two accepted, one rejected), covering the missing
capacity-rejection outcome. Proof initially assumed LLVM branch numbering in
the opposite order; corrected to verify both positive counts without assigning
meaning to branch numbering. Executable assertions establish acceptance/rejection.
No CORE/helper edit or allowance; no full/hosted run for this small addition.
Keep with local provider/pendant cases for the next cumulative batch. Hosted
percentages remain98.44% lines/90.62% branches pending a complete report.

# RAM residual ownership audit - 2026-10-23

Matched all ten partial RAM source branches against exact40024613962 XML:
eleven missing outcomes, zero missing lines. Traced allocation/open ownership,
refs-limited close/unlink, predecessor membership and directory wrapper contracts.
Recorded each count and native invariant in COVERAGE_GAPS, retaining all raw
outcomes. No malformed-handle tests, CORE edits or exclusions. Existing
nonzero-truncate defect regression remains intact. This resolves the next
selection decision: further RAM case padding cannot reach these guards through
valid native handles; move to another supported module. No full gate/hosted run.

# UTF-8 remaining outcome audited - 2026-10-23

Confirmed exact hosted utf8.c139 false outcome remains missing. Earlier
range rejection bounds the conversion to four bytes; independent exhaustive
integer check across all 0x110000 accepted numeric inputs confirms maximum4.
Recorded source proof in COVERAGE_GAPS; retained raw denominator and existing
boundary/rejection tests. No CORE edit or manufactured test. Current local
provider/pendant cases remain outside measured98.44%/90.62% head. Continue
independent supported gaps before cumulative validation.

# Stream/settings/tool checkpoint fully verified - 2026-10-23

Run40024613962 terminalsuccess with allfive source/GCC/Clang/coverage/Results
summary jobs green on exact35bcc9a/CORE2e165a1. Locks/filter and seven stages0
verified.4356coverage cases4342clean/14known/0failed/skipped. Refreshed badges
and inventories to17479/17756 lines98.44%,12536/13834 outcomes90.62%;277raw
missing lines/1298outcomes. Same-source old/new hit inventories verify no lost
covered lines and net+8outcomes with unchanged denominator. No new run for docs.

Local zero-port-provider extension, actual parser-to-pendant default observer
case and optional primary RX handoff remain outside this measured head. Keep
accumulating independent supported modules before the next full/hosted gate.
Source review of settings group discovery found a NULL-settings-table guard;
no ordinary native zero-setting metadata-only provider contract established,
so do not invent one just to hit that guard. No new exception or CORE edit.
Full supported line/branch objective remains active, not achieved by this run.

# Pendant optional-hook proof; I/O candidate withdrawn - 2026-10-23

Two public pendant coverage binaries exit0. Isolated mpg-optional-hooks-proof74
shows absent prior modal observer631 and registration observer774, plus absent
primary receive-disable on enable831/disable851. Actual parser reports and
input/output handoff assertions pass. Keep these local next-batch outcomes
separate from current measured/hosted35bcc9a.

Investigated optional unlabelled I/O lookup. Legacy fixture does not advertise
explicit claiming, required by ioports_enumerate; added numeric lookup assertion
therefore tested an unsupported fixture capability. Withdrew only this turn's
extension, restoring exact HEAD source and rebuilding the original passing
case. No assertion weakened or known-bug allowance added. Modern adapter's
setter veneer also assumes a callback; no malformed modern driver test added.
Continue reachable supported gaps without unrelated fixture machinery. CORE
unchanged; no repeated full gate or duplicate hosted run.

# Pendant handoff with optional primary receive-disable absent - 2026-10-23

Added mpg_handoff_without_primary_receive_disable_restores_input_and_output.
Prepare driver-owned primary UART without disable_rx before public registration;
register normal bidirectional pendant, enable MPG, verify pendant owns input
and receives replies while serial receives nothing, disable MPG and verify
original reader and sender output restored. Public mode flags agree throughout.
No callback removed from an active stream and no private MPG state set.
ASan/UBSan passes0.07s. Targets stream.c831/851 absent optional primary hook;
registration also has no optional plugin observer by default. No CORE/helper
edit, exception or new full/hosted run. Keep with the local provider/modal tests
for a substantial batch. Exact35bcc9a hosted40024613962 last verified live
with source/coverage successful and GCC/Clang running; do not duplicate it.

# Public mount review avoids unsupported defect claim - 2026-10-23

Reviewed remaining listing/routing candidate against actual native mount
callers: only/dev,/embedded,/ram in CORE. Nested-parent contract not established;
recorded bounded TODO evidence instead of adding a speculative WILL_FAIL or
assuming arbitrary external hierarchy semantics. Existing supported hidden/
immediate-child and direct-path tests remain intact. No CORE edit/exclusion.
Local zero-port/pendant authoring remains active; continue independent supported
gaps rather than padding duplicate directory tests. Latest measured snapshot
remains fully green8b13bc7/40021882976, with35bcc9a coverage job verified and
its full compiler checkpoint pending at last check.

# Latest coverage job and default pendant observer configuration - 2026-10-23

Exact35bcc9a/CORE2e165a1 coverage job40024613962 passed; both source/filter
locks and exactlyseven stages0 verified.4356cases4342clean/14known/0failed/skip.
Measured17479/17756 lines98.44%,12536/13834 outcomes90.62% (net+8outcomes,
unchanged denominator against prior40021882976). GCC/Clang still live at last
check; no overall-green claim or successful-run badge refresh yet.

Local default pendant modal case now also configures the optional plugin
on_mpg_registered observer absent BEFORE public registration. Fixture observer
is optional, not a required driver callback. Public registration succeeds and
installs modal handling; all original G20/G21 realtime output and unchanged-
report suppression assertions remain. No observer calls expected in this board
configuration; existing separate tests retain positive observer checks. ASan/
UBSan passes0.06s. Targets stream.c774 in the same coherent default-no-observer
workflow; no extra test count, CORE/private stream edit, exception or full gate.
Keep these local changes distinct from measured35bcc9a head.

# Grouped provider/pendant branch proof - 2026-10-23

Both updated coverage binaries exit0 with isolated provider-pendant-proof74
profiles. stream.c110 records normal nonempty and ignored zero-port provider
outcomes (1/2executions respectively); stream.c631 absent prior modal observer
executes on both actual G20/G21 realtime notifications. This confirms the two
missing supported outcomes locally. Existing tests cover present observers;
no callback is removed after registration to force a path. No aggregate claim.

Exact35bcc9a hosted40024613962 verified still live with source green and GCC,
Clang,coverage running. Keep its checkpoint separate from the local provider/
pendant authoring. No duplicate run, full-suite gate, CORE edit or new exception.
Continue other supported modules for a substantial cross-module delivery.

# Pendant modal reporting without a previous observer - 2026-10-23

Added mpg_parser_reports_modal_changes_without_previous_observer. Existing
fixture's default modal observer is NULL (asserted, not cleared). Public
Setting_StatusReportMask512 enables parser reports, public pendant registration
installs its handler, G20 plus realtime status emits correct pendant GC modes.
An unchanged next report emits no duplicate modal update; G21 restores metric
report content. EXEC_GCODE_REPORT behavior checked through public clear helper.
ASan/UBSan passes0.08s. Targets stream.c631 default absent prior observer through
normal reporting rather than invoking its private wrapper. No CORE/helper edit,
exception or full/hosted run. Keep with the local zero-port provider extension.
Exact35bcc9a hosted40024613962 remains independently active at last verified
state; no new aggregate percentage claimed for local authoring.

# Hosted handle and zero-port provider capability control - 2026-10-23

Single exact35bcc9a2e540c4bd28bbbd5bc88672c21d5568d8/CORE2e165a1 hosted
checkpoint accepted after duplicate/hourly checks (two prior runs). Actual
run40024613962 is in_progress:
https://github.com/petervanderwalt/Unit_tests/actions/runs/40024613962
Saved batch74-35bcc9a-hosted-handle.json. Do not redispatch or create workers.

Extended existing flags_reflect_registered_uart_capabilities: normally register
an optional provider with zero ports before UART claim and again while claimed.
Public flags/handler remain intact, close releases actual registered UART once,
and capability flags remain available afterward. ASan/UBSan passes0.07s.
Targets stream.c110's ignored empty-provider outcome without private registration
state or extra test-count padding. Local for next batch, outside40024613962;
no CORE edit, exception, aggregate claim or new full gate. Continue independent
supported coverage while hosted jobs run.

# Stream/settings/tool-storage cumulative gate passed - 2026-10-23

Full4356-case ASan/UBSan gate passes67.64s; strict summary4341clean/15known/
0failed/0skipped, no recovering sanitizer diagnostics. Evidence prefix
batch74-stream-settings-tools-delivery-{build.log,tests.log,results.xml,summary.log}.
Clean CORE2e165a1 unchanged. Four new cases plus three strengthened existing
cases cover serial transmit-count handoff, Telnet from disconnected serial,
WebSocket/Bluetooth reconnect availability, optional UART receive-disable,
web password replacement length, and non-tool NVS sync preserving tools.
Local isolated profiles verify stream391/397/403/409/558, settings3507 and
nvs_buffer371 supported outcomes. No new exception or denominator configuration.

README now distinguishes parameter-disabled cases on older supporting CORE
from omitted cases when current CORE forces parameters on. No unsupported
configuration is claimed executed. Refreshed measured snapshots still refer
to fully green8b13bc7/40021882976, not current unmeasured authoring. Deliver this
coherent three-module batch; one hosted checkpoint after duplicate/hourly-limit
checks. Full meaningful supported coverage remains active, not completed.

# Buffered ordinary update with persistent tool configuration - 2026-10-23

Added tool_table.buffered_build_information_update_preserves_tool_records in
the existing N_TOOLS=4 host variant. Persist tool1 radius2.5/Xoffset1.25, sync,
then call public settings_write_build_info and sync only that dirty region.
Exactlyone additional physical write targets build info; persisted text CRC
reads correctly and tool identity/radius/offset remain unchanged. No tool-data
dirty bits or extra tool writes. ASan/UBSan passes0.07s. Targets nvs_buffer.c371
false outcome when a real non-tool update occurs in a tool-enabled build.
No forced dirty flags, new core variant, helper change, exception or CORE edit.
Keep with local stream/settings batch for its cumulative validation boundary.

# Fully verified storage/UART checkpoint and local optional-RX proof - 2026-10-23

Allfive jobs of exact8b13bc7/CORE2e165a1 run40021882976 now terminalsuccess,
including GCC/Clang and Results summary. Verified source/filter locks, seven
stages0 and4352coverage cases4338clean/14known/0failed/skip. Refreshed badges,
KNOWN_BUGS measured snapshot and complete inventory:17479/17756 lines98.44%,
12528/13834 outcomes90.56%;277raw missing lines/1306outcomes. Exact same-source
+8outcomes/no lost lines already proven. No new run merely for these docs.

Local UART-without-disable_rx coverage binary exits0; optional-uart-proof74
shows stream.c558 optional callback absent on both close/reclaim cycles. This
is newly executed local next-batch coverage, not part of the measured report.
Keep local stream/settings changes separate until cumulative gate/delivery.
No CORE edits, new exceptions, duplicate hosted job or worker.

# Optional UART receive-disable callback - 2026-10-23

Added uart_without_receive_disable_can_be_closed_and_reclaimed with a driver-
owned stream copy configured before public registration. It omits disable_rx
but provides normal claim/release/handler callbacks. Open115200, verify live
handler, close/release, reclaim9600, verify handler and close again: exact
claim/release totals and no receive-disable calls. All driver flags change
through fixture driver callbacks; no CORE stream mutation. ASan/UBSan passes
0.08s. Targets stream.c558's omitted optional callback. No shared helper change,
exception, source edit, aggregate claim or new hosted/full gate. Keep with the
existing stream/settings improvements for next substantial batch delivery.

# Storage/RTU coverage job gains eight branches - 2026-10-23

Exact8b13bc7/CORE2e165a1 coverage job40021882976 passed; both source/filter
locks and allseven stages0 verified.4352cases4338clean/14known/0failed/skipped.
Measured17479/17756 lines98.44%,12528/13834 outcomes90.56%;277raw missing
lines/1306missing outcomes. Same-source comparison against40018600731 has
zero lost covered lines and exactly+1covered outcome at modbus69,modbus_rtu160,
vfs638/698/827/829/875/912 (total8, unchanged denominator). Saved comparison
JSON. GCC/Clang still live at lastcheck; do not update successful-run badges
or call overall checkpoint green yet. This validates the prior local proofs.

Current local password test coverage binary exits0, settings.c3507 allsix
condition outcomes executed: web/nonweb, same/different length, equal/different
placeholder text. Evidence password-length-proof74. This and stream handoff
improvements remain NEXT-batch work, outside measured8b13bc7. No duplicate run,
CORE edit, exception or premature aggregate claim for local changes.

# Existing web password update case covers longer value - 2026-10-23

Extended existing plugin_password_store_rejects_web_placeholder_without_overwriting_saved_value
with a valid10-character replacement while webui_connected is true. Existing
8-character replacement and exact PASSWORD_MASK rejection remain. Assert new
value saved/notified, reads masked over web, original label unchanged, rejected
placeholder preserves the final value, and serial readback returns final value.
Save/change totals advance from2 to3 because of one actual accepted update.
ASan/UBSan passes0.08s. Targets settings.c3507's web-connected/different-length
outcome; original same-length non-placeholder was already covered and not
re-added. No new test count, dependency, CORE edit, exception or aggregate claim.
Keep with local stream cases for the next cross-module delivery batch.

# Bluetooth branch proof and PR scope check - 2026-10-23

Isolated Bluetooth coverage binary exits0. bluetooth-reconnect-proof74 shows
stream.c409 both prior-console outcomes once, complementing local391/397/403
proofs. Keep the stream batch local; no full gate or aggregate update yet.

Read-only PR inventory confirms onlyPR28 is open, non-draft, frozen on
coverage-batch-73 a9f355c35717006f497754d1acc421cf5b141670. Do not merge or
change its head, nor create another cumulative master-targeted PR duplicating
its unmerged scope. Authorized successor74 continues with pushed8b13bc7 and
local stream improvements; preserve the existing review boundary. Exact-head
hosted40021882976 remains live with source green and compiler/coverage jobs
running at last check. No duplicate job or new worker; continue independent
supported-coverage work while it runs.

# Network handoff proofs and Bluetooth existing-case extension - 2026-10-23

Grouped isolated coverage runs of local Telnet/WebSocket cases exit0. Evidence
network-reconnect-proof74 shows Telnet397 disconnected-console path executed
and WebSocket403 both availability outcomes once. Existing baseline already
covers connected Telnet. No aggregate percentage update from these profiles.

Extended existing Bluetooth welcome case, preserving original welcome and
connected-console announcement, then reconnecting after driver-reported serial
disconnection. Bluetooth still welcomes its client and broadcasts status there
without writing to serial; clean disconnect after serial recovery. Targets the
separate stream.c409 handler. ASan/UBSan passes0.09s; no new case count, private
state mutation, CORE edit or exception. Keep all stream changes local for the
next substantial cross-module batch. Exact8b13bc7 hosted40021882976 was still
live on last refresh; no duplicate checkpoint/full-suite run or fresh coverage
claim. Continue independent supported workflows while it runs.

# Existing WebSocket welcome case extended to reconnect - 2026-10-23

Retained the original connected-console announcement and new-client welcome
assertions, then extended the same case: disconnect WebSocket, let serial driver
report disconnected, reconnect WebSocket through public stream_connect. New
client still receives firmware welcome, disconnected serial receives nothing,
broadcast routes only to live client, and clean disconnect works after serial
returns. ASan/UBSan passes0.10s. Targets stream.c403's prior-console-down outcome;
no extra case count, CORE edits, private connection mutation or exception.

Exact8b13bc7 hosted40021882976 was last verified live with source successful and
GCC/Clang/coverage running. This existing-case extension and the two new local
serial/Telnet workflows are outside that head. Accumulate next substantial
batch; no duplicate hosted dispatch or fresh aggregate percentage claimed.

# Serial-counter proof and disconnected-serial Telnet handoff - 2026-10-23

Isolated stream-tx-counter-proof74 coverage binary exits0; stream.c391 takes
both outcomes once (new counted driver plus fallback during normal cleanup).
This confirms a missing branch in the prior report without fixed-count polling
or an invented callback timing window.

Added telnet_handoff_from_disconnected_serial_preserves_live_output: driver
reports base serial disconnected, public stream_connect accepts live Telnet,
no announcement is sent to the disconnected endpoint, replies/broadcast go
only to Telnet, and reconnection/disconnect restores serial output. Base
identity and realtime command handler remain correct. ASan/UBSan passes0.08s.
Targets stream.c397's disconnected prior-console outcome. No private list
mutation, CORE edit, exception or new full/hosted run. Both stream cases stay
local for the next batch, outside active exact8b13bc7 run40021882976.

# Hosted handle and serial driver transmit-count path - 2026-10-23

Single exact8b13bc70eaf96040eeda5137be27620074776bc7/CORE2e165a1 dispatch
accepted after duplicate/hourly checks (two prior runs in rolling hour). Actual
run40021882976 is in_progress:
https://github.com/petervanderwalt/Unit_tests/actions/runs/40021882976
Handle saved in batch74-8b13bc7-hosted-handle.json; do not redispatch or poll
unchanged state repeatedly. Continue independent authoring while it runs.

The no-transmit-count fallback was already covered by existing serial tests.
Added the complementary driver-provided count path: register serial callback
before public network-to-serial stream_connect, observe drained-count query,
no fixed100ms fallback delay, correct active serial announcement and subsequent
output routing, then clean disconnect. Focused ASan/UBSan passes0.08s. Targets
stream.c391's other outcome; no private connection mutation or arbitrary timing
window. This new case is local for the NEXT batch, outside40021882976. No CORE
edit, exception, new aggregate claim or additional full/hosted gate.

# Storage/RTU cumulative gate passed - 2026-10-23

Full4352-case ASan/UBSan gate passes77.01s on clean CORE2e165a1. Strict
summary4337clean/15known/0failed/0skipped; no recovering sanitizer diagnostics.
Parsed original JUnit confirms new lookup regression reaches final rejected
assertion with stale/panel.nc only after initial-cache control and retry pass.
All shared RTU fixture cases included; pending_tx_bytes defaults0 as before.
Evidence: batch74-storage-rtu-delivery-{build.log,tests.log,results.xml,summary.log}.

Batch adds six public storage/RTU workflows and strengthens optional Modbus busy
reporting. One correct new VFS regression has exact WILL_FAIL and dated bug
entry; no CORE edit, diagnostic suppression or source exclusion. Commit/push
coherently; subsequent hosted measurement must check exact source/config/filter
and no duplicate run. Current badges remain verified1ec72ce/40018600731 until
the new batch's full hosted checkpoint passes. Full goal remains active.

# UART drain workflow and cumulative storage/RTU gate - 2026-10-23

Added pending_uart_output_waits_for_drain_before_receiving_reply. Existing RTU
fixture now returns driver-owned pending_tx_bytes (default0 unchanged for prior
cases). Three polls observe queued output decreasing3/2/1: transaction remains
busy with one send and no reply/error callback. After driver reports0, valid
CRC reply returns1234 and transport becomes idle. ASan/UBSan passes0.05s.
Targets normal modbus_rtu.c160 nonempty TX queue; no timing race, private
transport mutation or long transmit-stall policy asserted.

Started the ONE cumulative sanitizer gate for this multi-module batch and all
shared-RTU-fixture users: session15447, batch74-storage-rtu-delivery-build.log,
then delivery-tests.log/results.xml under the same prefix. Verify the live
handle before waiting; do not duplicate. After completion run strict summary
and inspect expected failure output for the exact stale-lookup assertion.
No CORE edits or new exceptions beyond that single documented VFS regression.

# Remaining local filesystem branch proofs - 2026-10-23

Built the relative-stat and unnamed-enumeration coverage cases together. Both
exit0. Isolated stat-enumeration-proof74 profiles show vfs.c638 success/failure
once each and vfs.c827 named/unnamed outcomes once each. These complement the
RTC698, lookup912 and optional Modbus69 proofs; format recovery remains correctly
asserted with its exact aggregate contribution left to the next hosted report.
No source exclusions or denominator changes in this local group.

Read-only upstream fetch confirms no successor to tested2e165a1. CORE remains
unchanged. Do not trigger a full/hosted gate merely for this small group; retain
the storage/Modbus work, including one narrowly documented stale-lookup failure,
while adding independent supported gaps toward the next substantial delivery.

# Relative stat query survives path allocation failure - 2026-10-23

Added relative_stat_path_allocation_failure_skips_backend_and_allows_retry with
the existing size-scoped allocator fixture. After public chdir to/store/jobs,
one failed allocation of part.nc's path produces-1/ENOMEM without a backend
stat. Retrying resolves exactly/jobs/part.nc, returns123-byte metadata and
clears errno, then unmounts cleanly. No output-metadata guarantee asserted on
the failed query. ASan/UBSan passes0.10s. Targets vfs.c638's parse-failure
outcome in the verified report. No new exception or CORE edit; reuse the
existing exact-case wrapped allocator group. Continue this coherent local
storage/Modbus batch before one cumulative delivery gate.

# Latest hosted batch fully green - 2026-10-23

Run40018600731 is completed success; allfive source/coverage/GCC/Clang/Results
summary jobs verified terminalsuccess. Exact1ec72ce/CORE2e165a1/filter locks,
seven stages0 and4346coverage cases4333clean/13known/0failed/skip alreadyverified.
Refreshed badges and inventories to17479/17756 lines98.44%,12520/13834 branch
outcomes90.50%;41source rows sum277missing lines/1314outcomes. Same-source
comparison preserves zero lost lines and explicit six-new-line denominator.
Local filename-allocation regression, format/RTC/enumeration workflows and
optional Modbus busy assertion remain outside the measured head. No new run.

Reviewed sleep eligibility against existing13cases: ordinary no-power, motor
shutdown, automatic reports, hold/door states and cancellation controls already
exist. Do not duplicate them or reenter its blocking timeout with invented
callbacks merely to hit the remaining condition counters. Continue from the
current measured branch inventory; full goal remains active.

# Unnamed backend enumeration and RTC branch proof - 2026-10-23

Added drive_enumeration_skips_unnamed_backend_between_visible_drives using
normal public registration. Iterator emits first named drive, skips an unnamed
backend, retains the later named/removable drive and reaches EOF; direct path
routing to the unnamed backend still succeeds before clean unmount. Targets
vfs.c827 fs_name outcome without changing private mount lists. ASan/UBSan passes
0.09s. No new exception or CORE change. Keep in the growing storage/Modbus batch.

The prior mount/RTC case's isolated coverage binary exits0; mount-rtc-proof74
vfs.c698 records both driver read results once. Local proof distinguishes
read-failure handling from absent callback. Hosted40018600731 last checked live
with source/coverage passed and GCC/Clang running. No duplicate checkpoint,
fresh aggregate claim or small full-suite gate at this authoring point.

# RTC read failure during ordinary mount - 2026-10-23

Added mount_with_failed_rtc_read_remains_discoverable_and_allows_remount through
public vfs_mount/get_drive/unmount. Registered RTC provider first returns false:
mount still succeeds, driver calledonce, correct filesystem/path discoverable,
then cleanly unmounts. Provider recovers with valid calendar fields; remount
succeeds with second callback and same public drive identity. ASan/UBSan passes
0.12s. Targets vfs.c698 read-failure outcome without invalid clock values or
private mount state. Mount timestamps are not exposed by this API; no timestamp
value assertion or claim added. No new exception/CORE edit/full or hosted run.
Keep with local filename-allocation defect, format recovery and Modbus change.

# Latest coverage job and local filesystem proof - 2026-10-23

Exact1ec72ce/CORE2e165a1 coverage artifacts from40018600731 verify both
source/filter locks and allseven stages0.4346tests4333clean/13known/0fail/skip.
Measured17479/17756 lines98.44%,12520/13834 outcomes90.50%;277raw missing
lines/1314missing outcomes. GCC/Clang remain running at last inspection; do
not call the overall checkpoint green or update successful-run badges yet.

Same-source comparison against40015747959: zero lost covered lines, six newly
compiled and covered delta lines135-136/190-191/275-276, no previously missing
line removed. Branch coverage increases10outcomes with6new outcomes compiled;
keep denominator expansion explicit. Comparison JSON saved in build-asan.

Measured local lookup/format workflows together under filesystem-recovery-proof74:
lookup exits1 at exact final stale-result assertion, vfs.c912 both outcomes2x;
format recovery exits0 and line875's error/optional-callback paths execute.
Exact additional hosted branch gain for these local cases remains unmeasured.
No CORE edits, duplicate run or additional exceptions. Continue independent work.

# Format failure without optional remount callback - 2026-10-23

Added vfs_integration.format_error_without_device_mount_callback_preserves_error_and_allows_retry
using the existing registered driver-format fixture. A backend without optional
device_mount returns-7: API/errno preserve-7, output drain/unmount/format events
are exactlyTUF, no device callback occurs and the drive remains discoverable.
A subsequent successful format returns0 with exactTUFM events and still no
device mount calls. ASan/UBSan passes0.08s; no new exception or CORE edits.
Targets the missing false outcome in vfs.c875 after a real format error.
Keep with local filename-allocation regression and Modbus optional-busy change.
Hosted40018600731 last verified live; no duplicate run or aggregate claim.

# Stale lookup narrowed with initial-cache control - 2026-10-23

Strengthened the same VFS regression, no new case: the first long-name growth
failure returns NULL and performs no backend lookup when the static result is
initially empty. Then successful panel.nc lookup primes the buffer, and another
single growth failure incorrectly returns /panel.nc. Restored allocation still
locates the longer filename and unmounts cleanly before final CHECK(rejected).
Exactlytwo scoped realloc failures total, one in each state. Updated dated bug
entry. ASan expected-failure execution0.18s; parsed JUnit explicitly confirms
its diagnostic is the final stale-result assertion, not an earlier control.
One narrow WILL_FAIL remains; no CORE edit, sanitizer suppression or duplicate
case/full-suite/hosted run. Continue independent batch work.

# Confirmed stale filename after allocation failure - 2026-10-23

Public VFS lookup first finds panel.nc, then a longer requested filename needs
one realloc. Scoped failure returns the old /panel.nc without another backend
stat. Restored allocation successfully locates the new path; all recovery and
unmount assertions run before the final correct NULL-result assertion fails.
ASan/UBSan reports no memory diagnostic. Saved raw JUnit reproduction, dated
KNOWN_BUGS entry and one exact WILL_FAIL; no CORE edit or sanitizer allowance.
No actual wrong-file execution is claimed. Keep this local regression with
next-batch optional Modbus busy coverage; hosted40018600731 remains separate.

# Exact hosted handle and optional busy-provider outcome - 2026-10-23

Requested one exact1ec72ce541dcae207c6c22197310f562b14821d1/CORE2e165a1
checkpoint after duplicate and rolling-hour checks (one prior dispatch).
Actual run40018600731 is in_progress:
https://github.com/petervanderwalt/Unit_tests/actions/runs/40018600731
Handle saved in batch74-1ec72ce-hosted-handle.json; do not redispatch.

During hosted execution strengthened the existing optional Modbus reset case
with the normal idle query when both registered transports omit is_busy.
No private state mutation or extra case. Updated coverage binary exits0 and
isolated gcov modbus.c69 takes the omitted-handler outcome4times, absent from
the last measured report. Evidence: modbus-optional-busy-proof74. This one-line
assertion is local for the NEXT batch, outside40018600731. Sanitizer/full gates
will include it cumulatively; no fresh aggregate percentage or tiny hosted run.

# Multi-axis/report/Modbus batch passed cumulative gate - 2026-10-23

Full4346-case ASan/UBSan gate passes70.30s on clean CORE2e165a1; strict
summary4332clean/14known/0failed/0skipped, no recovering sanitizer diagnostics.
Six new cases cover the supported five-axis delta build (mixed nonzero position
conversion and independent auxiliary reversals), registered bitfield allocation
failure/retry, public legacy-RT capability changes, terminal-newline descriptions,
and optional Modbus reset with post-reset fallback. All expected failures remain
narrow; no new exception or CORE change. Evidence uses prefix
batch74-multi-delta-report-modbus-delivery-{build.log,tests.log,results.xml,summary.log}.

Current percentages remain the fully verified0237d9f report40015747959, not these
six cases/new configuration. Commit/push this coherent batch, then request one
exact-source hosted checkpoint after duplicate/hourly-limit checks. No unchanged
Python helper rerun or repeated full suite. Full supported coverage remains active.

# Registered description with terminal newline - 2026-10-23

Added human_setting_description_accepts_terminal_escaped_newline. Register the
normal plugin metadata descriptor with First/Second/Third and a terminal escaped
newline before initialization. The public human-readable query must render the
three text lines, remove escaped delimiters, avoid repeating text and leave the
setting value unchanged. Uses the existing bounded write_n fixture. Targets
report.c1818's missing empty-remainder outcome after splitting descriptions.
Focused ASan/UBSan passes0.06s. No private callbacks, metadata mutation after
registration, CORE edits, exception or new aggregate claim. Retain with the
local multi-axis/report/Modbus batch for cumulative validation and delivery.

# Optional reset branch proof - 2026-10-23

The isolated coverage build of the normal mixed-transport reset/recovery case
exits0. modbus-reset-proof74/modbus.c.gcov shows line93's two outcomes taken
2times each, matching graceful/abort resets with one handler omitted and one
present. The locked40015747959 report has only1/2 outcomes here. This is exact
local evidence for a new supported branch in the next batch, not a refreshed
aggregate total. CORE remains clean; no new exceptions or hosted dispatch.

# Exact hosted checkpoint fully passed - 2026-10-23

Run40015747959 completed successfully: allfive source/GCC/Clang/coverage/
Results summary jobs green on harness0237d9f/CORE2e165a1. Artifact source/filter
locks and allseven coverage stages already verified. Measured17473/17750 lines
98.44%,12510/13828 outcomes90.47%;4340coverage cases4327clean/13known/0failed/
0skipped. Refreshed README badges and measured KNOWN_BUGS/COVERAGE_GAPS snapshots.
No new full/local/hosted run merely for documentation. Local five-axis delta,
reporting and optional Modbus reset cases remain outside this measured head.
Continue the full supported-coverage goal; this checkpoint is not completion.

# Optional Modbus reset and post-reset fallback - 2026-10-23

Added reset_skips_transport_without_handler_and_preserves_next_transaction.
Normal registration installs an RTU transport without an optional reset and
a TCP transport with a reset handler. Graceful and abort reset choices reach
that handler exactlyonce, preserve advertised transports, and each next write
falls back from TCP to RTU with exact address/value echo and no stale exception.
Targets missing modbus.c93 outcome without changing private transport state.

Initial fixture omitted TCP's required send callback; native TCP-first dispatch
therefore faulted. This was fixture misuse, not a CORE defect. Added a valid
TCP sender that declines this RTU server and assert each fallback attempt.
All original reset/response assertions retained. Affected ASan/UBSan1/1 passes
0.07s; no exception or diagnostic allowance. Keep with local delta/report batch;
no small full-suite/hosted run and no new aggregate coverage claim.

# Current-source inventory refreshed - 2026-10-23

COVERAGE_GAPS now enumerates the exact2e165a1/0237d9f coverage-job artifact:
41source rows sum to277missing executable lines/1318missing outcomes, checked
against XML totals. Every table link uses the measured source SHA. Explicitly
marks GCC/overall checkpoint pending and retains prior fully successful run
as historical reference; README badges were not changed prematurely. New
five-axis/report cases are explicitly outside the measured head and may expand
the compiled denominator. Coverage job data remains98.44% lines/90.47% branches.
No cross-revision line-hit comparison, exclusion, duplicate run or CORE edit.

# New-source coverage job verified; GCC pending - 2026-10-23

Downloaded40015747959 artifacts and verified both exact harness0237d9f/source
2e165a1/filter locks plus exactlyseven fetch/tooling/configure/build/test/
classify/coverage stages, all exit0. Coverage job measures17473/17750 lines
98.44% and12510/13828 branch outcomes90.47%;4340 tests4327clean/13known/0fail/
0skip. Source and Clang jobs passed; GCC was still live at last inspection.
Do not call the overall checkpoint green or refresh successful-run badges yet.
New raw inventory: batch74-post0237-missing-lines.json,277missing lines.
This source changed the denominator; no cross-revision line-hit gain claimed.

Separately, local metadata recovery binary exits0 and gcov report.c1680 has
both outcomes taken once (bitfield-recovery-proof74). This confirms a missing
supported allocation/retry branch for the NEXT batch. Its case and the new
five-axis configuration are not part of40015747959. No new dispatch.

# Bitfield metadata allocation recovery - 2026-10-23

Added report.bitfield_metadata_allocation_failure_allows_complete_retry using
registered text metadata and the existing malloc wrapper scoped to this exact
case. During the public human-readable query exactlyone allocation fails:
setting identity and reboot notice remain, no option rows are invented, and
stored value remains0. A subsequent query lists both exact option/bit values
and reboot notice with no additional failure. ASan/UBSan passes0.14s; no CORE
bug or allowance added. Targets report.c1680's missing allocation outcome.

The legacy0/1/0 capability report coverage binary also exits0 and executes
report.c1033 three times. Its output assertions prove RT-/RT+ behavior; local
Clang gcov has no branch counters on that ternary, so exact hosted branch gain
is not claimed from this local profile. Evidence: legacy-report-proof74.
Hosted40015747959 was still live with source green and three compiler/coverage
jobs running. Keep these reporting cases and five-axis delta work local for
the next substantive batch; no duplicate checkpoint or aggregate percentage.

# Public legacy realtime capability reporting - 2026-10-23

Added report.build_info_tracks_legacy_realtime_setting_without_stale_capability:
public Setting_EnableLegacyRTCommands writes0/1/0 and extended build reports
must show exactly the corresponding NEWOPT RT-/RT+ prefix, reject the stale
opposite prefix, and retain the stored flag. Each query also checks the two
plugin report phases. Initial repeated queries exceeded the existing fixture's
four-callback observation buffer; reset/check its count per query, without
changing shared fixture or CORE behavior. Focused ASan/UBSan passes0.06s.
This targets report.c1033's missing option outcome on unchanged report source.

Hosted40015747959 was verified live with source job successful and GCC/Clang/
coverage running. No duplicate dispatch. New report scenario and five-axis
delta work remain local for the next cumulative batch, outside that run.
No new coverage percentage or confirmed firmware defect claimed.

# Multi-auxiliary delta paths measured locally - 2026-10-23

Added a second five-axis real-boot job: simultaneous Z-0.5/A1/B-0.5 produces
5pulses on each delta joint,80 on A and40 reverse on B. Both parser coordinates
and system_convert_array_steps_to_mpos retain distinct nonzero A1/B-0.5;
Cartesian XYZ agree with the independent symmetric geometry within0.03mm.
Focused ASan/UBSan1/1 passes0.07s. The existing return-to-zero control separately
checks160/80 auxiliary pulses, no joint movement and independent reversals.

Built both coverage binaries together; both exit0. Isolated gcov evidence in
delta-multi-proof74/proof.json confirms execution of all three new N_AXIS>4
loops: delta.c135-136 inverse transform,190-191 forward transform and275-276
segment deltas. Bodies execute426/25160/6times respectively. This establishes
real execution under the new configuration, not an aggregate gain versus a
report that did not compile it. Local CMake/configuration and two cases remain
for the next batch; exact0237d9f hosted run40015747959 does not contain them.
No CORE changes, exclusions, new exceptions or extra hosted dispatch.

# Hosted checkpoint active; multi-auxiliary delta authoring - 2026-10-23

Exact pushed0237d9f3168c42564454991593f1019dc5d1f465/CORE2e165a1 hosted
run40015747959 is active: https://github.com/petervanderwalt/Unit_tests/actions/runs/40015747959
Duplicate/head and rolling-hour checks preceded its single dispatch; actual
run handle saved in batch74-core2e165-hosted-handle.json. Do not redispatch.

While it runs, added local host_core_delta_multi (DELTA_ROBOT=1,N_AXIS=5)
and boot_delta_multi module reusing the existing real-boot/pulse fixtures.
One streamed job drives A+1/B-0.5 then A-1/B+0.5:160/80 observed pulses,
independent exact zero endpoints, no delta joint pulses or position changes,
and original Cartesian height. This reaches upstream's N_AXIS>4 auxiliary
loops omitted by existing three/four-axis builds. Focused ASan/UBSan1/1
passes0.06s; no private transforms or CORE edits. This new configuration/case
is local for the NEXT cumulative batch and is not part of run40015747959.
No aggregate coverage claim until the exact source/configuration report exists.

# Cumulative sanitizer gate complete - 2026-10-23

CORE2e165a1ac4c74be8e68971972c6577775d856b05 remains clean. Full4340-case
ASan/UBSan gate finished149.11s: only two exact delta version expectations
failed after upstream changed0.05 to0.06. Updated both exact strings; affected
2/2 pass0.12s case time. Original full and repair XML retained separately.
Combined report replaces only those two original failed case nodes after
asserting exact name-set agreement and4340 total cases. Strict summary passes:
4326 clean/14 known regressions/0fail/0skip, no recovering sanitizer allowance.
Evidence: batch74-core2e165-{delivery-results,version-repair-results,combined-results}.xml
and batch74-core2e165-strict-summary.log. No repeated full suite. The earlier
session67275 is terminal, not an active wait. No new-source hosted coverage yet.

# Mixed delta/auxiliary job and cumulative gate — 2026-10-23

Added a real-boot streamed G91 job combining Z-0.5/A1 and Z+0.5/A-1 on the
four-axis delta build. Observed allthree delta motors return to0 with10pulses
each and auxiliary A returns0 with160pulses; Cartesian XYZ/A return to their
original coordinates. Focused ASan/UBSan passes0.08s on clean upstream2e165a1.
No forced homing flags, private transforms or production edits.

Started the single cumulative build/full sanitizer gate for this batch and
upstream update: session67275, batch74-core2e165-delivery-build.log, then
batch74-core2e165-delivery-tests.log/results.xml. Last verified build remains
active and progressing through4194 compilation/link steps; no result claimed.
Do not launch a duplicate gate. After completion inspect unexpected failures
and run strict scripts/summary.py tests on the JUnit result before delivery.
Corrected the obsolete M6 guard-review row; explicit check-mode message
ownership still needs verification after upstream moved that cleanup arm.

# Upstream2e165 fixes verified — 2026-10-23

Fetched and selected clean upstream2e165a1ac4c74be8e68971972c6577775d856b05;
no CORE edits. Rebuilt six exact affected cases. Direct execution preserves
all original assertions and exits0 for both same-block lathe plane regressions,
real-boot delta auxiliary80-step regression, rejected reverse motor nudge,
stale unary-expression output classification, plus the M6 check-mode control.
Raw results: batch74-core2e165-raw-regressions.json. Removed five obsolete
WILL_FAIL blocks and their four resolved KNOWN_BUGS sections; tests remain.

The measured coverage snapshot remains explicitly pinned to51b58594/run39996777540.
Do not compare shifted source line numbers or claim new-source percentages until
its cumulative report exists. New delta auxiliary transformations/segmentation
and check-mode message cleanup need affected-module validation and the next
substantial full gate, alongside the uncommitted RAM/parser/motor batch.

# Finite-motor focused measurement — 2026-10-23

The coverage build of the finite1000-step cruise workflow exits0. Isolated
profiles and gcov are retained in finite-cruise-proof74. Public wrapper line501
executes16 times, but this local compiler attributes the inline condition to
stepper2.h rather than emitting branch counters on the wrapper line. Therefore
do not claim an exact new hosted outcome at501 from this local file alone;
compare the cumulative hosted report using its own compiler later. Existing
finite/infinite cruise assertions remain correct. Reviewed file-stream/probe
fallback candidates against native callers; no synthetic callback removal or
closed-reader state added just to hit defensive branches. No full/hosted rerun.

# Finite auxiliary motor cruise observation — 2026-10-23

Added finite_move_reports_cruise_then_stops_at_exact_endpoint using the existing
secondary_stepper_host public motor API and polling clock. A1000-step move
starts noncruising, reaches100 speed while still short of its endpoint, finishes
at exactly1000 observed output pulses/position, reports noncruising when idle,
and emits no pulse on another poll. Existing cruise observers use infinite
moves; this targets the finite State_Run outcome of st2_motor_cruising, whose
hosted source line501 has only1/2 outcomes. No forced motor profile state.
Focused ASan/UBSan1/1 passes0.05s. No CORE changes or new exceptions; keep with
the RAM/parser batch. Exact new coverage awaits cumulative measurement, with
no new aggregate claim, full-suite run or hosted dispatch at this checkpoint.

# Accumulated parser branch evidence — 2026-10-23

Strengthened existing string_replace_grow with a shorter replacement (no stale
suffix), repeated final-entry deletion and reuse; strengthened the boolean
setting macro with public inch/metric changes and ngc_float_decimals checks.
Focused ASan/UBSan2/2 pass0.18s combined case time. No new exception.

Built all four changed/new parser scenarios together in the coverage build.
They exit0; isolated gcov under parser-branches-proof74 proves both outcomes
for existing missing branches at985 (short replacement),1065 (empty cleanup),
1209/1218 (registered nonnumeric provider), and the omitted-X outcome at1338.
The earlier hosted baseline has missing outcomes at all five sites. This is
local branch evidence, not an aggregate percentage update. Unit precision
assertions pass; no per-line gcov branch claim is made for1193. The short-packet
RAM proof separately covers both previously missing203/208 outcomes. Preserve
all work for the next substantial batch; no tiny full gate or hosted dispatch.

# Numeric macro with registered text provider — 2026-10-23

Added builtin_setting_macro_leaves_text_provider_unchanged using the existing
public plugin registration fixture. G65P1Q1001S123 selects a valid string setting:
label/password remain unchanged, no provider save/change callback occurs, and
_value_returned stays0. A following G65P1Q13S1 succeeds with value1 and changes
the numeric report-units flag, confirming parser recovery. This targets the
nonnumeric outcomes at ngc_params.c1209/1218 from the locked hosted report;
no arbitrary metadata or private calls. Focused ASan/UBSan1/1 passes0.08s.
No new exception or CORE change. Local batch now includes two parser cases and
the strengthened RAM packet workflow; no full/hosted gate for this small group.
Aggregate percentages remain the last verified39996777540 measurement.

# Default packed-coil G65 workflow — 2026-10-23

Added builtin_modbus_macro_defaults_packed_write_to_one_coil using the existing
registered blocking Modbus fixture and public G65P7 parser commands. Consecutive
F15 writes omit X and toggle A1/A0: exact slave/function/address, default count1,
byte count1, payload, request length and completion result2 are asserted. This
targets the omitted-X outcome at ngc_params.c1338, reported only2/4 outcomes in
39996777540, without injecting private macro arguments. Focused ASan/UBSan1/1
passes0.05s. No CORE change or new exception. Keep with the short-packet RAM
scenario for the next substantial cross-module delivery; no full/hosted gate
or new aggregate percentage claimed at this authoring checkpoint.

# Short-packet upload accumulation — 2026-10-23

Strengthened the existing chunked RAM upload scenario: split its initial13-byte
packet into consecutive6/7-byte packets, preserving the same full5159-byte
payload and readback/seek/lifetime assertions. This exercises normal buffered
accumulation before large-packet flushes, previously absent from the hosted
branch report at fs_ram.c203/208. Focused ASan/UBSan passes1/1; the separate
coverage binary also exits0, with local gcov evidence under short-packet-proof74.
No new test-count padding, CORE changes, full gate or hosted dispatch. Keep
this local change with the next substantial cross-module delivery batch;
aggregate coverage remains the last measured hosted report.

# Native setting guard accounted for — 2026-10-23

Completed the current-source NULL-value reporting audit: all eight native
setting arrays (162 descriptors, including conditional alternatives) have
non-NULL values; the 52 function tokens resolve to CORE definitions. Plugin
registration rejects missing values. Recorded the limited proof for
report.c450-452 in COVERAGE_GAPS without adding invalid metadata tests or
excluding lines. Corrected the audit-only format-string/directive flag.
Coverage remains the measured98.44% lines/90.40% branches from39996777540;
this source review does not add executed coverage. Full supported coverage
remains active. No new suite run or hosted dispatch for documentation.

# Hosted cross-module checkpoint verified - 2026-10-23

Run39996777540 fully succeeded on exact480ac7e/CORE51b58594: source, GCC,
Clang, coverage and the new Results summary job all passed. Both artifact source
locks match and all seven coverage stages exit0.4,336 hosted cases=4,318 clean,
18 known regressions/0failed/skipped. No new-source or partial-report claim.
Measured17,464/17,740 lines98.44%;12,497/13,824 outcomes90.40%. Same source/filter
as39986380812; exact comparison gains10 lines/7 outcomes and loses no lines.
README/KNOWN_BUGS snapshot and complete raw inventory refreshed only now.
Remaining276 lines/1,327 outcomes, with no source exclusions.

The Results summary executed successfully with stored measured totals. Its
public logged-out GitHub page exposes job success but hides job-summary content;
no logged-in rendered-content claim is made. Local rendered preview and80 helper
checks cover the visible tables and unavailable/partial/failure handling.
Continue supported remaining-gap work; passing checkpoint is not completion.

# Combined RAM/spindle/delta delivery gate passed - 2026-10-23

Full4,336 ASan/UBSan cases pass with strict summary:4,317 clean/19 documented
regressions reproduced/0 failed/skipped and no recovering sanitizer allowances.
Evidence: batch74-ram-spindle-delta-delivery-{results.xml,tests.log,summary.log}.
No second full run was needed. Eighty reporting helper checks already passed
on the final Python changes, including the requested visible workflow summary.
CORE remains unmodified51b58594. All five new cases and four strengthened API
cases are included. Exact fatal matchers preserve two correct RAM shrink
regressions; ordinary next-upload recovery passes. Targeted profiles demonstrate
ten missing baseline lines, but global coverage remains the prior hosted result.

Commit/push this coherent cross-module batch on74, then request one hosted run
pinned to51b58594 after duplicate/rate checks. Never restart or duplicate an
accepted/live exact-head run. New workflow Results summary will display coverage
and clean/known/failure counts; no PR merge or CORE patch is authorized.

# Cross-module supported-gap batch ready for delivery gate - 2026-10-23

Added a normal fine +/-1% spindle override scenario using registered paired PWM
providers, native public0.5s delay and M3S6000->M3S1000 job commands. Both changes
immediately reach1010/1000RPM without stale delayed writes or secondary-spindle
output. No scheduler saturation, fabricated callback timing or active-pointer
mutation. Sanitizer case passes0.28s, batch74-fine-override-results.xml.
Public delay was configured before M3, respecting setting writes shutting down
spindles;0.1s was correctly rejected as below the public minimum, not a CORE bug.

A real-boot/homing delta scenario sets public cuboid flags2, validates an interior
point, rejects +X/-Y points outside the configured cuboid, then accepts the
interior again with unchanged actual motor counters/position. No forced homed
bits. Sanitizer case passes0.30s, batch74-delta-cuboid-results.xml.
Isolated non-sanitized profiles confirm spindle_control636 and delta599; source,
case hashes and baseline39986380812 are recorded in
batch74-spindle-delta-line-proof.json. With eight RAM lines, ten baseline raw
gaps now have direct local runtime evidence; no aggregate percentage inferred.

Accumulated batch: five new cases across RAM/spindle/delta plus four strengthened
mount/settings cases and the exact memory-diagnostic reporting change. Eighty
reporting helpers pass, including compact fatal output and aggregate visible
coverage/failed-test summaries. One combined full sanitizer/strict pre-push gate
now validates the shared reporting change and this cross-module batch. No source
edits or repeated full run per individual case. Existing hosted39986380812 is
terminal success; its98.39/90.35 remains the measured global baseline.

# Complete new RAM shrink branches covered locally - 2026-10-23

Added one ordinary low-memory shrink/recovery scenario using the existing scoped
realloc fixture: shrink returns-1, handle closes cleanly, consumed job is removed,
and the next upload reads back byte-for-byte with correct EOF. No data-retention
policy is imposed on the failed shrink. Sanitizer case passes0.30s; evidence
batch74-ram-shrink-recovery-results.xml. Isolated non-sanitized profiling also
passes and reaches261/262/263, complementing the five lines from the two correct
prefix regressions. All eight baseline missing RAM-file lines now have direct
local workflow evidence in batch74-ram-prefix-line-proof.json; no global gain is
claimed until a future coherent batch is hosted.

Current-source routing review also accounts three unregistered/TBA Modbus
diagnostics lines and two dormant null-spindle RPM callback lines, without
private calls, invalid IDs or removing code from coverage. Full-source inventory
retains those lines and keeps historical audits separate.

This local group has three new RAM cases plus four strengthened mount/settings
cases and tested exact-diagnostic reporting. Keep it local while accumulating
further work; no full gate/push/hosted run for these three cases alone.
CORE remains clean51b58594; prior hosted39986380812 remains fully successful.

# Exact-source coverage measured; independent RAM routes validated - 2026-10-23

Hosted39986380812 is fully successful: source/GCC/Clang/coverage/diagnosis all
terminal success at2dc0101/CORE51b58594, matching locks and all seven stages0.
17,454/17,740 lines98.39%;12,490/13,824 outcomes90.35%;4,331 cases4,315 clean,
16 known,0 failed/skipped. README/KNOWN_BUGS snapshots refreshed only after this
whole-run success. Full raw inventory now accounts286 lines/1,334 outcomes.
Historical CORE50f audits are explicitly separate; source changes move lines and
denominator, so no old/new line-number-set gain claim is made.

Two local RAM shrink routes now share correct prefix/lifetime assertions:
committed file and pending upload. Both exact sanitizer wrappers and strict
summary pass0.44s (batch74-ram-prefix-pair-results.xml); correct assertions after
the fatal read cannot execute. Isolated unsanitized coverage proof confirms five
currently missing lines247/256/257/258/259 execute; each executable exits1 at
retained-prefix assertion. Exact case/helper hashes and source/report pins:
build-asan/batch74-ram-prefix-line-proof.json. No new aggregate percentage claim.

A prospective normal-mode M6 jog-cancel variant was withdrawn as duplicate:
boot.cancelled_manual_tool_jog_returns_to_wait_then_completes_acknowledged_change
already exercises that public cancellation transition. The exploratory fake UART
also lacked its mandatory cancel_read_buffer callback; its fault is not a CORE
bug. Remaining state-machine line502 is deferred-alarm emission, not the
already-covered return-to-tool-wait branch. Do not add duplicate cancellation
cases or force a pending alarm merely to cover it. All existing tests retained.
CMake registrations regenerated after withdrawal:4,333 current cases, no stale
exploratory registration. Continue a substantial cross-module batch; no new
hosted dispatch/full local gate.

# RAM retained-prefix regression and public return contracts - 2026-10-23

One new ordinary RAM upload/shrink/seek/read regression confirms a five-byte
ASan overread in fs_read184 after fs_truncate256 on clean CORE51b58594. Correct
assertions retained with one exact named WILL_FAIL/known_crash wrapper and dated
KNOWN_BUGS entry; no CORE edits. Unsanitized coverage build independently exits1
at the retained-prefix memcmp assertion, not a fixture or startup failure.
Raw/classified XML: batch74-ram-shrink-{raw,known}-results.xml; classified strict
summary passes with one known reproduction, zero unexpected failures/skips.
The matcher requires exact memcpy caller and allocation frames; compact output
retains them within CTest limits and full raw output remains in the log.
Changed reporting helper tests77 pass (batch74-ram-shrink-reporting-tests.log).

Strengthened three existing mount/retry lifecycle cases for new bool results;
source detection retains older void-API compatibility. Extended existing $60
persistence test to all four new action values. All four affected sanitizer
cases pass0.35s in batch74-mount-actions-results.xml; no duplicate cases added.
These local changes are after pushed2dc0101; keep accumulating a substantial
cross-module batch before another full gate/push/hosted checkpoint.

Hosted39986380812 coverage job passed at exact2dc0101/CORE51b locks, all seven
report stages0,4,331 cases=4,315 clean/16 known/0failed/skipped. GCC/Clang still
running when inspected; whole run is not yet verified successful. Artifacts
fetched for next-work ranking; no README badge refresh or old-source line-number
gain comparison. Coverage denominator changed with upstream source.

# Source51b delivery validation complete - 2026-10-23

All three scoped fixture repairs pass sanitizer execution0.40s and strict summary
(batch74-core51b-fixture-repair-results.xml). Combined with the initial4,331
source51b gate142.82s, no unexpected failure remains unresolved. Preserve initial
full XML and repair XML; do not describe the initial full run as entirely green.
Five new workflow cases since c9952ea cover normal tool-change/door interlock,
accepted spindle broadcast overrides and all independent M2/M30 action policies.
Fifteen resolved regression allowances removed;17 remain on this Windows build.
No CORE edits, source exclusions, repeated full gate or unchanged helper reruns.
Next delivery: cumulative branch74 checkpoint, one CORE51b-pinned hosted run.
Last measured coverage stays98.37% lines/90.33% outcomes on historical CORE50f.

# Latest-source full gate and scoped fixture repairs - 2026-10-23

CORE51b58594 full4,331 gate finished142.82s:4,328 passed, three ordinary fixture
failures;17 known regressions reproduced, no fatal diagnostic allowances.
Maximum-length named CALL control used premature EOF instead of executing its
valid registered file; it now reads the real SUB/body/ENDSUB stream through the
existing parser helper, preserving file/scope closure and parent argument checks.
Two long-CWD cases passed their path/stat assertions then tried to chdir into
hidden placeholder root during cleanup. They now use the existing public unmount
cleanup, which restores root automatically, preserving all target assertions.
Only these three local cases changed after the full gate; no second unchanged
full gate is warranted. Build and rerun affected cases, retain both XML reports
as combined evidence, then deliver for one exact-source hosted validation.

# Fifteen upstream fixes and new program-end workflow - 2026-10-23

CORE51b58594 direct sanitizer execution confirms fifteen unchanged regressions
now return0; cumulative exact list in batch74-core51b-confirmed-fixes.json.
Removed all fifteen corresponding WILL_FAIL allowances and resolved entries.
Both fatal diagnostic allowances are gone; manifest is empty and tests now run
directly. Remaining expected failures stay narrowly registered, including M48.

New public $60 scenario passes all four action combinations with both M2/M30,
readback, independent feed/rapid restore and G54/G55 offset behavior. Existing
multi-spindle shutdown cases retain G54 policy explicitly under the new bitfield.
The older named CALL argument control omitted the required first-pass ENDSUB;
it now completes prescan and reenters SUB before checking execution/arguments,
then checks successful EOF (OK or Handled), file closure and local-scope restoration.
Both prescan completion and the updated successful EOF return contract apply.

Affected run364 in7.73s isolated four newly obsolete allowances plus that fixture
sequence; subsequent focused cleanup execution and complete-source gate pending.
No new coverage percentage or hosted success claimed; CORE clean and unedited.

# Eleven upstream regressions verified fixed - 2026-10-23

CORE51b58594 affected-module run351 cases in23.31s identified eleven obsolete
allowances and one EOF callback return-contract change. All eleven unchanged
sanitizer executables independently returned0; exact list/evidence stored in
build-asan/batch74-core51b-confirmed-fixes.json. Removed their named WILL_FAIL
blocks, resolved KNOWN_BUGS sections and the fixed CONTINUE fatal matcher/wrapper;
correct assertions remain ordinary tests. Hidden-mount CWD is fixed; the separate
relative hidden-file access in a visible mount remains documented/expected-fail.
Existing named-macro callback control now accepts Status_Handled as well as OK,
matching upstream EOF handling; file closure and local-scope checks remain.
Shared-source initial rebuild succeeded; new scenario and fixture changes still
need the incremental rebuild/affected execution before the next complete gate.

# Upstream source update and completed prior-source gate - 2026-10-23

Existing batch74-broadcast-toolchange-delivery gate finished:4,330 tests in
152.61s, strict summary4,298 clean/32 known/0 failed/skipped. CORE50f38659 stayed
unchanged throughout. Four new local cases include normal M6 sender suspension,
physical door close/second-start interlock and accepted M48/M49 broadcasts.

Fetched and selected clean upstream CORE51b58594ce467e9c4b103fb93d1ca121e43cd15c
without production edits. Shared-source sanitizer rebuild is running; previous
coverage98.37/90.33 remains explicitly the historical CORE50f measurement.
New public $60 bitfield has independent restore-overrides/restore-G54 choices;
added one scenario covering all four values with M2 and M30, selected offsets,
setting readback and retained/restored feed/rapid percentages. Source detection
keeps this scenario unavailable on older CORE APIs. Not yet validated.
Existing multi-spindle program-end fixture now requests G54 restoration explicitly
when $60 is a bitfield, preserving its prior coordinate assertions while varying
override policy. Older Boolean-setting CORE revisions keep their prior inputs.
Do not remove resolved-bug allowances based only on source diff: execute them
against the rebuilt source first. No new hosted dispatch or PR merge.

# Accepted combined spindle broadcasts correct the old override audit - 2026-10-23

Two new public same-block cases: M3M49$-1 correctly disables both independent
speed overrides, keeps110/120% stored and permits secondary-only reenable.
M3M48$-1 accepts broadcast start and reenables feed override, but incorrectly
keeps both speed overrides disabled: actual3000/7000 vs required3300/8400RPM.
Correct regression has one exact WILL_FAIL and dated KNOWN_BUGS entry, no
sanitizer allowance or CORE change. Four affected sanitizer cases pass0.44s,
batch74-broadcast-override-known-results.xml, including existing standalone
controls. Raw batch74-broadcast-override-raw-results.xml; known output checked
to confirm the intended final assertion rather than an earlier fixture failure.

The old reachability proof considered standalone commands and missed a normal
same-block M3. Corrected both historical and latest TODO statements and the
inventory: six M48/M49 lines are reachable; only three M51 broadcast lines remain
behind its single-selector guard. They remain raw until a hosted measurement.
Local4,328 registered/32 known. Keep this new group in the next substantial batch;
no repeated full gate or hosted dispatch. Pushed c9952ea run39977472030 remains
the existing validation handle; never fold these new cases into its claimed head.

# Automatic sleep, threading cancellation and residual audit checkpoint - 2026-10-23

Measured hosted39969171772 is fully successful at b2cf02d/CORE50f38659: source,
GCC, Clang, coverage and diagnosis all passed; both source/filter locks match and
all seven report stages exit0. Hosted4,320=4,292 clean/28 known/0 failed/skipped.
17,419/17,714 lines98.33%,12,457/13,800 outcomes90.27%; zero new/lost lines and
16 new outcomes versus39961338202. README/KNOWN_BUGS snapshot refreshed only after
whole-run success. Raw remaining295 lines/1,343 outcomes; no exclusions.

Targeted Windows coverage proof (not aggregate coverage): five selected targets,
isolated short GCOV_PREFIX/STRIP99 paths. Profiles confirm seven unique formerly
missing lines: protocol354, gcode4849/4854/4856/4857, delta653 and motion_control718.
The held post-cut reset adds no raw line. Evidence includes case SHA256 hashes
and explicit uncommitted-worktree status at collection in
build-asan/batch74-targeted-line-proof.json; raw profiles/logs in line-proof74.
Overall percentages remain the hosted measurement until this batch is measured.

Six new local cases and one strengthened case after that measured head:
- Held G76: first cut completes at Z-1, four held polls preserve every motor
  counter, public reset stops spindle/driver and prevents the second cut.
  Three affected sanitizer cases pass0.40s, batch74-held-thread-reset-results.xml.
- Automatic boot sleep: public $62=1/M8 reaches idle timeout through the actual
  protocol loop and shuts down coolant/motors. Companion driver RX arrival
  cancels the timeout, executes $G/M9/$62=0 and remains awake beyond old expiry.
  Both pass0.34s, batch74-sleep-sender-recovery-results.xml; shutdown controls
  passed3/3 in0.37s, batch74-idle-sleep-protocol-results.xml. Targets protocol354.
- Stopped G33.1: running/native-unsupported control skips macro provider; M5 then
  tapping loses init error41 and calls macro331, returning39. Correct rejection
  assertions retained in one named WILL_FAIL/detailed KNOWN_BUGS entry. No motion,
  queue, encoder reset, override/scope leak observed; no executed-body claim.
  Raw batch74-stopped-tapping-raw-results.xml; three affected cases pass0.47s,
  batch74-stopped-tapping-known-results.xml. Its output verifies final expected
  assertion, not an earlier control failure. Targets real gcode4849-4857 error
  continuation; weak native support does not make that path unreachable.
- Delta fine-resolution jog: public XYZ2000step/rad settings, $20=1/$40=1,
  real XYZ homing, G0Z-300 and sender Idle wait before $J=G91X1000F100. Actual
  endpoint clips to X222.323/Y~-0.001/Z~-300.01, retains direction, passes public
  travel validation and matches parser/quantized joint position. No forced homed
  state. Two affected sanitizer cases pass0.35s,
  batch74-delta-fine-jog-final-results.xml. Targeted local profile confirms delta653
  executes once; line-proof74/delta-jog and batch74-targeted-line-proof.json.
  Initial invalid sequencing correctly rejected a jog while G0 was running;
  missing $40 also correctly rejected instead of clipping. Both fixture issues
  were corrected, with no defect exception. Abort/no-alarm checked before the
  deliberate fixture EXIT. No CORE edit or new allowance.
- Held G76 approach E-stop: actual control IRQ after four stable held polls,
  spindle/coolant/driver shutdown, four E-stop polls, physical release plus public
  reset; no encoder synchronization/cut or subsequent pulses. Abort/Alarm_EStop
  remains latched after reset. Two affected sanitizer cases pass0.37s,
  batch74-thread-approach-estop-results.xml. Local profile confirms motion_control
  718 once (line-proof74/approach-estop); the earlier post-cut phase added no line
  and was replaced during authoring, not retained as a duplicate case.
- Existing check-mode comment case now executes full G91(MSG,...) and verifies
  modal update without queue, owned message, output or plugin callback. Two
  affected cases pass0.32s, batch74-full-parser-dry-run-results.xml.

Full cumulative ASan/UBSan gate passes4,326 in161.97s:4,295 clean/31 known,
0 failed/skipped and no recovering sanitizer allowance. Strict summary passes.
Evidence: batch74-sleep-delta-thread-delivery-results.xml and matching tests/
summary logs under build-asan. No CORE edit. Unchanged reporting helpers were
not rerun. Hosted validation for this delivery is pending; no merge authorized.

COVERAGE_GAPS/TODO now source-review196 of295 raw missing lines;99 remain
unclassified. All58 settings residuals have explicit groups; typed-getter mismatch
and direct-buffer IPv4 remain caller/provider contract questions, not impossible
inputs or new defects. Registration/case audit checks eight callbacks and explicitly
excepts permanently hidden deprecated $7. Evidence:
build-asan/batch74-settings-routing-audit.json. Parser alphabet/all63 named IDs
and public override addressing also checked (batch74-parser-routing-audit.json);
no invalid-enum/forced-selector tests added. Exact subsets checked against hosted XML: unsupported homing,
validated/private dispatch guards, disabled/unrouted settings, integer-width I/O,
NVS counter/allocation invariants and backend lifecycle. Pending contracts stay
explicit; VFS NULL-path fallbacks272/779 are not declared unreachable. Fresh
CORE origin/master fetch remains clean50f38659. Audits are not measured line gain
or supported-scope completion. Continue realistic cross-module work.

# Public discovery batch full gate passed - 2026-10-23

All4,320 registered ASan/UBSan tests pass in201.64s, including30 documented
known cases (two exact fatal-diagnostic wrappers). Strict summary passes.
Evidence: build-asan/batch74-public-discovery-delivery-results.xml and matching
-tests.log/-summary.log. Eight new public workflows and four strengthened cases
span boot, settings, system help, reports, files, serial editing and I/O.
No CORE edits. Unchanged reporting helpers were not rerun. Coverage remains the
measured6ea4b5d report until a new exact-head hosted report exists.

# Expansion discovery cache and remaining-line review - 2026-10-23

A public digital-expansion registration after an earlier discovery query exposes
stale free-port counts: available totals become4, but free counts stay2.
Actual writes still route to native and expansion pins. Correct free-count
assertions remain in one narrow WILL_FAIL with dated KNOWN_BUGS evidence.
Four affected sanitizer cases pass0.55s, including that expected failure,
batch74-expansion-count-known-results.xml. No CORE edit or sanitizer allowance.
Local total4,320, eight new workflows plus four strengthened existing cases.

Reviewed remaining G-code lines before adding more scenarios. The M6 message
free arm at4260 is nested under the opposite check-mode guard; recorded the
source proof in TODO rather than manufacturing callback timing to reach it.
Measured coverage remains98.33% lines/90.15% branches. This cumulative local
batch now proceeds to its single full sanitizer/strict pre-push gate.

# Optional driver help and public homing-mode transition - 2026-10-23

New system-help workflow starts without optional services, then publishes real
pin-enumeration/stepper-status/reboot callbacks and registered digital I/O.
$HELP COMMANDS advertises $PINS/$PINSTATE/$SDS/$REBOOT without invoking hardware.
Subsequent $PINS/$SDS execute their providers, preserving no-reboot assertion.
Three affected help cases pass ASan/UBSan0.42s,
batch74-optional-service-help-results.xml. Targets system907/912/917/958.

New homing workflow uses public stores only: shared $22=1 with25/400rates,
$22=513 with distinct XYZ30/35/40 locate and450/550/650 search rates, persistence
reload, then $22=1 copies X30/450 to all axes. Per-axis metadata/stores become
disabled without notification. New shared50/700 values survive a second reload.
No direct mode/axis-setting mutation. Six affected sanitizer cases pass0.60s,
batch74-homing-mode-transition-results.xml. Targets settings1207/1234 transition
conditions that prior isolated per-axis fixtures set directly.

Local total4,319: seven new cases after measured6ea4b5d, including one narrow
EOF line-number known regression, plus four strengthened serial/passthrough
cases. No new exceptions in this group, no CORE edit, full gate, push or hosted
run. Keep accumulating the next substantial cross-module delivery. Verified
coverage remains98.33%lines/90.15%branches; these gains are unmeasured.

# Numeric UART recovery and printable sender data - 2026-10-23

New UART workflow publishes numeric TX9/RX10 pins without port prefixes and a
registered driver whose optional status is temporarily unavailable. First report
keeps correct pin/name fields and omits absent status. After driver recovery,
report includes230400baud/8N1/free state with the same numeric pins. Shared UART
fixture adds one availability flag default true; existing behavior preserved.
Nine affected ASan/UBSan UART cases pass0.75s,
batch74-uart-status-recovery-results.xml. Targets report2539/2551 outcomes.

New full-boot sender job publicly sets $39=0, saves $I=Router?~!, then queries
it. All three printable realtime characters remain literal stored build-info
bytes, verified through physical NVS/CRC readback and serial output; no error.
Existing setting passthrough case retains its $? assertions and now checks
legacy cycle-start/feed-hold bytes are returned as data without execution flags.
Four affected sanitizer cases pass0.42s,
batch74-build-info-rt-text-results.xml. Targets protocol1017 false handling via
an ordinary settings/data workflow rather than private line-flag mutation.

Local total4,317: five new cases after measured6ea4b5d (including one narrow
EOF diagnostic regression), plus four strengthened serial/passthrough cases.
No new exception beyond the documented EOF discrepancy, no CORE edits, no full
gate/push/hosted run for this small group. Continue accumulating related modules.
Verified coverage remains98.33%lines/90.15%branches at39961338202; local gains
are not measured yet and the full supported coverage objective remains active.

# Verified90% branch checkpoint and next file/provider group - 2026-10-23

Pushed6ea4b5d100244860217a46c514816532c11c016d hosted39961338202 is completed/
success: all five jobs pass, both source locks match clean CORE50f3865 and exact
filter, seven coverage stages0. Hosted4,312:4,286clean/26known/0failed/0skipped.
17,419/17,714lines98.33%,12,441/13,800outcomes90.15%: +2lines/+30outcomes
versus39955235052, no lost lines. Exact new lines motion_control772/779. Badges,
KNOWN_BUGS snapshot and asserted295rawline/1,359outcome inventory refreshed.
No claim that this checkpoint completes supported coverage.

Next local provider workflow uses the legacy API's explicitly optional NULL
pin-description setter, working get-info/claim/output/input handlers and proper
physical pin metadata. Report falls back to Aux in0/1 and Aux out0/1, leaves
output routing/value and available counts intact. Source contract ioports.h172;
no active driver pointer is nulled after registration. Targets report2663/2686
and registration's missing-optional-description paths. Existing serial edit
cases now erase repeatedly at an empty buffer before their original command,
retaining final position/query/ACK assertions; includes critical-alarm polling.
Four affected cases pass fresh sanitizer0.50s, batch74-empty-line-editing-results.xml.

New prior file-line observer workflow passes terminated implicit1/explicit42/
implicit43 and sender77 after close; every observed assignment matches its
phase, without an invented exactly-once promise. An unterminated final command
exposed a separate real diagnostic defect: G90\nG91 executes both commands but
assigns final line1 rather than2. Correct narrow regression documented/labelled
WILL_FAIL, no sanitizer allowance; raw1/expected2 evidence retained. Latest
CORE fetch still50f3865 clean. Five affected file controls pass0.39s including
one known reproduction, batch74-file-observer-known-results.xml.

Local total4,315 (three new cases, one expected defect, plus three strengthened
serial cases) after measured6ea4b5d. No new full gate, push or hosted run for
this small group. Keep accumulating supported cross-module work. CORE untouched.

# Driver/report/recovery cumulative gate passed - 2026-10-23

Confirmed repeat full ASan/UBSan gate passes4,312 in174.20s. Strict summary:
4,284clean/28known/0unexpected/0skipped, no recovering sanitizer allowances.
Evidence batch74-driver-report-recovery-confirmed-{tests,summary}.log and
results.xml. Repeat was warranted by the first gate's genuinely intermittent
CORE expression-error classification; diagnostic assertions remain intact and
one deterministic regression is narrowly expected/documented. No CORE fix.

This cumulative delivery adds ten supported workflows plus that confirmed
parser-error regression, and strengthens existing dwell, digital-config and
optional-hook cases. Nine modules, no duplicate aliases. Existing ioports
fixture return controls default true; allocator wrapping is one named test.
New known regression reproduces before allowance; two existing fatal wrappers
remain unchanged. Seventy-five reporting helpers are unchanged, not rerun.

Fresh CORE origin/master50f3865 clean, harness remotes fetched. Latest measured
successful report remains39955235052/48c9190 at98.32lines/89.93branches; this
checkpoint needs a separate exact-head report before attributing gain. PR28
remains frozen/unmerged. Commit/push current74 batch, request one hosted run
with duplicate/hourly safeguards, then keep independent coverage work moving.

# Confirmed unary error-status defect during cumulative gate - 2026-10-23

First4,311-case cumulative gate completed179.81s with one unexpected existing
malformed-unary-name failure, not a stopped process. Isolated original test
failed again. Source50f3865 ngc_read_real_value823-826 checks output finiteness
after a failed parse; ngc_eval_expression passes uninitialized values[0]. Adding
per-input diagnostics changed stack layout and all ten original correct error
assertions passed, but is not a CORE fix. Preserve that caveat in KNOWN_BUGS.

New deterministic public ngc_read_real_value regression verifies ordinary zero
output returns unknown-operation71, then retains the same assertion with a NaN
output sentinel: actual76. One exact named WILL_FAIL/known_bug, dated source/
raw evidence/removal instructions in KNOWN_BUGS. No sanitizer allowance, CORE
edit or accepted-invalid-motion claim. Affected3/3pass0.51s with exactly one
known reproduction, batch74-unary-known-results.xml. Total now4,312.

Repeated cumulative gate is justified by this unexpected failure and remaining
stack-dependent path uncertainty, rather than by the added case count. It is
running as batch74-driver-report-recovery-confirmed; retain its process handle.
Do not claim a passing full gate or new coverage until terminal evidence exists.
Independent driver/report work is retained; the confirmed defect is not a
blocker to the broader supported coverage goal.

# Catalog allocation fallback and auxiliary timer reset - 2026-10-23

New spindle-listing allocation failure/retry case uses the existing tracked
allocator only around public report_spindles. With two enabled and one unused
registered drivers, failed sorting allocation still reports every correct
machine-format entry via direct enumeration. No driver reconfiguration/output
occurs. Retry reports identical entries and frees its allocation. Narrow named
CMake wrapper registration only; five affected listings pass ASan/UBSan0.46s,
batch74-spindle-catalog-fallback-results.xml. Targets report.c2879 fallback.

New auxiliary-motor timer case starts real driver timer, emits three observed
steps, issues public mc_reset, then delivers the next interrupt from the still
running timer. It emits no extra pulse, preserves last auxiliary position,
reports zero speed and stops the timer without restarting it. No event after a
stopped timer is fabricated. Five timer/reset controls pass sanitizer0.50s,
batch74-aux-timer-reset-results.xml. Targets stepper2.c435 idle-before-tick arm.

Ten new local workflows plus five strengthened cases now total4,311. Full
cumulative sanitizer/strict gate is running in the existing process; preserve
its handle and do not restart from an observation timeout. CORE fresh fetch
remains clean50f3865; origin/upstream fetched. Next delivery needs the terminal
local result and exact-head hosted check. Verified coverage remains48c9190,
98.32%lines/89.93%branches; this ten-case group is unmeasured.

# Digital configuration failures and optional override hooks - 2026-10-23

Strengthened existing digital input/output configuration cases with driver
failure followed by retry. Both propagate false, preserve unclaimed counts and
other-pin call counts, then succeed with the same requested flags. Shared
ioports_settings fixture adds two callback-result controls defaulting true;
existing callback observations and behavior remain unchanged. Ten affected
configuration/settings-load controls pass fresh ASan/UBSan0.99s,
batch74-digital-config-recovery-results.xml. Targets ioports.c654/667 outcomes.

Existing unknown spindle/coolant override cases now first run without the
optional plugin hook: queues drain, percentages/output stay unchanged. They
then retain original forwarding checks with a registered hook and execute a
standard fine spindle increment/flood toggle, proving subsequent commands work
and the unknown hook is not called for recognized commands. Four affected
sanitizer controls pass0.55s, batch74-optional-override-hook-results.xml. Targets
protocol.c724/764's optional-hook absence. Uses existing public extension queues;
no synthetic private enum, timing window, new duplicate case or CORE changes.

Registration stays4,309. Eight new local workflows plus strengthened G82,
digital configuration and optional override cases accumulate after measured
48c9190. No new failure allowance, full local gate, push or hosted run for this
group. Current verified coverage remains98.32%lines/89.93%branches; these local
changes are unmeasured. Continue supported gaps toward full coverage.

# Measured mixed-workflow gain and independent report cases - 2026-10-23

Hosted39955235052 completed/success at48c91904d5be3930eb910f2bb84148d27c8d6b5f.
All five jobs successful. Both source locks match CORE50f3865 and the exact
core/.*\.[ch]$ filter; all seven coverage stages0. Hosted4,301:4,276clean,
25known,0failed/0skipped. Compared with39950801187 on the same denominator:
17,417/17,714lines98.32%,12,411/13,800outcomes89.93%; +6lines/+27outcomes,
no lost lines. Gained gcode134-135/1293-1294 and ioports1566-1567. Badges and
KNOWN_BUGS snapshot refreshed only after terminal success. Complete residual
inventory regenerated/asserted297rawlines/1,389missingoutcomes,41sources.
I/O reviewed-line accounting reduced30->28 after its public notification gain.

Continued authoring while hosted jobs ran. New mixed extended-probe report
workflow registers all three real probe inputs, seeds cached state by a full
report, independently asserts/releases toolsetter and primary, and checks a
stable poll emits no repeat edge. Held feed-hold input keeps the pin field
present; no cached probe-state assignment. Exact H/HJ/H/Hj/HI/Hi fields checked.
Three affected ASan/UBSan cases pass0.54s, batch74-mixed-probe-report-results.xml.
Targets report1447 unchanged-state and1450/1454/1458 conditional outcomes.

New real-motion line-number report workflow publicly stores $10=4, queues
N42X1/N43X2, verifies queued head42 wins over parser43, executes160actual X
pulses, verifies drained fallback43, then unnumbered G90 suppresses Ln field.
No fabricated position or line state. Two affected sanitizer cases pass0.43s,
batch74-motion-line-report-results.xml; targets report1354/1355.

Local total4,309: eight new cases after measured48c9190, plus strengthened G82.
These tests remain uncommitted/unmeasured for the next substantial batch. No
new known failure, CORE edit, repeated full gate or hosted dispatch. Goal stays
active;297rawlines/1,389outcomes still require coverage or supported-scope proof.

# Sender modal reporting and manual-reference status - 2026-10-23

New tool-table workflow saves tools2/3 with XYZ offsets(1,2,3)/(4,5,6), runs
G43H2 then G43.2H3 and G49 through the public parser, and queries modal output
after each. Checks ordinary G43 versus additive G43.2 without a spurious G43.1,
exact summed offsets(5,7,9), then G49/zero offsets. Existing inch drilling jobs
now query G20/G98 or G20/G99 after completion. Four affected sanitizer cases
pass0.46s, batch74-modal-tool-report-results.xml. Targets report.c809/810/813.

New manual-homing sender-status workflow publicly stores $22=41 and clears all
homing-cycle settings, executes actual X1/Y2/Z3 motion, queries incomplete H:0,
executes $H and queries complete H:1. No single-axis suffix is advertised. All
axes become referenced; logical position is zero while hardware stays at the
previous80/160/240steps, with no extra pulses/wakeup or limit enable. No private
homed-state assignment. Three manual-homing controls pass fresh ASan/UBSan0.39s,
batch74-manual-homing-report-results.xml. Targets report.c1581/1582/1584's valid
manual configuration with no switch-driven homing axes.

Registration4,307, six new cases beyond pushed48c9190 plus strengthened G82.
No new exception, shared fixture change, CORE edit or full/hosted gate. All this
work remains local and is excluded from the running4,301-case hosted checkpoint.
Keep accumulating the next cross-module group. Latest measured report remains
39950801187 at9dbcf3c; source-pinned39955235052 was last verified live, not failed.

# Inch peck drilling and inherited dwell - 2026-10-23

Two new public motor workflows cover inch conversion in canned cycles. Absolute
G83 uses G98 from0.25in clearance, R0.125in, Q0.1in and depth-0.125in. Checks
converted2.54mm pecks/3.175mm R, clipped-254step bottom and508step clearance;
next X-only hole reuses modal Q/R/Z. Two holes emit7,516Zpulses and1,524Xpulses.
Incremental G73 uses0.127mm chip-break setting with inch program R/Q/depth,
three initial holes plus two continuing without Q/R/Z. Checks1.27mm pecks,
0.635mm R, common-203step bottom and51step return;2,791Z/1,270Xpulses. No Y
pulses, alarm or abort. Fresh inch/control group5/5pass0.48s; completed modal
continuations2/2pass0.37s, batch74-inch-peck-continuation-results.xml. Targets
gcode.c3542/3599 inch conversions and3601's modal-cycle continuation outcome.

Existing G82 motor case now drills a second X-only hole without P/R/Z, retaining
0.1s dwell and depth:320totalZpulses,80Xpulses, exactly200ms. G82 controls2/2pass
0.33s, batch74-modal-dwell-results.xml. Targets gcode.c3583's continuation arm.
No new fixture, duplicate aliases, exceptions or CORE changes.

Total4,305 registered locally, four new cases since pushed48c9190 (two reset,
two inch drilling), plus the strengthened existing G82 case. No full suite or
hosted run for this small group. Hosted39955235052 remains live at exact48c9190:
source successful, GCC/Clang/coverage in_progress at last authoritative check.
Continue independent coverage; retain measured39950801187 badges until the
new run completes and its source/filter/harness locks and report are verified.

# Post-delivery G76 retract reset controls - 2026-10-23

Pushed cumulative48c91904d5be3930eb910f2bb84148d27c8d6b5f on
coverage-batch-74 after full4,301-case66.27s sanitizer/strict gate. Exact-source
hosted39955235052 is in_progress at verification; source pinned50f3865. One
dispatch only, after duplicate/hourly checks (two earlier runs in rolling hour).
No PR created or merged; PR28 remains frozen/unmerged. No coverage gain claimed.

Continued independent work with two real G76 encoder/motor reset cases. After
the first cut, reset when retract is queued prevents reposition/another pass:
position X680/Z-80 steps, pulses X120/Z80, one encoder start. After last cut,
reset prevents final radial retract: X640/Z-80, pulses X400/Z240, two encoder
starts. Both stop/reset callbacks and spindle/coolant shutdown execute once;
position is retained because axes are stopped, and no later service emits steps.
Uses the existing thread_reset_motion public realtime command/driver observer,
without private state or fixture changes. Targets motion_control.c772/779.

Initial expected X coordinates omitted the G76 I peak offset. Diagnostics and
source review corrected first-pass8.5mm/final8mm cutting radii and exact path
pulse totals; not classified as CORE failures. Fresh affected ASan/UBSan2/2pass
0.39s, batch74-thread-retract-repair-results.xml. No new allowance. These two
cases are local/uncommitted, total4,303, excluded from the running4,301-case
hosted checkpoint. Accumulate next substantial cross-module group; no new full
local gate or hosted dispatch for this pair. Goal remains active.

# Cumulative mixed-workflow delivery gate - 2026-10-23

One cumulative full ASan/UBSan gate passes4,301 cases in66.27s; strict summary
reports4,274clean/27known/0unexpected/0skipped. Both fatal known regressions
remain exact-wrapped; no new allowance or changed reporting helper. Evidence
build-asan/batch74-mixed-workflows-delivery-{build,tests,summary}.log and results.xml.

Batch adds four distinct public workflows (CSS/RPM mode restoration, unrelated
I/O setting notification, normal-spindle-only broadcast motion) and strengthens
existing integer/date/string, message ownership, eight-axis metadata and public
setting store/readback cases. Existing assertions remain. No duplicate case
aliases or CORE changes. Shared paired-PWM fixture defaults are unchanged.

Fresh CORE origin/master still50f38659db7b22f4689f3654df2d110d992bcc95, clean.
Harness origin/upstream fetched; PR28 remains open/unmerged at frozena9f355c.
Do not merge or extend it. Keep successor coverage-batch-74 for this delivery.
ReadMe/KNOWN_BUGS/COVERAGE_GAPS use fully successful39950801187 evidence;
this new batch requires its own matching hosted report before a gain claim.

Next: commit/push cumulative changes, request exactly one source-pinned hosted
run after checking the hourly ceiling and exact-head duplicates, then continue
independent supported gap work while it runs. Full coverage remains unproven.

# Optional decimal precision and registered setting readback - 2026-10-23

Strengthened existing direct and function-backed decimal getter cases. Both
retain explicit three-decimal formatting and raw numeric readback, then cover
NULL format and a format with no decimal point:12.375 renders12.4 through the
helper's default precision. Function-backed checks preserve offset1003 and
exact callback count4. Targets settings.c1908/1910. Fresh ASan/UBSan2/2pass0.49s,
batch74-decimal-defaults-results.xml.

Registered password-store case now accepts an actual eight-character password
from the web UI (same length as PASSWORD_MASK), verifies saved data and masked
readback, rejects the literal mask without another save/change, and verifies
serial readback after disconnecting the web UI. Existing non-mask-length store
remains. Reset-action case now checks selective5 and public stores/readbacks
for0/15, plus all four retention flags and exactly three change callbacks.
Targets settings.c3505's same-length non-placeholder outcome and inverted
readback bits1877-1879. Seven affected password/reset tests pass fresh
ASan/UBSan0.58s, batch74-settings-readback-results.xml.

Source audit found validate_pulse_width is an unconditional Status_OK stub on
CORE50f3865; its complete rejection logic is commented out. Added exact TODO
rather than manufacturing high-frequency rejection failures. Existing pulse
minimum and file-end driver-rate sanity controls remain intact. No new cases,
exceptions, dependencies, CORE edits or hosted run. Registration4,301 and
measured98.29%lines/89.74%branches remain unchanged until a cumulative gate.

# Marker-message cleanup and spindle-axis metadata isolation - 2026-10-23

Extended the existing gcode motion-comment ownership test with a normal
%(MSG,Program header) marker followed by G90 and a closing %. The same tracked
allocator verifies the header allocation has been released on the next block;
existing queued-motion/reset ownership assertions remain. This reaches the
public pending-message cleanup at gcode.c1293-1294 without assigning parser
state or adding another alias test. Current gc_at_exit already frees rejected
messages, so the existing parser-error control remains passing. Focused2/2
ASan/UBSan0.41s, batch74-marker-message-results.xml.

Extended the existing eight-axis spindle description case to request X-axis
steps, maximum rate, acceleration and travel after binding only A as a spindle.
All descriptions still come from the original provider; bound A descriptions
retain spindle-specific units. Targets the ordinary unbound-axis outcomes at
stepper2.c176/181/187. Five affected metadata/iterator cases pass fresh
ASan/UBSan0.48s, batch74-stepper-metadata-results.xml. Existing cross-module
metadata cases checked first; no new case count, callbacks or firmware edits.

Registration remains4,301. No new known defect/allowance. No full gate or hosted
run for this small group; accumulate with the pending cross-module batch.
Measured coverage remains39950801187,98.29%lines/89.74%branches. These additions
are local and unmeasured. Full supported coverage is still unproven.

# Mixed-machine broadcast motion and helper boundaries - 2026-10-23

New normal-only-enabled broadcast workflow uses the existing paired PWM fixture
with its registered laser left unused from startup. Global laser mode remains
valid: settings.c1131-1132 checks registered configured capabilities through
spindle_get_caps(false), which includes that registered laser. Broadcast M3/M5
must find no enabled laser, preserve the normal spindle's programmed6000RPM,
produce constant600/1000PWM throughout800actual X pulses to10mm, leave Y/Z and
unused laser untouched, then stop output. Targets gcode.c134-135 and the
no-enabled-laser branch, without changing CORE or private parser state.

The shared fixture's optional secondary-enable flag defaults true. Nine affected
paired PWM/broadcast/restore/ramp cases pass fresh ASan/UBSan0.63s, evidence
batch74-broadcast-motion-results.xml. Initial assertion incorrectly observed
set_state RPM rather than ramped PWM; replaced with actual emitted PWM and
programmed RPM checks. Initial synchronized stop exposed missing stepper
callbacks in this planner-only fixture, repaired using existing motor observer;
no CORE defect or allowance claimed.

Existing integer rejection case now checks both overflow conditions with
4294967296 and4294967300, retaining cursor/output on rejection. Timestamp case
rejects malformed separators at each field and retains valid recovery. Existing
substring cases now cover mismatch/restart, partial needle at end and needle
termination before a larger bound. Eleven helper cases pass in
batch74-helper-broadcast-results.xml; that earlier combined report also contains
the subsequently repaired broadcast fixture failure, superseded by the9/9above.
Existing crossbar AB mapping already has an eight-axis test; no duplicate added.

Registration4,301: four new local workflows beyond pushed9dbcf3c plus strengthened
existing boundaries. No new exception, CORE change, full gate, push or hosted
run. Keep accumulating a substantial cross-module batch. Measured coverage
remains98.29%lines/89.74%branches on39950801187, excluding this local work.

# Integer zero boundaries and latest measured branch checkpoint - 2026-10-23

Existing read_uint_valid now checks literal0 and a zero-padded field starting at
nonzero parser offset (X00012Y), including exact value and consumed delimiter
position. Original signed-positive/maximum controls remain. Fresh ASan/UBSan
integer group5/5pass0.44s, batch74-uint-zero-results.xml. Targets nuts_bolts.c222
leading-zero outcome; no new cases, exceptions or CORE changes. Registration
stays4,300; keep local with CSS/port/normalization work for the next batch.

Hosted39950801187 exact9dbcf3c/core50f/filter locks match; coverage/report all
seven stages pass. Hosted4,297:4,272clean/25known/0fail/0skip. Measured
17,411/17,714lines98.29% and12,384/13,800outcomes89.74%: +12outcomes, no line
changes or losses. Complete residual table now303lines/1,416outcomes. Terminal
status at refresh: completed/success. Badges updated only if completed/success.
Pending local tests are excluded from the new measurement; no fresh hosted run.

# Public unrelated I/O setting notification and complete line triage - 2026-10-23

New unrelated_setting_notification_preserves_pin_configuration_and_port_availability
stores actual X steps/mm100 then forwards that valid unrelated setting ID to
public ioport_setting_changed, as a generic driver notification can. No input/
output configuration callback runs; invert/pull/open-drain masks and unclaimed
port counts stay unchanged, while calibration remains100. Targets reachable
ioports.c1566-1567. Fresh affected ASan/UBSan3/3pass0.35s, evidence
batch74-unrelated-port-setting-results.xml. No invalid IDs/private callbacks,
new allowance or CORE edit. Registration now4,300; keep local for next batch.

COVERAGE_GAPS now accounts for all30 remaining I/O executable lines at the
measured report:18 disabled open-drain,6 unrouted private defaults,2 impossible
control masks,2 newly targeted public notifications,1 platform-dependent known
PWM wrap path and1 unresolved provider route. Source-set assertion verifies the
classification exactly covers the measured line set without overlap. All remain
in the denominator; missing branch outcomes are not declared fully classified.

# Runtime CSS/RPM snapshot modes verified and late guard explained - 2026-10-23

Two new M70/M72 controls use the real registered VFD/stepper fixture at X40.
Save G96S100D900, switch to G97S300, restore, then radial cut toX20: driver speed
rises with decreasing radius and ends at100000/(2*pi*20). Opposite mode save
restores G97S300 after G96 and holds300RPM during every pulse of the radial cut.
Both finish exactX1600steps/X1600newpulses, noY/Z motion/alarm/abort. Named modes
match actual behavior; snapshots are released afterward. No new allowances.
Fresh ASan/UBSan2/2pass0.46s, batch74-css-mode-restore-results.xml. Registration
now4,299; keep with local normalization upgrade for the next substantial batch.

Source audit explains why gcode.c573 stays uncovered despite correct mode
restoration: rpm_mode is inside the spindle prefix copied earlier at507-516;
by572 it cannot differ. Exact proof/revisit conditions in TODO. Tests deliberately
avoid the unresolved repeated-G96 S/D snapshot policy. CORE unchanged; no source
exclusion or new coverage percentage claimed.

# Compact/empty normalization added to existing case - 2026-10-23

Strengthened nuts_bolts.uppercase_compaction with compact lowercase G-code and
an already-empty string. Returned storage remains the caller's buffer and text
is correctly uppercased/terminated without requiring space compaction. Existing
spaced/whitespace-only controls remain. Targets nuts_bolts.c445's no-compaction
outcome. Fresh ASan/UBSan1/1pass0.28s, batch74-normalization-results.xml. No extra
case count, fixture/CORE edit or allowance. Registration remains4,297.

Reviewed deferred hold-alarm candidate before authoring: existing actual
active_probe_disconnect_decelerates_and_reports_alarm_before_reset already
asserts real IRQ-driven deceleration, protection alarm, stable motor position
and sender reset. No duplicate case added. Keep normalization local for the
next substantial batch; do not rerun full suite or dispatch hosted for it.

# Spindle/storage batch passed cumulative validation - 2026-10-23

Six new workflows and two strengthened date cases pass the full4,297-test
ASan/UBSan gate65.11s and strict summary:4,270clean/27known/0unexpected/0skip.
Evidence batch74-spindle-storage-delivery-{results.xml,tests.log,summary.log}.
One full pre-delivery gate only; affected fixture groups were checked during
authoring. No unchanged reporting-helper rerun, new failure allowance, source
exclusion or CORE edit. Fresh core fetch remains clean50f3865.

Batch combines RAM remount/reset lifecycle, optional secondary settings callback,
primary-only spindle state query, PWM ignore-delay settings/reconfiguration,
zero-tolerance feedback policy, one-shot G65P6 actual timing and independent date
range/no-Z/recovery checks. Shared setup options retain previous fixture defaults.
Previous hosted155e149 is fully successful with verified98.29line/89.65branch;
new batch coverage must await its own exact-source cumulative hosted report.
Deliver on74 and keep the full goal active; passing this checkpoint is not full
supported coverage completion.

# Built-in one-shot spindle wait macro exercised with actual timing - 2026-10-23

New builtin_spindle_delay_macro_skips_one_wait_then_restores_feedback_waiting
runs G65P6 through the NGC parser with a registered at-speed driver. M3S6000
starts without waiting or querying feedback; suppression is consumed. M4S6000
then waits400ms and reads feedback twice before notification, proving the next
command uses ordinary waiting. Macro scope returns0, speed/direction match the
driver and no alarm/abort occurs. Targets spindle_control.c817 using its public
command source rather than setting the runtime flag in a fixture.
Fresh ASan/UBSan2/2pass0.30s with the existing macro flag control, evidence
batch74-macro-spindle-wait-results.xml. Registration now4,297. No new allowance
or CORE change; one cumulative gate is running for this whole local batch.

Previous hosted39948391327 exact155e149 now completed/success in all five jobs.
Badges/known-gap snapshot updated to its measured98.29line/89.65branch, with
303raw lines and1,428missing outcomes. Fresh core fetch remains clean50f3865.
This does not attribute pending local changes to that hosted measurement.

# Zero at-speed tolerance uses delay without feedback polling - 2026-10-23

New zero_feedback_tolerance_uses_start_delay_without_polling_supported_feedback
registers an at-speed-capable driver with the documented disabled tolerance0.
M3S6000 waits the normal500ms, does not poll readiness (driver would report
ready only after2000ms), and notifies once; M5 stops and notifies without a new
wait or feedback read. No alarm/abort. Targets spindle_control.c823's tolerance
outcome independently of missing capability and torch bypass.
Existing ready fixture gains a default1 tolerance option applied before driver
registration; no active spindle_get fields are changed. Affected feedback/start/
stop/query group10/10 passes ASan/UBSan0.73s, evidence
batch74-zero-feedback-tolerance-results.xml. No CORE change or new allowance.
Registration now4,296. Keep with pending cross-module recovery/settings changes
for the next cumulative gate, not a full or hosted run for this individual case.

# Running-spindle query handles unused enabled-slot capacity - 2026-10-23

New any_on_with_only_primary_enabled_skips_unused_slots_without_output_changes
uses the existing registered multi-spindle fixture with only primary enabled;
secondary slot is genuinely unavailable, not disabled by pointer mutation.
spindle_is_on returns false/true/false through actual M3S5000/M5 driver output,
queries add no output callbacks and unused registered drivers receive no output.
Targets spindle_control.c958's NULL unused-slot outcome. Existing secondary-only
and all-off controls retained. Fresh ASan/UBSan3/3pass0.35s, evidence
batch74-primary-only-query-results.xml. No fixture/CORE/allowance changes.
Registration now4,295; keep with pending RAM, optional secondary callback, PWM
wait and date-parser work for the next substantial cross-module checkpoint.
No full/hosted run or new coverage percentage for this local addition.

# Supported-configuration branch gain measured - 2026-10-23

Hosted39948391327 exact155e149/core50f/filter source locks match; all seven
coverage/report stages passed. Hosted4,291cases:4,266clean/25known/0fail/0skip.
Measured17,411/17,714lines98.29% and12,372/13,800outcomes89.65%: seven extra
branch outcomes, no line changes or losses against39945588754. This matches the
configuration-oriented batch, not a new line-coverage claim. Full gap accounting
refreshed to303raw executable lines/1,428missing branch outcomes.
Overall run remains active at retrieval; successful-run badges retain the prior
fully successful run. Pending numeric/RAM/secondary/PWM changes are unmeasured.
No additional hosted dispatch, full gate or source exclusion for this update.

# Public PWM ignore-delay option changes actual start timing - 2026-10-23

New multi_spindle.pwm_ignore_delay_setting_bypasses_start_wait_and_disabling_restores_it
uses a registered normal-mode PWM driver. Public on-delay0.5s/options17 plus
public spindle_update_caps configuration refresh enables ignore_delays; M3S500
updates CW output immediately with no elapsed ticks. Public options1 clears the
option; after the same driver refresh M4S500 waits exactly500ms and preserves
commanded speed/direction. M5 stops output, no alarm/abort. No edits to active
spindle_get structures or forced internal wait flags. Targets spindle_control.c818.
Fresh ASan/UBSan2/2pass0.32s with existing options-storage control, evidence
batch74-pwm-ignore-delay-results.xml. Initial0.4s fixture setup correctly failed
validation; corrected to the documented0.5s minimum and existing multi-spindle
build exposing option bit16. Not a CORE defect or expected-failure allowance.
Registration now4,294. Keep with RAM remount, optional secondary callback and
date boundary upgrades for the next substantial cumulative gate. CORE unchanged.

# Secondary settings work without optional notification callback - 2026-10-23

New secondary_pwm_without_change_callback_preserves_primary_hook_and_setting_storage
registers the settings provider with NULL on_changed from the start. Public PWM
frequency storage/readback/reload works, the secondary callback is never invoked,
and the primary driver hook remains installed and receives a global spindle
change once. Targets spindle_control.c1348/1460's optional-callback outcomes.
The existing fixture gains a default-false setup option, not a callback removed
after registration; all existing callback-present cases keep their setup.
Fresh affected secondary-PWM ASan/UBSan group21/21pass1.20s, evidence
batch74-secondary-optional-callback-results.xml. No CORE or exception changes.
Registration now4,293. Retain with RAM remount and numeric boundary upgrades for
the next substantial cumulative gate; no new hosted request for this addition.
Hosted39948391327 exact155e149 was verified active with artifacts not yet ready.

# Repeat RAM mount preserves files and wraps driver reset once - 2026-10-23

New fs_ram.repeated_mount_preserves_uploaded_file_and_installs_reset_wrapper_only_once
uploads a real RAM job, calls mount again and verifies file metadata/storage
usage and the original reset wrapper remain. Reset invokes the real driver
callback once and removes the job; remount plus another reset invokes it only
once more, and a new upload still works. Full paths respect hidden-mount policy.
No active/open file is invalidated or private state edited. Targets fs_ram.c431's
already-mounted outcome; prior empty/populated reset controls remain distinct.
Fresh ASan/UBSan3/3pass0.38s, batch74-ram-remount-results.xml. No new allowance,
shared fixture or CORE change. Registration now4,292. Retain with the date-parser
upgrades for the next substantial batch; no full gate/hosted run for one case.
Latest measured98.29line/89.60branch still947fa2e; hosted155e149 pending.

# Date parser independent range checks and recovery strengthened - 2026-10-23

Existing datetime_valid now verifies every field for both explicitly supported
seconds terminators (Z and string end). Existing datetime_rejected adds independent
upper-year, zero-month, zero-day, minute60 and second60 failures, followed by a
valid midnight parse to prove static parser state recovers. Original invalid
leap/day/hour/old-year/text cases remain. Targets missing nuts_bolts.c397/402/
407/417 outcomes; no new executable, allowance or CORE change.
Fresh ASan/UBSan date group3/3pass0.41s, batch74-datetime-range-results.xml.
Registration stays4,291. Keep these local upgrades for the next substantial
batch, no full gate or hosted dispatch for this addition. Latest delivered
155e149 has the completed local full gate; its measured coverage remains pending.

# Supported planner/peripheral batch passed full validation - 2026-10-23

Eight new cases and one duplicate deletion pass the full4,291-case ASan/UBSan
gate153.51s and strict summary:4,264clean/27known/0unexpected/0skipped.
Evidence batch74-supported-config-delivery-{results.xml,tests.log,summary.log}.
The run stayed active and progressed during longer observations; no restart or
second full gate. No unchanged reporting-helper rerun. Fresh CORE remains clean
50f3865, matching fetched origin/master; no source/exception/denominator edits.

Batch combines documented nonzero junction floor with ordinary corner control,
alarm-cancelled sleep timer, toolsetter-first primary registration, primary
connection event scope and three passthrough prerequisite failures. Removed one
new duplicate no-table rejection alias, retaining the older stronger dynamic-
offset/queued-cut case. Build wiring adds only the supported junction-floor host
variant. Previous hosted947fa2e all five jobs succeeded; badges/inventory remain
its verified98.29line/89.60branch until this cumulative head is measured.
Deliver this coherent batch on74; full goal remains incomplete and active.

# Passthrough prerequisites preserve console and coprocessor state - 2026-10-23

Three new board/console scenarios independently reject passthrough when reset
pin is absent, USB line-state events are unavailable, or console is Bluetooth.
The missing-reset wiring is declared before registration; no registered pin
metadata is mutated to force a guard. USB/UART handlers remain untouched, no
binary data or receive cancellation occurs, and running startup tasks still
leaves copro boot/reset outputs unchanged. Existing missing-boot and non-USB
serial controls retained. Fresh ASan/UBSan5/5pass0.62s, evidence
batch74-passthru-prerequisites-results.xml. Targets all three residual outcomes
at stream_passthru.c136/160/161. No CORE change or new allowance.
Registration now4,291: eight new cases and one duplicate removal since947fa2e.
One cumulative pre-delivery gate is running; no claim of its result yet.

# Primary connection event scope and hosted completion verified - 2026-10-23

New primary_connection_events_preserve_selected_toolsetter_connection_and_input
uses three registered probes. Primary connected/disconnected notifications leave
the selected toolsetter connected, primary events work when primary is selected,
and toolsetter input remains independent after switching. Targets probe.c241's
nonprimary selection outcome. Fresh ASan/UBSan2/2pass0.36s with existing driver-
capability/primary-event control; batch74-probe-connection-scope-results.xml.
No new allowance or CORE change. Registration now4,288; five new local cases,
one removed duplicate, pending cumulative validation including the new variant.

Hosted39945588754 exact947fa2e completed/success, all five jobs verified (source,
coverage, GCC, Clang, diagnosis). Locked98.29%line/89.60%branch badges and known-
gap snapshot refreshed;303raw lines/1,435outcomes remain. The pending local
probe/sleep/junction-floor work is not counted in that measurement. No fresh
full gate or hosted dispatch for this small local addition; continue batching.

# Toolsetter-first board registers primary as default - 2026-10-23

New probe.primary_registered_after_toolsetter_becomes_default_and_preserves_independent_inputs
registers a real toolsetter input before the primary input. Toolsetter is active
initially; adding Probe_Default correctly replaces the default selection, retains
both capabilities and routes primary/toolsetter reads independently. Aggregate
reads preserve selection and explicit switches still follow the correct physical
input. Targets probe.c206's nonfirst default registration outcome. No private
state changes, invalid enum, new exception or CORE edit.
Fresh ASan/UBSan3/3pass0.41s with prior aggregate-selection and toolsetter/secondary
controls, batch74-probe-order-results.xml. Registration now4,287. Retain with
pending documented junction-floor variant, alarm-sleep cancellation and duplicate
cleanup for the next substantial gate. Latest measured98.29/89.60 still947fa2e.

# Documented nonzero junction-speed configuration validated - 2026-10-23

Added host_core_junction_floor with MINIMUM_JUNCTION_SPEED=5.0f, a documented
config.h314-324 option intended for machines that cannot dwell at corners.
This option needs its own compile configuration; ordinary builds keep default0.
Two public G-code/stepper cases reuse existing motion fixtures and public axis
acceleration stores. Near reversal uses the configured squared junction floor25
and starts from rest; right-angle control retains its computed junction speed
above25. Physical endpoints/pulses are exact: X0/Y1 with X160/Y1pulses and
X80/Y80 with X80/Y80pulses. Targets planner.c643's previously missing floor arm.
Fresh ASan/UBSan2/2pass0.44s, batch74-junction-floor-results.xml. No CORE edit,
private variable forcing or allowance. Registration now4,286 including pending
sleep-alarm case and duplicate removal. Shared build wiring change must be in
the next cumulative gate; do not infer all variants validated from these2cases.
Measured98.29line/89.60branch remains947fa2e, excluding this local configuration.

# Cumulative measured six-line gain verified - 2026-10-23

Hosted39945588754 exact947fa2e/core50f/filter locks match and all seven coverage
report stages pass. Hosted4,284cases:4,259clean/25known/0fail/0skip. Measured
17,411/17,714lines98.29% and12,365/13,800outcomes89.60%: +6lines/+18outcomes
against39940715358, no lost lines. Exact gained gcode.c1765,2472-2473,3085,
4871,4989. Source-set comparison saved under hosted39945588754; complete gap
inventory refreshed to303raw lines/1,435outcomes. No claim of universal reachability.

Overall run still in_progress at artifact retrieval; previous fully successful
badges remain until completion. Local pending sleep-alarm scenario and duplicate
removal are not represented by this report. Table-rejection duplicate did not
cover2977/2989, consistent with corrected source audit. No new hosted dispatch.

# Driver alarm cancels idle sleep timeout without late request - 2026-10-23

New sleep.pending_driver_alarm_cancels_sleep_timeout_without_late_sleep_request
uses actual M8 coolant activation and public system_set_exec_alarm(MotorFault)
from the normal realtime provider during idle sleep wait. Alarm remains pending
for normal protocol handling, input space stays100, no step pulses occur and
EXEC_SLEEP is absent both immediately and after advancing past the cancelled
timeout. Targets sleep.c47's pending-alarm outcome, distinct from reset and new
input. The test isolates timer cancellation; it does not claim to execute motor
fault shutdown itself. No private flags, task saturation or new allowance.
Fresh ASan/UBSan cancellation group3/3pass0.37s, batch74-sleep-alarm-results.xml.
Registration4,284 again: one new case replaces the removed duplicate in count,
not behavior. Retained stronger table-offset case separately passed1/1 in0.48s,
batch74-table-dedup-results.xml. No cumulative gate for these small local edits.
Latest pushed947fa2e and hosted39945588754 remain the checkpoint under test.

# Duplicate table-rejection case removed and target claim corrected - 2026-10-23

Removed the newer motion_control.table_tool_offsets_without_table_preserve_existing_cut_and_offsets.
The existing gcode.unavailable_table_offsets_preserve_dynamic_offset_and_queued_cut
already tests both G43/G43.2 rejection with stronger active-dynamic-offset
preservation and exact queued80-pulse completion. It is retained unchanged.
The new alias duplicated that coverage and does not improve the objective.

Earlier batch notes targeting gcode.c2977/2989 were too optimistic: current
50f3865 parser selects G43/G43.2 modes only with a nonzero table, so ordinary
no-table commands reject before those later guards. The existing TODO audit
was correct. No callback-time table mutation or fake test will cover them.
Deletion removes one duplicate executable; registration now4,283. No production
source, existing assertion or known-failure allowance changed. Keep cleanup for
the next coherent delivery rather than dispatching a separate hosted run.
Latest pushed947fa2e remains locally validated4,284; hosted39945588754 for that
exact head was verified in_progress. Do not report cleanup as new coverage.

# Cross-module recovery batch passed cumulative sanitizer gate - 2026-10-23

Five new workflows plus three strengthened existing helpers pass the full
4,284-case ASan/UBSan gate64.17s and strict summary:4,257clean/27known/
0unexpected/0skipped. Evidence batch74-recovery-delivery-{results.xml,
tests.log,summary.log}. No new exceptions, source exclusions or CORE edits;
fresh fetch still clean50f3865. No unchanged reporting helper rerun.

Final new pair: public Z max-rate50 rejects a1mm/rev thread at100RPM without
pulses or index acquisition; reducing spindle speed to40RPM completes two
passes at X800/Z-80 with X560/Z240pulses. A separate stopped-thread rejection
accepts user feed override110, then queues an ordinary G1 cut with
no_feed_override=false and executes its exact80-pulse displacement. This is a
passing recovery control, not a defect: runtime control bits alone were not
used to assert an observable override failure. Focused speed/stopped pair2/2
pass0.33s; ordinary-cut recovery1/1pass0.30s.

Batch also includes ordinary unsegmented sender stop/restart, modal G66.1L1
stack overflow/unwind/retry, both date-year representations and bounded-search
empty/NULL conventions. Source-only residual audits are in TODO. Deliver as one
checkpoint on74; latest measured98.26/89.47 remains39940715358 until cumulative
hosted artifacts exist. Full coverage objective remains active/incomplete.

# Stopped registered spindle rejects threading and permits retry - 2026-10-23

New ordinary M5 -> G76Z-1P1I-1J0.5K1 -> M3S100 -> identical G76 workflow uses
the registered encoder spindle and real stepper. Stopped feedback returns
SpindleNotRunning with no new pulses, planner block, index reset or alarm;
physical X800/Z0 stays unchanged. After restart, two passes complete with
X560/Z240pulses and endpoint X800/Z-80, no Y motion. Targets runtime G76 error
return gcode.c4871, distinct from earlier missing-encoder capability guards.
Fresh ASan/UBSan1/1pass0.28s, batch74-thread-stopped-results.xml. No private
callback removal, new allowance or CORE change. Registration now4,282.
Keep with pending ordinary sender-stop, modal recursion and strengthened helper
cases for the next substantial cumulative checkpoint; no fresh percentage claim.

# Residual flow/storage dispatch audit - 2026-10-23

Source-set verification finds all17 read_command assignments handled by the
ngc_flowctrl switch; unknown text exits before dispatcher default811-812.
The zero-size dirty-driver fallback at nvs_buffer.c366 likewise needs a write
to an unallocated area: every successful public allocation includes checksum
space and records a nonzero extent. Failed allocation returns0 and must not be
used as storage. Existing unknown-command and driver allocation/retry cases
already cover valid public outcomes. Exact evidence and revisit conditions in
TODO. No fake tests, exceptions, source edits or denominator exclusions.

These three raw lines are now explained rather than repeatedly pursued as
ordinary missing workflows. Current local test additions remain preserved.
Full objective remains incomplete; no completion or new coverage claim.

# Ordinary streamed linear stop and relative restart - 2026-10-23

Added motion_control.sender_stop_during_unsegmented_cut_clears_cancel_before_relative_restart.
An actual G1X20F100 starts through protocol_main_loop with a nonfull planner;
public sender STOP after40X pulses cancels input and decelerates the running
stepper. The sender then transmits G91G1X1F100 from the observed stopped position.
Exact final displacement is stoppedX+80pulses, Y/Z remain0, parser/physical
positions agree, cancellation clears and no alarm/position loss remains. Existing
stream/stepper fixture reused; no internal flag forcing, new allowance or CORE
change. This targets protocol.c350's outer-loop cancellation cleanup, distinct
from existing stops inside blocking segmented arc/drill generation.
Fresh ASan/UBSan1/1pass0.29s, batch74-linear-stop-results.xml. Registration now
4,281; keep with pending modal-recursion and strengthened helper cases for a
substantial cross-module gate. No new coverage percentage claimed.

# Bounded-search edge contract and control fallback audit - 2026-10-23

Extended existing strutils.substring_bounded with empty pattern, NULL pattern
and empty source; documented matching conventions hold without reading absent
pattern bytes. Fresh ASan/UBSan substring group3/3pass0.35s, evidence
batch74-string-boundary-results.xml. No additional executable count or allowance.

Audited ioports.c1550-1551 against crossbar's contiguous real control enum and
nonzero shifted-bit mapping: the outer function<Input_Probe gate precludes the
zero-control-mask fallback. Exact evidence recorded in TODO so it is not chased
again with invalid enum values. Raw coverage denominator remains unchanged.
Pending batch now consists of the modal-recursion case and strengthened date/
substring cases. No full gate or hosted run for this small local extension.

# Both supported date-year representations validated - 2026-10-23

Strengthened existing strutils.iso_date_format and internet_date_format cases:
tm_year124 and the helper's explicitly supported full-year2024 representation
produce identical leap-day timestamps, retaining existing NULL fallback checks.
Targets strutils.c315/354's >=1000 year-selection outcomes without adding new
cases or manufacturing oversized dates. No CORE, fixture or allowance changes.
Fresh combined ASan/UBSan3/3pass0.44s includes both date cases plus the pending
G66.1L1 recursion/overflow/recovery case, with its final diagnostic-only edit.
Evidence batch74-date-representation-results.xml. Registration stays4,280.
Keep these local changes together for the next substantial batch; no full gate
or hosted request for this small addition. Last measured98.26line/89.47branch
still belongs to39940715358, not these unmeasured changes.

# Recursive modal provider overflow and recovery - 2026-10-23

New public-parser G66.1P100A7L1 synchronous provider recursion reaches the call
stack limit via gcode.c4989. Each callback observes its own argument7 and the
next scope level; StackOverflow propagates, all modal arguments/scopes unwind,
caller#1=99 survives, and a subsequent G65P101X3 succeeds at scope1 then restores
scope0/caller99. Existing fixture reused, no private state injection, new
allowance or CORE change. Fresh ASan/UBSan1/1pass0.26s, evidence
batch74-modal-recursion-results.xml. Registration now4,280; retain locally for
the next substantial cross-module batch, not another full gate for one case.
Exploratory omitted-L nested callback reported repeats0 rather than1; explicit
L1 is requested by the retained case and the omitted default is recorded in TODO.
Latest delivered batch remains ea8cca5, fully locally validated4,279 cases.

# Configuration/recovery batch cumulative gate passed - 2026-10-23

Seven new cases pass the full4,279-test ASan/UBSan gate64.17s and strict summary:
4,252clean/27known/0unexpected/0skipped. Evidence
batch74-config-recovery-delivery-{results.xml,tests.log,summary.log}. New final
pair covers unsupported G10L2R rotation without changing saved G54/queued cut,
and a nonexistent second spindle address without changing actual running driver
output, followed by valid primary reversal/stop. Focused pair2/2pass0.32s.
Targets gcode.c3085/2472-2473; earlier batch cases target1765/2977/2989,
ngc_params.c639 and heap-only strset failure branches. No new exception, shared
fixture modification or CORE change. Fresh core fetch still clean50f3865.

Hosted39940715358 exact63965a0 is now completed/success. Measured badges and
known-gap snapshot updated to98.26%line/89.47%branch from that report, not these
seven local additions. No unchanged reporting helper rerun or tiny hosted run.
Deliver this coherent checkpoint on74; full supported coverage remains incomplete.

# Missing optional macro/tool-table services preserve real cuts - 2026-10-23

Two additional public workflows pass fresh ASan/UBSan. With the optional macro
provider absent, G67 rejects UnsupportedCommand, preserves the queued80-step cut,
keeps scope level0 and leaves no modal macro. Without a configured tool table,
G43H1 and G43.2H1 both reject UnsupportedCommand without changing offsets or
planner occupancy; the original cut reaches its exact endpoint. Existing
no-provider M98/no-table G10 fixtures establish these supported configurations.
Targets gcode.c1765/2977/2989. No new allowance or CORE change.
Evidence batch74-g67-provider-results.xml1/1pass0.27s and
batch74-no-tooltable-results.xml1/1pass0.30s. Five local cases now4,277registered;
retain for the next substantial cumulative gate, no hosted dispatch this turn.

A proposed G38.2F100 no-axis rejection failed with Status_OK and was withdrawn
rather than labelled a defect. Source axis_command gating allows modal-only
selection without a target; see TODO. Raw exploratory result remains in
batch74-probe-noaxis-results.xml; only the pre-existing current-position
rejection control passed in that exploratory pair. No new probe test registered.

# Measured checkpoint and optional output configuration - 2026-10-23

Hosted39940715358 exact63965a0/core50f/filter locks match; all seven coverage
report stages pass. Hosted4,272cases:4,247clean/25known/0fail/0skip. Measured
17,405/17,714lines98.26% and12,347/13,800outcomes89.47%: +3lines/+12outcomes,
no lost lines against39938331513. Gains ioports.c435 and stream.c412-413.
Overall run still active at retrieval; README successful-run badges unchanged.
COVERAGE_GAPS refreshed from exact XML, all309raw lines/1,453outcomes accounted.

New optional-output-config scenario changes output inversion3->0 with one pin
lacking its optional config callback; the other pin updates twice, saved mask
tracks both requests and input configuration is untouched. Fresh ASan/UBSan1/1
passes0.30s, batch74-output-config-results.xml. No allowance/CORE change.
Three local additions now4,275registered, retained for substantial next batch.

# Heap-only filename allocation failure and retry - 2026-10-23

Added strutils.strset_failed_heap_only_allocation_clears_ownership_and_allows_retry.
Public strset starts with a nulled string, rejects the first allocation cleanly,
then accepts the filename. A later rejected growth frees the owned allocation
exactly once, clears pointer/capacity without a static fallback, and accepts the
next filename on retry. Uses existing scoped realloc/free wrapping and CMake
registration; no shared fixture, allowance or CORE change. Targets previously
missing strutils.c401-402 no-base outcomes and the first-allocation failure arm.
Fresh ASan/UBSan allocation-failure group3/3pass0.37s, evidence
batch74-string-retry-results.xml. Registration now4,274; keep with the pending
registered-spindle parameter case for a substantial next delivery.
Hosted39940715358 for63965a0 was verified in_progress; coverage artifacts were
not available yet. No duplicate run dispatched and no new percentage claimed.

# Named spindle direction through registered driver output - 2026-10-23

New ordinary M4S200/M5/M3S100 workflow uses the enabled registered encoder spindle
rather than the older check-mode-only parameter fixture. Named spindle_on/cw
match actual driver on/direction and feedback RPM through reversal, stop and
clockwise restart. Axis counters remain at their setup position with zero new
pulses and no planner blocks. Targets ngc_params.c639's counterclockwise outcome.
Fresh ASan/UBSan1/1pass0.29s; batch74-spindle-parameter-results.xml. No allowance,
removed required callback or CORE edit. Keep local for the next cross-module
batch; the latest pushed checkpoint remains63965a0.

# Stream/I/O/macro/driver cumulative delivery validated - 2026-10-23

Four new cases and two strengthened existing scenarios pass the full4,272-case
ASan/UBSan gate153.75s and strict summary:4,245clean/27known/0unexpected/0skipped.
Evidence batch74-stream-io-macro-delivery-{results.xml,tests.log,summary.log}.
Batch covers null-console network reconnect, analog PWM assignment/retry, G65
bitfield persistence/error recovery, $SDS warning/fault/recovery, optional legacy
probe parameters and precise distance-mode motor nudges. No new allowances,
source exclusions, shared fixture changes or CORE edits. Fresh upstream fetch
still matches pinned50f3865; previous hosted39938331513 completed/success.
Measured98.24%line/89.38%branch remains b54a339 until the next exact report.
One cumulative gate only; no unchanged reporting-helper reruns or merges.

# Public primary-motor diagnostic query and recovery - 2026-10-23

New $SDS workflow uses a registered primary-only driver status callback: warningX
prints exact MOTORWARNING:X without a second-bank comma, then faultZ prints only
MOTORFAULT:Z, then the cleared driver status emits neither stale record. All3reads
use reset=false; query does not request a hardware reset or change idle position/
queue/alarm state. Targets report.c2910/2913/2921/2924's ordinary clear/single-bank
outcomes. Fresh ASan/UBSan1/1pass0.29s; batch74-motor-diagnostic-results.xml. No
new allowance, forced secondary capability or CORE edit. Current batch combines
four new cases and two extended workflows across streams, I/O, macros, driver
queries and auxiliary motor precision moves; next full gate is cumulative.

# Legacy probe state without optional per-probe helper - 2026-10-23

Extended the existing unavailable-capability named-parameter test, retaining all
original missing-probe assertions. A legacy driver advertises a primary probe
and supplies get_state while leaving the documented optional is_triggered handler
absent. Active-probe identity remains available and contact input toggles through
the driver, while _probe_state correctly reports unavailable(-1) rather than
inventing false data or calling NULL. Secondary/toolsetter remain unavailable.
Targets ngc_params.c737's capability-true/helper-absent condition. Fresh ASan/UBSan
1/1pass0.38s; batch74-legacy-probe-parameter-results.xml. No new registration,
allowance, removed required callback or CORE edit. Keep with current cross-module
batch before cumulative validation; no additional hosted dispatch.

# Built-in setting macro bitfield persistence and retry - 2026-10-23

New public G65P1 workflow writes status-report bitfield3, returns3, rejects
undefined bit32768, and preserves both runtime/saved mask plus notification count.
A query still returns3; valid retry to1 updates runtime, return value and saved
storage once. S remains a macro argument without spindle RPM side effects.
Targets ngc_params.c1207 list classification and1215 rejected-store outcome.
Fresh ASan/UBSan1/1pass0.31s; batch74-macro-bitfield-results.xml. No new allowance,
private callback mutation or CORE edit. Keep with null-console/analog assignment/
precision-nudge work before the next cumulative gate and hosted checkpoint.

# Measured driver/PID/JSON checkpoint - 2026-10-23

Coverage job39938331513 at exact harnessb54a339 / CORE50f3865 passes all7stages
and matching source/filter locks.4,268cases:4,243clean/25known/0failed/skipped.
Measured17,402/17,714lines98.24%,12,335/13,800outcomes89.38%. Versus39936164446:
0new/lost lines,16additional branch outcomes.312raw lines/1,465outcomes remain.
Evidence hosted39938331513/comparison39936164446.json. Badges and exact inventory
updated. Source/coverage passed; GCC and Clang still in_progress at inspection;
not an overall hosted-success claim. Local null-console/analog-function/nudge
changes remain outside this measured head. No new dispatch or source exclusion.

# Analog PWM driver-function assignment and retry - 2026-10-23

New registered analog-bank workflow advertises PWM capability, rejects the first
driver function-assignment request without changing pin function/free count, then
accepts Output_SpindlePWM. The dedicated pin is no longer auxiliary-claimable;
remaining output count is3, input count stays4, input sampling and an unrelated
analog output still reach their original pins. Targets ioports.c435's valid
analog-port switch arm, not an invalid enum. Fresh ASan/UBSan1/1pass0.29s;
batch74-analog-function-results.xml. No new allowance or CORE edit. Keep with
null-console handover and precision-nudge work for the next cumulative batch.

# Network-only controller null-console handover - 2026-10-23

New ordinary stream lifecycle starts with the exported stream_null_init fallback
as base, connects a Telnet client, delivers its output, disconnects back to the
null console, and reconnects/delivers again. Disconnected client receives no
broadcast; fallback reads SERIAL_NO_DATA and base ownership remains unchanged.
Uses the actual StreamType_Null provider, no out-of-enum stream or private state.
Targets stream.c412-413's currently uncovered default arm through a valid fallback.
Fresh build and ASan/UBSan1/1pass0.28s; batch74-null-console-results.xml. Initial
test compile assumed disconnect returned bool; corrected to its actual void API
and observable stream/callback/output assertions before execution. No allowance
or CORE edit. Keep with the local precision-nudge extension for the next batch.

# Distance-mode precision nudges - 2026-10-23

Extended the existing millimetre-rounding case after its original1.01mm/81step
assertions. Public forward and reverse distances of1/steps_per_mm each emit one
step through normal motor service, returning to position81 with83total pulses.
No immediate output occurs while queuing either distance-mode nudge. Targets
stepper2.c354's one-computed-step/non-Stepper2_Steps condition without private
profile access. Fresh ASan/UBSan1/1pass0.33s; batch74-mm-nudge-results.xml. No
new registration, allowance or CORE edit. Accumulate independent work before
another full/hosted checkpoint; the previous delivery remains b54a339.

# Driver/PID/JSON cumulative delivery validated - 2026-10-23

Four new cases and two extended scenarios pass the full4,268-case ASan/UBSan
gate72.26s and strict summary:4,241clean/27known/0unexpected/0skipped. Evidence
batch74-driver-json-pid-delivery-{results.xml,tests.log,summary.log}. Batch covers
small PID corrections/reset, JSON writer budget/recovery and malformed-prefix
recovery, auxiliary motor allocation failure/retry, rejected reverse nudge, and
unbound-to-bound spindle settings updates. One new exact WILL_FAIL records the
wrong-direction output; later endpoint assertions remain unvalidated. Only its
allocation companion gets the existing calloc wrapper; no shared fixture changes.

Previous hosted39936164446 at614c036 now completed/success. Its verified98.24%/
89.27% measurement remains the latest until this batch's exact report exists.
No source exclusions, diagnostic waivers, CORE edits, merges or redundant helper
runs. Gap inventory's completed-run note updated; raw counts remain source-matched.

# Measured flow/jog checkpoint, Clang still running - 2026-10-23

Coverage job39936164446 at exact harness614c036 / CORE50f3865 passes all7stages,
matching both source/filter locks.4,264cases:4,240clean/24known/0failed/skipped.
Measured17,402/17,714lines98.24%,12,319/13,800branches89.27%; relative to
39932438179 this is2new lines(gcode.c2427,ngc_flowctrl.c687),7new outcomes,
0lost lines.312raw lines/1,481outcomes remain. Evidence hosted39936164446/
comparison39932438179.json. Badges/raw-gap snapshot and complete inventory updated.
Source/GCC/coverage passed; Clang still in_progress at inspection. This is not an
overall hosted success claim. Pending PID/JSON/auxiliary motor work is unmeasured.

# Auxiliary spindle unbound notification and resolution update - 2026-10-23

Extended the existing A-axis pulse-routing test. A settings notification after
public spindle-motor creation but before public binding calls the previous hook
without pulses or starting the unbound motor. After st2_motor_bind_spindle,60RPM
maps to200steps/s; a public A-axis resolution setting changes that to400steps/s,
with the notification chained once and still no stray pulses. An accepted
single step then reaches only physical axisA and position1. Fresh ASan/UBSan
1/1pass0.30s; batch74-unbound-spindle-results.xml. Targets stepper2.c114's valid
unbound branch. No forced bound flags, new case registration, allowance or CORE
edit. Keep with the pending cross-module driver/PID/JSON batch before full gate.

# Auxiliary motor allocation failure and retry - 2026-10-23

One public motor workflow starts20forward steps, emits a step, then fails only
the allocation while adding a second motor. NULL result preserves the settings
hook and first accepted move, which finishes at20pulses/position20. Retrying the
second motor succeeds and a5step reverse move finishes independently, total25
pulses with the first position unchanged. Uses the existing calloc_failure_host;
one exact test target gets --wrap=calloc, fault enabled only during motor init.
No new allocation framework, CORE edit or allowance. Fresh build and focused
ASan/UBSan3/3pass0.44s with completed-reversal and concurrent-finite controls;
batch74-stepper-allocation-results.xml. Targets stepper2.c259 allocation rejection.
Keep with the pending PID/JSON/motor batch before cumulative delivery validation.

# Malformed JSON prefix and next-response callback - 2026-10-23

Extended the existing missing-colon parser case instead of adding a duplicate:
plain non-JSON text and an unquoted object key produce no callback, then a valid
status response returns the exact string tag/value and caller context. Preserves
original missing-colon assertions. Targets the two root-prefix outcomes in
stream_json.c264 using public inputs. Fresh ASan/UBSan1/1pass0.36s;
batch74-json-parse-recovery-results.xml and successful build log. No allowance,
parser feature assumptions or CORE changes. Keep with pending writer/PID/motor
batch; no full gate or hosted dispatch for this extension.

# JSON zero-depth budget and clean next response - 2026-10-23

New public writer scenario starts with an explicit max_levels0 budget, rejects
string/int/real fields and container operations without emitting bytes, and ends
as exact{}. A subsequent writer with budget2 emits a normal tagged response and
nested count, verifying fresh separator/depth state and exact output. Only the
fixture's captured output is cleared between responses; opaque writer state is
never accessed. Fresh build and ASan/UBSan1/1pass0.43s; batch74-json-budget-results.xml.
Targets the remaining public writer rejection arms in stream_json.c. No new bug
claim, allowance, private-state injection or CORE edit. Keep with PID and auxiliary
motor work for the next substantial batch; measured gain remains pending.

# Rejected auxiliary nudge reverses active output - 2026-10-23

New public stepper2 scenario accepts20forward steps, services one pulse, then
requests a reverse single step at the same speed while busy. Returnfalse means
not accepted, but next actual driver output is reverse: raw direction0/pulse1,
direction1/pulse2; correct forward-direction assertion fails in0.29s. Public API
doc and source mutation-before-rejection identify the cause. No private state,
concurrent callback injection, or synthetic timing window. One narrow WILL_FAIL
and dated KNOWN_BUGS entry; endpoint assertions remain unvalidated after the fault.
Raw batch74-stepper-reject-raw-results.xml. No CORE edit; continue independent work.

# PID feedback settling inside configured limits - 2026-10-23

Added a separate pid case through existing automatic standalone registration;
no CMake change or host-core variant. A1000unit setpoint with approaching,
slightly overshooting and settled feedback produces exact small positive/negative
corrections with P/I/D and nonzero clipping limits enabled. Reset preserves the
configuration but clears accumulated/history corrections at the setpoint.
Targets the two remaining pid.c85/98 unsaturated lower-bound outcomes; this is a
public helper test, not a claim of spindle/controller integration (CORE does not
call this utility). Fresh ASan/UBSan2/2pass0.33s with the original PID suite,
batch74-pid-settling-results.xml. No allowance/CORE edit. Keep local for the next
cross-module batch; coverage gain awaits measurement, no new hosted dispatch.

# Flow/jog/thread/probe/RAM cumulative delivery - 2026-10-23

Four new cases and two strengthened existing workflows pass the full4,264-case
ASan/UBSan gate70.06s and strict summary:4,238clean/26documented regressions/
0unexpected/0skipped. Evidence batch74-flow-jog-hold-delivery-{results.xml,
tests.log,summary.log}. One new exact expected failure records mismatched numeric
ENDSUB; the orphan terminator control passes through the missing error path.
Other work covers explicit jog feed, G76 inter-pass hold/resume, probe bounce/
re-arming, and empty/populated RAM reset with payload readback.

Post-gate review corrected the bounce model to issue only rising-edge callbacks:
release changes the input without invoking the rising-edge handler. Fresh build,
affected case and strict summary pass0.28s; batch74-probe-rising-bounce evidence.
No shared infrastructure or CORE change; no repeated full gate required. The
measured coverage remains7073ca1 until a new exact-source report exists. No source
exclusions, weakened defect assertions, script changes or redundant helper runs.

# Previous checkpoint fully verified - 2026-10-23

Run39932438179 at7073ca1 is now completed/success: source, GCC, Clang, coverage
and CI diagnosis all passed. Existing source-locked98.23%line/89.22%branch
measurement stands. Updated the complete gap inventory's earlier GCC-pending
note. No new hosted run dispatched during authoring.

# Reset mixed empty and populated RAM uploads - 2026-10-23

Extended populated_reset_clears_files_and_allows_reuse without adding a case:
close a normal5byte upload and an empty upload, verify storage counts only the
payload, reset through the installed driver hook, and require both names gone.
A fresh upload is then reopened and its exact payload read back. Exercises
fs_ram.c335's null-data cleanup and a multi-node reset through normal operations.
Fresh build and ASan/UBSan2/2pass0.34s with the unchanged empty-reset control;
batch74-ram-reset-results.xml. No allowances, forced handles or CORE changes.
Keep with pending probe, threading, jog and file-flow work before cumulative gate.

# Orphan ENDSUB passing control - 2026-10-23

A real file with O20ENDSUB and no registered subroutine rejects with syntax error,
suppresses its tail, preserves parent parameter99 and restores the sender query.
This exercises the previously uncovered ngc_flowctrl.c687 error arm with an empty
sub list, distinguishing it from the mismatched-label lookup defect. Pair passes
ASan/UBSan0.34s:1clean control/1documented expected failure, evidence
batch74-endsub-pair-results.xml. No additional allowance.

The first control run exposed an incorrect post-helper !sys.abort assertion:
ram_sender_read exits through CMD_EXIT, which intentionally calls mc_reset.
Removed that host-exit assumption from both new cases; syntax error, suppressed
body/tail, restored sender and idle/no-alarm checks remain unchanged. The mismatch
case still fails first at the correct status assertion; later checks are not yet
validated on current CORE. Keep additions together for the next batch gate.

# Bounded mismatched ENDSUB regression - 2026-10-23

Real RAM-file `O10SUB ... O20ENDSUB` accepts an undefined terminator label and
executes the tail. Bounded reproduction prints status0/body0/tail7 and fails the
correct syntax-error assertion in0.26s; batch74-endsub-mismatch-raw-results.xml.
Source lookup sub_get returns its last node on a miss. One exact WILL_FAIL with
dated KNOWN_BUGS evidence; no diagnostic/timeout allowance or CORE edit. The
initial candidate including a later CALL timed out and was reduced before
classification; that timeout is not accepted as evidence of assertion success.
Keep with the pending cross-module batch and continue independent work.

# Jog requires its own feed after program feed selection - 2026-10-23

New public command workflow selects G90/G1/F120, then rejects `$J=G91X1` with
Status_GcodeUndefinedFeedRate. Driver remains asleep, queue empty, all actual
motor counters/pulses unchanged; program feed120 and absolute mode are retained.
Retry `$J=G91X1F100` emits exactly80X pulses and returns idle without changing
program feed/mode. Fresh ASan/UBSan1/1pass0.33s; batch74-jog-feed-results.xml and
successful build log. Targets measured uncovered gcode.c2427 through the ordinary
system jog command. No new exception or CORE edit. Keep with probe bounce/G76
hold for the next substantial batch; no full or hosted run for this addition.

# Completed coverage job measurement, GCC still active - 2026-10-23

Hosted39932438179 coverage job completed successfully at exact harness7073ca1 /
CORE50f38659db7b22f4689f3654df2d110d992bcc95. Both source locks/filter agree,
all7coverage stages exit0,4,260cases:4,237clean/23known/0failed/skipped.
Measured17,400/17,714lines98.23%,12,312/13,800branches89.22%. Compared with
39927192936:1new line(tool_change.c512),13branch outcomes,0lost lines;314raw
lines remain. Evidence hosted39932438179/comparison39927192936.json. Badges and
raw-gap snapshot updated. Source and Clang jobs passed; GCC still in_progress
at inspection, so this is not an overall hosted-success claim. Uncommitted probe
bounce and G76 hold work are outside the measured head.

Compatibility saved-mode candidate reached earlier parser rejection because
legacy startup removes stream suspension. Withdrawn unfinished cases and
recorded the source guard in TODO; no forced handler or speculative allowance.

# PWM contract clarification - 2026-10-23

Narrowed the zero-tick bug's proposed repair and recorded Terje's resolution
question separately. Existing regression only expects rejection when clock/PWM
frequency truncates to zero ticks; it does not demand2MHz output or choose a
100/1,000tick cutoff. Preserved correct assertion and its existing narrow allowance.
Documented low-frequency servo period/prescaler constraints and preserved50Hz
controls. No code/CORE edits or redundant test run for this documentation change.

# Multipass G76 feed-hold/resume - 2026-10-23

One new realistic encoder-driven G76 workflow requests public feed hold20pulses
into its first synchronized cut. That cut reaches its endpoint; the hold completes
before a second encoder reset/pass. Four held polls preserve all motor positions
and pulse counts while the spindle stays on. Public cycle start completes the
remaining thread with the same560X/240Z pulses and exact clearance endpoint as
the ordinary control; saved override flags are restored and pending hold clears.
Fresh ASan/UBSan1/1pass0.29s, batch74-g76-hold-results.xml and successful build log.
No allowance, private state injection or CORE edit. Keep this new case with the
probe-bounce extension for the next cross-module batch; no full/hosted rerun.

# Probe bounce and consecutive-cycle latch - 2026-10-23

Extended the existing irq_latches_contact_until_probe_cycle_ends case without
adding another registration. Four physical contact/release cycles preserve the
first contact latch and probing history without dispatching idle control signals.
Ending the cycle disarms the IRQ; a second configured cycle clears prior history
and latches a fresh contact. Fresh build and ASan/UBSan1/1pass0.29s; evidence
batch74-probe-bounce-results.xml. Targets probe.c40's repeated-contact outcome.
No new allowances or CORE changes. Keep this with the next substantial batch.

Pushed checkpoint7073ca1 has live hosted run39932438179, observed in_progress;
no duplicate dispatch. Fresh upstream fetch still matches pinned CORE50f3865.

# Hidden-file contract clarification and cumulative gate - 2026-10-23

Terje clarified hidden entries are accessed through full paths, plans to block
CWD into hidden mounts, and wants successful embedded registration to report true.
Updated KNOWN_BUGS/TODO: hidden-CWD policy is resolved; existing rejection tests
stay intact. vfs_mount already returns boolean; fs_embedded_mount remains void,
so its future return API is tracked without editing CORE or inventing an assertion.

New mixed visible/hidden mount regression confirms ordinary relative visible
access and full-path hidden payload, then reproduces incorrect relative hidden
access. One exact WILL_FAIL/known_bug retains its final rejection assertion;
raw batch74-hidden-path-raw-results.xml. No sanitizer diagnostic waiver.

The preceding7-case cross-module batch passes the full4,259-case ASan/UBSan gate
162.66s and strict summary; evidence batch74-motion-probe-delivery-{results.xml,
tests.log,summary.log}. The new hidden-path case is subsequent and receives a
focused follow-up, rather than repeating that full gate. Total registration4,260.
No CORE edits or merges. Coverage delta for this local batch remains unmeasured.

# Nondefault probe board lifecycle - 2026-10-23

A new public registration scenario starts with a toolsetter and secondary probe,
without a default probe. Missing-default capability/trigger queries and selection
reject safely while preserving the selected toolsetter. Selecting the secondary
then changing its real input updates selected and aggregate states independently;
return selection restores the toolsetter. No private probe state or slot mutation.
Fresh ASan/UBSan1/1pass0.26s; evidence batch74-probe-order-results.xml and successful
build log. Targets empty-slot default-ID comparisons in probe.c103/125/138 and
nondefault registration/selection order. Coverage gain remains unmeasured until
the cumulative checkpoint. Seven new local cases total4,259 across tool-change,
arc fallback, rotary planner and probe lifecycle workflows. No new allowances.

# Sparse rotary workflows and fresh arc verification - 2026-10-23

Two new eight-axis workflows use public rotary settings and actual motor output:
a Y3/Z4 cut with A/V rotation derives duration from5mm linear travel at120mm/min
while X stays still; a metric rotary-only move retains120degrees/min even with
inch-conversion reversion enabled. Planner timing and exact pulses/endpoints pass.

Fresh build also exposed an error in the strengthened arc assertions: steps is
steps_t with member value[], not an array. The earlier0.31s arc run used prior
executables because that shell did not stop after build failure; it did not prove
the added planner assertions. Corrected both assertions to steps.value[], required
successful build before CTest, and ran all4changed rotary/arc cases:4/4pass0.50s
under ASan/UBSan, evidence batch74-sparse-rotary-arc-results.xml and matching build
log. This fresh result supersedes the earlier strengthened-assertion claim.
No CORE edits or new allowances. Six local cases now total4,258; continue the
substantial batch before cumulative delivery validation.

# Arc chord fallback workflows - 2026-10-23

Two new parser/stepper cases cover arcs whose diameter equals the configured
0.02mm tolerance and short5degree/radius1 arcs whose intermediate segment count
rounds to zero. Each checks the first planner endpoint separately, then executes
an ordinary following cut and verifies exact physical position and pulse counts
without reversal/overshoot. Both pass ASan/UBSan0.31s; evidence
build-asan/batch74-small-arc-results.xml. No new exceptions or CORE edits.
These target the remaining motion_control.c281/284 fallback outcomes in the
source-locked report; their measured coverage delta awaits cumulative reporting.
Four new local cases now total4,256 with the two G30 controls. Keep accumulating
cross-module work before the next full gate/push/hosted checkpoint.

# Source-locked hosted coverage measurement - 2026-10-23

Run39927192936 at harness6b29d886e3320aae90f5286e8b89bf11cc559e49 and
CORE50f38659db7b22f4689f3654df2d110d992bcc95 reports17,399/17,714 lines98.22%
and12,299/13,800 outcomes89.12%. Against run39922349935 this is0new/lost lines
and9additional branch outcomes. Both artifacts carry matching source locks;
all7coverage stages exit0;4,252cases include4,230clean/22known/0failed/skipped.
Evidence build-asan/hosted39927192936, comparison39922349935.json. README badges
and raw-gap snapshot now reference this measured run.315raw lines remain;
the unpushed G30 controls are not included in this measurement.

# Hosted checkpoint and auxiliary homing audit - 2026-10-23

Hosted run39927192936 completed successfully at exact harness6b29d88. Coverage
artifacts have not yet been inspected; do not replace the last measured98.22%/
89.06% snapshot with a guessed gain. No new hosted dispatch.

An actual four-axis delta homing/jog candidate fails before the jog: home callback
reports cycle15/success0/homed0. Retained unregistered pending a supported homing
fixture/contract; no fabricated homed state or speculative WILL_FAIL. Diagnostic
evidence and source boundary are recorded in TODO. The two passing aligned G30
cases remain local for the next substantial cumulative batch.

# Aligned G30 manual tool-change controls - 2026-10-23

Two new full-boot cases exercise G30 with X already aligned and with both XY
already aligned. Actual homing, tool acknowledgement and touch-off complete;
pulse observations prove aligned horizontal axes remain still, the G30 pose is
visited and the original handler and sender state are restored. Both new cases
and the existing G30 control pass ASan/UBSan:3/3 in0.32s, evidence
build-asan/batch74-g30-aligned-results.xml. Cumulative registration is4,254;
these additions await the next substantial full gate. No new exceptions or CORE
edits. Consolidated duplicate settings reachability notes against current CORE.

# Cumulative input/macro/settings delivery - 2026-10-23

Seven new cases plus three strengthened existing macro scenarios beyond e29e27e
pass the full4,252-case ASan/UBSan gate77.82s and strict summary:4,228clean/
24documented regressions/0unexpected/0skipped. No new defect allowances or CORE
edits. Evidence build-asan/batch74-ownership-macro-settings-delivery-{results.xml,
tests.log,summary.log}. This combines registered input ownership, singleton plugin
selection, actual nested macro motion/recovery and driver-dependent settings.

Three new settings controls use public writes and capability lookup: parking on
an input-less board hides DoorOptions and rejects writes without changing saved
flags; a board advertising its door before metadata initialization retains both
options across reload while parking stays enabled; a registered feedback VFD
exposes/sets/clears speed tolerance without a separate encoder. Seven focused
availability controls pass0.44s. The unused DoorSpindle/Coolant delay availability
switch cases have no descriptor callback; their raw gaps are documented, not
forced by altering private setting tables. Reporting helpers remain unchanged.

Previous e29e27e hosted run39922349935 passed all five jobs, both source locks
match50f3865 and all seven coverage stages exit0. Classifier4,245total/4,223clean/
22known/0failed/0skipped. Measured17,399/17,714 lines98.22% and12,290/13,800
branches89.06%: unchanged lines,+8 outcomes versus39919635378, no lost lines.
Comparison is build-asan/hosted39922349935/comparison39919635378.json.
README/gap badges use this locked result; no gain claimed for the newer batch.

# Assigned input ownership and real macro recovery batch - 2026-10-23

LOCAL beyond e29e27e: four new cases plus three expanded existing scenarios,
4,249 registered. Registered fault/probe inputs now use ioport_set_function;
ordinary aux inversion changes leave their physical configuration untouched,
while their dedicated inversion settings still update them. Probe registration
and get_state verify polarity too. A one-output board selects/claims its dust
relay through public configuration helpers, refuses a nonexistent next port and
continues routing that claimed relay's on/off writes to its original pin.
All I/O plus affected existing RAM/named macro controls pass204/204 ASan/UBSan
and strict summary in3.38s (199clean/5existing known/0unexpected/0skipped).
Evidence batch74-input-plugin-macro-{results.xml,tests.log,summary.log}.

The small shared RAM motion fixture now serves the two upgraded scoped G66
cases and a new nested M73 unit-restoration job. Real child files switch into
inch/incremental then metric/absolute modes, restore their callers and complete
the following parent relative cut with exactly160X/160Y pulses. Arguments99/5/7
remain in the correct scopes. The existing nested parser-error regression now
also executes its accepted child moves and the sender recovery cut: after a $G
query clears the sender error latch, final travel is160X/80Y pulses. Original
three-file error propagation, tail suppression and caller restoration assertions
remain. No new defect claim from a missing recovery-query fixture assumption.

All four affected real-motion macro jobs pass0.62s plus strict summary, evidence
batch74-nested-error-motion-{results.xml,summary.log}. No new exceptions, CORE
changes, full suite or hosted dispatch. Keep this cumulative group for its next
useful delivery boundary. An uncertain compound-capability setter contract is
recorded in TODO without registering a speculative failure.

# Active real-file modal-macro motion follow-up - 2026-10-23

Operator/arc cumulative checkpoint e29e27e is pushed and hosted run39922349935
is in_progress at that exact head. It follows the full4,245-case64.33s sanitizer
and strict gate. No repeated hosted checkpoint or PR merge. Last locked measured
coverage remains73c12ba98.22%/89.00%; no newer gain is claimed.

LOCAL follow-up upgrades two existing scoped G66/G65 real-file cases from parser
position checks to actual emitted motor steps. Reuses the RAM fixture's optional
setup hook, preserving existing default setup for all other callers. Registered
stepper callbacks service real nested files; a public dwell synchronizes completion
before sender exit. Both rapid and linear jobs emit exactly240Xsteps and end at
X3 with no Y/Z motion, no file errors, normal EOF status at all three depths,
restored scopes and one outer modal callback. Original parameter/file ownership
assertions remain. No new registered case or exception; total remains4,245.

Affected36-case ASan/UBSan and strict summary passes1.41s:35clean/1existing
missing-ENDSUB regression/0unexpected/0skipped. Evidence batch74-nested-motion-
fixtures-{results.xml,tests.log,summary.log}. No new full gate for two fixture
upgrades; retain this work for the next substantial batch. CORE unchanged.

# Cumulative operator/arc delivery gate - 2026-10-23

Full4,245-case ASan/UBSan plus strict summary passes64.33s on the operator/arc
batch:4,221clean/24documented regressions/0unexpected/0skipped. Raw and classified
arc endpoint evidence remains linked below; both correct regressions reproduce.
Evidence build-asan/batch74-operator-arc-delivery-{results.xml,tests.log,summary.log}.
The shared sampled-geometry fixture retains all prior full-circle combinations
and adds valid-endpoint short arcs. CORE unchanged50f3865. No script changes or
new sanitizer diagnostic allowances; reporting helpers were not redundantly rerun.

Previous hosted73c12ba run39919635378 is fully successful across all five jobs.
Both source locks agree, all seven coverage stages exit0; classifier4,239total/
4,219clean/20known/0failed/0skipped. Measured17,399/17,714 lines98.22% and
12,282/13,800 branches89.00%, +2 lines/+5 outcomes over39914617515, no losses.
Gained ioports.c1557 and spindle_control.c1014. Comparison saved under
build-asan/hosted39919635378/comparison39914617515.json.315 raw uncovered lines.
README/gap snapshot refreshed to that verified head; newer arc/hold work is not
included in those percentages. Deliver the cumulative group, then keep authoring.

# Operator hold policy and arc-envelope endpoint batch - 2026-10-23

LOCAL beyond pushed73c12ba: six new cases plus seven expanded existing cases,
4,245 registered. This cumulative group preserves the earlier two operator-start
controls: repeated starts do not disturb an active cut; start cannot wake completed
sleep before reset. Three additional registered-driver hold controls use public
HoldActions6: dynamic laser stays at zero PWM without a new spindle-state write;
constant laser reduces to zero then restores on cycle start; an M5 dry cut never
starts its spindle during hold/resume and accepts a later explicit M3.

Independent sampled arc geometry now includes endpoints15/45/75 degrees within
each quadrant, both directions, four limiting walls and XY/ZX/YZ planes. Original
45-degree/full-circle combinations remain. These controls isolate arc extrema
with valid endpoints; out-of-envelope endpoint handling has separate real G-code
regressions. All six expanded geometry controls pass.

Confirmed exact radius5 arc endpoint defect on clean CORE50f3865: CW from
(-6,-0.5) to(-13,+0.5) emits Y+40steps with no alarm; CCW from(-6,-49.5) to
(-13,-50.5) emits Y-4040steps with no alarm despite a -50..0mm envelope.
Both starts are reached by G0; tests execute real parser/planner/stepper motion.
Non-extremum Y bounding min/max are reversed in machine_limits.c785-795, and
accepted arc segments bypass further soft checks. Correct alarm/no-arc-step
assertions remain in two exact WILL_FAIL cases; dated KNOWN_BUGS entry includes
source cause, independent controls and cleanup instructions. No sanitizer waiver.

Grouped ASan/UBSan plus strict summary:13cases/11ordinary/2documented defects/
0unexpected/0skipped in0.68s. Evidence batch74-operator-arc-classified-results.xml
and summary.log. Raw invalid-endpoint traces are batch74-arc-endpoint-raw-results.xml
and batch74-lower-arc-endpoint-raw-results.xml. No CORE edit or new hosted dispatch.
Next cumulative full gate must include this group before delivery. Prior73c12ba
hosted run39919635378 remains the one existing checkpoint to verify separately.

# Active operator-start follow-up - 2026-10-23

Seven-workflow cumulative checkpoint73c12ba is pushed on coverage-batch-74.
One hosted run39919635378 is in_progress at this exact head; no terminal success
is inferred. Last fully locked measurement824e516 remains98.21%/88.96%.

New LOCAL follow-up: one case plus one expanded existing boot case,4,240
registered. Cycle start after16 emitted pulses and again during the following
relative block preserves the same planner owner, continuous1680Xpulses and one
driver wake, with no hold or position loss. Completed-sleep observer now requests
cycle start after receiving Sleep status and observes four stable sleeping turns:
outputs disabled, no position changes; original reset/warm parser/lock assertions
remain. Both pass ASan/UBSan0.30s, batch74-running-sleep-start-results.xml.
No new exception, full gate or hosted run for these local changes. Keep authoring
on the same batch; do not edit CORE or merge PR28.

# Cumulative public-workflow delivery gate - 2026-10-23

The seven-workflow group eb168ca passes the full4,239-case ASan/UBSan gate in
162.27s and strict summary:4,217clean/22documented regressions/0unexpected/
0skipped. Evidence build-asan/batch74-public-workflows-delivery-{results.xml,
tests.log,summary.log}. No new exceptions; CORE remains clean50f3865.
This checkpoint includes operator wiring, guarded named-file scans, inch-mode
selected probing, no-spindle commands, calibration removal, coolant modal timing
and PRINT allocation recovery. Reporting helpers are unchanged; no redundant
full helper rerun. Push one cumulative hosted checkpoint, then continue authoring.
Coverage badges below describe verified824e516, not this new group.

# Verified correction checkpoint coverage - 2026-10-23

Run39914617515 at824e516/core50f3865 is fully successful across source, GCC,
Clang, coverage and diagnosis. Both downloaded source locks agree; all seven
coverage stages exit0. Coverage classifier4,232total/4,212clean/20known/0failed/
0skipped. Measured17,397/17,714 lines98.21% and12,277/13,800 outcomes88.96%.
Net change from39908773015 is+11 lines/+27 outcomes; the withdrawn synthetic
scheduler saturation test legitimately loses spindle_control.c636. Raw covered
line comparison is build-asan/hosted39914617515/comparison39908773015.json.
317 raw uncovered lines remain; no exclusions or adjusted denominators.
README badges/gap snapshot now use this verified checkpoint. The seven local
workflows below are not part of this measurement. Fresh upstream fetch still
50f38659db7b22f4689f3654df2d110d992bcc95; CORE working tree remains unchanged.

# Public wiring, scan and probing follow-up - 2026-10-23

Seven new LOCAL workflows beyond824e516, current registered count4,239:
- Registered auxiliary input is assigned FeedHold using ioport_set_function.
  Public control inversion/pullup settings toggle inverted/pulldown then restore
  normal/pullup wiring, preserving debounce, assignment and the other aux input.
  This exercises the real setter/driver-notification path and clear-inversion arm.
- Named file with guarded ERROR is scanned before executing two valid calls.
  The diagnostic remains inactive, arguments accumulate once per call, and caller
  local99 is restored. No immediate-execution or implicit-EOF assumption.
- Inch/incremental G38.2 selects toolsetter, measures real motor contact, restores
  previously selected Probe2 and retains inch/incremental/feed modes. Incremental
  retract then metric/absolute return reach their physical endpoints.
- No-spindle board uses CORE's automatic null fallback for ordinary M3/M4/M5 and
  150/100 percent overrides; enabled/direction/stopped states remain coherent.

- Public calibration settings produce a below-minimum PWM request; driver
  conversion clamps to minimum for normal/PID output and keeps zero RPM off.
  Clearing the calibration setting restores ordinary linear output and capability.
- M70/M72 saves/restores both off and running coolant. Restoring off skips the
  configured100ms startup wait; restarting saved flood waits100ms; unchanged
  repeated restore adds no driver write or delay.
- PRINT substitution fails only its exact11-byte result allocation. It returns
  no owned message, suppresses the comment event, preserves parameter7.5 and
  successfully formats/frees the next message. Wrapper is scoped to this case.

Grouped ASan/UBSan and strict-summary validation now passes141/141 in17.79s,
including all affected expression/calibration/coolant controls. Evidence:
build-asan/batch74-calibration-coolant-message-{results.xml,summary.log}.
No new known exceptions. This is an affected-module gate, not a full suite.

Earlier grouped three-case ASan/UBSan evidence batch74-wiring-probe-scan-results.xml passes
1.13s; null-board scenario batch74-null-program-results.xml passes0.15s.
Initial wiring fixture omitted mandatory control reader; corrected the fixture.
Protocol CMD_EXIT intentionally sets abort, so named-file assertions use returned
status, restored scope, no error output and alarm state rather than a post-exit
!abort assumption. No new CORE defect or expected-failure allowance.
No new full local gate, hosted dispatch or coverage-gain claim for these seven.
They remain on batch74 for the next substantial cumulative delivery.

# Maintainer contract corrections - 2026-10-23

Terje clarified named files must scan through a matching ENDSUB before executing.
With valid SUB/ENDSUB fixtures and distinct scan/execution passes, 27 obsolete
expected failures were removed. The incorrect named-CALL defect and immediate
execution proposal were withdrawn. New controls observe no scan-time body effects
and exactly one later execution. A separate missing-ENDSUB regression retains
syntax-error/no-body/no-caller-tail assertions with one narrow expected failure:
current CORE skips the body but reports success at EOF. CORE remains unchanged.

The synthetic full scheduler pool override case is now an unregistered proposal;
its confirmed-defect entry and allowance are removed. No real plugin workload or
applicable scheduling window was established; public reachability is insufficient.

CONTINUE to a missing numeric loop label reproduces stack[-1] at CORE line628.
One exact sanitizer diagnostic wrapper records that fault; ordinary Clang passes.
Earlier independent workflow additions remain part of this cumulative batch.
Validation: one 4,233-case ASan/UBSan gate completed in299.45s, exposing four
allocation/EOF fixtures still consuming the old headerless body. Corrected those
fixtures to consume the valid file through both passes; all41 affected cases pass
in0.94s. Full gate plus affected repair, excluding the withdrawn stress test and
replacing the renamed EOF case, gives4,232 cases with zero unexpected failures.
Evidence: build-asan/named-correction-{delivery,repair,effective}-results.xml.
The effective XML combines those two runs explicitly; it is not a second full run.
Ordinary Clang missing-loop-label control passes0.23s. Hosted coverage for these
new changes has not been measured.

# Active encoder, label and probe-alarm follow-up - 2026-10-23

Delivered branch74 head c4e04619ce9f991e8c30c608731b64a1a3df33ba has one
hosted run39908773015, now fully green across all five jobs at that exact head.
Both coverage artifact source locks agree with clean CORE50f3865. All seven
coverage stages exit0; classifier4225total/4178clean/47known/0failed/0skipped.
Measured17,386/17,714 lines98.15% and12,250/13,800 branch outcomes88.77%.
Against exact-source39905420870: +7 lines/+8 outcomes, no lost covered lines.
Gained gcode3165/3968/3970, machine_limits544, protocol145/146/160. Evidence:
build-asan/hosted39908773015/comparison39905420870.json and both locked artifacts.
Badges/gap snapshot refreshed;328 raw uncovered lines remain. PR28 frozen.
No coverage gain is claimed for newer local work below.

Current LOCAL work beyond c4e0461:
- Expanded incomplete-threading case rejects negative P/J/K with unchanged
  spindle/motors/planner, preserves the original80-pulse recovery assertions,
  then completes real G76 encoder passes: cumulativeX640/Z240 pulses and physical
  X880/Z-80. ASan/UBSan0.30s, batch74-thread-negative-results.xml.
- New fractional O-label scenario rejects SUB/CALL labels with fractional values,
  retains call level0, original planner head/capacity, modal/feed state and
  unstarted motors, then accepts a corrected sender move and reaches160Xpulses.
- Extended door-reopen-during-spindle-restore case retains its original parked,
  accessories-off/no-resumed-cut assertions, then closes/resumes again and
  completes exact original X/Z endpoint with spindle5000RPM/coolant restored.
  Both pass grouped ASan/UBSan0.39s, batch74-label-parking-results.xml.
- New actual registered-probe disconnect starts motion, raises real control IRQ
  after16steps, requests hold/protection alarm, decelerates below80step endpoint,
  reports Alarm13 and holds the physical position across four alarm polls until
  a public reset aborts the probe. Reset-capable existing fixture supplies mandatory
  coolant/driver-reset callbacks; initial omitted-callback crash was a fixture
  mistake and has no diagnostic exception. ASan/UBSan0.30s,
  batch74-probe-disconnect-results.xml. No new known defect or allowance.

- New multi-spindle jog scenario rejects $J=G92 before motion, then jogs80steps
  using the last selected registered secondary spindle, preserving primary3000/
  secondary7000 outputs, originalG90/feed250 state and primary output writes.
  ASan/UBSan0.31s, batch74-multi-jog-results.xml. Initial primary-selection
  assumption was corrected to the public last-selected-spindle contract.
- New stopped-PWM dry run applies110% override after16real steps, completes
 1600steps with output continuously0, then explicitM3S500 starts at550. No
  implicit spindle activation. ASan/UBSan0.37s, batch74-dry-spindle-results.xml.
- New numeric-file WHILE allocation failure injects only sizeof("[1]")=4
  allocation after a public runtime comment. OutOfMemory leaves #100=0, closes
  the stream, and a reopened valid loop runs twice to#100=2. No named-subroutine
  path or exception. ASan/UBSan0.28s, batch74-numeric-while-results.xml. The
  fixture must run in Idle: check mode intentionally suppresses its arming
  comment. CMake adds wrapping only for this exact executable.

TODO records a source-proven unreachable parking-restoring true arm: the caller
changes the handler before entering the only function that sets the flag. The
real door/recovery workflow remains tested; raw coverage stays unchanged.
These changes remain grouped locally; no full gate or hosted run for this small
follow-up. The39908773015 report was read once for this batch and ranked the new jog and
stopped-spindle paths; continue its remaining supported gaps at the next checkpoint. CORE stays
clean50f3865; meaningful full supported coverage remains incomplete/goal active.

# Cumulative startup/lathe/storage delivery gate - 2026-10-23

Branch coverage-batch-74 accumulates10 new cases and2 expanded workflows beyond
1142871 across boot, boot_backlash, CAN, protocol, selected probing, lathe parsing
and persisted tools. One full ASan/UBSan gate passes4,225 cases in176.79s:
4,177 clean,48 documented known regressions,0unexpected/0skipped; strict summary
passes. Evidence: build-asan/batch74-workflows-delivery-{results.xml,tests.log,
summary.log,gate.json}. Session57908 completed; do not restart it.

New lathe matrix checks wrong-plane and missing-Q errors for all six G71/G72
forms, retains queued X motion and completes exact80 X/80 Z pulses afterwards.
A real initialized persisted-tool G10L11 read-failure scenario returns ReadFail,
preserves tool3 geometry and queued80-pulse cut, restores valid G59.3 and retries
successfully to tool Z offset40. Both pass focused sanitizers.

One confirmed same-block plane-validation defect has two correct named
regressions (accepting selected G18; rejecting selected G17 before dispatch),
two exact WILL_FAIL entries and dated KNOWN_BUGS documentation. Raw failures
were verified separately; no sanitizer allowance was added. CORE latest fetch
remains clean50f38659db7b22f4689f3654df2d110d992bcc95. No firmware edits.

Deliver this coherent checkpoint on74 with one hosted dispatch. PR28 remains
OPEN/ready/frozena9f355c; avoid a duplicate cumulative PR while it is open.
Latest measured hosted39905420870 at1142871 is fully green98.11% lines/88.71%
branches, NOT a measurement of these new cases. Continue independent reachable
encoder/parser work after delivery; the full coverage goal remains active.
Reporting helpers unchanged since75 passed checks, so no redundant rerun.

# Startup fault timing and post-homing backlash group - 2026-10-23

Four additional realistic boot workflows pass ASan/UBSan with CORE unchanged:
- Motor fault arriving at the serial welcome boundary blocks G91. Clearing the
  physical signal still makes $X return79; reset then $X permits G91 and $G.
- Public $65=32 arms an actual registered watchable probe; warm reset followed
  by guard contact reports Alarm_ProbeProtect (13), rejects G91 and permits
  clear/$X/retry. Existing saved-flag clearing is not bypassed.
- Engaged limit plus warm-reset physical limits_override enters Idle without
  $X, retaining the engaged switch and enabled hard-limit policy.
- Public $160/$161 configure0.1mm backlash; real $HX/$HY complete before a
  two-axis bidirectional job. Homing pulses110/150, logical positions-10/-10;
  final pulses278/318 and physical78/118 retain logical-10/-10 and no Z pulses.
  Reuses existing boot_stream_motion fixture, enabling supported homing at boot.

Three fault cases pass0.40s in batch74-late-alarm-results.xml; homing/backlash
passes0.30s in batch74-home-backlash-results.xml. Initial failures were fixture
setup/assertion mistakes: core resets its report callback, motor faults require
reset, probe alarm number is13, and the stream fixture disables homing by default.
Corrected driver-boundary setup and assertions; no CORE defect or allowance added.
Source review identifies previously uncovered protocol.c145/146/160 and
machine_limits.c544. These new local workflows have not had a fresh coverage
measurement; do not count source review as measured gain. Keep the cumulative
local group together and continue other reachable gaps before a delivery gate.

Hosted39905420870 at1142871 is now fully green, all5jobs success. Exact source
locks and measured98.11% lines/88.71% branches are verified below. Badges and
KNOWN_BUGS gap snapshot refreshed to that report (335 raw uncovered lines).
No new hosted run or small branch/commit checkpoint was created.

# Source-matched coverage measurement and local CAN recovery - 2026-10-23

Existing hosted run39905420870 coverage job completed successfully at harness
114287185fada5f337fe1c13fdb1480f9e189f4f, CORE
50f38659db7b22f4689f3654df2d110d992bcc95. Both artifact source locks agree;
all seven coverage stages exit0. 17,379/17,714 lines (98.11%) and
12,242/13,800 branch outcomes (88.71%). Against run39903031655 on the same
CORE: +4 lines, +7 outcomes, no previously covered line lost. Gains are
stepper.c1367,1494,1501,1503. This is +0.023 line percentage points and
+0.051 branch percentage points, NOT the requested two-point increase.
Coverage classifier:4,215 total,4,170 clean,45known,0failed/0skipped.
All five hosted jobs now completed successfully (source, GCC, Clang, coverage,
CI diagnosis), confirmed by the run/jobs API at the exact harness head. Evidence: build-asan/hosted39905420870,
comparison39903031655.json. No new hosted dispatch.

Local CAN group expands receive_capacity through full-queue rejection, draining,
retry and FIFO delivery across ring wrap; adds receive-generated ACK ordering
behind a busy transmitter with exactly-once receive delivery. Both pass focused
ASan/UBSan0.35s in batch74-can-recovery-results.xml. Callback signatures match
can_rx_ptr (bool return). These are workflow checks on already-covered CAN paths;
no extra coverage gain is claimed. Together with the existing local reboot case
and selected-probe retry, they remain uncommitted pending a substantial batch.
No CORE edits, exceptions or known bugs added. Full supported coverage remains
incomplete; retain active goal and avoid repeated tiny validation checkpoints.

# Missing-contact selected-probe recovery - 2026-10-23

Extended existing G38.3/toolsetter missing-contact scenario through real rapid
retract toX0, restored contact threshold and successful G38.2 retry toX1.
Two public probe cycles complete, selection count4 restores default each time,
previous failure becomes probe_succeeded, contact records64..66steps and no
alarm/abort remains. Actual motor position follows both retract/retry; original
no-contact endpoint/assertions retained. No private position/counter reset or
new alias. ASan/UBSan passes0.07s;4,216 registered unchanged. Evidence
build-asan/batch74-probe-retry-results.xml. One new and one extended local
workflow now follow hosted1142871; keep grouped. CORE unchanged/no new allowance.

# Unsupported reboot capability preserves queued machining - 2026-10-23

First local follow-up after1142871 sends documented ESC/DC4 realtime reboot
sequence with an ordinary driver that has no reboot callback. It leaves the
queued planner head, idle state, abort/exec flags and physicalposition unchanged.
Subsequent public cycle-start executes the retained cut to exactly80Xpulses,
no Y/Zpulses, and returns Idle. No fake reboot callback or private reset flags.
ASan/UBSan passes0.07s;4,216 total registered. Evidence
build-asan/batch74-no-reboot-results.xml. No new exception or CORE edit.
Latest hosted39905420870 at1142871 remains pending; earlier1142871 cumulative
4,215-case gate passed133.27s. Keep extending74 without another hostedrun.

# Batch74 second cumulative delivery gate passed - 2026-10-23

Session43857 completed: build,CTest,strict summary all0.4,215 cases pass133.27s,
4,169 ordinary and46 documented local expected failures;0unexpected/0skipped.
Includes7 new workflows since fullygreen afdc32b and two precise PWM issues.
Narrow PWM allowance is compile-width gated; wider hosts retain ordinary test.
CORE remains clean50f3865; reporting scripts unchanged since75/75 helper gate.
Evidence build-asan/batch74-cumulative-{results.xml,gate.json,summary.log}.
Commit remaining zero-period regression/docs and push same74 for one hosted
source-matched checkpoint. Previous39903031655 verifies98.09/88.66 before
these7cases. No duplicate PR while28 remains open; never merge or edit CORE.
Full supported coverage remains incomplete; continue after dispatch.

# Batch74 seven-scenario cumulative gate running - 2026-10-23

One cumulative4,215-case ASan/UBSan/strict gate started on current74 after the
seven new workflows since afdc32b, including narrow PWM wrap and zero-period
failure regressions. Build0; unified exec session43857 is live. Inspect that
handle and build-asan/batch74-cumulative-{tests.log,results.xml,gate.json,summary.log}
before any retry. Do not restart merely because a wait times out.
Expected narrow-host46 known regressions, no new diagnostic allowances. CORE
remains clean50f3865. On success commit remaining PWM/sourceevidence group,
push same74 and dispatch one source-matched hostedcheckpoint. Prior exacthead
afdc32b fullygreen39903031655 remains verified98.09/88.66; later cases are not
included in that figure. PR28 remains separate and unmerged. Goal incomplete.

# Zero-tick PWM range detection regression - 2026-10-23

Fresh upstream fetch leaves clean CORE50f3865 unchanged. Seventh follow-up
after afdc32b confirms public precompute reports success for2MHz PWM on1MHz
clock:period/min/max all0, contrary to its documented false/no-range fallback.
Correct !ready assertion retained with one exact WILL_FAIL and dated KNOWN_BUGS
source/fix/removal evidence. No sanitizer diagnostic. Regression and ordinary
precompute/midpoint controls classify3/3 in0.31s; strict summary passes. Later
valid-frequency retry assertions remain after failure and are not claimed run.
Evidence build-asan/batch74-pwm-frequency-{raw.xml,results.xml,summary.log}.
4,215 registered;46 known on narrow local host,45 on wider hosts if reproduced.
Existing six-case checkpoint978ba50 remains local. No CORE changes or hostedrun;
continue independent supported coverage, then one substantial cumulative gate.

# PWM narrow-host ordinary-build confirmation and local checkpoint - 2026-10-23

Ordinary Clang raw execution also records fastintegerwidth2, result1000 versus
correct9000 and assertion exit1; no sanitizer dependence. Instrumented and
ordinary configure both prove narrow type and apply only the named allowance.
Ordinary CTest classification passes0.08s; raw artifact
build-asan/batch74-pwm-ordinary-raw.json plus ordinary-results.xml. Wider-host
ordinary assertion remains pending next cumulative hosted delivery.
Six local follow-ups beyond afdc32b are checkpointed as a coherent group across
UART ownership, initial driver levels, fine-feed hold, G95 rejection,12channel
I/O and PWM defect.4,214 registered; no CORE edits. Eight-module prior delivery
is fully verified39903031655; badge refresh shares that evidence. No repeated
full gate or hostedrun for this localcheckpoint. Continue substantial work.

# Narrow-integer PWM wrap regression - 2026-10-23

Sixth local follow-up confirms a real PWM conversion defect on16-bit
uint_fast16_t: legal scaled65440 plus minimum1000 narrows to904, then returns
minimum1000 for over-range request828 rather than expectedmaximum9000.
10MHz/1kHz precomputed duty range1000..9000; conversion itself fits16bits,
no sanitizer diagnostic. Correct assertion retained. One exact WILL_FAIL gated
by compiler proof UINT_FAST16_MAX==65535; wider hosts keep ordinary assertion.
Dated KNOWN_BUGS sourcecause/fix/removal entry added. Regression and existing
upper-clamp control classify2/2 in0.30s, strict summary passes. Evidence
build-asan/batch74-pwm-wrap-{raw.xml,results.xml,summary.log}.4,214 total;
45 expected local regressions now, with44 for wider-integer hosted configurations.
Wider-host execution still awaits the next substantial delivery checkpoint.
No CORE edits, diagnostic allowance or extra hostedrun. Continue independent work.

# Batch74 fully verified hosted checkpoint - 2026-10-23

Run39903031655 at afdc32b / clean50f3865: source,GCC,Clang,coverage,diagnosis
allterminalsuccess. Coverage and reporting source/harness/filter locks verified;
all7 stages0;4,208cases4,164clean44known0failed0skipped.17,375/17,714lines98.09%
and12,235/13,800branches88.66%. Same-source gain versus39900281002:6lines,
20branches, no covered-line loss. Badges and known-gap snapshot refreshed to
successful exactrun;339 raw linesremain. Five additional local cases (4,213total)
are not included in this measurement. Do not claim goalcomplete or launch CI
for badge-only edits. Keep substantial cross-module expansion on74; PR28 remains
separate at its verifiedhead. No CORE edits or merges.

# Twelve-channel I/O registration/remap/claim workflow - 2026-10-23

Fifth local follow-up registers a real12-input/12-output driver and verifies
P9/P10/P11 labels, high-index input/output remaps, sampled physical channels,
and exclusive plugin ownership after remapping. Claim consumes physical aux0
and returns its mapped number; plugin output reaches physical0 while remaining
G-code indexes reach11 and10 without aliasing. Initial virtual-number claim
expectation corrected against ioport_claim's documented aux-number contract.
Remap refreshes displaced slot description only; no unagreed destination-label
policy is asserted. Initial registered names and explicit plugin name remain
checked. ASan/UBSan passes0.06s;4,213 total. Evidence
build-asan/batch74-twelve-port-results.xml. Targets double-digit pnum offsets and
map/claim interaction without private state. No new allowances or CORE edits.
Hosted74 GCC passes; Clang remains live at lastcheck. Keep5 localcases grouped.

# Batch74 source-matched coverage gain - 2026-10-23

Hosted39903031655 coverage job terminalsuccess at afdc32b /50f3865. Coverage
and reporting artifact locks match selected harness/source/filter; all7 stages0,
4,208 cases:4,164 clean,44 known,0unexpected,0skip. Source-match comparison to
39900281002 (same50f3865, identical17,714line/13,800branch denominators):
17,375 covered lines98.09% and12,235 covered branches88.66%; +6lines/+20branches,
no previously covered lines lost. Raw339lines remain. Explicit per-line diff
saved build-asan/hosted39903031655/comparison39900281002.json.
Sourcejob also passes; GCC/Clang stilllive at last check, so overall checkpoint
and badge update remain pending. Do not dispatch again or claim compiler jobs
passed. Four additional local scenarios remain outside this report. Continue
supported work on74; PR28 unchanged, no CORE edits or merges.

# Encoderless G95 rejects without losing a two-spindle cut - 2026-10-23

Fourth local follow-up after afdc32b selects each of two real registered
encoderless spindle drivers via G95F0.2$1/$0. Both reject unsupported; G94/feed100,
independent3000/7000RPM directions, driver output counts and queued planner head
remain unchanged. Subsequent actual stepper execution completes exactly1,600X
pulses with no Y/Zsteps and idleempty queue. No fake feedback capability or
post-registration callback mutation. ASan/UBSan passes0.06s;4,212 cases now.
Evidence build-asan/batch74-g95-spindle-results.xml. Targets G95 single-spindle
selection and error-path preservation. Keep4 local workflows grouped outside
hosted afdc32b; no new exceptions, CORE edits or hosted dispatch.

# Fine-feed partial-block hold with parking enabled - 2026-10-23

Third local follow-up after afdc32b uses public parking setting and two queued
1mm feed blocks at0.5mm/min. Waits for a real first motor pulse, then feedholds
before the first endpoint. Four held service polls preserve stopped position;
resume completes exact160Xsteps with no Y/Zsteps, idleempty planner and no
abort. This targets stepper's sub-step hold termination/partial-block retention
with parking enabled; no parking/private planner flags are set by the test.
ASan/UBSan passes0.07s;4,211 total. Evidence
build-asan/batch74-fine-hold-results.xml. Coverage gain remains unmeasured until
next substantial checkpoint. Hosted74head still excludes these3 localcases;
no new exception, CORE edit or extra hostedrun.

# Driver initial stepper output levels - 2026-10-23

Second local follow-up beyond afdc32b calls public st_get_enable_out from the
real boot driver_setup callback after public $4=5 persistence and CORE settings
load. Confirms all-disabled startup levels respect mixed XYZpolarity when
idle-lock and permanently-energized masks are0; sender query agrees, boot exits
Idle with no queued motion/errors. Explicit driver API use matches stepper.c's
caller contract. Does not bless the separately unfinished energize-policy TODO.
ASan/UBSan passes0.07s;4,210 registered. Targets previously uncovered public
stepper initial-enable function. Evidence build-asan/batch74-driver-enable-results.xml.
No new allowance/CORE edits. Two local scenarios remain outside hosted74head;
keep accumulating cross-module work while39903031655 runs.

# Independent UART provider lifetime - 2026-10-23

Continued same74 while hosted39903031655 runs at afdc32b. New scenario uses
two separately registered UART providers and independent claim/release/handler
callbacks. Closing second searches past first, leaves first claim/RX/handler
unchanged; reclaiming second then closing first preserves second claim/handler.
Both finally release exactly through their own driver callbacks. No registered
metadata mutation or private stream pointer manipulation. ASan/UBSan passes
0.07s;4,209 total,one local case beyond dispatchedhead. Evidence
build-asan/batch74-provider-close-results.xml. No new exception or CORE edit.
Keep extending cross-module group; no extra gate/hosted dispatch for thiscase.

# Batch74 cumulative delivery passed - 2026-10-23

One cumulative4,208-case ASan/UBSan gate passes132.18s:4,164 clean,44 known,
0unexpected,0skipped. Build/CTest/strict summary all0; session8092 completed.
Evidence build-asan/batch74-delivery-{results.xml,gate.json,summary.log}.
Includes eight new cross-module workflows and expanded realtime-byte scenario;
no new exceptions. Reporting scripts unchanged from75/75 validated sourcehead.
CORE clean50f38659db7b22f4689f3654df2d110d992bcc95. Commit/push same74 and
one hosted checkpoint for source-matched coverage delta against39900281002.
PR28 remains ready/frozen a9f355c; do not merge or create duplicate cumulative
PR while it remains open. Full supported coverage still incomplete.

# Batch74 cumulative gate in progress - 2026-10-23

Authorized successor coverage-batch-74 retains local checkpoint6a0c872 plus
eighth settings-reload scenario and reachability notes. PR28 stays ready/frozen
at hosted a9f355c. Probe reload now covers absent toolsetter, absent secondary,
both absent and missing select callback before capable-driver recovery.
One cumulative4,208-case ASan/UBSan/strict gate is running in unified exec
session8092; build passed and actual CTest log observed progressing past575.
Do not start another gate if observation expires; poll8092 or inspect
build-asan/batch74-delivery-{tests.log,results.xml,gate.json,summary.log}.
CORE clean50f38659db7b22f4689f3654df2d110d992bcc95. After success commit/push
this cross-module batch and dispatch one exact-source hosted checkpoint; no
new PR needed while28 remains open. Full coverage remains unproven.

# Probe capability filtering preserves saved preferences - 2026-10-23

Eighth local new scenario stores public probing flags24 with both selection
capabilities, then reloads settings under supported driver capability/callback
combinations. Runtime disables missing secondary probe while retaining toolsetter;
physical NVS retains both saved choices. Missing selection callback disables
both runtime flags. Restoring capable driver and callback recovers saved24;
reload never actively switches probes. Uses registered host NVS/settings APIs,
not private sanity_check. ASan/UBSan passes0.07s;4,208 cases now. Targets
settings2292/2293 capability and callback short-circuit outcomes. Evidence
build-asan/batch73-probe-reload-results.xml. No new allowances or CORE edits.
Previous seven-case checkpoint6a0c872 remains local; continue cumulative batch.

# Realtime report clear contract audit - 2026-10-23

Continued from clean6a0c872. Exact source reportClearAll returns immediately
before observer notification; the later explicit ClearAll condition and MPG
zero-flags callback arm cannot run through public report_add_realtime. Existing
primary clear and independent pendant consumption tests remain correct.
Recorded source/line evidence and maintainer fan-out contract question inTODO;
no private callback invocation, invented assertion, allowance or source exclusion.
Seven new cases plus expanded protocol scenario remain local;4,207 registered.
No extra gate/hosted run. Continue supported remaining branch workflows.

# Coherent local workflow checkpoint - 2026-10-23

Seven new cases plus one expanded protocol scenario are checkpointed together:
driver PID settings registration, MPG boot status, persisted legacy polarity,
nonreleasable UART ownership, multi-spindle broadcast notifications, nested
rapid G66scope and reduced-RPM/manual-stop hold behavior. Each uncertain path
was resolved by source contract review and focused ASan/UBSan evidence recorded
below.4,207 registered;44 expected regressions unchanged. No shared infrastructure
or CORE edits. Reporting helpers unchanged since75/75 verified a9f355c gate.
No extra full gate/hosted run for this local checkpoint; next substantial push
must include one cumulative sanitizer/strict gate. PR28 stays ready/frozen at
verified a9f355c. New-source badge evidence remains39900281002, not local cases.
Further I/O allocation exploration duplicates the existing digital expansion
first-allocation regression; no extra alias was added. Continue branch work.

# Extended realtime plugin dispatch boundaries - 2026-10-23

Extended the existing consumed-control-byte test rather than adding aliases.
Plugin receives0x01/0x1f/0xaf/0xbf exactly once each, covering control-range
and reserved extended-command bounds with signed-char-safe comparisons.
Printable G-code bytes and serial delete bypass the unknown-command callback;
no realtime motion/reset flags appear. Existing retain-control companion passes.
ASan/UBSan2/2 passes0.28s. No case-count inflation:4,207 registered remain,
seven new local cases plus this expanded protocol scenario. Evidence
build-asan/batch73-plugin-byte-range-results.xml. No new exceptions/CORE edits.
Keep cumulative validation and delivery at the next substantial boundary.

# Reduced-RPM hold followed by manual spindle stop - 2026-10-23

Seventh local scenario configures public Setting_HoldActions=4 before motion
on the registered PWM spindle. Real feed hold reaches configured minimum RPM;
manual stop during completed hold stops output without motor movement. Resume
with restore disabled completes exact1,600-Xstep cut while hardware and modal
spindle stayoff, power0 and stopoverride clears. Initial retained-S expectation
was corrected against explicit gc_spindle_off semantics (gcode885 clears modal
spindle fields); no invented preservation contract or defect was recorded.
ASan/UBSan passes0.09s;4,207 total cases. Evidence
build-asan/batch73-reduced-hold-stop-results.xml. No shared fixture changes,
new allowance, CORE edit or hostedrun. Keep this coherent cumulative batchlocal.

# Nested rapid modal-macro scope - 2026-10-23

Sixth local follow-up adds real redirected RAM G65files with nested G0 moves.
Outer G66 stays dormant in both deeper local scopes and triggers once after
returning to the parent rapid, then G67 clears it. Existing public macro loader
owns/releases asynchronous call scopes; no private stack mutation. Check-mode
parser positions/scope/arguments and restored sender reader are asserted; no
motor execution is claimed. Rapid and existing feed controls pass ASan/UBSan
2/2 in0.31s.4,206 total registered. Targets gcode4766 call-level mismatch, not
the unresolved G66 arc contract. Evidence
build-asan/batch73-rapid-macro-scope-results.xml. No new allowance or CORE edit.
Keep six local scenarios grouped; PR28 remains exact-hosted-ready at a9f355c.

# Broadcast driver-notification workflow - 2026-10-23

Fifth local case after a9f355c exercises public M5/M3/M4 broadcasts with two
registered enabled spindles at independent3000/7000RPM and an unused third.
Plugin hook sees correct driver/mode/speed once per addressed command;
repeated stopped broadcast notifies without extra driver writes, primary-only
start followed by broadcast preserves mixed-state notification ownership, and
reversal updates both observable outputs. Changed states notify through
spindle_set_state_synced; unchanged states use parser fallback at gcode4331.
Scenario passes ASan/UBSan0.07s.4,205 cases now. Evidence
build-asan/batch73-broadcast-hook-results.xml. No new allowances or CORE edits;
keep accumulating supported branch workflows before a full/hosted gate.

# Driver UART lifetime and branch-gap ranking - 2026-10-23

Ranked exact39900281002 branch inventory:1,585 uncovered outcomes across
1,214 partly covered executable lines plus fully unexecuted regions. Reusable
ranked evidence build-asan/hosted39900281002/remaining-branches.json avoids
rescanning reports. Prioritize supported lifetime/driver/error workflows; merged
inlined outcomes and unimplemented extension paths are not a case quota.
Fourth local follow-up: driver advertises claimable UART with no releasecallback;
public open succeeds, repeated close refuses without disabling RX or releasing
claim, handler remains usable and second claim is rejected. No runtime callback
mutation, no synthetic source state. ASan/UBSan passes0.05s;4,204 total cases.
Evidence build-asan/batch73-nonreleasable-uart-results.xml. Existing owned-file
release-failure/retry controls remain separate. Keep this cross-module batchlocal;
no repeated full gate or hostedrun. PR28 remains ready at verified a9f355c.

# Exact latest-source hosted result - 2026-10-23

Run39900281002 at a9f355c / CORE50f3865: source,GCC,Clang,coverage,diagnosis
allterminalsuccess. Three artifact source/harness/filter locks verified; all7
coverage stages exit0,4,200 cases:4,156 clean,44 known,0fail,0skip.
17,369/17,714 lines98.05%;12,215/13,800 branches88.51%;345 raw linesremain.
Different source from prior68eba79: do not describe net+29lines/+38branches as
a same-source test gain. Badges and gap snapshot refreshed. PR28 exacthostedhead
can be ready without merging. Three further local scenarios stay outsidehead.
Evidence build-asan/hosted39900281002/{coverage-core,report-core-coverage,source-lock-core}.
Full meaningful supported coverage remains incomplete; rank this report next.

# Residual transport and registry audit - 2026-10-23

Inspected hosted39900281002: source successful, GCC/Clang/coverage stilllive;
no coverage artifact yet. Preserved3 local passing scenarios (4,203total).
Source audit confirms async timeout cannot enter the synchronous timeout-state
async fallback; documented exact transitions rather than manipulating flags.
Reset during synchronous retry remains a driver cancellation contract question,
separate from ordinary abort/active-reset tests. Corrected stale TODO advice:
invalid plugin metadata scenario already exercises missing lifecycle/getter,
invalid type, null descriptor/group and self-parent rejection before recovery.
No duplicate cases or extra CI. Updated TODO evidence keeps these residuals
visible in the denominator; full supported coverage remains unproven.

# Persisted legacy stepper-enable boot/reset workflow - 2026-10-23

Third local follow-up after a9f355c: legacy10 driver initialization uses the
public settings writer to persist $4=0, verifies physical NVSall-axis inversion,
then performs full settings initialization, sender query, softreset and query.
Both queries retain0, all-axis polarity remains loaded, parser returns metric
absolute and no sender errors occur. ASan/UBSan case passes0.05s;4,203 cases.
Targets settings_init compatibility normalization with a legitimately persisted
nonzero mask, no forged private state. No new exception. Evidence
build-asan/batch73-legacy-polarity-results.xml. Keep3 local scenarios grouped
for later substantial checkpoint; hosted39900281002 remains live at a9f355c.

# Registered MPG boot status workflow - 2026-10-23

Continued independent authoring while hosted39900281002 runs. New real boot
registers a UART MPG receiver via stream_mpg_register, advertises driver MPG
capability, and verifies one initial Idle/WPos status, normal $G/ok response,
no errors, primary reader ownership and disabled MPGmode. Default status policy
is work coordinates; initial MPos expectation corrected after inspecting output.
ASan/UBSan scenario passes;4,202 registered now,2 local cases beyond hostedhead.
No defect/allowance. Targets grbllib startup capability-triggered status path.
Evidence build-asan/batch73-mpg-boot-results.xml. Preserve cumulative batching.

# Registered closed-loop driver settings - 2026-10-23

Hosted39900281002 at a9f355c against50f3865 is confirmed live: sourcepasses,
GCC/Clang/coverage inprogress. No repeated dispatch. Continued locally with
a registered driver settings group and gain setting, supplied load/restore/save
callbacks, capability availability off/on/off, public gain write/persistence,
and unaffected spindle parent visibility. Initial group-only fixture omitted
mandatory lifecycle callbacks; corrected registry contract, no corebug claimed.
New scenario passes ASan/UBSan0.06s;4,201 cases now. Targets previously
uncovered settings_is_group_available closed-loop driver branch through public
registration. No new exceptions. Keep local until a substantial batch boundary.
Evidence build-asan/batch73-pid-group-results.xml. CORE clean50f3865.

# Batch73 latest-source delivery gate - 2026-10-23

Cumulative4,200-case ASan/UBSan gate passes137.36s:4,156 ordinary passes,
44 documented regressions reproduced,0 unexpected failures,0 skips. Strict
summary exits0.75 reporting helpers passed6.932s; ordinary Clang startup pair
passed0.40s. CORE remains clean50f38659db7b22f4689f3654df2d110d992bcc95.
Evidence build-asan/batch73-delivery-latest-{results.xml,gate.json,summary.log}.
Checkpoint includes7 new scenarios,9 verified fixed-exception removals with
assertions retained,26 named-file regressions, and one exact startup crash.
Push same73/PR28 and dispatch one hosted check against exact50f3865.
Do not merge or claim new-source coverage until its exact hosted report passes.
Full meaningful supported coverage remains incomplete; continue independent work.

# Startup-setting callback regression and control - 2026-10-23

No build/test process was active at heartbeat; resumed batch73 on clean50f3865.
Public $N0 with a rejecting registered comment callback exposes a new null-store
defect at gcode.c1154: system startup validation intentionally passes NULL for
the optional message output, while new rejection cleanup dereferences it.
Correct error/persisted-line/retry assertions remain after the fault. One exact
diagnostic wrapper and dated KNOWN_BUGS entry; accepting-callback control passes.
Both ASan/UBSan and ordinary Clang pairs classify correctly (0.46/0.40s), with
strict sanitizer summary. Matcher helpers75/75 pass6.932s including wrongline,
wrongfunction, additionaldiagnostic, marker and exitcode rejection controls.
Windows missing ASan lines require exact preceding UBSan source/line/function;
ordinary builds require exact callback-stage output and access-violation exit.
Logs batch73-startup-comment-* and batch73-startup-ordinary-*; total4,200 cases.
44 known regressions including this crash; no CORE edits, PRmerge or hostedrun.
Continue cross-module authoring, then one substantial cumulative delivery gate.

# Continued queue and upload workflows - 2026-10-23

Two new public-API scenarios take registration to4,198 on clean CORE50f3865.
RTU queues four below-capacity bursts, wraps head/tail multiple times, reuses
caller stack immediately and verifies each transmitted address/CRC, copied
context, FIFO reply and final idle state. RAM upload mixes13/1024/17/4096/9byte
chunks across buffered/direct writes, rejects unsupported growth without data
loss, reads23byte slices toEOF and seeks back across a flush boundary.
Both pass ASan/UBSan0.33s; strict summary passes; no new defect allowance.
Evidence build-asan/batch73-stream-burst-results.xml. Existing latest-source
full gate plus28 affected-case verification remain valid for their4,196cases.
Keep accumulating coherent cross-module work; no tiny hosted checkpoint.
Goal API stillreports blocked from prior state; heartbeat continues authorized
concrete work without spawning another worker. No CORE edits or PRmerge.

# Latest-source affected-case verification - 2026-10-23

Focused rerun of all28 prior failures passes1.23s:2 ordinary changed-contract
controls and26 exact known regressions. Strict summary passes. Evidence:
build-asan/batch73-compat-repair-results.xml and matching summary log.
Combined with the completed cumulative gate, all4,196 cases are accounted for:
4,153 ordinary passes and43 documented expected failures. This is combined
full-gate plus affected-case evidence, not a second full-suite run. Latest source
introduces the named-file regression; tests preserve correct public behavior.
No hosted check or new-source percentage claimed. Continue substantial batch73.

# Full latest-source compatibility findings - 2026-10-23

Session3963 finished: build0, 4,196 cases, 4,151 clean,17 known,28 failures.
26 failures share the new named-file CALL skip/lifecycle regression; correct
assertions retained with exact WILL_FAIL entries and dated KNOWN_BUGS evidence.
Two existing expectations updated for deliberate upstream contracts: comment
rejection now clears normalized text; unavailable G33.1 also rejects in check mode
without advancing position. No CORE edits. Focused compatibility rerun follows;
no redundant full gate or hosted dispatch before these changes validate.

# Latest-source compatibility cleanup - 2026-10-23

Clean ignored CORE now50f38659db7b22f4689f3654df2d110d992bcc95. Initial targeted
27case check exposes9 obsolete allowances. All9 unchanged regression executables
then directly pass under ASan/UBSan,exit0 withno diagnostics; evidence
build-asan/batch73-latest-fixed-raw.json. Removed only their9 WILL_FAIL labels,
7 resolved known-bug sections and directG65 fatal wrapper/manifest entry.
Retained every correct regression assertion. Fixes cover comment validation,
2message ownership cases,2MPGpull-up cases,G65empty-flow-stack return,unsupported
native tapping status,wrong-directory unlink afterOOM,current-drive format routing.

New4-axis delta XYZcontrol passes; A1 endpoint still emitszero steps on50f3865
(delta source unchanged), precise known regression retained. RTU burst known
reproduction stillclassified.4,196 registered overall;17 expected reproductions
remain under selectedsource if the cumulative gate confirms. No CORE edits.
Initial compatibility process84584 is completed; do not restart it. Full cumulative
sanitizer/strict gate,including cleaned compatibility cases,is now running in
unified exec session3963. Inspect that handle and batch73-latest-full logs before
any retry. This is the one broader gate for the source/header advance and new cases. Prior98.05%/88.53% belongs68eba79 only;
no new-source coverage claim. Keep related work on73/PR28; do not merge.

# Source advance and delta auxiliary configuration - 2026-10-23

Fetched Terje50f38659db7b22f4689f3654df2d110d992bcc95; clean previous68eba79
has known fixes now upstream in gcode/flow/VFS/I/O. Moving only the clean ignored
checkout to that unmodified source for a deliberate compatibility pass; never
patch CORE. Preserve prior68eba79 coverage/hosted evidence separately.

Two local N_AXIS4 delta realboot cases added using existing host fixtures. XYZ
control passes0.07s. Auxiliary-only A1 is acknowledged/parserA1 but driverA0 and
zero pulses; proper endpoint assertion fails, narrow WILL_FAIL and dated known
entry retained. Boot fixture now exits after acknowledged idle even if defective
motion never wakes driver, so it reports actual endpoint instead of read-budget
failure. Delta source unchanged by50f3865; latest-source runtime check pending.
RTU queue known reproduction classified; no new full gate or hosted dispatch.
Compatibility build/test process is running in unified exec session84584; poll
that handle or inspect batch73-latest-compat logs before retrying.
Next: finish known regressions against50f3865, inspect obsolete exceptions,
retain passing regressions and remove only runtime-proven fixed entries.

# Continued batch73 RTU backpressure authoring - 2026-10-23

New public-driver burst case confirms16 successful send returns but only7
transmissions/replies after1000ms of real RTU polling; zero exceptions/rejections.
Source330 skips full-ring admission then returns true for asynchronous calls.
Correct accepted/completed and retry assertions retained; dated KNOWN_BUGS entry
and one exact WILL_FAIL added. Focused sanitizer/strict classification passes0.26s asone known reproduction; no full
gate, push or hosted dispatch for this isolated case. Total4,194,with25 expected
reproductions under ASan once the next cumulative gate runs. CORE freshly fetched
unchanged68eba79. Existing evidence-only badge edits and all local work preserved.
Continue a substantial group before delivery; goal flag remains blocked but the
hourly recovery can perform authorized concrete work. No competing worker found.

# CURRENT CHECKPOINT - exact batch73 hosted gate verified - 2026-10-23

PR28 head2c62fee65a8892dbd2f00e3d6064b5f52121b2e0 oncoverage-batch-73 has
all5 individual hosted jobs terminalsuccess inrun39859126742. Artifacts
12461368002/12460698374 both lock2c62fee/cleanCORE68eba7906ba60d66c8b55c4adc90cd5e85b5a828/
corefilter. All7 coverage stagesexit0. Coverage4,193cases/4,170clean/23known/0/0;
ASan/UBSan local4,169clean/24known because the direct G65 return only faults
under instrumentation. No failed or skipped cases. GCC formatting repair proved
on hosted source; prior39852077540 remains a failed historical run.

Verified coverage17,340/17,684 lines98.05%,12,177/13,754 branches88.53%.
Recovery group adds13branches vs35abd4e,zero additional lines andnone lost.
CombinedPR28 adds10lines/35branches vs91938f1.344 raw lines remain; known
unavailable implementation is retained in denominator. README/known-gap snapshot
updated locally to this passing exact-head report; these evidence-only edits are
not yet committed, so no redundant hosted run is needed for them alone.

PR28 marked ready for review after this verified gate; not merged. Continue
supported coverage onthis branch in substantial groups. Goal UI flag is still
blocked; heartbeat can perform authorized work but exposed goal tools cannot
reactivate automatic continuation. Recovery remains scheduled hourly.

# CURRENT CHECKPOINT - batch73 recovery gate - 2026-10-22

coverage-batch-73 tracksorigin/coverage-batch-73; pushed35abd4e is draftPR28:
https://github.com/grblHAL/Unit_tests/pull/28. All local follow-ups preserved.
CORE remains clean68eba7906ba60d66c8b55c4adc90cd5e85b5a828, freshfetch unchanged.

Hosted39852077540 at35abd4e is completed/failure. GCC's exact G65 global-buffer-
overflow was rejected only because its ASan top frame/summary omit columns.
Actual source774,ngc_flowctrl,index-1 UBSan and fault type match. Local matcher
now accepts optional ASan columns while retaining exact source/line/function/
fault and required UBSan location.10 matcher checks pass0.457s,including changed
source,line,function and unrelated diagnostic rejection; real GCC artifact matches.
The original hosted JUnit remains failed and must not be called green. A new
exact-head hosted check is required after the combined follow-up delivery.

That run's complete coverage job passed all7 stages; artifacts12458771355/
12458008457 verify35abd4e/68eba79/corefilter.4,185 cases,4,165clean/20known/0/0
(non-sanitizer G65 return passes).17,340/17,684 lines and12,164/13,754 branches:
+10lines/+22branches vs91938f1,none lost. Newlines gcode1737/1798/1799/1801/1803,
ioports834,motion_control593/625,spindle_control636,stepper1464. Overall matrix
failure means badges remain on earlier successful39837233097:98.00%/88.28%.

Eight additional local cases now register4,193 overall. Focused groups validate:
RAM handle-allocation recovery; nested leaf without local status callback;
root-directory calloc failure/retry and existing trailing-slash mount listing;
partial RTU exception/normal/wrong-device headers followed by valid reply;
interrupt-only input refusing reads without consuming neighboring input.
RTU fixture now waits the mandatory post-reply silence before asserting idle.

Two additional confirmed CORE defects have dated KNOWN_BUGS entries and three
exact WILL_FAIL labels: truncate-to-zero keeps pending RAM upload commands;
failed digital/analog provider calloc reports success and publishes phantom
ports. Correct content/count/retry assertions retained. Existing neighbors work
before bank failure assertions; no nonexistent port is dereferenced. No CORE edit
or new sanitizer suppression. Latest focused bank classification0.29s passes as
2 known reproductions. Logs build-asan/batch73-file-*,batch73-bank-allocation-*,
batch73-driver-recovery-* andbatch73-partial-rtu-repair-*.

Prior full gate at35abd4e:4,185 in134.66s,4,164clean/21known/0failed/0skipped;
72 helpers passed. Recovery cumulative gate passes4,193 in134.46s:
4,169clean/24known/0failed/0skipped; build/CTest/strict exits0.73 Python helpers
pass6.700s. Exact evidence build-asan/batch73-recovery-gate.json and matching
build/test/summary/helper logs. No repeated full gate is needed for this head.
Combined checkpoint2c62fee committed andpushed,trackingorigin/coverage-batch-73.
PR28 updated and remains draft. One updated-head hosted run39859126742 dispatched
against68eba79; inspect this run rather than restarting it. No new coverage gain
attributed before its artifact. Do not merge. Completion is unproven.

Recovery heartbeat found goal UI status blocked despite available independent
work; concrete validation resumed. Goal status cannot be reactivated through
the exposed update_goal tool. Keep respecting explicit user pauses/usage limits.

# Flow-control error cumulative gate and confirmed backlash wait gain - 2026-10-22

Full4,160-case ASan/UBSan passes82.19s:4,144 clean,16 known,0 failures/skips.
Build/test/strict all0 in batch72-flow-errors-gate.json. Unknowninitial/barelabel
rejection andnumericSUB recordOOM/retry validated together. No allowances/CORE
edits. Localgroup awaits delivery/hosted gain.

Allfive jobs on39828039606 at4616165 terminalsuccess. Artifacts12447802567/
12447773947 lock461616550703e3c95f6a342f9853a737b43464da/source68eba79/
corefilter;all stages0,4,156/4,140clean/16known/0/0.17,304/17,684lines97.85%,
12,116/13,754branches88.09%:+2lines/+2branches versus2b0cc0c. Newlycovered
machine_limits587 andmotion_control163 confirm split-rate rejection andfirstpoll
backlashwait target.380 raw lines remain. README/knownsnapshot updated. Later
091fc1c39829068251 compilerpending;73a2abf39829941823 running.

# Numeric SUB definition allocation failure and retry - 2026-10-22

New actualfile/publicparser O10SUB case rejects scoped recordcalloc,returnsOOM,
retains exact file/reader with no close or callscope. Retry defines successfully,
bodyassignment staysskipped,ENDSUB restores execution and nextassignmentupdates
parameter42to43. Properfile cleanup. Reuses existing flow/calloc fixtures; narrow
pertest calloc linker option alongside namedmacro counterpart. Targets flowctrl659.
Focused sanitizer passes0.37s. Total4,160,no allowances/CORE edits. Grouped with
unknownkeyword controls pending cumulative validation and measured gain.

# Unknown O-code initial and bare label rejection - 2026-10-22

Extended existing misspelled keyword/recovery case with O10XYZ andO10Z[1],
exercising general unknown-initial syntaxerror atngc_flowctrl199-200. Existing
parameter42/noalarm/noabort/emptyplanner controls retained and validIF assignment
stillrecovers. BareO10 is rejected earlier by mainparser asUnusedWords,so distinct
assertion follows that actual contract rather than classifying it asflowkeyword.
Focused sanitizer passes0.35s. No new cases/allowances/CORE edits,total4,159.
Local batch begins; cumulative gate and measured gainpending.

# Default driver callbacks cumulative gate - 2026-10-22

Full4,159-case ASan/UBSan passes77.95s:4,143 clean,16 known,0 failures/skips.
Build/test/strict all0 in batch72-default-drivers-gate.json. Defaultweak passthrough
command and default Modbus exception handling through realRTU validated together.
No new allowances/CORE edits. Local group delivery/hosted gain pending.

Allfive jobs on39826891832 at2b0cc0c individually terminalsuccess. Artifacts
12447807241/12447012617 bothlocks2b0cc0caeff0510b2aa4924c18becb3cb9cf98b0,
source68eba79/corefilter;all reportstages0,4,155/4,139clean/16known/0/0.
17,302/17,684lines97.84%,12,114/13,754branches88.08%:+1line/+1branch
versus277db12 (machine_limits611).382 raw lines remain. README/knownsnapshot
updated.4616165 run39828039606 Clangpending;091fc1c39829068251 running.

# Default Modbus exception handler releases transport for next reply - 2026-10-22

Extended existing realRTU exception/recovery case to deliver illegal-address
exception firstwithoutcallback,thenwith supplied modbus_null_exception_handler.
Both complete without userfailure callback or packet delivery; subsequent valid
request sends thirdframe and receives exactlyone response. Targets modbus129/132
through registered transportcallback,not directemptyfunction call. Focused sanitizer
passes0.33s. No new case/allowance/CORE edit; total4,159. Grouped with default
passthrough command case pending cumulative gate and hosted measurement.

# Default passthrough driver entry preserves connection ownership - 2026-10-22

New normal$PTRGH command case uses default weak stream_passthru_enter instead
of replacement. Command warning/delay executes,default hook returns with passthru
false,no USB/UART handler installation,no reset/boot pinchanges,cancel0 and no
linestate hook. Targets stream_passthru33/36. Focused sanitizer passes0.32s.
No success of programming/driver transition claimed. Total4,159,no allowances or
CORE edits. Next cumulative batch starts; gain pending hosted measurement.

# Inversion/sleep cumulative gate and green homing snapshot - 2026-10-22

Full4,158-case ASan/UBSan passes73.06s:4,142 clean,16 known,0 failures/skips.
Build/test/strict all0 in batch72-square-sleep-gate.json. Asymmetric inversion
publicwrites and sleep scheduling pressure/retry validated together. No new
allowances/CORE edits. Local group awaits delivery/hosted gain.

Allfive individual jobs on39826209629 terminalsuccess. Artifacts12446239029/
12446827666 both lock277db12dfae59d7a4bebb056f24c7c3db081e18c/source68eba79/
corefilter;all reportstages0,4,153/4,137clean/16known/0/0.17,301/17,684
lines97.83%,12,113/13,754branches88.07%:+1line/+2branches versus6a8d34f.
New machine_limits327.383 raw lines remain. README/known snapshot updated.
2b0cc0c run39826891832 Clangpending;4616165 run39828039606 running.

# Sleep timeout task-pool pressure and retry - 2026-10-22

New public scheduler/sleep case fills available delayed-task pool with valid future
plugin tasks. Sleep check cannot schedule timeout:returns immediately,noinputreads
or schedulerpolls,no sleepflag,stillIdle. Deleteone task and advance50ms;retry
schedules timeout,expires through normal callback andrequestsSleep. Remaining
plugin tasks neverexecute and aredeleted;IRQdepth0. Targets sleep39 without heap
wrappers/private pool writes. Focused sanitizer passes0.27s. Initial task_delete
return assumption corrected to declared void API. Total4,158,no allowances/CORE
edits. Grouped with asymmetric inversion for cumulative gate/hosted gain.

# Asymmetric auto-square public limit inversion propagation - 2026-10-22

New normal settings-store case appliesY inversion thenX-only thennone. Actual
registered kinematics settings hook propagatesY to secondaryaxis3,clearssecondary
whenY clears,preservesX,and chains prior settings notification once perwrite.
Targets asymmetric_ganging287 under supported auto-square build. Focused sanitizer
passes0.40s. Total4,157,no allowances/CORE edits. Next cumulative batch starts.

# Homing refusal/backlash wait cumulative gate - 2026-10-22

Full4,156-case ASan/UBSan passes74.17s:4,140 clean,16 known,0 failures/skips.
Build/test/strict all0 in batch72-homing-refusal-gate.json. Later-axis driverrefusal
with earlieraxis retained,publicretry and refined firstpoll backlash reset validated
together. No new allowances/CORE edits. CORE remote still68eba79 andclean.

Allfive individual jobs on39824927291 at6a8d34f nowterminalsuccess. Prior locked
artifacts rechecked:17,300/17,684lines97.83%,12,111/13,754branches88.05%,
384 raw uncovered lines. UpdatedREADME/known snapshot.277db12 run39826209629
coverage/source success,compilerspending;2b0cc0c run39826891832 running. Current
localgroup delivery/hosted gainpending. Sender homing status question retainedTODO.

# Backlash full-queue abort event boundary refinement - 2026-10-22

Existing reset scenario now uses long100mm leading cut and requests actual reset
on first service poll,processed at compensation-space wait. Source/trace review:
cycle-start transfers first planner block to stepper,freeing slot even for long
move; secondpoll reset was too late and allowed compensation append. Firstpoll
reset processes before transfer,returnsAborted,keeps exact previous lastblock
(no compensation append),no pulses/physical movement,onecallback. Focused sanitizer
passes0.32s. Targets motion_control163; measured gain stillpending. No new cases,
allowances or CORE edits. Grouped with split-rate provider failure for cumulative gate.

# Later split-rate homing provider refusal and recovery - 2026-10-22

New public homing API case requests configuredXYZ with unequal rates; X completes
110pulses/homedX,driver refusesY seek rate,API returnsUnhandled and failure callback;
YZ emit0,queueempty,Idle/noabort. Provider recovery and public$HY succeeds with
150Ypulses,homedXY;Xunchanged,Zneverstarted. Targets machine_limits587. Focused
sanitizer passes0.35s. Initial$H return expectation corrected after source review:
system.go_home deliberately mapsUnhandled toOK,so direct exportedhomingAPI used
for status assertion. No new defect/allowance claimed. Total4,156,CORE unchanged.

# Y/Z autosquare cumulative gate - 2026-10-22

Full4,155-case ASan/UBSan suite passes71.20s:4,139 clean,16 known,0 failures
or skips. Build/test/strict all0 in batch72-square-axis-gate.json. Shared simulated
axis selector preserves existingX cases and validates publicY/Z independenttrim
homing with no other-axis pulses. CORE clean,no new allowances. Delivery pending.

Prior6a8d34f coverage39824927291: artifacts12446203148/12446682058 bothlocks
6a8d34f7bef01a0ead460b2a2fd448d293135c7b/source68eba79/corefilter;all stages0,
4,151/4,135clean/16known/0/0.17,300/17,684lines97.83%,
12,111/13,754branches88.05%:+3lines/+5branches versusfac105e.
New tool_change204/364/368. GCC/Clang remain running; no allgreen claim or badge
refresh. Current277db12 run39826209629 also running. LocalY/Z gain unmeasured.

# Y/Z auto-square axis selection and independent trims - 2026-10-22

Generalized existing autosquare simulated motor axis from fixedX to selectable
index(defaultX,existing behavior retained). New public$HY positiveoffset0.25 and
$HZ negativeoffset-0.25 cases verify primary/secondary final70/90 and50/110steps,
only selected axis homed,other axis pulses0,motors reenabled,Idle and no abort.
Targets machine_limits611 loop pastX through valid driver registration. Built all
20 autosquare targets together; focused ASan/UBSan20/20 passes1.71s. Total4,155,
no allowances/CORE edits. Shared fixture change requires next full cumulative gate
before delivery; existing assertions unchanged.

# Homing/manual-control cumulative gate and green snapshot - 2026-10-22

Full4,153-case ASan/UBSan passes58.80s:4,137 clean,16 known,0 failures/skips.
Build/test/strict all0 in batch72-homing-manual-gate.json. Public zero-travel
homing/recovery and physicalmanual restore validated together. No new allowances
or CORE edits. Local group awaits delivery/hosted gain.

Runs39823116932 and39823928447 allfive jobs individually terminalsuccess.
Latestfac105e artifacts12445943834/12444859897 both lock exact
fac105e42075ae3d776aedb3e950c3084612242c/source68eba79/corefilter; all stages0,
4,148/4,132clean/16known/0/0.17,297/17,684lines97.81%,
12,106/13,754branches88.02%:+7lines/+9branches sincepublished59b8f60;
+4/+4 since1582c74. New tool_change177/506/517/524 in latestgroup;
previousgroup ngc_params1011,tool_change200/531.387 raw lines remain.
README/known snapshot updated. Newer6a8d34f run39824927291 stillrunning.

# Public zero-travel homing and recovery - 2026-10-22

New public settings/homing case stores maxtravel0,executes X homing,no wake/pulses
or homedX,empty planner; restores travel10 and normal homing produces pulses and
homedX whileYZ staystill. Targets machine_limits327. Initial recovery failed due
fixture issuing step IRQs while motor was never awakened; directtravel10 control
passed. Local wake/idle wrappers now gate IRQ service correctly,with no shared
fixture change. st_is_stepping was insufficient before first actual ISR; replaced
with driver wake tracking after stopping that stalled authoring run. Corrected
focused sanitizer passes0.27s. No core defect/allowance claimed. Total4,153;
grouped with physicalmanual restore pending cumulative gate/hosted measurement.

# Physical manual-change restore after touch-off - 2026-10-22

New serialT3M6/G10L2P1Z0 workflow acknowledges change, then sends two physical
cycle-start events before foreground task. No immediate motion; actual restore
returns to160/240/-80steps,clears change,restores stream/control handlers and
normal realtime transition emits exactlyone tool3 completion. Targets false arm
of physical-control execute_probe/execute_restore dispatch attool_change364.
Focused sanitizer passes0.27s. Total4,152,no allowances/CORE edits. Local group
awaits cumulative validation/hosted gain.

# Toolsetter/physical controls cumulative gate - 2026-10-22

Full4,151-case ASan/UBSan suite passes57.73s:4,135 clean,16 known,0 failures
or skips. Build/test/strict all0 in batch72-tool-controls-gate.json. Includes reset
before setterZ and physical-cycle-start automatic/G30 paths with duplicatepresses.
No new allowances/CORE edits. Local group awaits delivery/hosted gain.

Prior1582c74 coverage39823116932: artifacts12444694343/12444988901 locks exact
1582c74411155d104664d0afd96e54af7826b0ed/source68eba79/corefilter; all report
stages0,4,145/4,129clean/16known/0/0.17,293/17,684lines97.79%,
12,102/13,754branches87.99%:+3lines/+5branches versus59b8f60.
New ngc_params1011 andtool_change200/531. GCC/Clang remain running; published
snapshot stays green97.77/87.95. Currentfac105e run39823928447 also running.

# Physical cycle-start tool workflows - 2026-10-22

Two new actual HAL control-callback cases cover physical cycle-start while automatic
toolsetter waits and manualG30 return-to-fixture waits. Send duplicate press before
foreground execution; no immediate pulses. Automatic probe establishes reference,
restores originalXYZ and probe/command handlers; subsequent normal realtime service
emits one tool-change completion. G30 return reachesfixture1,1,-2 while retaining
manual-change wait and no completion. Targets tool_change364/368 control path,
complementing existing serial-resume tests. Built together,focused sanitizer2/2
passes0.32s. Initial completion assertion preceded required realtime transition;
serviced public transition before asserting. Total4,151,no allowances/CORE edits.
Grouped with pending toolsetterZ reset for cumulative gate.

# Reset before toolsetter Z approach - 2026-10-22

New Manual_G59_3 case observes normal queued toolsetterXY target via public planner
and sends actual reset before nextZ submission. Driver change returnsReset,one
reset/positioncallback,no XYZ pulses or completed tool notification; physical
160/240/-80 retained and latest queued targetZ stays0 rather thanapproach-2.
Targets tool_change204. Focused sanitizer passes0.27s. Total4,149,no allowances
or CORE changes. Pending next cumulative group validation/hosted measurement.

# Tool-change queue reset cumulative gate - 2026-10-22

Full4,148-case ASan/UBSan suite passes57.49s:4,132 clean,16 known,0 failures
or skips. Build/test/strict all0 in batch72-tool-queue-reset-gate.json. Initial
retract and G30XY/finalZ reset boundaries validated as group. No new allowances
or CORE changes. Local head awaits delivery/hosted gain.

Allfive jobs on39821728933 at59b8f60 terminalsuccess. Coverage/report artifacts
12445023812/12445896104 both exact59b8f600d2157444e4353c8409992620318ae918,
source68eba79/corefilter; all stages0,4,143/4,127clean/16known/0/0.
17,290/17,684lines97.77%,12,097/13,754branches87.95%:+1line/+1branch
versus7270deb (motion_control1064). Backlash reset scenario did not cover163;
retain this remaining gap without claiming gain.394 raw uncovered lines remain.
Published snapshot links/counts refreshed.1582c74 hosted run39823116932 running.

# G30 intermediate queue reset controls - 2026-10-22

Two new manual-change cases send actual reset after initial retract is queued
(beforeXY traverse) and afterXY is queued(before finalZ approach). Shared small
fixture observes public planner target to select event boundary; no static/private
state changes. Both driver changes returnReset,one reset,noXYZ pulses or completed
tool notification,physical160/240/-80 retained; latest queued target remains prior
stage atZ0. Targets tool_change517/524. Built together,focused sanitizer2/2 passes
0.33s. Total4,148,no allowances/CORE edits. Grouped with initial retract reset.

# Reset before initial manual-tool retract - 2026-10-22

New real manual change case sends public reset on initial motion service poll.
Driver change returnsReset,one reset callback,no pending tool-change or completed
notification,empty planner and zeroXYZ pulses; physical160,240,-80 unchanged.
Targets tool_change177/506. Focused sanitizer passes0.28s. Total4,146,no
allowances/CORE edits. This begins next cumulative tool-change error batch.

# Resource/stop cumulative gate and fully green coverage - 2026-10-22

Full4,145-case ASan/UBSan suite passes59.85s:4,129 clean,16 known,0 failures
or skips. Build/test/strict all0 in batch72-resource-stop-gate.json. String third
entry growth, actual probe protection stop completion and reset before toolsetter
traverse validated together. No new allowances/CORE edits; local delivery pending.

Allfive individual jobs on39820646831 terminalsuccess at7270deb. Downloaded
12444129239/12445625277; both locks exact7270deb8fb6bc43910c0f09fef7eb66b821d7356,
source68eba79/core filter; all report stages0,4,141/4,125clean/16known/0/0.
17,289/17,684 lines97.77%,12,096/13,754branches87.95%:+9lines/+7branches
versus prior published964457f. Newfs_embedded257,gcode2431,planner807,
report848/849,stepper2 149/150/191/192.395 raw lines remain. README/known
snapshot updated. Newer59b8f60 run39821728933 remains running.

# Toolsetter position callback reset prevents traverse - 2026-10-22

New real Manual_G59_3 tool-change case installs positioning callback that sends
normal realtime reset before go_toolsetter submits XY. Driver change returnsReset,
sys.abort set,tool-change flag clears,one position callback/driver reset,no completed
tool notification and no XYZ pulses; physical160,240,-80 unchanged. Initial
assumption Z home already executed was corrected: go_linear_home queues it, then
position callback runs before queue synchronization. Targets tool_change200/531.
Focused sanitizer passes. Total4,145,no allowances/CORE edits. Cumulative gate pending.

# Later string parameter growth retains list ownership - 2026-10-22

New public string API case stores four entries, grows third from5 to240chars,
checks both predecessors and successor unchanged, deletes/reinserts third and
checks every entry before cleanup. Uses actual allocator; relocation-specific
branch gain is measured later, not forced by private list manipulation. Targets
remaining ngc_params1011 traversal when growth relocates. Focused sanitizer passes
0.28s. Total4,144,no allowances/CORE edits; grouped with probe stop completion.

# Probe protection stop completes through public realtime service - 2026-10-22

Extended existing unexpected probe IRQ case beyond request flags: execute normal
realtime stop, verify cancellation returnfalse, actual Alarm_ProbeProtect with
pending alarm cleared, empty planner,no pulses/position change and ALARM:13 output.
Source protocol551-592 confirms cancellation returnfalse is expected, not a
continuable service return. Focused sanitizer passes0.26s. No new case/allowance
or CORE edit; no unmeasured state-machine branch gain claimed. Local group starts.

# Probe/backlash reset cumulative gate - 2026-10-22

Full4,143-case ASan/UBSan suite passes, build/test/strict all0 recorded in
batch72-reset-windows-gate.json.4,127 clean,16 documented expected failures,
0 failures/skips. Includes public reset after probe setup and while full planner
waits for backlash reversal. No new allowances/CORE changes. Local group awaits
hosted gain; full reset path callbacks are provided by fixtures.

Run39818343521 at964457f now allfive individual jobs terminalsuccess. Artifact
locks/stages previously verified; published snapshot updated to17,280/17,684
lines97.72% and12,089/13,754branches87.89%,404 raw uncovered lines. Later
metadata39819657478 Clang stillrunning; latest7270deb run39820646831 running.

# Probe reset after setup before planner submission - 2026-10-22

New real probe-registration case installs public probe-start observer, then sends
normal realtime reset on first motion service poll. mc_probe_cycle returnsAbort,
sys.abort set,no success/completion,no X pulses or position change,empty planner.
Targets motion_control1064 prequeue abort. Status_Aborted is deliberately0, so
boolean motion checks are valid; no bug claimed. Initial callback signature fixed
to declared bool provider type. Focused sanitizer passes0.27s. Total4,143; no
allowances/CORE edits. Grouped with backlash full-queue reset for cumulative gate.

# Reset during full-queue backlash reversal - 2026-10-22

New public motion case enables backlash, queues forward motion, fills planner with
valid driver lines, then requests reversal. Realtime observer sends normal reset
while compensation waits. ReturnsStatus_Aborted,sys.abort set,no X pulses/physical
position change,and requested zero endpoint absent from latest plan block.
Focused ASan/UBSan passes0.27s; total4,142. Initial fixture lacked mandatory
control/coolant/reset callbacks; corrected locally. Initial frozen/empty planner
assumptions were invalid because normal realtime servicing stages queued blocks;
assert observable abort/nonmovement instead. No defect/allowance/CORE edit claimed.
Exact abort branch gain remains for hosted coverage, not assumed from timing.

# Planner/files/parser cumulative gate - 2026-10-22

Full4,141 ASan/UBSan suite passes60.11s:4,125 clean,16 known,0 failures/skips.
Build/test/strict all0 in batch72-planner-files-gate.json. Includes third asset
catalog, driver plan initialization with acceleration profile, explicit G33.1I
check-mode parsing and pitch reuse. No new allowances/CORE changes.

Prior964457f coverage39818343521: artifacts12443293519/12444650465 lock both
harness964457f73230556d5b047dedd5012197c5873672/source68eba79/core filter;
all report stages0,4,138/4,122clean/16known/0failed/0skipped.17,280/17,684
lines97.72%,12,089/13,754branches87.89%:+3lines/+4branches versusd89ca53.
New lines gcode4737/4738,settings1926. GCC/Clang remain running, so published
snapshot stays fullygreen97.70/87.87. Current local group awaits hosted gain.

# Explicit tapping multiplier dry-run parser path - 2026-10-22

Extended existing synchronized-command check-mode case with G33.1Z2K0.2I2,
accepting and consuming explicitI multiplier, updating simulatedZ2/pitch0.2,
retaining overrides and empty planner. Following G33Z3 reuses pitch0.2 without
motion. Targets gcode2431. Native tapping runtime remains separately documented
unsupported-status bug; no execution-support claim or exception changes. Focused
sanitizer passes. No new case/CORE edit; pending cumulative batch validation.

# Driver planner initialization under selected acceleration profile - 2026-10-22

New acceleration-profile case queues G187P5 feed at20% acceleration, initializes
normal driver plan data and submits actual mc_line. Driver block gets default
factor1/acceleration36000 and800 steps toX20; previous G-code block retains7200,
modal factor remains0.2. Targets planner807 under enabled supported configuration.
Focused ASan/UBSan passes0.26s. Total4,141,no allowances/CORE edits. Grouped with
third embedded catalog extension pending cumulative gate/hosted measurement.

# Third embedded catalog preserves reader and enumeration - 2026-10-22

Extended existing catalog append case to register three distinct asset catalogs
while first asset reader is open. Directory enumerates first/later/last exactly
thenEOF; reader retains offset2 and remainingcde. Targets fs_embedded257 append
traversal without touching known cross-list name-lookup defect. Focused sanitizer
passes. No new cases/allowances/CORE edits; next cumulative batch begins here.

# Metadata/report cumulative gate and green coverage snapshot - 2026-10-22

Full4,140-case ASan/UBSan suite passes59.38s:4,124 clean,16 documented
expected failures,0 failures/skips; build/test/strict all0 in
batch72-metadata-report-gate.json. Includes bound-spindle metadata provider
fallbacks and M99 callback report. CORE clean/latest remote remains68eba79.
No new allowances. Current local group awaits delivery/hosted gain.

Allfive individual jobs on39816875087 are terminalsuccess. Previously verified
artifact locks/stages now support publishing its17,277/17,684 lines97.70% and
12,085/13,754 branches87.87%;407 raw uncovered lines. Updated README and known
gap snapshot. Exact newer964457f hosted run39818343521 still running.

# M99 callback modal reporting - 2026-10-22

New report case registers normal macro-return provider and executes M99. Callback
sees ProgramFlow_Return, requests public modal report, verifies complete GC frame
with spindle-off state and no invented M99 modal word; parser resumes Running
and callback fires once. Targets report848-849 default using valid transient
program-flow state rather than invalid enum injection. Focused sanitizer passes
0.27s. Total4,140,no new allowances/CORE edits; cumulative gate pending.

# Stepper spindle optional metadata providers - 2026-10-22

New eight-axis case binds actual spindle motor with optional prior unit/description
hooks unset. Bound step-resolution metadata is supplied; bound driver-current
and unbound-axis metadata both returnNULL without dereferencing missing provider.
Focused ASan/UBSan passes0.31s. Total4,139,no allowances/CORE edits. Grouped
with previous-provider fallback extensions; pending cumulative gate/hosted gain.

# File reader fallback reachability audit - 2026-10-22

Remaining stream_file.c72 is a no-file fallback in the private reader. Reviewed
normal redirect close: restores saved reader before restoring file stream; existing
close_restores_input verifies final serial reader and close count. No supported
workflow identified to reach fallback; recorded source evidence in TODO without
private callback manipulation or fake failure. Stepper metadata test group remains
local pending cumulative validation. No CORE changes.

# Bound stepper-spindle driver metadata fallback - 2026-10-22

Extended existing eight-axis metadata cases with driver motor-current setting
on the spindle-bound A axis. Unit and description callbacks preserve the previous
provider values rather than substituting spindle units. Targets stepper2.c149-150
and191-192 defaults using valid driver axis-setting identifier. Focused sanitizer
2/2 passes0.35s. No new cases/allowances/CORE edits; cumulative validation pending.

# Motion recovery cumulative gate and prior batch coverage - 2026-10-22

Full4,138 ASan/UBSan passes58.58s; build/test/strict all0 recorded in
batch72-motion-recovery-gate.json.4,122 clean,16 known,0 failed/skipped.
CORE unchanged; no new allowances. Rapid callback refusal/retry, queued arc
recovery and missing-setting value handling validated together.

Prior head d89ca53 coverage run39816875087 completed coverage/source, while GCC
and Clang remain running. Artifacts12442099474/12443365993 locks verified to
harnessd89ca535a8b9c16f91370fbaf48cdae532bb3a3b/source68eba79/core filter;
all stage exits0,counts4,138/4,122/16/0/0.17,277/17,684 lines97.70%,
12,085/13,754 branches87.87%:+8lines/+18branches versus green1049a01.
New lines encoders46,modbus249,nuts_bolts278/279/305/306,strutils114/115.
Do not call whole hosted run green or advance badges before compiler/diagnosis.

# Missing setting lookup/value boundary - 2026-10-22

Extended existing unknown-setting rejection with actual public detail lookup
returningNULL and setting_get_value(NULL,0) returningNULL before failed store.
No notifications remain asserted. Focused sanitizer passes; targets settings1926
without synthetic registered metadata. No new case/allowance/CORE change.
Pending cumulative gate with motion callback recovery group.

# Custom M-code reader guard audit - 2026-10-22

Existing normal-required-value and plugin-valueless tests already cover contracts.
Uncovered post-reader NaN rejection at gcode1471 cannot be reached with expression
reader: nonfinite status returns first, while explicit valueless NaN excludes the
guard. Added source evidence to TODO/known gap table, no duplicate tests or fake
expected failures. CORE unchanged; motion recovery test edits remain local.

# Motion extension queued-work recovery control - 2026-10-22

Extended existing arc rejection scenario to queue a valid160-step X cut, reject
a clockwise arc through registered extension, retain same sole planner block and
parser2,0, then retry after driver recovery. Retry appends arc while preserving
first block and reaches parser3,-1; exact callback counts/turn direction checked.
Focused ASan/UBSan passes0.28s. This strengthens recovery assertions; no measured
coverage gain claimed. No new cases/allowances/CORE changes. Pending cumulative
gate with rapid error-path addition and coverage audit documentation.

# Rapid extension rejection and recovery - 2026-10-22

Extended existing cutter motion-extension rejection scenario to G0: driver error
propagates, target reaches callback, parser XY stays origin and planner stays
empty. Re-enable actual previous motion handler and retry G0X3Y4: parser reaches
3,4, planner records240/320 steps and rapid flag. Three line callbacks, no arc
callbacks. Focused ASan/UBSan passes0.26s. Targets gcode4737-4738 missing rapid
error path. No new case/allowance/CORE change. Pending cumulative validation.

# G-code message cleanup reachability audit - 2026-10-22

Audited raw uncovered gcode.c4238 against enclosing4231 guard: check-mode arm
cannot execute because outer block excludes that mode and no callback/assignment
intervenes. Added source evidence to TODO and known coverage gap table, retaining
denominator. Broadcast override gap already documented; no duplicate tests or
fake expected failures. Coverage snapshot docs from green39814748999 remain local.

# Fully green I/O checkpoint and measured branches - 2026-10-22

Run39814748999 at1049a015df5cdbb8a2180f9621f51e29851e0b65/source68eba79
has allfive individual jobs terminalsuccess(source,GCC,Clang,coverage,diagnosis).
Downloaded coverage/report artifacts12441717480/12442811224; both locks match
exact harness/source/core filter; allseven report stage exits0.4,136 total,
4,120 clean,16 known,0 failed/skipped. Coverage17,269/17,684 lines97.65%,
12,067/13,754 branches87.73%: unchanged lines,+24 branches versus published
39811711030; +9 branches versus expression39812566612. README badges and known
gap snapshot refreshed. Newer spindle and utility/Modbus heads remain pending.

# Encoder/utility/Modbus cumulative gate - 2026-10-22

Full4,138-case ASan/UBSan suite passes58.57s:4,122 clean and16 documented
expected failures; no failures/skips. Build/test/strict exits all0 recorded in
build-asan/batch72-boundaries-gate.json. Includes third-encoder append/recovery,
bounded overlapping search, numeric retained-precision overflow, and unsupported
Modbus response recovery. CORE clean, no new allowances. Hosted gain pending.

# Modbus unsupported response and recovery - 2026-10-22

New public high-level transaction case injects transport response function0
(unassigned table entry) and255(out of range), checks completion exception255
with zero values, then valid read after each returns current register0x1234 and
cleared exception. Exact four request/completion counts verified. Uses existing
transaction fixture with local transport wrapper, no shared-fixture changes.
Focused ASan/UBSan passes; total4,138. No new allowances or CORE changes.
Pending combined utility/encoder/Modbus cumulative gate and hosted measurement.

# Bounded overlap search and numeric precision overflow - 2026-10-22

Extended existing bounded-search case with aaab/AAB overlap restart and AAX
negative control (strutils114-115). Extended float signs case with twelve-digit
integer and twelve-digit fractional input, preserving next-axis cursor; numeric
checks allow normal float precision while exercising dropped-digit exponent and
fraction handling (nuts_bolts278-279,305-306). Focused ASan/UBSan2/2 passes0.46s.
No new cases/allowances/CORE changes. Combined with encoder append group for next
cumulative validation; measured gain remains pending hosted report.

# Encoder third-driver append and heap recovery - 2026-10-22

Locked report39812566612 leaves encoders.c46 uncovered: third registration
traverses an existing linked-list next node. Extended existing enumeration order
case to three real driver objects, with callback bounds and exact pointer order.
Extended allocation-recovery case to fail third append, retain count2, then retry
and enumerate all3 in order. Focused ASan/UBSan2/2 passes0.33s. No new cases,
allowances or CORE changes; pending next cumulative gate and hosted measurement.

# Spindle API cumulative validation - 2026-10-22

Full4,137-case ASan/UBSan gate passes57.98s:4,121 clean and16 documented
expected failures; no failures/skips. Build/test/strict exits all0 in
build-asan/batch72-spindle-api-gate.json. Includes complete three-driver enumeration
with unclaimed callback return and current-driver identity, identifier boundaries,
empty enumeration/capabilities, configuration refusal/retry and raw/configured
capability isolation. CORE remains clean; no new allowances. Hosted gain pending.

# Spindle capability views and empty enumeration - 2026-10-22

Extended configuration recovery to have the actual config callback advertise
runtime direction support: configured aggregate and enabled driver reflect it,
raw registration aggregate and original driver remain unchanged. Extended empty
registry case with a valid callback that must never run, plus zero raw/configured
capabilities. Focused ASan/UBSan2/2 passes0.37s. Total4,137; no allowances or
CORE changes. Local spindle group remains pending cumulative gate and hosted gain.

# Spindle identifier boundary controls - 2026-10-22

Extended existing multi-spindle cases with negative and upper-bound enable IDs,
negative name/raw/configured lookups, and missing active lookups. Rejections
preserve default spindle and configuration counts, leave other slots disabled;
valid active lookup still resolves the selected driver. Focused ASan/UBSan2/2
passes0.33s. No new allowances or CORE edits; count remains4,137. Together with
configuration-refusal retry, this local spindle group awaits cumulative validation.

# Spindle configuration refusal and activation retry - 2026-10-22

New public registration/selection case passes ASan/UBSan0.27s. Registered real
basic driver rejects firstconfig:selectfalse,slot disabled,getNULL,default-2,
no selected callback. Provider recovery/retry configures again,activates once,
preserves real callbacks;repeat selection does not reconfigure/notify again.
Targets spindle_control104 failure and249 disabled-default branches. Uses engine
fixture with tiny local driver; unrelated listing fixture had a non-inline unused
setup warning,so avoided that fixture without weakening compiler flags or editing
shared infrastructure. Total4,137 cases,no new allowances/CORE edits. Local
spindle batch begins here; cumulative gate/hosted gain remain pending.

# I/O claim/search capability batch cumulative gate - 2026-10-22

Full4,136-case ASan/UBSan build/test/strict passes(all0):4,120 clean,16 known
reproductions,no failed/skipped. Evidence:build-asan/batch72-io-claims-gate.json,
delivery XML/log,strict log. One new provider-refusal/routed-retry case and three
extended search/capability/control-assignment scenarios. No new allowances/CORE
changes; upstream68eba79 unchanged. Search ordering with filter0 remains explicit
TODO question. Deliver coherent group on existingPR26; objective incomplete.

All five39811711030 jobs terminal success,eaead02/68eba79; verified locked
coverage17,269/17,684 lines97.65%,12,043/13,754 branches87.56%. Badges updated.
Expression39812566612 source/GCC/coverage passed,Clang live; locked artifacts
verify17,269 lines unchanged,12,058/13,754 branches87.67%,+15 branches on same
source/filter;4,135/4,119 clean/16 known/no failed/skipped,stages0.
Newer VFS39813351754 source passed,remaining jobs live at last check; artifacts
exist but not yet read. Local I/O group needs its own exact-head hosted report.

# Control assignment without optional capability record - 2026-10-22

Extended existing control-input assignment case:public CycleStart assignment with
empty driver_caps succeeds and preserves existing signal capability mask; then
FeedHold assignment with supplied capability record sets that bit. Exact callback
counts,function,available-input count and independent output bank checks remain.
ASan/UBSan1/1 passes0.28s. Targets ioports413 optional-record false branch, no
new executable/fixture/CORE change/allowance.4,136 unchanged. Existing rejection
case already covers provider refusal, so no redundant copy authored. Local I/O
batch now one new/three expanded scenarios, ready for cumulative gate/delivery.

# Missing claim/pin-info callback rejection and recovery - 2026-10-22

Expanded existing explicit-claim capability case beyond query flags:actual claim
with missing provider returnsNULL; missing pin-info handler returnsNULL/UNASSIGNED.
Both leave pins unclaimed and advertised count2. Restoring handlers makes claim
succeed with original pin/relay description and exactly one fewer free output.
ASan/UBSan1/1 passes0.27s. Covers ioports325/get_info272 guard outcomes using
supported absent-driver capability surface. No CORE edits/new allowance/case.
Total4,136; local I/O batch one new provider-refusal scenario/two extensions for
search and capability recovery. Cumulative validation remains for batch boundary.

# Driver claim refusal and routed retry - 2026-10-22

New public ownership scenario passes ASan/UBSan0.26s. One provider claim callback
returnsfalse for valid output0:resultNULL/indexUNASSIGNED,free/advertised counts2,
both pins unclaimed,description untouched. Restore normal provider and retry:
exact physical pin0 claimed,counts decrement once,Vacuum description retained,
returned handle drives original physical output0. Existing host and actual claim/
remap API reused; no private ownership forcing/CORE change/new allowance.
Targets ioports332 provider-failure branch. Total4,136 cases. Local I/O batch
one new case/one extended search scenario; cumulative gate still pending.
Hosted39811711030 source/GCC/coverage/Clang individually succeeded at last check;
diagnosis not yet listed,so do not claim full five-job completion.

# Claimable port search bounds and empty description - 2026-10-22

Expanded existing description lookup with explicit claimable filter:upper bound0
returns0,bound1 returns1,empty description returns last port1. Both pins remain
unclaimed,free count2 and named description unchanged. ASan/UBSan1/1 passes0.26s.
Targets ioports216 false-bound and244 empty-description branches; no new case/
CORE edit/allowance.4,135 unchanged. Unfiltered search initially returned0 because
enumeration with filter0 is ascending; documented source/comment discrepancy in
TODO rather than silently asserting a universal descending-order contract.
Keep local I/O batch for cumulative validation.

# VFS observer-boundary batch full validation - 2026-10-22

Full4,135-case ASan/UBSan build/test/strict passes(all0):4,119 clean,16 documented
reproductions,no failures/skips. Evidence:build-asan/batch72-vfs-observers-gate.json
plusdelivery XML/log/strict log. Four existing mkdir/rmdir/rename/writable-close
scenarios extended for absent observer; mkdir backend failure/retry emits correct
notification counts. No new executable/allowance/CORE edits. Upstream clean68eba79
unchanged. Deliver coherent observer group on existingPR26; objective incomplete.

Hosted39811711030 exacteaead02/68eba79/filter artifacts verified,stages0:
17,269/17,684 lines97.65%,12,043/13,754 branches87.56%,+0 lines/+3 branches.
4,134/4,118 clean/16 known/no failed/skipped,including isolated real M72 defect.
GCC/Clang live at last check. Newer expression39812566612 source succeeded,
remaining jobs live. This local VFS group still needs its own hosted report.

# Writable close without observer and hosted settings checkpoint - 2026-10-22

Expanded existing writable-close case with second public writable open after
observer removal: provider identity/update flag/path preserved,exact second
backend close,no extra notification. ASan/UBSan1/1 passes0.33s. Targets vfs342
callback-absent branch; no new executable/CORE edit/allowance.4,135 unchanged.
Local VFS batch now four extended filesystem cases, ready for cumulative gate.

All five individual jobs39810197175 terminal success at31718f9/68eba79. Verified
locked artifacts17,269/17,684 lines97.65%,12,040/13,754 branches87.54%,
4,132/4,117 clean/15 known/no failed/skipped. Refreshed badges/gap summary,
415 raw uncovered lines. Newer39811711030 source passed,coverage/GCC/Clang live.
Current M72 allowance count16 appears only in later heads, not this old report.

# Filesystem optional-observer and backend-failure branches - 2026-10-22

Three existing VFS scenarios expanded together, ASan/UBSan3/3 passes0.49s.
Successful mkdir/rmdir/rename still forward exact backend-local paths with no
registered change observer. mkdir backend failure returns-1 and emits no event;
corrected retry succeeds and notifies once. Previous normal-observer/path/count
assertions remain. No new executable/fixture or allowance,4,135 tests unchanged.
Targets partial branches vfs407/435/453 using public API/provider results only.
CORE untouched; cumulative gate/hosted branch gain deferred to batch boundary.

# Expression branch batch full gate - 2026-10-22

Full4,135-case ASan/UBSan build/test/strict passes(all0):4,119 clean,16 known
reproductions,0 failures/skips. Evidence:build-asan/batch72-expression-branches-
gate.json,delivery XML/log,strict log. Four existing Boolean/comparison scenarios
extended with seven missing truth-table outcomes; one new real-reader scenario
covers malformed signs/decimal syntax and valid signed fractions/axis stopping.
No new allowance/CORE edits. Upstream clean68eba79 unchanged. Deliver coherent
expression group on existingPR26. Full supported objective remains incomplete.

Hosted39810197175 source/GCC/coverage passed,Clang still live. Verified31718f9/
68eba79/filter locks and report stages0:17,269/17,684 lines97.65%,12,040/13,754
branches87.54%,+1 line/+8 branches same source.4,132/4,117 clean/15 known,
no failures/skips. New line settings805, expected configuration-specific guard.
Newer39811711030 source passed,remaining jobs live at last check; local latest
expression batch requires its own exact-head coverage report.

# Public real-reader malformed/sign boundaries - 2026-10-22

New focused real-number reader case passes ASan/UBSan0.28s. Empty input returns
ExpressionSyntaxError; dangling signs/decimal points and lowercase nonnumber
return BadNumberFormat. Following+.5X/-.25Y parse correct signed fractions and
stop at the next axis letter. No assumptions about output on rejected input,
private parser calls or new allowances. Targets partial ngc_expr811/814/818/821
branches. Total4,135. Local expression batch now one new/four extended scenarios
with seven added truth-table outcomes; cumulative gate pending. CORE unchanged.

# Expression truth-table branch completion - 2026-10-22

Expanded four existing public expression cases with seven missing outcomes:
XOR0/0 and0/nonzero,AND0/nonzero,ORnegative/0,GEfalse,NEequal andNEpositive
difference. Negative nonzero operands verify Boolean interpretation; existing
full-input consumption checks remain. Grouped build and ASan/UBSan4/4 passes
0.80s. No new executable/fixture/CORE change/allowance; total4,134 unchanged.
Targets partial branches atngc_expr138/142/150/172/173/182. Exact hosted gain
still pending. Keep grouped with next parser/expression coverage work.

# Modal/G84 policy batch cumulative gate - 2026-10-22

Full4,134-case ASan/UBSan build/test/strict passes(all0):4,118 clean,16 documented
reproductions,no unexpected failures/skips. Evidence:build-asan/batch72-modal-
policy-gate.json,delivery XML/log,strict log. New G84 pre-disabled-control case,
scoped direct-restore ownership extension and isolated M72 percentage-only bug
regression all included. New allowance is one exact known_bug/WILL_FAIL; correct
80/50 assertion retained after actual65/25 result, snapshot cleaned before failure.
No CORE edits or sanitizer suppressions. Six private constant-flag false arms
source-audited without exclusions. Clean upstream68eba79 unchanged. Deliver group.

All five individual39808684184 jobs terminal success at0f2406d/68eba79. Locked
coverage17,268/17,684 lines97.65%,12,032/13,754 branches87.48%,4,131 tests/4,116
clean/15 known/no failures/skips. Badges/gap summary now this fully green report,
416 raw executable lines uncovered. Newer39810197175 source passed, remaining
jobs live; this latest modal group needs its own exact-head report.

# G84 helper flag branch audit - 2026-10-22

Verified all call sites of static override_disable/override_restore:one each,
constant all-enabled flags. Six false guard arms atgcode174/180/185/198/205/208
are unreachable under current callers, documented in TODO/coverage-gap table.
Do not confuse these with saved disabled-policy branches199/210, covered by the
new real G84 control test. Raw denominator/CORE/assertions unchanged. Existing
M72 percentage-only defect remains isolated exactWILL_FAIL; continue independent
work. No full objective/coverage completion claim.

# Confirmed modal percentage-only restore defect - 2026-10-22

New correct M70/M72 regression: saved80/50, changed65/25 with unchanged enable
flags, M72 returnsOK but leaves65/25. Raw sanitizer assertion failure retained;
exact WILL_FAIL/known_bug and dated source-cause/fix/removal entry added. Snapshot
freed before failing assertion; no diagnostic allowance/CORE edit. Existing
root/scoped direct restore now also verifies separate snapshot ownership using
legal flag-change restoration; passes focused. Two-case raw result1 pass/1 real
failure0.34s. Total4,134,16 known allowances now. Continue independent work.

# G84 retains preexisting disabled override policies - 2026-10-22

New supported tapping scenario passes ASan/UBSan0.28s. Public M49 thenM53P0
establish disabled spindle/feed overrides and hold beforeG84Z-1R0P0. After actual
160 Z pulses/retract to0 and spindle forward1000, both modal/runtime policies
remain disabled; subsequentG80/M48/M53P1 reenables controls. Existing canned
spindle fixture reused, no source/private-state changes or allowances. Initial
combinedM49M53 fixture block violated modal grouping; corrected to legal blocks.
Targets missing restored-disabled branches gcode199/210, not duplicate enabled
restore behavior. Total4,133 cases; keep local for cumulative parser batch.

# Settings branch batch cumulative gate - 2026-10-22

Full4,132-case ASan/UBSan build/test/strict passes(all0):4,117 clean plus15
known reproductions,0 failed/skipped. Evidence:build-asan/batch72-settings-
branches-gate.json plus delivery XML/log and strict log. One new mixed8-axis
pulse setting scenario, three existing Boolean inversion/acceleration/jerk
scenarios extended. Metadata default reachability documented without exclusions.
No CORE edits/new allowances; clean upstream68eba79 unchanged. Deliver grouped.

Hosted39808684184 coverage/report locks verified0f2406d/68eba79/filter; all
stages0,4,131/4,116 clean/15 known/no failed/skipped.17,268/17,684 lines97.65%,
12,032/13,754 branches87.48%,+10/+11 same-source. New lines:machine_limits93/
94/312/842 anddelta236/237/259/260/591/602. GCC/Clang still running at latest
check; no full hosted/current settings-head coverage claim. Objective incomplete.

# Override reset before backup exists - 2026-10-22

Extended existing acceleration and jerk restore scenarios with public zero reset
before first positive override. Configured values12345 acceleration/216000 jerk
remain unchanged; subsequent multiple overrides and restoration assertions remain.
Grouped ASan/UBSan2/2 passes0.35s. Targets missing false branches of backup-valid
checks settings578/601, no private backup manipulation/new executables/allowances.
Total4,132 remains. Local batch now one mixed-axis case/three expanded legacy/
override scenarios plus metadata audit, ready for substantial cumulative gate.
CORE unchanged; hosted coverage gain not yet measured for local additions.

# Compatibility Boolean inversion round trips - 2026-10-22

Branch audit found partial settings646/654 despite covered lines. Expanded
existing compatibility10 Boolean metadata case to write1 then0 for step-enable
and limit inversion, verify exact axis-mask translation and normalized getter
values in both directions, then checksummed persisted values. Original invalid2
assertion retained. ASan/UBSan1/1 passes0.28s. No duplicate executable, CORE
edit or allowance;4,132 total. Local batch one new/eight-axis setting case and
one expanded legacy scenario plus metadata reachability audit; keep grouped.

All five individual jobs39807024328 are now terminal success,d0b2f90/68eba79.
Existing locked artifacts verify17,258/17,684 lines97.59%,12,021/13,754 branches
87.40%,4,129 total/4,114 clean/15 known/no failed/skipped. Refreshed badges/gap
summary,426 raw uncovered lines. Newer39808684184 source passed, compiler/
coverage jobs live at latest check; no current-head green claim.

# Mixed eight-axis pulse-width configuration - 2026-10-22

New supported8-axis case uses public rotary-mask and pulse-width settings. With
8 runtime axes and mixed rotary mask40,8.5us pulse setting succeeds, emits one
change notification and persists exact width/mask in checksummed NVS. Focused
ASan/UBSan passes0.30s. Existing3-axis pulse tests do not compile the N_AXIS>3
guard; this targets settings805 without changing source/configuration variants.
validate_pulse_width rate computation is commented out upstream; no claim of
physical timing validation or invented failure. Total4,132 cases, no allowances.
Keep local metadata/settings batch for cumulative gate/push. CORE unchanged.

# Metadata guard reachability audit - 2026-10-22

Classified report1955-1956: complete declared datatype enum is handled after
Int8/Int16 normalization to Integer. Recorded exact enum/conversion/switch source
in TODO and coverage-gap table. No invalid enum injection, fake WILL_FAIL or
coverage exclusion. This does not classify other residual lines as unavailable.
CORE unchanged. Hosted39807024328 latest individual endpoints:source,coverage,
GCC succeeded;Clang still running. Newer39808684184 remains separate current
head validation; no claim of merge readiness or completed objective.

# Limits/homing/delta cumulative gate - 2026-10-22

Full4,131-case ASan/UBSan build/test/strict passes(all0)61.76s:4,116 clean plus15
known reproductions,no failed/skipped. Evidence:build-asan/batch72-limits-delta-
gate.json,delivery XML/log,strict log. Two new cases/three extensions cover driver
homing-rate rejection/retry with actual pulses, short delta segment validation/
endpoint, unhomed travel guard, rotary-excluded IRQ handling, and nonlinear delta
clip validation in both coordinate domains. No CORE changes/new allowances.
Clean upstream68eba79 unchanged. Zero-locate reference contract remains TODO,
not a fabricated expected failure. Deliver coherent group on existingPR26.

Hosted39807024328 coverage/report locks verifiedd0b2f90/68eba79/filter; stages0,
4,129/4,114 clean/15 known/no failed/skipped.17,258/17,684 lines97.59%,
12,021/13,754 branches87.40%,+9/+15 same source. New lines:modbus_rtu239-240/
242-244/273/509/529,report2898. GCC/Clang still running at latest check;
current limit/delta group requires its own exact-head hosted report.

# Nonlinear clipped delta target accepted in both coordinate domains - 2026-10-22

Extended existing positive-X nonlinear jog clip case: finite inverse alone is
insufficient, so check the resulting Cartesian endpoint and converted motor
coordinates through grbl.check_travel_limits with all XYZ homed. Both accepted,
ASan/UBSan1/1 passes0.26s. Reuses real clipping/transform/limit callbacks; no
private geometry edits or new allowance. Targets fallback motor-coordinate
validation after cuboid fast path; exact new coverage awaits hosted report.
Count unchanged4,131. Current local batch two new cases/three extensions across
limits, driver homing recovery and delta geometry is ready for cumulative gate.
CORE unchanged; no claim of completed full supported objective.

# Delta short-move validation and endpoint - 2026-10-22

New delta public-kinematics scenario passes ASan/UBSan0.26s:0.01mm X move at
Z-300 starts unvalidated, becomes accepted, returns exactly one finite positive-
feed segment, reconstructs XYZ endpoint within0.001mm through quantized motor
coordinates. Existing delta fixture/conversion precision convention reused.
Targets delta236-237 successful validation and259-260 unsegmented short-move
path. No internal state edits/CORE changes or new allowances. Total4,131 cases;
local batch now two new cases/two expanded limit/homing scenarios. Full gate
remains for cumulative delivery. This validates kinematics, not physical hardware.

# Driver-provided homing rate unavailable/retry - 2026-10-22

New supported provider-boundary case passes ASan/UBSan0.27s. Driver feedrate
callback returns0 for initial Y seek while normal global X seek remains valid.
Public mc_homing_cycle returnsUnhandled, restoresIDLE, reports failed completion,
no homed bits/pulses. After normal realtime poll/provider recovery,$HY succeeds:
Y physical110/reference-10,150 pulses,other axes untouched,successful callback.
Existing homing fixture reused, no private phase forcing/CORE edits/allowances.
Targets machine_limits312; total4,130 cases. Unlike pending zero-locate policy,
this rejection occurs before any seek motion. Local batch one new/two expanded
limit/homing scenarios; cumulative gate still pending.

All five individual jobs39804789709 now terminal success for b473a27/68eba79.
Verified locked coverage17,249/17,684 lines97.54%,12,006/13,754 branches87.29%,
4,127/4,112 clean/15 known/no failed/skipped. Badges/known-gap summary refreshed
435 raw uncovered lines. Newer39807024328 source passed,coverage/compilers live.

# Excluded rotary-limit interrupt boundary - 2026-10-22

Extended existing8-axis rotary hard-limit setting case beyond metadata: invoke
public limit IRQ handler with empty signal and excluded rotary min/max mask40.
Verify last-event snapshot, state, realtime flags/alarm and abort flag unchanged,
while enabled nonrotary mask215 and driver enable remain. Focused ASan/UBSan
1/1 passes0.27s after adding the required state_machine declaration include.
Targets machine_limits93-94 via valid registered settings, no source edits or
private-state injection. Existing hard-limit reset tests retain enabled-axis
positive coverage. Count remains4,129, no new allowances. Two local limit cases
now extend existing scenarios since publishedd0b2f90; batch full gate deferred.

# Unhomed travel-limit boundary - 2026-10-22

Extended partial-homing clipping test with initial unhomed calls, both endpoint-
only and positioned travel API. All target coordinates and caller position remain
unchanged; existing homed-X-only clipping assertions remain. Focused ASan/UBSan
1/1 passes0.31s. Targets machine_limits842 through supported installed callback,
no new fixture/CORE edits/allowances. Count remains4,129; keep local for batch.

Zero locate feed rate after successful search has ambiguous reference semantics:
source clears cycle axis before final reference assignment but merges previous
homed mask. Recorded exact concern in TODO rather than inventing expected final
coordinates or registering an unsupported failure. No runtime defect claimed.

# Modbus/startup batch full validation - 2026-10-22

Full4,129-case ASan/UBSan build/test/strict passes(all0):4,114 clean plus15
known reproductions,no failed/skipped. Evidence:build-asan/batch72-rtu-startup-
gate.json,delivery XML/log,strict log. Two new RTU scenarios cover automatic UART
fallback through rejected/invalid claims plus real reply, and nested synchronous
send rejection/later recovery. Existing timeout scenario spans two scheduler ticks;
normal boot now queries empty spindle list in both formats. No CORE changes or
new allowances; latest upstream remains68eba79. Deliver together on existingPR26.

Hosted39804789709 coverage/report locks verifiedb473a27/68eba79/filter; stages0,
4,127 tests/4,112 clean/15 known,no failures/skips.17,249/17,684 lines97.54%,
12,006/13,754 branches87.29%,+4 lines/+7 branches same source. New lines exactly
gcode2819,ngc_flowctrl340,ngc_params1077,stream428. GCC/Clang live at last check;
retain prior fully green badge baseline. Latest batch needs its own hosted report.

# Normal boot with no real spindle: sender query boundary - 2026-10-22

Extended existing complete startup scenario with$G/$SPINDLES/$SPINDLESH stream.
Normal core dummy-spindle boot retains0 real registered devices, human query
reports No spindles registered, queries emit no error, setup/release counts and
welcome/driver-start assertions remain. Focused ASan/UBSan1/1 passes0.27s.
Targets report2898 via real sender workflow, no synthetic inventory/private state.
Registered total unchanged4,129. Current local batch now two new Modbus cases
and two expanded scenarios (timeout scheduling and boot reporting); no CORE
changes or new allowances. Previous hosted39804789709 source passed, compiler/
coverage jobs live at latest individual endpoint check; no artifact yet.

# Modbus timeout across scheduler ticks - 2026-10-22

Extended existing dedicated-timeout/recovery scenario to service two timer ticks
per foreground callback using existing public task executor. Allows poll to see
pending synchronous TimeoutException before sender resumes, without modifying
private protocol state. Exact one timeout, no exception/reply, one transmission,
then next independent request receives valid1234 reply. Focused ASan/UBSan passes
0.34s;4,129 cases unchanged. Local Modbus batch now two new/one expanded cases.
No new exceptions, fixture variants or CORE edits.

All five individual jobs of39802929753 now terminal success atba111a2/68eba79.
Verified coverage/report artifacts already17,245/17,684 lines97.52%,
11,999/13,754 branches87.24%,4,127 tests/4,112 clean/15 known/no failed/skipped.
Updated badges/known-gap summary to fully green report,439 raw uncovered lines.
Newer39804789709 source passed;coverage/GCC/Clang still live at last check.

# Blocking Modbus callback re-entry guard - 2026-10-22

New real reply callback attempts another blocking send. Exact false return and
unchanged TX count verify guard273; outer reply completes once with1234 payload,
then a subsequent independent blocking request succeeds. Focused ASan/UBSan1/1
passes0.56s using existing RTU blocking scheduler/CRC fixture. No private calls,
state forcing or timeout allowances. Distinct from unresolved asynchronous
spin-lock re-entry policy: this synchronous callback executes outside poll lock
while is_blocking remains set, with explicit rejection contract in source.
Total4,129 cases; two new local Modbus scenarios sinceb473a27, no CORE changes
or new expected failures. Keep building batch before cumulative gate/push.

# Modbus automatic UART selection recovery - 2026-10-22

New public initialization scenario passes focused ASan/UBSan0.28s. Inventory:
non-Modbus port and already-claimed port must never be claimed; next ready port
claim fails, next returns an incomplete driver, final valid UART succeeds. Public
modbus_rtu_init(-1,-2) selects it, settings load exposes live transport, request
transmits once and a CRC-checked reply returns1234 payload with no exception.
Existing RTU fixture and polling reused, no new host variant or private states.
Targets automatic selection/invalid-claim guards509/529; new total4,128 cases.
No CORE edits or expected failures. Keep local for next substantial API batch.

Failed-startup detailed driver diagnostic is already a policy question in TODO;
do not duplicate it or call its private formatter to chase grbllib140-150.

# Parser/list/stream cumulative delivery gate - 2026-10-22

Full4,127-case ASan/UBSan build/test/strict gate passes(all0),4,112 clean plus15
known reproductions,0 failures/skips. Logs/XML/JSON:build-asan/batch72-parser-
stream-*. Four existing scenarios extended for G51/G50 lathe UVW geometry,
undefined subroutine callback after valid registration, absent/repeated string
parameter deletion, and disabled-base serial fallback after network disconnect.
No new executable or allowance; CORE clean68eba79 and upstream unchanged.
Residual four-line reachability proof included in TODO/KNOWN_BUGS without
changing raw coverage. Deliver together on existing branch/PR26.

Hosted39802929753 exactba111a2/68eba79 coverage/report locks/filter verified,
all stages0:17,245/17,684 lines97.52%,11,999/13,754 branches87.24%,+9/+11
same-source.4,127/4,112 clean/15 known/no failed/skipped. New lines:ioports1220/
1262,spindle_control154/445,vfs467/498-500/871. Individual GCC/Clang endpoints
still running; retain older fully green badge checkpoint until all finish.

# Lathe UVW scaling and cancellation - 2026-10-22

Expanded existing UVW absolute-mode scenario through public G51/G1/G50 blocks.
Starting10/24/36, scale2/2/4 plusU4V2W3 yields14/28/48 (U remains diameter
increment); G50 then identical increments yield16/30/51. G90 remains active.
Focused ASan/UBSan1/1 passes0.29s. Targets previously missing gcode2819 UVW
scaling with existing LATHE_UVW_OPTION fixture; check-mode parser geometry only,
no claim of additional physical motor coverage. Registered count stays4,127,
no CORE edits or new allowances. Current local batch has four extended scenarios
(stream fallback, callback miss, string deletion miss, UVW scaling) plus residual
reachability evidence; cumulative full gate remains for the next delivery boundary.

# Macro and string-list missing-entry boundaries - 2026-10-22

Two existing scenarios expanded, grouped ASan/UBSan2/2 passes0.34s. A failed
callback registration for undefined label999 traverses populated subroutine list
without invoking/replacing the valid label10 callback; subsequent real call/return
still restores parameter scope and invokes it once successfully. String deletion
of absent999 traverses all three entries, preserves exact values, then middle
removal/repeated removal preserves neighbors. Existing return/cleanup assertions
retained. Registered count unchanged4,127; no redundant new executable, CORE
change or allowance. Covers populated-list miss paths in ngc_flowctrl340 and
ngc_params1077; hosted attribution awaits the next cumulative batch report.

# Base serial fallback and fully green hosted checkpoint - 2026-10-22

Expanded existing network-disconnect scenario: base serial broadcast explicitly
disabled while network client stays active, verified network-only output, then
network disconnect restores base serial connected state and sole output route.
Existing callback-count/output assertions retained. Focused ASan/UBSan1/1 passes
0.28s, no new exception or CORE edits; registered count unchanged4,127.

All five individual hosted39801089848 job endpoints now terminal success for
5205e56/68eba79:source,coverage,GCC,Clang,diagnosis. Earlier downloaded source-
locked coverage/report artifacts verify17,236/17,684 lines97.47% and
11,988/13,754 branches87.16%,4,123 tests/4,108 clean/15 known/no failures/skips.
ReadMe badges/gap summary refreshed to that fully green checkpoint,448 raw
uncovered lines. Current ba111a2 run39802929753:source succeeded, compilers
running,coverage queued; do not claim current-head green or local-test coverage.

# Residual guard reachability audit - 2026-10-22

Verified four residual lines are unreachable under current public contracts:
vfs474/774 null-mount fallback, vfs410 second rename notification, ngc_params942
empty virtual list. Added source reasoning to TODO/KNOWN_BUGS gap table. Raw
coverage and correct assertions unchanged; no fake tests or private-state forcing.
Existing lookup/rename/provider tests retain reachable behavior. CORE unchanged.
TODO has legacy non-UTF8 bytes; appended ASCII without transcoding existing text.

# API-boundary batch cumulative gate - 2026-10-22

Full4,127-case ASan/UBSan build/test/strict gate passes, all exit0,15 known
reproductions and no new allowances. Evidence: build-asan/batch72-api-boundaries-
gate.json, delivery XML/log and strict log. Four new cases/two expanded scenarios
cover VFS allocation+failed rollback/root safety/retry, null spindle replacement,
default selector bounds, expansion-bank input/output persistence and root-format
failure/fallback/remount. No CORE edits or source exclusions. Root-format case
focused passes0.30s; full gate includes all accumulated local work.

Previous hosted39801089848 coverage locks verified5205e56/68eba79/filter,
all coverage stages0,4,123 total/4,108 clean/15 known/no failures/skips.
17,236/17,684 lines97.47%,11,988/13,754 branches87.16% (+14/+12 same-source).
New lines:gcode4182-4183/4253-4254;motion_control927/950-951/953-954/956;
state_machine807;vfs870/873-874. GCC/Clang live; do not claim full hosted success.

# Expansion-bank configuration persistence - 2026-10-22

New realistic multi-bank settings scenario passes focused ASan/UBSan0.28s.
Public pin lookup selects bank1/local1 (global3) for input/output. Save inversion,
pull-down and open-drain, verify global bit3 plus preserved primary bit0 in live
settings and checksummed NVS; clear the expansion configuration and verify only
bit0 remains persisted. No output/event callbacks emitted. Existing multi-bank
fixture reused; no new variant or private-state forcing. Covers settings-save
bank-list traversal absent from first-bank tests. Total4,126 cases; three new
cases/two extended scenarios local since5205e56, no new exceptions/CORE edits.

Current hosted39801089848 individual jobs confirm source success; coverage,
GCC and Clang in progress. That run is for5205e56/68eba79, not these local cases.

# Dummy spindle replacement and default selector - 2026-10-22

New startup registration case installs the public null placeholder, replaces it
with a real registered basic driver before activation, then verifies one listed
driver, preserved name, default selection, real callbacks and repeated selection.
Use normal registration-before-activation order; replacing an already active
spindle was not assumed to be a supported hot-swap contract. Existing multi-
spindle selection case now checks documented-1 default alias and invalid-2 guard
without another duplicate scenario. Grouped ASan/UBSan2/2 passes0.32s.
Total4,125 cases, no new expected failures or CORE changes. Current local batch
contains two new cases and two expanded scenarios since pushed5205e56; keep
building the coherent API-boundary batch before full gate/push.

# Directory allocation and rollback boundaries - 2026-10-22

One new VFS case and one expanded existing scenario pass grouped ASan/UBSan2/2
in0.31s. Initial saved-cwd malloc rejection returns ENOMEM without backend change;
existing reallocation recovery assertions remain. New double-failure scenario
accepts backend chdir, rejects cache growth, then rejects backend rollback: EIO,
root fallback, no relative unlink to the affected backend, followed by successful
long-directory retry and correctly routed unlink. Uses existing allocation fixture;
new target added to its exact wrapping/strset compatibility lists. Initial missing
compatibility define was a fixture error, corrected before classification.
Registered total4,124, no new allowances/CORE edits. Keep local for next batch.
Previous full gate/push5205e56 has4,123 cases; run39801089848 was dispatched
for that exact head, not these new local changes.

# Parking/tool/storage recovery batch full gate - 2026-10-22

Full4,123-case ASan/UBSan build/test/strict gate passes (all exit0), retaining15
known reproductions and no new allowances. Evidence: build-asan/batch72-parking-
tools-gate.json plus delivery XML/log and strict log. Three new cases cover
parking pullout clamping and M61/M6 plugin spindle stop preservation; two expanded
existing cases cover public homing driver-error completion/retry and current-drive
format-error fallback/remount/routing recovery. CORE remains clean68eba79, fresh
upstream master check unchanged. Deliver together on coverage-batch-72/PR26;
next hosted run must lock the new harness head before attributing coverage gain.

# Hosted recovery checkpoint fully green - 2026-10-22

All five individual job endpoints now confirm terminal success for run39797619172:
source119888956919, GCC119889103663, coverage119889103764, Clang119889103785,
diagnosis119896396248. Exact773569c/68eba79 coverage/report locks and filter
verified previously;4,120 executed,4,105 clean,15 known,0 failed/skipped.
ReadMe badges/KNOWN_BUGS gap summary refreshed97.39% lines/87.07% branches,
462 raw executable lines remaining. Local five-scenario additions/extensions
remain outside that hosted head and require cumulative gate before delivery.

# Current-drive format failure and recovery - 2026-10-22

Extended existing backend format-error test with current-directory routing:
chdir/store/jobs, preserve exact backend error-7 and TUFD drain/unmount/format/
dismount ordering, verify fallback root cwd, successfully reformat/remount, then
re-enter/jobs and route relative part.nc to/jobs/part.nc. Focused sanitizer test
passes0.28s. Existing frontend-only getcwd omission is separately documented and
its correct regression retained; this case verifies routing recovery instead.
No new allowance or CORE change. Current batch has three new cases and two
expanded workflows,4,123 total; hold full gate/push for substantial boundary.

# Public homing driver-error recovery - 2026-10-22

Extended the existing missing-auto-square-disable test through public $H rather
than adding another low-level duplicate. Invalid driver returns the exact
IllegalHomingConfiguration status, leaves IDLE, reports one failed completion,
and emits no pulses or homed flags. After normal realtime polling consumes the
completion event, correcting the driver capability allows $H retry: all XYZ
references and exact physical endpoints/pulse totals pass, with success callback.
Focused ASan/UBSan1/1 passes0.28s. No new CORE defect or allowance; initial retry
fixture omitted the normal command-loop realtime poll and was corrected.
Total remains4,123; three new cases plus this expanded workflow await the next
substantial cumulative gate/push. CORE unchanged.

# Tool-selection callback boundaries - 2026-10-22

Two new M61/M6 scenarios pass grouped ASan/UBSan2/2 in0.31s. Registered
on_tool_selected callback calls public gc_spindle_off while spindle is running;
block commit preserves its stopped state, selected tool completes, and following
M3S600/M5 still starts/stops normally. These target distinct immediate selection
and ATC selection branches, not private parser-state mutation. Total4,123 cases,
including the local parking boundary. No new exceptions or CORE edits.

Hosted39797619172 coverage artifact locks verified773569c/68eba79 and
core/.*\.[ch]$; all coverage stages exit0,4,120 executed/4,105 clean/15 known,
0 failed/skipped.17,222/17,684 lines97.38747%,11,976/13,754 branches87.07285%:
+8 lines/+18 branches against the same-source prior baseline. New lines include
legacy CRC recovery settings3783, G66 allocation failure gcode2287, registration
settings3088, expression null guards997/1083 and deferred alarm system456.
Compiler jobs still live at last individual-endpoint check; retain draft PR26.
The three new local tests are not part of that hosted coverage report.

# Parking clearance boundary - 2026-10-22

One new supported parking scenario passes focused ASan/UBSan (0.30s total).
Pullout20mm from Z-10 with parking target-2 exercises the clamped waypoint and
immediate parked completion without a fast retract. Actual motor position/pulses
verify640 retract steps, then1280 total Z steps after restoration; interrupted
X cut completes at1600 steps. Existing parking fixture reused; no CORE changes,
exceptions or source exclusions. Registered total4,121. Keep local for the next
substantial batch; no repeated full suite or hosted dispatch for this one case.

Hosted39797619172 exact773569c/68eba79 is live: individual source and coverage
jobs succeeded; GCC/Clang still running. Do not claim all hosted checks complete
or attribute coverage gain to this new local case before its own report exists.

# Eight-scenario recovery/validation delivery - 2026-10-22

Complete4,120-case ASan/UBSan gate passes62s:4,105 clean,15 documented
reproductions,0 failed/skipped. Build/test/strict all0 in
build-asan/batch72-eight-boundaries-gate.json; delivery XML/strict.log retain detail.
Five added tests and three extended scenarios beyond publishedec17fcb; no new
allowances, host variants, source exclusions or CORE edits.

Previously local work now included: metadata registration's nine invalid-input
boundaries and corrected retry; deferred alarm across E-stop/reset/two unlocks;
G66 allocation failure/queued-cut retry; public substitution/comment null guards.
This final group extends unknown-group availability lookup and expression-enabled
malformed-block rejection, preserving scope/queue and following160step endpoint.

Two new legacy compatibility2/10 checksum cases reuse the existing boot recovery
fixture. They verify a valid changed saved record, damage only its CRC while
keeping the version valid, and check defaults, sender error/query output and
repaired persistent checksum. Four old/new fault controls plus the group lookup
pass5/5; parser/basic guard group passes7/7 strict. The earlier counter question
is resolved: version repair occurs in NVS buffering before settings_init, whereas
CRC damage reaches the later recovery branch. No attribution bug is claimed.

Hosted39792966993 is FULLY successful at ec17fcbb838f1a17054eccf2b6049e34122292ed /
CORE68eba7906ba60d66c8b55c4adc90cd5e85b5a828, exact lock/filter verified.
Individual job endpoints confirm source/coverage/Clang/GCC/diagnosis terminal
success; listing responses had stale states.4,115 executed,4,100 clean,15 known,
0 failed/skipped. Measured17,214/17,684 lines97.34%,11,958/13,754 branches86.94%,
470 uncovered lines. Same-source prior delta+16 lines/+21 branches. Badges and
known-gap summary now point to this fully verified baseline. Current additions
have no hosted measurement yet. Push once on PR26 and dispatch one exact-head
68eba79 checkpoint; retain draft until its complete matrix passes.

# Local macro-allocation and public null-guard follow-up - 2026-10-22

The previous turn expanded registration guards and added deferred-alarm boot
coverage. This turn adds two passing scenario files,4,118 registrations total:
G66 argument-allocation rejection preserving an existing cut, corrected retry,
G67 cleanup and exact160step endpoint; and the public null-input guards of
ngc_substitute_parameters/ngc_process_comment, followed by unchanged parameter
readback and valid formatted output. Reuse existing macro/motion/heap fixtures;
one exact new target gets the existing malloc/calloc/free wrappers.

Six affected/control cases pass grouped ASan/UBSan +strict,6 clean,0 exceptions
(build-asan/batch72-resource-guard-followup.xml and strict.log). No full suite or
new hosted checkpoint for this local group. Last cumulative gate remains4,115
at publishedec17fcb. No source edits, source exclusions or new allowances.

Hosted39792966993 coverage job terminal success, all artifact stages exit0:
4,115 executed,4,100 clean,15 known,0 failed/skipped. Exactec17fcb/68eba79 source
lock and C+header filter verified. Measured17,214/17,684 lines97.34%,
11,958/13,754 branches86.94%; same-source delta+16 lines/+21 branches with
unchanged denominators against39788587225.470 measured lines remain uncovered.
Artifact/report/gaps saved in build-asan/hosted39792966993/. GCC/Clang remain
live and diagnosis queued at last authoritative check; do not call full matrix
green or dispatch a duplicate. Badges remain the fully successful97.25/86.79
baseline. Known-gap summary synchronized to that verified baseline.

New report confirms no-table offset cases exercise earlier parser branches,
not the later defensive zero-table arms. Added exact reachability evidence in
TODO rather than another duplicate test or forced metadata mutation.

# Local validation-branch and deferred-alarm follow-up - 2026-10-22

Previous turn delivered nine scenarios; this turn extends an existing case,
rather than adding one alias per branch. Renamed the plugin registration test
for its broader metadata scope: nine malformed declarations independently reject
(missing load/restore/save, invalid public type, missing value/getter, missing
description/group name, self-parent group). Every rejection leaves both settings
and the group undiscoverable, invokes no provider callbacks and preserves data.
Corrected registration then exposes group/description and ordered values.

One new full-boot scenario raises a second alarm through public system_raise_alarm
while E-stop is active, releases the input, sends reset and serial unlock/G-code.
The pending alarm survives warm reset, the first unlock reports it and still
blocks G91; a second explicit unlock returns to idle. No internal pending-alarm
flags are assigned. No motor motion occurs; all physical coordinates stay0.
This exercises previously uncovered system_raise_alarm/disable_lock branches.

Grouped ASan/UBSan +strict passes2/2,0 exceptions (build-asan/batch72-guard-alarm.xml
and strict.log).4,116 registrations expected; last complete local gate is4,115
before this follow-up. CORE clean/latest checked68eba79. No new source variant,
source edit, allowance or percentage claim. Keep local until a useful batch.

Hosted39792966993 source job passed; GCC/Clang/coverage confirmed live at last
check. Do not restart or dispatch a duplicate. Latest fully successful measured
baseline remains39788587225, exact2847aae/68eba79,97.25% lines/86.79% branches.

# Nine-scenario public API/parser delivery - 2026-10-22

4,115 registered tests pass complete ASan/UBSan66s:4,100 clean,15 documented
reproductions,0 failed/skipped. Build/test/strict all0 in
build-asan/batch72-nine-scenarios-gate.json; delivery XML/strict.log retain detail.
Nine additions beyond published2847aae are all ordinary passing cases, with no
new exceptions. The earlier five parser/compensation cases are listed below.

Four additional public-API scenarios pass grouped/strict (batch72-public-gaps.xml):
- Directory query's owned-buffer size rejection and malloc failure preserve
  caller storage/errno and allow correct current-directory retry.
- Missing plugin value storage rejects the whole settings owner; corrected
  registration exposes both settings and reports their values in order.
- A setting write during a real queued cycle preserves calibration and the
  original80step physical cut.
- Existing legacy help API respects its supplied command count and preformatted
  text; zero-count call adds no output.

Rejected the attempted null-value N/A listing candidate: public registration
forbids that descriptor. Its real validation boundary is tested instead. Added
source-backed known-gap/TODO evidence without bypassing registration. Existing
legacy corrupt-version recovery cases were found, not duplicated; their
uncovered report-call counter discrepancy is separately recorded for attribution
review. CORE remains clean68eba79. No new host variant or source exclusion.

Hosted39788587225 is now FULLY successful: source/GCC/Clang/coverage/diagnosis.
Exact2847aae/68eba79 lock/filter verified. Measured17,198/17,684 lines97.25%,
11,937/13,754 branches86.79%. Compared with the same-source prior checkpoint,
+13 lines/+9 branches, unchanged denominators. ReadMe badges now point here.
The nine additions have no hosted coverage measurement yet. Push this combined
boundary on existing PR26 and dispatch one exact-head68eba79 run; keep draft
until its full matrix completes. No redundant helper/full local rerun.

# Same-source measured coverage improvement - 2026-10-22

Hosted39788587225 coverage and Clang jobs terminal success; GCC remains live
at last authoritative check. Downloaded coverage artifact source lock verified:
harness2847aaef7522a9d6c5dc53f4c809f0bc9ab64615 / CORE68eba7906ba60d66c8b55c4adc90cd5e85b5a828 /
filter core C+headers. All coverage stages exit0.4,106 executed:4,091 clean,
15 documented reproductions,0 failed/skipped.

Measured17,198/17,684 lines97.25%,11,937/13,754 branches86.79%. Compared with
successful39779207602 at the SAME source/filter/configuration denominators,
13 additional lines and9 branches are covered (approximately+0.074/+0.065
percentage points). Newly covered lines: gcode2428/2429 and4812-4838 selections,
motion_control793/795 native unsupported stub, and vfs259 path-allocation
fallback.486 measured lines remain uncovered. No exclusions or adjusted totals.
Raw coverage/report/lock/gaps saved in build-asan/hosted39788587225/.

Five newer local scenario cases below are not part of these metrics and have
only grouped focused validation. No duplicate hosted run. Keep badges on the
last FULL-matrix successful checkpoint until GCC/diagnosis are terminal too.

# Five reachable parser-gap scenarios validated locally - 2026-10-22

Coverage-driven authoring resumes from exact68eba79 report39779207602, with
existing-case checks before each candidate. Five new scenario files (4,111
registrations) pass grouped ASan/UBSan and strict reporting,5 clean/0 exceptions,
0.4s runtime: build-asan/batch72-parser-gaps.xml and strict.log.

- No-table G43/G43.2 rejection preserves active dynamic Z offset and queued cut.
- Read-only material provider assignment rejects through the parser, preserves
  both provider/queued feed, and the following two cuts finish at160steps.
- Failed computed O-label expression preserves root scope and queued80step cut.
- Canned-cycle compensation conflict and active-compensation work-system switch
  reject without changing modal/callback state; cancelling allows valid retry.
- Static cutter radius uses the fitted tool both with omitted D and D0. Fitted
  tool is declared using M61 in execution mode with mandatory tool notification
  installed, then check mode validates extension configuration. Initial missing
  callback/check-mode fixture mistakes were corrected, not labelled CORE bugs.

Existing negative coordinate-index regression was found and not duplicated.
No CORE edits, forced private state, new configuration, source exclusions or
known allowances. These five are outside the last full/hosted checkpoint and
have no measured coverage gain yet. Accumulate on this branch; no per-module
full suite/push/CI. Published2847aae is under exact hosted39788587225; source job
passed and runtime jobs were confirmed live, with no duplicate dispatch.

# Combined parser/state coverage delivery - 2026-10-22

Resume coverage-driven unit testing: inspect uncovered executable paths, select
supported public inputs and assert observable behavior. Real failures become
known regressions; incomplete/unreachable implementation remains explicit in
KNOWN_BUGS' gap table, without fake tests or adjusted coverage totals.

Four accumulated cases beyond validated97bb6aa now total4,106 registrations:
wrong-directory unlink on allocation failure, trailing comment overriding a
validation error, direct compensation restore ignoring extension refusal, and
unsupported native G33.1 returning success with parser-only displacement.
The last specifically exercises previously uncovered parser/native-stub paths
using the existing working encoder/stepper fixture; no tapping geometry added.
Each has a correct assertion, narrow WILL_FAIL and dated evidence/cleanup.
No CORE edits, source exclusions or sanitizer suppression.

Full4,105-case ASan/UBSan gate before the final G33.1 addition passes63s:
4,091 clean,14 documented reproductions,0 failed/skipped. Build/test/strict all0
in build-asan/batch72-three-bugs-gate.json; XML and strict.log retain detail.
Final G33.1 case +two real synchronized-motion controls pass focused/strict:
2 clean,1 documented reproduction (batch72-tapping-final.xml). The final case
fails correct unsupported-status assertion after observing parser Z2 vs physical
Z1; later preservation/retry assertions are unvalidated until that fix. No
redundant unchanged full suite/helper run; next complete gate is hosted.

Latest successful hosted baseline39779207602 remains exact97bb6aa/68eba79,
all five jobs green,97.18% lines/86.72% branches. Current additions have no new
coverage measurement yet. Deliver together on existing PR26 and dispatch one
updated-head/source checkpoint. PR remains draft pending that exact run.

# Explicit known-gap placeholders - 2026-10-22

User requested visible placeholders for unfinished/inaccessible coverage regions.
KNOWN_BUGS.md now has a linked known-coverage-gaps table: wall homing, native
rigid tapping, disabled open-drain/timezone settings, stale settings metadata,
atomic scheduler fallback and inaccessible broadcast override arms. Each records
status, exact68eba79 source evidence and the condition for executable testing.
ReadMe Known issues links it. Existing real public rejection tests remain.
No synthetic WILL_FAIL tests, source exclusions, adjusted denominator or inflated
case count. Raw successful baseline remains97.18%/86.72% with499 uncovered lines;
not all499 are classified unavailable. Runtime source/tests unchanged in this
inventory-only commit, so no redundant build/full suite/hosted dispatch.

# Verified hosted checkpoint39779207602 - 2026-10-22

All five jobs terminal success: source, GCC, Clang, coverage, CI diagnosis.
Exact published harness97bb6aa5b379732701e117ed5caa73b7d1a40d5c / clean CORE
68eba7906ba60d66c8b55c4adc90cd5e85b5a828 / filter core C+headers verified
against downloaded source lock.4,102 registrations:4,091 clean,11 documented
expected failures,0 skipped/unexpected failures. Coverage17,185/17,684 lines
97.18%;11,928/13,754 branches86.72%. ReadMe badges now reference this successful
baseline; no comparable-source gain claim. PR26 body updated with exact evidence.
Do not merge automatically. Current two local bug commits remain outside that
head and need a future combined delivery; goal remains active and incomplete.

# Local material-comment bug and verified coverage report - 2026-10-22

Previous turn made progress: committed wrong-directory unlink reproduction.
This group adds a second concrete public bug, not duplicate confidence tests:
normalization overwrites a plugin comment error with a later successful plain
comment. A rejected material-selection comment followed by a contour note
accepts G20/G91 motion and advances parser X from1 to51.8mm. Correct rejection,
modal, queue-capacity and80-step assertions reuse the existing shared fixture;
status fails before preservation assertions run. Narrow named WILL_FAIL,
dated KNOWN_BUGS cause/proposal/cleanup. CORE untouched.4,104 registrations.

Grouped follow-up ASan/UBSan and strict reporting:3 clean controls,2 known
reproductions,0 failures (batch72-bug-followup.xml /strict.log). Format case
separately confirms doubled separator. Do not rerun the full unchanged suite
or push a tiny checkpoint while the published run is still finishing.

Hosted39779207602 exact97bb6aa/68eba79 source-lock verified. Source, Clang and
coverage jobs are terminal success; GCC remains live at last authoritative
check. Coverage artifact stages fetch/tooling/configure/build/test/classify/
coverage all exit0,4,102 tests:4,091 clean,11 known,0 failed/skipped. New measured
baseline17,185/17,684 lines97.18%;11,928/13,754 branches86.72%,499 uncovered
lines. No like-for-like gain claim against older different-source reports.
Raw artifact/lock/report/gaps saved at build-asan/hosted39779207602/.
Badges/PR readiness await the complete matrix. New grbllib atomic-selection
fallback reachability evidence is in TODO; no exclusions or forced interrupts.

# Current local file-safety follow-up - 2026-10-22

Published97bb6aa is under hosted39779207602, authoritatively in progress at
last check. Source job passed; downloaded source-lock artifact confirms exact
harness97bb6aa / clean Terje68eba79 / core C+header filter. GCC, Clang and
coverage remain live; do not dispatch a duplicate or claim terminal success.

Local follow-up adds one bug regression (4,103 registrations), not another
confidence case. A size-specific temporary path malloc failure during public
relative unlink in `/store/jobs` dispatches `part.nc` and reports success,
removing a different same-named root file. Valid frontend-only provider and
normal retry to `/jobs/part.nc` establish the fault; final unrelated-file
preservation assertion remains correct. One narrow WILL_FAIL; dated KNOWN_BUGS
cause/proposal/cleanup. No CORE edits or sanitizer exemption. Raw evidence:
build-asan/batch72-unlink-oom-raw.xml.

Existing current-drive format case now uses a valid callback-free frontend
directory provider and records backend routing. On68eba79 it reaches backend
as `//new.nc`: mount cache's trailing slash is doubled by parse_path. Updated
the existing known entry rather than adding a duplicate test. Grouped focused
ASan/UBSan +strict passes both expected reproductions (batch72-vfs-safety.xml).
Prior full4,102 gate remains the last cumulative gate; no redundant full run
or hosted dispatch for this one-case follow-up. Accumulate useful work here.

# Current batch72 bug-hunting delivery - 2026-10-22

CORE is clean detached68eba7906ba60d66c8b55c4adc90cd5e85b5a828. No firmware
edits. Prior checkpoint below is historical. Branch coverage-batch-72 retains
five accumulated local follow-ups plus this source-compatibility/bug group.

- Prioritize plausible public bug paths, reuse existing regressions, and avoid
  confidence-only additions. One shared-header rebuild, grouped affected run,
  one full pre-push sanitizer gate. No new source coverage claimed yet.
- All4,102 current registrations now build/run; zero unavailable. Full
  ASan/UBSan147s:4,091 clean,10 known reproductions,1 existing alarm-upload
  failure. Evidence: build-asan/batch72-core68-delivery.xml and strict.log.
  The upload contract remains unsettled; its correct assertion now has one
  documented named WILL_FAIL per requested nonblocking handling. Focused final
  classification XML/strict log records upload and combined message regression.
- All41 cutter cases pass again after upstream's flag-field fix. Scheduler
  cancellation and five ordinary directory/root regressions pass; their
  allowances removed. The invalid chdir-without-getcwd provider is now rejected
  at public mount; adapted regression checks rejection and corrected retry,
  retaining repeated-directory and relative-unlink assertions. Removed both old
  fatal manifests/wrappers; remaining failures use no sanitizer exemptions.
  Linux device allowance removed with the common validation fix, pending hosted
  Linux confirmation. Local fs_device passes; do not call hosted checks green.
- Fallback frontend-only getcwd still loses its directory. Format relative path
  assertion and two hidden-mount navigation assumptions still fail. Preserve
  named exceptions and distinguish unresolved hidden-navigation policy in TODO.
- Default backend's old direct-call metadata assumptions changed upstream.
  Existing root/missing tests now use public stat and check metadata/status;
  no promise is imposed on failed output buffers. Retired callback-free child
  metadata fallback case because that implementation was removed, not replaced
  by forced NULL-callback invocation. Evidence and scope recorded in TODO.
- New combined public parser-error probe confirms zero messages released across
  unsupported G999, negative feed and unused Q. Expected errors, prior queued
  cut and80-step endpoint all pass before correct ownership assertion fails.
  One named WILL_FAIL, expanded existing message-leak entry, no suppression.
- Latest hosted report remains failing39762025374 at19bb4ab/fab8d1c, PARTIAL
  97.05% lines/86.67% branches. Changed source/config denominators prevent a
  defensible gain claim. Keep successful96.60/85.54 badges unchanged until an
  exact updated-head/source hosted report exists. PR26 remains draft.

# Current batch72 verification checkpoint - 2026-10-22

The full supported CORE coverage goal is active and unproven. Highest priority:
obvious bugs and uncovered reachable paths, not extra confidence cases or test
counts. Batch source review/authoring/builds; focused runs resolve uncertainty.
One cumulative gate and hosted checkpoint per substantial delivery. CORE belongs
to Terje and remains untouched.

- Branch coverage-batch-72; published PR26 is draft at19bb4ab. Local follow-ups
  are accumulated, not yet pushed.4,102 registered cases /100 beyond merged
  upstream; these counts do not establish coverage progress.
- Clean CORE and latest checked Terje master remain
  fab8d1c248990f53f13a444018fbb3ee353061dd.
- Latest exact-source hosted39762025374 is terminal FAILURE at19bb4ab/fab8d1c.
  Source/helpers passed. Each runtime job attempted4,094 registrations:4,022
  clean,10 known,58 unavailable and4 failures (alarm contract, Linux /dev
  rejection and two documented crashes reported differently). No live job awaits.
- Hosted PARTIAL measurement:17,065/17,583 lines97.05%;11,818/13,635 branches
  86.67%.518 measured executable lines remain uncovered. This is not a passing
  baseline or like-for-like gain from the96.60/85.54 successful badge baseline;
  source/configuration denominators differ. Badges unchanged. Exact source lock,
  HTML/XML, compiler reports and fresh gaps.json: build-asan/hosted39762025374/.
- Current configuration recovery:17 generic existing cases were unnecessarily
  coupled to cutter compensation. Four pre-execution cases moved to lathe_ngc;
  five geometry cases moved to ngc_tools and eight generic G-code table cases now
  link the existing host_core_ngc_tools with LATHE_UVW_OPTION=1. No duplicate cases
  or source exclusions. All28 affected geometry/offset/reload/M6/parameter tests
  pass ASan/UBSan and strict1.67s: batch72-tool-config.xml /strict.log /build.log.
  The remaining41 cutter tests genuinely require CUTTER_COMP_ENABLE and remain
  registered/unavailable due to CORE's stale ccomp_off field references.
- Concrete local bug regressions: MPG pull-up ordering (two named WILL_FAILs),
  active macro WHILE allocation error leaving its file current at EOF (one), and
  plugin rejection losing its CORE message (one). Correct assertions retained;
  dated source/cleanup evidence in KNOWN_BUGS.md. No new sanitizer suppression.
  Four relocated hook controls +message regression pass5/5 strict0.52s, with
  observed orphan reclaimed only in probe teardown: batch72-plugin-hook.xml.
  WHILE regression/control pass2/2 strict0.29s: batch72-while-allocation.xml;
  MPG regressions/control pass3/3 strict0.35s: batch72-mpg-pull.xml. Raw failure
  XMLs retain the actual ownership/pull-up evidence.
- Three local macro-loader memory recovery cases use actual file reads, parser
  execution and EOF after retry. Filename growth, sub-record and callee-argument
  failures preserve sender, parent#1=99, scope and close ownership. Three +two
  existing controls pass5/5 strict0.82s: batch72-macro-loader.xml /strict.log.
- Linux diagnostic follow-up: /dev rejection gets one Linux-only WILL_FAIL;
  GCC/Clang null-call reports match only exact captured source/frame or PC-zero
  harness caller chains. Changed/additional faults and fixes remain red.71 helper
  checks pass6.695s; four captured Linux crash outputs replay and actual Windows
  crash checks pass2/2 strict0.54s. Evidence: batch72-linux-diagnostic-python.log
  and batch72-mpg-linux-repair.xml. No unchanged helper rerun is needed.
- Last cumulative local gate preceded the17 relocations and message regression:
  4,043 buildable cases (4,101 registered minus58),4,027 clean,15 known,one
  unsettled alarm-upload contract failure. Build failed only host_core_cutter;
  CTest/strict remain red. Evidence: batch72-recovery-delivery.xml and related
  build/test/strict logs. Preserve this scope; do not claim the newer configuration
  has a whole-suite or hosted pass. Do not repeat full gates after each small edit.
- Next: review remaining fresh-map regions for concrete bug hypotheses, retaining
  maintainer TODOs and unreachable guards. Accumulate a meaningful group before
  the next combined validation/push. Current config has41 unavailable cases and
  4,061 buildable registrations, not yet cumulatively gated. No new percentage
  is claimed until a matching source/configuration report exists. PR27 remains
  independent draft reporting repair, integrated into this branch ind58f2bc.

Historical entries below may describe old branches, completed runs or superseded pauses.

# Live CI measurement recovery - 2026-10-20

The coverage workflow previously skipped gcovr whenever tests failed, preventing
fresh gap guidance. An isolated fix is pushed on ci-partial-coverage at eb746fe,
based on upstream/master3b16ba3; it contains no coverage batch tests or CORE edits.
57 Python checks pass. Hosted run 39369581523 is in_progress at last query:
https://github.com/petervanderwalt/Unit_tests/actions/runs/39369581523
Poll that existing handle; do not redispatch. Verify it emits labelled PARTIAL
HTML/XML, retains failed CI and skips changed-code assessment after failed tests.
Do not call it ready or create its PR before hosted evidence is inspected.
The raw counters are investigation data, never a new passing coverage baseline.
Core stays clean7a6a432 and the98 documented crashes remain unsuppressed.

Back on coverage-batch-72; its25 new cases comprise22 hosted-verified at05806c8
and three later local snapshot cases atad3ed49. PR24 remains open/unmerged.
Continue independent tests here while CI runs. Do not duplicate PR24 in a new
master-target PR. The separate CI branch can be reviewed independently of24.

Named-label parser follow-up: four new cases PASS ASan/UBSan. Allocation
failure/retry and label reuse under memory pressure pass0.31s; unterminated and
overlong label rejection/recovery pass0.31s. The rejection cases execute an
already queued cut to its exact motor endpoint, then accept a corrected named
conditional and assignment. No VFS workaround, source patch or exception.
Evidence: build-asan/batch72-label-results.xml and batch72-label-rejection-results.xml,
../batch72-label-tests.log and ../batch72-label-rejection-tests.log.
Batch72 now29 additions:22 verified hosted at05806c8 plus7 later local cases.
Registered total4,031. No updated full-suite/hosted claim for those7. Continue
supported gaps; await the existing isolated CI run for fresh partial measurements.

Fresh partial-coverage guided group: four cases PASS ASan/UBSan0.36s.
Negative G10 P preserves the queued cut, modal state and saved coordinates;
inverse-time canned drilling rejects then accepts a G94 retry; rotary A words
in an eight-axis canned cycle reject without pulses, then linear drilling works;
YZ cutter-comp activation rejects before the plugin and accepts a G17 retry.
The first cutter assertion expected the later IllegalPlane guard; source review
shows the earlier common check returns CutterCompConflict. The test follows
that public contract. Do not force the redundant later guard for coverage.
Evidence: build-asan/batch72-public-validation-results.xml and
../batch72-public-validation-tests.log. Batch72 now33 new cases:22 previously
hosted plus11 later local cases. Registered total4,035. No CORE or exception change.

Isolated CI coverage job39369581523 has completed with its expected failed test
stage but SUCCESSFUL coverage collection. Artifact contains HTML/XML; HTML title
is "Partial core coverage - tests failed". Classification retains98 failures and
coverage_partial warning, suppressing changed-code assessment. Summary step ran
successfully with COVERAGE_COMPLETE=false (job log retained). Remaining compiler
and diagnosis status must still be verified before CI PR readiness. Current gap
map: ../ci-partial-coverage-core.gaps.json, explicitly partial. Do not promote its
percentages to a passing baseline. The CI branch predates batches71/72.

Isolated partial-coverage CI repair is now PR25 (open, non-draft):
https://github.com/grblHAL/Unit_tests/pull/25 . Hosted39369581523 is terminal;
all builds pass, GCC/Clang each reproduce only98 known strutils.c:393 failures.
Coverage collection succeeds despite failed tests, produces labelled partial
HTML/XML, records coverage_partial and withholds changed-code assessment.
Summary step succeeds with COVERAGE_COMPLETE=false.57 Python checks pass.
No CORE or exception change. Do not merge either PR24 or25.
Use ../ci-partial-coverage-core.gaps.json for current-source investigation only;
it is based on upstream/master before batches71/72, so discount already covered
paths from our new cases. VFS/macro gaps may be downstream of the core crash.
Continue batch72 tests on this branch. No new hosted/full-suite claim for the11
local post05806c8 cases; local total4,035,72 additions33. No repeated CI dispatch.

# Current batch72 continuation - refreshed 2026-10-20

Goal active after usage reset. Reuse coverage-batch-72; do not proliferate branches.
Core freshly fetched remains clean/unmodified Terje7a6a432. PR24 is open,
unmerged, for the25-case71 batch. Never merge it or modify CORE.

Hosted72 run39341429819 is terminal failure. Source/build stages pass; GCC and
Clang each run4,024 cases:3,923 clean passes,3 known reproductions,98 failures,
0 skips. All22 additions at pushed05806c8 pass in both compilers. Every sanitizer
case reports the same documented strutils.c:393 NULL-base access. No coverage
percentage was produced. Artifacts: ../batch72-hosted-{results,report}-core-*.zip.
Do not rerun that unchanged checkpoint or treat its source fault as a test fix.

Three additional local snapshot cases PASS ASan/UBSan0.36s: M70 allocation
failure leaves parser state intact and permits retry; replacing an existing save
reuses storage under memory pressure; a failed local M73 preserves the caller's
snapshot and permits later restore. Public parser/modal-scope APIs plus existing
malloc failure fixture; linker wrapping is narrow to these three cases. No new
bug/exception. Registered total4,027. Evidence: build-asan/batch72-snapshot-results.xml
and ../batch72-snapshot-tests.log. These three are NOT in hosted05806c8 evidence.
Keep authoring supported gaps before the next single pre-push full gate. PR72
must not duplicate PR24 changes while24 remains unmerged.

# Active continuation batch72 - 2026-10-20

Branch coverage-batch-72 continues from pushed coverage-batch-71 at5133033.
Do not duplicate batch71's PR or include unfinished72 work in its readiness claim.
Batch71 hosted run39339402897 was confirmed in_progress against clean Terje
7a6a432; check the existing run, never dispatch repeated unchanged validation.
Local71 full gate:4,002 build;3,901 clean passes,3 known reproductions,98
strict sanitizer failures all at documented strutils.c:393; all25 new cases pass.
No CORE modifications, broad allowances or new coverage percentage claims.

First72 group: four real homing workflows PASS ASan/UBSan in0.39s. Equal
per-axis rates retain a combined XY cycle; distinct seek-only or locate-only
rates split axes; noncontiguous XZ homing leaves Y completely unmoved. Verify
physical endpoints, pulse counts, limit re-enabling and completion callback.
Evidence: build-asan/batch72-homing-results.xml and ../batch72-homing-tests.log.
Registered total4,006. Keep adding practical groups before the next full gate.
Terje alone fixes source defects. Goal active; hourly recovery remains configured.

Batch72 second group: four delta nonlinear jog cases pass ASan/UBSan0.40s.
Check positive/negative Y and diagonal XY/XYZ clipping preserves the requested
line, produces finite motor coordinates and passes the public travel checker.
One CSS-to-rapid lathe workflow passes: queued radial cut drains to its exact
endpoint before the new rapid is queued; CSS mode remains active and the rapid
reaches its exact motor endpoint. No fixed-RPM convention is assumed for G0.
A second draft assuming two consecutive CSS cuts remain queued was discarded:
the parser can synchronize them; it is not a core bug. No allowance added.
Evidence: build-asan/batch72-delta-results.xml and batch72-css-results.xml,
../batch72-delta-tests.log and ../batch72-css-tests.log. Nine new72 cases pass;
registered total4,011. No full rerun until a substantial delivery boundary.

Batch72 third group: five cases PASS ASan/UBSan0.43s. A real probe and
$TLR establish a tool reference in each fixed X/Y/Z configuration. Public homing
notifications preserve it for unrelated axes and invalidate it for the configured
axis, regardless of active plane, with the expected report flag. Two public
$HELP COMMANDS cases enumerate separate registered plugin groups exactly once
and refresh optional command help availability without invoking commands.
Evidence: build-asan/batch72-reference-help-results.xml and
../batch72-reference-help-tests.log. Batch72 now14 new passing cases;
registered total4,016. No CORE change, known bug or allowance added.

Batch72 fourth group: two public startup upload boundary cases PASS
ASan/UBSan0.31s. Oversized normalized input returns Overflow before changing
saved program or parser distance mode; a long valid pipe-separated program
round-trips intact and preserves slot1. Evidence:
build-asan/batch72-startup-results.xml and ../batch72-startup-tests.log.
Batch72 now16 new passing core cases; registered total4,018.

Hosted71 coverage artifact is terminal failure; GCC/Clang were still running at
last query. Exact source-lock confirms clean Terje7a6a432. All25 additions pass
in hosted coverage; full counts match local:3,901 clean,3 known,98 failed,0
skips. All98 JUnit failures carry SEGFAULT. Coverage was NOT produced; do not
claim a new percentage. Downloaded artifacts and extracted XML are in ../batch71-
hosted-coverage*. No new dispatch is needed.

Reporting repair for72: ci_report ignored JUnit's failure message when captured
stdout/stderr contained only whitespace. Retain SEGFAULT instead of saying
no diagnostic was emitted. Classification remains failed/known_changed; never
call a crash a fixed regression. Regression test plus changed helper checks:
14 CI-report and11 sanitizer-report checks PASS. Set TEMP/TMP to a workspace
folder for Python helper tests; the default sandbox temp folder rejected child
writes. Reclassifying the real coverage artifact now reports98 SEGFAULT findings.
No CORE modification or diagnostic exception is involved.

Batch72 fifth group: two protected-probe status workflows PASS
ASan/UBSan0.30s. Register a real watchable/latchable probe, enable protection via
$65=32, forward its actual queued report flags, and verify the protection marker
is removed on disconnect/probing and restored on reconnect/return to idle guard.
The initial draft used the generic report helper's empty flags; correcting the
caller to pass pending stream flags fixed the fixture. No core bug or exception.
Evidence: build-asan/batch72-probe-report-results.xml and
../batch72-probe-report-tests.log. Batch72 now18 new passing core cases;
registered total4,020. CI-report repair also has25 passing Python checks.
GCC hosted71 is terminal failure solely from98 documented strutils.c:393
NULL-base sanitizer cases; all25 new71 tests pass. Clang remains pending until
rechecked. Never imply the source suite is green or fabricate coverage output.

Batch71 delivery complete: PR24 is OPEN, non-draft:
https://github.com/grblHAL/Unit_tests/pull/24 . Hosted39339402897 is terminal
failure. Source selection/all builds pass; GCC and Clang each confirm3,901
clean passes,3 known reproductions,98 source sanitizer failures,0 skips. Every
new71 case passes in all jobs. Coverage is unavailable, not a percentage claim.
PR explicitly documents the unchanged core fault and has no source patches.
Do not merge PR24. Batch72 is based on71; avoid a cumulative duplicate PR before
24 merges. Continue tests on72 and push at the next coherent boundary.

Batch72 sixth group: normal all-off follows its configured PWM stop ramp,
reset all-off stops immediately without ramp delay, and two enabled PWM spindles
each ramp monotonically to zero. Three cases PASS ASan/UBSan0.34s.
Secondary PWM unsupported inversion case PASS0.23s. Registration trims that
option from public metadata, so its public validation returns OutOfRange before
the private setter's Disabled guard. Do not invoke the private setter to force
coverage; retain the supported public rejection and normal enable/direction path.
Evidence: build-asan/batch72-stop-results.xml and batch72-secondary-invert-results.xml.
Batch72 now22 new core cases pass; registered total4,024; reporting checks25 pass.
Next: one full local pre-push gate for72, not repeated focused/checker runs.

Batch72 full pre-push gate completed: all4,024 targets build. Full
ASan/UBSan run61s:3,923 clean passes,3 known reproductions,98 strict failures,
0 skips. All22 additions pass. The exact set of98 sanitizer cases is identical
to71, each at documented strutils.c:393 NULL-base access. No new failing case,
exception or CORE change. Raw CTest96 still differs from strict98 due two
inherited expected-failure labels.25 changed reporting checks pass.
Evidence: ../batch72-full-build.log, build-asan/batch72-full-results.xml,
../batch72-full-summary.md and ../batch72-validation.json.
Push72 and dispatch one hosted check against clean7a6a432; no repeated run of
unchanged source. PR24 is open for71. Avoid duplicating its changes in a new
master-target PR until24 merges. Continue independent work while72 CI runs.

# Active coverage batch71 - 2026-10-20

Goal ACTIVE: meaningful full supported core line/branch coverage. The hourly
recovery task is configured in the app to continue stalled work when usage is
available. Routine passing checks, commits and PR checkpoints do not stop work.

Branch coverage-batch-71 starts freshly fetched upstream/master3b16ba3, which
contains merged PR23. Core clean/unmodified Terje7a6a432eaf78e028b81ff3a5f9804e14519f5f01.
Terje alone implements core fixes. Never edit/commit/push CORE or open core PRs.
Confirmed faults go to KNOWN_BUGS.md; uncertain contracts/questions go to TODO.
Requests to fix CI/tests never imply permission to change source firmware.

Read one clean-source coverage report this batch:39288629614/core16c7dff,
96.60% lines85.54% branches, as historical gap guidance only. Never use the
withdrawn agent-patched run39332728069 as readiness/coverage evidence.
Large dormant gaps include wall-plotter homing, unpublished settings and weak
rigid-tapping implementation; avoid forcing private paths or unfinished features.

First group:16 separate cases for job-end coordinate reload/CRC-error retry,
check-mode persistence isolation, G92 save policy, completion callback ordering,
feed/rapid/spindle override reset policy, parking policy and modal-snapshot
invalidation. Settings cases cover supported spindle-sync/auto-square groups,
optional plugin channel discovery and public homing-direction readback.
First20 new cases PASS ASan/UBSan in0.67s, no diagnostics or new exceptions.
The four added secondary-switch-first auto-square cases verify both homing
directions, positive/negative trim, physical motor endpoints, completion and
release of both motors. The two missing PWM coolant callbacks were fixture
errors and are corrected, not recorded as core faults.
Evidence: build-asan/batch71-first20-results.xml and ../batch71-first20-tests.log.
Core remains clean7a6a432. Registered total3,997 (source still has documented
independent faults; no full passing-core/coverage claim). Commit this coherent
group, then continue practical gaps before a useful push/PR boundary. No full
local rerun until pre-push; no unchanged reporting-helper reruns.

I/O follow-up: five new public plugin-configuration cases pass ASan/UBSan
in 0.32s: named output restoration, capability-filtered fallback after a saved
name disappears, nonexistent output rejection without changing selection,
reserved coolant output rejection, and early termination of unfiltered port
enumeration. A first draft incorrectly treated setting selection as ownership;
review showed set_value validates capability while claim handles ownership.
The replacement uses the existing driver assignment fixture and a real coolant
function. No core bug or exception was added. Evidence:
build-asan/batch71-io-results.xml and ../batch71-io-tests.log.
Batch71 now adds25 passing cases; registered total4,002. No new overall coverage
measurement or full-suite claim. Next: continue high-value supported workflows,
then one full local gate at the delivery boundary; preserve clean core7a6a432.

Full pre-push gate completed on clean Terje7a6a432: all4,002 targets build.
Full ASan/UBSan CTest run completed130s. Strict classification:3,901 clean
passes,3 known reproductions,98 failures,0 skips. All98 diagnostic cases report
the same already documented strutils.c:393 NULL optional-base dereference;
there are no other raw failed cases. Raw CTest reports96 failures because two
VFS expected-failure labels invert their crashes; strict reporting rejects all98.
All25 batch71 cases pass in the full run, with no skipped case or new exception.
Evidence: ../batch71-full-build.log, build-asan/batch71-full-results.xml,
../batch71-full-summary.md and ../batch71-full-failure-classification.json.
This is not a green suite or a new coverage measurement. The source fix is
Terje's responsibility; never modify CORE to make this run green. Push71 and
run one hosted checkpoint against the exact revision before PR readiness claims.
Four additional homing-rate drafts are outside the repo in
../batch71-next-homing-proposals; unregistered/unvalidated, for the next group.

# Core ownership and withdrawal - 2026-10-20

Terje owns CORE implementation. This repository authors tests and documents
bugs; NEVER modify, commit or push CORE, or create a core PR. Requests to fix
failing tests/CI do not authorize changing the firmware. Record confirmed faults
in KNOWN_BUGS.md, uncertain contracts in TODO.md, retain correct regressions and
wait for Terje's implementation. Proposed fixes may be documentation only.

The agent-created source PR terjeio/grblHAL_core#1 was a mistake and has been
closed without merging. Its remote/local fix-vfs-string-ownership branch was
deleted. Core is back on clean detached Terje7a6a432eaf78e028b81ff3a5f9804e14519f5f01.
Unit_tests PR23 is draft again and must have no dependency on agent-patched core.
Run39332728069 used agent-patched source and is WITHDRAWN as readiness/coverage
evidence for this project. Do not present its green result as a Terje-core pass.
The older fully green clean-Terje baseline39288629614 remains historical evidence.

Keep genuine test repairs and API compatibility work. Terje's own cwd/safety-door/
G65 fixes stay resolved. Restore still-unfixed directory bug documentation and
narrow exceptions. Document the current strset NULL-base crash without suppressing
unrelated sanitizer diagnostics. Allocation-failure tests follow Terje's retained
storage policy; no requirement to free reachable storage is imposed.
Clean-source targeted reproduction completed:7 string cases in0.54s;4 pass,
3 reproduce the NULL-base sanitizer crash at strutils.c:393. Evidence:
build-asan/core-withdrawal-results.xml and ../core-withdrawal-tests.log.
No full rerun/CI dispatch is needed to reproduce this same fault. No source edits.

# Current PR23 integrated repair checkpoint - 2026-10-19

Working branch coverage-batch-69. PR22 is merged; existing PR23 receives this
combined batch. Never commit/push master or merge PRs. User approved repairing
upstream20f186f's incoming116 tests in this same PR, superseding older notes
about a separate integration blocker/branch. Repair commit22a68cc is merged.

All116 incoming cases compile. Corrected invented APIs/fields and unsupported
G-code assumptions, valid arc geometry, coordinate-offset calculations, macro
callback/scope behavior, tool selection, overrides and spindle capabilities.
Feature-specific cases link the appropriate real core configuration. Shared host
fixtures provide valid callbacks and mutable parser input. No core source edits.
G53 with active Fanuc scaling remains a contract question in TODO with an
unregistered proposal; the registered control uses explicit G50 cancellation.

Core fresh fetch remains49eff3c5c66afa1cc1915b26ae8160fa805593c7, clean.
The known VFS cached-directory NULL pointer, borrowed-buffer realloc and enabled
safety-door preprocessing faults remain unsuppressed. Existing KNOWN_BUGS entries
include reproductions and proposed fixes. They are separate from incoming-test
repairs; do not weaken assertions or add blanket sanitizer exceptions.

Final integrated validation: all3,985 targets build after narrowing the boot
link-wrap rule to its seven intended incoming fixtures. One full ASan/UBSan run
completed137.97s. All116 repaired incoming tests pass, with zero skips/exceptions.
Full strict result:3,884 clean passes,5 known reproductions,96 failures,0 skips.
Failure names match the previous core49 checkpoint exactly:95 sanitizer crashes
from the two documented memory faults plus the safety-door-enabled compile fault.
CTest raw count93 differs because three inherited expected-failure labels invert
crash exits; strict reporting correctly rejects those crashes. No new allowance.
Evidence: build-asan/pr23-integrated-results.xml, extracted
build-asan/pr23-incoming116-results.xml and ../pr23-integrated-summary.md.
Build logs retain the six initial link failures and narrow repair separately.
55 reporting helper checks passed previously after6741803; unchanged here.

Push this integrated repair to existing PR23 and dispatch one hosted checkpoint
against the exact core49eff3c revision. Keep PR draft while unsuppressed source
faults remain. Do not claim latest-core coverage or full hosted success.
Latest fully green measured baseline remains39288629614/core16c7dff:
17,052/17,652 lines96.60%,11,719/13,700 branches85.54%; not coverage of49eff3c.

# Latest core update introduces VFS crashes - 2026-10-19

Core freshly fetched and selected49eff3c5c66afa1cc1915b26ae8160fa805593c7,
clean/unmodified. Previous checkpoint39288629614 at2881c0b/core16c7dff has
ALL FIVE hosted jobs successful. Both source/coverage locks were verified.
Coverage17,052/17,652 lines96.60%;11,719/13,700 branches85.54%. README badges
now point to that fully successful baseline; do not describe this as49eff3c.

New49eff3c adds string_t/strset and refactors VFS. Windows CRT has an unrelated
two-argument strset declaration. A MinGW-only forced header hides that unused
CRT declaration before core headers; original core source/symbols unchanged.
New string API cases are registered only when that API exists in selected core.

Reproduced two NEW ordinary-workflow memory defects in existing tests:
- vfs_locate_file("workbee_panel_fixture_01.nc") reallocates a static buffer;
  ASan bad-free at strutils.c393 called from vfs.c901.
- first vfs_chdir/unlink normalizes a path with cwd.name initially NULL;
  ASan null read at strlen, vfs.c264.
Three-case diagnostic XML/logs retained in build-asan/batch69-core49-reproduce*
and parent logs. Two older known logical regressions appeared CTest-passing
because WILL_FAIL inverted these new crashes; strict summary still rejects
sanitizer text. Never interpret that as reproducing/fixing the older bugs.
Two dated KNOWN_BUGS entries link exact source, normal reproductions, fix proposals
and cleanup. No broad exception or sanitizer allowance was added.

A single full rebuild/gate is now running for new core49eff3c (exec76959).
Source and global Windows compatibility changed, so all variants rebuild. Do not
edit test sources/fixtures during it. After completion fix the new heap-copy
strset test's comparison expression: capture strset() result before comparing
with text.data, avoiding unspecified operand evaluation order. Then targeted
repairs only; no unchanged full rerun. Inspect structured failures for fixed
pullup regression and new sanitizer effects before removing any allowances.

Eighteen queued-cut validation cases authored;17 passed0.75s on16c7dff.
Bare G10 correctly means L0/reload, not missing-P/L; renamed that case to
bare_g10_without_reload_handler_rejection_preserves_preceding_cut and kept
expected unsupported-command when no reload handler exists. Source guard
missing-P/L inside values.l>0 is unreachable through ordinary L-word parsing;
do not force it. Five normal string API cases also added (one directly asserts
safe promotion of base storage). Working registered total should now3,867,
90 beyond PR22 (verify from current CTest configuration).

Pending upstream116-test integration question remains; preserved attempt branch
integration-upstream-20f186f. No new PR readiness claim while latest source has
unsuppressed crashes and that upstream batch fails compilation. Continue useful
independent coverage and prepare truthful draft checkpoint if needed, no merging.

# Current batch69 transport, threading and upgrade checkpoint - 2026-10-19

Sixteen additional cases are validated:67 beyond PR22 /3,844 registered.
Five Modbus cases cover pin descriptions, oversized expected replies without
exception callbacks, separate timeout notification, blocking no-callback timeout
and device-exception recovery. G33 accepts cumulative encoder counters without
an optional reset callback. Three G76 sender-stop workflows cancel initial
radial approach, compound clearance and between-pass return; no subsequent cut
starts and parser/motor positions agree for relative restart. Three repeated-hole
G81 stops cover initial clearance, positioning and retract with unread tail
canceled. Three persisted legacy-build cases verify one-time spindle tolerance/
coolant migration and the downgrade opt-out. Full multi-spindle boot plus $RST=$
verifies persisted registered compile-time default and stopped spindle outputs.

One full local sanitizer gate3,844 ran57.32s,3,843 passed. The factory-reset
candidate wrongly expected a reboot-required spindle selection to change during
soft reset. Corrected it to assert persisted default reference, registered
reboot-required metadata and both stopped outputs; focused repair passed0.26s.
Consolidated full+repair3,844 passes strict summary. Raw evidence retained.
No additional expected failure or sanitizer exception. Core16c7dff unmodified.

Hosted51-case checkpoint39288629614 has source and coverage successful; compiler
jobs were still running at last read. Both downloaded locks match2881c0b/core
16c7dff, full regex and unchanged header filter. Measured17,052/17,652 lines
96.60%;11,719/13,700 branches85.54%. Last fully green verified run39286594112
measured96.54%/85.45%. No PR readiness claim until all five exact-head jobs pass.

Continue ordinary rejected sender blocks identified by the latest gap report.
Batch authoring first; no full-run repeats for unchanged code. Preserve separate
upstream integration branch and pending user question about its116 broken cases.

# Incoming upstream test integration held - 2026-10-19

Upstream20f186f adds116 G-code cases beyond merged PR22. A clean merge into
coverage-batch-69 failed compilation against clean Terje16c7dff: missing
ngc_tools.h in five initial targets; settings_get_coord_data and coord_system
.offset do not exist. Build log ../batch69-upstream-build.log retains evidence.
The merge attempt is preserved on integration-upstream-20f186f. Working branch
coverage-batch-69 was restored with reset --keep to its own validated2fa6e30;
no upstream cases were edited/deleted, no core source changed. Ask user whether
to repair the incoming batch separately; continue independent coverage meanwhile.
Do not merge that incoming batch or claim its116 cases passed. Next PR can still
compare our51 cases against upstream because Git retains shared aa80971 ancestry.
The original full sanitizer gate3,828 plus six-case repairs covers our actual tip.

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

CoreXY manual referencing: two normal-boot sender workflows PASS ASan/UBSan
0.30s. Public settings enable manual homing with empty automatic cycles; $H
zeros all Cartesian/motor coordinates, while $HX preserves Y/Z and updates
the coupled A/B motor coordinates. The host rejects any pulse or wakeup, so
manual referencing is verified without motion. Evidence:
build-asan/batch72-corexy-manual-results.xml and ../batch72-corexy-manual-tests.log.
Batch72 now35 new cases:22 hosted at05806c8 plus13 later local cases.
Registered total4,037. No new full-suite/hosted claim or CORE/exception changes.


Mixed CoreXY referencing: automatic Z switch homing plus manual XY completes
from normal boot through $H/$G. The test verifies real Z pulses and switch
pulloff, zero XY pulses, all axes homed, zero parser/motor origins and idle
without an alarm. PASS ASan/UBSan0.28s, evidence:
build-asan/batch72-mixed-results.xml. Batch72 now36 new cases, total4,038;
22 hosted plus14 later local. No new full-suite claim or CORE change.


Probe synchronization reset workflow PASS ASan/UBSan0.25s: queue a real cut,
request probing and send realtime reset after ten actual X pulses while the
probe waits for preceding motion. Verify interrupted motion, one driver reset,
GCProbe_Abort and no probe-start/completion callbacks or active probe monitor.
Fixture supplies mandatory coolant shutdown and driver reset callbacks; initial
missing-callback crashes were fixture errors, not CORE defects. Evidence:
build-asan/batch72-probe-reset-results.xml. Batch72 adds37, total4,039:
22 hosted and15 later local. No full-suite rerun, CORE change or allowance.


Active probe reset also PASS: a realtime reset after ten physical pulses aborts
before contact, invokes driver reset once, marks position lost and never reports
a successful probe/completion. Shared reset fixture now serves both timing cases.
Both PASS ASan/UBSan0.32s (batch72-active-probe-results.xml). Batch72 adds38,
registered4,040, with22 hosted plus16 local. One full gate now running in
../batch72-next-full-{build,tests}.log, tool session29505. Poll that handle; do
not restart. Fresh API: PR24 and25 remain open/unmerged; fetched clean Terje
core still7a6a432. Do not duplicate PR24 in a master-target coverage PR.


Batch72 second delivery gate is terminal: all4,040 targets build; full ASan/UBSan
129.52s gives3,939 clean passes,3 known reproductions and98 strict sanitizer
failures. Raw CTest96 differs because two inherited WILL_FAIL labels invert
crashes. Exact sanitizer case set matches prior checkpoint: zero additions or
removals; no failing case without sanitizer output. All38 batch72 cases pass.
Evidence: build-asan/batch72-next-full-results.xml, ../batch72-next-validation.json,
../batch72-next-full-summary.md and ../batch72-next-full-{build,tests}.log.
Push this checkpoint and dispatch one hosted check against clean7a6a432.
PR24/25 remain open; do not duplicate unmerged71 changes in a new master PR.


Spindle-address group: three sender-command cases PASS ASan/UBSan0.40s.
With primary M3/5000 and secondary M4/7000 running, reject M51P0$-1,
M5$-2 and disabled M5$2 without any hardware output callback, direction or
RPM change. A valid M5$1 afterward still stops only the secondary spindle.
Evidence: build-asan/batch72-address-results.xml and ../batch72-address-build.log.
Batch72 now41 additions, total4,043. These three are local-only after the
4,040-case full gate and hosted checkpoint539278b. Existing hosted run:
https://github.com/petervanderwalt/Unit_tests/actions/runs/39371716116
Do not dispatch unchanged validation or claim these three are hosted-verified.
No CORE changes, new exceptions or defect claims.

Acceleration profile guard: fractional G187.1 rejection preserves a previously
queued G187P2 cut, modal units/distance and selected acceleration. The following
ordinary move still plans at the same factor; both execute to160 physical pulses.
PASS ASan/UBSan0.26s, build-asan/batch72-profile-results.xml. This exercises the
previously uncovered fractional G187 guard through normal parser input.
Batch72 now42 additions, registered4,044; four are local-only after539278b.
Hosted39371716116 remains genuinely in_progress (source success; GCC/Clang/
coverage running). Do not restart or claim its result before terminal evidence.

Repeated drilling reset group: three workflows PASS ASan/UBSan0.40s.
A sender realtime reset interrupts G91 G81 L20 during initial clearance,
first-hole XY positioning or first drill feed. Real pulses verify that no
following phase/hole runs, the driver resets once, position is marked lost,
and motor/software positions remain at the reset snapshot. No speculative
alarm severity or restart policy assertion. Evidence:
build-asan/batch72-drill-reset-results.xml and ../batch72-drill-reset-build.log.
Batch72 now45 additions, total4,047; seven are local-only after hosted539278b.
No CORE modifications, known-bug changes, exception or full rerun.

Drill-reset follow-up adds two PASS cases: reset during G81 retract prevents
positioning for the next hole; reset during G83 drilling discards later pecks
and holes. The existing three cases also pass after shared fixture extension:
5/5 ASan/UBSan0.48s. Evidence: build-asan/batch72-drill-followup-results.xml.
Batch72 adds47, total4,049; nine local-only beyond hosted539278b. No new full
suite, hosted or coverage claim; source remains unmodified. Next work should
move to another supported gap rather than proliferating reset phase aliases.

Two sender-facing metadata cases PASS ASan/UBSan0.29s. Public resolution help
switches A between steps/degree and steps/millimeter as rotary configuration
changes, preserving linear X help. Actual settings iteration invokes the bound
stepper spindle unit hook for each axis, with step/rev only on A and normal
step/mm elsewhere; public description lookup reaches the spindle hook too.
The inherited callback-only fixture used a long placeholder unit; this integration
case instead supplies ordinary step/mm units fitting the existing core unit buffer.
No overflow issue is classified from that artificial placeholder. Evidence:
build-asan/batch72-metadata-results.xml. Batch72 adds49, total4,051; eleven
local-only after hosted539278b. No CORE changes, exception or full rerun.

Secondary-stepper reset chain PASS ASan/UBSan0.26s. Three registered motors
emit actual pulses; public mc_reset stops all before invoking the prior plugin
hook. Subsequent polling emits no pulses and reports zero speed. Repeated reset
while EXEC_RESET remains pending does not call the hook again. This covers the
third motor registration/list traversal and chained reset callback through the
public reset entry rather than directly invoking the installed callback.
Evidence: build-asan/batch72-stepper-reset-results.xml. Batch72 adds50,
registered4,052; twelve local-only after hosted539278b. CORE unmodified.
Hosted39371716116 last verified live: source success, coverage failed, GCC/Clang
running. Poll that exact run at next useful boundary, never redispatch unchanged.

Integrated pending PR25 reporting as a dependency for the next fresh coverage
checkpoint, preserving its independent review branch/PR. Merge retains current
AGENTS/PROGRESS and combines both CI-report fixes.58 Python helpers PASS6.808s.
No source changes or allowances. Next hosted run can now emit PARTIAL HTML/XML
while remaining red for documented CORE crashes; changed-code assessment stays
withheld on failed execution. This is not new passing coverage evidence.

Integrated batch72 checkpoint: all4,052 targets build; full sanitizer/strict
62.67s gives3,951 clean passes,3 known reproductions and98 source sanitizer
failures, identical case set to prior hosted/local checkpoints. All50 additions
pass; zero new/removed sanitizer cases and no failure without sanitizer output.
58 helpers pass. Evidence: build-asan/batch72-integrated-full-results.xml,
../batch72-integrated-validation.json and ../batch72-integrated-full-summary.md.
Hosted539278b evidence is now fully inspected: all38 additions pass both compilers;
source/harness locks verified; sole error location strutils.c:393. No firmware edit.
Push this50-case checkpoint and dispatch once to obtain fresh PARTIAL coverage.

Backlash restore group: two cases PASS ASan/UBSan0.30s. Public default restore
on a started driver clears cached take-up before the next real move; pulse and
physical/logical positions match the restored steps/mm with no compensation.
Coordinate-only restore retains the existing .1mm compensation:88 physical
pulses versus80 logical steps. These test settings_restore, not a reload API.
Evidence: build-asan/batch72-backlash-restore-results.xml. Batch72 adds52,
total4,054; latest two local-only after c9941ca. No CORE or exception changes.
Hosted integrated checkpoint is39373002337 at c9941ca (4,052 cases). Poll that
existing handle at the next useful boundary; do not dispatch unchanged validation.

Driver ganged-axis hook chaining: two cases PASS in normal/asymmetric auto-square
builds. A driver advertises an independently paired/auto-squared X axis before
kinematics registration. Public get_ganged queries preserve that X and add the
kinematics Y pair; Y is auto-squared only in its corresponding build. Both query
modes reach the original driver hook exactly once. The shared fixture gains an
optional pre-registration driver hook; all34 cases across both affected modules
PASS ASan/UBSan1.77s. Evidence: build-asan/batch72-ganged-hook-results.xml.
Batch72 adds54, total4,056; latest four local-only after c9941ca. No source or
exception changes. Next full gate remains deferred until a substantial boundary.

Auto-square driver-disable chaining PASS: original driver receives the exact Y/B
request and the subsequent all-motors re-enable request. Pulses suppress only
the secondary motor before re-enable, then restore the complete mask. Optional
pre-registration fixture callback leaves other cases unchanged. All35 affected
asymmetric ganging/auto-square cases PASS ASan/UBSan1.26s, evidence:
build-asan/batch72-disable-hook-results.xml and ../batch72-disable-hook-tests.log.
Batch72 adds55, total4,057; latest five local-only after c9941ca. No source,
known-bug or exception changes. Keep building a substantial group before another
full gate/push; current hosted run39373002337 must not be restarted unchanged.

Delayed plugin retry lifecycle: two cases PASS ASan/UBSan0.52s. A due event
callback cancels another pending retry during task processing while unrelated
due work still runs in order. A second case replaces that retry with a deadline
relative to current time, verifies it does not run early, then runs exactly once.
No private scheduler calls or simulated interrupt races; public task APIs and
controlled host ticks only. Evidence: build-asan/batch72-task-retry-results.xml.
Batch72 adds57, total4,059; latest seven local-only after c9941ca. Existing
standalone deletion/order tests were inspected first to avoid duplicate cases.
No CORE/exception changes. Hosted39373002337 last checked live with source-lock
and source-report artifacts only; await its fresh coverage, do not redispatch.

Builtin parameter macro read-only-write guard PASS ASan/UBSan0.27s. G65P3
cannot overwrite read-only position parameter5420; its value and caller Q scope
remain intact, call level unwinds and the failed return flag is clear. A following
write to writable global100 succeeds. Evidence:
build-asan/batch72-param-write-results.xml. Batch72 adds58, total4,060; latest
eight local-only after c9941ca. No source or exception changes. Hosted39373002337
was checked live this turn: all compiler/coverage jobs still running, no coverage
artifact published yet. Continue supported gaps without restarting that run.

No-tool-table builtin macro control PASS ASan/UBSan0.26s. Normal table-free
configuration rejects a G65P2 offset query, unwinds call scope, preserves caller
Q and clears the failed-return marker. A following writable-parameter macro works.
No fabricated tool pointer, source modification or expected-failure allowance.
Evidence: build-asan/batch72-no-tool-table-results.xml. Batch72 adds59,
registered4,061; latest nine local-only after c9941ca. Continue pending fresh
coverage39373002337 before selecting duplicates from the old map.

Fresh integrated coverage artifact is available from live run39373002337, harness
c9941ca and clean Terje7a6a432. HTML explicitly titled "Partial core coverage -
tests failed". Coverage JUnit has4,052 cases and98 SEGFAULT failures, exact same
case set as the documented core fault. GCC/Clang terminal results are still
pending; do not call the run complete. Partial investigation counters only:
16,916/17,645 lines and11,644/13,696 branches (NOT a passing baseline).
Relative to the earlier same-source partial artifact this records49 more covered
lines and80 more covered branches. Fresh map:
../batch72-integrated-coverage-core.gaps.json. It includes50 additions but not
later local cases. Use this map instead of the older ci-partial map.

Two full-queue drilling reset cases PASS, alongside all five affected existing
cases (7/7 ASan/UBSan0.44s). Sender queues ordinary short X moves, then G81
blocks waiting for planner room; reset interrupts preceding X motion before
any drill clearance/positioning or Z pulse. Positive-R and below-current-R
controls cover the distinct entry paths without private calls or forced abort
state. Evidence: build-asan/batch72-full-queue-results.xml. Batch72 adds61,
total4,063; latest eleven local-only after c9941ca. CORE/allowances unchanged.

Three additional buffered-drill reset controls PASS with all seven affected
existing cases (10/10 ASan/UBSan0.52s). Ordinary X cuts occupy the planner;
G81 then waits for room for its R-plane approach, feed or retract. Reset during
preceding X motion stops at the driver snapshot without any Z pulse, including
when the drill feed was already queued before retract enqueue blocked. Tests
use public queue availability and valid G-code, not private entry calls or
forced abort flags. Targeted paths come from the fresh partial gap map; no
new line-coverage claim until the next measured checkpoint.
Evidence: build-asan/batch72-drill-enqueue-results.xml. Batch72 adds64,
registered4,066; latest14 local-only after c9941ca. CORE/allowances unchanged.


### 2026-10-22 - asymmetric boot homing authoring

Added two public full-boot $H workflows with real asymmetric Y/A motor pulses.
Clear switches home independently to Y=80/A=160; X/Z remain stationary.
Engaged switches expose initial pull-off using a primary-only motor lock:
secondary receives no pulses and homing raises alarm8. Correct assertion retained
as exact WILL_FAIL/known_bug with source cause and removal guide in KNOWN_BUGS.
Four boot_square cases pass classification in0.43s:3 clean,1 expected failure.
Raw evidence square-engaged-raw.xml; classified square-engaged-classified.xml.
No CORE changes or sanitizer allowance. Local authoring group awaits the next
substantial cumulative full gate/push. No coverage gain claimed for this group.


### 2026-10-22 - asymmetric boot homing cumulative gate

Five new scenarios now cover initially clear/engaged switches, positive/negative
motor alignment trim, and public reset during final trim. Reset raises alarm6
and leaves both homed flags clear; physical travel and unrelated motors checked.
Full ASan/UBSan build/test/strict gates all0:4,165 cases in73.21s,4,148 clean,
17 exact expected failures,0 failed/skipped. Logs batch72-square-homing-*.
One new confirmed primary-only initial pull-off lock defect; no CORE changes
or sanitizer diagnostic allowances. Fresh origin master remains clean68eba79.
Previous pushed4c0c021 coverage artifact source/harness/filter locks match:
17,313/17,684 lines97.90%,12,121/13,754 branches88.13%,371 raw uncovered.
All seven coverage stage exits0; GCC/Clang still running at inspection, so this
is a coverage-job result rather than a new fully-green snapshot badge.


### 2026-10-22 - macro returns and short RTCP paths authored

Four cases: nested G65 O-word RETURN unwinds live IF frames through a plugin
return callback, preserves each caller argument, returns values13/17 and skips
both file tails; orphan named SUB rejects while retaining caller-owned file and
allows next assignment; short rotary move off-center emits one exact segment;
zero-linear-distance C90 exposes lost rotary endpoint, exact WILL_FAIL documented.
A mismatched named-file SUB protocol proposal timed out15.03s; retained outside
registration with TODO evidence pending error/stream ownership isolation.
No CORE changes. Cumulative sanitizer gate follows before next push.


### 2026-10-22 - macro/RTCP cumulative delivery gate

Full build/ASan/UBSan/strict summary all0:4,169 cases in69.07s,4,151 clean,
18 exact expected failures,0 unexpected failures/skipped. RTCP raw output
confirms requestedC90/emittedC0; no sanitizer diagnostic allowance. Four new
cases and the unregistered malformed-header proposal are retained distinctly.
All five individual hosted jobs for39831104507 at4c0c021 are terminalsuccess.
Both downloaded locks verify68eba79/source filter/core scope, all7 coverage
stages0,4,160total/4,144clean/16known. Report17,313/17,68497.90% lines and
12,121/13,75488.13% branches; badges/known-gap snapshot updated,371 raw gaps.
Newer homing run39833149909 at3c3f1d9 remainslive; no new coverage attributed
to this macro/RTCP batch before its exact hosted report. CORE remains clean.


### 2026-10-22 - flow error ownership and public rejection batch

Three new cases total4,172. Malformed named SUB timeout isolated to frame/sub
cleanup before named-file error reporting: bounded correct file-closure assertion
fails after safely releasing observed orphan, exact WILL_FAIL/known_bug and
source cause/removal guide added. Existing valid named CALL control now checks
its matching SUB header. Original full-protocol proposal remains unregistered
until upstream fixes ownership, replacing the previous uncertain TODO account.
Two grouped parser controls reject negative output/input ports, invalid wait
mode, and G70/71/72 axis-command conflicts without disturbing queued80-pulse cut;
registered output and input commands work afterwards. No CORE changes.
Full ASan/UBSan build/test/strict all0:4,172 in59.82s,4,153 clean,19 known,
0 unexpected/skipped. No sanitizer diagnostic allowance. Fresh core master
still68eba79 and clean. Logs batch72-flow-ownership-io-*.
Hosted39833149909 at3c3f1d9 now has all5 individual jobs terminalsuccess;
both artifact source/harness/filter locks and7 coverage stage exits verified.
17,317/17,684 lines97.92%,12,124/13,754 branches88.15%,367 raw uncovered.
New covered lines machine_limits206/524/527,motion_control1181. README/known-gap
snapshot updated. Newer0522e4e run39834732774 stilllive at inspection; current
ownership/I/O batch needs its own exact-head hosted validation before readiness.


### 2026-10-22 - real G76 interruption batch

Five new registered encoder/physical-motor workflows total4,177: sender STOP
during first synchronized cut cancels remaining passes and unread G1Z-5, stops
spindle and permits next sender move; RESET during cut immediately stops pulses,
marks position lost and prevents later passes; idle reset before entry taper,
after queued entry taper and after queued main cut prevents following stages
without falsely marking position lost. Exact radial/axial steps, encoder starts,
spindle/coolant shutdown and reset callbacks checked via normal realtime APIs.
Shared thread_reset_motion fixture installs mandatory coolant/reset callbacks;
initial missing-callback ASan fault was a fixture defect and was repaired.
No CORE defect/exception/sanitizer allowance added. Full build/ASan/UBSan/strict
all0:4,177 in59.96s,4,158 clean,19 known,0 failed/skipped. Logs
batch72-thread-interruptions-*. Fresh CORE master remains clean68eba79.
All5 individual jobs for39834732774 at0522e4e now terminalsuccess; both downloaded
source/harness/filter locks and7 coverage stage exits0 verified.4,169 cases,
4,151clean/18known.17,323/17,684 lines97.96%,12,131/13,754 branches88.20%,
361 raw uncovered. New lines RTCP308/363,flow657/773/774/779. Badges and known-gap
snapshot updated. Ownership/I/O run39835932809 remainslive at inspection;
thread group needs its own exact-head hosted report before coverage attribution.


### 2026-10-22 - batching correction and direct G65 return authoring

User rejects repeated 3-5-case full gates/hosted dispatches. Local AGENTS now
requires substantial cross-module authoring before cumulative delivery; never
full gate/push/dispatch just because a goal turn ends. Continue independent
work while CI runs; no repeated status polling. Three hosted runs/hour is a
ceiling, not a cadence. No artificial500-case quota or covered-case duplication.
Current direct G65 RETURN regression exposes real stack[-1] atflow774 with
UBSan then fatal ASan. Existing IF-frame return control passes. Shared loader
extracted without behavior changes; exact fatal inventory/runner handles this
combined diagnostic and rejects unrelated errors.9 matcher helper tests pass
0.519s; focused direct expected-crash plus IF-frame control pass0.48s.
Known-bug cause and exception removal guide recorded. This is local authoring
work, not a new full-suite/hosted checkpoint; no dispatch or coverage claim.


## Allocation failure and homing scope - 2026-10-24

Recorded user decision to retain all wall-plotter/polar homing on TODO, manual
referencing included. Valid VFS timestamp allocation failure returns -1 but loses
ENOMEM; untouched-backend, retry timestamp and preserved-CWD controls pass.
Retained correct errno assertion with one exact known failure and dated entry.
No CORE changes; no full gate or hosted run for this isolated addition.


## Two evidenced helper branch gaps and external provider evidence - 2026-10-24

Extended existing entry-extraction and bounded-substring cases for exact missing
branch outcomes in hosted40074304720. First axis-list entry and complete middle
placeholder matches assert returned pointers and content. No new fixture/case
count, no permutation batch. Recorded the bounded40-descriptor/10-file IPv4
provider survey with immutable primary-source links and blob IDs. Coverage gain
for local work remains unmeasured.

Focused validation: string-vfs74-results.xml has2 clean passes and1 exact known
regression, no unexpected failure/skips. Existing delta four-case classified
evidence and compound-reset evidence remain separate; no new full gate, hosted
run, commit or coverage increase claimed. CORE stays clean.


## Exact branch gap inventory - 2026-10-24

Created COVERAGE_BRANCH_INVENTORY.csv from locked40074304720 XML plus HTML.
It contains890 unique source/line sites and exactly1,097 missing outcomes.
Each emitted untaken-ID count matches XML; zero-hit sites whose HTML omits IDs
are explicit. Expressions come from pinned CORE2e165a1. Line dispositions are
context, not branch proofs; most sites remain review-pending. No coverage gain
or goal completion claimed.

First branch selection review: G-code4764/4780 has existing root invocation and
nested-scope motion controls despite7/10 reported outcomes. Marked both sites
compiler-mapping-review-pending rather than duplicating these scenarios. No
new test or run for this already exercised behavior.


## Preserve branch mapping at the normal report boundary - 2026-10-24

Observed duplicate branch3/4/5 labels with opposite coverage at G-code4764/4780
in actual hosted HTML. Added gcovr8.4 JSON output and HTML block IDs to the
existing report command; coverage* upload already collects them. No new hosted
run, source filter, merge-mode or instrumentation change. This retains the
metadata needed to distinguish branch records before adding duplicate G66 tests.

Validation: parsed reusable-tests.yml with PyYAML, checked all three explicit
report filenames and confirmed the existing coverage* upload matches each.
Diff check passes. gcovr8.4 option support verified in official documentation;
the changed hosted invocation remains unexecuted until the next substantial
batch boundary. No coverage or hosted-success claim from static validation.


## Legacy driver preserves ownership when modern banks are rejected - 2026-10-24

New ioports.legacy_driver_rejects_modern_banks_without_losing_existing_io uses
public legacy registration and real read/write callbacks. A modern digital and
analog expansion both reject through claim_hal=false while callbacks, counts,
metadata and the existing output remain intact. A following output transition
and input read still reach the legacy driver. No rejected-bank callback runs.
This complements the existing reverse-compatibility rejection; no fake private
state or unused provider was installed solely to enter a callback.

Focused ASan/UBSan passes0.07s, no allowance. Targets the short-circuit rejection
at ioports1071/1107; other missing records at those lines remain unproven and
all gain awaits cumulative measurement. No full gate, push or hosted dispatch.


## Accepted Modbus follow-up is silently discarded - 2026-10-24

A blocking read's normal reply observer requests the next register asynchronously.
CORE returns true but sends no follow-up after100 scheduler polls. First reply
bytes and a later independent blocking request pass. Retained accept-implies-
delivery assertion permits explicit refusal; no requirement for reentrant
blocking sends. Raw rtu-followup74-raw-results.xml confirms accepted1/sent0 and
recovery before final assertion fails. Exact WILL_FAIL plus dated KNOWN_BUGS;
no IRQ injection, sanitizer allowance or CORE edit. Gain remains unmeasured.


## Valid high-bit Modbus address loses completion - 2026-10-24

Standard server200 read reaches common decoder through the existing registered
transport fixture. Status_OK and correctly addressed request but zero callback;
server7 read controls deliver0x1234 before/after. Decoder217 checks the address
byte's high bit rather than the function exception flag. Correct callback and
value assertions retained with one exact allowance/dated KNOWN_BUGS entry.
Primary serial specification section2.2 establishes valid addresses1..247.
Raw modbus-high-address74-raw-results.xml fails only after the controls. This
is decoder validation, not physical UART evidence. No CORE edit or claimed gain.


## High-address decoder regression promoted to real RTU path - 2026-10-24

Replaced the new decoder-only case with modbus_rtu high-address regression,
without increasing case/allowance count. Public modbus_message now drives the
real RTU scheduler and driver UART callbacks. Driver returns the transmitted
address with valid CRC; request frame CRC checked too. Three replies consumed,
TX3, zero CRC errors/timeouts and both server7 register controls pass. Server200
still yields zero common completion callbacks. Raw rtu-high-address74-results
evidence is rtu-high-address74-raw-results.xml; final correct assertion fails.
Initial statistics check referenced nonexistent RX field; fixed to use actual
TX report, observed replies and consumed bytes, after reviewing report_stats.
No physical hardware claim, CORE edit or duplicate test. Exact allowance follows
the relocated case; coverage remains pending cumulative measurement.


## Accumulated driver/auxiliary checkpoint - 2026-10-24

Nine new cases beyond2d8b8d0 plus two existing helper extensions, covering delta
manual/auxiliary motion, compound G76 reset, VFS timestamp allocation failure,
legacy IO ownership and Modbus follow-up/high-address decoding. Six new exact
known-regression allowances retain correct assertions; no new sanitizer waiver.
One cumulative build and ASan/UBSan gate passes4,462 cases in147.17s. Strict
classification:4,427 clean,33 known regressions,2 known sanitizer diagnostics,
zero unexpected failures/skips. Evidence: build-asan/residual-driver74-results.xml,
residual-driver74-tests.log and residual-driver74-summary.log. Static workflow
YAML/artifact checks also pass. Unchanged reporting-helper tests were not rerun.

This gate pins clean CORE2e165a1, not latest upstream. Read-only remote refresh
found b01f481072edecac33d5e40c25869359a5b3fa1f, a single15-file update. Fetched
objects and reviewed diff without changing the CORE checkout. It includes
synchronized-output allocation validation/calloc, tapping macro fallback, RAM
truncate pointer repair, embedded mount ordering, claimed-pin boolean fix,
laser restore changes and VFS locate initialization. Next: validate affected
contracts against that revision and remove only demonstrated resolved allowances.
Do not dispatch stale-source CI merely to measure this checkpoint. Existing
PR28 remains open/unmerged at frozen a9f355c; branch73 matches it. Branch74
remote currently2d8b8d0. No PR merge or overlapping PR is authorized here.

Latest measured coverage remains frozen2d8b8d0/run40074304720:98.46% lines,
92.07% branch outcomes. This checkpoint has no measured gain yet. Raw line
inventory273 and branch inventory890sites/1,097outcomes still describe that
locked source/report. Rebuild inventories only from the next source-matched
measurement, preserving historical proof scope.


## Upstream b01 affected-contract validation and allowance cleanup - 2026-10-24

Selected upstream b01f481072edecac33d5e40c25869359a5b3fa1f after checking that
CORE had no local changes; only version selection, no firmware edits. The
16 affected regression targets build and pass classified ASan/UBSan1.16s:
12 clean,3 reproduced known regressions,1 exact remaining UBSan diagnostic;
zero unexpected failures/skips. Evidence: upstream-b01-cleanup-results.xml,
upstream-b01-cleanup-tests.log and upstream-b01-cleanup-summary.log.

Removed11 proven resolved WILL_FAIL allowances and the absent-axis sanitizer
label. Removed4 obsolete diagnostic manifest entries (two RAM fatal patterns,
absent-axis shift and signed bank-mask shift), retaining only the reproduced
32-channel map[32] diagnostic. Correct regression assertions remain. Removed
9 resolved KNOWN_BUGS sections and narrowed the 32-channel section.
- eight_axis.absent_named_w_position_in_inches_returns_zero
- fs_ram.truncate_committed_file_to_nonzero_length_preserves_prefix
- fs_ram.truncate_pending_upload_to_shorter_nonzero_length_preserves_prefix
- ioports.claimed_nonzero_output_retains_ownership_metadata
- motion_control.synchronized_output_allocation_failure_rejects_command_and_preserves_queued_cut
- multi_spindle.starting_secondary_preserves_pending_primary_override_ramp
- spindle_sync.stopped_spindle_rejects_rigid_tapping_without_calling_macro_fallback
- state_machine.constant_laser_door_resume_with_feed_hold_disable_action_off
- state_machine.dynamic_laser_door_resume_with_feed_hold_disable_action_off
- system.readonly_rtc_rejects_write_and_preserves_readable_time
- uvw_axis.motor_fault_uv_inversion_uses_remapped_axis_bits
- uvw_axis.motor_fault_w_inversion_uses_w_axis_without_following_x

The synchronized-output fixture now rejects calloc as well as malloc, matching
upstream's allocation change, while requiring exactly one rejected allocation,
queue preservation and successful retry. Tapping's running control explicitly
declines its now-supported fallback; stopped-spindle rejection still requires
no additional provider call and the original SpindleNotRunning status.

Partial fixes remain exact known failures: broadcast M48 clears disable bits but
secondary RPM remains7000 instead of8400; pendant release restores console and
handler but leaves RX enabled; VFS lookup still reuses /panel.nc after a later
growth failure. No broad success claim from patch appearance. Full b01 suite,
conditional-enum fixture compatibility, tapping fallback coverage and hosted
measurement remain pending in this accumulated source-update batch. No hosted
run or new PR dispatched for the affected-only check.


## Native tapping macro handoff with an A argument - 2026-10-24

COREb01 exposes the normal Unhandled tapping macro fallback instead of entering
it only through a failed synchronization defect. Added one eight_axis case using
its existing host variant and a publicly registered encoder-capable VFD. M3S100
establishes live RPM; N27G33.1A12.5Z-3K0.75I2 invokes macro331 exactly once at
scope1 with matching A/I/K/Z flags and local values. Parent #1/#26 restore, scope
returns0, overrides restore, no firmware motion is queued by the stub and no
alarm/reset occurs. The provider observes the handoff; this is not a physical
tapping geometry claim. No substitute mc_rigid_tapping or new build variant.

Focused ASan/UBSan passes0.06s: tapping-a-b01-results.xml. Initial fixture needed
state_machine.h and the same cold-start initialization as existing spindle
fixtures; fixed those setup errors without a CORE allowance. CMake registers
the case only when the selected source has the new native fallback guard; old
sources retain their documented unavailable-feature scope. Earlier source2e
line4866's A-argument gap now has a supported b01 trigger, still unmeasured.


## Conditional enum compatibility and full source rebuild - 2026-10-24

Started one full compile against b01 because its crossbar header changes every
host variant. Ninja session is tracked through the active tool handle; no
restarted build or full test run during this compile. The obsolete UVW test of
unconfigured ABC identifiers is omitted only for headers that no longer expose
those identifiers. Configured UVW mapping/inversion tests remain unchanged.
Unsupported tapping recovery now uses an explicitly declining macro provider;
its position, pulse and following-G33 assertions are preserved.

Verified feature selectors against actual2e/b01 source objects. A generic
Status_Unhandled guard also exists in older gcode, so tightened the new tapping
case selector to the native mc_rigid_tapping stub's Unhandled implementation.
It is absent on2e and present onb01. This corrects fixture registration rather
than accepting an unexpected old-source test failure. Build result pending.


The full b01 compile completed its11,728-step plan with one fixture error:
RTCP A/C test referenced now-absent Input_LimitB. Guarded only that legacy
identifier check; retained all configured A/C and grouped-enable assertions.
Incremental full build then passed. Started the single cumulative b01 sanitizer
suite with tracked session25395 and output upstream-b01-suite-tests.log/XML.
Its runtime result remains pending; do not claim full-suite success yet.


## Full b01 sanitizer result and isolated compatibility repair - 2026-10-24

Full4,462-case execution completed233.32s with one obsolete tapping-status
fixture failure. Raw XML and strict summary remain unchanged/red, preserving
that evidence: upstream-b01-suite-results.xml and upstream-b01-suite-summary.log.
The remaining4,461 cases completed:4,438 clean,22 documented regressions and
one exact map[32] sanitizer diagnostic. No other unexpected failure/skips.

The gcode check-mode case assumed native G33.1 always rejects. Registered an
explicitly declining provider, preserving UnsupportedCommand, no queued motion,
unchanged position/overrides and successful following G33. Focused repaired case
passes0.07s plus strict summary in upstream-b01-checkmode-repair-results.xml.
No new allowance, synthetic green aggregate or repeated full suite. This is
a full execution plus separately verified repair, not a single exact-head clean
full-run claim; hosted current-head validation remains required.


## Supported recursive tapping overflow and next-cut recovery - 2026-10-24

Added one case on the existing encoder/stepper fixture. A public macro331
provider accidentally calls G33.1 recursively until the ordinary call-stack
limit rejects it. No direct ngc_call_push or scope injection. Every unwinding
callback retains its local #1 and depth; root #1=99 and overrides restore.
The recursion emits no pulses or sync starts. A following real G33 completes
80 Z pulses at the requested endpoint, with X stationary and no alarm/reset.
Focused ASan/UBSan passes0.07s (tapping-overflow-b01-results.xml), no allowance.
This targets b01 gcode4861's native stack-overflow return (old2e4864), now
reachable through the supported fallback. No new full gate/push/CI for this
isolated addition. Frozen hosted7bece00 does not include it.


## Hosted source-check recovery after allowance cleanup - 2026-10-24

Run40082454827 stopped in source/helper validation; compiler and coverage jobs
were skipped. Reproduced locally: the type-spelling matcher unit test read the
active absent-axis diagnostic allowance after that defect was correctly fixed
and removed. Isolated its historical diagnostic fixture for both matching and
wrong-source rejection tests; production manifest stays clean. All82 helper
tests pass7.85s under simulated Actions environment. Reporting policy and
regression assertions unchanged. Pushed7bf1306 (helper repair only), preserving
new recursive-tapping work locally. A single corrected-head hosted retry was
requested against the same pinned b01 source; no full local rerun for this
Python-only fix. Previous failure remains recorded, never counted as green.


## No invented external providers from indexed caller survey - 2026-10-24

A bounded grblHAL organization search found only native CORE symbols for
device_fs_add_stream and gc_set_tool_offset. It supplies no actual non-UART
mount provider or additional tool-offset mode caller. Recorded this evidence
without claiming exhaustive unreachability or writing artificial provider tests.
Hosted40082861198 source job is now verified successful; GCC, Clang and coverage
jobs are live at the last inspection. No redispatch or measurement claim.


## Redirected macro to plain RAM job ownership transition - 2026-10-24

New stream_file case executes a redirected G91 fixture file through the actual
protocol loop. Its local EOF closes that owner; the prior provider opens a real
RAM G90 job and selects its own reader through public stream_set_file. The
persistent EOF wrapper must delegate the second completion with no active
redirect context. Exactly one redirect EOF, two provider EOFs, both files closed,
no parser error, G90 state, restored serial reader and responding $G are asserted.
No direct invocation of private readers or fabricated NULL file state.

ASan/UBSan passes0.09s: file-owner-transition-b01-results.xml. Reused existing
protocol fixture; made its optional whole-run helper static inline so callers
can reuse setup callbacks without unused-function warnings. No behavioral
change to existing helper. Targets stream_file94's empty-redirect-stack arm,
still unmeasured and not included in frozen7bf1306 hosted run. No full gate
or additional hosted run for this case.


## First b01 coverage evidence available - 2026-10-24

Downloaded coverage/report artifacts from40082861198 without waiting on the
still-running GCC/Clang builds. Verified both harness/source/filter locks and
exactly seven successful coverage stages. Counts:17,488/17,757 lines98.49%,
12,774/13,852 branches92.22%,269 missing lines/1,078 missing outcomes. Coverage
4,462 cases:4,441 clean/21 known/0failed/skipped. No badge promotion or full-run
success claim; source changed, so no same-source delta attribution.

Raw coverage.json now preserves source-block identities: G66's repeated branch
numbers represent distinct blocks with different counts, not one unique branch
key. Mapping review remains required before duplicate tests. New concrete
source targets include analog-output allocation rejection gcode2647 and
embedded first-mount rollback252. Full missing list is captured separately in
build-asan/upstream-b01-missing-lines.json. The new file-transition test was
strengthened to require G91 at first EOF then G90 at second EOF/final sender
report, proving both programs executed; focused sanitizer check passes0.07s.


## Analog allocation rejection and embedded mount rollback - 2026-10-24

New analog M67 failure case uses registered two-output hardware, rejects one
allocation with exact OutOfMemory, preserves the existing queued80-step cut
and prior setpoint, retries then verifies160 physical X steps and exactly
two correctly ordered analog outputs25/50 on pins0/1. No premature output or
abort/alarm. ASan/UBSan passes0.05s, targeting new gcode2647.

First embedded mount allocation failure reaches new rollback252. The asset
pointer resets and retry works, including reading assets from the mount
notification. However the failed operation changes unrelated root hidden1->0
without a mount notification. Correct root-preservation assertion retained
with one dated known regression and exact allowance; no leakage claim or
sanitizer waiver. Raw two-case evidence: analog-embedded-b01-raw-results.xml.
No new full gate, push or hosted run for these local additions.
