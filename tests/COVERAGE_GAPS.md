# Remaining raw CORE coverage

Measured coverage: [run40036375055](https://github.com/petervanderwalt/Unit_tests/actions/runs/40036375055),
harness `a432e12e868638392a3dac6961e5be559538f093`, CORE `2e165a1ac4c74be8e68971972c6577775d856b05`,
filter `core/.*\.[ch]$`. Both artifact locks match and exactly seven coverage
stages exit0. Source, Clang and coverage jobs passed. GCC tests passed but
classification failed on its unsigned-long diagnostic spelling; the exact matcher
repair is local. This measurement is not an all-jobs success claim.

17,480/17,756 lines (**98.45%**) and12,586/13,834 branch outcomes (**90.98%**)
were covered:276 raw missing lines and1,248 missing outcomes. Coverage job:
4,367 cases,4,352 clean/15 known/0 failed/skipped. Against same-source40034582551:
seven additional branch outcomes, unchanged line coverage and no lost lines.

Success badges remain pinned to fully green40034582551 (98.45%/90.93%). Local
NVS allocation/reuse and probe IRQ-disable recovery extensions are not included.

Raw coverage does not establish correctness or reachability. See [TODO](TODO.md)
and [KNOWN_BUGS](KNOWN_BUGS.md) before selecting workflows. Historical audits
remain pinned to their stated revisions; no source exclusions were added.

| Source | Uncovered lines | Missing branch outcomes | Exact executable line numbers |
|---|---:|---:|---|
| [core/crossbar.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/crossbar.c) | 0 | 1 | none |
| [core/crossbar.h](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/crossbar.h) | 0 | 3 | none |
| [core/fs_device.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/fs_device.c) | 3 | 3 | 59, 190, 192 |
| [core/fs_embedded.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/fs_embedded.c) | 4 | 5 | 133, 135, 138, 140 |
| [core/fs_ram.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/fs_ram.c) | 0 | 11 | none |
| [core/gcode.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/gcode.c) | 29 | 214 | 325-326, 573, 1043, 1367-1368, 1499, 2190, 2728, 2730-2731, 2746-2747, 2898, 2987, 2999, 3065, 3482-3484, 3616-3617, 3929, 4314-4315, 4864, 4866, 4978-4979 |
| [core/grbllib.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/grbllib.c) | 14 | 37 | 92, 95, 140, 144-147, 149-150, 590-594 |
| [core/ioports.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/ioports.c) | 28 | 145 | 782, 1195, 1291-1292, 1385, 1387, 1389, 1391, 1394-1398, 1401-1402, 1404, 1406-1407, 1409, 1411-1412, 1436-1438, 1440-1441, 1558-1559 |
| [core/kinematics/asymmetric_ganging.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/kinematics/asymmetric_ganging.c) | 1 | 4 | 254 |
| [core/kinematics/delta.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/kinematics/delta.c) | 9 | 46 | 180, 320-321, 376, 619-620, 625, 643, 706 |
| [core/kinematics/polar.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/kinematics/polar.c) | 4 | 3 | 212, 214, 232, 234 |
| [core/kinematics/rtcp_ac.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/kinematics/rtcp_ac.c) | 0 | 3 | none |
| [core/kinematics/wall_plotter.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/kinematics/wall_plotter.c) | 56 | 28 | 208, 213-214, 216-227, 229, 234, 237, 239-240, 242-255, 257, 260, 262, 264-280, 283-284 |
| [core/machine_limits.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/machine_limits.c) | 2 | 17 | 269, 502 |
| [core/modbus.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/modbus.c) | 3 | 4 | 231-233 |
| [core/modbus_rtu.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/modbus_rtu.c) | 3 | 36 | 241, 360-361 |
| [core/motion_control.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/motion_control.c) | 2 | 28 | 690, 715 |
| [core/my_plugin.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/my_plugin.c) | 2 | 0 | 26, 29 |
| [core/ngc_expr.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/ngc_expr.c) | 11 | 13 | 115-116, 189-190, 250, 252, 292-293, 337-338, 341 |
| [core/ngc_flowctrl.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/ngc_flowctrl.c) | 2 | 60 | 816-817 |
| [core/ngc_params.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/ngc_params.c) | 4 | 44 | 772-773, 942, 1247 |
| [core/nuts_bolts.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/nuts_bolts.c) | 0 | 1 | none |
| [core/nvs_buffer.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/nvs_buffer.c) | 3 | 9 | 366, 391-392 |
| [core/planner.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/planner.c) | 0 | 1 | none |
| [core/probe.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/probe.c) | 0 | 2 | none |
| [core/protocol.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/protocol.c) | 1 | 45 | 185 |
| [core/regex.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/regex.c) | 0 | 0 | none |
| [core/report.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/report.c) | 5 | 76 | 450-452, 1955-1956 |
| [core/settings.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/settings.c) | 58 | 128 | 701, 703, 780-781, 839, 925, 928, 1012, 1056, 1140-1141, 1199-1200, 1341, 1351, 1507-1508, 1569, 1577, 1584, 1591, 1594-1596, 1652-1653, 1693-1694, 1901-1902, 1960-1961, 2026-2027, 2175-2177, 2179-2181, 2192-2194, 2196-2198, 2239-2241, 2247-2248, 2957, 2959, 3476-3477, 3625-3627 |
| [core/sleep.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/sleep.c) | 0 | 2 | none |
| [core/spindle_control.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/spindle_control.c) | 7 | 40 | 499, 503, 1160-1161, 1172, 1215-1216 |
| [core/state_machine.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/state_machine.c) | 12 | 44 | 157, 449, 502, 524-527, 614-615, 658-659, 819 |
| [core/stepper.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/stepper.c) | 1 | 13 | 1093 |
| [core/stepper2.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/stepper2.c) | 0 | 11 | none |
| [core/stream.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/stream.c) | 3 | 37 | 277, 370, 615 |
| [core/stream_file.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/stream_file.c) | 1 | 9 | 73 |
| [core/strutils.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/strutils.c) | 0 | 5 | none |
| [core/system.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/system.c) | 2 | 35 | 466, 468 |
| [core/tool_change.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/tool_change.c) | 2 | 46 | 435-436 |
| [core/utf8.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/utf8.c) | 0 | 1 | none |
| [core/vfs.c](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/vfs.c) | 4 | 38 | 272, 415, 482, 779 |

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
|VFS415,482|2|Successful rename requires equal mounts; chdir path validation precedes its nonnull mount lookup. NULL-path guards272/779 remain unclassified, not folded into this proof. See same audit.|
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
