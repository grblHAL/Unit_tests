# Scope and remaining work

Thirteen cases execute original WebUI args.c/webui_files.c with real CORE VFS,
embedded filesystem, string helpers and formatting. They cover normal IP/server/
time-command arguments, boolean values, null-terminated argument trimming, and
source-supported no-flash/flash/SoftAP asset lists. Asset checks use declared
lengths, file signatures, complete reads and read-only behavior. No production
functions are copied or private state changed; no diagnostic allowance.

The HTTP server, authentication/login, command-v2/v3, SD/flash upload backends,
lwIP transport, rendered browser UI and real board storage are untested. These
portable helper/provider cases do not establish full WebUI behavior or coverage.
Only supported mutable/null-terminated argument arrays are supplied; actual
server argument construction and command integration remain to be checked.
CORE drive-format waiting and controller delay callbacks fail if unexpectedly
reached. No filesystem format, networking listener or live device is exercised.
