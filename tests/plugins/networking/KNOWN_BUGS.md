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
Service mask is Telnet/Websocket/DNS/mDNS; their listener implementations are not
compiled here. MQTT, FTP, HTTP/WebDAV, DHCP server and protocol transports remain.
Original warnings stay visible under -Wno-error while fixtures keep -Werror.
No sanitizer allowances or full networking-repository coverage claim.
