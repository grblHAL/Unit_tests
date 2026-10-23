# Known CORE issues and coverage gaps

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

## Device open allocation failure leaves the UART reserved

Confirmed 2026-10-23 on clean CORE `2e165a1ac4c74be8e68971972c6577775d856b05`.
A registered UART is claimed normally, then the file-wrapper calloc fails during
public `vfs_open("/dev/uart2", "w")`. Open returns NULL, but retry after allocator
recovery also returns NULL without reclaiming or returning a usable file. A
separate registered UART still opens, writes and closes normally. This is a
failed-open resource reservation, not a communication failure on other devices.

[Regression](cases/fs_device/open_allocation_failure_releases_device_for_retry.c)
injects exactly one scoped calloc failure and retains the correct non-NULL retry
assertion. Raw ASan/UBSan execution reaches that final assertion without any
sanitizer diagnostic; earlier allocation-count, claim-count and independent UART
controls pass. One exact WILL_FAIL/known_bug allowance is registered in
[known_bugs.cmake](known_bugs.cmake); no diagnostic suppression is needed.

Cause: [fs_device.c116-122](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/fs_device.c#L116-L122)
sets `state.passthru` before allocating the returned file. On allocation failure
that reservation remains set, so the next open rejects at117. There is no returned
file for the caller to close and release. Suggested maintainer fix: reserve only
after successful allocation, or roll back the reservation when allocation fails.
CORE is unchanged here. Once corrected upstream, remove this one allowance and
retain the passing retry and independent-device assertions.

## RAM nonzero truncate loses the retained file allocation

Confirmed2026-10-23 on clean CORE `51b58594ce467e9c4b103fb93d1ca121e43cd15c`.
An ordinary public VFS sequence uploads `G1X1\nG1X2\n`, closes/reopens the file,
shrinks it to five bytes, confirms the reported size, seeks to zero and reads the
retained prefix. Shrink succeeds and size is correct, but the read starts just
past the five-byte allocation. ASan reports a five-byte heap-buffer-overread in
`fs_read` at `core/fs_ram.c:184`, allocated by `fs_truncate` at256.

Regression: [retained-prefix workflow](cases/fs_ram/truncate_committed_file_to_nonzero_length_preserves_prefix.c).
The [pending-upload variant](cases/fs_ram/truncate_pending_upload_to_shorter_nonzero_length_preserves_prefix.c)
shrinks before closing the write handle, covering the normal pending-buffer flush
branch as well as committed-file shrink. Each case has its own exact allowance.
Correct prefix, EOF, close and consumed-file assertions remain; the fatal
sanitizer reproduction cannot execute assertions after the read. Two named
WILL_FAIL allowances and sanitizer-only known_crash wrappers accept only this memcpy
read-overrun, exact CORE caller/source line and shrink allocation frame.
Other faults, changed frames, missing diagnostics and a repaired executable
remain failures requiring allowance cleanup. Raw evidence:
`build-asan/batch74-ram-shrink-raw-results.xml`; classified evidence:
`build-asan/batch74-ram-shrink-known-results.xml`.

Cause: the shrink branch first retains the realloc base, then overwrites both
`data` and `pos` with `data + length` at258. Subsequent public seek/read uses that
one-past-end pointer as the allocation base. No private state or invalid handle
is injected. This does not claim executed motion or a sender-specific effect.

Suggested repair for Terje: retain the allocation base and keep cursor/remaining
length coherent after shrink. Remove this entry, named allowance, diagnostic
manifest entry and wrapper registration when the unchanged sanitizer regression
passes. CORE has not been edited.

## Combined broadcast M48 leaves both spindle speed overrides disabled

**Confirmed:** 2026-10-23, clean CORE `50f38659db7b22f4689f3654df2d110d992bcc95`.
Normal same-block spindle/override commands expose the broadcast path:
M3M49$-1 starts both enabled spindles and disables their overrides correctly.
M3M48$-1 is also accepted, reenables feed override, but leaves both spindle speed
overrides disabled. Programmed3000/7000RPM at110/120% should become3300/8400;
actual driver outputs remain3000/7000, with both disable flags set. Stored
percentages remain110/120; the third registered but unenabled driver is untouched.

[Correct regression](cases/multi_spindle/broadcast_spindle_start_with_m48_restores_both_speed_overrides.c)
uses registered drivers and public parser/override APIs. It verifies broadcast
start/direction, unchanged percentages and no unused-driver calls before the
correct enable/output assertions. [M49 control](cases/multi_spindle/broadcast_spindle_start_with_m49_disables_both_speed_overrides.c)
passes and also reenables only the secondary through public M51P1$1.
Existing standalone M48 positive controls remain ordinary passing tests.
Raw evidence: build-asan/batch74-broadcast-override-raw-results.xml.

Cause: [M48 broadcast loop](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/gcode.c#L2689)
sets spindle_rpm_disable bits with bit_true; the single-spindle branch clears
them with bit_false. Preserve broadcast selection while clearing the requested
disable bits. One exact named WILL_FAIL in known_bugs.cmake; no sanitizer
allowance or CORE edit. When fixed, retain the regression, remove its exception
and delete this entry. This is an ordinary accepted command combination, not a
saturated scheduler or timing-window proposal.

## Stopped-spindle rigid tapping enters macro fallback after synchronization fails

**Confirmed:** 2026-10-23, clean CORE `50f38659db7b22f4689f3654df2d110d992bcc95`.
With an actual registered encoder spindle, M5 followed by G33.1Z-1K1I2 fails
synchronization with Status_GcodeSpindleNotRunning (41). The G33.1 execution
path nevertheless tests only whether status differs from UnsupportedCommand,
pushes a call scope, and calls macro331. An unhandled provider changes the
result to Status_GcodeValueOutOfRange (39), losing the original error.

[Regression](cases/spindle_sync/stopped_spindle_rejects_rigid_tapping_without_calling_macro_fallback.c)
uses public parser commands, real encoder/stepper observers, and a normal macro
provider returning Unhandled. The running-spindle control correctly returns the
current weak implementation's UnsupportedCommand without calling that provider.
The stopped command must preserve error41 and must not invoke a macro after
failed synchronization. No motion, queue, encoder reset, override leak or call
scope leak was observed; do not claim an executed macro body or unsafe motion.
Raw evidence: build-asan/batch74-stopped-tapping-raw-results.xml: status39,
expected41, provider called1. All preceding no-motion/restoration assertions pass.

Source: [init_sync_motion](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/gcode.c#L1058)
and [G33.1 execution](https://github.com/terjeio/grblHAL_core/blob/50f38659db7b22f4689f3654df2d110d992bcc95/gcode.c#L4841).
Preserve initialization failures before considering any native/macro continuation;
maintain the separate unsupported-native-tapping contract. One exact named
WILL_FAIL in known_bugs.cmake; no sanitizer allowance or CORE edit. When fixed,
retain this regression and remove its expected-failure properties and this entry.

## Known coverage gaps

These are tracked placeholders for missing or inaccessible implementation, not
executable bug reproductions. They are **known uncovered**, not covered code.
They do not create synthetic CTest failures, increase test counts, exclude source
or change the coverage denominator. Existing public rejection tests still run.
`WILL_FAIL` is reserved for a runnable regression with a meaningful assertion.

**Measured:** 2026-10-23, clean Terje `2e165a1ac4c74be8e68971972c6577775d856b05`.
The successful [exact-source report](https://github.com/petervanderwalt/Unit_tests/actions/runs/40032608243)
measures 17,479/17,756 lines (98.44%) and 12,567/13,834 branches (90.84%).
The 277 uncovered lines include the following known gaps; this table does not
claim that every remaining line is unavailable. See the complete measured
[line/branch inventory](COVERAGE_GAPS.md) before selecting the next workflow.

| Region | Status and evidence | What makes it testable |
|---|---|---|
| VFS lookup/rename residual guards | Three unreachable lines: lookup always returns cwd/root; cross-mount rename rejects before its second notification. [Source audit](TODO.md#verified-residual-guards-vfs-lookuprename-and-virtual-parameter-root). | Upstream changes lookup or cross-mount rename semantics. |
| G84 helper flag guards | Six false arms are unreachable: both private helper call sites pass every flag enabled. [Caller audit](TODO.md#g84-private-override-helper-flag-guards). | A supported caller uses partial flags. Saved disabled-policy behavior is separately tested. |
| Tab-setting datatype default | All declared public datatypes are handled; Int8/Int16 normalize to Integer. [Source audit](TODO.md#tab-setting-metadata-default-datatype-arm). | A new valid datatype reaches the formatter. |
| Virtual-parameter empty-list registration | Built-in `_value`/`_value_returned` nodes keep the list nonempty. [Source audit](TODO.md#verified-residual-guards-vfs-lookuprename-and-virtual-parameter-root). | A supported lifecycle permits an empty list. |
| Wall-plotter homing helpers | Unimplemented public workflow. [home_machine](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/kinematics/wall_plotter.c#L301) warns and returns false; [existing rejection test](cases/wall_plotter/unsupported_homing_reports_warning.c) passes. The report has 56 uncovered helper lines. | Implement public homing and define its reference/endpoint contract; then test actual motion through that entry point. |
| Native rigid tapping and its downstream execution | Unimplemented extension. [mc_rigid_tapping](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/motion_control.c#L793) is a weak TBC stub returning unsupported. | The real parser/stub rejection path now has a [ordinary rejection regression](cases/spindle_sync/unsupported_rigid_tapping_preserves_position_and_next_supported_sync_move.c). Native geometry still needs a supported implementation, then encoder/spindle synchronization, reversal and physical endpoint tests. |
| Auxiliary open-drain setting handlers | Inaccessible setting. [Public registration](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/ioports.c#L1449) is commented out; [existing setting-disabled test](cases/ioports/open_drain_setting_is_not_exposed.c) passes. | Expose the setting upstream; test public write/readback, persistence and driver effect. |
| Timezone setting availability | Inaccessible setting. [Registration](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/settings.c#L2494) is commented out. | Expose it upstream and define accepted units/range before public setting tests. |
| Stale setting getters/availability and closed-loop group arms | Unreachable through current registry: registered getters bypass the old cases, some settings have no availability callback, and the closed-loop group is not registered. See [detailed registry audit](TODO.md#remaining-coverage-unexposed-settings-and-parser-branches). | Update the registry or remove obsolete implementation upstream. Test the public behavior if exposed; never install a fake registry entry to hit a private case. |
| Plugin-induced N/A setting listing | Public registration rejects a null value pointer before linking the provider. See [registration/listing audit](TODO.md#settings-list-na-fallback-cannot-be-reached-by-a-valid-plugin-descriptor). The actual rejection and corrected retry have an executable test. | Reassess if public descriptor rules change; do not corrupt registered metadata to enter the fallback. |
| Parking restore restart flag | The only setter of restoring runs after the handler changes to state_await_resumed; door events use its restart path. [Handler audit](TODO.md#parking-restore-restart-flag-and-callback-handler-ordering). | Upstream changes restore/event handler ordering. Real repark and second-resume completion remain tested. |
| Delayed-task fallback search | Defensive/unreachable under supported single-core IRQ masking: task_get_due returns the selected head with IRQs still masked. See [atomic-selection audit](TODO.md#delayed-task-fallback-after-atomic-selection-68eba79). | Reassess if the selection/concurrency contract changes; retain the passing public interrupt/cancellation regressions. |
| Post-reader NaN rejection | Expression reader rejects NaN before this guard; explicit valueless-word NaN is excluded by its M-code type condition (gcode.c1470-1471). See [reader audit](TODO.md#parser-post-reader-nan-guard-audit---2026-10-22). | Revisit if reader or valueless-word contract changes; retain raw coverage. |
| M6 check-mode message cleanup | Historical guard audit applies to the earlier source. Upstream2e165a1 moves check-mode message cleanup outside the execution-only arm. | Existing M6 check-mode control passes. Current-source normalization still preempts message allocation; see the updated routing review in TODO. |
| M48/M49/M51 broadcast override arms | Unreachable through current parser addressing rules; ordinary blocks reject the unused/invalid dollar selector before these arms. See [parser audit](TODO.md#remaining-coverage-unexposed-settings-and-parser-branches). | Define and expose broadcast syntax upstream, then test observable output of every enabled spindle. |

Pending contract questions, including G70-G72 execution/reporting and G76 main
taper, remain in [TODO.md](TODO.md). They cannot become asserted failures until
the required behavior is settled. Move a gap to an executable regression when
it becomes publicly reachable, or to a confirmed defect entry when a supported
workflow demonstrably fails. Retain raw coverage throughout.

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

## Fallback getcwd does not preserve the frontend current directory

**Marked known:** 2026-10-14. **Reconfirmed:** 2026-10-22, Terje fab8d1c.
Mount `/store` without fgetcwd and change to `/store/dir`. The frontend must
report `/store/dir`; older source duplicated the prefix, while the current
[fallback](https://github.com/terjeio/grblHAL_core/blob/7a6a432eaf78e028b81ff3a5f9804e14519f5f01/vfs.c#L590-L616)
uses `/` and loses the subdirectory. The ordinary regression reproduces the
assertion failure after the independent string-allocation crash was fixed.

**Regression:** [frontend getcwd](cases/vfs/getcwd_without_backend_handler_preserves_mount_prefix_once.c).
**Control:** [backend-local getcwd](cases/vfs/getcwd_with_backend_local_directory_prefixes_mount_once.c).
**Cleanup:** remove this named block in [known_bugs.cmake](known_bugs.cmake),
retain the correct assertion and control, then delete this entry once fixed.
**Suggested fix for Terje (not applied):** use the cached absolute frontend path
when no backend callback exists; prefix only a backend-local path.


## Hidden files in a visible mount remain accessible by relative path

**Maintainer contract clarified 2026-10-23:** hidden files require a full path.
CORE51b58594 now rejects CWD into hidden mounts; the two unchanged directory
regressions pass under sanitizers and their allowances were removed. Explicit
full-path reads remain passing controls. The separate mixed-mount file issue
below remains outstanding; no caller-identity API is assumed.

**Full-path-only file reproduction,2026-10-23, CORE50f3865:**
[Hidden file in a visible mount](cases/fs_embedded/hidden_file_in_visible_mount_requires_full_path_after_chdir.c)
registers one visible and one hidden asset, changes into the legitimately visible
mount, confirms a relative visible-file read and full-path hidden-file read, then
opens the hidden file by relative name. That last open wrongly succeeds under
the clarified full-path-only contract. One exact WILL_FAIL retains the rejection
assertion; no sanitizer allowance. Raw evidence:
build-asan/batch74-hidden-path-raw-results.xml. Merely blocking CWD into hidden
mounts will not address this mixed visible/hidden mount case. Preserve ordinary
relative visible access and explicit hidden access when fixing it; remove the
allowance once the unchanged test passes. No caller-identity API is assumed.


## Alarm-rejected block prevents closing settings-upload demarcation

**Observed:** 2026-10-22, clean Terje fab8d1c and68eba79.
[Full boot regression](cases/boot/alarm_locked_settings_upload_demarcates_batch_and_keeps_motion_blocked.c)
streams `%`, valid $11, alarm-rejected G91, then `%`. The closing observer
callback is missing: the test fails its two-demarcation assertion. The later
motion-blocking assertions have not executed. Compatibility-zero last_error
gating follows the demarcation alarm bypass. Whether the sender must clear
that error is a pending contract question, not a confirmed firmware diagnosis.
Per requested nonblocking failure handling, retain the correct assertions and
one named WILL_FAIL while Terje confirms the contract. No sanitizer allowance.
Remove it when the agreed public upload workflow passes; see TODO's closing
serial demarcation entry. Full evidence: batch72-core68-delivery.xml.

## Direct modal restore reports compensation that its extension refused

**Confirmed:** 2026-10-22, clean Terje68eba7906ba60d66c8b55c4adc90cd5e85b5a828.
[gc_modal_state_restore](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/gcode.c#L594-L616)
updates the live cutter-compensation state from the snapshot before calling
cc_enable, then ignores a false return. Public ngc_modal_state_restore therefore
returns true and leaves the parser in G41 even when the extension refused to
leave G40. Ordinary M72 follows the checked block-execution path and correctly
returns Status_GcodeUnsupportedCommand while preserving G40 in the same setup.

**Regression:** [refused direct restore and retry](cases/cutter_comp/direct_modal_restore_preserves_disabled_mode_when_extension_refuses.c).
The existing linked extension fixture first accepts G41.1D6 and M70, then
accepts G40 and its10mm exit. With refusal enabled, M72 is a passing control;
direct restore is invoked through its public API and incorrectly reports side1.
The test records that inconsistency, re-enables the extension, demonstrates a
successful saved-state retry and frees the snapshot before its final correct
assertion. No compensated geometry or physical-controller result is invented.
One named WILL_FAIL/known_bug, no sanitizer allowance. Raw evidence:
batch72-cutter-refusal-raw.xml (result1, parser side1 after refusal).

**Suggested fix for Terje (not applied):** validate/commit cutter compensation
restoration consistently with the checked parser path, retaining the previous
accepted state if the extension refuses and reporting restoration failure.
Preserve successful restore/disable behavior. Remove this allowance and entry
once clean source passes the refusal, M72 control and accepted retry under
sanitizers.

## Asymmetric auto-squaring initial pull-off leaves the secondary motor on its switch

**Confirmed:** 2026-10-22, clean CORE `68eba7906ba60d66c8b55c4adc90cd5e85b5a828`.
[Regression](cases/boot_square/engaged_switches_pull_off_before_independent_motor_homing.c)
boots the four-axis asymmetric Y/A configuration, with both physical switches
engaged, then sends public `$H`. The primary motor pulls away, but the secondary
receives no pulses and remains engaged; homing raises alarm 8 rather than
completing. The same driver and settings with initially clear switches pass
[the independent motor control](cases/boot_square/clear_switches_home_both_motors_independently.c),
including final physical positions Y=80/A=160, released switches, both homed bits,
and no X/Z pulses. Startup alarm 11 is expected before either homing command.
Raw sanitizer evidence: `build-asan/square-engaged-raw.xml`.

`machine_limits.c:616` passes only the auto-squared primary axis to
`limits_pull_off`. Its kinematics transform creates a secondary target, but
`sys.homing_axis_lock` is still set to that primary-only mask at line 213.
The secondary motor therefore cannot move. The later dual-axis offset path
explicitly adds the asymmetric secondary axis before calling the same helper.

**Suggested fix for Terje (not applied):** include the asymmetric secondary motor
in the initial pull-off lock/motion mask while preserving switch checking and
normal independent homing. Keep the correct regression; remove its exact
WILL_FAIL/known_bug block and this entry once upstream passes under sanitizers.
No CORE edit or sanitizer allowance.

## RTCP rotation at the tool center loses the rotary endpoint

**Confirmed:** 2026-10-22, clean CORE `68eba7906ba60d66c8b55c4adc90cd5e85b5a828`.
[Regression](cases/rtcp_ac/rotation_at_tool_center_preserves_requested_rotary_endpoint.c)
enables RTCP through its registered M851 handler with zero rotation centers,
then asks the public segmenter for a C=90 degree move at XYZ=0. The move emits
one segment, but its C endpoint remains0 instead of90. Linear coordinates stay
zero. [Short-move control](cases/rtcp_ac/short_rotary_move_keeps_one_segment_and_exact_endpoint.c)
starts one millimeter off-center and reaches the requested transformed endpoint
in one segment. Existing longer rotary paths continue to exercise interpolation.
Raw sanitizer evidence: `build-asan/rtcp-short-raw.xml` (endpoint assertion).

In `kinematics/rtcp_ac.c`, segment count is based solely on XYZ arc length.
Zero linear distance is clamped to one segment at line308; the sampling cursor
remains0, so the idx==0 branch at line363 chooses s_out=0 before the final-segment
branch can choose1. The commanded rotary delta is therefore discarded.

**Suggested fix for Terje (not applied):** preserve the exact final endpoint for
zero-linear-distance rotary motion, including both rotary axes and subsequent
moves. Keep the correct regression and remove this exact WILL_FAIL/known_bug
block and entry after upstream passes. No CORE changes or sanitizer allowance.

## Failed I/O bank allocation publishes nonexistent ports and reports success

**Confirmed:** 2026-10-22, clean Terje CORE `68eba7906ba60d66c8b55c4adc90cd5e85b5a828`.
[Digital expansion regression](cases/ioports/allocation_failure_digital_bank_preserves_counts_and_allows_retry.c)
starts with two registered inputs/outputs and rejects the new bank's single
calloc. ioports_add_digital returns true and raises both counts to three even
though the provider was not allocated. The [first analog bank regression](cases/ioports/allocation_failure_first_analog_bank_preserves_counts_and_allows_retry.c)
likewise returns true and publishes one input/output without an analog provider.
Both verify the original digital ports still work before the correct failure
assertion. No nonexistent port is dereferenced, so no crash suppression is needed.
Raw evidence: `build-asan/batch73-bank-allocation-raw.xml`.

[Digital registration](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/ioports.c#L1096-L1128)
and [analog registration](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/ioports.c#L1061-L1093)
publish counts, maps and bus metadata in _ioports_add before insert_ports calloc.
When allocation fails, neither rolls that state back nor changes the true result.
This also makes a later retry accumulate another set of phantom ports.

**Suggested fix for Terje (not applied):** make provider allocation and public
port publication transactional: reserve the provider before committing maps and
counts, report failure on allocation errors, and release any unused allocation.
Preserve earlier providers, logical routing and settings metadata. Test successful
retry for first and appended banks as well as ordinary I/O ownership/remapping.

Both exact cases have WILL_FAIL/known_bug in [known_bugs.cmake](known_bugs.cmake).
Keep the correct failure/count/retry assertions. The retry assertions currently
follow the first failing success-result assertion and are not yet validated.
Remove both blocks and this entry once upstream passes under sanitizers.
No CORE edit or sanitizer diagnostic allowance applies.

## Large analog PWM request wraps to minimum duty with 16-bit fast integers

Confirmed 2026-10-23 on clean CORE `50f38659db7b22f4689f3654df2d110d992bcc95`,
Windows LLVM/MinGW with `sizeof(uint_fast16_t) == 2`. Public PWM precomputation
at 10 MHz / 1 kHz gives period10000, input range10..110, duty1000..9000.
A request828 should clamp to9000, matching the ordinary upper-clamp contract.
Instead `ioports_compute_pwm_value` casts the scaled65440, adds minimum1000,
then narrows66440 to904 before clamping (`ioports.c:1181`). The resulting
underflow comparison returns minimum1000, turning an over-range request into
low output. The float conversion65440 fits16bits; only defined unsigned
assignment wrapping is involved, and ASan/UBSan emits no diagnostic.

Regression: `ioports.pwm_large_request_clamps_before_minimum_duty_addition_can_wrap`.
Raw evidence `build-asan/batch74-pwm-wrap-raw.xml` records width2/result1000.
Keep the correct9000 assertion. One exact WILL_FAIL applies only when a CMake
compile check proves `UINT_FAST16_MAX == 65535`; wider integer hosts retain an
ordinary test. No sanitizer allowance or source exclusion is used.

Proposed upstream fix: compare/clamp the scaled floating value including minimum
duty before narrowing it, or bound it in a sufficiently wide intermediate.
After repair retain the test and remove its scoped exception and type check.
CORE is unchanged.

## Filename lookup allocation failure returns the previous job path

Confirmed2026-10-23 on clean CORE `2e165a1ac4c74be8e68971972c6577775d856b05`.
Public `vfs_locate_file("panel.nc")` first returns `/panel.nc` from a mounted
root backend. The next lookup for `workbee_panel_fixture_01.nc` needs a larger
path buffer. If that single realloc fails, lookup returns `/panel.nc` without
checking the requested filename with the backend. Failure must not report a
previously located, different file as the requested result.

[Correct regression](cases/vfs/locate_allocation_failure_does_not_return_previous_job_and_allows_retry.c)
first verifies that allocation failure before any successful lookup returns NULL
without a backend lookup. It then checks one failed allocation after the short
successful lookup (two failures total) and no new backend lookup, then restores
allocation and verifies the full new path and successful second stat before
asserting the failed lookup returned NULL. The final assertion fails with the
stale `/panel.nc` result. This proves an incorrect path result; it does not claim
that any caller opened or executed that file. No private VFS state is modified.
Raw evidence: `build-asan/batch74-locate-allocation-raw-results.xml`.

At `vfs.c:912`, failed `strset` skips rebuilding the path. The final return at933
still reads the static path buffer. On this initial static-to-heap growth,
`strset` falls back to its existing static buffer without clearing its old text
when the requested length cannot be met (`strutils.c:385-419`).

Suggested repair for Terje: return NULL immediately when path allocation fails
(or explicitly clear the result), preserving normal search ordering. Retain
all regression/retry assertions; remove the single exact WILL_FAIL/known_bug
block and this entry once the unchanged case passes. No CORE edit or sanitizer
allowance is included.
