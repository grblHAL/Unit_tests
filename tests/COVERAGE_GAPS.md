# Remaining raw CORE coverage

Measured report: [run39945588754](https://github.com/petervanderwalt/Unit_tests/actions/runs/39945588754),
harness `947fa2ef7c3277dea262d59d38361b88f16ce78f`, CORE
`50f38659db7b22f4689f3654df2d110d992bcc95`, filter `core/.*\.[ch]$`.
Coverage job passed with matching source locks and all seven stages successful.
The overall hosted run subsequently completed successfully; all five jobs,
including GCC and Clang, were verified before refreshing the badges.

17,411/17,714 lines and12,365/13,800 branch outcomes were covered. The table
accounts for all303uncovered executable lines and1,435uncovered branch outcomes.
A branch outcome can be missing on an otherwise covered line; `none` therefore
does not mean full coverage. Counts include compiler-emitted conditions.

This is an inventory, not a claim that remaining code is unreachable. Use
[TODO](TODO.md) for source/contract audits and [KNOWN_BUGS](KNOWN_BUGS.md) for
correct regression assertions and exact failure allowances. Do not remove source
from the denominator, inject private state, or add duplicate tests to clear rows.
Check those notes and existing cases before authoring a public workflow.

Local unmeasured work adds pending-alarm sleep cancellation, a documented
nonzero MINIMUM_JUNCTION_SPEED configuration, toolsetter-first primary-probe
registration and removes a duplicate tool-table
rejection case. The stronger existing dynamic-offset
rejection remains. Both tool-table late guards remain uncovered because their
early parser capability checks reject first; see [the audit](TODO.md#tool-table-absence-guards-implied-by-earlier-parsing).
Do not attribute local changes to this measured head.

| Source | Uncovered lines | Missing branch outcomes | Exact executable line numbers |
|---|---:|---:|---|
| [core/crossbar.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/crossbar.c) | 0 | 1 | none |
| [core/crossbar.h](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/crossbar.h) | 0 | 3 | none |
| [core/fs_device.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/fs_device.c) | 3 | 7 | 59, 190, 192 |
| [core/fs_embedded.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/fs_embedded.c) | 4 | 4 | 133, 135, 138, 140 |
| [core/fs_ram.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/fs_ram.c) | 0 | 12 | none |
| [core/gcode.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/gcode.c) | 46 | 234 | 134-135, 325-326, 573, 1045, 1293-1294, 1357-1358, 1489, 2180, 2689, 2691-2692, 2702, 2704-2705, 2718, 2720-2721, 2736-2737, 2888, 2977, 2989, 3055, 3472-3474, 3606-3607, 3919, 4260, 4291-4294, 4849-4850, 4852, 4854, 4856-4857, 4964-4965 |
| [core/grbllib.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/grbllib.c) | 14 | 37 | 92, 95, 140, 144-147, 149-150, 590-594 |
| [core/ioports.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/ioports.c) | 30 | 149 | 782, 1187, 1283-1284, 1377, 1379, 1381, 1383, 1386-1390, 1393-1394, 1396, 1398-1399, 1401, 1403-1404, 1428-1430, 1432-1433, 1550-1551, 1566-1567 |
| [core/kinematics/asymmetric_ganging.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/kinematics/asymmetric_ganging.c) | 1 | 4 | 254 |
| [core/kinematics/delta.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/kinematics/delta.c) | 11 | 48 | 173, 287-288, 343, 586-587, 592, 599, 610, 653, 673 |
| [core/kinematics/polar.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/kinematics/polar.c) | 4 | 3 | 212, 214, 232, 234 |
| [core/kinematics/rtcp_ac.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/kinematics/rtcp_ac.c) | 0 | 3 | none |
| [core/kinematics/wall_plotter.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/kinematics/wall_plotter.c) | 56 | 28 | 208, 213-214, 216-227, 229, 234, 237, 239-240, 242-255, 257, 260, 262, 264-280, 283-284 |
| [core/machine_limits.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/machine_limits.c) | 2 | 21 | 269, 502 |
| [core/modbus.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/modbus.c) | 3 | 6 | 231-233 |
| [core/modbus_rtu.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/modbus_rtu.c) | 3 | 41 | 241, 359-360 |
| [core/motion_control.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/motion_control.c) | 6 | 33 | 690, 715, 718, 772, 779, 1122 |
| [core/my_plugin.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/my_plugin.c) | 2 | 0 | 26, 29 |
| [core/ngc_expr.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/ngc_expr.c) | 11 | 13 | 115-116, 189-190, 250, 252, 292-293, 337-338, 341 |
| [core/ngc_flowctrl.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/ngc_flowctrl.c) | 2 | 59 | 811-812 |
| [core/ngc_params.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/ngc_params.c) | 4 | 65 | 772-773, 942, 1247 |
| [core/nuts_bolts.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/nuts_bolts.c) | 0 | 16 | none |
| [core/nvs_buffer.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/nvs_buffer.c) | 3 | 11 | 366, 391-392 |
| [core/planner.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/planner.c) | 0 | 2 | none |
| [core/probe.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/probe.c) | 0 | 4 | none |
| [core/protocol.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/protocol.c) | 2 | 53 | 185, 354 |
| [core/regex.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/regex.c) | 0 | 1 | none |
| [core/report.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/report.c) | 5 | 102 | 450-452, 1955-1956 |
| [core/settings.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/settings.c) | 58 | 137 | 701, 703, 780-781, 839, 925, 928, 1012, 1056, 1140-1141, 1198-1199, 1340, 1350, 1506-1507, 1568, 1576, 1583, 1590, 1593-1595, 1651-1652, 1692-1693, 1899-1900, 1958-1959, 2024-2025, 2173-2175, 2177-2179, 2190-2192, 2194-2196, 2237-2239, 2245-2246, 2955, 2957, 3474-3475, 3623-3625 |
| [core/sleep.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/sleep.c) | 0 | 4 | none |
| [core/spindle_control.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/spindle_control.c) | 8 | 49 | 499, 503, 636, 1160-1161, 1172, 1215-1216 |
| [core/state_machine.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/state_machine.c) | 12 | 44 | 157, 449, 502, 524-527, 614-615, 658-659, 819 |
| [core/stepper.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/stepper.c) | 1 | 14 | 1093 |
| [core/stepper2.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/stepper2.c) | 0 | 17 | none |
| [core/stream.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/stream.c) | 3 | 47 | 275, 368, 614 |
| [core/stream_file.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/stream_file.c) | 1 | 10 | 72 |
| [core/stream_passthru.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/stream_passthru.c) | 0 | 3 | none |
| [core/strutils.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/strutils.c) | 0 | 17 | none |
| [core/system.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/system.c) | 2 | 42 | 466, 468 |
| [core/tool_change.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/tool_change.c) | 2 | 46 | 435-436 |
| [core/utf8.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/utf8.c) | 0 | 1 | none |
| [core/vfs.c](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/vfs.c) | 4 | 44 | 272, 415, 482, 779 |
| **Total** | **303** | **1435** | |
