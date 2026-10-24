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

## Blocking Modbus CRC failure reports NoException to its error callback

Confirmed 2026-10-24 on clean CORE `2e165a1ac4c74be8e68971972c6577775d856b05`.
A blocking RTU read with CRC checking and no retries receives a normal-length
reply with one corrupted CRC byte. The call correctly returns false and invokes
its exception observer once, but reports0 (`ModBus_NoException`) instead of254
(`ModBus_CRCError`). The asynchronous CRC control reports the correct CRC code.

[Regression](cases/modbus_rtu/blocking_crc_error_reports_crc_code_and_allows_next_request.c)
uses the existing registered serial fixture, actual CRC calculation and public
`modbus_send`. Before its final correct CRC-code assertion, it proves one failed
request, no receive callback for corrupt data, and successful next request with
one valid response and expected address/function/data bytes. No transport lockup,
corrupt data acceptance or sanitizer fault is claimed. Exactly one named
`WILL_FAIL`/`known_bug` applies in [known_bugs.cmake](known_bugs.cmake).

Source: [CRC detection](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/modbus_rtu.c#L212)
sets `ModBus_Exception` for blocking requests but does not assign the CRC error
to the stored exception code. The [blocking dispatcher](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/modbus_rtu.c#L295)
passes that stored code to the observer. Review assigning the CRC code for that
path; CORE is unchanged here. Keep the assertions and remove the allowance and
this entry after a fixed source passes sanitizer validation and recovery controls.

## Acknowledged tool-zero G43 retains the previous tool offsets

Confirmed 2026-10-24 on clean CORE `2e165a1ac4c74be8e68971972c6577775d856b05`.
The existing asynchronous changer fixture first completes `T1M6G43H1` through
public cycle-start acknowledgement and applies its table offsets (2,3,4 mm).
`T0M6G43` then defers tool0's zero table offsets while waiting. After the same
public acknowledgement, the current tool becomes0 and the change notifications
complete, but the old offsets remain (2,3,4 mm). No motion or physical collision
claim is made. The immediate `G49` recovery correctly clears all three offsets.

[Regression](cases/gcode/m6_unloading_tool_with_g43_clears_previous_offset_after_sender_ack.c)
retains the correct zero-offset assertion after checking both change callbacks,
idle state, released change flag, zero table entry and successful G49 recovery.
The failure is deterministic with no sanitizer diagnostic. Exactly one named
`WILL_FAIL`/`known_bug` entry applies in [known_bugs.cmake](known_bugs.cmake).
The omitted-H tool1 control passes using the same driver and public handshake.

Source: [deferred selection](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/gcode.c#L4310)
stores pending0, but [completion](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/gcode.c#L996)
applies offsets only for pending values greater than0. Review valid tool0 versus
the -1 sentinel during acknowledgement; CORE is not changed here. Once fixed,
retain the regression, remove its exact allowance and delete this entry after
sanitizer validation confirms offset application and recovery.

## Pendant release fails to restore a network-only controller's null console

Confirmed 2026-10-24 on clean CORE `2e165a1ac4c74be8e68971972c6577775d856b05`.
A controller uses the public null console as its base, connects then disconnects
a network client, and enables a registered serial pendant. Disabling pendant
control returns success and clears `sys.mpg_mode`, but does not restore the
original reader/writer, clear `hal.stream.state.is_mpg`, disable pendant RX or
restore its previous realtime handler. The pendant remains attached while the
public system mode says control has been released. No unintended motion is
claimed; the regression does not send motion through this mismatched state.

[Regression](cases/stream/mpg_disable_after_network_disconnect_restores_null_console.c)
uses `stream_null_init`, normal connect/disconnect, real pendant registration
and public enable/disable calls. Before its final correct restoration assertions,
an independent network reconnect and output check succeed. Raw sanitizer run
logs `reader=0 writer=0 mode=0 rx=0 handler=0`, without sanitizer diagnostics.
Existing serial-base pendant-release and network-only reconnect controls remain.

Cause: [stream.c829-850](https://github.com/terjeio/grblHAL_core/blob/2e165a1ac4c74be8e68971972c6577775d856b05/stream.c#L829)
uses `org_stream.type == StreamType_Null` as the empty-backup marker, although
`StreamType_Null` is also a valid original console. The disable guard at847
therefore skips restoring a legitimately saved null stream.

Suggested maintainer repair: track whether a stream backup exists separately
from its stream type, and restore valid null-console backups through the same
handler/RX restoration path. No CORE change is included here.

Exception: one exact `WILL_FAIL`/`known_bug` entry in
[known_bugs.cmake](known_bugs.cmake). Remove only that entry when the unchanged
regression passes; retain serial, null-console, reconnect and pendant controls.
No sanitizer allowance is added. Raw evidence:
`build-asan/batch74-null-console-release-raw-results.xml`.

Upstream b01f481 retest2026-10-24 restores reader, writer, mode and realtime
handler, but pendant RX remains enabled (rx=0 in restoration diagnostic).
The correct receiver-restoration assertion still fails. Keep the allowance
for this remaining observable release failure.

## Supported 32-channel free-port scan reads beyond its map

Reconfirmed 2026-10-24 on clean upstream CORE `b01f481072edecac33d5e40c25869359a5b3fa1f`.
The public full-bank regression still reaches index32 when a free-port query
searches for the terminating null pin; ioports.c696 reads map[32] before
validating that index. UBSan reports index32 out of bounds for uint8_t[32].
The same upstream update repaired signed input/output bus-mask shifts. Those
obsolete diagnostic patterns are removed; only the exact remaining bounds
pattern is allowed in known_sanitizer_diagnostics.json.

[Regression](cases/ioports_32/full_bank_registers_p31_and_routes_highest_channels.c)
retains correct channel31 registration, counts, ownership and routing assertions.
Its affected-module output is in upstream-b01-affected-raw-results.xml. Keep the
single known_sanitizer_bug label until the unchanged regression has no bounds
diagnostic; then remove its manifest entry and this section. No CORE edits.

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

Upstream b01f481 retest2026-10-24: both disable bits now clear, but the
secondary output remains7000 instead of8400 while primary reaches3300. The
same correct output assertion still fails; retain the exact allowance until
both driver outputs match their restored overrides.

## Known coverage gaps

These are tracked placeholders for missing or inaccessible implementation, not
executable bug reproductions. They are **known uncovered**, not covered code.
They do not create synthetic CTest failures, increase test counts, exclude source
or change the coverage denominator. Existing public rejection tests still run.
`WILL_FAIL` is reserved for a runnable regression with a meaningful assertion.

**Measured:** 2026-10-24, clean Terje `2e165a1ac4c74be8e68971972c6577775d856b05`.
The successful [exact-source report](https://github.com/petervanderwalt/Unit_tests/actions/runs/40074304720)
measures 17,483/17,756 lines (98.46%) and 12,737/13,834 branches (92.07%).
The 273 uncovered lines include the following known gaps; this table does not
claim that every remaining line is unavailable. See the complete measured
[line/branch inventory](COVERAGE_GAPS.md) before selecting the next workflow.

| Region | Status and evidence | What makes it testable |
|---|---|---|
| VFS lookup/rename residual guards | Two native routing guards: valid chdir lookup returns cwd/root; cross-mount rename rejects before its second notification. Separate NULL-path fallbacks remain unclassified. [Source audit](TODO.md#verified-residual-guards-vfs-lookuprename-and-virtual-parameter-root). | Upstream changes lookup or cross-mount rename semantics. |
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


Upstream b01f481 retest2026-10-24 fixes initial lookup allocation handling,
but a later growth failure after a successful lookup still returns /panel.nc.
Retry succeeds; the final rejected-path assertion remains false. Retain this
exact allowance for stale-path reuse rather than classifying the whole fix done.

## Manual auxiliary homing rewrites stationary delta joint coordinates

Confirmed2026-10-24 on clean CORE `2e165a1ac4c74be8e68971972c6577775d856b05`,
supported four-axis delta configuration with three automatic XYZ home switches
and a manually referenced auxiliary A axis. Complete actual XYZ homing, enable manual
homing with the public $22 setting, then issue $HA. Both homing events succeed
and the homed mask becomes15. No motor pulse occurs during manual A referencing,
but all three stored delta joint counters change from0 to-6 steps at1000steps/rad.
A remains at its manually supplied zero.

[Regression](cases/boot_delta_aux/manual_auxiliary_homing_preserves_delta_joint_coordinates.c)
keeps the correct assertion that selecting A must preserve the other three joint
coordinates. Physical pulse counts, automatic XYZ homing, manual A completion,
parser response and absence of command errors are checked before that assertion.
Raw ASan/UBSan evidence: `build-asan/delta-manual-a74-raw-results.xml` reports
`joint0/1/2 before=0 after=-6`, then fails coordinate preservation. This coordinate-preservation
case has its own exact WILL_FAIL/known_bug; no sanitizer allowance or CORE edit.

Native manual homing in motion_control.c marks only the selected manual axis and
calls kinematics.limits_set_machine_positions with that cycle. Delta's callback
at kinematics/delta.c527 ignores its cycle argument and unconditionally rewrites
XYZ using machine.home_angle. A manual A reference therefore changes unrelated
joint coordinates after the previous real homing callback updates that angle.
Suggested upstream repair: honor the selected axis mask and establish auxiliary
coordinates without rewriting stationary XYZ. Keep the unchanged assertion;
remove this entry and its exact allowance once it passes.

The [independent auxiliary retry regression](cases/boot_delta_aux/manually_homed_auxiliary_axis_rejects_outside_jog_and_allows_inside_retry.c)
uses the same real homing sequence, enables $20, verifies that A999 rejects with
TravelExceeded, then requires A-1 to succeed inside the configured[-10,0] travel interval. Current
CORE rejects both jogs: five success acknowledgements instead of six, A remains0
and no A pulse occurs. Every input receives a terminal response and $G remains
usable. Raw evidence: `build-asan/delta-manual-a74-retry-raw-results.xml`.
This second correct outcome has one separate exact WILL_FAIL; its required80
A pulses and-1 parser/physical endpoint assertions remain. The XYZ coordinate
rewrite is directly established; the retry is a separate observed consequence
of this sequence, not a claim that every auxiliary rejection has the same cause.


## Delta soft limits reject a valid cut when a homed auxiliary axis is stationary

Confirmed2026-10-24 on clean CORE `2e165a1ac4c74be8e68971972c6577775d856b05`.
Manually reference A before actual XYZ homing so the separate post-XYZ manual
reference defect is avoided. All four homed bits come from public commands.
A remains at0 inside its configured[-10,0] interval. A normal1mm vertical cut
works with soft limits disabled. Enabling $20 then incorrectly raises SoftLimit
for the next valid1mm vertical cut, despite the auxiliary axis remaining stationary.
The independent mixed-jog control reaches X100/Z-300/A-1 with the same homed
configuration and soft limits enabled.

[Correct regression](cases/boot_delta_aux/valid_cartesian_cut_with_stationary_homed_auxiliary_axis_does_not_raise_soft_limit.c)
requires the first cut to complete, then retains the correct no-false-alarm and
second-cut endpoint assertions. Its public realtime exit only releases the
critical alarm loop for diagnosis; it does not make the alarm acceptable.
Initial raw ASan/UBSan evidence: `build-asan/delta-aux-cut74-raw-results.xml`
reports `soft_limit=1 acks=5 A=0 XYZpulse0=98/98` for the original isolated cut.
Only this exact case is WILL_FAIL/known_bug, with no sanitizer allowance.

G-code4036 leaves target validation pending when soft limits are enabled.
Delta's segmenter passes inverse-transformed motor coordinates to its travel
checker. At delta.c619 the auxiliary check forwards is_cartesian=false to the
original Cartesian checker, which returns false whenever that flag is false
(machine_limits.c698). Auxiliary coordinates themselves are pass-through axes;
forwarding the delta XYZ frame flag makes every such auxiliary check reject.
Suggested upstream repair: check pass-through auxiliary axes in their Cartesian
frame while independently checking transformed XYZ. Preserve the ordinary-cut
and working mixed-jog controls; remove this entry and its exact allowance when
the unchanged cut regression passes. CORE remains unmodified.

Strengthened raw control evidence: `build-asan/delta-aux-cut74-control-raw.log`
confirms the first cut completed (XYZpulse0 increases98->108) before the second
cut falsely alarms, with7 acknowledgements and A0. Classified four-case evidence
is `build-asan/delta-aux74-classified-results.xml`; the independent mixed-jog
control passes with physical/logical motor agreement and a non-cuboid endpoint.


## VFS timestamp path allocation failure loses ENOMEM

Confirmed 2026-10-24 on CORE `2e165a1ac4c74be8e68971972c6577775d856b05`.
The [regression](cases/vfs/utime_path_allocation_failure_preserves_errno_skips_backend_and_allows_retry.c)
uses a valid relative filename under a mounted working directory and rejects only
its path-copy allocation. `vfs_utime` returns -1 but exposes errno 0 instead of
ENOMEM. The backend is untouched, the working directory survives, and a retry
sets the expected timestamp on the expected file. These controls pass before
the retained errno assertion fails. Raw ASan/UBSan evidence:
`build-asan/vfs-utime-errno74-raw-results.xml`.

`parse_path` sets ENOMEM, but vfs.c643 forwards its NULL result to `get_mount`,
whose unconditional errno reset precedes its NULL guard at272. Unlike `vfs_stat`,
`vfs_utime` does not short-circuit on path allocation failure. Suggested repair:
retain the parse error before mount lookup. One exact WILL_FAIL/known_bug, no
sanitizer allowance or CORE changes. Remove the allowance when the unchanged
assertion passes.


## Blocking Modbus reply acknowledges an asynchronous follow-up without queuing it

Confirmed 2026-10-24 on CORE `2e165a1ac4c74be8e68971972c6577775d856b05`.
A successful blocking register-read callback requests the next register through
public modbus_send(..., false). It returns true, but the follow-up never reaches
the UART. There is no queue-pressure or interrupt race: the attempt occurs in
the normal reply observer. A later independent request completes successfully.

[Regression](cases/modbus_rtu/blocking_reply_followup_is_transmitted_if_send_reports_acceptance.c)
checks the first reply bytes, exactly one follow-up attempt, no unsolicited
output, and transport recovery before its correct final assertion. It permits
explicit rejection; a true return requires exactly one transmission and reply.
Raw ASan/UBSan evidence `build-asan/rtu-followup74-raw-results.xml` reports
accepted=1, transmissions=0, and successful independent recovery, then fails
that final assertion. One exact WILL_FAIL/known_bug; no sanitizer allowance.

At modbus_rtu.c329 the asynchronous enqueue guard examines the active packet
against sync_msg, rather than the new request. During the blocking callback
packet points to sync_msg and its function byte is nonzero, so all three terms
are false. Enqueue is skipped, but return !block at337 is true. Suggested
upstream repair: queue the follow-up safely or report refusal explicitly.
Keep the unchanged acceptance/delivery assertion and remove this entry and
allowance once it passes. CORE remains unmodified.


## Modbus register replies from valid high-bit server addresses lose completion

Confirmed 2026-10-24 on CORE `2e165a1ac4c74be8e68971972c6577775d856b05`.
The [serial specification](https://www.modbus.org/file/secure/modbusoverserial.pdf)
section2.2 permits individual server addresses1 through247. Server200 is valid.
A normal function3 register reply from that server is silently discarded by the
common decoder, so modbus_message returns Status_OK without its completion
callback. The same register read at server7 completes before and after it.

[Regression](cases/modbus_rtu/high_bit_server_address_delivers_register_reply_and_preserves_next_request.c)
uses the real registered RTU transport, scheduler and common decoder. Its driver
fixture returns a complete CRC-valid reply with the transmitted server address.
Outgoing frame bytes and CRC are checked; all three replies are consumed, TX3
and zero CRC errors/timeouts are reported, and both server7 controls deliver
register0x1234. Only the correct server200 callback assertion then fails.
Raw ASan/UBSan evidence: `build-asan/rtu-high-address74-raw-results.xml`,
callbacks=0. This replaces the initial decoder-only regression, preserving one
case and one exact allowance. It is host UART-callback evidence, not physical
hardware validation.

modbus.c217 tests msg->adu[0]&0x80, the server address byte, before decoding.
The exception flag belongs to the function byte msg->adu[1]. The wrong byte
therefore drops legitimate replies from addresses128..247. Suggested repair:
classify exception responses by their function field while preserving normal
address bits. Keep the callback/function/value assertions unchanged. One exact
WILL_FAIL/known_bug; remove it and this entry when the unchanged regression
passes. No CORE changes or sanitizer allowance.


## Failed embedded mount changes the unrelated root mount visibility

Confirmed 2026-10-24 on CORE `b01f481072edecac33d5e40c25869359a5b3fa1f`.
Reject the first embedded mount's allocation through the public VFS path. The
mount correctly returns false and emits no mount notification, but changes the
existing root mode from hidden1 to hidden0. Failure must preserve unrelated
mount policy. This establishes a metadata mutation, not a claim of file leakage.

[Regression](cases/fs_embedded/allocation_failure_first_mount_preserves_root_mode_and_allows_asset_retry.c)
uses the normal initial root state and a real embedded asset list. Retry mounts
exactly once; its mount observer can already read the asset. Directory contents
and later reads are correct before the retained root-preservation assertion
fails. Raw ASan/UBSan evidence: `build-asan/analog-embedded-b01-raw-results.xml`,
root hidden1->0. One exact WILL_FAIL/known_bug, no sanitizer allowance.

fs_embedded.c252 correctly clears the asset pointer when vfs_mount fails, but
the later !all_hidden arm still calls vfs_mount_set_mode("/embedded", ...).
That API resolves the absent path to the root mount and updates its mode.
Suggested upstream repair: change embedded visibility only after a successful
mount/append, preserving other mount metadata on failure. Keep the regression
and remove only its allowance and this entry when unchanged assertions pass.
No CORE edits.


## Linux Clang tapping argument handoff reads beyond its offset table

Confirmed 2026-10-24 on CORE `b01f481072edecac33d5e40c25869359a5b3fa1f`,
hosted run40082861198, harness7bf1306. The correct eight-axis tapping handoff
regression reaches macro_arguments_push at gcode.c485 with index27 for its
27-entry offset table. Hosted Clang reports the exact bounds UBSan followed
by an ASan global-buffer-overflow at that function/line. Windows Clang, hosted
GCC sanitizer and GCC coverage execute the assertions successfully.

[Regression](cases/eight_axis/rigid_tapping_fallback_receives_a_axis_arguments_and_restores_caller_scope.c)
retains exact argument/scope/override assertions. Only Linux Clang sanitizer
builds use the diagnostic launcher and WILL_FAIL/known_crash. The manifest
requires index27, const27-entry table, source485, macro_arguments_push, and
the global-buffer-overflow signature. Changed/unrelated faults and absent
diagnostics make that exception red; assertions after the fatal fault are
unvalidated on the reproducing platform. No broad crash acceptance or CORE edit.

The handoff initializes named bitfields of parameter_words_t, then the helper
iterates its full32-bit mask against27 offset entries. Unused/padding bits in
that initialization are a source hypothesis, not a proven exclusive cause.
Upstream should ensure the complete mask is initialized and bound offset
accesses. Remove only this platform-scoped launcher/allowance and manifest
entry after unchanged assertions run without diagnostics. Hosted evidence:
build-asan/hosted40082861198/report-core-clang/logs/clang-test.log.


## Twenty-nine-argument CALL fails to inherit the final caller local

Confirmed 2026-10-24 on CORE `b01f481072edecac33d5e40c25869359a5b3fa1f`;
Terje's master still resolves to that revision at classification.
[Regression](cases/ngc_flowctrl/call_with_twenty_nine_arguments_inherits_last_local_and_restores_caller.c)
uses the real RAM backend and protocol loop. A thirty-argument control receives
#29=29/#30=30; both calls restore caller #1=99/#29=72/#30=73 and the following
root statement executes. The twenty-nine-argument call receives #29 correctly,
but its omitted #30 fails the correct inherited73 assertion. No prescan or
named-file execution-policy change is requested.

The [O-call contract](https://www.linuxcnc.org/docs/html/gcode/o-code.html#_subroutines)
requires omitted arguments through #30 to retain their calling-context values.
CORE's own argument-fill loop implements this contract for shorter calls.
At ngc_flowctrl.c754-760, parsing29 arguments increments param_id to30, then
`param_id < 30` skips the fill loop entirely. The later copy reads the unfilled
params[29] stack slot. Its incidental value is not part of the test contract;
no particular corrupt value or sanitizer diagnostic is required.

Raw sanitizer evidence: `build-asan/call-argument-boundary-raw-results.xml`.
One exact WILL_FAIL/known_bug retains all correct assertions. Suggested upstream
repair: initialize every omitted parameter through30 before pushing scope.
Keep the regression and remove only its allowance and this entry after the
unchanged assertions pass. No CORE edits or sanitizer suppression.


### Additional Linux Clang tapping occurrences - 2026-10-24

Run40093560650 at harness8b189a9/COREb01f481 reproduces the same table read in
spindle_sync.recursive_tapping_macro_overflow_restores_scope_and_allows_next_cut
(index30) and spindle_sync.unsupported_rigid_tapping_preserves_position_and_next_supported_sync_move
(index28). Both diagnostics identify the27-entry table, gcode.c485 and the
macro_arguments_push top frame, followed by ASan global-buffer-overflow. The
existing eight-axis index27 exception reproduced correctly in this run.

Two additional exact test/index entries and Linux-Clang-only launchers retain
all correct assertions; assertions after these crashes remain unvalidated on
that platform. Hosted GCC/coverage and local Windows Clang execute them without
these faults. Different indices, locations or unrelated diagnostics remain red;
no blanket sanitizer acceptance. Remove each entry/launcher/label when its
unchanged regression passes after an upstream fix. No CORE edits.


### Tapping diagnostic varies on the same source - 2026-10-24

Exact-head run40103625282 (harness58774aa, COREb01f481) confirms that this
fault is intermittent across builds. The eight-axis handoff executable exits0
with no diagnostic; its strict expected-diagnostic wrapper therefore correctly
fails. The recursive tapping case now reports index27 at gcode.c485 with the
same27-entry table and macro_arguments_push top frame; run40093560650 reported
index30. The unsupported fallback still reproduces index28 and matches.
Saved evidence: build-asan/hosted40103625282/results-core-clang/build/
known-crash-spindle_sync.recursive_tapping_macro_overflow_restores_scope_and_allows_next_cut.log.

One additional exact recursive-test/index27 manifest entry recognizes that saved
diagnostic. All other test/source/table/function matching remains unchanged;
missing expected diagnostics still fail. Do not force padding/private bits or
weaken the functional assertions to obtain repeatable crashes. Complete mask
initialization remains an upstream source hypothesis. Terje origin/master was
freshly fetched and remainsb01f481. No CORE edits. This run remains failed;
post-crash assertions remain unvalidated on Clang, and no PR-ready claim follows.


### Further observed tapping variants - 2026-10-24

Run40107107939 at harness49b18b0/COREb01f481 reports eight-axis handoff index29
and unsupported tapping fallback index27 at gcode.c485:32, the same27-entry
const offset table and macro_arguments_push top frame, followed by ASan
global-buffer-overflow. Recursive tapping index27 matches its existing entry.
All nine newly authored ordinary workflows pass on Clang; its only two reported
failures are these previously unlisted diagnostic variants.

Two additional exact test/index entries recognize these saved outputs. Production
runner replay and first1024 checks pass; different indices/source lines, missing
diagnostics and zero-exit output remain rejected. No range/wildcard allowance or
matcher implementation change. The hosted run remains failed; post-crash
assertions remain unvalidated. Saved logs are under
build-asan/hosted40107107939/results-core-clang/build/known-crash-<test>.log.


### Tapping diagnostic evidence update - 2026-10-24, run40114356917

[Run40114356917](https://github.com/petervanderwalt/Unit_tests/actions/runs/40114356917)
at harnessd05945e/COREb01f481 passed source/GCC/coverage but failed Clang and
summary. All six newly added normal controller workflows pass Clang individually.
The existing eight-axis tapping handoff reports index28 and unsupported tapping
fallback reports index30 at core/gcode.c485:32, const27-entry offset table,
macro_arguments_push top frame and ASan global-buffer-overflow. Two separate
exact test/index entries record only these actually saved diagnostics. Production
runner replay and first1024 matching pass; changed index/source/table/function
and zero-exit diagnostics reject. Matcher implementation and assertions unchanged.

The recursive tapping regression exited0 with no diagnostic in this build.
Its strict known-crash wrapper correctly remains red: CORE is unchanged and
other builds still reproduce the fault, so this does not prove a firmware fix.
No clean-exit allowance, wildcard/range, forced padding, private-state setup or
new known failure was added. Assertions after fatal faults remain unvalidated.
Do not rerun CI solely for these manifest additions. Saved logs and replay proof:
build-asan/hosted40114356917/results-core-clang/build/known-crash-<test>.log,
verified-exact-diagnostic-replay.json and verified-new-workflows.json.


## Accepted sleep command is ignored while the controller is in alarm

Confirmed2026-10-24 on clean CORE `b01f481072edecac33d5e40c25869359a5b3fa1f`.
With saved forced-initialization alarm and sleep enabled, the normal sender
command `$SLP` is acknowledged `ok` but the controller remains in alarm instead
of entering sleep. The regression allows eight ordinary foreground polls after
acknowledgement, then retains the correct `STATE_SLEEP` assertion. It fails on
that assertion, without a sanitizer fault, read-limit failure or injected state.
The same fixture/control using `$X` before `$SLP` enters sleep, reports Sleep,
resets and explicitly unlocks successfully. It uses normal public commands.

Source cause: [enter_sleep](https://github.com/terjeio/grblHAL_core/blob/b01f481072edecac33d5e40c25869359a5b3fa1f/system.c#L571)
explicitly accepts Idle or Alarm and posts `EXEC_SLEEP`. The
[alarm state](https://github.com/terjeio/grblHAL_core/blob/b01f481072edecac33d5e40c25869359a5b3fa1f/state_machine.c#L352)
installs `state_noop`; state_update dispatches to that handler, so the accepted
sleep request is ignored. The idle handler consumes the same request normally.
CORE remains unchanged. Upstream should make accepted alarm-state sleep requests
reach the sleep transition consistently with the public command's allowed states.

[Regression](cases/boot/sleep_from_forced_startup_alarm_reports_sleep_and_allows_reset_unlock.c)
has one exact `WILL_FAIL`/`known_bug` block in [known_bugs.cmake](known_bugs.cmake).
No sanitizer allowance. Sleep/recovery assertions after the known failure remain
in the case; their common fixture tail is validated by the explicit-unlock control.
Evidence: build-asan/alarm-sleep-regression-raw-results.xml,
alarm-sleep-unlock-control-results.xml and alarm-sleep-verification.json.
After upstream fixes it, retain the case, remove only this expected-failure block
and entry, and verify the complete workflow under ASan/UBSan before cleanup.


### Tapping diagnostic evidence update - 2026-10-24, run40118321363

[Run40118321363](https://github.com/petervanderwalt/Unit_tests/actions/runs/40118321363)
at harnesscf41105/COREb01f481 passed source/GCC/coverage but failed Clang/summary
on one existing recursive tapping diagnostic: index29 at core/gcode.c485:32,
const27-entry table, macro_arguments_push top frame, ASan global-buffer-overflow.
All six new normal workflows pass Clang individually without allowances. One
additional exact recursive-test/index29 entry records only this actual saved
output. Production runner/first1024 replay pass; changed index/source/table/
function, absent diagnostic and zero-exit output reject. No matcher code,
assertion, padding or wildcard/range changes. Earlier clean recursive exits still
remain red; CORE has not changed. Do not rerun CI solely for this data addition.
Evidence: build-asan/hosted40118321363/results-core-clang/build/known-crash-<test>.log,
verified-exact-diagnostic-replay.json and verified-new-workflows.json.
