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

## Lathe roughing modal reports use invalid probe command codes

**Marked known:** 2026-10-13, Terje's core
`e65020a8389b19d3c03277e02f34219e25800e6a`.

After successfully dispatching a roughing cycle to the plugin interface, `$G`
reports G71 as `G38.572` and G72 as `G38.582`. Fractional G71.1/G71.2/G72.1/G72.2
report `G38.573`/`G38.574`/`G38.583`/`G38.584`. Each accepted motion must instead
retain its actual G71/G72 command name in the modal report.

The [motion formatter](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/report.c#L744)
treats every motion enum at or above `MotionMode_ProbeToward` as a probe code.
The encoded roughing enums 710–722 also enter that branch. Core plugin dispatch
is tested; pending roughing geometry remains separately documented in TODO.md.

**Regressions:** [G71](cases/lathe_ngc/roughing_modal_report_uses_g71.c),
[G71.1](cases/lathe_ngc/roughing_modal_report_uses_g71_1.c),
[G71.2](cases/lathe_ngc/roughing_modal_report_uses_g71_2.c),
[G72](cases/lathe_ngc/roughing_modal_report_uses_g72.c),
[G72.1](cases/lathe_ngc/roughing_modal_report_uses_g72_1.c), and
[G72.2](cases/lathe_ngc/roughing_modal_report_uses_g72_2.c).
**Passing control:** [G70](cases/lathe_ngc/finishing_modal_report_uses_g70.c),
using the same initialized parser, plugin capture and report fixture.

**Suggested fix (proposal, not runtime-verified):** Limit the probe-format branch
to the actual G38 probe enums. Add explicit formatting for the encoded roughing
enums: integer G71/G72 for variants ending in zero, with `.1` or `.2` for the
fractional variants. Preserve G70, G5.1, G33.1 and normal probe formatting.

**Remove exceptions when fixed:** delete all six
[CMake blocks](known_bugs.cmake#L59), keep the correct report assertions and
G70 control, run the lathe/parser/report tests and full sanitizer suite, then
delete this section. No sanitizer allowance applies.

## Scaling-factor reports apply coordinate unit and diameter conversions

**Marked known:** 2026-10-13, Terje's core
`e65020a8389b19d3c03277e02f34219e25800e6a`.

With `G51X2Y3Z4`, the scaling factors are dimensionless 2, 3 and 4. The `$#`
`[G51:...]` record instead reports 0.0787, 0.1181 and 0.1575 when `$13=1` selects
inch display. In lathe G7 diameter mode it reports 4, 3 and 4: the X factor is
doubled. Metric radius-mode output correctly reports 2, 3 and 4. The tests check
the unchanged parser scaling factors before inspecting the serialized report.

[report_ngc_parameters() at report.c:620](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/report.c#L620)
passes the factor vector through the coordinate formatter, which converts inches
and doubles X for diameter mode. These conversions are appropriate for positions
but change the meaning of scaling factors.

**Regressions:** [inch display](cases/report/scaling_parameter_report_keeps_dimensionless_factors_in_inches.c)
and [lathe diameter mode](cases/lathe_ngc/scaling_parameter_report_does_not_double_diameter_mode_factor.c).
**Passing control:** [metric factors](cases/report/scaling_parameter_report_preserves_metric_factors.c).

**Suggested fix (proposal, not runtime-verified):** Use a dedicated dimensionless
factor formatter for this record, retaining all configured axis factors and decimal
precision without applying `INCH_PER_MM` or diameter doubling. Keep the existing
coordinate formatter for positions, work offsets and probe results.

**Remove exceptions when fixed:** delete both [CMake blocks](known_bugs.cmake#L84),
retain all three tests, run the scaling/parser/report cases and full sanitizer
suite, then delete this section. No sanitizer diagnostic allowance applies.

## Named motion-mode parameter exposes internal enum encoding

**Marked known:** 2026-10-13, Terje's core
`e65020a8389b19d3c03277e02f34219e25800e6a`.

After G38.2/G38.3/G38.4/G38.5, `#<_motion_mode>` returns
1400/1410/1420/1430 instead of 382/383/384/385. The
[documented parameter contract](https://www.linuxcnc.org/docs/2.8/html/gcode/overview.html)
uses ten times the numerical G-code value. Applying that convention to G5.1,
G71, G71.1 and G72 also exposes 510, 7100, 7110 and 7200 instead of
51, 710, 711 and 720. G70 and ordinary G0/G1/G80 controls pass.

The [getter at ngc_params.c:521-522](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/ngc_params.c#L521)
multiplies the internal motion enum by ten. Special enums already encode
fractional commands or use an unrelated probe range.

**Regressions:** separate `named_motion_mode_reports_*` cases under
[cases/ngc_params](cases/ngc_params) and [cases/lathe_ngc](cases/lathe_ngc).
The G38 cases execute real simulated probe motion; lathe cases verify accepted
plugin dispatch. The G70 case is an ordinary passing control.

**Suggested fix (proposal, not runtime-verified):** Map special motion enums to
their numerical G-code parameter values before applying the ordinary integer
conversion. Preserve G0/G1/G80 and G70, and cover all fractional motion modes.

**Remove exceptions when fixed:** delete the eight named-motion-mode blocks in
[known_bugs.cmake](known_bugs.cmake), retain their correct assertions and passing
controls, run parameter/probe/lathe tests and the full sanitizer suite, then
delete this section. No sanitizer diagnostic allowance applies.

## Cancelled dynamic compensation reports a nonexistent G40.1 mode

**Marked known:** 2026-10-13, Terje's core
`e65020a8389b19d3c03277e02f34219e25800e6a`.

After G41.1 or G42.1, G40 and a completed sufficiently long linear exit,
`#<_ccomp>` returns 401. It should return 400 for cancelled compensation, as
specified by the [named parameter contract](https://www.linuxcnc.org/docs/2.8/html/gcode/overview.html).
The side is off and the pending exit has completed, but the retained dynamic bit
is still added by the [getter at ngc_params.c:531](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/ngc_params.c#L531).
Static G42 followed by G40 returns the correct 400.

**Regressions:** [left](cases/cutter_comp/dynamic_left_compensation_named_parameter_tracks_enable_and_cancel.c)
and [right](cases/cutter_comp/dynamic_right_compensation_named_parameter_tracks_enable_and_cancel.c).
**Passing control:** [static compensation](cases/cutter_comp/static_right_compensation_named_parameter_uses_integer_code.c).
The fixture captures the plugin configuration and checks parser state; it does
not implement compensated toolpath geometry.

**Suggested fix (proposal, not runtime-verified):** Return 400 when the side is
`CComp_Off`; add the dynamic fractional part only for active G41/G42 modes.
Retain any compensation data needed to complete an exit move.

**Remove exceptions when fixed:** delete both dynamic-compensation named-parameter
blocks in [known_bugs.cmake](known_bugs.cmake), retain all three tests, run
cutter/parser/parameter tests and the full sanitizer suite, then delete this
section. No sanitizer diagnostic allowance applies.

## Reading all probe inputs changes the selected probe

**Marked known:** 2026-10-13, Terje's core
`e65020a8389b19d3c03277e02f34219e25800e6a`.

Register the default probe, toolsetter and second probe; select the default probe
with its input false and the second probe input true. After `probes_get_state()`,
`hal.probe.get_state()` reports Probe_2 and triggered=true, without a selection
command. This is the aggregate reader used by extended realtime reports.

[probe.c:223](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/probe.c#L223)
assigns each input to the shared active `probe` pointer during enumeration.

**Regression:** [selection preservation](cases/probe/aggregate_states_preserves_selected_probe_and_trigger_input.c).
**Passing control:** [aggregate input flags](cases/probe/aggregate_states_reports_each_registered_probe_input.c).

**Suggested fix (proposal, not runtime-verified):** Iterate using a local
`probe_t *entry` instead of overwriting the active `probe`. Leave active IRQ,
connection and probing state unchanged during reporting.

**Remove exception when fixed:** delete the selection-preservation block in
[known_bugs.cmake](known_bugs.cmake), retain the test and control, run probe and
realtime report cases plus the full sanitizer suite, then delete this section.
No sanitizer diagnostic allowance applies.

## Aggregate probe states ignore independent input inversion

**Marked known:** 2026-10-13, Terje's core
`e65020a8389b19d3c03277e02f34219e25800e6a`.

With three false raw inputs, default probe selected and only toolsetter inversion
enabled, `hal.probe.is_triggered(Probe_Toolsetter)` correctly returns true.
`probes_get_state()` instead reports the toolsetter untriggered. Its
[conversion at probe.c:224](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/probe.c#L224)
applies the selected probe's shared inversion to every input.

**Regression:** [independent toolsetter inversion](cases/probe/aggregate_states_respects_independent_toolsetter_inversion.c).
**Passing control:** [uninverted inputs](cases/probe/aggregate_states_reports_each_registered_probe_input.c).

**Suggested fix (proposal, not runtime-verified):** Convert each raw input using
its own `inverted_bit` and `settings.probe.value`, consistently with
`hal.probe.is_triggered()`. Aggregate reporting should describe physical input
states independently of the active probe's toward/away cycle configuration.

**Remove exception when fixed:** delete the independent-inversion block in
[known_bugs.cmake](known_bugs.cmake), retain correct assertions and the control,
run probe/realtime tests and the full sanitizer suite, then delete this section.
No sanitizer diagnostic allowance applies.


## Modbus RTU startup crashes when no direction output is available

**Marked known:** 2026-10-13, Terje's core
`e65020a8389b19d3c03277e02f34219e25800e6a`.

With a valid serial stream lacking its own direction callback and no auxiliary
outputs, `modbus_rtu_init(0, -1)` crashes instead of leaving RTU disabled.
[modbus_rtu.c:601](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/modbus_rtu.c#L601)
calls `d_out.claim` even though `ioports_cfg()` returned an empty configuration.
The Windows sanitizer reports an access violation at address `0xfffffffffffffff8`
in that exact initialization line.

**Regression:** [unavailable outputs](cases/modbus_rtu/aux_direction_without_outputs_disables_transport_safely.c).
**Passing controls:** separate first-output, last-output and automatic-selection
`aux_direction_*` cases complete a real RTU request/reply exchange with two
claimed-capable outputs and verify TX/RX direction transitions.

**Suggested fix (proposal, not runtime-verified):** Check `d_out.n_ports`,
`d_out.claim` and the selected port before attempting a claim. When no usable
output exists, leave direction unset and `hal.driver_cap.modbus_rtu` false.
Preserve serial-provided direction callbacks and explicit automatic-direction
mode (`dir_aux == -2`).

**Remove exception when fixed:** delete its block in [known_bugs.cmake](known_bugs.cmake)
and the specialized registration in CMakeLists.txt; the default registration
then runs the unchanged C regression directly. Delete
[scripts/rtu_direction_regression.py](../scripts/rtu_direction_regression.py) and
its matcher tests. Run RTU/I/O tests, Python helpers and full sanitizers, then
delete this section. The wrapper matches only the known fault address, source
line and regression origin. A fixed regression or different crash fails CI;
coverage mode skips it explicitly until the memory fault is fixed. No general
sanitizer diagnostic allowance applies.
