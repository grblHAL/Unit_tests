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

## Failed startup-line writes are discarded instead of retried

**Marked known:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

Write startup slot 0 or 1 through `settings_write_startup_line()`, then have the
physical EEPROM handler reject its first write. RAM accepted the new command,
but `nvs_buffer_sync_physical()` clears the slot's pending bit
[before attempting the physical write at nvs_buffer.c:345](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/nvs_buffer.c#L345).
The pending mask and aggregate dirty flag both become zero. Subsequent syncs
therefore never retry the command, and physical storage retains the old text.
Coordinate, global, build-info and driver writes retain their dirty flag on
failure and have passing retry controls.

**Regressions:** [slot 0](cases/nvs_buffer/startup_slot_0_failed_sync_remains_pending_for_retry.c)
and [slot 1](cases/nvs_buffer/startup_slot_1_failed_sync_remains_pending_for_retry.c).
Separate `startup_slot_*_sync_preserves_text_and_checksum` cases verify successful
persistence and CRCs without an injected failure.

**Suggested fix (proposal, not runtime-verified):** Remove the unconditional
pre-write clear; clear that slot only after the physical handler reports success.
Leave failed slots dirty so another idle sync can retry them.

**Remove exceptions when fixed:** remove the two startup retry blocks in
[known_bugs.cmake](known_bugs.cmake), keep all assertions, run storage/startup
cases and full sanitizers, then delete this entry. No sanitizer allowance applies.

## Failed version-only writes lose the aggregate retry flag

**Marked known:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

Write the settings version byte through buffered `hal.nvs.memcpy_to_nvs()`, then
reject its first physical write. The version flag correctly remains true, but
[the aggregate dirty calculation at nvs_buffer.c:379](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/nvs_buffer.c#L379)
omits `settings_dirty.version` and makes `is_dirty` false when no other record is
pending. Later syncs return immediately without retrying the version byte.

**Regression:** [failed version sync](cases/nvs_buffer/failed_version_only_write_remains_pending_for_retry.c).
**Passing control:** [successful version sync](cases/nvs_buffer/version_only_successful_sync_clears_pending_write.c).
Both exercise the public buffer-write API without manually changing dirty flags.

**Suggested fix (proposal, not runtime-verified):** Include the pending version
flag in the aggregate dirty expression. Preserve per-record success/failure flags.

**Remove exception when fixed:** remove the version retry block in
[known_bugs.cmake](known_bugs.cmake), retain correct assertions and the control,
run storage/version cases and full sanitizers, then delete this entry.
No sanitizer allowance applies.

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

## Long filename lookup reallocates a static buffer

**Marked known:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

`vfs_locate_file("workbee_panel_fixture_01.nc")` aborts under ASan before looking
up the file. The initial `path.name` points to static `_name[32]`, but
[vfs.c:896](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/vfs.c#L896)
passes it to `realloc()` when `strlen(filename) + 11` exceeds the initial capacity.
The captured Windows diagnostic is a bad-free of the 32-byte global
`vfs_locate_file._name` at that exact source line.

**Regression:** [long file lookup](cases/vfs/locate_long_filename_returns_mounted_file_path.c).
Its correct expectation is the mounted file path, not a crash.

**Suggested fix (proposal, not runtime-verified):** Allocate a heap buffer for the
first growth from `_name`; call `realloc()` only on an existing heap allocation.
Keep the original pointer on failure and retain valid short-path fallback state.
Verify initial long names, later growth and allocation failure/recovery.

**Remove exception when fixed:** remove its block from
[known_bugs.cmake](known_bugs.cmake) and the special CMake registration, then run
the unchanged C test directly. Delete [diagnostic wrapper](../scripts/vfs_path_regression.py)
and its matcher tests. Run filesystem/Python checks and full sanitizers, then
delete this entry. The wrapper requires the bad-free, exact source/case frames,
32-byte static global and summary; a fix or different fault fails classification.
Coverage explicitly skips this fatal reproducer until fixed. No general
sanitizer allowance applies. Actual hosted Linux validation is still pending.

## Mount allocation failure reports success and emits a mounted event

**Marked known:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

Reject the [mount allocation at vfs.c:680](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/vfs.c#L680). `vfs_mount()` creates no
mount record, but still invokes `vfs.on_mount` and
[returns true at line 719](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/vfs.c#L719). The caller sees
a successful mount even though drive lookup still resolves to the default root.

**Regression:** [return and notification contract](cases/vfs/mount_allocation_failure_reports_failure_without_notification.c).
**Passing control:** [retry after allocation failure](cases/vfs/mount_retry_after_allocation_failure_registers_one_backend.c)
verifies no record was registered by the failed allocation and that a retry
creates exactly one backend entry. Iterator allocation failure/retry is also
covered independently.

**Suggested fix (proposal, not runtime-verified):** Return failure immediately
when non-root mount allocation fails; notify only after a mount record is linked.
Keep idempotent mounting and legitimate root-mount handling unchanged.

**Remove exception when fixed:** remove its block from
[known_bugs.cmake](known_bugs.cmake), retain correct assertions and retry controls,
run filesystem/allocation tests and full sanitizers, then delete this entry.
No sanitizer allowance applies.

## Root current-directory output rejects an exactly sized buffer

**Marked known:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

At the default root, `/` and its terminator fit in two bytes. `vfs_getcwd(buf, 2)`
returns NULL instead. Its [length calculation at vfs.c:605](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/vfs.c#L605)
adds both root prefixes plus two extra bytes and rejects the caller's adequate
buffer before copying the actual one-character result.

**Regression:** [exact root buffer](cases/vfs/root_current_directory_fits_exact_two_byte_buffer.c).
A separate too-small-buffer case and existing allocated-root-path case provide
controls; long-directory allocation and growth are tested independently.

**Suggested fix (proposal, not runtime-verified):** Determine the actual formatted
path's size including its terminator, accounting for separator removal and whether
backend or frontend current-directory text is being used. Reject inadequate buffers
without reading their previous contents.

**Remove exception when fixed:** remove its block from
[known_bugs.cmake](known_bugs.cmake), retain correct assertions and controls, run
filesystem/current-directory cases and full sanitizers, then delete this entry.
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

## Failed absolute file lookup returns an earlier filename

**Marked known:** 2026-10-14, Terje core `39a69a22c72283ab186133b25fb89b8f5be35767`.

After `vfs_locate_file("panel.nc")` finds `/panel.nc`, a later
`vfs_locate_file("/missing.nc")` whose backend stat fails returns `/panel.nc`
instead of NULL. The absolute-path branch does not clear the reusable relative
result before the common return at
[vfs.c:927](https://github.com/terjeio/grblHAL_core/blob/39a69a22c72283ab186133b25fb89b8f5be35767/vfs.c#L927).
A caller may act on a different file after the requested path was not found.

**Regression:** [absolute miss after success](cases/vfs/locate_absolute_miss_after_success_does_not_return_previous_result.c).
Passing controls cover a fresh absolute miss and a relative miss after success.

**Suggested fix (not applied):** return NULL immediately from the absolute-path
branch when root is unavailable or stat fails, keeping the existing original-path
return when stat succeeds. This avoids falling through to a stale cached result.

**Remove exception when fixed:** remove the named `WILL_FAIL` block in
[known_bugs.cmake](known_bugs.cmake), retain the assertion and controls, rerun
lookup cases and full sanitizers, and delete this section.

## Stopping during a pending spindle override briefly raises PWM

**Marked known:** 2026-10-14 on Terje `39a69a22c72283ab186133b25fb89b8f5be35767`.

With PWM ramping enabled, start at 6,000 RPM and request a 150% override without
executing its first delayed update. A subsequent stop ramps down from the stored
9,000 RPM target rather than the still-emitted 6,000 RPM output. The first stop
update raises PWM from 600 to 818 before later decreasing it and disabling the
spindle. The regression runs the original PWM, override, scheduler and stop code.

The override stores its target before scheduling output in
[spindle_set_override](https://github.com/terjeio/grblHAL_core/blob/39a69a22c72283ab186133b25fb89b8f5be35767/spindle_control.c#L627).
The stop uses that stored target as its starting speed in
[_spindle_set_state](https://github.com/terjeio/grblHAL_core/blob/39a69a22c72283ab186133b25fb89b8f5be35767/spindle_control.c#L730).

**Regression:** [stop during pending override](cases/spindle_control/pending_override_stop_does_not_increase_pwm_before_disabling.c).
Passing controls verify normal monotonic stops and cancellation of future override
updates. The assertion requires every stop PWM update to stay at or below the
output emitted before the stop; it does not require instantaneous physical braking.

**Suggested fix (not applied):** retain the last emitted RPM of the pending ramp
and use it when starting stop/direction-change ramps, before cancelling the delayed
work. Keep commanded RPM and emitted output state distinct. Revalidate ordinary
stops, partially progressed overrides, reversal and scheduler cleanup.

**Remove exception when fixed:** remove the named `WILL_FAIL` block from
[known_bugs.cmake](known_bugs.cmake), retain the assertion and controls, run the
full sanitizer suite/strict summary, and delete this section.

## Auxiliary stream allocation failure writes through a null connection

**Marked known:** 2026-10-14 on Terje `39a69a22c72283ab186133b25fb89b8f5be35767`.

When `malloc` fails while adding a client after the primary stream is registered,
[add_connection at stream.c:310](https://github.com/terjeio/grblHAL_core/blob/39a69a22c72283ab186133b25fb89b8f5be35767/stream.c#L310)
writes `connection->is_up` although `connection` is NULL. Clang reports null member
access and ASan reports a write at address 0x8. `stream_connect()` should return
false and preserve the primary connection rather than crash.

**Regression:** [failed allocation](cases/stream/auxiliary_connection_allocation_failure_preserves_primary_stream.c).
The [successful control](cases/stream/auxiliary_connection_success_allocates_and_releases_linked_node.c)
checks normal registration/removal and the primary broadcast path. Fault injection
is enabled only immediately before the auxiliary registration.

The [strict diagnostic wrapper](../scripts/stream_allocation_regression.py) accepts
only the injected failure, exact null-member-access source line/type, write at 0x8,
expected connection/caller/test frames and ASan summary. Different faults remain
failures. The fatal case skips only in unsanitized coverage runs; it is not a source
coverage exclusion. Actual Linux GCC/Clang verification remains pending delivery.

**Suggested fix (not applied):** return NULL immediately if allocation of the
connection node fails, before assigning fields. Existing caller guards can then
return false without changing the active connection or linked list.

**Remove exception when fixed:** remove this case's `WILL_FAIL` block from
[known_bugs.cmake](known_bugs.cmake), replace the wrapper CMake registration with a
normal executable test, remove [wrapper](../scripts/stream_allocation_regression.py)
and [matcher helpers](../scripts/test_stream_allocation_regression.py), retain the
functional regression and control, run full sanitizers/summary, and delete this entry.
