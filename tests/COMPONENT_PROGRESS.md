# Latest component checkpoint - 2026-10-24

Continuing the active all-plugin/driver/CORE goal on isolated plugin-driver-tests.
No production source edits or merges. The separate CORE chat remains untouched.
PR29 is freshly confirmed OPEN/draft/unmerged; its fork still registers only
Core tests and Reusable host tests. No hosted component success is claimed.

83 cases against CORE b01f481072edecac33d5e40c25869359a5b3fa1f pass strict
Windows Clang ASan/UBSan classification:66 clean,16 correct known assertions,
1 previously scoped fan callback diagnostic,0 unexpected failures/skips.
All81 Python helpers pass9.906s; actionlint and whitespace checks pass.
The combined gate rebuilt/rechecked all seven current-compatible suites after
CORE-root selection changes. Fixture files retain strict compiler warnings;
original-source portability warnings remain visible and documented.

New odometer10 cases use real EEPROM/CRC storage and pulse/state/time callbacks:
restart persistence runs in two processes, reset preserves previous readings,
foreground work persists spindle time, and settings callbacks reclaim pulse
observation. Encoder12 cases use real CORE registration/claim/enumeration,
actual EEPROM restart and observed realtime command bytes. Four correct
regressions reproduce rapid command mapping and early enumeration termination.
No encoder sanitizer allowances. Unsupported MPG routes remain TODO.

Simulator VFS is separate from its EEPROM suite. Current CORE compilation fails
on removed vfs_path_t; the failure log is retained, with no alias/fallback.
The driver's own CORE gitlink4ec1ae44b857a70d2f9298344feac4b43ed0eb6b was fetched
unchanged to a separate directory. Its explicit reference build passes strict
classification:9 cases,6 clean/3 known assertions,0 unexpected/skipped/diagnostics.
These confirm nested-directory metadata, stale remount success and buffered
truncate defects. Reference success does not validate current CORE.

New local LLVM coverage, selected original files/configurations only:

| Suite / CORE selection | Lines | Branch outcomes |
|---|---:|---:|
| plugin_odometer / b01f481 | 124/124 (100.00%) | 44/50 (88.00%) |
| plugin_encoder / b01f481 | 186/346 (53.76%) | 77/195 (39.49%) |
| driver_simulator_vfs / reference4ec1ae4 | 125/139 (89.93%) | 54/72 (75.00%) |

Each measured JUnit file passes strict profiling-error classification. Maximum
counter paths217/229/223; no counters lost. Unused/unproven encoder code remains
in the denominator. Earlier five-suite coverage below remains unchanged.
Source locks were independently resolved through GitHub and verified against
clean local source checkouts; odometer a752dc6, encoder b3e31df, EEPROM backend
0c278db, Simulator150e3f9. Immutable full revisions are in ignored build-evidence
*-batch3-source-lock.json alongside sanitizer/coverage logs, XML, JSON and HTML.

Next substantial work: SD-card stream/job ownership and spindle integrations;
resolve valid public encoder MPG contracts without private-state forcing. The
48-repository inventory is partial; this checkpoint does not complete the goal.

---

# Plugin and driver coverage - 2026-10-24

Goal: meaningful functional tests across all plugin/driver catalogue implementations
and CORE. Never edit CORE/plugin/driver production sources or merge PRs. Preserve
other work and use substantial batches. CORE coverage continues in its active chat.

## Previous validated checkpoint

Draft https://github.com/grblHAL/Unit_tests/pull/29 is OPEN/draft, not merged
(fresh API check). Branch plugin-driver-tests tracks origin/plugin-driver-tests;
initial checkpoint200ecaf was already published. Tested implementation:
6bcfb404aacdaf39a1ff69150dd372ff1b134129; a documentation-only checkpoint records these results.
Do not touch the concurrent CORE checkout or merge the PR.

61 Windows Clang ASan/UBSan cases pass strict classification:48 clean,
12 correct expected-failure regressions,1 exact known recovering fan-setting
callback diagnostic; no unexpected failures/skips. Suite times: misc0.81s,
EEPROM1.56s, fans0.88s, Simulator0.38s, OpenPNP0.51s. All81 CI helpers pass9.590s;
actionlint also passes. No production source was edited.

The batch adds OpenPNP, real EEPROM-backed littlefs format/write/unmount/remount/
read with settings-region preservation, upper-bank CRC blocks, persisted fan
ports, delayed program end, callback chaining and RGB/RGBW/servo readback.
Dependency-only littlefs is independently locked and cannot be selected as a
suite. Correct regressions additionally record M42 fractional output ports and
littlefs physical read/program failures reported as success.

One misc coverage attempt lost a counter file at Windows path length263 and is
REJECTED. Both reporters now fail Clang/GCC profiling errors even for known tests;
positive/negative helper controls and the saved real failure prove this. Verified
misc coverage uses the shorter attached-workspace build-plugin-cov directory
(max counter path226), reading this isolated branch's source. All five accepted
coverage JUnit files have zero counter errors and pass strict classification.

Latest LOCAL LLVM measured coverage (instrumented files/configurations only):

| Suite | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugins_misc | 238/243 (97.94%) | 178/238 (74.79%) |
| plugin_eeprom | 156/156 (100.00%) | 52/58 (89.66%) |
| plugin_fans | 184/190 (96.84%) | 101/119 (84.87%) |
| plugin_openpnp | 141/148 (95.27%) | 86/113 (76.11%) |
| driver_simulator | 48/54 (88.89%) | 19/26 (73.08%) |

These are not full repository/catalogue coverage: uncompiled files/configurations
remain in the inventory. Same-source/configuration misc gains20 lines/31 outcomes
and fans22 lines/18 outcomes over the initial checkpoint. EEPROM additionally
instruments its littlefs adapter, so its denominator expanded; do not present its
percentage change as a like-for-like gain. Known defects remain despite coverage.

PR29 remains draft: the fork only registered Core tests and Reusable host tests
at the last workflow-list check. New manual workflows require default-branch
installation; no hosted component success or hardware verification is claimed.
Do not repeatedly dispatch/poll unavailable workflows. Continue substantial
independent batches from COMPONENT_TODO.md, starting Simulator VFS and the next
catalogue implementations. Keep the full goal active; this checkpoint is not
completion. Local logs/locks/HTML/XML/JSON remain in ignored build directories.

## Current branch and source locks

`plugin-driver-tests`, isolated from concurrent `coverage-batch-74` authoring,
initially based on 58774aa; moved onto merged upstream for focused delivery. Only this chat's verified edits were moved from the shared
checkout; original source checkouts and all existing work remain preserved.

| Suite | Repository | Local revision |
|---|---|---|
| plugins_misc | grblHAL/Plugins_misc | 265711922037cab6b6e47a9560ef11da3a6e5f83 |
| plugin_eeprom | grblHAL/Plugin_EEPROM | 0c278db74edc38303b9d86583a7d51a1ec1be51e |
| plugin_fans | grblHAL/Plugin_fans | c5c3613c8d311b43427ec32d551a1e62a5a68531 |
| driver_simulator | grblHAL/Simulator | 150e3f935e4b7cab7b90263b6b90b78912d9158d |
| plugin_openpnp | grblHAL/Plugin_OpenPNP | 76dbbc1420dd9773b1008a21f9d97b266f564bc9 |

CORE dependency: b01f481072edecac33d5e40c25869359a5b3fa1f.
littlefs dependency: 6cb4e86540eca0d9ba62500a298385c9d863c8be. Sources are unchanged.
Separate manual-only Plugin tests and Driver tests Actions callers reuse the
compiler/sanitizer/coverage/reporter workflow. Each resolves immutable candidate
and CORE revisions and uses separate artifacts, diagnostics and coverage filters.

## Implemented workflows and confirmed defects

- Misc plugins: M220 override validation/backup/restore; M150 RGB strip routing,
  masks and brightness; M280 servo attachment, PWM configuration, angle and readback.
- EEPROM plugin: single-/two-byte address layouts, 16/32/64/256-byte pages,
  upper bank, CRC roundtrip/corruption, write failure and EEPROM versus FRAM delay.
- Fan plugin: M106/M107, check mode, reset/program end, spindle-linked delayed
  shutdown, realtime reports, toggling and unavailable resources/ports.
- Simulator driver: erased-file creation, persistence, close-before-open,
  block roundtrip and checksum regressions.

Correct assertions retained for confirmed defect groups, documented under
suite-specific KNOWN_BUGS.md with individual expected-failure properties:
Simulator checksum writer/reader; EEPROM failed reads reported as successful;
two-byte-address EEPROM writes checksums after failed payload transfer; fan
spindle-link setter integer type differs from CORE callback contract.
One exact Clang-only fan-setting callback type diagnostic is tracked; all other sanitizer diagnostics fail. Checksum-reader fixture provides spare valid
caller buffer room so it validates rejection without relying on an overread.

These are callback-level unit tests using original source and real CORE headers,
math and CRC helpers. Full parser/firmware integration and board electrical/timing
behavior are additional work, not implied by a host pass.

## Full catalogue backlog and next action

COMPONENT_INVENTORY.csv includes official and third-party plugin repositories,
plus drivers.json and all architecture links from the driver overview. Duplicate
laser features share their implementation repository; per-file/configuration
coverage remains unfinished within each repository. SDKs, examples, senders,
hardware accessories and unrelated WebUI dependencies are not driver entries.

Catalogue snapshots: grblHAL/plugins f642e7f82fcf91077048cea7833dbdff6afde743;
grblHAL/drivers 9f443d40ccb7060b8bdcaece2b67100e5c2dfc25. Reconcile future
catalogue additions before claiming all implementations are accounted for.

## Initial validation checkpoint

43 Windows Clang ASan/UBSan component cases classified strictly: 33 clean,
9 correct expected-failure regressions, 1 exact known recovering fan-setting
function-type diagnostic; zero unexpected failures or skipped cases. Individual
suite wall times: misc0.85s, EEPROM1.74s, fans0.58s, Simulator0.52s.
CI helpers78/78 passed7.271s. YAML parsing and checksum-verified actionlint1.7.7
passed for the new callers/reusable workflow. Live resolver plus preservation
checks verified all four candidate/CORE locks against unchanged local checkouts.
Sandbox temp-directory failures were infrastructure-only; retry with a workspace
temp directory passed. No production source changes were needed.

Local LLVM coverage measurements (same source revisions above):

| Suite | Covered/total measured lines | Covered/total branch outcomes |
|---|---:|---:|
| plugins_misc | 218/243 (89.71%) | 147/238 (61.76%) |
| plugin_eeprom | 134/136 (98.53%) | 46/50 (92.00%) |
| plugin_fans | 162/190 (85.26%) | 83/119 (69.75%) |
| driver_simulator | 48/54 (88.89%) | 19/26 (73.08%) |

These denominators contain instrumented files/configurations only; they do NOT
include uncompiled implementations in these repositories or the full catalogue.
Inventory/report missing-file rows remain essential. Windows LLVM results are
not substituted for hosted Linux GCC/Clang evidence. Local build-evidence and
build-coverage-* directories retain logs, source locks and HTML/XML/JSON reports.

Next: publish one focused initial-support draft PR against current upstream,
then continue the highest-value remaining fan/misc workflows and additional
catalogue implementations. New manual workflows require installation on the
default branch before GitHub exposes dispatch controls; do not merge them
yourself or claim hosted success. No hosted run or full-coverage claim is made.
