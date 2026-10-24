# Plugin and driver coverage - 2026-10-24

Goal: meaningful functional tests across all plugin/driver catalogue implementations
and CORE. Never edit CORE/plugin/driver production sources or merge PRs. Preserve
other work and use substantial batches. CORE coverage continues in its active chat.

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

CORE dependency: b01f481072edecac33d5e40c25869359a5b3fa1f. Sources are unchanged.
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

Next: cumulative local component sanitizer/strict validation and CI-helper gate,
source-filtered coverage, then one coherent commit/delivery checkpoint. Hosted
validation has not run for this branch. New manual workflows require installation
on the default branch before GitHub exposes their dispatch controls; do not merge
them yourself or claim hosted success. Continue highest-value source workflows
while hosted workflow availability is pending. No full-coverage claim is made.
