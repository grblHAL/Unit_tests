# Known defects

Source for both entries: grblHAL/Plugin_EEPROM
0c278db74edc38303b9d86583a7d51a1ec1be51e, CORE
b01f481072edecac33d5e40c25869359a5b3fa1f. Confirmed 2026-10-24 under
Windows Clang ASan/UBSan without sanitizer diagnostics.

## Block reads discard I2C transfer failure

`eeprom_24LC16B.c` and `eeprom_24AAxxx.c` call `i2c_nvs_transfer`
in `readBlock` without checking its result. With checksums disabled they
return success even when the driver reports a failed read and the destination
remains untouched. Correct `plugin_eeprom.{16,32,128,1024}_read_failure`
assertions require failure propagation and currently fail at `CHECK(!ok)`.

Proposed upstream fix: stop and return failure when any payload read fails;
review checksum-byte read failure handling as well. No plugin code was edited.

## Two-byte-address EEPROM writes checksum after failed payload transfer

`eeprom_24AAxxx.c` enters its checksum block after the payload write fails.
`plugin_eeprom.{32,128,1024}_checksum_write_failure` requires the failed
operation to stop without writing a checksum for an unwritten payload. Each
fails at the exact transfer-count assertion; the overall result already reports
failure. The 24LC16B control correctly guards checksum writes on transfer success.

Proposed upstream fix: require `res == NVS_TransferResult_OK` before writing
checksum bytes, as the single-byte-address implementation already does.

Each listed regression has an explicit CMake `WILL_FAIL` and `known_bug` label.
Keep the correct assertions. When upstream fixes a defect, remove only its
named properties and resolved entry and rerun this suite and strict summary.
No sanitizer exceptions, source exclusions or hardware claims are involved.
