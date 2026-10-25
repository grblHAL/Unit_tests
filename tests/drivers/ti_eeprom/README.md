# Shared EEPROM host cases

The TM4C123 and TI shared suites compile their own original EEPROM implementation
against these common public NVS scenarios. No production functions are copied.
Real CORE crc.c supplies checksum algorithms. Original source-local malloc is
redirected only for bounded allocation refusal; normal allocations use the host
allocator and original free. SDK EEPROMRead/EEPROMProgram retain real vendor
prototypes and operate on word-aligned bounded host storage.

CRC-neutral cases run once per actual source. CRC layout/read cases run with both
source-supported checksum widths. See each suite KNOWN_BUGS.md for exact expected
assertion failures and scope. Both direct-copy else paths remain uncovered because
original alignend is always1..4; no source exclusions or fake state are used.
