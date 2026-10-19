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

Outstanding exceptions were revalidated on 2026-10-17 against Terje core
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216` after removing fixed G76 inch-unit,
motion-comment ownership and queued-message callback exceptions.
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
[gcode.c:1293â€“1294](https://github.com/terjeio/grblHAL_core/blob/e65020a8389b19d3c03277e02f34219e25800e6a/gcode.c#L1293),
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

## Current-directory fallback duplicates a filesystem mount prefix

**Marked known:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

Mount a filesystem at `/store` without an optional `fgetcwd` callback and change
to `/store/dir`. `vfs_getcwd()` returns `/store/store/dir` rather than `/store/dir`.
The [fallback at vfs.c:604](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/vfs.c#L604)
uses the frontend's already absolute `cwd.name`; the
[concatenation at line 615](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/vfs.c#L615)
then prepends the mount prefix again. A backend supplying its own local `/dir`
current-directory callback passes the separate control.

**Regression:** [fallback getcwd](cases/vfs/getcwd_without_backend_handler_preserves_mount_prefix_once.c).
**Passing control:** [backend local getcwd](cases/vfs/getcwd_with_backend_local_directory_prefixes_mount_once.c).

**Suggested fix (proposal, not runtime-verified):** Copy the absolute frontend
path directly for the fallback; prepend the mount only for a backend-local path.
Preserve allocation, length checks and root formatting.

**Remove exception when fixed:** remove its block from
[known_bugs.cmake](known_bugs.cmake), retain correct assertions and control, run
filesystem/current-directory tests and full sanitizers, then delete this entry.
No sanitizer allowance applies.

## Parent traversal selects the target mount but sends a malformed filename

**Marked known:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

Mount `/store` and `/elsewhere`, then unlink `/store/../elsewhere/file`.
`mount_modifiable()` resolves the parent traversal and correctly selects the
`/elsewhere` backend, but
[vfs.c:453](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/vfs.c#L453)
strips the selected mount's prefix length from the original unnormalized path.
The target backend receives `elsewhere/file`, not its local `/file`. This can
operate on the wrong backend-local file. Same-mount paths may retain dot segments
for the backend to resolve; that supported delegation is covered by passing cases.

**Regression:** [cross-mount parent path](cases/vfs/parent_path_crossing_mount_passes_target_local_filename.c).
The test independently verifies selection of the target backend before checking
its received filename.

**Suggested fix (proposal, not runtime-verified):** Preserve the resolved path
alongside the chosen mount and strip that same path's mount prefix before calling
the backend. Check unlink/mkdir/rmdir and avoid reparsing a shared static path
buffer through itself. Retain relative-path support for backend current directories.

**Remove exception when fixed:** remove its block from
[known_bugs.cmake](known_bugs.cmake), retain correct assertions, run filesystem
path/permission tests and full sanitizers, then delete this entry.
No sanitizer allowance applies.

## Directory buffer growth failure leaks the previous allocation

**Marked known:** 2026-10-14.

When a heap-backed current directory needs to grow and `realloc` fails,
[vfs.c:513–521](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/vfs.c#L513)
overwrites the old pointer before falling back to root. GCC and Clang Linux
sanitizers both report the original 118-byte allocation as leaked in run
[38521365384](https://github.com/petervanderwalt/Unit_tests/actions/runs/38521365384).

**Regression:** [directory growth failure](cases/vfs/current_directory_reallocation_failure_falls_back_to_root.c)
checks root fallback and release of the original allocation. It reclaims a leaked
fixture allocation before asserting, allowing the same ownership check on Windows.

**Suggested fix (not applied):** assign `realloc` to a temporary pointer; if growth
fails and root fallback is retained, free the original buffer before replacing it.
Alternatively retain the original directory and return failure consistently.

**Remove exception when fixed:** remove the named `WILL_FAIL` block from
[known_bugs.cmake](known_bugs.cmake), retain the ownership assertion, run GCC/Clang
sanitizers and strict summaries, and delete this entry.

## Auxiliary pullup disable differs between live and loaded settings

**Marked known:** 2026-10-14 on Terje `39a69a22c72283ab186133b25fb89b8f5be35767`.

With `AUX_SETTINGS_PULLUP=1`, writing pullup-disable mask 2 configures input 1
with `PullMode_Down`. Loading the same stored mask configures that input with
`PullMode_None`. The physical input bias therefore depends on whether the setting
was changed live or loaded. The regression requires both paths to agree; it does
not decide which disabled-pullup mode the maintainer should choose.

The live mapping is at
[ioports.c:1335](https://github.com/terjeio/grblHAL_core/blob/39a69a22c72283ab186133b25fb89b8f5be35767/ioports.c#L1335),
and the loaded mapping is at
[ioports.c:1594](https://github.com/terjeio/grblHAL_core/blob/39a69a22c72283ab186133b25fb89b8f5be35767/ioports.c#L1594).

**Regression:** [live/load consistency](cases/ioports_pullup/pullup_disable_live_and_loaded_configuration_agree.c).
The [loaded control](cases/ioports_pullup/loaded_pullup_disable_uses_no_pull_without_changing_debounce.c)
and other pullup cases verify selected pins, mask readback, clearing, unchanged
values, inversion and absent driver configuration. Their mode-specific checks
currently document each path's existing behavior and need review when aligning
that behavior. No assertion was weakened to classify this inconsistency.

**Suggested fix (not applied):** choose one disabled-pullup mode and use the same
mapping for live changes and settings load. If disable means no pull, use
`PullMode_None` in the live setter; otherwise align the load path to the agreed
pull-down behavior. The number of driver retries and storage-failure TODO are
unrelated to this pin-configuration issue.

**Remove exception when fixed:** remove the named `WILL_FAIL` block in
[known_bugs.cmake](known_bugs.cmake), retain the consistency regression, align the
controls' mode expectations with the agreed behavior, run all pullup tests plus
the full sanitizer suite/strict summary, and delete this entry. No sanitizer
suppression or diagnostic wrapper applies.


## Stopping G83 during synchronized drilling leaves parser Z at the retract plane

**Known since:** 2026-10-17. **Reproduced on:** Terje core
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.

**Scope:** ordinary sender workflow, verified with simulated step interrupts;
not reproduced on physical hardware. Stream `G91G83X1Z-5R1Q0.25L20F100`.
Send the realtime stop command while drilling below Z0. In the host reproduction
the machine stops at X1, Z-0.25 mm, but the parser subsequently reports Z1 mm.
Sending `G91G1X1F100` then moves X by 1 mm **and moves Z from -0.25 to +1 mm**,
although the command supplies no Z word. The queued remaining holes are discarded.

The stop handler synchronizes parser and machine position, but the canned cycle
continues after its synchronized dwell and changes its `position` argument
(which aliases parser position) to the retract plane before the next motion
call notices cancellation. See [motion_control.c:596-618](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/motion_control.c#L596-L618).
The parser passes `gc_state.position` to that routine at
[gcode.c:4937](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/gcode.c#L4937),
and its cancellation guard at
[gcode.c:4972-4982](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/gcode.c#L4972-L4982)
prevents the normal final position update but does not restore that mutation.

**Regression:** [G83 stop and relative restart](cases/motion_control/sender_stop_during_peck_drill_synchronization_preserves_restart_position.c).
It uses protocol_main_loop, driver stream cancellation and emitted pulses, with
no private motion-state changes. The same fixture passes for G73 chip-break
drilling, repeated G81 holes and all six arc/spline stop controls. Ordinary G83
completion is covered by [full-retract peck drilling](cases/gcode/g83_pecks_with_full_retraction.c).
Only the named G83 stop case is expected to fail in [known_bugs.cmake](known_bugs.cmake).
There is no sanitizer allowance.

**Suggested fix (proposal, not applied):** return from the canned cycle as soon
as a synchronized dwell or spindle operation observes cancellation, before
modifying the parser-backed position again. Alternatively keep cycle working
coordinates separate and explicitly resynchronize parser position on cancellation.
Review all canned-cycle synchronization exits, not just G83, while preserving
normal retract behavior. Verify stop, hold/resume and subsequent X-only motion.

**Cleanup:** remove this single WILL_FAIL block when fixed, retain the parser and
physical-position assertions, run focused and full sanitizer checks, then delete
this entry.


## Low-memory settings lists ignore visibility and legacy-only selection

**Known since:** 2026-10-17. **Reproduced on:** Terje core
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.

**Scope:** reporting consistency under heap pressure, reproduced at the public
reporting API with one injected sort-buffer allocation failure.
Register normal plugin descriptors: two visible settings, one hidden setting and
one whose availability callback returns false. `report_grbl_settings(true, ...)`
normally passes only the two visible descriptors to the reporting callback.
When its pointer-array calloc fails, the callback also receives both hidden and
unavailable descriptors. `report_grbl_settings(false, ...)` normally selects
legacy core settings, but its allocation fallback also passes extended plugin
settings. Visible settings are still present; the selected scope changes.

The ordinary path applies its filters at
[report.c:501-521](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/report.c#L501-L521).
The [fallback, lines 530-533](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/report.c#L530-L533)
iterates every settings list without those filters. The public iterator does
not filter ordinary non-axis descriptors at
[settings.c:3215-3242](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/settings.c#L3215-L3242).
The [system command handlers](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/system.c#L300-L348)
choose full versus legacy output according to command and compatibility level.

**Regressions:** [visibility](cases/report/all_settings_sort_allocation_failure_preserves_hidden_and_unavailable_filter.c)
and [legacy-only scope](cases/report/all_settings_sort_allocation_failure_preserves_legacy_only_selection.c).
Each first verifies the ordinary successful-allocation control, then fails only
the reporting allocation and retains the same selection expectation. They observe
the public reporting callback rather than assuming a controller heap size or
allocation failure frequency. The two named exceptions are in
[known_bugs.cmake](known_bugs.cmake); there is no sanitizer allowance.

**Suggested fix (proposal, not applied):** apply the same hidden, availability,
core/plugin and `all` filters while traversing the unsorted fallback. Keep the
fallback allocation-free and allow native registration order; it need not sort.
Preserve axis/channel iterator handling and still emit every eligible setting.

**Cleanup:** remove these two WILL_FAIL blocks when fixed, keep the correct
assertions and calloc linker instrumentation, rerun focused/full sanitizer checks,
then delete this entry. The allocation observer is test instrumentation, not an
exception to remove.


## Completing a manual tool change with the door open leaves the old tool selected

**Known since:** 2026-10-17. **Reproduced core:**
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.

With a registered manual tool-change interface and safety-door input, execute
`T3M6`, save the current work offset with `G10L2P1Z0`, open the door, acknowledge
the change and send cycle start. The completion handler correctly restores input
handlers and queues the safety-door event. Close the door and explicitly resume.
The machine reaches Idle without moving, but the parser still reports tool 0
and the tool-changed callback has not fired. The ordinary closed-door control
selects tool 3 and fires that callback once. This is a parser/tool bookkeeping
reproduction; no physical cutting consequence or frequency is claimed.

[change_completed()](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/tool_change.c#L89-L115)
clears the pending tool-change flag and queues the door event. The normal
[state_await_toolchanged()](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/state_machine.c#L467-L483)
finalizes the parser tool on cycle start. The safety-door restore route instead
[returns to Idle/Cycle](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/state_machine.c#L869-L884)
without calling that finalization.
[gc_tool_changed()](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/gcode.c#L1002-L1013)
applies the pending tool and notifies its observer.

**Regression:** [door open at manual completion](cases/tool_change/open_door_at_manual_completion_queues_safety_door_before_motion.c).
**Control:** [closed-door G10 completion](cases/tool_change/g10_touch_off_notifies_plugin_and_allows_manual_change_completion.c).
One named WILL_FAIL exception is in [known_bugs.cmake](known_bugs.cmake); no
sanitizer allowance. Assertions require the selected tool and notification after
explicit door-close/resume, plus no unexpected motor pulses.

**Suggested fix (proposal, not applied):** retain a successful M6 completion
handshake across safety-door handling, and finalize the parser tool exactly once
before normal execution resumes. Preserve door motion gating. Do not finalize
a cancelled/failed change just because the generic cleanup/reset handler ran.

**Cleanup:** remove this named WILL_FAIL block when the full regression passes,
keep both regression and ordinary control assertions, run full sanitizer checks,
and delete this entry.


## Reset during manual tool-change travel selects the uncompleted tool

**Known since:** 2026-10-17. **Reproduced core:**
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.

Enable manual tool change and changing at G30. In a full driver/startup run, home
XYZ, move to X-2 Y-3 Z-1 and request `T3M6`, with G30 saved at X-4 Y-5 Z-0.5.
Send the ordinary realtime reset halfway through the initial Z retract. The
machine stops before reaching the tool-change location. After normal warm
initialization, the parser and `$G` nevertheless identify tool 3, although no
manual tool-change acknowledgement or touch-off occurred. The correct result
is to retain the previous tool 0. No physical cutting consequence is claimed.

The control sends the same reset during an ordinary positioning move and retains
tool 0. Both fixtures perform real homing, calibrate raw motor counters to homed
machine coordinates, verify reset delivery after the second startup greeting,
and compare final software positions with emitted motor steps. They do not treat
transient parser state before restart as the result. The host exit command's
additional cleanup is excluded from reset-delivery counts.

[tool_change()](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/tool_change.c#L539-L547)
does not check the final synchronization result before entering the tool-change
wait and returning success. The parser's
[completion check](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/gcode.c#L4291-L4292)
can then finalize the pending tool because the reset has left the normal
tool-change state. Warm parser initialization retains the current tool.

**Regression:** [full-boot reset during M6 positioning](cases/boot/sender_reset_during_tool_positioning_restarts_without_selecting_unfitted_tool.c).
**Control:** [ordinary positioning reset](cases/boot/sender_reset_during_ordinary_positioning_retains_current_tool_after_restart.c).
A [completed streamed G30 change](cases/boot/streamed_g30_manual_change_returns_before_touch_off_and_selects_fitted_tool.c)
selects tool 3 and restores the original position after proper acknowledgement.
One named WILL_FAIL block is in [known_bugs.cmake](known_bugs.cmake); no sanitizer
allowance.

**Suggested fix (proposal, not applied):** propagate failed/cancelled tool-change
synchronization before setting the pending wait or returning success. Guard
parser tool finalization after an aborted change, while retaining successful
manual/ATC completion and warm-reset preservation of an already fitted tool.

**Cleanup:** remove this named WILL_FAIL block once the complete restart
regression passes, retain its correct assertions and ordinary control, run full
sanitizer checks, and delete this entry.


## Cancelling a segmented delta jog retains its unreached parser target

**Known since:** 2026-10-17. **Reproduced core:**
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.

From normal delta startup, send `$J=G91Z-50F100` and ordinary realtime jog cancel
while the planner is full, before the command's acknowledgement, after 20 motor
pulses. Motion stops at 98 pulses per joint (about 10 mm of Cartesian travel),
but the parser retains the requested 50 mm endpoint. Software joint counters
agree with emitted physical steps; the mismatch is the parser Cartesian position.
This can affect the starting position for a subsequent relative command. This
host reproduction does not establish a physical incident on a particular board.

The same cancellation after the jog acknowledgement synchronizes the parser to
the stopped Cartesian position and passes. Both cases use normal boot, actual
planner/stepper execution and the public realtime command; neither forces private
kinematics state or requires an instantaneous stop.

[Parser jog completion](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/gcode.c#L4045-L4046)
copies the original target after `mc_jog_execute()` returns OK. Cancellation can
already have stopped motion and synchronized position during segmented refill.
[Jog execution](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/motion_control.c#L796-L827)
unconditionally returns OK after the segmented move.

**Regression:** [cancel during refill](cases/boot_delta/sender_jog_cancel_stops_segment_refill_and_syncs_cartesian_position.c).
**Control:** [cancel after acknowledgement](cases/boot_delta/sender_jog_cancel_after_ack_syncs_stopped_cartesian_position.c).
One named WILL_FAIL block in [known_bugs.cmake](known_bugs.cmake); no sanitizer allowance.

**Suggested fix (proposal, not applied):** carry segmented jog cancellation back
to parser completion so it does not overwrite the synchronized stopped position
with the original target. Preserve normal accepted jogs and cancellation during
motion after acknowledgement. Do not resynchronize every accepted jog immediately,
as its ordinary endpoint may still be queued for execution.

**Cleanup:** remove the named WILL_FAIL block once the full regression passes,
retain both tests and their correct assertions, run the full sanitizer suite,
and delete this entry.


## Valid ten-digit unsigned numbers ending in 6-9 are rejected

**Known since:** 2026-10-17. **Reproduced core:**
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.

A registered plugin's ordinary uint32 setting accepts `2000000005` and
`4294967295`, but rejects `2000000009` with SettingValueOutOfRange. The latter
is inside uint32 range and below the registered maximum. This affects the core
numeric parser, independently of board hardware; no particular production plugin
or physical failure is claimed. A direct parser regression also checks valid
`1000000006` and `4294967289`.

[read_uint() overflow check](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/nuts_bolts.c#L218-L223)
requires the tenth digit to be at most5 regardless of the preceding value.
That restriction is needed only when the preceding value equals429496729.
The ordinary controls verify UINT32_MAX is accepted and UINT32_MAX+1 rejected;
plugin save/notification and independent typed storage are also checked.

**Regressions:** [public plugin counter store](cases/settings/registered_plugin_counter_accepts_valid_ten_digit_value_ending_in_nine.c)
and [minimal unsigned parser](cases/nuts_bolts/read_uint_valid_ten_digit_values_ending_above_five.c).
Two named WILL_FAIL blocks in [known_bugs.cmake](known_bugs.cmake); no sanitizer allowance.

**Suggested fix (proposal, not applied):** validate the accumulated value before
multiplication using the actual uint32 limit, rather than digit count:

```c
if(intval > (UINT32_MAX - c) / 10u)
    return Status_SettingValueOutOfRange;
intval = intval * 10u + c;
```

Remove the now-unused digit counter from this function. Preserve the existing
leading-zero, optional-plus, negative-value, zero-decimal and fractional-rejection
contracts. Retest valid ten-digit endings6-9 and actual overflow.

**Cleanup:** remove both named WILL_FAIL blocks once both complete regressions
pass, keep their correct assertions and ordinary maximum/overflow controls,
run the full sanitizer suite, and delete this entry.


## Nested CRLF macro returns overcount caller file lines

**Known since:** 2026-10-18. **Reproduced core:**
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.

An asynchronous G65 file provider opens a child RAM file while its caller's
CRLF command still has the LF pending. On return, that LF is counted again.
A three-line main file calling a three-line child, which calls a two-line leaf,
finishes with reported line numbers 4, 4, 2 instead of 3, 3, 2. These are real
VFS files executed through protocol_main_loop, not manually forced parser state.
This affects file line diagnostics; the tested commands and modal results succeed.
LF-only callers, CR-only callers, and a CRLF leaf with LF callers pass.

[Shared end-of-line state](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/stream_file.c#L24-L79)
is a static variable in stream_read_file(). Nested contexts save the position and
line number but not that state; the child's EOF clears it before the caller's LF.

**Regression:** [nested CRLF files](cases/ngc_params/nested_crlf_ram_g65_files_preserve_physical_line_numbers.c).
One named WILL_FAIL block in [known_bugs.cmake](known_bugs.cmake); no sanitizer allowance.

**Suggested fix (proposal, not applied):** keep end-of-line state per active file
context. Initialize it for a new file and restore the caller's pending CRLF state
when closing its child. Preserve ordinary EOF and synthetic final-newline behavior.

**Cleanup:** remove the named WILL_FAIL block once the full regression passes,
keep its correct physical-line assertions and the LF/CR/mixed controls, run the
full sanitizer suite, and delete this entry.


## Embedded file lookup skips entries in later registered lists

**Known since:** 2026-10-18. **Reproduced core:**
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.

Registering two embedded file lists is supported by fs_embedded_mount(). With
two files in the first list and three in the second, opening the first file in
the second list returns NULL even though directory enumeration exposes it.
The lookup carries index2 from the exhausted first list into the second list,
skipping that list's first two entries. This can affect separately registered
plugin assets; no particular plugin deployment failure is claimed.

With a one-file second list, the same ordinary open additionally reproduces
AddressSanitizer global-buffer-overflow at fs_embedded.c:58. The committed test
uses a longer second list so its correct open/read assertions fail deterministically
without an invalid read, including in the non-sanitized coverage configuration.
It does not pad or alter a production list and no source fix is applied.

[find_file()](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/fs_embedded.c#L46-L64)
initializes idx only before searching the first list.

**Regression:** [open appended-list file](cases/fs_embedded/later_registered_file_can_be_opened_after_searching_first_list.c).
One named WILL_FAIL block in [known_bugs.cmake](known_bugs.cmake); no sanitizer allowance.

**Suggested fix (proposal, not applied):** reset idx to zero for every registered
list before its search. Preserve first-match ordering and hidden-file direct reads.
Retest differently sized lists, missing names, stat and directory enumeration.

**Cleanup:** remove the named WILL_FAIL block when the complete regression passes,
keep its correct open/read assertions, recheck the shorter-list ASan reproduction,
run the full sanitizer suite, and delete this entry.


## JSON minimum signed integer formatting negates INT32_MIN

**Known since:** 2026-10-18. **Reproduced core:**
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.

json_add_int() accepts an int32_t, but formatting INT32_MIN negates it while still
signed. Positive2147483648 cannot be represented by int32_t. The observed output
is the correct -2147483648 on the tested compiler; UBSan reports the undefined
signed negation. This is a formatter boundary defect, not an observed machine
motion failure or a claim that a production caller currently emits this value.
Ordinary maximum, zero and negative-number output controls pass.

[Signed negation](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/stream_json.c#L221-L231)
casts to uint32_t only after evaluating the signed conditional expression.

**Regression:** [minimum signed output](cases/stream_json/minimum_signed_integer_emits_full_decimal_value.c).
Correct decimal output assertions remain ordinary passes. Sanitizer builds also
require the narrowly matched diagnostic via its known_sanitizer_bug label in
[known_bugs.cmake](known_bugs.cmake) and test/source/line/message-scoped entry in
[known_sanitizer_diagnostics.json](known_sanitizer_diagnostics.json). Coverage
builds have no diagnostic expectation. A missing or changed sanitizer diagnostic
fails reporting with cleanup guidance; an unrelated assertion/crash is not proof
of a fix. No WILL_FAIL or global sanitizer suppression is used for this case.

**Suggested fix (proposal, not applied):** compute the magnitude in unsigned
arithmetic before formatting, preserving the existing minus sign output:

```c
uint32_t magnitude = (uint32_t)value;
if(value < 0)
    magnitude = 0u - magnitude;
char *v = uitoa(magnitude);
```

**Cleanup:** retain the correct decimal output test; remove its known_sanitizer_bug
label block and scoped manifest entry together after the corrected implementation
passes without diagnostics. Run the full suite and both report classifiers, then
delete this entry.


## Subroutine return expressions use restored caller arguments

**Known since:** 2026-10-19. **Reproduced core:**
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.

A named subroutine called with local #1=3 returns [#1+10]. Its caller has #1=99.
The observed result is109 rather than13 because the core restores the caller's
arguments before evaluating the expression. Both RETURN and ENDSUB are affected.
The regressions execute bounded recursive .macro programs through real embedded
file handles and a RAM caller. All four invocations, caller argument restoration,
normal sender recovery and return-present flags (where asserted) succeed before
the correct return-value assertion fails. Constant return-value controls pass.
This can affect macros that calculate a result from their local arguments; no
specific deployed probing/machining failure is claimed.

[LinuxCNC subroutine scope and return values](https://linuxcnc.org/docs/html/gcode/o-code.html#_subroutine_return_values)
document local call arguments and optional return expressions, including a local
parameter expression. The core supports those expressions but its
[ENDSUB path](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/ngc_flowctrl.c#L661-L672)
and [RETURN path](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/ngc_flowctrl.c#L767-L785)
unwind the subroutine before ngc_eval_expression().

**Regressions:** [RETURN expression](cases/ngc_flowctrl/embedded_named_recursive_return_preserves_outer_return_value.c)
and [ENDSUB expression](cases/ngc_flowctrl/embedded_named_recursive_endsub_closes_each_real_file_handle.c).
Two named WILL_FAIL blocks in [known_bugs.cmake](known_bugs.cmake); no sanitizer allowance.

**Suggested fix (proposal, not applied):** evaluate the optional expression while
the callee's local/modal scope still exists, save its result and presence flag,
then unwind and publish the saved return value to the caller. Preserve normal
no-expression behavior, M73 restoration, named-file callback lifetime and G65
return-handler ownership. Retest nested named and numeric callers.

**Cleanup:** remove both named WILL_FAIL blocks once both complete regressions
pass, keep correct return-value and scope assertions, run the full sanitizer
suite and classifiers, and delete this entry.


## Running spindle override changes are skipped during ordinary feed hold

**Known since:** 2026-10-19. **Verified core:**
`ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216` (Terje).

**Sender workflow:** start a normal variable-speed spindle with `M3S500`, run
`G1X20F100`, issue feed hold and wait for axis deceleration to complete, then
send the +10% spindle override realtime command. The registered non-laser PWM
driver stays on at level500 while override_pct becomes110 and calculated
rpm_overridden becomes550. Servicing the ordinary suspend manager clears
update_spindle_rpm without applying level550. Axis motion remains paused.
The same registered driver changes to550 while idle; stopping and restoring
the held spindle also applies550 and the cut then reaches its1600-step endpoint.
Coarse decrease and fine +/- show the same mismatch in local diagnostics.
This is a host reproduction through parser/realtime/driver callbacks, not a
claim about a particular board, physical acceleration or frequency in use.

**Cause:** [pending held-spindle update](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/state_machine.c#L405-L407)
calls state_spindle_restore(), but [spindle_restore()](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/spindle_control.c#L881-L891)
short-circuits when enable/direction and programmed RPM match. A changed
override alone does not invalidate that shortcut. The caller then clears the
pending flag.

**Regression:** [held override sequence](cases/state_machine/held_running_spindle_overrides_update_output_without_axis_motion.c).
Passing controls: [idle override/reset](cases/state_machine/idle_registered_spindle_overrides_update_driver_and_restore_nominal_speed.c)
and [held stop/restore followed by resume](cases/state_machine/held_spindle_stop_and_restore_apply_changed_override_before_resuming_cut.c).
One exact named WILL_FAIL block in [known_bugs.cmake](known_bugs.cmake); no sanitizer allowance.
Evidence: `../batch63-registered-diagnostic.log`, `../batch63-controls.log`.

**Suggested fix (proposal, not applied):** make the pending normal-spindle
override update bypass the unchanged-programmed-RPM shortcut. One candidate
is setting the existing `spindle->hal->param->option.restore_rpm` flag inside
that pending-update branch immediately before state_spindle_restore(), so the
restore path actually rewrites the output and then clears that force flag.
Review abort/delay/ramp behavior and only clear the pending update after an
applied output. Preserve stopped-spindle, reduced-RPM hold, dynamic laser and
plugin notification behavior. Do not use spindle_set_state_synced() here: a
held planner must not be drained by a speed-only override. This proposal has
not been validated as a production patch.

**Cleanup:** when the whole override sequence passes, remove its exact
WILL_FAIL block, keep all driver/output and no-axis-motion assertions, run the
full sanitizer suite and strict classifier, and delete this entry.
