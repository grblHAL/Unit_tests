# Known defects and scope

Seven selected adapter cases pass without runtime defect allowances. Sources:
Plugin_SD_card d0fe753d622e79a60e54e729ba83f7207276114c;
CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
STM32F4xx a6318ac92f079f49fab91687530f832997396edc (FatFs R0.14b).
Original adapter, CORE VFS and actual ff.c/ffunicode.c compile unchanged with
original ffconf.h. No file-system ABI alias, fake FatFs API or edited SDK config.

Block provider starts a standard valid1.44MiB FAT12 disk image and captures
sector operations. Original FatFs creates/reads files, directories and metadata.
A normal sector read failure exercises adapter error/reopen recovery. No
malformed disk/parser or unsafe boundary reproduction is used. This is not a
physical SD/SPI driver, card detector or native controller integration test.

Windows FatFs has an explicit native Windows branch. Platform headers load
before CORE On; existing CRT string compatibility precedes platform headers.
Fixture includes FatFs before math checks and undefines Windows' empty NEAR
qualifier locally before the test assertion macro. CMake groups repeated
-include options so deduplication cannot drop an argument. These handle host
header names, not firmware API/signature changes. Fixture remains-Werror;
original source warnings remain visible/nonfatal under existing policy.

Original STM32F4 ffconf enables writes/LFN/chmod/exFAT and disables mkfs. Only
FAT12 selected scenarios execute; no formatting/exFAT/FAT32 coverage claim.
Root stat constructs a timestamp from uninitialized FILINFO in the adapter by
source inspection; root-stat runtime is intentionally not exercised. Adapter
cwd ignores caller buffer/length; small-buffer behavior is not reproduced.
Source-only concerns, legacy variants, media lifecycle and full firmware/
physical timing remain unfinished. No sanitizer allowance or production edits.
