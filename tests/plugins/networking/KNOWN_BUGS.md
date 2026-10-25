# Known defects and scope

No runtime defect is currently classified for this interface/report configuration.
Original networking source 0b665ee0c0be5161d5044bdf2dcdf59ad62509f8 and CORE
b01f481072edecac33d5e40c25869359a5b3fa1f are unchanged. Actual lwIP headers
are independently locked to d08f4773edd0182b7910fc8f046eed82ffcd67c9. The host
port provides architecture declarations and NO_SYS/IPv4 configuration; no lwIP
stack/service runtime, socket/traffic, radio or Ethernet hardware is exercised.

Cases use the public networking event/provider/enumeration API and registered
NETIF/report hooks. Driver information and stream/file state are simulated host
boundaries. They cover Ethernet/STA/AP reports, availability changes, enumeration
short-circuiting, enabled service labels, MAC formatting and hook chaining.
The original interface-only cases use Telnet/Websocket/DNS/mDNS service labels;
those cases do not establish listener behavior. MQTT, FTP, HTTP/WebDAV, DHCP server and protocol transports remain.
Original warnings stay visible under -Wno-error while fixtures keep -Werror.
No sanitizer allowances or full networking-repository coverage claim.

## Telnet daemon host integration - batch42

Eleven additional cases compile unchanged telnetd.c with the same locked original
lwIP headers and actual CORE stream/passthrough/VFS/formatting modules. Connection
selection/restoration and ring operations run through CORE and the daemon. Native
TCP callbacks are captured and delivered by a deterministic host provider; there
are no sockets, packets on a network, TCP engine, allocator or Ethernet device.
Valid nonempty one/two-pbuf chains have process-local lifetime; provider free/ACK
counts check normal input ownership without claiming lwIP allocator semantics.

Cases cover accept/stop, chained G-code input, realtime dispatch, cancellation and
flush/reuse, binary output, retry after ERR_CONN, output-full abort/recovery, MPG
input discard, orderly peer close, link-down notification and bind rejection.
All22 combined networking cases pass Clang ASan/UBSan and strict classification
with no exceptions. Original daemon unused arguments get a narrow source-only
warning rule; fixture code stays -Werror. No source/CORE edits.

Selected coverage now includes networking.c/telnetd.c/multipartparser.c:
480/585 lines and256/368 branches across28 clean cases. Interface source remains
157/165 lines and84/106 branches; Telnet199/276 and72/120; multipart124/144 and
100/142. This expanded denominator is separate from the old interface-only report. TCP allocation/listen failures, timeout,
keepalive/RTOS variants, actual stack/controller/parser and physical links remain.
Do not pass a null PCB/session or malformed/empty pbuf to enter unavailable paths.
The partial-write compaction indexes from len+1 by source review; its transport
contract needs review before any runtime case. No unsafe reproduction is included.

## Multipart parser host support - batch42

Six cases call unchanged multipartparser.c through its public initialization,
callbacks and execute API. Capture assertions verify body/part/header/data order,
normal file metadata and exact contents. One-byte transport delivery splits both
headers and boundaries; other cases cover form plus file, binary octets, empty
files and absent optional callbacks. Six focused sanitizer cases pass0.35s.
No internal parser state is changed or copied. All boundaries are short ordinary
valid values. No malformed/oversized inputs, upload filesystem, HTTP listener,
request authentication, target transport or physical-device claim is included.
Combined selected-source filter includes networking.c/telnetd.c/multipartparser.c;
its denominator must remain separate from the old interface-only report.

## HTTP file-upload handler - batch43

Ten cases compile unchanged http_upload.c and multipartparser.c with actual CORE
VFS, the existing SD FatFs adapter and original STM32F4 FatFs engine/configuration.
Only disk sectors remain RAM-backed host media. Real lwIP def.c supplies string
comparison; no copied upload/parser/filesystem algorithm or fake VFS calls.
Original driver_opts selects HTTP/SD/FatFs using declared feature options.

Cases read back exact text/binary/empty files, upload one byte at a time, process
path/size fields and an ordinary filename callback, remove an interrupted partial
file through request cleanup, reuse sequential requests and reject the unavailable
non-FatFs backend. Initial eight focused Clang ASan/UBSan plus strict cases pass0.53s; missing-
directory and header-case controls pass0.17s. Combined38 networking cases pass
the full batch43 sanitizer/strict gate with no exceptions.
Known diagnostics/assertions remain unchanged; no production source edits.

The source lock now includes explicit sdcard_source and fatfs_stm32f4 dependencies
alongside networking/CORE/lwIP. sdcard_source is not a selectable test suite. The
selected coverage filter adds http_upload.c:119/124 lines and41/53 branches;
combined599/709 lines and297/421 branches. Batch42's480/585 report remains the
older narrower scope. Missing-directory failure produces no file or uploaded
bytes and preserves an existing file; parser completion alone is not asserted
as successful persistence. Actual HTTP
listener, client request lifecycle, authentication, physical media and concurrent
uploads remain untested; these cases invoke registered request cleanup directly.

## MQTT settings contract and client IDs - batch48 local

One independent MQTT-enabled helper case checks ordinary MAC-derived client IDs
and the empty-MAC default, using original networking.c and locked lwIP headers.
Focused sanitizer/strict1/1 passes0.10s; no connection or message engine claim.
Broker callback integration stays unregistered: native type-layout evidence puts
network_settings_t.mqtt.ip at offset98 while ip_addr_t requires alignment4.
Original F4/H7/ESP callers pass that embedded object and mqtt.c casts the address.
See proposals/MQTT.md and its read-only probe. No misaligned read, broker action,
packing/padding/alias workaround, source edit or new allowance is included.
Combined coverage/full gate pending; earlier selected counts remain separately dated.
