# Confirmed defects in pinned core

When updating the pinned core, run the regressions before removing exceptions.
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

Source links point to the tested core revision, rather than the latest upstream code.

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
[core/ngc_params.c](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/ngc_params.c#L607) returns the counterclockwise
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

[core/gcode.c:3153](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3153) mutates the table during validation,
and [core/gcode.c:3169](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3169) calls `set_tool` before
[core/gcode.c:3985](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3985) rejects remaining unused words.
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

[core/gcode.c:2758](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L2758) changes the live factor and
[core/gcode.c:2799](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L2799) changes the live modal flag before
[core/gcode.c:3985](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3985) rejects unused words. The regression
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

[core/gcode.c:4591](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L4591) and
[core/gcode.c:4601](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L4601) rewrite `sys.position` during rotary
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

[core/settings.c:3373](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/settings.c#L3373)'s `remove_element` writes
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

[core/gcode.c:1606](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L1606) accepts these modes and
[core/gcode.c:3540](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3540) prepares their cycle data. The
execution dispatch at [core/gcode.c:4864](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L4864) includes
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

## Axis-mask getter is called through an incompatible function pointer

**Marked known:** 2026-10-11

`get_axis_mask` in [core/settings.c:709](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/settings.c#L709) takes two
arguments, `(setting_id_t id, uint_fast16_t int_value)`. The numeric setting
reader at [core/settings.c:2054](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/settings.c#L2054) casts it to a
one-argument getter and calls it with only the setting ID. Clang UBSan reports
`call to function get_axis_mask through pointer to incorrect function type`.
The unused second argument means the selected motor mask currently reads
correctly in these host runs, but the incompatible callback call is undefined
behavior. Match the getter implementation to the callback signature.

**Regressions:** the motor [warning enable](cases/settings/motor_warning_enable_persists_axis_mask.c),
[warning inversion](cases/settings/motor_warning_inversion_persists_axis_mask.c),
[fault enable](cases/settings/motor_fault_enable_persists_axis_mask.c), and
[fault inversion](cases/settings/motor_fault_inversion_persists_axis_mask.c)
tests keep the correct getter values and persisted axis masks.

These are passing functional tests with a known sanitizer diagnostic, rather
than expected assertion failures. GCC does not detect this callback-signature
violation with the current sanitizer configuration.

**Remove exception when fixed:** delete only the
`axis-mask-getter-callback-signature` entry from
[known_sanitizer_diagnostics.json](known_sanitizer_diagnostics.json). The
summary accepts only the named callback diagnostic at `core/settings.c:2054`;
other sanitizer diagnostics still fail the run. Keep the functional tests.

## Tool-table index getter is called through an incompatible function pointer

**Marked known:** 2026-10-11

With `N_TOOLS=4`, [core/settings.c:3732](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/settings.c#L3732) casts
`settings_get_tool_data` to `get_tool_by_idx_ptr`. The getter at
[core/settings.c:2912](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/settings.c#L2912) takes a signed `tool_id_t`
(`int32_t`), while the index callback in
[core/core_handlers.h:150](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/core_handlers.h#L150) takes `uint32_t`.
Calling through this incompatible function pointer is undefined behavior.
Clang UBSan reproduces it both through the public callback and in the actual
coordinate/tool report at [core/report.c:673](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/report.c#L673).
Use a callback with the declared index signature instead of casting the signed
getter. The current functional tool data and report output remain correct.

**Regressions:** [indexed lookup](cases/tool_table/index_lookup_returns_persisted_tool_and_matching_pocket.c)
and [parameter report](cases/tool_table/parameter_report_reads_persisted_tool_slots.c)
retain their correct tool, pocket, offset, radius, and output expectations.
These are passing functional tests with a known sanitizer diagnostic.

**Remove exception when fixed:** delete the two
`tool-table-index-getter-callback-signature` entries from
[known_sanitizer_diagnostics.json](known_sanitizer_diagnostics.json).
They match only the named getter/type diagnostic at the public callback test's
line 10 and `core/report.c:673`; unrelated diagnostics still fail the run.
Keep both functional tests. GCC does not detect this function-signature
violation with the current sanitizer configuration.

## Laser power adjustment uses the previous spindle mode on M3/M4 transitions

**Marked known:** 2026-10-11

In laser mode, `G1X10F100M4S500` should plan dynamically adjusted laser power
for that move. Instead, the block's `is_rpm_rate_adjusted` flag is false.
Conversely, `M4S500` followed by `G1X10F100M3` leaves that move dynamically
adjusted even though it explicitly selects constant power.

[core/gcode.c:4076](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L4076) calculates the flag from
`sspindle->state.ccw`, which still represents the previous spindle mode.
The requested block state is applied later at
[core/gcode.c:4297](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L4297), and the stale adjustment flag is
copied into the plan at [core/gcode.c:4400](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L4400).
Determine laser adjustment from the spindle mode requested for the current
block. Separate `M4` followed by a cutting block passes as a control.

**Regressions and removable exceptions:**

- [dynamic_laser_cutting_move_uses_rate_adjusted_power](cases/gcode/dynamic_laser_cutting_move_uses_rate_adjusted_power.c): [CMake exception](known_bugs.cmake#L209).
- [switching_dynamic_to_constant_laser_disables_rate_adjustment_in_same_move](cases/gcode/switching_dynamic_to_constant_laser_disables_rate_adjustment_in_same_move.c): [CMake exception](known_bugs.cmake#L213).

Keep both correct planner expectations and remove their linked `WILL_FAIL`
blocks when the core fix makes them pass normally.

## Spindle speed updates call the laser driver during check mode

**Marked known:** 2026-10-11

In check mode, `M3S500` correctly updates the parser without calling the
registered PWM laser driver. A following speed-only `S250` block calls the
driver with the spindle enabled and power 250. Check mode should update
parser state without issuing hardware output commands.

[core/gcode.c:4118-4121](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L4118) synchronizes and calls
`spindle_set_state` directly when the speed changes without motion. This
path does not check `check_mode`. In contrast, the synchronized spindle-state
path suppresses driver output in
[core/spindle_control.c:777](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/spindle_control.c#L777).
Guard this speed-update hardware call in check mode while retaining the
correct parsed spindle speed.

**Regression:** [laser_check_mode_speed_change_does_not_call_driver](cases/gcode/laser_check_mode_speed_change_does_not_call_driver.c).

**Remove exception when fixed:** remove its [CMake exception](known_bugs.cmake#L217),
keeping the expected speed of 250 and zero driver calls.

## Plain G71 and G72 use the wrong motion codes

**Marked known:** 2026-10-12

With `LATHE_UVW_OPTION=1` and `NGC_EXPRESSIONS_ENABLE=1`, select G18, then
execute `G71X10Z20Q7F100` or `G72X10Z20Q7F100`. Both should validate and
forward the roughing cycle to the `mc_lathe_cycle` replacement supplied by a
plugin. The pinned core rejects them before calling that handler. The tests
provide an argument-capturing replacement; they do not implement roughing
geometry. G70 and the G71.1/G71.2/G72.1/G72.2 controls use the same setup.

[core/gcode.c:1594](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L1594) stores plain G71/G72 as 71/72.
However, [core/gcode.h:107-112](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.h#L107-L112) defines their
motion codes as 710/720, so they miss the matching validation cases at
[core/gcode.c:3936](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3936-L3941) and execution dispatch at
[core/gcode.c:4842](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L4842-L4847). G71 reproduces an unused-word
error with no handler call. The fractional commands are correctly multiplied
by ten at [core/gcode.c:1597](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L1597).
Map the plain commands to the corresponding enum values while preserving
G70's code and fractional variant mapping.

**Regressions:** [G71](cases/lathe_ngc/g71_passes_default_roughing_arguments_to_plugin.c)
and [G72](cases/lathe_ngc/g72_passes_default_roughing_arguments_to_plugin.c).
Each retains the correct successful dispatch, motion mode, subroutine label,
endpoint and default argument expectations.

**Remove exceptions when fixed:** delete only the
[G71 block](known_bugs.cmake#L220) and [G72 block](known_bugs.cmake#L224)
from `tests/known_bugs.cmake`, rerun both tests as clean passes and retain all
fractional-variant controls. Delete this section when both are fixed.

## G40 exit-distance validation reads arc offsets instead of the linear target

**Marked known:** 2026-10-12

With `CUTTER_COMP_ENABLE=1`, accept cutter configuration `G41.1D6` through
the plugin interface, then cancel it with standalone `G40`. The core requires
the next linear exit to be at least the cutter diameter (6 mm in this example).
The regressions isolate core parsing with a configuration-accepting plugin
replacement; they do not implement compensated geometry or physical motion.

[core/gcode.c:3363-3365](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3363-L3365)
computes that exit vector from `gc_block.values.ijk`, the arc-offset fields,
instead of the actual linear XYZ target. With no I/J/K words these are zero:
the comparison effectively depends on the current distance from the origin.

- Starting at X0, `G1X10F100` is a valid 10 mm exit, but it is rejected.
- Starting at X10, `G1X11F100` is a 1 mm exit and should be rejected; it returns
  `Status_OK` and advances the parser position to X11.

Use the resolved linear target and current position to calculate exit distance,
accounting for units, offsets and distance mode. The existing short-exit-from-
origin control must continue to reject a move shorter than the cutter diameter.

**Regressions:** [valid long exit](cases/cutter_comp/g40_long_linear_exit_is_validated_from_xyz_target.c)
and [invalid short exit](cases/cutter_comp/g40_short_exit_away_from_origin_is_rejected.c).

**Remove exceptions when fixed:** delete the [long-exit block](known_bugs.cmake#L228)
and [short-exit block](known_bugs.cmake#L232) from `tests/known_bugs.cmake`.
Keep both correct expectations and the passing boundary/control cases. Delete
this section once both regressions pass without exceptions.

## Rejected G187 commands still change the acceleration profile

**Marked known:** 2026-10-12

With `ENABLE_ACCELERATION_PROFILES=1`, start at the default 100% acceleration
profile and execute `G187P5R1`. The R word is unused, so the core returns
`Status_GcodeUnusedWords` (error 36). Despite rejecting the block, it changes
the active profile to P5 (20%). The following valid move therefore receives
20% acceleration instead of the unchanged default. At 36,000 mm/min squared configured
X acceleration, a subsequent `G1X10F100` is planned at 7,200 instead of 36,000.

[core/gcode.c:3206](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3206)
writes directly to `gc_state.modal.acceleration_factor` during validation,
before the [unused-word check](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3984-L3985).
Stage the requested factor in block state and commit it only after successful
validation. Preserve valid same-block G187/motion behavior and already queued
blocks' original acceleration.

**Regressions:** [modal state](cases/acceleration_profiles/unused_word_error_preserves_acceleration_profile.c)
and [next planned move](cases/acceleration_profiles/rejected_profile_command_does_not_slow_next_planned_move.c).
The passing P1-P5, same-block and queued-move controls remain separate tests.

**Remove exceptions when fixed:** delete the [modal-state block](known_bugs.cmake#L236)
and [planned-move block](known_bugs.cmake#L240) from `tests/known_bugs.cmake`.
Retain both tests with their correct expectations; delete this section once
they pass without exceptions.

## Rotated single-axis incremental moves add movement from the omitted axis

**Marked known:** 2026-10-12

With `ROTATION_ENABLE=1`, set G55 rotation to 90 degrees. From the origin,
`G55G1X3Y4F100` reaches machine X=-4, Y=3 mm. Follow it with `G91G1X2`:
the correct endpoint is X=-4, Y=5 mm, since omitted incremental Y means zero.
The pinned core instead reaches X=-8, Y=5 mm. At 80 steps/mm, the real stepper
code sends the driver 640 negative X pulses instead of 320 over these two moves.
The equivalent explicit-zero command `G91G1X2Y0` passes, as does absolute
single-axis motion, so the defect is specific to omitted incremental axes.

[core/gcode.c:3226-3233](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3226-L3233)
fills the omitted rotated-plane axis from the unrotated current absolute
position, even for G91. The later
[incremental addition](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/gcode.c#L3266-L3267)
then adds that unwanted component to the current machine position. Fill omitted
incremental components with zero before rotating the delta; retain absolute
single-axis completion behavior.

**Regressions:** [parser/planner endpoint](cases/rotation/incremental_single_axis_keeps_omitted_delta_zero.c)
and [actual driver pulses](cases/rotation/incremental_single_axis_executes_only_rotated_delta.c).
The explicit-zero incremental and absolute single-axis controls remain separate.

**Remove exceptions when fixed:** delete the [endpoint block](known_bugs.cmake#L244)
and [pulse block](known_bugs.cmake#L248) from `tests/known_bugs.cmake`.
Keep both tests with their correct expectations. Delete this section once both
pass without exceptions.
