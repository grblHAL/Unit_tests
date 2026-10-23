# Remaining raw CORE coverage

Measured report: [run39969171772](https://github.com/petervanderwalt/Unit_tests/actions/runs/39969171772),
harness `b2cf02dc30af60c9358b7a0015e081d0230f5f54`, CORE
`50f38659db7b22f4689f3654df2d110d992bcc95`, filter `core/.*\.[ch]$`.
Coverage job passed with matching source locks and all seven stages successful.
All five hosted jobs completed successfully, including GCC, Clang and CI
diagnosis. Whole-run terminal success was verified before refreshing badges.

17,419/17,714 lines and12,457/13,800 branch outcomes were covered. The table
accounts for all295uncovered executable lines and1,343uncovered branch outcomes.
A branch outcome can be missing on an otherwise covered line; `none` therefore
does not mean full coverage. Counts include compiler-emitted conditions.

This is an inventory, not a claim that remaining code is unreachable. Use
[TODO](TODO.md) for source/contract audits and [KNOWN_BUGS](KNOWN_BUGS.md) for
correct regression assertions and exact failure allowances. Do not remove source
from the denominator, inject private state, or add duplicate tests to clear rows.
Check those notes and existing cases before authoring a public workflow.

The measured eight-workflow batch gained16 branch outcomes and no lines relative
to39961338202; no prior covered line was lost. The held G76 reset/approach E-stop, stopped-spindle G33.1 regression, real-homed fine-resolution
delta jog and two automatic-sleep boot workflows are
local after this head and unmeasured. The sleep cases target protocol354 via
public $62 stores and real idle polling, including new-input cancellation.
G33.1 initialization failure reaches its macro continuation despite the weak
native implementation being unavailable; see the dated KNOWN_BUGS entry. Local targeted
Windows profiles confirm protocol354, gcode4849/4854/4856/4857, delta653 and motion_control718 execute. This
is positive line evidence only, not an updated global percentage; hosted Linux
measurement for this checkpoint is pending. The held reset adds no raw line in
that profile check. Source audits below retain unsupported
and unreachable code in the raw denominator.

| Source | Uncovered lines | Missing branch outcomes | Exact executable line numbers |
|---|---:|---:|---|
| [core/crossbar.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/crossbar.c) | 0 | 1 | none |
| [core/crossbar.h](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/crossbar.h) | 0 | 3 | none |
| [core/fs_device.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/fs_device.c) | 3 | 7 | 59, 190, 192 |
| [core/fs_embedded.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/fs_embedded.c) | 4 | 4 | 133, 135, 138, 140 |
| [core/fs_ram.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/fs_ram.c) | 0 | 11 | none |
| [core/gcode.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/gcode.c) | 42 | 223 | 325-326, 573, 1045, 1357-1358, 1489, 2180, 2689, 2691-2692, 2702, 2704-2705, 2718, 2720-2721, 2736-2737, 2888, 2977, 2989, 3055, 3472-3474, 3606-3607, 3919, 4260, 4291-4294, 4849-4850, 4852, 4854, 4856-4857, 4964-4965 |
| [core/grbllib.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/grbllib.c) | 14 | 37 | 92, 95, 140, 144-147, 149-150, 590-594 |
| [core/ioports.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/ioports.c) | 28 | 145 | 782, 1187, 1283-1284, 1377, 1379, 1381, 1383, 1386-1390, 1393-1394, 1396, 1398-1399, 1401, 1403-1404, 1428-1430, 1432-1433, 1550-1551 |
| [core/kinematics/asymmetric_ganging.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/kinematics/asymmetric_ganging.c) | 1 | 4 | 254 |
| [core/kinematics/delta.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/kinematics/delta.c) | 11 | 48 | 173, 287-288, 343, 586-587, 592, 599, 610, 653, 673 |
| [core/kinematics/polar.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/kinematics/polar.c) | 4 | 3 | 212, 214, 232, 234 |
| [core/kinematics/rtcp_ac.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/kinematics/rtcp_ac.c) | 0 | 3 | none |
| [core/kinematics/wall_plotter.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/kinematics/wall_plotter.c) | 56 | 28 | 208, 213-214, 216-227, 229, 234, 237, 239-240, 242-255, 257, 260, 262, 264-280, 283-284 |
| [core/machine_limits.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/machine_limits.c) | 2 | 21 | 269, 502 |
| [core/modbus.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/modbus.c) | 3 | 6 | 231-233 |
| [core/modbus_rtu.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/modbus_rtu.c) | 3 | 41 | 241, 359-360 |
| [core/motion_control.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/motion_control.c) | 4 | 31 | 690, 715, 718, 1122 |
| [core/my_plugin.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/my_plugin.c) | 2 | 0 | 26, 29 |
| [core/ngc_expr.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/ngc_expr.c) | 11 | 13 | 115-116, 189-190, 250, 252, 292-293, 337-338, 341 |
| [core/ngc_flowctrl.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/ngc_flowctrl.c) | 2 | 59 | 811-812 |
| [core/ngc_params.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/ngc_params.c) | 4 | 65 | 772-773, 942, 1247 |
| [core/nuts_bolts.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/nuts_bolts.c) | 0 | 3 | none |
| [core/nvs_buffer.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/nvs_buffer.c) | 3 | 11 | 366, 391-392 |
| [core/planner.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/planner.c) | 0 | 1 | none |
| [core/probe.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/probe.c) | 0 | 2 | none |
| [core/protocol.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/protocol.c) | 2 | 46 | 185, 354 |
| [core/regex.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/regex.c) | 0 | 1 | none |
| [core/report.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/report.c) | 5 | 82 | 450-452, 1955-1956 |
| [core/settings.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/settings.c) | 58 | 130 | 701, 703, 780-781, 839, 925, 928, 1012, 1056, 1140-1141, 1198-1199, 1340, 1350, 1506-1507, 1568, 1576, 1583, 1590, 1593-1595, 1651-1652, 1692-1693, 1899-1900, 1958-1959, 2024-2025, 2173-2175, 2177-2179, 2190-2192, 2194-2196, 2237-2239, 2245-2246, 2955, 2957, 3474-3475, 3623-3625 |
| [core/sleep.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/sleep.c) | 0 | 3 | none |
| [core/spindle_control.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/spindle_control.c) | 8 | 43 | 499, 503, 636, 1160-1161, 1172, 1215-1216 |
| [core/state_machine.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/state_machine.c) | 12 | 44 | 157, 449, 502, 524-527, 614-615, 658-659, 819 |
| [core/stepper.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/stepper.c) | 1 | 14 | 1093 |
| [core/stepper2.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/stepper2.c) | 0 | 12 | none |
| [core/stream.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/stream.c) | 3 | 47 | 275, 368, 614 |
| [core/stream_file.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/stream_file.c) | 1 | 9 | 72 |
| [core/strutils.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/strutils.c) | 0 | 15 | none |
| [core/system.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/system.c) | 2 | 36 | 466, 468 |
| [core/tool_change.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/tool_change.c) | 2 | 46 | 435-436 |
| [core/utf8.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/utf8.c) | 0 | 1 | none |
| [core/vfs.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/vfs.c) | 4 | 44 | 272, 415, 482, 779 |
| **Total** | **295** | **1343** | |

## Reviewed I/O residual lines

Against this exact report, all28 missing ioports.c lines are accounted below.
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

This subset accounts for154 of the295 raw missing lines in the measured report
above. Counts are checked against that XML, not estimated from source ranges.
It does not classify the remaining141 lines or prove supported-scope completion.
The local held-thread reset case targets another ordinary cancellation path;
its gain requires a later hosted report.

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
|**Reviewed subset**|**154**|All remain in the raw denominator; no source exclusions or fabricated scenarios.|
