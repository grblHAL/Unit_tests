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


## Cutter compensation still references flags removed from parser state

**Known since:** 2026-10-22, clean Terje `fab8d1c248990f53f13a444018fbb3ee353061dd`.
With `CUTTER_COMP_ENABLE=1`, [gcode.c:2920](https://github.com/terjeio/grblHAL_core/blob/fab8d1c248990f53f13a444018fbb3ee353061dd/gcode.c#L2920),
3364, 3373 and 5036 use `gc_state.ccomp_off`, but the field moved into
`gc_state.flags`. The existing `host_core_cutter` build fails before its ordinary
[cutter-compensation cases](cases/cutter_comp) can run. Test callers use the
source-detected parser-flag accessor; firmware references remain untouched.

**Suggested fix for Terje (not applied):** update the stale field references to
the new parser flags structure. Rebuild the complete supported configuration
matrix and run the existing cutter, tool-table and tool-selection regressions.
There is no compile-diagnostic matcher, skipped registration or sanitizer allowance.
Remove this entry after the clean source builds and those regressions pass.

## Directory validation accepts a regular file and rejects returning to root

**Known since:** 2026-10-22, clean Terje `fab8d1c248990f53f13a444018fbb3ee353061dd`.
The new [vfs_chdir validation](https://github.com/terjeio/grblHAL_core/blob/fab8d1c248990f53f13a444018fbb3ee353061dd/vfs.c#L499-L504)
only sets ENOTDIR when stat fails and its output directory flag is true. A
successful stat identifying a regular file passes the check and changes the
frontend directory. The built-in root stat path also returns failure for `/`,
so ordinary directory-growth controls cannot return to root.

**Regressions:** [regular-file rejection](cases/vfs/chdir_without_backend_handler_rejects_regular_file.c),
[long-directory root return](cases/vfs/long_current_directory_allocates_and_resolves_relative_stat.c)
and [growth root return](cases/vfs/current_directory_growth_preserves_relative_path_resolution.c).
Keep their correct assertions. These three regressions and the four existing
fs_embedded/fs_ram missing or hidden directory rejection regressions have named
`WILL_FAIL` / `known_bug` allowances in [known_bugs.cmake](known_bugs.cmake).
Remove all seven allowances when directory validation and root routing are fixed.

**Additional Linux reproduction:**
[device-directory rejection](cases/fs_device/device_nodes_reject_directory_and_delete_operations.c)
fails at `/dev/subdir` in hosted39762025374, both coverage and GCC. The failed
stat's output is not a valid directory classification. Its named Linux-only
WILL_FAIL allowance preserves the ordinary Windows control, which currently
happens to reject the path. Remove this allowance too after fixing validation.

**Suggested fix for Terje (not applied):** reject failed stat or a successful
non-directory result, and make the built-in root stat resolve `/` correctly.
Retain directory-positive controls and remove this entry once all three regressions
pass against clean source under sanitizers.

## Repeated directory change calls an absent optional getcwd callback

**Known since:** 2026-10-22, clean Terje `fab8d1c248990f53f13a444018fbb3ee353061dd`.
[vfs_chdir:509](https://github.com/terjeio/grblHAL_core/blob/fab8d1c248990f53f13a444018fbb3ee353061dd/vfs.c#L507-L509)
unconditionally calls fgetcwd on a second change within the current mount.
The public getcwd frontend explicitly supports an absent backend callback.
Complete-driver controls now register the paired callback; the dedicated
[optional-callback regression](cases/vfs/repeated_chdir_without_getcwd_handler_preserves_relative_resolution.c)
retains a missing callback intentionally. In sanitizer builds, an exact-diagnostic
wrapper plus named WILL_FAIL/known_bug/known_crash allowance reproduces only the
inventoried ASan access-violation at vfs.c509, frame vfs_chdir. Full output is
retained in build-asan/known-crash-<test>.log. A fix, runner error or different
diagnostic makes the wrapper/strict report fail; post-crash assertions remain
unvalidated. Cleanup: restore direct registration in CMakeLists.txt and remove
the named known_bugs.cmake allowance and known_sanitizer_diagnostics.json entry.

**Suggested fix for Terje (not applied):** guard the optional callback and use
frontend directory state for recovery when a backend has no getcwd operation.
Keep the regression and remove this entry once repeated directory changes and
relative backend routing pass under sanitizers on clean source.

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

**Suggested fix for Terje (not applied):** keep frontend absolute directory and
selected mount consistent when resetting the formatted drive to its root.
Retain the relative backend operation assertion and remove this entry once it
passes on clean source under sanitizers.

## Interrupt cancellation of a selected delayed task calls a cleared callback

**Known since:** 2026-10-22, clean Terje
`fab8d1c248990f53f13a444018fbb3ee353061dd`; remote master rechecked unchanged.

[task_execute](https://github.com/terjeio/grblHAL_core/blob/fab8d1c248990f53f13a444018fbb3ee353061dd/grbllib.c#L573-L595)
selects a due queue entry before masking interrupts. An interrupt can call the
ISR-safe [task_delete](https://github.com/terjeio/grblHAL_core/blob/fab8d1c248990f53f13a444018fbb3ee353061dd/grbllib.c#L647-L666)
for that still-queued entry. Deletion unlinks it and clears its callback via
task_free. The foreground resumes with the cached entry, copies its now-NULL
callback and calls it at line595, producing an ASan access violation.

**Regression:** [interrupt cancellation](cases/grbllib/interrupt_cancelling_due_task_before_masking_preserves_later_work.c).
**Passing controls:** [interrupt insertion](cases/grbllib/interrupt_arrival_before_masking_preserves_due_and_new_delayed_work.c)
and [future retry cancellation](cases/grbllib/interrupt_cancelling_future_retry_preserves_selected_due_work.c).
The same driver IRQ-mask hook models a pending interrupt just before masking;
all scenarios use only public ISR-safe task APIs. No private queue access or
firmware patch is used. The cancellation case retains correct no-callback and
later-work assertions. Sanitizer builds now use an exact-diagnostic wrapper and
named WILL_FAIL/known_bug/known_crash allowance for only the inventoried ASan
access-violation at grbllib.c595, frame task_execute. Post-crash assertions remain
unvalidated. Cleanup: restore direct registration in CMakeLists.txt and remove
the named known_bugs.cmake allowance and known_sanitizer_diagnostics.json entry.
Different diagnostics, additional sanitizer faults, fixes and runner errors fail.
Evidence: build-asan/batch72-task-irq.xml (insertion passes; cancellation crashes
at grbllib.c595), plus batch72-task-irq-build.log. The future-retry cancellation
control passes in0.32s: batch72-task-irq-control.xml. This is a host-controlled
single-core interrupt interleaving, not a claim of reproduction on a board.

**Suggested fix for Terje (not applied):** select/remove the due task and snapshot
its callback/data atomically under the IRQ mask, or revalidate a cached candidate
under the mask before dispatch. Account for cancellation and pool-slot reuse;
merely checking the old queue link does not establish callback lifetime. Keep
callbacks outside the critical section. Retain the regression and both controls, run the task
module and full sanitizers, then remove this entry when clean source passes.

### Linux diagnostics for the two documented indirect NULL calls

Hosted39762025374 confirms both faults under GCC and Clang. Clang reports SEGV
at the same exact CORE source/frame as Windows access-violation. GCC reports
PC/address zero and omits the tail-called CORE frame: VFS has main at its test
line9; tasks have engine_execute_tasks at task_host.c8 followed by main at test
line27. The fatal inventory now records these exact caller chains. Matching
requires PC zero, unknown-module frame0 and summary, the named test and every
recorded caller frame. Changed source/caller/line/PC, additional sanitizer errors,
runner errors and fixed executables remain failures. This is diagnostic
classification, not successful execution of assertions after the crash.
Captured evidence: hosted39762025374/{gcc,clang}-results/build/results.xml.
All four captured diagnostics replay successfully;71 helper checks pass, and
both actual Windows reproducers plus strict summary pass in0.54s. Keep cleanup
of both named wrappers, allowances and manifest entries linked above.

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

## Pre-execution plugin rejection loses a CORE-allocated message

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
