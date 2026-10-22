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
Keep their correct assertions. No expected-failure or sanitizer allowance is added.

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
retains a missing callback intentionally. No sanitizer allowance is added.

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
No expected-failure or sanitizer allowance is added.

**Suggested fix for Terje (not applied):** keep frontend absolute directory and
selected mount consistent when resetting the formatted drive to its root.
Retain the relative backend operation assertion and remove this entry once it
passes on clean source under sanitizers.
