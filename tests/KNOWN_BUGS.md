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

Outstanding regressions were reconfirmed on 2026-10-14 against Terje core
`50055a283328c3f9726bbc8f22d20a801190c66e`.
Source links identify the revision used for the described code and reproduction. CI can test
a newer revision; a fixed regression forces review and cleanup of its exception.


## Using the suggested fixes

Each **Suggested fix (proposal)** below is based on source inspection of the
revision linked in that entry. These are review suggestions, not applied or
runtime-verified patches. Check the linked revision and current code before
applying a suggestion. Snippets show the relevant edit, not complete
patches, unless stated otherwise.

Apply a proposal in a separate core checkout, select that checkout as the test
source using the README instructions, and run the linked regressions and related
module tests under sanitizers. A correct fix makes an expected-failure test turn
red because its exception is now obsolete. Follow the entry's cleanup links:
remove the allowance, replace diagnostic wrappers with direct tests where needed,
keep the regression assertions, and delete the resolved entry. Then run the full
suite and strict diagnostic summary before committing. Multiple defects can
block the same test; remove only allowances whose underlying faults are fixed.


## Analog output commands truncate fractional values

**Marked known:** 2026-10-09

**Regression:** [test](cases/gcode/m68_preserves_fractional_output.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L4).

`M68E1Q1.25` passes 1.0 to the analog output callback instead of 1.25.
The callback accepts a float (`core/ioports.h:49`), but `output_command_t.value`
is an `int32_t` ([gcode.h:312](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/gcode.h#L312)). Assigning Q at `core/gcode.c:2604`
truncates fractional values before immediate output at line 4201 or synchronized
M67 output in `core/stepper.c:515`. Preserve the numeric value through command
storage. The regression retains the fractional output expectation.


**Suggested fix (proposal):** Preserve the floating-point Q value in
[output_command_t at gcode.h:312](https://github.com/terjeio/grblHAL_core/blob/4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa/gcode.h#L312):

```diff
-    int32_t value;
+    float value;
```

Immediate M68 and queued M67 then carry the same value through storage to the
float callback. Review every `output_command_t.value` consumer: digital M62/M63
must retain their boolean 0/1 behavior. This changes a shared structure's type;
rebuild core and dependent plugins/drivers together. Validate fractional immediate
and synchronized output, queued command ordering and digital output controls.

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

**Remove exception when fixed:** delete the [CMake block](known_bugs.cmake#L25),
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

**Remove exception when fixed:** delete the [CMake block](known_bugs.cmake#L30),
retain the correct regression and passing controls, then delete this section.
No sanitizer diagnostic allowance applies.


## Named motion-mode parameter scales encoded values twice

**Marked known:** 2026-10-13; reconfirmed 2026-10-14 on Terje
`50055a283328c3f9726bbc8f22d20a801190c66e` after the motion-enum refactor.

`#<_motion_mode>` must report ten times the numerical G-code value. The latest
motion enums already use that convention, but the
[getter at ngc_params.c:522](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/ngc_params.c#L522)
multiplies them by ten again. G1 reports 100 instead of 10; G38.2 reports 3820
instead of 382; G71 reports 7100 instead of 710. G0 remains a passing zero control.
Earlier source used unrelated probe enums, so old observed values differ.

**Regressions:** `named_motion_mode_reports_*` under [NGC parameters](cases/ngc_params)
and [lathe](cases/lathe_ngc), plus
[ordinary motion modes](cases/ngc_params/named_motion_mode_tracks_g0_g1_and_g80.c).
G5.1 and G70 cases are also blocked by the separate parsing defects below.

**Suggested fix (proposal, not runtime-verified):** Return the newly encoded enum
without another multiplication. Recheck integer, fractional, probe and lathe modes.

**Remove exceptions when fixed:** remove the named-motion blocks from
[known_bugs.cmake](known_bugs.cmake), retain correct assertions, run parameter,
probe and lathe cases and full sanitizers, then delete this entry. G5.1/G70 also
require their parser fixes before shared regressions pass; remove only resolved
allowances. No sanitizer diagnostic allowance applies.

## G5.1 loses its fractional motion code during parsing

**Marked known:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

The parser accepts `.1` for G5, but
[gcode.c:1588](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/gcode.c#L1588)
clears the mantissa before the fall-through branch calls `cv()` at line 1593.
G5.1 is therefore assigned the G5 cubic mode instead of the quadratic mode, and
`G5.1X1Y1I0J1F100` is rejected. The previously passing parser and real-motion
regressions both fail at command acceptance on this source.

**Regressions:** [parser](cases/gcode/quadratic_nonzero_j_accepted.c),
[execution](cases/motion_control/quadratic_spline_executes.c), and the shared
[named parameter](cases/ngc_params/named_motion_mode_reports_quadratic_spline_code.c).

**Suggested fix (proposal, not runtime-verified):** Preserve the validated mantissa
until converting the G value into the motion enum, then clear it. Verify G5, G5.1
and rejection of unsupported fractional modes as well as executed endpoints.

**Remove exceptions when fixed:** remove the two quadratic parser/motion blocks
from [known_bugs.cmake](known_bugs.cmake); the named parameter case also needs the
getter fix above. Keep all assertions, run spline/parser/motion cases and full
sanitizers, then delete this entry.

## G70 still uses the old integer enum after the motion-code refactor

**Marked known:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

[gcode.c:1603](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/gcode.c#L1603)
still assigns 70 to G70 while `MotionMode_LatheCycle` is now 700. Finishing-cycle
validation and plugin dispatch no longer recognize the mode. Previously passing
G70 default/explicit arguments, missing-Q and wrong-plane checks now fail, along
with modal and named-parameter reporting cases.

**Regressions:** separate `finishing_cycle_*`,
[modal report](cases/lathe_ngc/finishing_modal_report_uses_g70.c) and
[named parameter](cases/lathe_ngc/named_motion_mode_reports_g70.c) under
[lathe tests](cases/lathe_ngc).

**Suggested fix (proposal, not runtime-verified):** Use the same encoded motion
conversion for G70 as G71/G72, preserving fractional-command validation. Verify
successful plugin dispatch and existing missing-Q/plane error statuses.

**Remove exceptions when fixed:** remove the six G70 blocks from
[known_bugs.cmake](known_bugs.cmake), retain all assertions, run the lathe/parser
suite and full sanitizers, then delete this entry. Named-parameter reporting also
requires the getter fix above. No sanitizer diagnostic allowance applies.
