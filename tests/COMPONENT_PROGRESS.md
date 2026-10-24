# Latest component checkpoint - 2026-10-24 (batch7)

Full all-plugin/driver/CORE goal remains active across48 implementation repos.
No production sources or concurrent CORE work changed. Isolated branch continues
existing PR29, freshly OPEN/draft/unmerged. Fork list still registers only Core
tests and Reusable host tests. No hosted component run or merge is claimed.

Added26 cases:14 Trinamic and12 plasma. One cumulative Windows Clang ASan/UBSan
gate rebuilds/rechecks all seventeen compatible suites against pinned COREb01f481:
224 cases =200 clean +23 correct known assertions +1 previously scoped fan
callback diagnostic. Zero unexpected failures/skips. All81 CI/reporting helpers
pass9.677s; actionlint/whitespace checks pass. Original source warnings remain
visible under documented rules; fixtures stay -Werror. No new sanitizer allowance.

Trinamic executes original plugin plus actual TMC2209 chip/HAL/common library
against a simulated UART register device with CRC-checked packets and real IFCNT
accounting. Cases cover3 registered motors, setup/address callbacks, current and
mode commands, current/microstep settings/rejection, communication/setup/storage
failure, recovery/status reset, fault IRQ, callback chaining and EEPROM-backed
restart in two processes. Current checks concern configured values, not measured
motor current. Host parser/settings boundaries model named axis words and their
consumption/restoration; full CORE parser execution is not claimed. An initial
fixture mistake caused NaN conversions and was corrected to the real public
parser contract before classification; no diagnostic was waived.

Plasma compiles original THC/SheetCam/LinuxCNC modules with actual CORE I/O
registration, secondary stepper, PID, VFS/embedded backend and real EEPROM/CRC.
Cases use its normal initial Off mode and do not fabricate private ready state.
Initialization failures, material validation/add/overwrite/enumeration, comments/
rejection/recovery, registered listing and report hooks pass. Both external file
formats load through actual VFS mount listeners with the read-only host backend
mounted through public APIs. I/O and plasma settings are distinct registrations
and receive separate NVS allocations. Full torch/arc/voltage/up-down motion,
PowerMax, expression integration and hardware timing remain untested. MinGW's
exported isnanf lacks a math.h declaration; the Windows-only host declaration
uses the actual runtime function, without replacement code or production aliases.

Fresh LOCAL LLVM measured compiled-file/configuration coverage:

| Suite | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_trinamic / trinamic.c | 320/885 (36.16%) | 122/570 (21.40%) |
| plugin_plasma / THC + two importers | 263/869 (30.26%) | 150/553 (27.12%) |

Plasma detail: THC167/764 lines, LinuxCNC51/56, SheetCam45/49. Remaining runtime
code stays in the denominator; no whole-plugin, library or catalogue claim.
All coverage result sets pass strict profiling-error checks; maximum counter
paths222/227. The largest remaining supported runtime regions are recorded in
COMPONENT_TODO.md rather than excluded or entered through private state.

GitHub-resolved locks match clean local sources:
motor9229617c1d8a3cc7a71fd584896500a779978b02,
plasma d2f91b5887db6550ddec0fc0229cd87ec0af1a56,
COREb01f481072edecac33d5e40c25869359a5b3fa1f,
EEPROM0c278db74edc38303b9d86583a7d51a1ec1be51e,
Trinamic-library9b304175318d93818c8967faadc89dd101b17e92. The latter is an
explicit dependency-only pin from the inspected RP2040 gitlink, not an implicit
fallback. Full immutable locks/classification/logs are in ignored build-evidence/
*batch7*, alongside per-suite coverage XML/JSON/HTML. New Plugin tests choices
await default-branch installation. No hosted/GCC/board/physical-device pass claim.

Continue supported plasma/TMC runtime and remaining catalogue/modules/configs.
The full goal is not complete.

---

# Previous batch6 checkpoint - 2026-10-24

Full all-plugin/driver/CORE goal remains active across48 inventoried repositories.
No production sources or concurrent CORE work changed. This isolated branch
continues PR29, freshly OPEN/draft/unmerged. Fork workflow list still exposes
only Core tests and Reusable host tests; no hosted component run is claimed.

Added31 cases:11 common networking,12 laser PPI and8 LightBurn cluster cases.
One cumulative Windows Clang ASan/UBSan gate rebuilds/rechecks all fifteen
current-compatible suites:198 cases =174 clean +23 correct known assertions
+1 previously scoped fan callback diagnostic. Zero unexpected failures/skips.
All81 CI/reporting helpers pass11.915s; actionlint/whitespace checks pass.
Source warnings remain visible under documented rules; fixture warnings stay
strict. No sanitizer allowances added.

Networking uses the original public event/provider/enumeration API and registered
NETIF/report hooks. Cases cover Ethernet/STA/AP notifications, unavailable provider,
enumeration/short-circuit, listening-port/status reports, one hostname, cached
stream selection across file mode, enabled service labels, MAC conversion and
idempotent init/hook chaining. Actual lwIP headers are source-locked with a local
NO_SYS IPv4 architecture/configuration boundary. No actual listeners/packets,
stack runtime, wireless or Ethernet hardware is exercised by this suite.

PPI tests compile actual CORE spindle registration/selection. Driver step/pulse/
PWM/RPM callbacks and gc_laser_ppi_enable are simulated public boundaries. Normal
spacing/width, zero RPM, enabling/disabling, check mode, reset/program-end,
zero configuration, hardware delegation and callback chaining pass. One correct
regression demonstrates ppiUpdatePWM requests pulse_on even when PWM becomes
zero. Driver callback observation does not establish physical emitted energy.

LightBurn tests execute the original decoder with simulated normal/file byte
sources and real CORE numeric helpers. Valid X/Y/negative moves divide distance,
preserve feed/power, restore initial S when required and acknowledge one input
cluster. Paired EOL, fragment reset, source changes and report chaining pass.
Default unscaled16-value configuration only; not full parser/motion or physical
LightBurn integration. Coolant/overdrive/alternate PPI and decoder modes remain.

Fresh LOCAL LLVM measured-file/configuration coverage:

| Suite / file | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_networking / networking.c | 157/165 (95.15%) | 84/106 (79.25%) |
| plugin_laser_ppi / ppi.c | 144/146 (98.63%) | 83/100 (83.00%) |
| plugin_laser_cluster / lb_clusters.c | 181/209 (86.60%) | 97/141 (68.79%) |

All coverage result sets pass strict profiling-error checks; maximum counter
paths229/198/203. Uncovered code remains in denominators. These are not whole
repository/catalogue percentages. Known defects remain despite line coverage.

GitHub-resolved source locks match clean local checkouts and master defaults:
networking0b665ee0c0be5161d5044bdf2dcdf59ad62509f8,
laser26934c6c9607e0b5ba4a711516a60d4657bf142c,
lwIPd08f4773edd0182b7910fc8f046eed82ffcd67c9,
COREb01f481072edecac33d5e40c25869359a5b3fa1f. Local immutable locks,
classification and sanitizer logs are in ignored build-evidence/*batch6*, with
per-suite coverage XML/JSON/HTML and build logs. lwIP is dependency-only and
cannot be selected as a suite. New choices are in the separate Plugin tests
workflow, awaiting default-branch installation. No hosted/GCC/hardware pass claim.

Plasma d2f91b5 and motor9229617 sources were fetched unchanged and assessed for
real registration/dependency requirements; no test suite or runtime support is
claimed for them yet. RP2040's actual Trinamic-library gitlink was identified.
Continue THC/material/Trinamic workflows and remaining modules/configurations
from COMPONENT_TODO.md. The full goal is not complete.

---

# Previous batch5 checkpoint - 2026-10-24

Goal remains active across all48 implementation repositories. No production
sources or concurrent CORE work changed. The isolated plugin-driver-tests branch
continues existing PR29, freshly confirmed OPEN/draft/unmerged. Fork workflow
listing still contains only Core tests and Reusable host tests; no hosted plugin/
driver success or merge is claimed.

Added43 cases:30 keypad cases and13 driver-storage cases. One cumulative Windows
Clang ASan/UBSan gate rebuilds/rechecks all twelve current-compatible suites:
167 cases =144 clean +22 correct known assertions +1 previously scoped fan
callback diagnostic. Zero unexpected failures/skips. All81 CI/reporting helpers
pass9.743s. Actionlint and whitespace checks pass. Keypad source warnings remain
visible under documented production-source rules; fixtures and both small driver
sources retain -Werror. No sanitizer allowances added.

Keypad cases cover I2C strobe/UART registration, fast/slow/step and diagonal jog
commands, modifiers, preview hooks, released-key suppression before foreground
processing, successful/rejected enqueue cancellation, legacy control, real CORE
override queues, settings/report callbacks, initialization failures and NVS
restart. The NVS provider is opaque CRC-backed RAM, with two-process persisted
bytes and actual CORE CRC; no private serialized plugin structure is copied.
Initial jog string expectations were corrected to CORE ftoa's trailing decimal
point; actual numeric distances/feed assertions remain exact.

Four correct regressions reproduce extended keys lost when char is signed:
I2C/UART extended control and override cases. The identical unsigned-char controls
pass. Compile modes are explicit, not inferred as universal firmware behavior.
UART failed stream opening leaves no settings registration but init returns NVS
allocation success; intended bool semantics remain TODO, not a declared defect.

RP2040 original flash.c executes against a RAM XIP mapping and simulated erase/
program/IRQ calls. Five cases verify erased reads, bytes copied, unchanged-write
avoidance, page rounding with a padded source and readback verification failure.
The host preinclude omits board driver.h setup intentionally; it does not compile
the actual Pico SDK/PIO/pins or prove timing/multicore safety. ESP32 original
main/nvs.c executes through simulated partition APIs. Eight cases verify discovery,
absent/uninitialized storage, bytes, erase/write/read failures, invalidation,
reinitialization and retry. Every erase checks all256 input values through the
original temporary realtime filter; handler restoration is observed on success
and failure. No physical flash/cache/UART timing or full-driver claim.

Fresh LOCAL LLVM coverage, selected compiled files/configurations only:

| Suite / measured file | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_keypad / keypad.c | 218/230 (94.78%) | 109/144 (75.69%) |
| driver_rp2040_flash / flash.c | 12/12 (100.00%) | 2/2 (100.00%) |
| driver_esp32_nvs / main/nvs.c | 16/16 (100.00%) | 14/14 (100.00%) |

All coverage result sets pass strict profiling-error classification. Maximum
counter paths237/203/199. Initial local keypad aggregation failed because the
two conditional keypad_init definitions occupy different lines. Re-reading the
same counters with --merge-mode-functions=separate, already used by hosted CI,
fixes reporting; no source changes, ignored errors, denominator exclusion or
redundant test run. Rejected attempt/log retained. These are not percentages for
whole drivers/catalogues. Source/configuration gaps remain in the inventory.

GitHub-resolved locks match clean source checkouts and verified master defaults:
keypad c34933091df668d009fe11ed7397a9b78c9bfd79,
RP2040 2f5bc4a06ecea3b1f78c1644623810f9b6416376,
ESP32 0b2d3e1bb7da3b0ae0e03490b71275374eb84c67,
CORE b01f481072edecac33d5e40c25869359a5b3fa1f. Local evidence is in ignored
build-evidence/*batch5* plus per-suite sanitizer/coverage logs/XML/JSON/HTML.
SDK boundary declarations are local test fixtures, not SDK version-lock claims.

The new choices are wired into separate Plugin tests / Driver tests workflows,
available after default-branch installation. No hosted/GCC/hardware pass claim.
Next: remaining catalogue families, VFD/SD/MPG gaps and other driver modules;
keep source incompatibilities and reference-only results visible below. The full
goal is not complete.

---

# Previous batch4 checkpoint - 2026-10-24

Goal remains active across all48 inventoried implementation repositories. No
production sources or concurrent CORE work changed. Isolated plugin-driver-tests
continues the existing OPEN/draft/unmerged PR29. Fresh fork API still registers
only Core tests and Reusable host tests; no hosted component success is claimed.

Added41 cases:28 GS20/MODVFD cases and13 SD streaming cases. One cumulative
Windows Clang ASan/UBSan gate rebuilds/rechecks all nine current-compatible suites:
124 cases =105 clean +18 correct assertion regressions +1 previously scoped fan
callback diagnostic. Zero unexpected failures/skips. A subsequent fixture-only
cancellation assertion verifies EXEC_MOTION_CANCEL before simulating the stop;
its affected connection-change case and strict summary pass0.11s. All81 helpers pass9.626s;
actionlint and whitespace checks pass. Original-source compiler warnings remain
visible under documented production-source rules; fixtures retain -Werror.

VFD tests use original coordinator/protocols, real CORE spindle registration,
selection, at-speed math and Modbus API dispatch. A registered RTU fixture verifies
exact requests and returns replies/rejections/exceptions. Tests cover CW/CCW/stop,
asynchronous speed updates, query throttling, measured RPM, exception thresholds
and success reset, cold-start alarm deferral, settings/report hook chaining,
missing transport/storage, down-bus recovery and custom registers/conversions.
Two-process EEPROM-backed restarts verify saved protocol settings without copying
private serialized layouts. Initial feedback equality was replaced with0.01 RPM
float tolerance; exact Modbus byte assertions remain.

SD tests use original fs_stream.c/macros.c with real CORE VFS, stream, redirect
and embedded read-only filesystem mounted at / via public VFS calls. Job byte
streaming/completion, final newline, status-error recovery, reset, tool-change
ack/suspend/resume, rejected startup, filtered/all listings, progress, realtime
input filtering, connection-change termination and external M98-style macro repeat
are observed. Parameter-local G65, expression ATC and physical SD are not claimed.
Two correct known assertions reproduce extra EOF blank lines in already terminated
job input and dumps. Unterminated job/dump controls pass. No new sanitizer waivers.

The separate original SD littlefs adapter syntax check fails against current CORE
on removed vfs_path_t (fs_littlefs.c58/64), after resolving real CORE/littlefs
headers. No source alias/fallback masks it. Streaming success does not establish
adapter or FATFS/SD hardware compatibility. Simulator reference-only results from
batch3 below remain separate and unchanged.

Fresh LOCAL LLVM coverage (only compiled original files/configurations):

| Suite | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_spindle_vfd | 288/320 (90.00%) | 81/136 (59.56%) |
| plugin_sdcard_stream | 394/591 (66.67%) | 174/378 (46.03%) |

All coverage cases pass strict result/profile-error checks; max counter paths
226/209. Unused supported paths remain counted. No catalogue-wide percentages.
Coverage includes coordinator plus GS20/MODVFD and stream/macros configurations;
other files/configurations remain in COMPONENT_INVENTORY.csv/COMPONENT_TODO.md.

GitHub-resolved locks match clean source checkouts: spindle
8a3ae47f5a218834da9c742424c3dd22c5629fdb, SD card
d0fe753d622e79a60e54e729ba83f7207276114c, CORE
b01f481072edecac33d5e40c25869359a5b3fa1f, EEPROM backend
0c278db74edc38303b9d86583a7d51a1ec1be51e. Local evidence is retained in ignored
build-evidence/*batch4* plus per-suite coverage HTML/XML/JSON and compile logs.
Both suites are selectable in the separate Plugin tests workflow after default
branch installation; no merge/hosted/hardware/GCC completion claim.

Next: remaining VFD protocols, supported SD adapter/job paths, I2C keypad and
host-testable driver helpers. The full goal is not complete.

---

# Previous batch3 checkpoint - 2026-10-24

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
