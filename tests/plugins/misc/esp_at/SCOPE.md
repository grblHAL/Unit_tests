# ESP-AT scope

Original `Plugins_misc`265711922037cab6b6e47a9560ef11da3a6e5f83 esp_at.c links
CORE b01f481072edecac33d5e40c25869359a5b3fa1f stream/passthrough/IO-port/
VFS/crossbar/string code and the original EEPROM plugin/CORE CRC. UART commands,
ordinary short modem replies, scheduled callback delivery and I2C storage bytes
are explicit host boundaries. Settings are obtained through the plugin's registered
public provider; no private settings struct or stream state is fabricated.
This checks requests and routing, not radio, modem firmware or real task timing.

Batch49 local authoring covers AP/STA/static setup, initial-server cleanup, echo
retry, normal configuration rejection, disabled mode, missing UART/storage,
stream connect/normal duplex binary output, realtime handler replacement,
disconnect/reconnect, station-disconnect notification, prompt-timeout recovery,
receive full/wrap/flush/cancel, settings reload and checksum recovery. One correct
reserved-slot capacity assertion remains a named known failure with a separate
passing full-ring retention control. Registered control banks use actual CORE
function assignment/port enumeration before checking Boot0/reset order or the
incomplete-pair fallback. Tool-ACK suspension uses actual CORE queue backup and
restoration. Six ETHERNET_ENABLE1 cases link original networking.c and lwIP headers
with the existing networking host platform header: AP/STA events and interface
flags, disconnect flags, active-stream report routing, server-stop rejection and
prior-provider delegation pass. A second correct known assertion retains the
configured Telnet port versus NETIF report mismatch. These do not start a TCP
listener or execute the lwIP engine. No new type/API compatibility alias is used.
Other provider metadata, additional disconnect forms, extended input and physical
behavior remain. Immediate/timer callbacks are explicitly delivered by tests;
the task fixture does not establish real scheduler priority or timing.
Batch49 cumulative1281-case sanitizer/strict gate passes across56 suites.
Misc selected coverage is1716/1897 lines and841/1146 branches; esp_at.c itself is
444/524 lines and180/280 branches,33/36 functions. Existing misc file totals are
unchanged; remaining original ESP-AT executable paths stay in the denominator.
No sanitizer allowance or source exclusion is added. This does not establish
all configurations, full plugin repository coverage or controller behavior.

## Native IPv4 setter remains unregistered

A normal provider setter check encountered an ASan bounds diagnostic in original
`validate_ip` at esp_at.c822. Source inspection shows its scan can advance beyond
the final string terminator. The setter invocation was removed from executable
authoring cases; the diagnostic is preserved in local batch49 test logs. No
further unsafe execution, padded caller storage, alternate parser, source edit or
sanitizer allowance is used. Maintainer review of the validator's input-boundary
contract is needed before registering setter integration. Getter/default-address
and stored-settings checks do not prove this setter safe.
