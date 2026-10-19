# Confirmed core defects

When updating the tested core, run the regressions before removing exceptions.
For a fixed defect, keep its regression test and remove its CMake `WILL_FAIL` and
`known_bug` properties so it becomes an ordinary passing test. Record the fix date
and core revision in the cleanup commit message, then delete the resolved defect
section from this file. Each entry links its reproduction and identifies any exception.
New memory or compile failures can remain unsuppressed; being documented here
does not by itself make a red run acceptable.
All expected-failure blocks live in [known_bugs.cmake](known_bugs.cmake), so
adding host configurations does not move the linked exceptions.
For memory defects, also replace the diagnostic-wrapper registration with a direct
executable test; the fixed test must pass under sanitizers. For feature compile
defects, remove the diagnostic matcher and retain an ordinary successful compile
check. Recovering sanitizer diagnostics have a separate, narrowly scoped
[manifest](known_sanitizer_diagnostics.json); remove its linked entries when fixed.

Remaining exceptions are validated with the selected source revision recorded in
[PROGRESS.md](PROGRESS.md). Fixed entries and their allowances
are removed; their regression assertions remain ordinary tests.
Source links identify the revision used for the described code and reproduction. CI can test
a newer revision; a fixed regression forces review and cleanup of its exception.

Storage-write failure handling is a **low-priority maintainer TODO**, documented
in [storage write-failure policy](TODO.md#storage-write-failure-policy), including
its observations, existing test exceptions and cleanup links. It is not a
settled requirement to retry physical writes a specific number of times.

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

**Maintainer disposition (2026-10-14):** Deferred to the longer-term TODO list.
Keep the fractional-value regression and its explicit exception until implemented.
See [maintainer follow-ups](TODO.md#deferred-confirmed-defects).

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

## Unexpected file percent marker reports success

**Maintainer disposition (2026-10-14):** Deferred pending review of file-demarcation
status semantics. Terje currently uses demarcation to bundle mass settings updates
into one storage commit; avoid changing that event behavior without reviewing the
sender/update workflow. The status regression remains explicit, with its exception.
See [maintainer follow-ups](TODO.md#deferred-confirmed-defects).

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

**Remove exception when fixed:** delete the [CMake block](known_bugs.cmake#L25),
retain the correct regression and passing controls, then delete this section.
No sanitizer diagnostic allowance applies.

## An armed G66 skips required-P and default-repeat checks for a new G65

**Known since:** 2026-10-19. **Reproduced core:**
`16c7dff3aa9614322cfc2b47a2109cc9196ccca4`.

Arm `G66P200X12`, then issue `G65P100X7`. The core dispatches macro100 with
repeat count0; ordinary G65 normalizes an omitted/zero L to one iteration.
With G66 armed, `G65X7` also returnsOK and calls macro0 instead of rejecting the
missing required P. A loader's treatment of repeat0 determines its actual macro
execution; the test does not claim every loader necessarily skips the body.
The accidental acceptance/dispatch of a missing macro number is directly observed.

[Macro validation](https://github.com/terjeio/grblHAL_core/blob/16c7dff3aa9614322cfc2b47a2109cc9196ccca4/gcode.c#L2264-L2279)
is guarded by `gc_state.g66_args == NULL`, so it is bypassed even for a new
explicit G65 whenever another modal macro is armed.

**Regressions:**
[default repeat](cases/ngc_params/g65_default_repeat_with_armed_g66_dispatches_one_iteration.c)
and [missing P](cases/ngc_params/g65_missing_macro_number_with_armed_g66_rejects_before_callback.c).
Both retain their correct assertions with exact named WILL_FAIL blocks in
[known_bugs.cmake](known_bugs.cmake). No sanitizer suppression applies.

**Passing controls:**
[explicit L1 with G66 armed](cases/ngc_params/g65_explicit_repeat_with_armed_g66_preserves_modal_setup_and_parent_scope.c)
and [ordinary G65 L0 defaults to one](cases/ngc_params/g65_zero_repeat_defaults_to_one.c).
The armed control verifies the original modal macro and caller arguments survive.

**Suggested fix (proposal, not applied):** always perform this validation for
`MacroCall_NonModal` (G65), while retaining the existing handling for deferred
G66/G66.1 argument blocks. A minimal guard change to review is:

```c
if(gc_block.macro_call
#if NGC_PARAMETERS_ENABLE
    && (gc_block.macro_call == MacroCall_NonModal || gc_state.g66_args == NULL)
#endif
) {
    /* existing required-P, range and default-L checks */
}
```

Check ordinary G65, G65 while G66 is armed, explicit repeats, nested macro files,
and G66.1 argument updates before adopting it.

**Cleanup:** once both regressions pass, remove their two exact WILL_FAIL blocks,
keep the assertions and passing controls, and delete this entry. No other known
issue allowance or sanitizer manifest entry needs changing for this fix.
