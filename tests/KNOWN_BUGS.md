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

## Known coverage gaps

These are tracked placeholders for missing or inaccessible implementation, not
executable bug reproductions. They are **known uncovered**, not covered code.
They do not create synthetic CTest failures, increase test counts, exclude source
or change the coverage denominator. Existing public rejection tests still run.
`WILL_FAIL` is reserved for a runnable regression with a meaningful assertion.

**Reviewed:** 2026-10-23, clean Terje `50f38659db7b22f4689f3654df2d110d992bcc95`.
The successful [exact-source report](https://github.com/petervanderwalt/Unit_tests/actions/runs/39903031655)
measures 17,375/17,714 lines (98.09%) and 12,235/13,800 branches (88.66%).
The 339 uncovered lines include the following known gaps; this table does not
claim that every remaining line is unavailable.

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
| Delayed-task fallback search | Defensive/unreachable under supported single-core IRQ masking: task_get_due returns the selected head with IRQs still masked. See [atomic-selection audit](TODO.md#delayed-task-fallback-after-atomic-selection-68eba79). | Reassess if the selection/concurrency contract changes; retain the passing public interrupt/cancellation regressions. |
| Post-reader NaN rejection | Expression reader rejects NaN before this guard; explicit valueless-word NaN is excluded by its M-code type condition (gcode.c1470-1471). See [reader audit](TODO.md#parser-post-reader-nan-guard-audit---2026-10-22). | Revisit if reader or valueless-word contract changes; retain raw coverage. |
| M6 check-mode message cleanup | Nested check-mode branch is enclosed by a guard excluding check mode, with no intervening callback or assignment (gcode.c4231-4238). See [guard audit](TODO.md#m6-check-mode-message-cleanup-guard-audit---2026-10-22). | Revisit after upstream changes the guard or ownership; retain raw coverage. |
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


## Hidden embedded mount directory policy remains unresolved

Two existing hidden-only mount cases still expect chdir rejection on clean
Terje 68eba7906ba60d66c8b55c4adc90cd5e85b5a828. Their named allowances remain
pending confirmation of whether hidden mount metadata controls navigation or
only listing. Ordinary file rejection and root-return regressions now pass;
their allowances were removed. See TODO for the policy distinction.

## Active macro flow error clears scope metadata before closing its file

**Confirmed:** 2026-10-22, clean Terje fab8d1c248990f53f13a444018fbb3ee353061dd.
A real embedded named macro enters a WHILE block after a comment arms one malloc
failure. Failure retaining the loop expression returns FlowControlOutOfMemory.
[ngc_flowctrl.c789-791](https://github.com/terjeio/grblHAL_core/blob/fab8d1c248990f53f13a444018fbb3ee353061dd/ngc_flowctrl.c#L789-L791)
calls ngc_flowctrl_init, clearing subroutine records and stack frames before the
redirect's error/EOF callbacks finish. onNamedSubError and onNamedSubEOF require
that metadata to unwind/close. At actual EOF the named file remains current,
so the protocol repeatedly consumes EOF instead of returning to the sender.

**Regression:** [WHILE allocation recovery](cases/ngc_flowctrl/macro_while_expression_allocation_failure_returns_to_sender_and_retries.c).
**Control:** [normal completion and sender reopen](cases/ngc_flowctrl/macro_while_expression_normal_completion_returns_to_sender_and_reopens.c).
The shared fixture runs actual RAM/embedded file streams through protocol_main_loop;
a public comment callback arms one allocation failure immediately before WHILE.
A global EOF observer runs after the CORE named-sub EOF handler and checks that
its owned file is no longer current. This makes the fault an immediate ordinary
assertion, rather than relying on a timeout. Sender query/retry, parent#1=99 and
skipped caller tail assertions remain for validating a fix. With injection off,
the same fixture completes both calls, counts four loop iterations and restores
the caller. No synthetic EOF, private queue manipulation or firmware patch.

Raw ASan/UBSan evidence: batch72-while-allocation-raw.xml (failure plus passing
control). One named WILL_FAIL/known_bug allowance is in known_bugs.cmake; no new
sanitizer allowance. **Suggested fix for Terje (not applied):** coordinate named
redirect unwinding with flow reset before discarding the metadata needed by the
error/EOF handlers, preserving parent error propagation. Keep the regression and
control, remove its allowance and this entry when clean source passes both plus
related macro-loader/scope tests under sanitizers.

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

## M72 misses saved feed/rapid percentages when enable flags are unchanged

**Confirmed:** 2026-10-22, clean CORE `68eba7906ba60d66c8b55c4adc90cd5e85b5a828`.
[Regression](cases/ngc_params/m72_restores_override_percentages_when_enable_flags_are_unchanged.c)
saves80% feed/50% rapid with M70, changes them through public plan_feed_override
to65%/25%, then executes M72. Both modal/runtime override-enable flags remain
unchanged. M72 returns success but leaves65%/25%, instead of restoring80%/50%.
The snapshot is released before the correct failing percentage assertion.
Raw ASan/UBSan evidence: build-asan/modal-percentage-raw.xml.

[Action selection](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/gcode.c#L583)
sets M9 only when override-control flags differ. Both the direct restore and
parser M72 percentage restoration are gated on M9 (gcode.c606-607/4382-4385),
so percentage-only changes are skipped. Existing flag-change controls pass;
scoped direct restore also passes while retaining its parent snapshot.

**Suggested fix for Terje (not applied):** include saved/current feed and rapid
percentage differences when selecting restoration work, preserving enable policy
and planner update semantics. Keep this correct regression, remove its exact
WILL_FAIL/known_bug block and this entry once upstream passes under sanitizers.
One new named allowance; no sanitizer suppression or CORE modification.

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

## Flow syntax errors orphan an active named macro file

**Confirmed:** 2026-10-22, clean CORE `68eba7906ba60d66c8b55c4adc90cd5e85b5a828`.
[Bounded regression](cases/ngc_flowctrl/named_macro_flow_syntax_error_closes_file_before_status_returns.c)
opens a real named macro with CALL, encounters a SUB with a different named
label, then reports the returned FlowControlSyntaxError through the installed
status handler. The local argument scope returns to its caller, but the macro
file and redirected reader remain installed. The test captures this ownership
failure, releases the orphan for cleanup, then retains the correct assertion
that the error handler should have closed it. Raw evidence:
`build-asan/macro-flow-error-raw.xml` (closed_on_error assertion).
The valid same-label SUB header is covered by the existing successful CALL/EOF
control. Generic parser-error cleanup remains separately tested.

`ngc_flowctrl.c:789-790` clears all sub records and flow frames on this syntax
error before the installed `onNamedSubError` sees it. That handler only closes
named files through a surviving frame/sub lookup (lines395-419), so it can no
longer identify the redirected file. Its EOF handler has the same frame guard.
The full-protocol malformed-header reproduction is retained as an unregistered
[proposal](proposals/named_macro_wrong_sub_header_unwinds_scope_and_skips_both_tails.c):
it reaches a repeat-EOF timeout15.03s rather than returning to the sender.

**Suggested fix for Terje (not applied):** preserve ownership until named-file
error unwinding completes, or close the corresponding files while clearing the
frames. Validate nested files, parameter restoration, and sender recovery. Keep
the bounded regression; remove this exact WILL_FAIL/known_bug block and entry
when upstream passes, then promote the full-protocol proposal if it terminates
with the intended error. No CORE edits or sanitizer diagnostic allowance.

## Spindle override task-pool fallback leaves stale ramp state

**Confirmed:** 2026-10-22, clean Terje CORE `68eba7906ba60d66c8b55c4adc90cd5e85b5a828`.
[Regression](cases/spindle_control/full_task_pool_override_fallback_allows_later_ramped_retarget.c)
starts a registered PWM spindle at 6000 RPM with a 500 ms ramp, fills the public
scheduler with future plugin tasks, then requests 150 percent override. The
unschedulable ramp correctly falls back immediately to 9000 RPM. After releasing
the plugin tasks, requesting 100 percent should ramp from the actual 9000 RPM
output back to 6000 RPM. Instead it immediately writes 6000 RPM.

`spindle_ramp_override` sets `ramp->delay` and `ramp->rpm` before scheduling.
When `task_add_delayed` fails in [spindle_ramp_override](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/spindle_control.c#L623-L639), the ordinary fallback
updates the hardware but leaves delay nonzero and the ramp RPM at 6000. The next
request treats that stale value as an active ramp, computes a zero change and
falls back immediately again. No private state is written by the test; pool
pressure and release use task_add_delayed/task_delete. Raw evidence:
`build-asan/batch73-ramp-pressure-raw.xml`, failed assertion at the second request.

**Suggested fix for Terje (not applied):** clear the pending-ramp marker when
scheduling fails so a later request starts from the current overridden RPM.
Keep immediate fallback and the registered spindle enabled. Validate task-pool
pressure, normal retarget, stop cancellation and configured ramp timing.

The exact test has WILL_FAIL/known_bug in [known_bugs.cmake](known_bugs.cmake).
Keep its correct output/timing assertions; remove that block and this entry when
upstream passes under sanitizers. No sanitizer exception or CORE edit applies.

## RAM upload truncation keeps previously buffered commands

**Confirmed:** 2026-10-22, clean Terje CORE `68eba7906ba60d66c8b55c4adc90cd5e85b5a828`.
[Regression](cases/fs_ram/truncate_pending_upload_discards_old_bytes_before_replacement.c)
opens a writable RAM job, writes `G1X99`, successfully truncates to zero, then
writes replacement `G1X1` and closes it. A fresh reader gets both commands
(11 bytes) instead of only the replacement (5 bytes). All operations use public
VFS APIs, valid handles and ordinary writable-file lifetime. No execution of the
stale motion is needed to prove that the stored job is wrong.

[fs_truncate](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/fs_ram.c#L237-L249)
clears committed data/position/length but leaves the pending txbuf length and
cursor untouched. A small upload has no committed data yet, so the operation
returns success without discarding any buffered bytes. Closing the writer later
flushes the old and replacement commands together. Raw evidence:
`build-asan/batch73-file-resources-raw.xml`.

**Suggested fix for Terje (not applied):** on successful truncate-to-zero, clear
pending txbuf length and reset its cursor to the buffer start as well as clearing
committed data. Verify pending-only and committed-plus-pending uploads, rewrite,
close/readback and existing allocation-failure recovery under sanitizers.

The exact regression has WILL_FAIL/known_bug in [known_bugs.cmake](known_bugs.cmake).
Retain its correct replacement-content assertions; remove that block and this
entry once upstream passes. No sanitizer allowance or CORE edit applies.

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

## Full asynchronous RTU queue silently drops accepted requests

**Confirmed:** 2026-10-23, clean Terje CORE `68eba7906ba60d66c8b55c4adc90cd5e85b5a828`.
[Regression](cases/modbus_rtu/full_async_queue_reports_backpressure_and_preserves_accepted_requests.c)
submits an ordinary burst of valid asynchronous reads before polling. All16
modbus_send calls return true, but the registered RTU transport sends only7
requests and delivers only7 successful replies; no rejection or exception is
reported for the other9. The bounded driver then polls1000ms, well past all
reply/silence deadlines, so no accepted transaction remains merely pending.
Raw evidence: `build-asan/batch73-rtu-backpressure-raw.xml`.

[Queue admission](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/modbus_rtu.c#L329-L336)
skips add_message when the ring is full but still returns !block, which is true
for asynchronous callers. This turns queue exhaustion into reported success
without a transmitted request or completion callback. Existing upper-level
Modbus code treats a false transport result as rejection, so success cannot
communicate backpressure to a driver trying to retry.

**Suggested fix for Terje (not applied):** return false when asynchronous queue
admission fails, preserving already queued requests and callback ownership.
Validate a burst, ordered successful replies, explicit rejection on exhaustion
and retry after draining; retain abort/flush and blocking-transaction controls.

The exact case has WILL_FAIL/known_bug in [known_bugs.cmake](known_bugs.cmake).
Keep the accepted-versus-completed assertion and the subsequent backpressure/
retry assertions (currently not reached after the first failure). Remove its
block and this entry when upstream passes under sanitizers. No CORE edit,
timeout allowance or sanitizer diagnostic suppression applies.

## Delta auxiliary-axis command advances parser but emits no motor steps

**Confirmed:** 2026-10-23, clean Terje CORE `68eba7906ba60d66c8b55c4adc90cd5e85b5a828`.
[Real-boot regression](cases/boot_delta_aux/streamed_auxiliary_move_preserves_delta_joints_and_reaches_a_endpoint.c)
builds DELTA_ROBOT=1,N_AXIS=4, boots with physical NVS and normal driver setup,
then streams G91G1A1F100. The sender acknowledges success and parserA becomes1,
but the auxiliary driver never wakes and A remains0steps instead of80.
[Same-configuration control](cases/boot_delta_aux/streamed_delta_cut_keeps_auxiliary_motor_stopped.c)
passes: Z-0.5 moves allthree delta joints5steps while auxiliaryA remains stopped.
CORE explicitly has N_AXIS>3 travel-limit handling, so this is an exposed
configuration, not a forged axis state. Raw evidence: build-asan/batch73-delta-aux-raw.xml.

[delta_segment_line and transforms](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/kinematics/delta.c#L125-L295)
only transform/copy XYZ joint coordinates. The static motor target's extra axis
remains zero instead of preserving the requested auxiliary coordinate. Forward
conversion likewise does not copy coordinates beyond the three transformed axes.

**Suggested fix for Terje (not applied):** preserve unchanged auxiliary coordinates
in both transform directions and segmented targets; retain XYZ geometry and
apply configured auxiliary limits independently. Verify auxiliary-only and mixed
motion, unchanged joints, encoder-independent pulse counts and Cartesian reports.
The exact endpoint case has WILL_FAIL/known_bug in [known_bugs.cmake](known_bugs.cmake).
Retain its correct80-step/endpoint assertion and the passing XYZ control; remove
the block and this entry when upstream passes. No CORE edits or sanitizer allowance.
Delta source is unchanged in newly fetched50f3865; latest-source runtime recheck pending.

## Named file CALL skips its body and fails to restore caller scope

Confirmed 2026-10-23 on clean CORE `50f38659db7b22f4689f3654df2d110d992bcc95`, after passing on `68eba79`. The new `NGCFlowCtrl_Call` path sets `skip_sub = o_label > NGC_MAX_PARAM_ID` after repositioning the opened named file. Ordinary body statements and RETURN are consequently skipped; EOF can leave the call frame active. The real RAM/embedded protocol fixtures observe missing assignments, missing modal changes, or incorrect error/scope restoration. Existing direct file lifecycle controls also fail to close the named file. No fixture or assertion was weakened.

Exact affected regressions (26 individually scoped WILL_FAIL entries):

- `ngc_flowctrl.embedded_named_loop_reopens_child_file_and_preserves_parent_arguments`
- `ngc_flowctrl.embedded_named_macro_can_be_reopened_for_independent_calls`
- `ngc_flowctrl.embedded_named_macro_empty_file_restores_scope_and_resumes_caller`
- `ngc_flowctrl.embedded_named_macro_eof_restores_real_ram_caller_and_local_argument`
- `ngc_flowctrl.embedded_named_macro_m71_disarms_automatic_modal_restore`
- `ngc_flowctrl.embedded_named_macro_m73_restores_modals_on_real_file_eof`
- `ngc_flowctrl.embedded_named_macro_message_is_visible_before_caller_completion`
- `ngc_flowctrl.embedded_named_macro_nested_files_restore_each_local_scope`
- `ngc_flowctrl.embedded_named_macro_nested_m73_restores_each_file_modal_scope`
- `ngc_flowctrl.embedded_named_macro_nested_parser_error_unwinds_both_file_scopes`
- `ngc_flowctrl.embedded_named_macro_parser_error_unwinds_and_suppresses_callers_tail`
- `ngc_flowctrl.embedded_named_macro_return_value_skips_tail_and_restores_caller`
- `ngc_flowctrl.embedded_named_recursion_can_be_called_again_after_complete_unwind`
- `ngc_flowctrl.embedded_named_recursion_restores_each_callers_local_argument`
- `ngc_flowctrl.embedded_named_recursion_returns_to_numeric_subroutine_scope`
- `ngc_flowctrl.embedded_named_recursive_m73_restores_each_modal_frame`
- `ngc_flowctrl.embedded_named_recursive_parser_error_unwinds_all_file_scopes`
- `ngc_flowctrl.embedded_named_recursive_return_preserves_outer_return_value`
- `ngc_flowctrl.macro_while_expression_normal_completion_returns_to_sender_and_reopens`
- `ngc_flowctrl.named_macro_end_sub_preserves_subroutine_callback_lifetime`
- `ngc_flowctrl.named_macro_return_closes_file_and_restores_caller_scope`
- `ngc_flowctrl.named_macro_return_preserves_subroutine_callback_lifetime`
- `ngc_long_names.long_named_macro_parser_call_and_return_restore_caller_scope`
- `ngc_params.named_macro_parser_error_restores_call_level_for_sender`
- `ngc_params.named_macro_return_restores_parser_visible_call_level`
- `ngc_params.recursive_named_macro_uses_call_level_to_bound_recursion`

Evidence: `build-asan/batch73-latest-full-results.xml` (full 4,196-case ASan/UBSan gate). Proposed upstream repair: enter a named file body with execution enabled and unwind its own call frame on EOF/RETURN; preserve numeric SUB scanning semantics. Remove each allowance only after its unchanged executable passes, including nested/error/reopen controls. CORE is untouched.

## Rejected startup-line comment stores through a null message pointer

Confirmed 2026-10-23 on CORE `50f38659db7b22f4689f3654df2d110d992bcc95`. Public `$N0=G91(Keep Case)` with a registered comment callback returning `Status_UserException` reaches `system.c:775`, which deliberately passes NULL for the optional message output. The new rejection cleanup in `gc_normalize_block`, `gcode.c:1154`, unconditionally writes `*message = NULL`, causing a null store instead of returning the plugin error.

Regression: `system.startup_comment_rejection_preserves_saved_line_and_allows_retry`. Correct assertions require the error, preservation of saved G90 and successful later retry. They remain after the fault and are not reached today. The accepting-plugin companion passes. Raw evidence: `build-asan/batch73-startup-comment-raw.xml`. One exact crash wrapper checks function/source and UBSan line1154 plus the null-store diagnostic. Uninstrumented builds require the exact callback-stage marker and SIGSEGV/access-violation exit, rejecting ordinary assertions, successful fixes and unrelated output. Windows ASan may omit source line information; its preceding UBSan location remains mandatory.

Proposed upstream fix: guard the optional message output before clearing it on comment rejection. Remove the named exception, wrapper registration and manifest entry once the unchanged test passes under instrumented and ordinary builds. No CORE changes.

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

## PWM precomputation reports success for a zero-tick period

Confirmed 2026-10-23 on clean CORE `50f38659db7b22f4689f3654df2d110d992bcc95`.
`ioports_precompute_pwm_values` documents false when no PWM range is possible,
so the driver can fall back to on/off control. At timer clock1MHz, requested
frequency2MHz and otherwise valid input/duty ranges, it instead returns true
with period0, minimum0 and maximum0. `ioports.c:1152` truncates clock/frequency
to zero, while the return at1166 checks only the analog input range.

Regression: `ioports.pwm_frequency_above_timer_clock_reports_no_range_and_allows_valid_retry`.
Correct `!ready` assertion is retained with one named WILL_FAIL, no sanitizer
allowance. Evidence `build-asan/batch74-pwm-frequency-raw.xml` records
ready1/period0/min0/max0. Later assertions require a valid1kHz configuration to
recover normal PWM; they are not reached while this defect remains. Existing
ordinary precompute/midpoint controls cover that valid configuration separately.

Proposed upstream fix: reject a nonpositive or unrepresentable timer period and
any computed duty range with no usable span before reporting success. Keep
valid on/off fallback semantics. Remove the named allowance and retain regression
once fixed. CORE is unchanged.
