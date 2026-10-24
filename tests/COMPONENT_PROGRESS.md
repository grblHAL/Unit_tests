# Latest component checkpoint - 2026-10-24 (batch16)

Goal remains active. Added41 cases: Sienci RGB24 (legacy2 and advanced3 modes),
FlexGPIO17 (three-axis behaviors and six-axis registration). New Plugin tests
choices source-lock candidate/CORE separately. Corrected both component workflow
run names to suite default instead of assuming master; Sienci defaults SLB32_DEV.
No production source changes, concurrent CORE edits or merges.

One cumulative Windows Clang ASan/UBSan gate:38 compatible suites,564 cases =
511 clean +53 documented known results, zero unexpected failures/skips. Known
results comprise49 correct assertion regressions +4 passed-assertion diagnostic
cases;3 assertion cases also have exact diagnostics, counted once. New assertions
retain legacy delayed tool color, FlexGPIO IRQ-disable result and unsupported
pull-mode acceptance. Four new exact test/file/line/function/type expectations
cover original FlexGPIO config callbacks through CORE's GNU transparent-union API;
this records the Clang signature diagnostic separately from functional defects.
No sanitizer disabled; unknown/missing diagnostics fail strict reporting. Actual
mixed assertion/diagnostic summary verified. All84 helpers pass17.106s; actionlint
and whitespace pass after workflow label correction.

Fresh local LLVM selected-file coverage: Sienci rgb.c194/200 lines97%,104/125
branches83.2%,15/15 functions; rgbv2.c339/357 lines95%,163/186 branches87.6%,
34/34 functions. Combined533/557 lines,267/311 branches. FlexGPIO257/272 lines
94.5%,123/150 branches82%,19/21 functions. Adds790 exercised executable lines.
Fresh counter paths max212 characters, strict profiling checks pass. No full
controller/parser/CORE task scheduling/port aggregation or hardware claim.

Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
Sienci RGB df3409058f8bb9c202f560e562bb2671a0829561;
FlexGPIO bc8dab40162b49718179bffe973c4533fc73436f.
API-matched local source/CORE HEADs clean. Datron RGB672ebd8beeed746b5c668be18b4e4c48b6c14883
fails unchanged-source syntax compilation due private static bit_count versus
CORE declaration; ffsl is additionally undeclared on Windows. No source aliases,
header bypasses or compatibility fallback; no runtime choice registered for it.
Remaining scope in TODO/per-suite guides; evidence and source locks ignored in
build-evidence. PR29 stays draft/unmerged. Hosted workflow installation on default
branch and physical target checks remain outstanding.

---

# Latest component checkpoint - 2026-10-24 (batch15)

Goal remains active. Added35 cases: TM4C123 EEPROM12/UART012 and standalone TI
shared EEPROM11. Three new Driver tests choices source-lock original driver/
shared code, CORE and a declared TivaWare vendor-header mirror. Actual driver.h,
tiva.h and board headers compile unchanged. CORE CRC and full stream support
execute; hardware calls are explicit bounded EEPROM and UART/IRQ simulations.
No production edits, no concurrent CORE checkout changes, no merges.

One cumulative Windows Clang ASan/UBSan gate:36 compatible suites,523 cases =
476 clean +47 documented known results, zero unexpected failures/skips. Known
results now46 correct expected assertion regressions +1 fan-only diagnostic;
two existing SAM assertion cases also retain exact diagnostics, counted once.
Added12 correct assertion regressions: CRC8 read location, shared checksum layout/
read location, ignored hardware/allocation errors in both EEPROM modules, and
full RX ring dropping realtime dispatch. No new sanitizer allowance. All84
reporting helpers pass16.302s; actionlint and whitespace pass.

Fresh local LLVM selected-file coverage: TM4C123 EEPROM49/51 lines96.1%,17/20
branches85%,7/7 functions; shared EEPROM49/51 lines96.1%,17/20 branches85%,7/7
functions; TM4C123 UART0112/112 lines100%,44/48 branches91.7%,14/14 functions.
Adds210 exercised executable lines. Fresh counter paths max227 characters;
strict profiling checks pass. Missing EEPROM direct-transfer branches cannot be
entered by valid alignment: alignend is always1..4. Retained without exclusions.

Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
TM4C12314fdf8de2126316c14d88656f3a19337800ad1c1;
TI shared6adcc848946fe69075f6ed062afa31f11c5a4c97;
TivaWare mirror c23bf8ba7a82b20421aa04d4df3f77501c5883ea(yuvadm/tiva-c).
API-matched upstream/CORE/SDK HEADs clean. Shared is a standalone candidate;
archived TM4C1294 parent pins a different shared source3e7873 and remains unbuilt.
No latest-official-SDK, full target-link, timing/endurance or physical-board claim.
Evidence/source locks in ignored build-evidence; remaining scope in TODO and
per-suite guides. PR29 remains draft/unmerged; hosted component workflow default-
branch installation remains separate from these local results.

---

# Latest component checkpoint - 2026-10-24 (batch14)

Goal remains active; no production sources or concurrent CORE edits, no merges.
Added34 cases:21 Virtual Inputs and13 Homing Acceleration. Separate Plugin tests
choices resolve candidate and CORE independently into immutable source locks.
Topology-independent Virtual Inputs cases run once; only sensor behavior varies
across shared/separate registration. Original CORE probe.c and formatting execute
with public registration/select/configure/IRQ boundaries and simulated pins.
Homing cases capture public per-axis settings/override requests, including
restoration, failures, persistence and rotary units; real settings.c backup and
planner/stepper homing are not executed by that suite.

One cumulative Windows Clang ASan/UBSan gate:33 compatible suites,488 cases =
453 clean +35 documented known results, zero unexpected failures/skips. Same34
correct expected assertion regressions plus1 fan-only diagnostic; two existing
SAM assertion cases also have exact callback diagnostics, counted once. All34
new cases clean; no new exception/diagnostic allowance. All84 reporting helpers
pass16.345s; actionlint and whitespace pass.

Fresh local LLVM selected-file coverage: Virtual Inputs146/146 lines100%,66/71
branches93.0%,17/17 functions; Homing Acceleration101/101 lines100%,43/44
branches97.7%,14/14 functions. Adds247 exercised executable lines. Fresh counter
paths max226 characters; strict profiling checks pass. These are selected host
configurations, not complete plugin/controller or hardware coverage.

Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
Virtual Inputs e943e0c5da8a70ac9cfa91234bfa0a35a388c5f6;
Homing Acceleration a06b7cd6095a40478dde5bb1b44323d0e10373c2.
API-matched local source/CORE HEADs clean. Panel09c90184288a09d7357fd994c395911dec38683f
fails unchanged-source syntax checks in CAN and README-required Modbus64 configs:
obsolete one-argument system_execute_line at707 versus CORE two-argument API.
No panel runtime suite/Actions choice or source alias; evidence in build-evidence.
Remaining TI families fetched/read for next batch; details and ownership concerns
in COMPONENT_TODO. PR29 stays draft/unmerged. Hosted component workflows still
need default-branch installation; no Linux/GCC/physical-board success claimed.

---

# Latest component checkpoint - 2026-10-24 (batch13)

Goal remains active. Added50 unchanged-source third-party plugin cases in separate
behavior files: AUXP7, Interlock13, PneumaSeal15 and Thermistor15. Added four
Plugin tests workflow choices with immutable candidate/CORE plans. Default branches
are main, not master. No production source or concurrent CORE edits, no merge.

One cumulative Windows Clang ASan/UBSan gate:31 compatible suites,454 cases =
419 clean +35 documented known results, zero unexpected failures/skips. This is
34 correct expected assertion regressions plus1 fan-only diagnostic; two SAM
assertion cases also retain exact callback diagnostics without double counting.
All50 new cases clean, no new exception/diagnostic allowance. All84 CI/reporting
helpers pass15.879s; actionlint and whitespace checks pass. Clang23's original
Interlock default-const-field initialization warning stays visible/nonfatal only
for that source; fixtures remain strict.

Fresh local LLVM selected-file coverage:
- AUXP45/45 lines100%,24/24 branches100%,5/5 functions.
- Interlock173/185 lines93.5%,67/84 branches79.8%,19/23 functions.
- PneumaSeal128/141 lines90.8%,43/52 branches82.7%,20/26 functions.
- Thermistor133/139 lines95.7%,68/74 branches91.9%,10/12 functions.
These add479 exercised lines across510 selected executable lines. Fresh counter
paths max215 characters; strict profiling checks pass. No full-plugin, complete
settings parser, physical sensor/solenoid or actual emergency-stop timing claim.
Port/settings/NVS/task/alarm boundaries are explicit host simulations; original
CORE formatting is linked where used. No private plugin state is modified.

Pinned CORE remains b01f481072edecac33d5e40c25869359a5b3fa1f.
AUXP ded4a654f9ad17eec449431a51310b44f6da86c9;
Interlock5893ea35645c334ec96333ccd0519eac03128ee6;
PneumaSeal3127ab8c15982569d7e89822a9e1095cdce89cbb;
Thermistor4fae94b9b553604f2f41222bbc04fa45669c2bdf.
All local upstream/CORE HEADs API-matched and clean. Source locks, classification,
coverage and helper evidence are ignored under build-evidence. Remaining settings
getters/parser integration and lifecycle contract questions are in COMPONENT_TODO.
PR29 remains draft/unmerged. Hosted component workflows still require default-
branch installation; no hosted Linux/GCC or hardware result is claimed.

---

# Latest component checkpoint - 2026-10-24 (batch12)

Goal remains active across48 inventoried implementations. Added62 driver cases:
27 Teensy PWM across4.0/4.1/MicroMod and35 SAM3X8E serial across UART/USART1.
Original production sources, actual board/device headers and pinned SDK register
layouts compile unchanged; host memory, clock and IRQ callbacks model hardware
boundaries. No production or concurrent CORE checkout changes, no merges.

One cumulative Windows Clang ASan/UBSan gate covers27 compatible suites:
404 cases =369 clean +34 correct expected assertion regressions +1 fan-only
passed-assertion diagnostic. Two of the34 assertion cases also reproduce exact
SAM callback type diagnostics; they are counted once, with explicit mixed labels.
Zero unexpected failures/skips. All84 reporting helpers pass9.514s; actionlint
and whitespace pass. Two new narrowly scoped SAM diagnostic expectations retain
the actual callback defect; no blanket sanitizer suppression.

SAM regressions cover RX disable writing IER instead of IDR, secondary realtime
routing to the primary handler, and USART1 TX pin peripheral selection. The
secondary callback also has a char versus uint8_t signature mismatch. Correct
assertions and repair/removal guides remain in the suite KNOWN_BUGS.md. Reporting
now distinguishes mixed assertion/diagnostic cases without double counting or
claiming their assertions passed.

Fresh local LLVM selected-file coverage: Teensy pwm.c88/88 lines100%,31/37
branches83.8%,6/6 functions; SAM serial.c274/278 lines98.6%,100/108 branches92.6%,
38/39 functions. Fresh counter paths max210 characters; strict profiling checks
pass. These are selected-file host results, not whole-driver/board coverage.

Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
iMXRT1062 d1f8d1ed904242ee08b0a5583e78f490afd9ae93;
SAM3X8E2321092b02cbbdecf2eba2b168a74b085e573418;
Teensy SDK7f107ee0a309f3813ed13f0d8f615497eca2ee49;
Arduino SAM SDK790ff2c852bf159787a9966bddee4d9f55352d15.
Source locks and local evidence live in ignored build-evidence. Separate Driver
tests choices added for both suites. PR29 stays draft/unmerged; fork default
branch still registers only Core tests and Reusable host tests. No hosted GCC,
Linux, full ARM SDK or physical-board success is claimed. Remaining public APIs,
other modules and SAMD21 legacy support boundary are in COMPONENT_TODO.md.

---

# Latest component checkpoint - 2026-10-24 (batch11)

All-plugin/driver/CORE goal remains active across48 inventoried implementations.
No production sources or concurrent CORE work changed. Existing PR29 verified
OPEN/draft/unmerged at prior pushed head20fa750. Fork still registers only Core
tests and Reusable host tests; no hosted component success or merge is claimed.

Added37 cases:18 H7 (nine each H743/H723),9 F1 and10 F3. All three have separate
Driver tests choices and immutable host_bits32 source plans. One cumulative
Windows Clang ASan/UBSan gate covers all25 compatible suites:342 cases =314 clean
+27 correct known assertion regressions +1 previously scoped fan diagnostic.
Zero unexpected failures/skips. All83 CI/reporting helpers pass9.325s; actionlint
and whitespace pass. No new sanitizer allowance. New STM32 sources/fixtures stay
-Werror; native LPC fixed-address cast warnings remain visible under one narrow
original-source warning rule, and its fixture remains strict.

H7 compiles original Src/flash.c and original Inc/flash.h in actual source-supported
H743 dual-bank/H723 single-bank configurations. Inspected CMSIS/HAL headers define
8 sectors and32-byte flash words for both; BANK_2 only applies to H743. The host
HAL uses the real32-bit DataAddress third argument. Cases cover bank/sector
selection, aligned and exact-length36-byte source writes with zero-padded tail,
readback/unchanged handling, unlock/erase/first/second word failures and retry.
No invented16-byte write configuration is compiled despite the source comment.

F1 uses the shared halfword fixture with its actual page erase layout and linker
page-count/address symbols. Its unlock status is unchecked; locked erase errors
are returned by the HAL model rather than becoming fixture assertions. Erase
retry/failure, both halfword failures, recovery and copy/read controls pass.
Existing F4/F7 layout/lock checks remain intact and pass the cumulative gate.

F3 keeps FLASH_TARGET calculation unchanged. Dedicated test-process mappings
supply actual F303xC flash base0x08000000 and size register0x1FFFF7CC with2KB pages.
Separate128/256KB cases validate end-minus4KB target selection; full2KB-page,
read/unchanged, unlock/erase/program failure and retry controls execute. One new
correct first-halfword failure assertion reproduces its F7-like overwritten
status defect. Exact WILL_FAIL/known_bug plus dated guidance retain the proper
false result/immediate-stop contract without changing firmware.

Initial cumulative execution caught an intermittent address collision in the old
32-bit LPC fixture. Its original module does not convert RAM pointers to32-bit
integers, so that host restriction was unnecessary. It now uses native64-bit RAM
pointers with unchanged32-bit physical flash addresses and normal ASLR. Mappings
still refuse occupied addresses. All10 affected cases pass three repetitions,
then cumulative strict classification and fresh coverage. Failed evidence is kept
as lpc-batch11-address-collision.xml. Earlier passing suites were retained after
this isolated repair; they were not repeatedly rerun. LPC CORE2048 allocation/
4096-copy compatibility remains unresolved and is not masked by padded tests.

Fresh LOCAL LLVM compiled-file/configuration coverage, strict profiling checks pass:

| Suite / original selected file | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| driver_stm32h7_flash / Src/flash.c | 21/21 (100%) | 12/12 (100%) |
| driver_stm32f1_flash / Src/flash.c | 20/20 (100%) | 10/10 (100%) |
| driver_stm32f3_flash / Src/flash.c | 20/20 (100%) | 6/6 (100%) |
| driver_lpc176x_flash / src/flash.c, native host repair | 14/14 (100%) | 4/4 (100%) |

Maximum counter paths219/220/214/213 in fresh short builds. These are selected
storage-module results including retained regressions, not whole-driver/SDK/board
coverage. No Linux/GCC execution, physical flash/cache/IRQ timing or ARM firmware
build is claimed. Default-branch workflow installation remains unavailable.

GitHub-resolved locks match clean unchanged sources:
H7bfe5d4f6ec271cc9929336244c3b1c8e55d1d040 (dresco/STM32H7xx),
F1c22362352f6abeea94897bb0346ae8042cdf3210,
F39a40877b87b6fffbb475f753f0e12cc6c5126770,
COREb01f481072edecac33d5e40c25869359a5b3fa1f.
LPC source remains ea6e9f78fa349e86fbd58a203760b614f513684a; its updated native
source lock is part of this checkpoint. Ignored build-evidence/*batch11* contains
classification, locks, coverage XML/JSON/HTML and logs. Local short builds:
build-sh7-asan/build-sf1-asan/build-sf3-asan; PATH needs LLVM bin plus its
i686-w64-mingw32/bin for STM32 ASan DLLs. LPC now uses the normal native LLVM bin.

Continue the remaining driver families and untested plugin modules/configurations.
No full-goal completion claim, CORE edits or merges.

---

# Previous batch10 checkpoint - 2026-10-24

All-plugin/driver/CORE goal remains active across48 inventoried implementations.
No production sources or concurrent CORE work changed. Continue PR29, freshly
OPEN/draft/unmerged. Fork still registers only Core tests and Reusable host tests;
component dispatch/32-bit runtime installation awaits default-branch workflow
installation. No hosted component run or merge is claimed.

Added27 driver cases:9 STM32F4 flash,8 STM32F7 flash and10 LPC176x IAP storage.
All three have separate Driver tests choices and immutable source plans with
host_bits32. One cumulative Windows Clang ASan/UBSan gate covers all22 compatible
suites:305 cases =278 clean +26 correct known assertion regressions +1 previously
scoped fan callback diagnostic. Zero unexpected failures/skips. All83 CI/reporting
helpers pass17.915s; actionlint/whitespace checks pass. No new sanitizer allowance.
Existing plugin/CORE source warning policies remain; these new storage sources
and their fixtures compile with -Werror.

STM32 cases compile original flash.c with -m32, a pointer-width assertion and
linker-style region/sector symbols. No original pointer type or source is patched.
Shared HAL fixture models the distinct F4/F7 erase structures, unlock/erase/
halfword program/lock, byte output and failure state. Cases cover read/copy,
unchanged suppression, unlock failure, F4 erase retry, exhausted erase failure,
first/second halfword failure, recovery and selected word-aligned buffer sizes.
CORE nvs_buffer_init253 explicitly requires word alignment. These helper tests
are not complete CORE settings boot/integration or real STM32 HAL execution.

F7 first-halfword write failure is a confirmed source defect: its second call
unconditionally overwrites failure status with success, continuing and returning
true despite missing data. One exact program_first_failure WILL_FAIL/known_bug
retains the correct false assertion, with dated source/removal guidance. F4's
corresponding failure path and F7's second-halfword failure controls pass.

LPC tests compile original src/flash.c and map its fixed0x78000 region inside the
dedicated test process. Windows VirtualAlloc refuses an occupied address; Linux
MAP_FIXED_NOREPLACE is authored but not executed here. Simulated IAP callbacks
validate sector29, preparation/blank-state requirements, writes and IRQ restoration.
Cases cover erased reads,1024/4096 copy/readback, unchanged suppression, failure
at either preparation/erase/copy stage and retry. The2048 configured-size case
supplies4096 source bytes because original code copies4096 except for size1024.
It does not establish safety for normal CORE2048 allocation; unpadded overread is
not reproduced. Earlier IAP errors are overwritten in source; provider state
preserves failed prerequisites so final copy reports failure. Immediate abort,
allocation/copy-size compatibility and full CORE integration remain TODO.

Reusable jobs now install gcc-multilib/libclang-rt-dev only for source-locked32-bit
plans; existing plans default64. Host width is validated before source resolution.
Two new helpers verify default/accepted/rejected widths; component plan checks
also validate width metadata. The target Linux STM32 flags disable PIE to retain
absolute sector-symbol semantics. No Linux/GCC/multilib execution is claimed until
actual hosted runs exist. Source and fixture SDK boundaries remain simulated.

Fresh LOCAL LLVM compiled-file/configuration coverage, strict profiling checks pass:

| Suite / original selected file | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| driver_stm32f4_flash / Src/flash.c | 20/20 (100%) | 12/12 (100%) |
| driver_stm32f7_flash / Src/flash.c | 19/19 (100%) | 8/8 (100%) |
| driver_lpc176x_flash / src/flash.c | 14/14 (100%) | 4/4 (100%) |

Maximum counter paths220/223/213 in fresh short builds. These numbers cover only
three storage modules, including the retained F7 regression; no full-driver,
board, cache/IRQ timing, ARM firmware or real SDK validation is claimed.

GitHub-resolved locks match unchanged clean original sources:
STM32F4a6318ac92f079f49fab91687530f832997396edc,
STM32F785e6e800b16fb1a46bc00b87b7015489b9d3ec93,
LPC176x ea6e9f78fa349e86fbd58a203760b614f513684a,
COREb01f481072edecac33d5e40c25869359a5b3fa1f.
Ignored build-evidence/*batch10* contains immutable source locks, classification,
coverage XML/JSON/HTML and logs. Local short builds are build-sf4-asan,
build-sf7-asan and build-lpc-asan; PATH needs LLVM bin plus its i686-w64-mingw32/bin
for32-bit ASan DLLs. Historical compatibility limits remain unchanged.

Continue remaining driver families and plugin modules/configurations with public
interfaces. Do not narrow the full goal to these storage helpers, modify CORE or
merge PRs. The requested full supported coverage is not complete.

---

# Previous batch9 checkpoint - 2026-10-24

All-plugin/driver/CORE goal remains active across48 inventoried implementations.
No production sources or concurrent CORE work changed. Continue existing PR29,
freshly verified OPEN/draft/unmerged. Fork still registers only Core tests and
Reusable host tests. No hosted component run or merge is claimed.

Added34 registered cases:21 Bluetooth HC-05 and13 embroidery reader cases. Both
suites are now selectable in Plugin tests with their own immutable source plans.
One cumulative Windows Clang ASan/UBSan gate covers all19 compatible suites:
278 cases =252 clean +25 correct known assertion regressions +1 previously scoped
fan callback diagnostic. Zero unexpected failures/skips. All81 reporting/helper
checks pass17.050s; actionlint/whitespace checks pass. No new sanitizer allowance.
Source warnings remain visible under documented rules; fixtures retain -Werror.

Bluetooth compiles original hc_05.c with actual CORE stream registry/selection,
I/O registration and EEPROM/CRC. Simulated UART module replies, ticks and STATE
IRQs exercise all four AT command stages, failure/timeout, custom name, baud and
handler restoration, manual enable/disable, missing dependencies, port settings,
claimed-pin rejection, reports and fresh-process persisted auto-configuration.
Actual CORE selects/restores streams and sends the welcome message; no stream
switch stub is used. No radio/hardware or full protocol execution is claimed.

Two correct regressions reproduce original source defects and retain exact
WILL_FAIL/known_bug labels plus dated source/removal guidance in KNOWN_BUGS.md:
- Factory default selects highest free STATE pin but load rejects it using
  >= port_max, although CORE port_max is the highest valid index. No setup runs.
  Other workflow controls explicitly select the valid lower pin through settings.
- An enabled, boot-high STATE input selects Bluetooth and sends welcome but its
  connection predicate stays false; setup updates only a local variable.

Reserved options from erased storage are masked to the defined enable bit in
fixture getter checks; their broader Format_Bool contract remains a TODO. Shared
MPG mode and IRQ-provider failure notification remain untested, not excluded.

Embroidery compiles original tajima.c/brother.c readers with actual CORE VFS and
embedded backend. Valid DST/PES fixtures cover metadata/counts/dimensions/palette,
small/large signed movement, jump/trim/stop/color/end and format fallback/rewind.
No replacement decoder or private state forcing. Results omit the uncompiled
embroidery.c job coordinator: rendering, planner/needle synchronization, settings,
SD hardware and physical stitch timing remain. Mixed-axis flag precedence and
sequin lifetime need contract review before assertions.

Fresh LOCAL LLVM compiled-file/configuration coverage, strict profiling checks pass:

| Suite | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_bluetooth / HC-05 serial mode | 122/124 (98.39%) | 56/66 (84.85%) |
| plugin_embroidery_readers / two readers | 168/177 (94.92%) | 96/108 (88.89%) |

Reader detail: Brother62/63 lines and26/28 branches; Tajima106/114 and70/80.
Both fresh short builds have maximum counter path212. No source exclusions or
whole-plugin/catalogue claim. No hosted/GCC/firmware/board validation is claimed.

GitHub-resolved locks match clean unchanged sources:
Bluetooth3fc40665af6d49250f09fec665ec267a988ee148,
embroidery9a112c3c2509563aa5c745d5773aba5a62046d7c,
COREb01f481072edecac33d5e40c25869359a5b3fa1f,
EEPROM0c278db74edc38303b9d86583a7d51a1ec1be51e.
Ignored build-evidence/*batch9* contains source locks, strict classifications,
coverage XML/JSON/HTML and validation logs. Prior source compatibility limits and
known assertions remain unchanged. Full goal is not complete.

Next: remaining supported modules/configurations and additional driver families.
STM32F4 sourcea6318ac92f079f49fab91687530f832997396edc was fetched/read only;
flash.c uses linker-address symbols and a32-bit target address contract. Establish
an appropriate target/linker fixture before runtime assertions; no driver result
or SDK/board build is inferred from this source review.

---

# Previous batch8 checkpoint - 2026-10-24

Goal remains active across48 inventoried implementation repositories. No production
sources or concurrent CORE work changed. Existing PR29 verified OPEN/draft/unmerged.
Fork still registers only Core tests and Reusable host tests: component workflows
await default-branch installation. No merge or hosted component success claimed.

Added20 registered cases:9 Trinamic runtime cases plus7 plasma runtime cases and
4 fresh-process EEPROM setup/cleanup cases. One cumulative Windows Clang ASan/UBSan
gate covers all17 current-compatible suites:244 cases =220 clean +23 correct known
assertion regressions +1 previously scoped fan callback diagnostic. Zero unexpected
failures/skips. Both expanded suites pass23/23. All81 reporting/helper checks pass
9.554s; actionlint and whitespace checks pass. Source warnings remain visible under
documented rules; host fixtures remain -Werror. No new exception/diagnostic waiver.
Formatting reordered two dependent headers; restoring the host include first fixed
those fixture builds. Completed unaffected suite results were retained, not rerun.

Trinamic enables actual status polling and dynamic current in nine targets while
keeping the existing default targets. Registered task/stepper/limit callbacks cover
hold/block/idle current, quiet polls, persistent/recovered over-temperature reports,
moving feed-hold requests and homing seek/locate sensitivity plus IRQ routing.
Disable retains the homing-rate callback but inactive axes prevent register writes;
assert that observable behavior. The source Pending holding-state assignment is
commented out; no private state is forced. Current is configured/register behavior,
not measured electrical current; actual homing motion and stall timing remain.

Plasma saves its registered reboot-required Mode setting through actual EEPROM/CRC
then boots a fresh process into Arc-ok or Up/down mode. Actual CORE spindle registry,
I/O registration and secondary-stepper polling execute with simulated torch/pins,
clock and controller state. Cases cover successful ignition/shutdown, three failed
attempts, third-attempt success, lost-arc hold requests, positive/negative Z output,
velocity lock/recovery and reset. No private init_ok/state handler is assigned.
Mode3 does not claim cutter inputs: fixture setup now initializes physical values
without demanding those unregistered descriptions. Full CORE suspension, primary XY
motion, voltage/PID regulation, pierce/cut-height planner moves, PowerMax, expression
integration and physical timing remain. These are not board/firmware build results.

Fresh LOCAL LLVM compiled-file/configuration coverage, strict profiling checks pass:

| Suite | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_trinamic / trinamic.c | 446/1001 (44.56%) | 192/652 (29.45%) |
| plugin_plasma / THC + two importers | 457/869 (52.59%) | 222/553 (40.14%) |

Trinamic gained126 covered lines while the denominator expanded885->1001 because
polling/dynamic configurations now compile. Plasma gained194 covered lines with
unchanged denominator: THC361/764; importers remain LinuxCNC51/56 and SheetCam45/49.
Fresh short coverage builds have maximum counter paths223/225. No source exclusions,
whole-plugin/library/catalogue coverage claim or reused old counter graphs.

GitHub-resolved locks match unchanged clean source checkouts:
COREb01f481072edecac33d5e40c25869359a5b3fa1f,
motor9229617c1d8a3cc7a71fd584896500a779978b02,
plasma d2f91b5887db6550ddec0fc0229cd87ec0af1a56,
EEPROM0c278db74edc38303b9d86583a7d51a1ec1be51e,
Trinamic library9b304175318d93818c8967faadc89dd101b17e92 (explicit RP2040 gitlink pin).
Ignored build-evidence/*batch8* contains strict classifications, source locks, logs
and coverage XML/JSON/HTML. Existing source compatibility limits remain recorded.
No hosted/GCC/hardware validation is claimed. Continue remaining supported modules
and configurations; the all-plugin/driver/CORE goal is not complete.

---

# Previous batch7 checkpoint - 2026-10-24

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
