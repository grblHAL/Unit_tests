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

**Reviewed:** 2026-10-22, clean Terje `68eba7906ba60d66c8b55c4adc90cd5e85b5a828`.
The successful [exact-source report](https://github.com/petervanderwalt/Unit_tests/actions/runs/39823928447)
measures 17,297/17,684 lines (97.81%) and 12,106/13,754 branches (88.02%).
The 387 uncovered lines include the following known gaps; this table does not
claim that every remaining line is unavailable.

| Region | Status and evidence | What makes it testable |
|---|---|---|
| VFS lookup/rename residual guards | Three unreachable lines: lookup always returns cwd/root; cross-mount rename rejects before its second notification. [Source audit](TODO.md#verified-residual-guards-vfs-lookuprename-and-virtual-parameter-root). | Upstream changes lookup or cross-mount rename semantics. |
| G84 helper flag guards | Six false arms are unreachable: both private helper call sites pass every flag enabled. [Caller audit](TODO.md#g84-private-override-helper-flag-guards). | A supported caller uses partial flags. Saved disabled-policy behavior is separately tested. |
| Tab-setting datatype default | All declared public datatypes are handled; Int8/Int16 normalize to Integer. [Source audit](TODO.md#tab-setting-metadata-default-datatype-arm). | A new valid datatype reaches the formatter. |
| Virtual-parameter empty-list registration | Built-in `_value`/`_value_returned` nodes keep the list nonempty. [Source audit](TODO.md#verified-residual-guards-vfs-lookuprename-and-virtual-parameter-root). | A supported lifecycle permits an empty list. |
| Wall-plotter homing helpers | Unimplemented public workflow. [home_machine](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/kinematics/wall_plotter.c#L301) warns and returns false; [existing rejection test](cases/wall_plotter/unsupported_homing_reports_warning.c) passes. The report has 56 uncovered helper lines. | Implement public homing and define its reference/endpoint contract; then test actual motion through that entry point. |
| Native rigid tapping and its downstream execution | Unimplemented extension. [mc_rigid_tapping](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/motion_control.c#L793) is a weak TBC stub returning unsupported. | The real parser/stub rejection path now has a [documented regression](#unsupported-rigid-tapping-reports-success-and-advances-only-parser-position). Native geometry still needs a supported implementation, then encoder/spindle synchronization, reversal and physical endpoint tests. |
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

## Formatting the current drive loses relative-file routing

**Confirmed:** 2026-10-22, clean Terje `fab8d1c248990f53f13a444018fbb3ee353061dd`.
[vfs_drive_format](https://github.com/terjeio/grblHAL_core/blob/fab8d1c248990f53f13a444018fbb3ee353061dd/vfs.c)
writes `/` into the frontend cached directory while leaving the current non-root
mount selected. After formatting `/store`, displayed getcwd is `/store`, but
relative `new.nc` stat returns failure instead of reaching `/store`'s backend.

**Regression:** [current-drive format and relative stat](cases/vfs_integration/formatting_current_drive_resets_removed_subdirectory_to_drive_root.c).
The fixture now supplies the stat callback required before changing directory.
Its format/remount and displayed-directory assertions pass; relative stat fails.
This regression has a named `WILL_FAIL` / `known_bug` allowance in
[known_bugs.cmake](known_bugs.cmake); remove it when relative routing is fixed.

**Reconfirmed on68eba79:** the cache now stores the mount path `/store/`
with its trailing separator. parse_path appends another separator for a relative
file, so the backend receives `//new.nc` rather than `/new.nc`. The fixture now
uses valid frontend-only directories (neither chdir nor getcwd callback), records
the routed name, and asserts it after stat. Evidence: batch72-format-routing.xml
and its strict summary. The earlier `/` cache fault is fixed, but normalization
still fails; keep the existing exception until the backend path is correct.

**Suggested fix for Terje (not applied):** keep frontend absolute directory and
selected mount consistent when resetting the formatted drive to its root.
Retain the relative backend operation assertion and remove this entry once it
passes on clean source under sanitizers.

## MPG select pull-up initialization depends on another input's configuration

**Confirmed:** 2026-10-22, clean Terje fab8d1c248990f53f13a444018fbb3ee353061dd.
[ioports.c1599-1606](https://github.com/terjeio/grblHAL_core/blob/fab8d1c248990f53f13a444018fbb3ee353061dd/ioports.c#L1599-L1606)
places `Input_MPGSelect` handling inside `function < Input_Probe`, but the MPG
function is declared after Input_Probe in crossbar.h. Its forced pull-up branch
is unreachable. The reused in_config then retains the previous input's pull mode,
or its initial None when MPG is configured first.

**Regressions:** [first configured input](cases/ioports/loaded_first_mpg_input_receives_pullup_without_neighbor_state.c)
and [neighbor uses pull-down](cases/ioports/loaded_mpg_input_does_not_inherit_neighbor_pulldown.c).
Both configure valid driver capabilities and pin functions before public bank
registration, then load settings through grbl.on_settings_changed. Neighbor
configuration, callback counts, debounce and inversion controls pass; only MPG
pull-up assertions fail. Existing [up-neighbor control](cases/ioports/loaded_mpg_select_pin_uses_pullup_and_preserves_debounce.c)
passes incidentally because its auxiliary neighbor supplies PullMode_Up.
Evidence: batch72-mpg-pull-raw.xml. Narrow named WILL_FAIL/known_bug allowances
are in known_bugs.cmake; correct assertions remain.

**Suggested fix for Terje (not applied):** handle MPG outside the lower-valued
control-function guard and give each pin a deliberate pull configuration. Retain
both pin-order regressions and the existing control; remove their two allowances
and this entry once clean source passes the I/O settings group under sanitizers.

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

## Rejected parser and plugin blocks lose CORE-allocated messages

**Confirmed:** 2026-10-22, clean Terje fab8d1c248990f53f13a444018fbb3ee353061dd.
A normal MSG comment allocates a message before the public on_pre_gcode_execute
hook. [gcode.c3983-3984](https://github.com/terjeio/grblHAL_core/blob/fab8d1c248990f53f13a444018fbb3ee353061dd/gcode.c#L3983-L3984)
returns the plugin status directly. The message has not reached planner ownership,
and the hook API receives no message pointer. A rejected block therefore loses
its allocated message while correctly preserving previously queued motion.

**Regression:** [message ownership after rejection](cases/lathe_ngc/pre_execute_rejection_releases_core_message_and_preserves_queued_motion.c).
The supported LATHE_UVW_OPTION/NGC expression build executes the shared hook
without the currently broken cutter configuration. One tracked allocation is
observed around the rejected block; after the prior cut finishes at80 motor
steps, CORE has freed zero messages. Probe teardown reclaims only the observed
orphan after recording the result, avoiding a secondary leak diagnostic without
suppressing sanitizers or changing the failing ownership assertion.

Four existing generic hook tests were relocated from cutter_comp to lathe_ngc
and use a generic motion fixture, preserving their assertions instead of adding
duplicates. They pass unhandled, consumed and rejected-block controls. Raw
ASan/UBSan evidence: batch72-plugin-hook-raw.xml. One named WILL_FAIL/known_bug
allowance is in known_bugs.cmake. **Suggested fix for Terje (not applied):**
release a still-owned message on the hook's early-return path, and preserve
normal parser error cleanup. Retain the regression/controls; remove its allowance
and this entry when clean source frees the message and passes related parser,
planner and message-ownership sanitizer tests.

**Expanded reproduction, 2026-10-22, clean Terje 68eba79:**
[ordinary parser errors](cases/lathe_ngc/parser_rejection_releases_message_and_preserves_queued_motion.c)
combine unsupported G999, negative feed and unused Q after allocating MSG comments.
All three return the expected status, preserve the queued cut and finish at80
steps, but CORE releases zero of the three messages. This needs no plugin
rejection. RETURN calls gc_at_exit, which cannot access the local message;
planner ownership has not yet begun. The combined case retains the correct
three-release assertion with one named WILL_FAIL. Probe teardown reclaims the
observed orphans after measuring ownership, without suppressing diagnostics.
Fix parser early-exit ownership as well as plugin-hook rejection; remove both
message allowances when clean source passes. Evidence: batch72-core68-affected.xml.

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

## Path allocation failure can unlink a same-named file in another directory

**Confirmed:** 2026-10-22, clean Terje68eba7906ba60d66c8b55c4adc90cd5e85b5a828.
[vfs.c parse_path](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/vfs.c#L227-L265)
falls back to copying the unnormalized input when its temporary path malloc
fails. A valid frontend-only provider (no chdir/getcwd callbacks) is mounted at
`/store`; public chdir sets `/store/jobs`. Public unlink of `part.nc` should
reach `/jobs/part.nc`, but the allocation-failure path instead invokes the backend
with `part.nc`, reports success, and can remove the same-named root file.

**Regression:** [wrong-directory unlink under memory pressure](cases/vfs/relative_unlink_path_allocation_failure_preserves_other_directory_and_retries.c).
The registered backend models two distinct files. One size-specific malloc
failure is enabled only around the public unlink. The wrong root-file removal
is recorded, then normal retry demonstrably reaches `/jobs/part.nc` and removes
the intended job file. The final correct unrelated-file-preservation assertion
fails. One named WILL_FAIL/known_bug; no sanitizer allowance. Raw evidence:
batch72-unlink-oom-raw.xml. This is deterministic host driver injection, not a
claim of reproduction on a physical controller.

**Suggested fix for Terje (not applied):** propagate path-normalization allocation
failure to public operations without dispatching an unnormalized destructive
request, or preserve correct absolute routing without allocation. Keep the
unrelated-file and retry assertions; remove the allowance/entry once clean
source preserves both directory identity and normal retry under sanitizers.

## A later successful comment clears a plugin validation error

**Confirmed:** 2026-10-22, clean Terje68eba7906ba60d66c8b55c4adc90cd5e85b5a828.
[gc_normalize_block](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/gcode.c#L1144-L1145)
overwrites the shared normalization status on every plain comment callback.
A plugin rejecting the first comment with Status_UserException is overridden
by a later ordinary comment returning Status_OK, so gc_execute_block accepts
and queues the block. This can defeat material-validation rejection when a
line also carries a contour note; no plasma-plugin implementation is assumed.

**Regression:** [material error followed by ordinary comment](cases/gcode/trailing_comment_does_not_clear_material_validation_error.c)
uses a registered public comment handler, valid queued1mm cut, then
`G20G91G1X2F50(Material selection)(Cut contour)`. The first callback rejects,
the second succeeds; actual status is0 and parser X becomes51.8mm instead of
remaining1mm. Correct error, planner-capacity, modal-state and80-pulse endpoint
assertions reuse the queued-rejection fixture. Those preservation checks cannot
execute until status propagation is fixed. One named WILL_FAIL/known_bug, no
sanitizer allowance. Raw evidence: batch72-comment-status-raw.xml.

**Suggested fix for Terje (not applied):** retain a prior comment error across
normalization or stop processing once a comment fails. Do not allow a later
successful callback to authorize a rejected block. Preserve ordinary multi-
comment processing and the existing single-comment rejection control. Remove
this entry and allowance once clean source passes both under sanitizers.

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

## Unsupported rigid tapping reports success and advances only parser position

**Confirmed:** 2026-10-22, clean Terje68eba7906ba60d66c8b55c4adc90cd5e85b5a828.
The native [mc_rigid_tapping stub](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/motion_control.c#L793-L796)
explicitly returns Status_GcodeUnsupportedCommand. The parser's
[rigid-tapping case](https://github.com/terjeio/grblHAL_core/blob/68eba7906ba60d66c8b55c4adc90cd5e85b5a828/gcode.c#L4811-L4841)
does not propagate that status: it falls through to successful block completion
and copies the target into parser position without executing the requested move.
This is a rejection/status defect in existing code, separate from implementing
native tapping geometry.

**Regression:** [unsupported tapping and following supported move](cases/spindle_sync/unsupported_rigid_tapping_preserves_position_and_next_supported_sync_move.c).
The existing valid encoder/stepper fixture first executes G33Z1K1 and observes80
physical pulses. G33.1Z2K1 then returns0 and sets parser Z=2 while physical/system
position remains80steps (1mm). Correct unsupported-status, unchanged-position
and following ordinary G33 endpoint assertions are retained; the status fails
before the preservation/retry checks execute. No private state injection or
replacement tapping implementation. One named WILL_FAIL/known_bug; no sanitizer
allowance. Raw evidence: batch72-tapping-rejection-raw.xml.

**Suggested fix for Terje (not applied):** propagate unsupported status before
committing a target that did not move, and preserve the existing position for
the next supported move. Confirm the intended macro fallback separately. Remove
this exception/entry once the stub path correctly rejects under sanitizers. If
native tapping is implemented upstream, replace the unsupported-stub expectation
with its agreed execution test and remove the native-feature gap entry as well.

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
