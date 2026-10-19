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

Remaining exceptions were revalidated on 2026-10-19 against Terje core
`16c7dff3aa9614322cfc2b47a2109cc9196ccca4`. Fixed entries and their allowances
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


## First filesystem path normalization reads an uninitialized directory string

**Known since:** 2026-10-19. **Reproduced core:**
`49eff3c5c66afa1cc1915b26ae8160fa805593c7`.

A normal first `vfs_chdir("/store/dir")` or
`vfs_unlink("/store/../elsewhere/file")` crashes before reaching its backend.
AddressSanitizer reports a null read in `strlen`, called by
[parse_path at vfs.c:264](https://github.com/terjeio/grblHAL_core/blob/49eff3c5c66afa1cc1915b26ae8160fa805593c7/vfs.c#L232-L265).
The new `cwd` string has a base buffer but its `data/name` pointer is initially
NULL; `parse_path` reads it before any `strset` call initializes it.
Unmounting root storage before a path operation likewise writes through this
NULL cached pointer at vfs.c:741; ordinary directory-list cleanup reproduces it.

**Existing reproductions:**
[current directory](cases/vfs/getcwd_without_backend_handler_preserves_mount_prefix_once.c)
and [cross-mount unlink](cases/vfs/parent_path_crossing_mount_passes_target_local_filename.c).
Their older logical-bug exceptions do not authorize this new sanitizer failure:
the strict summary rejects it. No broad exception or sanitizer allowance is added.
Raw evidence: `batch69-core49-reproduce-results.xml` and matching parent logs.

**Suggested fix (proposal, not applied):** initialize the current directory's
`data` and capacity from `_cwd` before its first read, rather than relying on a
future string-write call. Audit other base-backed strings for the same ordering.
Retest first path operations, relative paths, named macro lookup and allocation
failure recovery under sanitizers. After confirming any older logical defects
are also fixed, remove only their corresponding existing exceptions/entries.
Delete this entry once ordinary path operations are sanitizer-clean.

## Growing a base-backed string reallocates static or stack storage

**Known since:** 2026-10-19. **Reproduced core:**
`49eff3c5c66afa1cc1915b26ae8160fa805593c7`.

Looking up `workbee_panel_fixture_01.nc` through `vfs_locate_file` calls
[the new strset growth path](https://github.com/terjeio/grblHAL_core/blob/49eff3c5c66afa1cc1915b26ae8160fa805593c7/strutils.c#L383-L408).
It initializes `data` to the supplied base buffer, then passes that pointer to
`realloc`. The lookup buffer is a 32-byte static array rather than a heap
allocation. AddressSanitizer reports an attempted free of non-malloc storage at
`strutils.c:393`, called from `vfs.c:901`. Named macro construction also uses a
local base buffer and needs the same ownership rule.

**Existing reproduction:**
[long macro/job filename lookup](cases/vfs/locate_long_filename_returns_mounted_file_path.c).
The new direct [base-buffer promotion regression](cases/strutils/strset_long_filename_promotes_static_base_to_owned_heap.c)
asserts successful growth, correct text and the original base remaining intact.
No expected-failure registration or sanitizer allowance is added; this remains
an ordinary red test until fixed. Existing heap copy/reuse and base-capacity
controls exercise the supported small-string paths.

**Suggested fix (proposal, not applied):** when `data` is the base buffer,
allocate owned storage with `malloc` (or `realloc(NULL, size)`), never
`realloc(base, size)`. Reallocate only owned heap buffers. On failure, retain a
consistent base pointer/capacity and return NULL; avoid restoring the base and
then overwriting that restored pointer with NULL. Review callers before choosing
whether existing text must survive failure. Verify lookup and long named macros
with ordinary controller filenames under sanitizers. Keep both regressions,
remove no unrelated allowance, and delete this entry once fixed.


## Enabling the safety-door driver option now fails preprocessing

**Known since:** 2026-10-19. **Reproduced core:**
`49eff3c5c66afa1cc1915b26ae8160fa805593c7`.

A normal driver configuration with `SAFETY_DOOR_ENABLE=1` and no
`NO_SAFETY_DOOR_SUPPORT` definition fails at
[driver_opts.h:530-532](https://github.com/terjeio/grblHAL_core/blob/49eff3c5c66afa1cc1915b26ae8160fa805593c7/driver_opts.h#L530-L532).
The former combined guard became `#if SAFETY_DOOR_ENABLE`, so every enabled
configuration emits `Driver does not support safety door functionality!`.

**Reproduction:** preprocess a translation unit including `driver_opts.h` with
`clang -std=gnu11 -fsyntax-only -DSAFETY_DOOR_ENABLE=1 -Icore <probe.c>`.
The same probe with the previous16c7dff header succeeds. The latest header with
`SAFETY_DOOR_ENABLE=0` also succeeds. Parent logs `batch69-door-compile.log`,
`batch69-door-old-compile.log` and `batch69-door-disabled-compile.log` retain all
three outcomes. No board SDK, source modification or private state is involved.
Positive compile regression: [safety-door driver configuration](compile/safety_door_configuration.c),
registered as feature_compile.safety_door_option_1 with the disabled control
feature_compile.safety_door_option_0. No diagnostic matcher or expected-failure
exception is added.

**Suggested fix (proposal, not applied):** remove the obsolete rejection guard
if the removed NO_SAFETY_DOOR_SUPPORT mechanism is no longer supported, or gate
it on an actual driver incompatibility rather than on enabling the feature.
Verify both ordinary enabled and disabled configurations before adopting a fix.
Keep the positive compile regression and delete this entry once fixed.
