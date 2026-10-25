# Known regressions - 2026-10-24

Source14fdf8de2126316c14d88656f3a19337800ad1c1, original eeprom.c, pinned CORE.

- crc1_checksum_read: valid payload plus trailing original CORE CRC8 is rejected.
  The one-byte readBlock path compares CRC with getByte(source), not source+size.
  The CRC2 read/layout and corruption controls pass. Append-only storage layout
  is required by the public NVS block interface; keep the correct assertion.
- crc2_program_failure: EEPROMProgram returns the real SDK NOPERM error and
  leaves storage unchanged, but writeBlock reports success unconditionally.
- crc2_allocation_write_failure and crc2_allocation_read_failure: scoped heap
  allocation refusal prevents the transfer, but unchecked-checksum transfers
  report success. No out-of-bounds access or uninitialized checksum is exercised.

Upstream repair should propagate allocation/program failure and use the trailing
CRC8 address. Remove only each resolved WILL_FAIL/known_bug label and this entry
when its correct assertion passes. No sanitizer diagnostic allowance.

# Scope

Original driver.h/tiva.h/board map and pinned TivaWare vendor headers compile.
The SDK checkout is a source mirror, not a new official SDK release claim.
Host EEPROM callbacks implement word-aligned transfers into bounded storage;
original CORE crc.c provides checksums. Allocation injection affects only the
original EEPROM source. Alignment scenarios vary valid address/length combinations
and verify adjacent storage. Native host pointers are safe here: original module
passes RAM pointers through unchanged. No physical endurance, write timing,
whole-driver, target SDK link or board validation is claimed. CRC-neutral cases
run once; only checksum behavior varies between CRC1/CRC2 configurations.
