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

## Lathe roughing checks the previous plane when a block selects a new plane

**Confirmed:** 2026-10-23, clean Terje `50f38659db7b22f4689f3654df2d110d992bcc95`
(latest fetched revision). A block's plane selection precedes its motion; the
lathe cycle validator instead reads `gc_state.modal.plane_select` rather than
`gc_block.modal.plane_select` at gcode.c3967. The finishing guard at3948 has the
same source-level issue; executable reproductions below use G71.

- From G17, `G18G71X10Z20Q7F100` returns IllegalPlane instead of accepting the
  selected ZX plane and dispatching the supported driver/plugin interface.
  [Correct acceptance regression](cases/lathe_ngc/roughing_same_block_plane_change_uses_selected_plane_before_dispatch.c).
- From G18, `G17G71X10Z20Q7F100` dispatches the lathe plugin instead of rejecting
  the selected XY plane. [Correct rejection regression](cases/lathe_ngc/roughing_same_block_xy_plane_is_rejected_before_plugin_dispatch.c).

The capture fixture replaces only the documented weak lathe plugin interface;
it does not implement roughing geometry. Standalone plane commands followed by
roughing controls pass. The separate queued-motion rejection scenario covers
all six G71/G72 forms with wrong-plane and missing-Q errors, preserves the
original planner block and subsequently completes exact X/Z motor travel.

**Proposed CORE correction (not applied):** validate the block's selected plane
in both finishing and roughing guards before dispatch. Keep both correct test
assertions. After a fix, remove only their two exact `WILL_FAIL`/`known_bug`
blocks from known_bugs.cmake, run the lathe group and normal delivery gates,
then remove this resolved entry. No sanitizer diagnostic allowance applies.

## Known coverage gaps

These are tracked placeholders for missing or inaccessible implementation, not
executable bug reproductions. They are **known uncovered**, not covered code.
They do not create synthetic CTest failures, increase test counts, exclude source
or change the coverage denominator. Existing public rejection tests still run.
`WILL_FAIL` is reserved for a runnable regression with a meaningful assertion.

**Reviewed:** 2026-10-23, clean Terje `50f38659db7b22f4689f3654df2d110d992bcc95`.
The successful [exact-source report](https://github.com/petervanderwalt/Unit_tests/actions/runs/39940715358)
measures 17,405/17,714 lines (98.26%) and 12,347/13,800 branches (89.47%).
The 309 uncovered lines include the following known gaps; this table does not
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


## Hidden embedded mounts must reject CWD navigation

**Maintainer contract clarified 2026-10-23:** hidden mounts and files are for
components that registered them; hidden files are accessed by full path only.
Terje plans to block CWD into hidden mounts. This resolves the earlier navigation
policy question; it does not introduce a caller-identity authorization API.

The existing [hidden-only directory](cases/fs_embedded/hidden_only_directory_has_no_visible_entries.c)
and [visible registration](cases/fs_embedded/visible_registration_reveals_previously_hidden_mount.c)
regressions retain their two narrow WILL_FAIL allowances: hidden-only CWD must
reject, while adding a visible asset makes ordinary navigation available.
The [explicit-path hidden read](cases/fs_embedded/hidden_file_remains_readable_by_explicit_path.c)
remains a passing control. CORE50f3865 still permits CWD into the hidden mount.
Remove each allowance when its unchanged rejection assertion passes; preserve
full-path reads and hidden-entry listing suppression. No CORE change applied.

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

**Maintainer discussion,2026-10-23:** this is an invalid-request rejection test,
not a request for hardware to generate2MHz from a1MHz timer. The retained
assertion only requires false for a computed zero-tick period, matching the
helper's documented no-range result. It does not prescribe a minimum of100 or
1,000ticks, nor require support at every other frequency. Minimum useful duty
resolution and low-frequency timer/prescaler selection remain driver/API policy.
Existing50Hz servo controls must remain supported with a suitable timer clock.

**Further maintainer confirmation,2026-10-23:** impossible and unreasonable
periods will be rejected. Retain the rejection assertion. The exact additional
reasonable-period limits are maintainer policy, not thresholds invented by this
suite. Fresh upstream fetch still resolves to50f3865, matching the reproduced
zero-tick result; remove the allowance when the unchanged regression passes on
the updated implementation, rather than treating this statement as test evidence.

Proposed narrow repair for Terje: reject a computed zero-tick period before
reporting success. Any broader frequency/resolution limits need a separate
agreed contract. Preserve the driver's existing on/off fallback. Remove the named
allowance once the unchanged rejection assertion passes. CORE is unchanged.

## Named file without matching ENDSUB returns success after prescan

Confirmed 2026-10-23 on clean CORE `50f38659db7b22f4689f3654df2d110d992bcc95`.
Maintainer clarification requires scanning a named file for its matching ENDSUB
before executing the body, and rejecting the file when that terminator is absent.
The body is correctly suppressed during this scan. However, `onNamedSubEOF` in
`ngc_flowctrl.c` closes/unwinds the file and returns the incoming successful status
without rejecting the missing terminator.

Regression: `ngc_flowctrl.named_file_without_end_sub_rejects_without_executing_body`.
It retains the required flow-control syntax error, no body side effects and no
caller continuation after rejection. One exact WILL_FAIL records the missing
error; no sanitizer allowance is needed. Raw evidence is
`build-asan/named-prescan-contract-results.xml`.

Proposed upstream fix: diagnose EOF while the named-file prescan still awaits its
matching ENDSUB, preserving the existing scan-before-execution behavior. Do not
execute the body on the first pass. Retain the test and remove its allowance
when rejection is implemented. CORE is unchanged.

## CONTINUE to an absent loop label reads before the flow stack

Confirmed 2026-10-23 on clean CORE `50f38659db7b22f4689f3654df2d110d992bcc95`.
Inside O10 WHILE, O99 CONTINUE exhausts the stack while searching for its target.
`ngc_flowctrl.c:628` compares the next label before checking whether stack_pull
has left a valid stack index, reading stack[-1]. ASan reports a global buffer
read overflow, preceded by UBSan index -1, instead of a flow-control syntax error.

Regression: `ngc_flowctrl.continue_to_missing_loop_label_reports_syntax_without_reading_past_stack`.
Correct syntax-error and untouched-body assertions remain. Sanitized builds use
one exact fatal-diagnostic wrapper, source line/function and preceding UBSan
matched in `tests/known_sanitizer_diagnostics.json`; no other fault is accepted.
Raw evidence: `build-asan/batch74-continue-missing-raw.xml`. Assertions after the
fatal read cannot execute until repaired. Ordinary builds retain the ordinary test.
Proposed upstream fix: validate stack index before each target-label comparison;
retain the regression and remove the sanitizer allowance after repair. CORE is unchanged.

## Arc bounding box can omit an out-of-range Y endpoint

Confirmed 2026-10-23 on clean CORE `50f38659db7b22f4689f3654df2d110d992bcc95`.
The real parser, arc segment generator, planner and stepper accept these exact
radius5 arcs with XYZ soft limits enabled and a homed envelope of -50..0mm:

- From X-6 Y-0.5, `G2X-13Y0.5I-4J-3F100` emits an endpoint at Y+0.5mm
  (motor counter+40), without a soft-limit alarm.
- From X-6 Y-49.5, `G3X-13Y-50.5I-4J3F100` emits an endpoint at Y-50.5mm
  (motor counter-4040), without a soft-limit alarm.

Both starts are reached through ordinary G0 commands. The 3-4-5 geometry is exact;
this is not a radius-roundoff or private-state injection reproduction. The host
fixture supplies the normal homed soft-limit envelope and observes actual steps.

In `machine_limits.c:785-795`, the non-extremum lower-Y bound uses max of the
endpoints, while the upper-Y bound uses min. This can exclude the offending end.
`mc_arc` marks the accepted arc target validated/valid; its segments then bypass
individual soft-limit checks in `mc_line`, so the final out-of-range move executes.

Correct regressions retain Alarm_SoftLimit and no arc-step assertions:
`motion_control.clockwise_arc_rejects_endpoint_above_y_limit_before_emitting_steps`
and `motion_control.counterclockwise_arc_rejects_endpoint_below_y_limit_before_emitting_steps`.
Each has one exact WILL_FAIL/known_bug, with no sanitizer diagnostic allowance.
Raw evidence: `build-asan/batch74-arc-endpoint-raw-results.xml` and
`build-asan/batch74-lower-arc-endpoint-raw-results.xml`. Six existing independent
sampled-geometry cases now also cover short same-quadrant arcs with valid endpoints
and remain ordinary passing controls; their original full-circle cases remain.

Proposed upstream fix: include both endpoints in the bounding rectangle, using
min for the non-extremum lower-Y bound and max for the upper-Y bound. Verify all
planes, directions and crossed extrema. Retain the regressions and remove only
their two allowances after repair. CORE is unchanged.

## Mismatched numeric ENDSUB accepts another subroutine's record

**Confirmed2026-10-23, clean CORE50f38659db7b22f4689f3654df2d110d992bcc95.**
[Real-file regression](cases/ngc_flowctrl/file_subroutine_with_mismatched_endsub_rejects_before_body_and_restores_sender.c)
streams `O10SUB`, a skipped body assignment, then `O20ENDSUB` and a tail
assignment. Label20 has never been defined. Expected syntax-error termination
instead returns success and executes the tail: status0/body0/tail7. The correct
syntax-error, suppressed-tail and restored-sender assertions remain. One exact
WILL_FAIL; no sanitizer or timeout allowance. Raw evidence:
build-asan/batch74-endsub-mismatch-raw-results.xml.

`sub_get` in ngc_flowctrl.c249-260 returns the final list node on a failed
label/file match rather than NULL. The ENDSUB handler therefore takes that
unrelated record instead of its explicit syntax-error arm at687. A version with
a subsequent CALL timed out; that consequence is not used as the regression's
acceptance condition and is not separately classified as a confirmed hang cause.

Proposed repair for Terje: return NULL when the search exhausts without a matching
label/file, retaining matching-label behavior and the existing error path. No
CORE edits. After repair retain this bounded regression, remove its allowance,
and validate normal numeric subroutine definitions/calls and file recovery.

## Rejected auxiliary reverse nudge changes the running motor direction

**Confirmed2026-10-23, clean CORE50f38659db7b22f4689f3654df2d110d992bcc95.**
[Public auxiliary motor regression](cases/stepper2/rejected_reverse_nudge_preserves_running_finite_move.c)
accepts a20step forward move, emits its first forward pulse, then requests a
one-step reverse nudge at the same speed. The nudge returns false (documented as
command not accepted), without immediately emitting a step. The next driver
pulse nevertheless has the reverse direction bit. The correct forward-direction
assertion fails deterministically on pulse2; endpoint preservation assertions
remain after it and are not reached. No private motor state or IRQ race is used.
Raw evidence: build-asan/batch74-stepper-reject-raw-results.xml.

`st2_motor_move` writes motor->dir and calls the speed/step-profile mutators before
its one-step busy check (stepper2.c350-366). Returning false does not undo those
changes. One exact WILL_FAIL preserves the correct direction/endpoint assertions;
no sanitizer, timeout or broader failure allowance. Normal completed forward/
reverse finite motion remains an independent passing control.

Suggested repair for Terje: decide whether the nudge can be accepted before
changing the active direction/profile, or preserve the accepted move when
rejecting. Retain the test and remove its allowance once it passes. CORE unchanged.
