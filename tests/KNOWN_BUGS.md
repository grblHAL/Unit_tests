# Confirmed core defects

When updating the tested core, run the regressions before removing exceptions.
For a fixed defect, keep its regression test and remove its CMake `WILL_FAIL` and
`known_bug` properties so it becomes an ordinary passing test. Record the fix date
and core revision in the cleanup commit message, then delete the resolved defect
section from this file. Each entry below links to its test and exception.
All expected-failure blocks live in [known_bugs.cmake](known_bugs.cmake), so
adding host configurations does not move the linked exceptions.
For memory defects, also replace the diagnostic-wrapper registration with a direct
executable test; the fixed test must pass under sanitizers. For feature compile
defects, remove the diagnostic matcher and retain an ordinary successful compile
check. Recovering sanitizer diagnostics have a separate, narrowly scoped
[manifest](known_sanitizer_diagnostics.json); remove its linked entries when fixed.

Source links point to the revision where each defect was verified. CI can test
a newer revision; a fixed regression forces review and cleanup of its exception.

## datetime century leap

**Marked known:** 2026-10-08

**Regression:** [test](cases/nuts_bolts/datetime_century_leap.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L5).

Year 2000 is a Gregorian leap year, but the date parser rejects February 29.

`nuts_bolts.datetime_century_leap` is a labelled expected failure, with the same
removal policy described above.

## VFS close use-after-free

**Reconfirmed:** 2026-10-13, core `4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa`.
The attempted fix saves the update flag, but [vfs.c:369](https://github.com/terjeio/grblHAL_core/blob/4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa/vfs.c#L369)
still reads `file->fs` after `fclose()` frees the handle. ASan reproduces the
same heap use-after-free. The matcher includes this verified new line.

**Marked known:** 2026-10-08

**Regression:** [test](cases/fs_ram/close_lifetime.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L9).

`vfs_close()` calls the backend close at `core/vfs.c:365`, which frees the file
handle (`core/fs_ram.c:174`). It then reads `file->status.update` at `vfs.c:367`.
Confirmed by native Clang AddressSanitizer with `fs_ram.close_lifetime`.

**Additional reproduction confirmed:** 2026-10-10. Embedded-file close also frees
the handle at `core/fs_embedded.c:86`. [Named macro return](cases/ngc_flowctrl/named_macro_return_closes_file_and_restores_caller_scope.c)
reproduces this on Clang; GCC instead reaches the separately documented freed
subroutine callback at `ngc_flowctrl.c:316`. Its strict
[named-macro matcher](../scripts/named_macro_cleanup_regression.py) accepts only
those two exact lifetime defects on this cleanup path.
Remove its additional exception in `known_bugs.cmake` and replace the wrapper
registration in `CMakeLists.txt` with a direct test when both defects are fixed.

The ordinary passing [call/EOF cleanup](cases/ngc_flowctrl/named_macro_call_opens_file_and_sets_local_arguments.c)
and [EOF restoration](cases/ngc_flowctrl/named_macro_eof_restores_caller_stream_and_parameter_scope.c)
tests use a static file backend to verify stream and parameter restoration
independently of the defects caused by freeing file or subroutine records.

## Embedded filesystem seek

**Marked known:** 2026-10-08; memory failure reconfirmed 2026-10-13.

**Regression:** [seek within a file](cases/fs_embedded/seek_within_file.c).
The same fault blocks [embedded named-macro return](cases/ngc_flowctrl/named_macro_return_closes_file_and_restores_caller_scope.c).

At [fs_embedded.c:122](https://github.com/terjeio/grblHAL_core/blob/4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa/fs_embedded.c#L122),
`fs_seek()` casts `file->handle` to an embedded handle instead of using
`&file->handle`, as the other backend operations do. Seeking to byte two of a
five-byte file reports an ASan global buffer overread instead of returning `llo`.
The attempted seek fix therefore still needs correction.

**Remove exception when fixed:** remove this test's block in
[known_bugs.cmake](known_bugs.cmake), replace its special CMake command with a
normal executable test, and delete [embedded_seek_regression.py](../scripts/embedded_seek_regression.py).
Also remove the `seek_defect` branch in [named_macro_cleanup_regression.py](../scripts/named_macro_cleanup_regression.py),
then rerun macro cleanup to determine whether its separate lifetime exception is still needed.
Both wrappers accept only the verified global overread at line 122 with an eight-byte read;
other faults fail the run. The correct seek and macro assertions remain intact.

## Delta travel check accepts an unreachable Cartesian target

**Marked known:** 2026-10-09

**Regression:** [test](cases/delta/unreachable_cartesian_target_rejected.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L17).

With the default delta geometry and all axes homed, the Cartesian target
`X1000 Y1000 Z-300` is physically unreachable, yet `grbl.check_travel_limits()`
returns true. `core/kinematics/delta.c:603` tests successful inverse kinematics
as an error, while a failed inverse can leave zero joint angles that pass the
following range checks. Reject inverse-kinematics failure before checking the
joint-angle bounds. The regression retains the correct rejection expectation.

## RTCP rotary segmentation overshoots the endpoint

**Marked known:** 2026-10-09

**Regression:** [test](cases/rtcp_ac/rotary_segment_endpoint.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L21).

With both rotary centers at zero, an RTCP move from the origin to `X10 C90`
should finish at machine position `X0 Y10 C90`. The segmented move finishes
at `X-20 Y0 C180` instead. `core/kinematics/rtcp_ac.c:348` replaces the starting
RTCP position with the endpoint before interpolation at lines 373-377 adds the
move delta. Preserve the original starting position throughout segmentation.
The regression retains the correct machine endpoint and rotary angle.

## Analog output commands truncate fractional values

**Marked known:** 2026-10-09

**Regression:** [test](cases/gcode/m68_preserves_fractional_output.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L25).

`M68E1Q1.25` passes 1.0 to the analog output callback instead of 1.25.
The callback accepts a float (`core/ioports.h:49`), but `output_command_t.value`
is an `int32_t` (`core/gcode.h:312`). Assigning Q at `core/gcode.c:2604`
truncates fractional values before immediate output at line 4201 or synchronized
M67 output in `core/stepper.c:515`. Preserve the numeric value through command
storage. The regression retains the fractional output expectation.

## Three-register Modbus macro reply loses its second value

**Marked known:** 2026-10-09

**Regression:** [test](cases/ngc_params/builtin_modbus_macro_preserves_three_register_results.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L37).

A `G65P7` read requesting three registers reports `_value_returned=3`, but
returns only the first and third register values. For a reply containing
17, 34, and 51, the expected results are `_value=17`, `_value2=34`, and
`_value3=51`. Instead, `_value2` becomes 51 and `_value3` is not created.

**Reconfirmed:** 2026-10-13 against Terje's latest revision
`4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa`.

The [handler starts at line 1266](https://github.com/terjeio/grblHAL_core/blob/4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa/ngc_params.c#L1266).
[Lines 1271-1274](https://github.com/terjeio/grblHAL_core/blob/4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa/ngc_params.c#L1271)
now correctly copy the second register when more than one value is present,
but the three-value branch still writes the third register to `_value2`.
It overwrites 34 with 51 and never creates `_value3`. That branch needs to
write `_value3` instead. The regression passes a packet through the real
Modbus reply parser and retains all three correct expected values.
The direct executable still fails with `observed second result=51, expected=34`;
CTest's green `known_bug` result confirms reproduction, not a successful fix.

## Named macro cleanup reads a freed subroutine callback

**Marked known:** 2026-10-10

A named macro's `RETURN`, `ENDSUB`, or error cleanup calls `clear_subs()` at
`core/ngc_flowctrl.c:311`, freeing its record at line 259. `stack_unwind_sub()`
then reads `stack[stack_idx].sub->callback` from that freed record at line 316.
AddressSanitizer confirms an eight-byte heap-use-after-free even when the callback
is null. The static-file backend keeps its file handle alive, independently
isolating this defect from the known VFS close use-after-free.

**Regressions:** [RETURN](cases/ngc_flowctrl/named_macro_return_preserves_subroutine_callback_lifetime.c),
[ENDSUB](cases/ngc_flowctrl/named_macro_end_sub_preserves_subroutine_callback_lifetime.c),
and [error cleanup](cases/ngc_flowctrl/named_macro_error_preserves_subroutine_callback_lifetime.c).

**Remove exceptions when fixed:** [CMake registrations](known_bugs.cmake#L53).
Also replace their `named_sub_lifetime_regression.py` registrations in
`CMakeLists.txt` with direct executable tests. The matcher requires the exact
callback read at line 316 and the freeing frame at line 259; a successful fix
or any different failure fails the regression and requires review.

## Dynamic laser power is not restored after a separate M4 command

**Marked known:** 2026-10-13

Verified in core `4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa`.
With a registered PWM laser in laser mode, `M4S500` followed by `G1X10F100`
queues a cutting block without dynamic power adjustment. Equivalent arc moves
and stepper PWM execution fail as well. `G1X10F100M4S500` in one block passes.

[The M4 state-change branch](https://github.com/terjeio/grblHAL_core/blob/4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa/gcode.c#L4291)
updates `is_rpm_rate_adjusted` only when spindle state changes. The initial M4
in G0 mode leaves it false; the later cutting move keeps the same spindle state
and does not recompute it before [planner assignment](https://github.com/terjeio/grblHAL_core/blob/4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa/gcode.c#L4402).

**Regressions:** [separate M4 and line](cases/gcode/previously_enabled_dynamic_laser_cut_uses_rate_adjusted_power.c),
[clockwise arc](cases/gcode/clockwise_laser_arc_segments_keep_dynamic_power.c),
[counterclockwise arc](cases/gcode/counterclockwise_laser_arc_segments_keep_dynamic_power.c),
[check-mode parser](cases/gcode/laser_check_mode_updates_parser_without_driver_output.c),
and [stepper PWM](cases/stepper/dynamic_laser_pwm_tracks_acceleration_and_returns_to_zero.c).

**Remove exception when fixed:** delete the five associated blocks in
[known_bugs.cmake](known_bugs.cmake), retain the assertions, and delete this section.

## Empty tool-table slots lose their tool identity

**Marked known:** 2026-10-13

Verified with `N_TOOLS=4` in core `4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa`.
A fresh slot has `tool_id=0`. `G10L1P2X1.25Y2.5Z3.75R4.5` returns success but
leaves slot two unchanged: the parser copies that zero ID and the setter ignores
updates to tool zero. Writing an explicitly identified tool through the API passes.

[settings_load_tool_data()](https://github.com/terjeio/grblHAL_core/blob/4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa/settings.c#L2953)
clears missing/corrupt slots without restoring each slot's tool ID. The
[G10 copy](https://github.com/terjeio/grblHAL_core/blob/4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa/gcode.c#L3096)
passes that ID to the [setter](https://github.com/terjeio/grblHAL_core/blob/4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa/settings.c#L2918).
Corrupt-storage tests reload settings before lookup because the tool table is now cached.

**Regressions:** [G10 into a fresh slot](cases/tool_table/g10_l1_persists_tool_offsets_and_radius.c),
[missing storage](cases/tool_table/missing_storage_returns_zeroed_tool_with_requested_id.c),
[invalid checksum](cases/tool_table/checksum_failure_returns_zeroed_tool.c), and
[wrong stored ID](cases/tool_table/valid_checksum_with_wrong_tool_id_returns_zeroed_slot.c).

**Remove exception when fixed:** delete the four associated blocks in
[known_bugs.cmake](known_bugs.cmake), retain the assertions, and delete this section.
