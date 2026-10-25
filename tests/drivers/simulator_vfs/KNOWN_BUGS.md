# Known defects

## Current CORE compatibility - 2026-10-24

Simulator150e3f935e4b7cab7b90263b6b90b78912d9158d uses `vfs_path_t`
in fs_posix.c43/47. COREb01f481072edecac33d5e40c25869359a5b3fa1f
removed that type in favor of its newer string API, so this suite does not
compile against current CORE. No alias or source patch hides the incompatibility.
The main Simulator EEPROM suite remains independent.

Simulator's actual src/grbl gitlink is4ec1ae44b857a70d2f9298344feac4b43ed0eb6b.
A separately labelled reference run against that pinned dependency passes
strict classification (six clean cases and three reproduced regressions). It does not prove current-CORE compatibility or validate paths after
a compile failure. Default CI still selects current CORE unless core_ref is
explicitly set. Never waive a compile error as a known assertion failure.

## Nested directory metadata resolves against current directory

`nested_listing` lists /archive without changing into it. fs_readdir() calls
fs_stat(entry->name), which resolves relative to the adapter cwd instead of the
opened directory. The correct nine-byte file entry metadata assertion fails.
Root-directory listing and ordinary file stat/read controls pass. The test uses
public VFS calls and cleans its own files before checking the retained result.

## Missing remount reports stale success

`remount_missing` mounts, unmounts, removes its backing directory, then attempts
to mount that now-missing directory. The adapter returns true from its previous
non-null root.name although no new mount callback occurs. The correct failure
assertion remains. No private pointer is cleared or fabricated by the fixture.

## Buffered writes undo file truncation

`pending_truncate` writes ten bytes, requests a four-byte truncate, then closes.
The truncate callback acts on the descriptor without flushing the FILE buffer;
closing writes pending data back to ten bytes. The test checks persisted file
size after close, with a normal closed/reopened file truncate as passing control.

All three are confirmed assertions against the driver's own pinned CORE commit
4ec1ae44b857a70d2f9298344feac4b43ed0eb6b on Windows Clang ASan/UBSan, with
individual WILL_FAIL/known_bug properties and no sanitizer allowances. They do
not validate current-CORE execution, which remains blocked at compilation.
Proposed upstream changes: retain directory ownership in listing handles,
validate/refresh mount state on every attempt, and synchronize buffered writes
before truncation. Keep correct tests and remove only their resolved properties
and entries after actual fixes pass. Do not patch the source in this harness.
