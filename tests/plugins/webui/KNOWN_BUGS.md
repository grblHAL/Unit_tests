# Scope and remaining work

Thirteen cases execute original WebUI args.c/webui_files.c with real CORE VFS,
embedded filesystem, string helpers and formatting. They cover normal IP/server/
time-command arguments, boolean values, null-terminated argument trimming, and
source-supported no-flash/flash/SoftAP asset lists. Asset checks use declared
lengths, file signatures, complete reads and read-only behavior. No production
functions are copied or private state changed; no diagnostic allowance.

Batch48 adds22 common file-handler cases:11 workflows each with WEBUI_ENABLE2/3.
They compile original fs_handlers.c, networking upload/multipart code, SD adapter,
the STM32F4 FatFs engine, and CORE VFS/RAM-filesystem/JSON/formatting. HTTP request
parameters, status/header delivery and pbuf release are explicit host callbacks;
disk sectors use the existing RAM-backed FatFs fixture. The HTTP server/parser,
actual lwIP packet handling and physical media are not simulated by these cases.

The workflows cover file/directory listings and v2/v3 JSON fields, file sizes,
free-space fields, normalized subdirectory paths, create/existing/nonempty/empty
directory operations, delete/missing-file preservation, quiet responses, drive
selection and download URI generation, missing-drive statuses, multipart upload
completion, chained/fragmented binary data, empty files, maintenance attributes,
hidden-file listing policies, missing content headers and response cleanup.
Actual stored bytes are read back; upload contexts must be released. CORE RAM
responses are read and closed using their original consume-on-close semantics.
Tests set TZ=UTC0 for the fixed local FAT timestamp before UTC JSON formatting.
All supplied filenames/paths/headers are ordinary short valid values. No unsafe
root-stat, overlong/malformed path, private HTTP-state or production edit is used.
Original source warnings remain warnings; test code stays under -Werror.

The HTTP server, authentication/login, command-v2/v3 execution, mounted flash
backend, endpoint wrappers, live lwIP transport, rendered browser UI and real
board storage remain untested. These selected handlers do not establish full
WebUI behavior or repository-wide coverage.
Only supported mutable/null-terminated argument arrays are supplied; actual
server argument construction and command integration remain to be checked.
CORE drive-format waiting and controller delay callbacks fail if unexpectedly
reached. No filesystem format, networking listener or live device is exercised.
