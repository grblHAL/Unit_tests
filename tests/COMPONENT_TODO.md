# Remaining component work

This is the continuation list, not a list of waived source exclusions.
Repository-wide status is in COMPONENT_INVENTORY.csv. All recorded percentages
cover only instrumented files/configurations. Never edit firmware/plugin sources
or force private state to enter a path.

## Next source families

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
- Assess the next catalogue family (I2C keypad) and real host-testable RP2040/
  ESP32 driver helpers; do not treat firmware builds as hardware validation.
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
- For RP2040 and ESP32, identify real host-testable driver helpers and required
  SDK/board build contracts before enabling suites. A firmware compile does not
  prove GPIO timing or physical hardware behavior. Other drivers and third-party
  plugins retain explicit not-yet-assessed inventory rows.

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
