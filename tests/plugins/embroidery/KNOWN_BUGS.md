# Embroidery reader scope

Original source9a112c3c2509563aa5c745d5773aba5a62046d7c and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f are unchanged. No known assertion or
sanitizer allowances are registered for these valid-format reader cases.

Original tajima.c and brother.c execute through their public open functions and
returned get_stitch/get_thread_color callbacks. Real CORE VFS/embedded backend
reads and seeks constructed valid DST/PES bytes; no replacement parser is used.
DST cases cover header bounds/counts, small/large signed moves, jump/stop/end and
format rejection/rewind. PES cases cover label/palette/dimensions, initial color,
short/long signed moves, paired-axis jump/trim, color change/end, format rejection
and parser fallback. PES dimensions are reported in the implementation's stored
tenths-of-mm units; no coordinator scaling behavior is claimed.

Seven coordinator cases now compile original embroidery.c and exercise public
file-open conversion for DST signed moves/jumps and PES color/signed moves,
plus missing NVS allocation, chained reset and streamed stepper/trigger/planner-space
workflows. Original CORE VFS/embedded,
ioports/crossbar/stream/CRC and EEPROM plugin execute. One digital input bank is
registered before initialization; settings restore/load uses the actual EEPROM
backend. NVS allocation, settings registration and startup execution are explicit
host boundaries. Motion requests, spindle on/off and planner capacity are captured
callbacks; model initialization provides a valid spindle callback and zero machine
position. Public registered trigger IRQ releases queued stitching; unused task and
report callbacks fail fast. SD hardware, actual planner/stepper execution, full
settings/parser, and physical stitch timing remain. Truncated input,
long metadata and allocation-failure paths have not been exercised. Mixed-axis
PEC flag precedence, persistent DST sequin state and coordinator unit contracts
need source/spec review before assertions. Do not force private parser state or
exclude remaining implementations to imply whole-plugin coverage.

Original warnings remain visible under -Wno-error; host fixtures remain strict.
The Windows CRT string declaration shim is the existing shared host-only header.
No production alias, patch, fallback CORE or board/firmware build is used.

## Unregistered DST stop conversion contract - 2026-10-25

`proposals/coordinator_dst_stop.c` is not built or registered. Its proposed
T0 assertion failed during first authoring. Source review shows coordinator
onFileOpen declares an uninitialized stitch_t and initializes only target.x/y;
Tajima get_stitch sets Stitch_Stop without assigning color, and conversion prints
stitch.color. No deterministic color/tool-number contract is established. Do not
rerun this proposal, initialize plugin-private storage in the fixture, or add an
expected-failure allowance from an invented T0 contract. No production fix is
made. Existing reader jump/stop assertions and the supported independent jump
conversion case remain registered. PES initializes its palette color explicitly.
