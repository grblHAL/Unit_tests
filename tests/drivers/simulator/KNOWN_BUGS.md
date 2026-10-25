# Known defects

## EEPROM block checksums are not written or read from the payload - 2026-10-24

Source: grblHAL/Simulator 150e3f935e4b7cab7b90263b6b90b78912d9158d,
`src/grbl_eeprom_extensions.c`, with CORE b01f481072edecac33d5e40c25869359a5b3fa1f.

`driver_simulator.checksum_write` uses the public block writer with checksums
enabled and requires the stored trailing checksum to equal CORE's checksum of
the original payload. It fails: the writer decrements `size` to zero before
checking `size > 0 && with_checksum`, so no checksum is written. Inside that
currently unreachable block the source pointer, destination and high-byte shift
also need review; a fix must compute from the original payload, store after it,
and use an eight-bit high-byte shift.

`driver_simulator.checksum_read` preloads a valid payload and checksum and
requires the public reader to accept them and return the payload. Payload bytes
are correct but validity is false: the reader calculates from the advanced
output pointer rather than its saved start. The caller buffer has spare room,
so this regression does not cause an overread or need sanitizer allowances.

Both tests failed their exact assertions under Windows Clang ASan/UBSan.
Each retains its correct assertion and has a named `WILL_FAIL` plus `known_bug`
label. No production code was changed. When fixed upstream, keep the tests,
remove their individual CMake expected-failure properties and this entry, and
rerun the driver suite with strict summary. Check both one- and two-byte checksum
configurations when implementing the upstream fix.
