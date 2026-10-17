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
