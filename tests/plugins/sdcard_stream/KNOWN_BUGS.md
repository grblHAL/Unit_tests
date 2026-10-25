# Known defects

Source grblHAL/Plugin_SD_card d0fe753d622e79a60e54e729ba83f7207276114c,
CORE b01f481072edecac33d5e40c25869359a5b3fa1f. Original production code is
unchanged. These are host streaming tests with the real CORE VFS, embedded
filesystem, stream redirection and macro modules. The fixture exposes that
read-only filesystem at / through the public mount API; it is not SD hardware.

## EOF adds a blank line to already terminated files

file_read() clears file.eol when its read returns EOF. stream_read() then treats
the last line as unterminated and adds LF. The dump command similarly appends
ASCII_EOL. A four-line CRLF/LFCR/CR/LF fixture yields five logical line endings.
The named line_endings and dump cases retain the correct four-line assertions
and are individually WILL_FAIL/known_bug. Actual bytes and failure logs are
saved; ordinary unterminated job and dump controls pass and get the required
final newline. Proposed upstream repair: preserve final EOL state on EOF while
retaining CRLF/LFCR collapse. Remove only the resolved properties/entry after
both controls and the full suite pass. No sanitizer allowance is present.

## Scope and compiler warnings

Original plugin/CORE warnings are retained with the main harness's -Wno-error
production-source policy; fixtures keep -Werror. No clean-Werror source claim.
FATFS/SD detection, littlefs adapter, YMODEM, parameter-local G65 and expression
ATC are not tested here. The external M98-style macro repeat callback is tested
with real CORE redirect/reposition/close; internal macro lookup is a fail-fast
host boundary returning not-found for the empty parent file.
