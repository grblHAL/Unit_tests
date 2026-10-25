# Known regressions - 2026-10-24

Source6adcc848946fe69075f6ed062afa31f11c5a4c97, original base/eeprom.c.

- crc1_checksum_layout and crc2_checksum_layout: checksums overwrite the first
  payload bytes, rather than being stored after payload. The two-byte high part
  also uses checksum>>1 instead of >>8. Assertions preserve payload and require
  the trailing original CORE checksum. No malformed input or memory fault.
- crc1_checksum_read and crc2_checksum_read: independently seeded valid payload
  plus trailing checksum is rejected because readBlock compares prefix bytes.
- crc2_program_failure, crc2_allocation_write_failure and
  crc2_allocation_read_failure: hardware/heap failure is ignored and the API
  reports success without transferring data. Same safe failure injection as
  the standalone TM4C123 suite; no uninitialized data or memory-safety failure.

Upstream repair should append/check trailing CRC and propagate failures. Remove
only resolved exact WILL_FAIL/known_bug labels and corresponding entries once
correct assertions pass. No sanitizer diagnostic allowance.

# Scope

Tests compile original shared driver/tiva/BoosterPack headers with pinned
TivaWare vendor headers from a declared source mirror. Public
CNC_BOOSTERPACK_A4998=1 matches the selected original board map. Host EEPROM
implements aligned bounded transfers; original CORE crc.c computes CRC. Only
source-local malloc is replaced for safe allocation refusal.

This is a standalone shared-module candidate suite, not a TM4C1294 parent-driver
build. That archived parent pins shared3e7873dba011c0cb405c31771720a189b8841760,
which differs from this explicitly tested current shared candidate. Do not silently
substitute it or claim parent-driver/board/SDK-link success. MSP432E-specific
headers/configuration and full controller integration remain untested.
