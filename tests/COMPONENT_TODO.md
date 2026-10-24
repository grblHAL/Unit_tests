# Remaining component work

This is the continuation list, not a list of waived source exclusions.
Repository-wide status is in COMPONENT_INVENTORY.csv. All recorded percentages
cover only instrumented files/configurations. Never edit firmware/plugin sources
or force private state to enter a path.

## Next source families

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
