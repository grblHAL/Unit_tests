# Confirmed defects in pinned core

When updating the pinned core, run the regressions before removing exceptions.
For a fixed defect, keep its regression test and remove its CMake `WILL_FAIL` and
`known_bug` properties so it becomes an ordinary passing test. Record the fix date
and core revision here. Each entry below links to its test and exception.
All expected-failure blocks live in [known_bugs.cmake](known_bugs.cmake), so
adding host configurations does not move the linked exceptions.
For memory defects, also replace the diagnostic-wrapper registration with a direct
executable test; the fixed test must pass under sanitizers. For feature compile
defects, remove the diagnostic matcher and retain an ordinary successful compile
check. Recovering sanitizer diagnostics have a separate, narrowly scoped
[manifest](known_sanitizer_diagnostics.json); remove its linked entries when fixed.

## UTF-8 ASCII encoding

**Marked known:** 2026-10-08

**Regression:** [test](cases/utf8/ascii.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L5).

`utf8.ascii` checks that U+0041 encodes to byte 0x41. At core revision
451a539c6ed0f00499b8b48258f9aa7971fac384, it produces 0xC1.
The ASCII branch uses a six-bit mask; the resulting leading-byte expression adds
0x80 modulo 256. This is a core defect, not a reason to change the expected byte.

CTest marks this one regression `WILL_FAIL` with label `known_bug`. Thus a green
run confirms the defect still reproduces, not that ASCII encoding is correct.
Unexpected success fails CI so the exception must be removed when core is fixed.
Run `ctest --test-dir build -C Debug -L known_bug --output-on-failure` to isolate it.
Run the executable directly to see the original failing assertion.

No core source changes have been made.

## read uint decimal zeros

**Marked known:** 2026-10-08

**Regression:** [test](cases/nuts_bolts/read_uint_decimal_zeros.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L9).

Decimal zero suffix: `read_uint("42.000")` returns 42000 instead of 42.

`nuts_bolts.read_uint_decimal_zeros` is a labelled expected failure, with the same
removal policy as the ASCII test above.

## read uint maximum

**Marked known:** 2026-10-08

**Regression:** [test](cases/nuts_bolts/read_uint_maximum.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L13).

UINT32_MAX parsing: the final 5 is dropped, producing 429496729.

`nuts_bolts.read_uint_maximum` is a labelled expected failure, with the same
removal policy as the ASCII test above.

## datetime century leap

**Marked known:** 2026-10-08

**Regression:** [test](cases/nuts_bolts/datetime_century_leap.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L17).

Year 2000 is a Gregorian leap year, but the date parser rejects February 29.

`nuts_bolts.datetime_century_leap` is a labelled expected failure, with the same
removal policy as the ASCII test above.

## VFS close use-after-free

**Marked known:** 2026-10-08

**Regression:** [test](cases/fs_ram/close_lifetime.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L21).

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

## Read-only named parameter assignment

**Marked known:** 2026-10-08

**Regression:** [test](cases/ngc_params/named_builtin_read_only.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L25).

`ngc_named_param_set("_metric", 0)` should reject the assignment with NULL.
At `core/ngc_params.c:855`, it forms `&rw_param->value` while `rw_param` is NULL
for predefined parameters, returning an invalid non-null pointer.
`ngc_params.named_builtin_read_only` retains the correct NULL expectation and is
a labelled expected failure until the pinned core is fixed.

## Embedded filesystem seek

**Marked known:** 2026-10-08

**Regression:** [test](cases/fs_embedded/seek_within_file.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L29).

`vfs_seek(file, 2)` on a five-byte embedded file returns -1 and leaves the
position unchanged. `core/fs_embedded.c:120` reverses the valid-offset test;
line 123 also returns failure for valid offsets. The correct seek expectation
is retained in `fs_embedded.seek_within_file`, labelled as an expected failure.

## Secondary stepper finite-move overshoot

**Marked known:** 2026-10-08

**Regression:** [test](cases/stepper2/finite_polled_move.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L33).

`st2_motor_move(motor, 10, 100, Stepper2_Steps)` emits 12 pulses and leaves
position at 12 instead of 10 in polling mode. The acceleration/deceleration
state transitions in `core/stepper2.c:501-530` continue into the unconditional
step output at line 554. The regression retains the correct 10-pulse expectation.

## JSON escaped-string serialization

**Marked known:** 2026-10-08

**Regression:** [test](cases/stream_json/escaped_quote.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L37).

Serializing the string `a"b` should preserve both letters and escape the quote.
`json_add_string()` instead loses text and produces invalid JSON. The escape path
at `core/stream_json.c:211-219` writes the wrong string spans and escape bytes.
The regression retains the correct JSON expectation. Its bounded output fixture
tracks byte counts explicitly so embedded NUL bytes cannot hide malformed output.

## Device filesystem read byte count

**Marked known:** 2026-10-09

**Regression:** [test](cases/fs_device/read_byte_count.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L41).

Reading three available bytes transfers `abc` correctly but returns `SIZE_MAX`
instead of 3. `core/fs_device.c:151` decrements the unsigned counter through zero
and line 155 returns the underflowed counter. The regression verifies content,
EOF, and the correct byte count; retain the test when removing the exception.

## Quadratic spline rejects a valid J-only control offset

**Marked known:** 2026-10-09

**Regression:** [test](cases/gcode/quadratic_nonzero_j_accepted.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L45).

`G5.1X1Y1I0J1F100` defines a valid quadratic spline with a nonzero J control
offset. The parser returns `Status_GcodeValueOutOfRange` (39) instead of
`Status_OK`. The zero-offset check in `core/gcode.c:3861` compares I twice,
so any I=0 input is rejected even when J is nonzero. Check both I and J for
zero. The regression keeps the accepted-command and final-position expectations.

## Delta travel check accepts an unreachable Cartesian target

**Marked known:** 2026-10-09

**Regression:** [test](cases/delta/unreachable_cartesian_target_rejected.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L49).

With the default delta geometry and all axes homed, the Cartesian target
`X1000 Y1000 Z-300` is physically unreachable, yet `grbl.check_travel_limits()`
returns true. `core/kinematics/delta.c:603` tests successful inverse kinematics
as an error, while a failed inverse can leave zero joint angles that pass the
following range checks. Reject inverse-kinematics failure before checking the
joint-angle bounds. The regression retains the correct rejection expectation.

## RTCP rotary segmentation overshoots the endpoint

**Marked known:** 2026-10-09

**Regression:** [test](cases/rtcp_ac/rotary_segment_endpoint.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L53).

With both rotary centers at zero, an RTCP move from the origin to `X10 C90`
should finish at machine position `X0 Y10 C90`. The segmented move finishes
at `X-20 Y0 C180` instead. `core/kinematics/rtcp_ac.c:348` replaces the starting
RTCP position with the endpoint before interpolation at lines 373-377 adds the
move delta. Preserve the original starting position throughout segmentation.
The regression retains the correct machine endpoint and rotary angle.

## Serial DEL editing character is discarded

**Marked known:** 2026-10-09

**Regression:** [test](cases/protocol/serial_delete_edits_block.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L57).

Receiving `G0X12`, DEL (0x7f), then `3` and a newline should edit the command
into `G0X13`. The serial realtime filter discards DEL, so the main loop instead
executes `G0X123`: 9840 X steps instead of 1040 at 80 steps/mm. The default
filter in `core/protocol.c:1014` excludes 0x7f before the main loop's DEL editing
branch can handle it. Retain the intended edited-command endpoint expectation.

## M66 digital input port wraps before validation

**Marked known:** 2026-10-09

**Regression:** [test](cases/gcode/m66_large_port_rejected.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L61).

With two digital inputs registered, `M66P256L0` should reject unavailable port
256 with `Status_GcodeValueOutOfRange` (39). It instead succeeds and reads
physical input 0. `core/gcode.c:2576` casts P to an eight-bit port number before
checking the available input count; 256 wraps to zero. Validate the full numeric
value before narrowing it. The regression keeps rejection and zero-read expectations.

## Analog output commands truncate fractional values

**Marked known:** 2026-10-09

**Regression:** [test](cases/gcode/m68_preserves_fractional_output.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L64).

`M68E1Q1.25` passes 1.0 to the analog output callback instead of 1.25.
The callback accepts a float (`core/ioports.h:49`), but `output_command_t.value`
is an `int32_t` (`core/gcode.h:312`). Assigning Q at `core/gcode.c:2604`
truncates fractional values before immediate output at line 4201 or synchronized
M67 output in `core/stepper.c:515`. Preserve the numeric value through command
storage. The regression retains the fractional output expectation.

## Named parameter parser accepts one character beyond its maximum

**Marked known:** 2026-10-09

**Regression:** [test](cases/ngc_expr/name_over_maximum_rejected.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L68).

`ngc_read_name()` accepts a 31-character name although `NGC_MAX_PARAM_LENGTH`
is 30. The `len <= NGC_MAX_PARAM_LENGTH` check at `core/ngc_expr.c:602`
allows the extra character. The terminating null at line 609 then requires
32 bytes, exceeding the 31-byte local buffer used by `ngc_read_parameter()`
at line 648. Reject the overlong name before writing beyond the supported
length. The regression deliberately allocates extra storage so it can assert
correct rejection without relying on a memory-corruption crash.

## NGC position parameters use display units instead of G20/G21

**Marked known:** 2026-10-09

**Regression:** [G20 test](cases/ngc_params/absolute_position_parameter_inches.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L72).

At 80 steps/mm, an X position of 2032 steps is 25.4 mm, or one inch.
After executing `G20`, `#<_abs_x>` should return 1.0; the pinned core
returns 25.4 with the default display setting. NGC parameter units must
follow `gc_state.modal.units_imperial` (`G20`/`G21`), independently of `$13`.
Both `_convert_pos()` variants in `core/ngc_params.c:144` and
`core/ngc_params.c:151` instead use `settings.flags.report_inches`, and
multiply by 25.4 when that display flag is enabled. Use modal units and
divide by 25.4 for imperial linear positions, retaining rotary-axis
exemptions in multi-axis builds. The G20 regression leaves `$13` untouched;
the separate G21 metric case expects 25.4 mm.
The [display-independence regression](cases/ngc_params/absolute_position_metric_ignores_display_inches.c)
sets G21 and `$13=1`; it expects 25.4 but gets 645.16. Remove its
[separate exception](known_bugs.cmake#L84) along with the G20 exception
when this defect is fixed.

## Negative broadcast spindle selector fails on Linux

**Marked known:** 2026-10-09

**Regression:** [test](cases/multi_spindle/gcode_m5_broadcast_stops_enabled_spindles.c).

**Remove exception when fixed:** [Linux-only CMake registration](known_bugs.cmake#L80).

`M5$-1` is the supported command to stop all enabled spindle slots, but both
Linux GCC and Clang reject it. `core/gcode.c:1486` converts the negative
floating word value to an unsigned integer; line 1487 then converts the
resulting negative fractional calculation to an unsigned mantissa. Linux
Clang additionally reports undefined floating-to-unsigned conversions at
both lines. Compute a valid magnitude or signed fractional part before
checking whether the selector is integral. These generic conversions also
run for other negative word values.

The same correct regression passes on Windows, so only Linux currently has
an expected-failure exception. The test still requires successful broadcast
stop and zero speed on both spindle outputs. Windows success does not prove
the underlying unsigned conversions are defined.

Recovering sanitizer diagnostics from these two conversions are explicitly listed
in [the diagnostic manifest](known_sanitizer_diagnostics.json). Remove that entry
when the conversions are fixed. The report separates affected assertion passes
from clean passes and fails on any unrecognized sanitizer diagnostic.

## Too-short step pulse returns generic setting error

**Marked known:** 2026-10-09

**Regression:** [test](cases/settings/pulse_width_minimum_reports_specific_error.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L88).

With a driver minimum of 2 microseconds, storing `$0=1.9` correctly rejects
and preserves the previous pulse width, but returns
`Status_SettingValueOutOfRange` (52) instead of `Status_SettingStepPulseMin`
(6). In `core/settings.c:3574`, `setting` is a pointer to the setting
metadata, while `Setting_PulseMicroseconds` is setting ID 0. Comparing the
pointer with that ID makes the intended specific-error mapping unreachable.
Compare `setting->id` with the ID instead. The regression verifies unchanged
timing and no change notification before checking the correct status code.

## Settings recovery overreads the default build-info string

**Marked known:** 2026-10-09

**Regression:** [test](cases/settings/initialize_bad_version_restores_defaults.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L92),
[diagnostic matcher](../scripts/settings_recovery_regression.py), and its
special test command in [CMakeLists.txt](../CMakeLists.txt).

Invalid stored settings trigger `settings_init()` → `settings_restore()`.
At `core/settings.c:3041`, restoration calls `settings_write_build_info(BUILD_INFO)`.
The default `BUILD_INFO` in `core/config.h:79` is an empty string occupying
one byte, but `settings_write_build_info()` at `core/settings.c:2825` asks
the NVS driver to read `sizeof(stored_line_t)` (70 bytes) from it. ASan confirms
a global buffer overread. Copy the build-info string into a bounded, padded
record before writing it. The test retains successful recovery, persisted
version, defaults, and notification expectations. Its wrapper accepts only
the matching ASan overread and both source frames; unrelated crashes fail.
Without sanitizers, this memory regression is explicitly skipped.

## Auxiliary pullup setting feature does not compile

**Marked known:** 2026-10-09

**Regression:** [compile case](compile/ioports_aux_pullup.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L96)
and [diagnostic matcher](../scripts/aux_pullup_compile_regression.py);
retain an ordinary successful syntax check for this feature.

Compiling `core/ioports.c` with `AUX_SETTINGS_PULLUP=1` fails at line 1446:
the pullup-setting metadata references `digital.in.port_names`, but `digital`
is not declared in the current implementation. Use the current input port
metadata, as the adjacent inversion setting does. Clang also reports the
resulting incomplete settings array at line 1646. The compile regression
expects this feature to compile and recognizes only these specific errors;
fixes and unrelated build errors force review of the exception.

## Rejected negative spindle speed changes RPM/CSS mode

**Marked known:** 2026-10-09

**Regression:** [test](cases/gcode/css_negative_speed_preserves_rpm_mode.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L100).

With a variable-speed spindle in lathe mode, `G96S-1` correctly returns
`Status_NegativeValue` but changes the existing RPM mode to CSS mode.
`core/gcode.c:2492` assigns `sspindle->rpm_mode` during validation, before
the negative S value is rejected at line 2498. Defer that modal-state update
until the block has passed validation. The regression checks the expected
negative-value error and retains the original RPM-mode expectation; it
prints the observed mode 1 versus expected mode 0.

The reverse transition has the same defect: after a valid `G96S100`,
`G97S-1` returns `Status_NegativeValue` but changes CSS mode to RPM mode.
Keep the [G97 regression](cases/gcode/g97_negative_speed_preserves_css_mode.c)
and remove its [separate exception](known_bugs.cmake#L104) when fixed.

## Axis-word validation accepts a valueless axis

**Marked known:** 2026-10-09

**Regression:** [test](cases/gcode/claim_axis_words_validation_retains_valueless_axis.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L108).

`gc_claim_axis_words()` with validation enabled for X accepts an X word whose
value is `NaN`, clears that word from the block, and reports X as claimed.
The regression expects X to remain unclaimed while the numeric Y word is
claimed. `core/gcode.c:392` uses the mutating `bit_true` macro inside the
validation condition. The macro expands to an unparenthesized `|=` assignment;
its existing nonzero mask makes the expression true even when `!isnan()` is
false. Use an explicit validation condition with the intended mask semantics,
and retain the numeric-value check before claiming a validated axis.

## Built-in setting macro excludes boolean settings

**Marked known:** 2026-10-09

**Regressions:** [boolean read](cases/ngc_params/builtin_setting_macro_reads_boolean.c)
and [boolean write](cases/ngc_params/builtin_setting_macro_writes_boolean_and_returns_value.c).

**Remove exceptions when fixed:** [read registration](known_bugs.cmake#L116)
and [write registration](known_bugs.cmake#L120).

`G65P1Q13` returns `Status_OK` but leaves `_value_returned` at zero instead
of returning the current boolean setting. `G65P1Q13S1` also succeeds but
ignores the requested change. `core/ngc_params.c:1105` treats only decimal,
integer, and list formats as numeric. `Format_Bool` is excluded by both
`setting_is_integer()` (`core/settings.c:3370`) and `setting_is_list()`
(line 3365), although the integer-value accessor supports it. Include
boolean settings in the numeric read/write path. The regressions retain
expected successful reads, writes, return values, and notifications.

## Three-register Modbus macro reply loses its second value

**Marked known:** 2026-10-09

**Regression:** [test](cases/ngc_params/builtin_modbus_macro_preserves_three_register_results.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L124).

A `G65P7` read requesting three registers reports `_value_returned=3`, but
returns only the first and third register values. For a reply containing
17, 34, and 51, the expected results are `_value=17`, `_value2=34`, and
`_value3=51`. Instead, `_value2` becomes 51 and `_value3` is not created.

`modbus_response_handler()` in `core/ngc_params.c:1204-1207` copies the
second register only when the reply has exactly two values. For three values,
it copies the third register into `_value2` instead. Copy the second register
when at least two values are present, and the third into `_value3` when three
are present. The regression passes a packet through the real Modbus reply
parser and keeps the correct expectations for all three values.

## Unsupported Modbus macro function crashes instead of returning an error

**Marked known:** 2026-10-09

**Regression:** [test](cases/ngc_params/builtin_modbus_macro_rejects_unknown_function.c).

**Remove exception when fixed:** [CMake registration](known_bugs.cmake#L128)
and [diagnostic matcher](../scripts/modbus_function_regression.py); register
this as an ordinary test after the fix.

With a working Modbus interface, `G65P7F99S7R0` should return
`Status_GcodeUnsupportedCommand` without sending a request. Instead, it crashes.
`modbus_get_function_properties(99)` returns `NULL`, and
`core/ngc_params.c:1225` reads `p->function` without checking `p`.
Validate the function descriptor before accessing its fields.

The regression keeps the expected rejection and zero transport calls. Its
wrapper accepts only a sanitizer-confirmed read through a null pointer at
line 1225, together with the matching Modbus macro stack frame. A fix or
unrelated failure forces exception review. This memory regression is
explicitly skipped when sanitizers are disabled.

## Clockwise spindle parameter reports the opposite direction

**Marked known:** 2026-10-10

**Regression:** [test](cases/ngc_params/named_spindle_clockwise_parameter_matches_m3.c).

After `M3S1000`, the spindle modal state is on and clockwise, but
`#<_spindle_cw>` returns 0 instead of 1. The getter in
[core/ngc_params.c](../core/ngc_params.c#L607) returns the counterclockwise
flag without inverting it. This affects macros that inspect spindle direction.
The expected clockwise meaning follows the
[LinuxCNC named parameter definition](https://www.linuxcnc.org/docs/2.9/html/gcode/overview.html).

**Remove exception when fixed:** remove the registration for
`ngc_params.named_spindle_clockwise_parameter_matches_m3` in
[known_bugs.cmake](known_bugs.cmake).

## Rejected G10 command changes and persists a tool offset

**Marked known:** 2026-10-10

**Regression:** [test](cases/gcode/rejected_g10_l1_preserves_tool_table_and_persistent_storage.c).

With tool 3's X offset initially 1, `G10L1P3X10E1` returns
`Status_GcodeUnusedWords` (error 36), because `E1` is unused. Despite rejecting
the block, the core changes the X offset to 10 and calls the tool table's
`set_tool` persistence callback. The expected result is an error with the
existing tool data and persistent storage unchanged.

[core/gcode.c:3153](../core/gcode.c#L3153) mutates the table during validation,
and [core/gcode.c:3169](../core/gcode.c#L3169) calls `set_tool` before
[core/gcode.c:3985](../core/gcode.c#L3985) rejects remaining unused words.
The regression runs in idle mode and captures the actual persistence callback.

**Remove exception when fixed:** remove the registration for
`gcode.rejected_g10_l1_preserves_tool_table_and_persistent_storage` in
[known_bugs.cmake](known_bugs.cmake).

The separate [G10 L10 regression](cases/gcode/rejected_g10_l10_preserves_existing_tool_offsets.c)
confirms the same premature mutation in `G10L10P3Z2E1`: it returns error 36
but changes tool offsets from `(1,2,3)` to `(0,0,-2)`, including axes absent
from the rejected block. L10 does not call the persistence callback in this
regression; its in-memory tool data still changes. Remove the registration for
`gcode.rejected_g10_l10_preserves_existing_tool_offsets` in
[known_bugs.cmake](known_bugs.cmake) when the G10 validation defect is fixed.

## Rejected G51 command enables scaling

**Marked known:** 2026-10-10

**Regression:** [test](cases/gcode/rejected_g51_preserves_scaling_state_and_factors.c).

Starting with scaling disabled, `G51X2E1` returns
`Status_GcodeUnusedWords` (error 36), because `E1` is unused. Despite rejecting
the block, the core enables scaling and sets the X factor to 2. Later X motion
can therefore be scaled by a command that was reported as unsuccessful.
The correct expectation is unchanged scaling state and factor 1.

[core/gcode.c:2758](../core/gcode.c#L2758) changes the live factor and
[core/gcode.c:2799](../core/gcode.c#L2799) changes the live modal flag before
[core/gcode.c:3985](../core/gcode.c#L3985) rejects unused words. The regression
runs in idle mode.

**Remove exception when fixed:** remove the registration for
`gcode.rejected_g51_preserves_scaling_state_and_factors` in
[known_bugs.cmake](known_bugs.cmake).

## Rotary G28 changes machine position during check mode

**Marked known:** 2026-10-10

**Regression:** [test](cases/eight_axis/g28_rotary_check_mode_preserves_actual_machine_position.c).

With rotary wrapping enabled, A at 710 degrees (56800 steps), and a stored G28
position of 10 degrees, `G91G28A0` in check mode produces no motor pulses.
Nevertheless, the core changes the live A machine position to 10 degrees
(800 steps). The physical axis remains at 710 degrees, equivalent to 350
degrees modulo a full turn, so the reported angle no longer matches it.
Check mode should simulate the parser result while preserving actual machine
position.

[core/gcode.c:4591](../core/gcode.c#L4591) and
[core/gcode.c:4601](../core/gcode.c#L4601) rewrite `sys.position` during rotary
G28 without a check-mode guard. Separate normal-mode tests verify wrapping
through actual motor pulses.

**Remove exception when fixed:** remove the registration for
`eight_axis.g28_rotary_check_mode_preserves_actual_machine_position` in
[known_bugs.cmake](known_bugs.cmake).

## Disabling a short settings option also removes following options

**Marked known:** 2026-10-10

**Regression:** [test](cases/settings/remove_elements_preserves_options_after_short_label.c).

For plugin option metadata `Off,On,Auto`, calling
`setting_remove_elements(id, 5, false)` should disable only the middle option
and leave `Off,N/A,Auto`. Instead it produces `Off,N/A`, removing the available
`Auto` option. The test supplies a mutable 64-byte buffer with enough room
for the replacement.

[core/settings.c:3373](../core/settings.c#L3373)'s `remove_element` writes
the three-character `N/A` placeholder before finding the original end of
the option. For a name shorter than three characters, that overwrites the
separator and loses subsequent labels. This is an option-metadata API edge
case; no affected shipped driver or plugin has been identified.

**Remove exception when fixed:** remove the registration for
`settings.remove_elements_preserves_options_after_short_label` in
[known_bugs.cmake](known_bugs.cmake).

## G85, G86 and G89 are accepted without executing the drilling cycle

**Marked known:** 2026-10-10

**Regressions:**

- [G85](cases/gcode/g85_accepted_cycle_executes_drill_and_retract.c).
- [G86](cases/gcode/g86_accepted_cycle_executes_drill_and_retract.c).
- [G89](cases/gcode/g89_accepted_cycle_executes_drill_and_retract.c).

`G85Z-1R0F100`, `G86Z-1R0P0F100`, and `G89Z-1R0P0.1F100` all return
`Status_OK`, but none produces a Z-axis motor pulse. For an accepted cycle,
the requested 1 mm plunge and return should produce 160 Z pulses at the
fixture's 80 steps/mm. The tests also accept an explicit
`Status_GcodeUnsupportedCommand` with no motion; silently returning success
without drilling is the defect.

[core/gcode.c:1606](../core/gcode.c#L1606) accepts these modes and
[core/gcode.c:3540](../core/gcode.c#L3540) prepares their cycle data. The
execution dispatch at [core/gcode.c:4864](../core/gcode.c#L4864) includes
G73 and G81 through G84, but omits G85, G86, and G89.

**Remove exceptions when fixed:** remove the three matching
`gcode.g85_accepted_cycle_executes_drill_and_retract`,
`gcode.g86_accepted_cycle_executes_drill_and_retract`, and
`gcode.g89_accepted_cycle_executes_drill_and_retract` registrations in
[known_bugs.cmake](known_bugs.cmake). Each regression then passes when the
cycle executes correctly or is explicitly rejected as unsupported.

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

**Remove exceptions when fixed:** [CMake registrations](known_bugs.cmake#L180).
Also replace their `named_sub_lifetime_regression.py` registrations in
`CMakeLists.txt` with direct executable tests. The matcher requires the exact
callback read at line 316 and the freeing frame at line 259; a successful fix
or any different failure fails the regression and requires review.

## NGC ALARM and ERROR silently discard expression failures

**Marked known:** 2026-10-10

`ALARM[1/0]` and `ERROR[1/0]` return success (status 0) instead of the
expression evaluator's division-by-zero error (status 72). At
`core/ngc_flowctrl.c:642` and `:647`, evaluation failure suppresses the action
but is not assigned to the returned status. The caller therefore receives
success for an invalid script expression.

**Regressions:** [ALARM](cases/ngc_flowctrl/alarm_expression_errors_are_reported.c)
and [ERROR](cases/ngc_flowctrl/error_expression_errors_are_reported.c).
Each independently confirms that evaluating `[1/0]` returns status 72 before
checking the flow-control command. The correct expectation remains status 72.

**Remove exceptions when fixed:** [CMake registrations](known_bugs.cmake#L192).
These ordinary assertion regressions need no sanitizer wrapper. Keep both tests
and remove their `WILL_FAIL` and `known_bug` properties when errors propagate.

## Legacy compatibility reporting does not compile

**Marked known:** 2026-10-11

`COMPATIBILITY_LEVEL=2` and `COMPATIBILITY_LEVEL=10` remove the extended G59.1-G59.3 coordinate-system
enums from `core/gcode.h:194-196`. The tool-reference position report still
uses `CoordinateSystem_G59_3` unconditionally at `core/report.c:718`, so
compilation fails with an undeclared-identifier diagnostic. The feature cannot
be exercised as a linked firmware build until the report handles coordinate
systems available at the selected compatibility level.

**Regression:** [compile case](compile/report_compatibility.c). The
[diagnostic matcher](../scripts/report_compatibility_compile_regression.py)
first requires the same source to compile at level 1, then accepts only the
missing `CoordinateSystem_G59_3` error at `core/report.c:718`. Fixed builds
and unrelated errors fail classification and require review.

**Remove exceptions when fixed:**

- Level 2: [CMake exception](known_bugs.cmake#L200) for `feature_compile.legacy_compatibility_level_2_reporting`.
- Level 10: [CMake exception](known_bugs.cmake#L204) for `feature_compile.legacy_compatibility_level_10_reporting`.

Remove the matcher and special compile commands in [CMakeLists.txt](../CMakeLists.txt),
and replace these compile regressions with ordinary runtime tests for the
working compatibility configurations.
