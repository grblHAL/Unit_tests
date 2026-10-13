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

## Delta travel check accepts an unreachable Cartesian target

**Marked known:** 2026-10-09

**Regression:** [test](cases/delta/unreachable_cartesian_target_rejected.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L4).

With the default delta geometry and all axes homed, the Cartesian target
`X1000 Y1000 Z-300` is physically unreachable, yet `grbl.check_travel_limits()`
returns true. [kinematics/delta.c:603](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/kinematics/delta.c#L603) tests successful inverse kinematics
as an error, while a failed inverse can leave zero joint angles that pass the
following range checks. Reject inverse-kinematics failure before checking the
joint-angle bounds. The regression retains the correct rejection expectation.

## RTCP rotary segmentation overshoots the endpoint

**Marked known:** 2026-10-09

**Regression:** [test](cases/rtcp_ac/rotary_segment_endpoint.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L8).

With both rotary centers at zero, an RTCP move from the origin to `X10 C90`
should finish at machine position `X0 Y10 C90`. The segmented move finishes
at `X-20 Y0 C180` instead. [kinematics/rtcp_ac.c:348](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/kinematics/rtcp_ac.c#L348) replaces the starting
RTCP position with the endpoint before interpolation at lines 373-377 adds the
move delta. Preserve the original starting position throughout segmentation.
The regression retains the correct machine endpoint and rotary angle.

## Analog output commands truncate fractional values

**Marked known:** 2026-10-09

**Regression:** [test](cases/gcode/m68_preserves_fractional_output.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L12).

`M68E1Q1.25` passes 1.0 to the analog output callback instead of 1.25.
The callback accepts a float (`core/ioports.h:49`), but `output_command_t.value`
is an `int32_t` ([gcode.h:312](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/gcode.h#L312)). Assigning Q at `core/gcode.c:2604`
truncates fractional values before immediate output at line 4201 or synchronized
M67 output in `core/stepper.c:515`. Preserve the numeric value through command
storage. The regression retains the fractional output expectation.

## Named macro cleanup reads a freed subroutine callback

**Marked known:** 2026-10-10

A named macro's `RETURN`, `ENDSUB`, or error cleanup calls `clear_subs()` at
[ngc_flowctrl.c:311](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/ngc_flowctrl.c#L311), freeing its record at line 259. `stack_unwind_sub()`
then reads `stack[stack_idx].sub->callback` from that freed record at line 316.
AddressSanitizer confirms an eight-byte heap-use-after-free even when the callback
is null. The static-file backend keeps its file handle alive, independently
isolating the callback lifetime independently of file-handle allocation.

**Reconfirmed:** 2026-10-13 against `e65020a8389b19d3c03277e02f34219e25800e6a` under Clang ASan.

**Regressions:** [RETURN](cases/ngc_flowctrl/named_macro_return_preserves_subroutine_callback_lifetime.c),
[ENDSUB](cases/ngc_flowctrl/named_macro_end_sub_preserves_subroutine_callback_lifetime.c),
and [error cleanup](cases/ngc_flowctrl/named_macro_error_preserves_subroutine_callback_lifetime.c).

**Additional regression:** [embedded named-macro return](cases/ngc_flowctrl/named_macro_return_closes_file_and_restores_caller_scope.c)
now reaches this same callback fault after the VFS close and seek fixes. Its
[narrow matcher](../scripts/named_macro_cleanup_regression.py) accepts only this remaining defect.

**Remove exceptions when fixed:** [CMake registrations](known_bugs.cmake#L36).
Also replace the embedded return and `named_sub_lifetime_regression.py` registrations in
`CMakeLists.txt` with direct executable tests. The matcher requires the exact
callback read at line 316 and the freeing frame at line 259; a successful fix
or any different failure fails the regression and requires review.

## M72 restores runtime overrides but leaves parser overrides disabled

**Marked known:** 2026-10-13, Terje's core `e65020a8389b19d3c03277e02f34219e25800e6a`.

**Regression:** [M72 after M50 disable](cases/ngc_params/m72_restores_feed_and_rapid_overrides_after_m50_disable.c).
**Passing control:** [direct modal restoration](cases/ngc_params/direct_modal_restore_reinstates_feed_override_controls.c).

Save enabled feed overrides with `M70`, disable them with `M50P0`, then restore
with `M72`. Runtime override control is enabled again and the saved feed/rapid
percentages return, but `gc_state.modal.override_ctrl.feed_rates_disable` remains
true. The parser uses that stale flag for subsequent motion's `no_feed_override`
condition. The direct restore API correctly restores both representations.

The [M72 restore branch at gcode.c:4376](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/gcode.c#L4376)
clears the pending M9 action after restoring percentages, without copying the
restored `gc_block.modal.override_ctrl` into `gc_state.modal.override_ctrl`.
The [ordinary update at line 4444](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/gcode.c#L4444)
is consequently skipped. Observed after M72: parser disable=1, runtime disable=0,
feed=80, rapid=50; expected both disable flags=0.

**Suggested fix (proposal, not runtime-verified):** In the M72 M9-action branch,
copy the restored override control into parser state before clearing the action:
`gc_state.modal.override_ctrl = gc_block.modal.override_ctrl;`. Review associated
`plan_data.overrides` and `mc_override_ctrl_update()` ordering too; verify subsequent
motion and M51/M53 controls rather than treating a flag-only change as a complete fix.

**Remove exception when fixed:** delete the [CMake block](known_bugs.cmake#L49),
retain the correct regression and passing control, rerun the modal/planner tests
and full sanitizer suite, then delete this section.

## Unexpected file percent marker reports success

**Marked known:** 2026-10-12. **Reconfirmed:** 2026-10-13 against Terje's core
`e65020a8389b19d3c03277e02f34219e25800e6a`.

After parsing a normal block from a redirected file without an opening `%`, a
later `%` should return `Status_UnexpectedDemarcation`. The parser detects it at
[gcode.c:1293–1294](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/gcode.c#L1293),
then clears the block and returns `Status_OK` from the
[empty-block path at line 1343](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/gcode.c#L1343).
The caller therefore receives success for the detected invalid marker.

**Regression:** [unmarked file start](cases/gcode/file_percent_marker_after_unmarked_start_is_rejected.c).
[Runtime](cases/gcode/file_percent_markers_complete_once_in_runtime.c) and
[check-mode](cases/gcode/file_percent_markers_complete_once_in_check_mode.c)
valid-marker tests provide passing controls. This test and entry were preserved
in the archived earlier batch; they have now been restored and revalidated.

**Suggested fix (proposal, not runtime-verified):** Return the detected error
before continuing ordinary block parsing, using the existing `RETURN(status)`
cleanup path when `status != Status_OK` after handling demarcation. Retain valid
serial markers, file completion callbacks and check-mode behavior.

**Remove exception when fixed:** delete the [CMake block](known_bugs.cmake#L54),
retain the correct regression and passing controls, then delete this section.
No sanitizer diagnostic allowance applies.
