# Remaining raw CORE coverage

## Latest coverage job passed; compiler matrix remains failed

[Run40107107939](https://github.com/petervanderwalt/Unit_tests/actions/runs/40107107939)
coverage passed on harness49b18b0cb0e0e4f76d689173355cc0e5721ca55f and
COREb01f481072edecac33d5e40c25869359a5b3fa1f. Artifact/report locks and
filter core/.*\.[ch]$ match; all seven coverage stages exit0, no findings.
17,491/17,757 lines (**98.50%**) and12,801/13,852 outcomes (**92.41%**):
266 missing lines and1,051 missing outcomes. Coverage4,484 total/4,461 clean/
23 known/0 failed/skipped. Same-source40103625282 delta: zero new/lost lines,
ten additional outcomes/no loss. Exact new sites: gcode2998, delta761/907,
report395/1480/1498, settings2163(three outcomes)/2260. These match the authored
ordinary workflows. All nine new cases individually pass on Clang.

The nonblocking MPos case adds no outcome, so its mapping was inspected before
more offset work. The remaining synchronized MPos path now has a local public
$10=289/G92/actual-motion regression; gains remain unmeasured. Eight later local
homing/jog/offset/timer/check-mode/PWM-settings workflows pass full4,492 local
sanitizer/strict validation and await a new exact-head measurement. Both inventories
match this report, preserving dispositions and function/source-block identities.
Historical explanations below still require current-caller proof.

The run completed FAILURE: source/GCC/coverage passed; Clang/summary failed.
Clang's existing tapping table fault varies across builds. This run reports
eight-axis index29 and unsupported fallback index27 at the same27-entry table,
gcode485 and macro_arguments_push. Recursive index27 matches. Two new local
exact test/index entries pass saved production replay/first1024 and negative
controls. Different/unseen diagnostics, absent diagnostics and zero-exit output
remain red; no range/wildcard allowance. Post-crash assertions are unvalidated
on Clang. Draft PR30 stays unready; badges retain fully green40074304720.
No CORE edits, exclusions or dummy tests were added.

Current b01 source proof: report_driver_error's queued callback is removed by
native failed-startup filtering (grbllib407-424/844-861); output_help is bypassed
by HELP prefix dispatch (system1159-1160 before table dispatch). Nine historical
line rows now have these specific current-source explanations. Raw counts remain;
existing public tests cover the actual routes, so no private-entry tests were added.

Working checkout is now upstream `b01f481072edecac33d5e40c25869359a5b3fa1f`.
The table and percentages below are the prior fully green CORE2e165a1
snapshot; current coverage-job evidence is reported separately above.

Verified coverage report: [run40074304720](https://github.com/petervanderwalt/Unit_tests/actions/runs/40074304720),
harness `2d8b8d0f980c74dd6da5252a9a91cf17a50e93e8`, CORE `2e165a1ac4c74be8e68971972c6577775d856b05`,
filter `core/.*\.[ch]$`. Both artifact locks match and exactly seven coverage
stages exit0. All five source/GCC/Clang/coverage/Results summary jobs passed
at final API inspection.

17,483/17,756 lines (**98.46%**) and12,737/13,834 branch outcomes (**92.07%**)
were covered:273 raw missing lines and1,097 missing outcomes. Coverage job:
4,453 cases,4,427 clean/26 known/0 failed/skipped. Against same-source40070163310:
Three additional lines and seven branch outcomes, no lost covered lines and the
same denominator. New lines: machine_limits269 and delta320-321.

Success badges show fully green40074304720 (98.46%/92.07%). New manual-auxiliary and compound-preparation-reset cases remain local and are
separate from this measured head. The earlier G76 preparation reset did not cover715.

Raw coverage does not establish correctness or reachability. See [TODO](TODO.md)
and [KNOWN_BUGS](KNOWN_BUGS.md) before selecting workflows. Historical audits
remain pinned to their stated revisions; no source exclusions were added.

| Source | Uncovered lines | Missing branch outcomes | Exact executable line numbers |
|---|---:|---:|---|
| [core/crossbar.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/crossbar.c) | 0 | 0 | none |
| [core/crossbar.h](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/crossbar.h) | 0 | 2 | none |
| [core/fs_device.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/fs_device.c) | 3 | 3 | 59, 190, 192 |
| [core/fs_embedded.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/fs_embedded.c) | 4 | 5 | 133, 135, 138, 140 |
| [core/fs_ram.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/fs_ram.c) | 0 | 11 | none |
| [core/gcode.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/gcode.c) | 29 | 189 | 325-326, 573, 1043, 1367-1368, 1499, 2190, 2728, 2730-2731, 2746-2747, 2898, 2987, 2999, 3065, 3482-3484, 3616-3617, 3929, 4314-4315, 4864, 4866, 4978-4979 |
| [core/grbllib.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/grbllib.c) | 14 | 29 | 92, 95, 140, 144-147, 149-150, 590-594 |
| [core/ioports.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/ioports.c) | 28 | 129 | 782, 1195, 1291-1292, 1385, 1387, 1389, 1391, 1394-1398, 1401-1402, 1404, 1406-1407, 1409, 1411-1412, 1436-1438, 1440-1441, 1558-1559 |
| [core/kinematics/asymmetric_ganging.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/kinematics/asymmetric_ganging.c) | 1 | 4 | 254 |
| [core/kinematics/delta.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/kinematics/delta.c) | 7 | 45 | 180, 376, 619-620, 625, 643, 706 |
| [core/kinematics/polar.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/kinematics/polar.c) | 4 | 3 | 212, 214, 232, 234 |
| [core/kinematics/rtcp_ac.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/kinematics/rtcp_ac.c) | 0 | 3 | none |
| [core/kinematics/wall_plotter.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/kinematics/wall_plotter.c) | 56 | 28 | 208, 213-214, 216-227, 229, 234, 237, 239-240, 242-255, 257, 260, 262, 264-280, 283-284 |
| [core/machine_limits.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/machine_limits.c) | 1 | 15 | 502 |
| [core/modbus.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/modbus.c) | 3 | 4 | 231-233 |
| [core/modbus_rtu.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/modbus_rtu.c) | 3 | 34 | 241, 360-361 |
| [core/motion_control.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/motion_control.c) | 2 | 26 | 690, 715 |
| [core/my_plugin.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/my_plugin.c) | 2 | 0 | 26, 29 |
| [core/ngc_expr.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/ngc_expr.c) | 11 | 13 | 115-116, 189-190, 250, 252, 292-293, 337-338, 341 |
| [core/ngc_flowctrl.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/ngc_flowctrl.c) | 2 | 45 | 816-817 |
| [core/ngc_params.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/ngc_params.c) | 4 | 40 | 772-773, 942, 1247 |
| [core/nuts_bolts.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/nuts_bolts.c) | 0 | 1 | none |
| [core/nvs_buffer.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/nvs_buffer.c) | 3 | 7 | 366, 391-392 |
| [core/planner.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/planner.c) | 0 | 1 | none |
| [core/probe.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/probe.c) | 0 | 0 | none |
| [core/protocol.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/protocol.c) | 1 | 45 | 185 |
| [core/regex.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/regex.c) | 0 | 0 | none |
| [core/report.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/report.c) | 5 | 65 | 450-452, 1955-1956 |
| [core/settings.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/settings.c) | 58 | 124 | 701, 703, 780-781, 839, 925, 928, 1012, 1056, 1140-1141, 1199-1200, 1341, 1351, 1507-1508, 1569, 1577, 1584, 1591, 1594-1596, 1652-1653, 1693-1694, 1901-1902, 1960-1961, 2026-2027, 2175-2177, 2179-2181, 2192-2194, 2196-2198, 2239-2241, 2247-2248, 2957, 2959, 3476-3477, 3625-3627 |
| [core/sleep.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/sleep.c) | 0 | 1 | none |
| [core/spindle_control.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/spindle_control.c) | 7 | 24 | 499, 503, 1160-1161, 1172, 1215-1216 |
| [core/state_machine.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/state_machine.c) | 12 | 42 | 157, 449, 502, 524-527, 614-615, 658-659, 819 |
| [core/stepper.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/stepper.c) | 1 | 12 | 1093 |
| [core/stepper2.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/stepper2.c) | 0 | 11 | none |
| [core/stream.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/stream.c) | 3 | 17 | 277, 370, 615 |
| [core/stream_file.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/stream_file.c) | 1 | 9 | 73 |
| [core/strutils.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/strutils.c) | 0 | 5 | none |
| [core/system.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/system.c) | 2 | 30 | 466, 468 |
| [core/tool_change.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/tool_change.c) | 2 | 37 | 435-436 |
| [core/utf8.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/utf8.c) | 0 | 1 | none |
| [core/vfs.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/vfs.c) | 4 | 37 | 272, 415, 482, 779 |



## Complete line inventory and finite review queue - 2026-10-24

[Per-line inventory](COVERAGE_LINE_INVENTORY.csv) contains all 269 current raw
missing lines from the pinned report above, one row per source/line with disposition and
evidence. Its source/line set was checked against the downloaded coverage XML,
not just summed from the Markdown table. Historical matches remain labelled as
historical; a matched explanation is not a fresh proof of global unreachability.
No line was removed from the denominator.

Every line now has an explicit disposition. This does not mean every line has a
reachability proof: protocol185 and state_machine502 remain public-trigger-pending
after their native alarm producers were enumerated. machine_limits269 and delta320-321 are now measured covered and removed from
the residual CSV. motion_control715 remains missing; the revised compound setup
regression awaits the next measurement. The standalone internal-motor homing case is configuration-contract-
pending; normal public masks exclude that motor. Other contracts, configuration
and fixture dependencies retain separate categories in the CSV.

## Current-source target correction - 2026-10-24

Source inspected at CORE `2e165a1ac4c74be8e68971972c6577775d856b05`.
This supplements the raw report above; it changes no coverage counts. The
113-line settings/G-code/helpers/state-machine total is not a reachable target
estimate. No supported line-gain estimate is established yet.

### General helpers: all 14 missing lines accounted for

| Exact lines | Count | Evidence / disposition |
|---|---:|---|
|grbllib.c92,95|2|Empty weak board_ports_init hook, replaced by driver-owned initialization in the host. No observable default action. Harness/no-op limit.|
|grbllib.c140,144-147,149-150|7|Private report_driver_error formatter. Existing failed-startup audit establishes that startup task filtering drops this detailed diagnostic. Preserve the generic fatal-startup regression; formatter policy needs upstream clarification, not a direct private call.|
|grbllib.c590-594|5|Interior delayed-task removal fallback. Existing atomic-selection audit applies to the unchanged code: due-task selection retains IRQ masking through the head identity check. No supported intervening mutation identified.|
|**Total**|**14**|**Remove these from the proposed executable-work queue. Keep them in the raw denominator.**|

### G-code: newly matched source contracts

| Exact lines | Count | Evidence / next action |
|---|---:|---|
|gcode.c325-326|2|gc_set_tool_offset handles Cancel and EnableDynamic; both native tool_change.c callers pass EnableDynamic. Other enum values are public API values but a supported external caller of this particular helper has not been established. External-caller contract question, not proven universally unreachable.|
|gcode.c573|1|Existing prefix-copy proof still matches source507-516: rpm_mode is restored before the later comparison. Do not author another CSS snapshot test for this assignment.|
|gcode.c2987,2999|2|Public G43/G43.2 decoding at1706-1709 requires a nonempty tool table before selecting these modes. The later no-table checks repeat that requirement. Do not mutate the table between parser phases to reach them.|
|gcode.c4864|1|Call-push failure in rigid-tapping continuation. Native mc_rigid_tapping is an UnsupportedCommand stub, but the existing stopped-spindle regression proves an initialization error can enter this continuation. This is defect-dependent reachability, not a blanket unreachable classification. A resource/depth regression here must preserve the original SpindleNotRunning contract; do not normalize the erroneous macro fallback.|
|gcode.c4866|1|A-axis argument construction in that same continuation. Requires both A_AXIS and entry into the continuation. Establish an actual supported tapping provider/configuration before adding a substitute implementation solely for this line.|
|**Matched here**|**7**|These are classifications, not seven promised newly coverable lines. Other G-code gaps retain their individual audits or remain pending.|

### Settings: all 58 missing lines matched to existing audits

Current source line mapping checked at CORE2e165a1. Existing registration and
caller proofs are documented in TODO under "Counted public settings guards"
and "Remaining settings defaults"; the historical line offsets below have
been corrected against the current source. These are not 58 pending tests.

| Current exact lines | Count | Classification |
|---|---:|---|
|2175-2177,2179-2181,2192-2194,2196-2198,2239-2241|15|Unused availability arms: four descriptors use NULL availability; timezone registration is disabled.|
|839,1012,1056,1341,1351,1569,1577,1584,1591|9|Repeated capability/build/availability rejection after public setting lookup has already gated access.|
|925,928,1140-1141|4|PWM bounds and mode default preempted by registered format validation.|
|701,703,780-781,1199-1200,1507-1508,1594-1596,1652-1653,1693-1694,1901-1902,2247-2248|19|Private routing defaults without a corresponding available registered ID; deprecated spindle getter is hidden.|
|1960-1961,3476-3477|4|Datatype defaults after all applicable valid types have explicit handling.|
|2026-2027|2|Public integer getter with noninteger direct metadata: possible API mismatch, but no supported caller established. Contract question, not universal unreachability.|
|2957,2959|2|No-tool-table persistence success/no-op stub; native G10 rejects before calling it.|
|3625-3627|3|Direct-buffer IPv4 write-provider contract unresolved. Registered function-provider writes already covered.|
|**Total**|**58**|**53 have existing guard/unused/stub explanations; five remain external-caller/provider questions. No proven untested native settings workflow identified.**|

### Controller-state routing: current source, not an assumed test gap

The native hold entry calls in state_machine.c324/341 accept HOLD, SAFETY_DOOR
or SLEEP. They install the hold/resume handlers for those states. Selecting
TOOL_CHANGE at315-318 instead installs state_await_toolchanged directly.
Consequently the TOOL_CHANGE arms at524-527 and658-659 (six missing lines)
do not describe the native manual-change acknowledgement workflow. The existing
full-boot M6 pause and cancelled manual jog cases already assert acknowledgement,
position, stream restoration and completed tool selection; do not add variations
of them to try to reach these six arms.

The hold-switch default arm at614-615 (two lines) is likewise outside the three
native hold states, all of which have explicit cases. These eight lines remain
raw gaps. This is a native-routing proof, not a universal restriction on external
plugins calling state_set during callbacks. The cycle-handler tool-change line449 and pending-alarm cancellation line502
are examined separately in the later caller reviews below.

### Selected-stream predecessor fallback

Current stream.c370 follows removal of a stream whose predecessor is MPG. The
fallback tests the descriptor before MPG. add_connection installs base.stream
before any later connection is linked, and every allocated connection receives
its nonnull descriptor before insertion. The chain before MPG therefore has a
nonnull base/registered descriptor. No native stream API clears it. The fallback
remains counted; do not mutate connection records to create a missing descriptor.

### Other matched gaps retained outside the authoring queue

- RTU241: TimeoutException is assigned only for the blocking owner; asynchronous
  timeout clears its packet and enters Silent earlier. Existing async and blocking
  timeout/recovery tests remain. RTU360-361 are separately unresolved nonaborting
  reset-during-blocking-retry semantics; do not simulate cancellation ownership.
- motion_control690 and gcode3482-3484: G76 main-taper calculations have no
  consuming generated taper move. Preserve the implementation-scope question;
  executing the calculations while asserting straight motion would bless the
  wrong geometry. Existing entry/exit taper tests address different behavior. User decision2026-10-24:
  retain main taper on TODO; no regression or expected-failure allowance.
- machine_limits502: zero locate rate after seek has an unresolved reference/
  disabled-axis contract. Do not invent final homed coordinates to cover it.

### Delta: nine audited lines, seven still missing

| Lines | Count | Current evidence / next action |
|---|---:|---|
|706|1|Unreachable post-search fallback: the do/while continues while !ok, and its early break also requires ok. Both exits therefore imply ok before if(!ok). No test can reach the copy through this unchanged loop.|
|619-620|2|Public XYZ automatic home followed by $22/manual $HA now establishes A's homed precondition. A999 rejects; correct A-1 retry also rejects and is retained in an exact known regression. Targets pending measurement, no sys.homed injection.|
|643|1|Resolved setup: reference A first, then automatically home XYZ. A public soft-limited mixed jog reaches X100/Z-300/A-1; published cuboid maxX=1. Physical/logical joint counters agree. Passing local regression, line measurement pending.|
|180,625|2|Forward-transform nonassembly/NaN handling and its travel-check rejection. An actual motor-position/driver failure contract is still needed before choosing an input and expected recovery. Not classified as impossible for arbitrary numeric input.|
|320-321|2|Reachable: normal streamed move from(-250,0,-150) to(250,0,-150) crosses an unreachable interior with default rod lengths. New full-boot physical-cutoff regression passes; cumulative line measurement pending. No private state injection.|
|376|1|Workspace top lies below the configured floor. Establish the required behavior for physically incompatible home/floor geometry before asserting a clamped usable workspace. Do not bless an infeasible robot configuration merely because the descriptor accepts its numbers.|
|**Audited total**|**9**|**Two measured covered; one dead fallback; one local passing target; two known-regression targets; three pending trigger/contract questions.**|

### Reachable aborted-homing guard: local regression added

machine_limits.c269 is not necessarily an invalid post-abort caller. With normal
compatibility0 homing progress reports disabled, mc_homing_cycle first reports
status and performs a 100ms realtime-serviced delay at motion_control.c901-906.
A sender reset during that interval sets abort before limits_go_home invokes the
native home_machine. The entry guard therefore protects a real supported reset.

New boot.reset_during_initial_homing_report_delay_prevents_all_motor_motion
uses the existing full initialization/stepper driver fixture, a public reset
command and an ordinary $HX/$G input stream. It asserts no driver wake, no motor
pulses or displacement, no homed axes, an empty planner and a responding parser
after reset. Focused ASan/UBSan passes0.05s. No expected-failure allowance or CORE
edit. Hosted40074304720 now verifies machine_limits269 covered. The denominator is
unchanged; that line has been removed from the current residual inventory.

### G76 first-approach abort: measured target correction

Hosted40074304720 proves the earlier idle-preparation reset case did not execute
motion_control715: reset was consumed before thread initialization. It remains
a valid no-motion preparation-abort regression, but is not claimed as a line gain.

New spindle_sync.reset_after_g76_compound_setup_is_queued_prevents_first_radial_move
uses G76Q29 to queue the compound-slide setup rapid. At the next public foreground
poll it observes that real queued setup, requests reset and verifies no driver
pulse, encoder synchronization or first radial move; spindle/coolant shut down
and physical position is preserved. Focused ASan/UBSan passes0.15s. This is a
cooperative realtime checkpoint, not an invented IRQ between adjacent instructions.
It targets715 after a setup move exists; actual coverage still awaits measurement.

### Other newly matched callers

Asymmetric ganging254 requires a homing cycle containing the internal secondary
motor without its primary. Public Format_AxisMask validation uses the three
logical axes, rejecting bit8 before its setter; the ganging callback adds bit8
only to cycles containing the primary. A persisted configuration migration or
external provider that supplies a standalone internal motor remains a separate
contract question, not a normal public setting test.

State-machine449's active-cycle EXEC_TOOL_CHANGE branch has no native producer
before motion synchronization: both G-code and manual tool-change producers
synchronize first. Do not queue that internal flag during an unrelated cut.
Existing full-boot manual change tests cover the native idle dispatcher.

### Deferred alarm paths: native producers enumerated, trigger still pending

A scan of all CORE C files finds pending-alarm assignments only in system.c:
probe contact during CYCLE/JOG140, disconnected active probe147, and alarm deferral
while in ESTOP/critical blocking state1355. Reads are protocol184/577,
state_machine501/519 and system455; system1349 clears an alarm when raised.

For state_machine502, ordinary probe contact queues EXEC_STOP, whose protocol
handler consumes the pending alarm before motion-cancel dispatch. Disconnection
queues feed hold, whose completion uses state_await_hold520 instead. Deferring
an alarm in ESTOP/critical lock does not supply a normal runnable jog. No ordinary
cancel sequence reaching502 has been demonstrated. An asynchronous alarm during
cancellation is not declared impossible, but no timing-specific injected flag is
being used as a substitute for an established driver event sequence.

For protocol185, startup's idle/door branch has no demonstrated active
CYCLE/JOG/probing producer. Existing critical/deferred boot alarms stay in their
alarm/unlock path instead. External callbacks could change this conclusion;
this is a public-trigger question, not proof that all possible providers are
excluded. Both lines remain raw and explicitly pending, with no allowance.

### Reachable delta interior inverse failure: local regression added

Default 300mm forearms and100mm biceps admit both Cartesian endpoints
(-250,0,-150) and(250,0,-150), but not their connecting segment's center. For
example the center's distance to a leg pivot is less than the200mm difference
between the two rod lengths. A bounded independent geometry calculation found
this pair; no private state or invalid enum was used.

New full-boot streamed G53 rapid/dwell/move/dwell/$G regression reaches the first
endpoint using real driver pulses and observes cutoff near(-164.857,0.126,-149.930)
before the inner unreachable region. It asserts finite physical position, stopped
planner, unchanged travel height, matching motor counters, exactly one terminal
response per command and a responding parser. The opposite endpoint also has a
finite inverse/forward roundtrip to the requested position. Safe cutoff is the
contract under test; error versus success response policy is deliberately separate.
Final focused ASan/UBSan passes0.10s including the opposite-endpoint assertion;
hosted40074304720 now verifies delta320-321 covered. Both are removed from the
current residual inventory; no CORE edit or allowance.

### Historical audit freshness check

Compared the historical CORE50f3865 source blobs with the pinned CORE2e165a1.
Twenty-one historical inventory rows refer to line-identical source files;
this confirms unchanged local code, not every external caller/header assumption.
For changed expression, flow, I/O, stream, reader and VFS files, reviewed their
source diff: native enum dispatch sets and the cited lookup/registration guards
are retained. G-code M6 release4314-4315 is now explained by the current check-
mode normalizer, not the obsolete opposite-outer-guard argument. Earlier proofs
remain explicitly scoped rather than promoted to universal runtime claims.

### Public manual auxiliary reference resolves the homing setup question

A four-axis configuration can home only XYZ automatically, then enable manual
homing through $22 and issue $HA for an operator-referenced auxiliary A axis.
The new fixture performs both real native paths; it never sets sys.homed.
This supersedes the assumption that an all-four-switch $H was the only possible
precondition. That older automatic homing proposal remains separately unresolved.

The supported manual route exposed a defect: stationary XYZ joint coordinates
change0 to-6 at1000steps/rad when $HA references A. The companion limit sequence
correctly rejects A999 but also rejects the legal A-1 retry. Both keep correct
assertions in separate narrow known regressions, with raw evidence and dated
KNOWN_BUGS entry. Focused classified2/2 plus strict summary passes: two reproduced
known defects, no unexpected failure/skip and no sanitizer allowance. This makes
auxiliary rejection619-620 a demonstrated target; line gain awaits measurement.
A separate manual-first positive control now resolves the outside-cuboid
auxiliary guard643 dependency without changing production state directly.

### Correct manual-first configuration and false-cut soft-limit regression

Referencing A before automatic XYZ homing avoids the unrelated post-XYZ manual
reference defect. The positive control completes both public homing paths, then
with $20 enabled reaches X100/Z-300/A-1 through ordinary jog commands. Published
cuboid maxX is1, so this accepted point exercises the non-cuboid auxiliary limit
loop643. Physical pulse-derived joint counters agree with logical counters and
the requested Cartesian endpoint; no private homing flag or coordinate write.

The same configuration exposes a distinct ordinary-cut defect: a first1mm Z cut
completes with soft limits off, but enabling $20 falsely alarms on the next1mm Z
cut while A stays correctly at0. Delta619 forwards is_cartesian=false for the
auxiliary pass-through check, and the native checker698 rejects that frame.
The correct no-false-alarm/second-cut assertions have one exact WILL_FAIL and a
dated KNOWN_BUGS entry. A public realtime exit only releases the alarm loop.
Raw positive-control cut evidence shows7acks, A0 and XYZpulse0=108/98 before the
correct false-alarm assertion fails. Source and output issue is documented;
CORE remains unchanged. Classified four-case ASan/UBSan and strict summary pass
0.55s: one clean control, three reproduced known regressions, zero unexpected
failure/skip. These local cases are not part of frozen hosted head2d8b8d0.

### Work queue before another cumulative measurement

1. Match remaining current missing lines to the existing exact audits; only
   investigate unmatched source. In particular, do not re-open the 14 helper
   lines above or the disabled I/O/settings registrations as fresh opportunities.
2. Resolve remaining native configuration/caller questions first: delta homing
   and motion paths, state-machine tool-change transitions, Modbus recovery,
   and remaining filesystem entry guards. A target enters the authoring queue
   only with a public trigger and an observable result identified from source.
3. Keep G76 main-taper semantics, external provider contracts and incomplete
   native homing/tapping implementations separate from executable test work.
4. Accumulate tests for proven supported targets on the current branch. Existing
   broadcast-tool and bounded-CWD additions were validated at frozen2d8b8d0.
   The later delta-auxiliary, G76 compound reset, VFS allocation, legacy-driver
   and Modbus additions are a separate accumulated checkpoint.

## Native setting reporting guard review — 2026-10-23

On CORE `51b58594ce467e9c4b103fb93d1ca121e43cd15c`, the three missing
`report.c:450-452` lines print `$id=N/A` only when a setting descriptor has a
NULL `value`. All eight native `setting_detail_t` arrays were enumerated:
canbus, ioports, Modbus RTU, asymmetric ganging, delta, RTCP, global settings
and secondary spindle. Their 162 initializer rows all provide a storage address
or function; all 52 distinct function value tokens have definitions in CORE.
This is a source inventory including conditional alternatives, not a claim that
all 162 descriptors coexist in one configuration. No initializer gaps remained.

The global table is installed directly (`settings.c:2750`); additional tables
pass `settings_register`, whose line2759 rejects a NULL value before linking
at2772. Together these account for the native tables and normally registered
providers. They do not prove safety after a provider mutates registered metadata,
or establish a contract for arbitrary unregistered descriptors. No synthetic
NULL descriptor test was added; these three lines remain in the raw denominator.
The audit's earlier conditional flag incorrectly treated `#` inside numeric
format strings as a directive; that flag was corrected before this conclusion.


## Current-source dormant dispatch review

Reviewed CORE51b58594 against the raw table above; these five lines remain in the
denominator. This is native caller evidence, not a claim about arbitrary plugins.

| Current source lines | Count | Native routing evidence |
|---|---:|---|
|modbus.c231-233|3|The high-level command table leaves diagnostics function8 unregistered (`function=0`). rx_packet requires a nonzero registered function before its switch, so its TBA diagnostics case cannot run through that native dispatch. Do not inject private callbacks or pretend the TBA operation is implemented.|
|spindle_control.c499,503|2|The null spindle supplies both get_pwm and update_pwm. Override routing chooses that pair before update_rpm, and stepper segment dispatch likewise prefers update_pwm. The dormant null_update_rpm body only discards arguments and has no output to assert. Do not clear registered pointers solely to call it.|

## Historical CORE50f I/O review

Against historical run39977472030 (CORE50f38659), all28 missing ioports.c lines were accounted below.
These old line numbers are not the current CORE51b inventory.
These classifications do not remove lines from coverage or claim all missing
branch outcomes explained.

| Lines | Count | Evidence and next action |
|---|---:|---|
|1377-1401,1428-1430 (executable subset)|18|Auxiliary open-drain registration is commented out; existing public setting-disabled test passes. Expose the setting upstream before testing its handlers. See [disabled registration audit](TODO.md#disabled-auxiliary-output-open-drain-and-timezone-registrations).|
|1283-1284,1403-1404,1432-1433|6|Private setting callback defaults have no registered setting ID routing to them. Do not invoke private callbacks with invented IDs.|
|1550-1551|2|The preceding control-function range always maps to a nonzero signal bit. See [control mapping proof](TODO.md#assigned-control-zero-mask-fallback-is-unreachable-for-valid-pin-functions---2026-10-23).|
|1187|1|The lower clamp after narrow integer wrap is exercised by the existing 16-bit-fast-integer PWM regression on the Windows host; Linux's wider fast integer does not wrap at that input. Retain the platform-scoped correct assertion and raw Linux gap. See [PWM wrap defect](KNOWN_BUGS.md#large-analog-pwm-request-wraps-to-minimum-duty-with-16-bit-fast-integers).|
|782|1|Unmatched analog-output routing needs a supported provider advertising a port without its generic output callback. No real provider contract established yet; do not fabricate one to clear this guard.|
|**Total**|**28**||

## Source-reviewed residual subset - 2026-10-23

The historical CORE50f report39977472030 had237 of288 raw missing lines reviewed.
This table preserves those source-specific audits; it is not a recount of the
new CORE51b report above. Current lines moved and some reviewed reachable lines
are now covered. Revalidate changed source before treating any old audit as a
current reachability proof. No source exclusions or supported-scope completion
claim follows from this historical subset.

| Source / measured missing lines | Count | Classification and next action |
|---|---:|---|
|Wall-plotter homing helpers|56|Public home_machine still warns and returns false in CORE50f3865. Existing rejection test passes. Await implemented homing/reference contract; do not call its unused helpers for a percentage. See [audit](TODO.md#wall-plotter-homing-coverage-requires-an-implemented-public-workflow).|
|Polar homing hooks212,214,232,234|4|polar_init installs these hooks but replaces home_machine with polar_homing_cycle, which only warns and returns false. Existing public rejection test checks unchanged axes. Await implemented homing; installed callbacks alone do not establish a supported homing workflow.|
|Expression dispatch defaults and bypassed EXISTS arm|11|Unknown operations reject before private enum dispatch; EXISTS has a dedicated reader. See [audit](TODO.md#expression-dispatcher-gaps-that-require-invalid-private-enums).|
|Parameter macro1247|1|Failed read is of constant valid local4; the public getter always succeeds for that writable index. See [audit](TODO.md#built-in-parameter-macro-outer-read-failure-cannot-occur-for-literal-local4---2026-10-23).|
|G-code M6 message release4260|1|Nested check-mode arm is behind an opposite outer guard. See [audit](TODO.md#tool-change-check-mode-message-release-is-behind-an-opposite-guard---2026-10-23).|
|I/O residuals detailed above|28|18 disabled handlers,8 unrouted/impossible guards,1 platform-specific integer-width case and1 unresolved provider contract. Retain the separate classifications in that table.|
|Buffered NVS366,391-392|3|Zero-size driver dirty state requires an unallocated write; warning equality skips5 because the retry counter stays even. See [allocation audit](TODO.md#zero-length-driver-dirty-fallback-requires-unallocated-writes---2026-10-23) and [counter audit](TODO.md#buffered-nvs-warning-equality-is-skipped-by-an-even-retry-counter---2026-10-23). Warning frequency remains a policy question, not a new exception.|
|G-code1357-1358|2|Normal check-mode comment handling allocates no message; the full public dry-run test verifies no callbacks/output/queue. See [audit](TODO.md#parser-check-mode-message-cleanup-is-preempted-by-normal-normalization---2026-10-23).|
|G-code1045|1|The only initialization callers are G33/G33.1/G76, whose earlier validation already requires the encoder getter. See [audit](TODO.md#sync-motion-initialization-encoder-guard-repeats-public-validation---2026-10-23).|
|Settings unused availability handlers|15|Four registered descriptors use NULL availability and timezone is unregistered. MPG baud rate is distinct. See [exact audit](TODO.md#counted-public-settings-guards-and-unused-availability-cases---2026-10-23).|
|Settings repeated capability/build gates|9|Public lookup hides unavailable settings before their setters. Disabled-backlash registration is compiled out; shared/per-axis transitions have a public rejection control. See same audit.|
|Settings PWM bounds and invalid mode default|4|Validated four/five-bit PWM option masks and a three-choice mode descriptor reject invalid values before these private guards. See same audit.|
|Modbus diagnostics231-233|3|TBA command has function0; validation rejects it before response dispatch. See [current audit](TODO.md#counted-protocolbackend-residuals-after-public-sleep-coverage---2026-10-23).|
|VFS415,482|2|Successful rename requires equal mounts; chdir path validation precedes its nonnull mount lookup. VFS272 now has a valid allocation-failure regression;779 retains a separate caller question. Neither is folded into this proof. See same audit.|
|Flow dispatcher811-812|2|Every recognized operation has a case; unknown text rejects earlier. See [command-set audit](TODO.md#flow-dispatcher-default-has-no-recognized-command---2026-10-23).|
|Virtual parameter942|1|Built-in return-value nodes make the root nonempty; public registration appends. See [root audit](TODO.md#verified-residual-guards-vfs-lookuprename-and-virtual-parameter-root).|
|File reader72|1|Normal close restores the parent/serial reader before dropping the file. No supported detached-reader call identified. See [audit](TODO.md#file-reader-no-file-fallback-audit---2026-10-22).|
|System HELP466,468|2|HELP prefix dispatch bypasses this command-table wrapper. Existing public help tests exercise the actual handler; see current audit and TODO.|
|Secondary spindle1160-1161,1172,1215-1216|5|Public capability/value validation precedes setters; both registered getter IDs have cases. Existing public rejection controls verify preserved configuration. See [audit](TODO.md#secondary-pwm-and-parser-repeated-validation-counted-guards---2026-10-23).|
|G-code2888,3055,1489|3|Earlier cutter-plane validation, positive-L word presence and finite-value reading preempt these later guards. See same audit.|
|Settings routed callback defaults|19|Every registered callback ID has a case, except permanently hidden deprecated $7's getter; its legacy store bypass does not call that getter. See [routing/type audit](TODO.md#remaining-settings-defaults-routing-sets-types-and-no-table-stub---2026-10-23).|
|Settings1958-1959,3474-3475|4|Formatted-value and integer-validation switches cover every applicable valid datatype; no malformed metadata tests. See same audit.|
|Settings2024-2025|2|Noninteger direct-value integer reads are possible, but current CORE callers check types/selectors first. A real external mismatch caller remains unestablished, not declared impossible. See same audit.|
|Settings2955,2957|2|No-table success/no-op persistence stub; public G10 tool edits reject earlier. See same audit.|
|Settings3623-3625|3|Direct-buffer IPv4 write representation needs an actual provider/contract; function-provider writes already have tests. Not declared unreachable for every valid enum or a confirmed defect. See same audit.|
|G-code2180 and named parameter772-773|3|Complete accepted letter set and all63 named registry IDs have handlers. See [mapping audit](TODO.md#counted-parser-alphabet-named-ids-and-spindle-broadcast-guards---2026-10-23).|
|G-code override broadcast loops|9|Six M48/M49 lines are reachable through accepted same-block M3M48$-1/M3M49$-1; local runtime cases demonstrate this, including the documented M48 defect. Only three M51 lines remain behind its single-selector requirement. The former standalone-only audit was incorrect for combined commands; see same audit.|
|G-code Normal M6 pause4291-4294|4|Mode0 clears the automatic handler while a real UART retains stream suspension. Full boot/ack/cycle-start case and local profile demonstrate reachability. See [workflow audit](TODO.md#normal-m6-stream-pause-is-a-reachable-no-handler-workflow---2026-10-23).|
|G-code native dispatch defaults2736-2737,3606-3607,4964-4965|6|Every native motion/override enum and all eight parsed canned cycles have handlers; None is excluded by the execution guard. See [mapping audit](TODO.md#native-motion-canned-and-override-dispatch-defaults---2026-10-23).|
|Device closedir190,192 and embedded modification stubs133,135,138,140|6|Device opendir cannot supply a valid handle. Embedded mounts are natively hidden/read-only; changing owner flags could reach fixed rejection stubs but no writable-owner contract is established. See [scope audit](TODO.md#native-backend-stubs-and-startup-residuals-counted---2026-10-23).|
|Scheduler interior removal590-594|5|Due-task selection retains IRQ masking until the head identity check; no supported intervening mutation. See same audit and the earlier atomic-selection proof.|
|Detailed driver diagnostic140,144-147,149-150|7|Failed-startup filtering discards this task; detail-versus-generic policy remains unresolved. Private formatter is not invoked for coverage. See same audit.|
|Weak empty hooks:grbllib92,95/my_plugin26,29|4|Driver-owned initialization is replaced by the host; default hooks have no action to assert. Harness/no-op scope limit, not a claim production cannot call them. See same audit.|
|Device transport default59|1|A real claimable/modbus-ready non-UART provider needs an established naming contract. Serial/Bluetooth controls remain; no fake transport. See same audit.|
|Report450-452 and1955-1956|5|Plugin registration rejects NULL values; no universal native/global-table proof is claimed. Tab formatting handles valid external types. See [caller audit](TODO.md#reporting-and-restore-fallbacks-current-caller-limits---2026-10-23).|
|State157,819 and stream614|3|In-range spindle lookup is nonnull, restore changes handler before setting the flag, and ClearAll returns before report observers. Pending observer-clear policy stays separate; see same audit.|
|**Reviewed subset**|**237**|All remain in the raw denominator; no source exclusions or fabricated scenarios.|


## UTF-8 encoder range guard review - 2026-10-23

Exact CORE `2e165a1ac4c74be8e68971972c6577775d856b05`, verified
run40024613962: utf8.c139 has one missing outcome, the false side of
`length <= 4`. Line121 returns before conversion for every code point above
0x10FFFF. For remaining inputs the loop shifts six bits per continuation
byte: at the maximum, successive first-byte values are 0x43FF, 0x10F and
0x4, with masks 0x1F, 0xF and 0x7. It therefore stops at length4. Smaller
accepted values stop no later; ASCII uses length1. An independent exhaustive
integer check of all 1,114,112 accepted numeric inputs confirmed maximum4.
Existing ASCII, two/three/four-byte boundary and out-of-range cases remain.
No invalid input can reach the missing outcome past the earlier rejection;
no test, source edit or coverage exclusion was added. The raw missing
outcome remains counted, separately explained rather than treated as a
supported workflow gap.


## RAM filesystem residual ownership guards - 2026-10-23

Exact CORE `2e165a1ac4c74be8e68971972c6577775d856b05` and verified
run40024613962 contain no uncovered RAM filesystem lines and eleven missing
branch outcomes. Compared every partial branch in the artifact with the native
allocation, open/close, unlink and VFS wrapper paths:

| Source line | Missing outcomes | Native invariant |
|---|---:|---|
|103|1|New ram_file_t comes from calloc; its txbuf.s is necessarily NULL before initialization.|
|140|2|Open rejects an existing nonzero refs count before incrementing. Close sees refs1 and decrements to0; pathname unlink requires refs0. Neither native caller supplies refs greater than1, so the retained-reference result cannot occur.|
|146|1|Non-head unlink receives a member found in the same live list. Its predecessor is reached before a NULL next link.|
|148|1|The predecessor starts at the nonempty list head and only advances while next is non-NULL.|
|153|1|The unlink result is already true on both native call paths described above.|
|200|1|Every successfully opened file has a non-NULL ram_file_t handle; allocation failure frees the wrapper instead of returning it.|
|229|1|The same successful-open ownership invariant applies to seek.|
|241|1|The same successful-open ownership invariant applies to truncate.|
|268|1|The return's rfile test cannot be false for a valid opened file. Truncate success and length-mismatch failure remain exercised.|
|332|1|VFS closedir dereferences dir before backend dispatch; a valid opened directory is required. Calling this private backend with NULL is not a public workflow.|

Counts sum to eleven, matching the exact artifact. These are bounded native
caller/ownership findings, not proof about forged handles, stale handles after
reset, or unsupported concurrent mutation. No fabricated handles, source edits
or exclusions were introduced. The separately confirmed nonzero-truncate
allocation bug retains its correct regression and narrow allowance; this audit
does not classify its failure as acceptable behavior.

## Required owner save callback - 2026-10-24

On CORE2e165a1, the unobserved false outcome of settings.c3658 follows a required
callback: the native owner initializes save, settings_claim_save ignores NULL,
and settings_register rejects an external owner without save before linking it.
The existing invalid-metadata regression exercises rejection and corrected public
registration/store/query. No invalid post-registration mutation case was added.
See [source evidence](TODO.md#successful-setting-stores-always-have-a-registered-save-callback---2026-10-24).
This branch remains in the raw measured denominator.

## Imperial formatter argument bound - 2026-10-24

CORE2e165a1 report.c103's missing false-position outcome has no native caller:
all nine selector calls pass true. Scaling is the only false-position call and
selects the metric formatter directly. The selector and both formatters are
file-local. Existing public metric/inch diameter reporting remains covered;
no direct private formatter test or exclusion was added. See
[exact call-site audit](TODO.md#imperial-coordinate-formatter-position-flag-has-no-native-false-caller---2026-10-24).

## Fast-cancel preparation guard - 2026-10-24

CORE2e165a1 stepper.c1093 is behind a native ordering contradiction: its only true
flag writer leaves the planner block pointer NULL; the next preparation pass
returns before the check or reloads the block and clears the flag first. Native
IRQ step output does not reenter preparation. Existing public jog cancellation
and hold/resume checks remain; no flag injection or exclusion was added. See
[exact ordering audit](TODO.md#fast-cancel-segment-guard-is-cleared-before-its-native-check---2026-10-24).

## Native macro read and response guards - 2026-10-24

On CORE2e165a1, constant local reads in the native setting/parameter/probe/tool/
Modbus macros use IDs1..30. The public getter returns true for that writable
range even when unset, without allocation. Missing argument flags and the
remaining setting/selector/write/transport conditions are separate reachable
paths. Two Modbus _value2/_value3 exception ternaries additionally sit inside
an exception-free guard, so their opposite outcomes have no ordinary native
execution. See [exact calls and limits](TODO.md#native-macro-literal-reads-and-dominated-response-ternaries---2026-10-24).
No test or source exclusion was added; all outcomes remain in raw coverage.


### Homing scope and VFS allocation follow-up - 2026-10-24

User explicitly keeps all wall-plotter and polar homing on TODO, including manual
$H. Those 60 missing lines remain in the raw denominator without a supported
homing claim. VFS272 has a demonstrated valid allocation-failure trigger through
`vfs_utime`: its errno assertion is a confirmed narrow regression. This is
unmeasured local work; VFS779 remains a separate caller-contract question.


### Remaining string-helper outcomes - 2026-10-24

The exact hosted HTML identifies two ordinary missing outcomes: extracting entry0
from a delimited axis list (strutils169), and completing a case-insensitive
placeholder match before the source ends with remaining comparison budget
(strutils102). Existing readable helper cases now cover these with exact returned
pointers and strings; no new fixture or case count. Cumulative measurement is
pending. UTF8's length>4 arm remains dominated by the code-point <=0x10FFFF guard:
ASCII uses1 byte and the six-bit reduction needs at most4 for this bound. No
invalid-code-point bypass or source exclusion is warranted.

The external provider survey found40 active callback-based IPv4 descriptors in10
source files. Pinned per-file sources and blob IDs are recorded in TODO. This is
a bounded absence finding for direct-buffer providers, not universal proof.


## Exact remaining branch locations - 2026-10-24

[Branch inventory](COVERAGE_BRANCH_INVENTORY.csv) records every incomplete
branch site from verified40074304720 with its source expression and raw outcome
counts. Missing counts sum to1,097, matching XML. Untaken IDs come from the HTML
where emitted; zero-hit sites omit branch IDs in HTML and are marked explicitly.
IDs belong to this pinned report/toolchain, not portable true/false labels.

Most entries remain branch-review-pending. A linked uncovered-line disposition
is context only, not proof about all missing branch outcomes. Three previously
reviewed native bounds, two locally extended helper sites and two compiler-
mapping questions have narrower statuses. No denominator changes or automatic unreachable classifications.
Use this finite list with existing cases and caller contracts before authoring.

The first ranked review caught an important duplication risk: G-code4764/4780
show7/10 outcomes each, while existing root G66 and nested G65 linear/rapid
controls already cover normal invocation and scope mismatch. Those six missing
reported outcomes require generated-mapping review before any additional G66
case. They are not classified unreachable or solved by more argument variants.


### G66 mapping evidence retained for the next batch report

At4764 and4780, hosted40074304720 HTML lists branch3/4/5 as both taken and
untaken, and branch6 more than once. Branch numbers alone are not unique keys
for these aggregated sites. Existing root and nested-scope controls therefore
do not establish that every reported branch record is covered, nor do the
missing records prove an untested G66 behavior.

The normal gcovr8.4 reporting invocation now also emits coverage.json and HTML
block IDs. Existing coverage* artifact collection retains both, without another
run or changes to filters, merge mode, instrumentation or denominator policy.
The JSON includes function names and branch source_block_id metadata, which
the current XML/HTML-only artifact lacks. Use those keys before choosing more
G66 cases. References: [8.4 JSON schema](https://gcovr.com/en/8.4/output/json.html)
and [HTML block IDs](https://gcovr.com/en/8.4/manpage.html#cmdoption-html-block-ids).

Historical inventory caveat (CORE2e snapshot): branch IDs were raw HTML labels
and could repeat. The current b01 CSV now uses function@source_block:branch
keys from JSON and contains1,078 missing outcomes. Neither keys nor counts
prove that every missing outcome has a supported trigger.


### Supported legacy-driver registration refusal - 2026-10-24

The existing reverse-compatibility test rejects old-style registration after a
modern bank takes ownership. The new complementary driver-startup scenario
registers legacy IO first, attempts modern digital/analog plugin banks, and
requires rejection with unchanged working driver callbacks, pin metadata and
port counts. Follow-up read/write operations verify observable recovery. This
reaches the claim_hal=false short-circuit at1071/1107 without changing private
state. Focused ASan/UBSan passes; coverage gain remains unmeasured and does not
resolve every reported branch record at these two locations.


### Upstream-supported tapping handoff - 2026-10-24

On b01, the native tapping stub returns Unhandled and the parser intentionally
invokes macro331. The new eight-axis case verifies public A/I/K/Z transfer,
line/repeat identity, caller scope restoration and override cleanup using a
registered running spindle. No replacement native tapping function or new host
variant was introduced. This supersedes the earlier implementation-contract
blocker for the A-argument path (source2e line4866). The raw inventory remains
the old measured source snapshot; new-source line gain awaits measurement.


### Native tapping stack rejection now has a public trigger

On b01, recursive macro331 -> G33.1 calls reach the normal tapping scope limit.
The new spindle-sync case requires StackOverflow, intact caller scope/overrides,
no motion during recursion, and a successful80-pulse G33 cut afterwards. It uses
public parser callbacks and the existing registered encoder driver; no private
stack setup. The earlier defect-dependent classification of source2e4864 is
superseded for b01 by this tested native trigger. Gain remains unmeasured.


### Persistent file EOF wrapper after a redirected job

An ordinary file provider can start a plain RAM job after a redirected macro
finishes. The new protocol scenario uses real VFS handles and public stream
selection, verifies both owner completions and sender query recovery, and
provides a supported empty-redirect-stack trigger for stream_file94. Existing
no-file private-reader55/73 proof is separate and unchanged. Local sanitizer
validation passes; branch gain awaits the next accumulated measurement.


### Extension-enabled modal macro workflow - 2026-10-24

The cutter-compensation configuration has now been exercised with a public
motion-extension filter and G66. Refused feed/rapid commands produce no pulses
or invocation; normal parser-error cleanup cancels G66 and explicit public
rearming permits retry. Accepted moves queue through the extension and invoke
the callback with correct target, arguments and scope. Physical endpoints are
checked after synchronization; the callback is a parser loader, so no artificial
physical-completion-before-callback contract is asserted. G67 cancels subsequent
invocations. Focused sanitizer evidence is recorded in PROGRESS. Contribution
to the duplicate branch records at current gcode4762/4778 awaits cumulative
coverage measurement; no complete mapping or percentage gain is claimed.


### Forced list-pointer assignment outcomes - 2026-10-24

On COREb01f481, four missing outcomes in run40082861198 follow a nonnull
short-circuit guard of the very pointer subsequently assigned. stream_file96,
124 and164 each miss function-specific block2/branch3; spindle_control594
misses _get_ramp block3/branch5. There is no intervening function call between
the pointer test and assignment. Native sequential ownership cannot make the
assignment false. Existing traversals cover empty/nonempty and interior list
movement; private concurrent list corruption is not a supported workflow.
The CSV records these exact four outcomes as forced-pointer-assignment, with
all outcomes retained in raw coverage. This proves only these operands, not
that all branches in those modules or all provider interactions are covered.

The remaining nvs_buffer162 source-pointer comparison is separate: copying
increments source before comparing it with driver_area.mem_address. The public
field documents where RAM resides, but that alone does not establish an
in-place write/save contract. Locate an actual owner or obtain a maintainer
contract before introducing a mirror mutation test or classifying a defect.
