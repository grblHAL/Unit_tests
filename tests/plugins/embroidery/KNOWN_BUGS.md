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

These selected-file results omit the uncompiled embroidery.c coordinator. SD
hardware, file-open/job callbacks, rendering, parser/planner motion, queue/needle
synchronization, settings and physical stitch timing remain. Truncated input,
long metadata and allocation-failure paths have not been exercised. Mixed-axis
PEC flag precedence, persistent DST sequin state and coordinator unit contracts
need source/spec review before assertions. Do not force private parser state or
exclude remaining implementations to imply whole-plugin coverage.

Original warnings remain visible under -Wno-error; host fixtures remain strict.
The Windows CRT string declaration shim is the existing shared host-only header.
No production alias, patch, fallback CORE or board/firmware build is used.
