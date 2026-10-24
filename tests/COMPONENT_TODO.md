# Remaining component work

This is the continuation list, not a list of waived source exclusions.
Repository-wide status is in COMPONENT_INVENTORY.csv. All recorded percentages
cover only instrumented files/configurations. Never edit firmware/plugin sources
or force private state to enter a path.

## Next source families

- Batch18 now validates WebUI13 helper/provider and MSP432P15 primary UART cases
  together. WebUI measured args/provider41/41 lines,41/44 branches, not HTTP/backend
  coverage. Primary MSP108/108 lines,37/41 branches uses original driver/board/
  TI/CMSIS headers and real CORE stream lifecycle. Retain pending-TX loss when
  disable_rx(true) clears all IE bits; no sanitizer exception.
- MSP secondary SERIAL2_MOD expands to A2, while its status array uses #if and
  other declarations use #ifdef. Do not activate that instance or force a status
  table memory failure; establish/fix the guard contract. RTS bit-band mode,
  alternate SDK configurations, target link and actual hardware remain untested.
- Remaining source review: MSP430 d6d11c74b87d4fd456a01dd2f45579dcd7ad6b73 uses
  external EEPROM and MCU interrupt/register syntax; its CORE gitlink is
  31f6a4bf04b3136e653c53df586d3351fa9cb7b9. MSP432E
  eb6371652d2b0bed1e79746e4505a8bd279be8b7 and PSoC5
  c9d721259783ca578ee1b0c3f6111839610c26a4 READMEs end support at CORE20250518,
  both pin070f80cc5c0d095ff63d5980795b5a15c5bb0202. MSP432E pins shared6adcc848,
  whose EEPROM is tested separately with Tiva headers, not that SDK/parent build.
  PSoC5 needs generated project.h/UART APIs and keeps NVS inside driver.c. Pin
  original SDK interfaces; never extract firmware functions or silently fall back
  to legacy CORE. No actual runtime/compile result for these remaining drivers.
- ATCi18 cases now exercise original registered settings/M-code/travel/sensor
  callbacks at671f145530ec8ec9f5828897477dc0192593b3d8:292/305 lines,156/193
  branches. Retain M960 P0 regression: validate consumes words.p, execute tests
  consumed flag and never disables. Logical host AUX inputs are not actual board
  maps; full parser/planner/native envelope and LongBoard validation remain.
  Clipped paths return without chaining native apply_travel_limits; an initial
  exact callback-count assumption was removed, with all coordinate assertions
  retained and unrestricted chaining separately tested. Establish integration
  contract before classifying that source path.
- MPG transport21 cases at503b422d0aa92c4d2b6a190e92ce25344bcc629e cover valid
  plain/framed RX/TX, duplicate suppression, ACK/NAK/retry budget, normal capacity
  backpressure, chunks, reset and resource/baud/diagnostic workflows. Original
  .c404/468 lines,146/234 branches; public wire header25/25 lines,10/10 branches.
  Stream registration is captured, not actual CORE MPG switching/broadcast or
  tool-ACK suspend. Eight local authoring cases (affected suite29/29 ASan/UBSan) now cover pending
  transport persistence, in-flight timeout/attempt changes, output discard/stale
  ACK isolation, payload limit, restore and plain/framed byte-only UART. Not yet
  cumulatively validated/delivered. Remaining NVS clamping and
  controller/physical transport integration need the next substantial group.
- PicoHAL babac83b030fdc053b66f711e82f92b6fdfcc455 fails unchanged-source syntax
  compilation against pinned CORE: on_probe_fixture_ptr and grbl.on_probe_fixture
  removed; on_probe_completed argument changed. No obsolete-type aliases, header
  bypasses, old-CORE fallback or runtime/Actions choice. Exact evidence locked in
  build-evidence/picohal-batch17-source.json and picohal-syntax.log.

- Sienci RGB24 cases now cover original legacy STATUS_LIGHT_ENABLE2 and advanced3
  sources at df3409058f8bb9c202f560e562bb2671a0829561(default SLB32_DEV). Combined
  533/557 lines,267/311 branches. Retain stale legacy delayed tool-color regression.
  Remaining regions include optional absent callbacks, offboard green override and
  live state-transition animation edges; actual CORE scheduler/parser/hardware
  still need integration. Workflow names use suite default instead of master.
- FlexGPIO17 cases at bc8dab40162b49718179bffe973c4533fc73436f cover257/272 lines,
  123/150 branches. Eight additional local authoring cases now exercise public pin value callbacks
  across both axis configurations, configuration-send failure and input-read
  recovery without false edges (8/8 ASan/UBSan and strict checks). Await cumulative
  delivery; no updated coverage percentage yet. Registered descriptors are captured,
  not passed through actual CORE ioports aggregation/remapping; multiple bank
  offsets, controller/physical IRQ/I2C timing and no-MCU-IRQ mode remain untested.
  Retain exact IRQ-disable/pull-mode result regressions and four Clang transparent-
  union call diagnostics, with strict scoped manifest/labels and no suppression.
- Datron-style RGB672ebd8beeed746b5c668be18b4e4c48b6c14883 fails unchanged-source
  current-CORE syntax compilation: status_light.c207 private static bit_count
  conflicts with CORE nuts_bolts.h541 declaration. Windows also reports ffsl
  undeclared at427. No source macro renaming/header bypass, runtime/Actions choice
  or old-CORE fallback was added; exact source/evidence is in build-evidence.

- TM4C123 EEPROM12 and UART012 cases now run unchanged sources with real driver/
  board/TivaWare headers and CORE CRC/stream support. Shared TI EEPROM11 cases
  test its current standalone candidate, not archived TM4C1294 parent gitlink.
  Retain12 correct new known assertions: TM4C123 CRC8 trailing-address mismatch,
  each module's hardware/malloc failure reporting, shared CRC payload overwrite/
  prefix reads and UART realtime dispatch at full ring capacity. No diagnostic
  allowance or firmware fix. Source-specific reports/guides are in each suite.
- Both EEPROM files cover49/51 lines and17/20 branches. Their only missing lines
  are direct EEPROMProgram/EEPROMRead else paths: alignend=4-((alignstart+size)&3)
  is always1..4, so alignstart||alignend cannot be false for valid transfers.
  Do not manufacture invalid states or exclude these branches. UART0112/112 lines,
  44/48 branches; UART1 cannot be selected without editing its unconditional
  BACKCHANNEL source header, which is forbidden. Full SDK/link/physical work remains.
- TivaWare original vendor headers come from declared mirror yuvadm/tiva-c at
  c23bf8ba7a82b20421aa04d4df3f77501c5883ea. No newer official SDK provenance is
  claimed. Parent TM4C1294 pins TI shared3e7873dba011c0cb405c31771720a189b8841760;
  separately tested shared candidate6adcc848946fe69075f6ed062afa31f11c5a4c97 must
  never be silently substituted for the parent's dependency or called a parent build.

- Virtual Inputs now links real CORE probe.c and formatting.21 cases cover shared/
  separate sensors, physical/virtual toward-away input, inversion, registered
  commands/counters and lifecycle. Selected source146/146 lines,66/71 branches;
  full G38 jobs, legacy missing callbacks, optional private init and alternate
  command base remain. Homing Acceleration13 cases cover requested override and
  restoration for4 axes; selected source101/101 lines,43/44 branches. Real
  settings.c backup/parser and actual planner/stepper homing remain untested.
- Homing Acceleration source uses NULL prior unit hook as install sentinel; with
  no previous hook, repeated settings changes can capture its own wrapper. Keep
  this source-review concern separate; do not force recursive stack failure.
- Panel09c90184288a09d7357fd994c395911dec38683f fails syntax compilation against
  CORE b01f481 for CAN(PANEL_ENABLE2/CAN_PORT1) and documented Modbus configuration
  (PANEL_ENABLE1/MODBUS_ENABLE1/MODBUS_MAX_ADU_SIZE64): panel.c707 calls
  system_execute_line with1 argument; CORE system.h330 requires2. An initial
  default15-byte Modbus probe also failed array initialization; that probe omitted
  the README-required64-byte option and is not an independent compatibility defect.
  No source aliases/edits, obsolete CORE fallback or runtime/Actions pass claimed.
- Earlier TI source review (TM4C123 EEPROM/UART now tested above):
  TM4C12942374d48ea5580c7912c999bf99e94fdd1c7e4ded is archived/unsupported per
  README and delegates to TI_SimpleLink_shared. MSP432P401R
  1fa8bc31d8e8669d4d569e768154a0532ec5311e uses external EEPROM or NVS_None;
  assess serial/helpers with pinned SDK. No driver execution/compilation yet.

- Four third-party suites now run unchanged sources: AUXP selected file45/45
  lines and24/24 branches; Interlock173/185 lines,67/84 branches; PneumaSeal
  128/141 lines,43/52 branches; Thermistor133/139 lines,68/74 branches. Remaining
  Interlock lines include settings getters and inverse-disable handling;
  PneumaSeal includes port setter/getter and integer getters; Thermistor includes
  port getter/availability and guarded conversion paths. Full public settings
  parser integration is still absent; captured registered callbacks only are tested.
- Interlock observes alarm/reset requests and suppresses writes at host boundaries;
  real controller shutdown, ISR ordering, other slot counts and multi-spindle scope
  remain. Unreadable monitoring deliberately follows source-documented fail-open.
- PneumaSeal delayed task requests/explicit expiry do not validate real scheduler
  timing or air pressure. Keep claimed-port remapping and programmed M5 ordering.
- Thermistor repeated settings-load hook ownership needs contract review; do not
  reproduce recursive callback failure. Invalid sensor samples interrupting the
  advertised consecutive alarm readings, and malformed/trailing calibration
  parameters remain unclassified. No new known runtime exception is registered.

- SAM3X8E serial now has dual-port queue/IRQ/callback/settings/suspend cases using
  actual SDK/device/board headers and CORE stream APIs. Retain three functional
  regression groups and exact secondary callback signature diagnostic. Primary
  SERIAL_PORT0 appears to omit its status array entry; do not force a memory
  failure or add an obsolete-type alias. Other port/format/error IRQ states,
  primary manual realtime enqueue, metadata detail and full controller jobs remain.
- Teensy PWM executes original code/board headers with pinned real SDK register
  definitions for4.0/4.1/MicroMod. Timer/fault side effects and real frequency/edge
  timing are not modelled. Type0 config/out paths are not returned by public claim;
  do not forge handles for coverage. Review five-slot ownership capacity without
  force-entering a memory failure. Shared FlexPWM channel polarity/compare
  preservation needs a supported multi-output board contract before classification.
- SAMD21 source55c61e6f028482fd90e77031802a3e391aa076a3 README ends support at
  CORE build20250518. Its grbl gitlink070f80cc5c0d095ff63d5980795b5a15c5bb0202
  is a potential explicit reference, not automatic fallback or a verified build.
  Its NVS routines live inside driver.c; do not extract/copy functions to inflate
  coverage. Serial/SDK fixtures and current-CORE compatibility remain untested.

- H7 flash cases exercise source-supported H743/H72332-byte configurations and
  distinct banks; no16-byte mode is exposed by the inspected source header. F1
  now has page HAL cases and F3 uses mapped register/flash geometry. Retain F3's
  first-halfword failure regression. Full driver/SDK/IO/serial/board scope remains.
- LPC now uses native-width host RAM pointers with original32-bit physical flash
  addresses. The initial32-bit Windows fixture suffered an address collision;
  do not restore that unnecessary pointer-width constraint or force an occupied
  mapping. Actual CORE allocation/copy-size compatibility remains unresolved.

- STM32F4/F7 flash helpers execute in32-bit host suites with shared linker-symbol/
  HAL fixtures. Retain F7 first-halfword-status regression. Linux multilib steps
  remain unverified hosted; actual SDK/cache/IRQ/serial/IO and board configurations
  remain. Current storage tests do not establish full-driver coverage.
- LPC176x IAP cases use a dedicated process-local0x78000 mapping and valid padded
  source buffers. Original implementation copies4096 unless NVS size is1024;
  CORE normally allocates2048. Resolve allocation/copy-size compatibility before
  claiming normal CORE integration. Do not reproduce an unpadded overread. Earlier
  IAP errors are overwritten; the provider preserves prepare/blank requirements
  so failed prerequisites produce final copy failure. Immediate abort and actual
  ROM/SDK/IRQ/board behavior remain unvalidated.

- HC-05 serial mode now executes AT success/rejection/timeout, stream switching,
  settings/report hooks and EEPROM restart through actual CORE stream/I/O APIs.
  Retain two source regressions: highest valid STATE pin rejected at load, and
  boot-high input never initializes the connection predicate. Shared MPG mode,
  failed IRQ registration notification and reserved option bits remain. Factory
  restore clears only the enable bit; clarify the bool getter contract before
  treating reserved erased bits as a separate defect.
- Embroidery DST/PES readers now execute valid metadata/movement/control records
  through real CORE VFS. The uncompiled embroidery.c coordinator still needs
  supported settings/file-open/render/job/needle-sync fixtures. Mixed-axis PEC
  flag precedence, DST sequin-state lifetime and coordinate unit integration
  require contract review. Do not imply reader coverage includes the coordinator.

- Extend Plugins_spindle beyond the tested GS20/MODVFD single-spindle protocols:
  other VFD commands/feedback, multiple registered spindles and output/stepper
  plugins remain. The actual coordinator/CORE transport/spindle registry and
  EEPROM-backed settings fixtures are reusable; retain real protocol differences.
- SD streaming has13 cases with real CORE VFS/stream/macro modules. Add remaining
  read ownership/job recovery paths, WebUI and full parser parameter/ATC fixtures
  only under supported configurations. The EOF extra-line assertions remain.
  FATFS/SD detection and YMODEM are separate untested implementations. Original
  fs_littlefs.c fails current-CORE syntax checking on removed vfs_path_t; record
  an explicit compatible reference before adapter runtime work, never alias it.
- Keypad now has I2C/UART jog, cancellation, override, callback and NVS restart
  cases. Retain four signed-char extended-command regressions and paired unsigned
  controls. Shared MPG, coordinate cycling with the real parser, macro/display
  modules, ring-buffer saturation and additional initialization paths remain.
  UART init reports allocation success despite failed stream opening; its bool
  contract remains a question, not a classified defect. Coordinate string
  formatting is a fixture boundary, not a tested CORE formatting contract.
- Networking common events/providers/enumeration/reports now execute with real
  locked lwIP headers. Actual Telnet/Websocket, DHCP, MQTT, FTP/HTTP/WebDAV and
  transport implementations remain. Do not equate service labels with listeners.
- Laser PPI and LightBurn default clusters now have functional callback/stream
  cases. Retain zero-PWM pulse regression; coolant/overdrive, scaling, alternate
  spindle selection and full parser/planner integration remain. Review PPI hook
  ownership on spindle changes before extending that scenario; do not fabricate
  ppi_spindle or static laser state. Cluster malformed/overflow contracts remain
  source-review work, not covered by the valid-stream cases.
- Plasma has materials/imports and fresh-process EEPROM boots into Arc-ok and
  Up/down modes. Actual registered spindle callbacks, public timers, ARC input,
  retries/loss, secondary Z step output, velocity lock and reset now execute.
  Voltage/PID regulation, pierce/cut-height planner moves, full CORE suspension,
  PowerMax and expression integration remain. Never set private init_ok or state
  handlers. Material add currently always returns true even if malloc fails
  (source598-622); public allocation-failure semantics remain unclassified.
- TMC2209 compiles actual plugin + library9b304175318d93818c8967faadc89dd101b17e92
  with simulated UART register replies, real CRC/IFCNT and EEPROM-backed restart.
  Dynamic hold/block/idle current, status polling/recovery, moving over-temperature
  hold requests and homing rate/IRQ callbacks now execute through public hooks.
  Debug/report modes, other chips and transport configurations remain. The
  holding-state Pending assignment is commented out in source; do not force it.
  Homing disable retains the rate callback but its inactive axes prevent writes;
  test that observable outcome rather than requiring callback removal.
  The library pin is an inspected RP2040 gitlink, not automatic fallback. Actual
  RP2040/ESP32 UART transports return static buffers with address0xFF on timeout;
  null reply behavior was not force-entered.
- Simulator VFS fails current-CORE compilation: removed vfs_path_t. The explicit
  driver gitlink reference executes nine cases with three known assertions;
  retain both incompatibility evidence and separate source locks. No fallback.
- Encoder: registered radio settings expose modes0-3; CORE rejects higher values.
  Establish a supported MPG/migration route before testing modes4+. Source does
  not copy provider velocity into its internal velocity field; live mode rebinding
  and per-device settings-slot assignment also need maintainer contract review.
  Do not forge persisted settings or private state to cover these paths.
- Odometer: all124 measured lines execute, but6 branch outcomes and other storage/
  axis configurations remain. Keep visible report-format warnings documented.
- RP2040 flash-copy and ESP32 partition NVS helpers now execute original source
  with simulated SDK boundaries. Other IO/serial/timing modules, SDK builds and
  board/hardware checks remain. RP2040 rounding test provides a padded page buffer;
  it does not prove arbitrary unpadded buffers safe. Keep multicore flash access
  as an explicit hardware contract. Other drivers and third-party plugins retain
  not-yet-assessed inventory rows.

## Current suites

- Misc: test valid servo-capability/ownership filtering and invalid selection
  through the parser, after confirming capability meaning in real drivers.
  RGB validation still has channel/brightness-specific errors to exercise.
  BLTouch and the other miscellaneous source files are not yet compiled/tested.
- Fans: fan_spindle_set_state is initialized NULL and its only later assignment
  is commented out (fans.c65/241); the fallback at229-232 is unavailable without
  implementation changes. Do not assign that private pointer in a test.
  The empty-body spindle enumeration callback at237/242 needs a valid registered
  spindle integration fixture, not fabricated state solely for two lines.
  One-, three- and four-fan configurations and stored port recovery remain.
- EEPROM: measured lines are covered for the tested chip/FRAM/littlefs layouts,
  but several branch outcomes and other supported configurations remain. The
  byte helpers discard I2C errors, so checksum-byte failure propagation needs
  maintainer/source review. Investigate bank-boundary reads against real chip
  addressing contracts. Do not manufacture impossible provider geometry.
- OpenPNP: add M143 raw-analog feedback after M145 scaling, further supported
  validation and jerk-enabled axis claims using real parser behavior. Detailed
  reporting without the real-position flag appears to leave print_position
  uninitialized at source review; confirm the intended M114 D/R contract before
  creating a deterministic regression. Do not accept incidental stack values.
- Simulator: eeprom.c's fseek-failure fallbacks have no proven ordinary-file
  trigger; do not corrupt private FILE state to execute them. The checksum writer
  block is unreachable because size is zero after its payload loop; retain the
  correct regression instead of forcing the branch. See its KNOWN_BUGS.md.

## Validation constraints

New manual workflows are not registered on the fork default branch yet; draft
PR29 remains unmerged and no hosted component run is claimed. Continue independent
source work rather than repeatedly polling or dispatching the same unavailable
workflow. Use one local/hosted checkpoint per substantial batch.

Windows coverage requires short writable counter paths. A real 263-character
path lost one .gcda file; that old report is rejected. Both classifiers now
reject Clang/GCC profiling errors even on expected-failure tests. Verified misc
coverage uses the shorter build-plugin-cov directory in the original attached
workspace, with maximum counter path226; it reads the isolated branch's source.
All five suites' accepted coverage result sets were checked for counter errors.
