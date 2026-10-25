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

## littlefs adapter discards physical read and program failure - 2026-10-24

`eeprom_lfs_hal.c` returns LFS_ERR_OK after invoking the physical provider's
read/write callbacks without checking their boolean results. The littlefs
block-device contract requires an error when storage fails.
`plugin_eeprom.lfs_read_failure` and `plugin_eeprom.lfs_program_failure` use
valid partition geometry and aligned requests, with an ordinary physical
EEPROM provider returning failure. Both correct LFS_ERR_IO assertions fail;
the provider calls and checksum-disabled flag are independently checked.

Source/CORE revisions are the same as above; actual littlefs headers/library
6cb4e86540eca0d9ba62500a298385c9d863c8be define the callback contract.
Windows Clang ASan/UBSan reproduced both without a sanitizer diagnostic.
Successful format/write/unmount/remount/read and settings-partition isolation
pass against the real littlefs library and actual I2C EEPROM implementation.

Proposed upstream fix: translate failed physical read/write calls to LFS_ERR_IO
instead of unconditional success. Retain the two tests; remove only their
individual WILL_FAIL/known_bug properties and this entry after the source fix
passes the suite and strict summary. No production source changes were made.
