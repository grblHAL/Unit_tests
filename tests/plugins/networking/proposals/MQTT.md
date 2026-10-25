# MQTT callback integration contract - 2026-10-25

Source review only; no broker connection, topic/payload callback, misaligned read
or malformed input is executed. These are not registered functional tests or
known-failure allowances. Only the independent client-ID helper is host-tested.

Pinned networking0b665ee0c0be5161d5044bdf2dcdf59ad62509f8, CORE
b01f481072edecac33d5e40c25869359a5b3fa1f and lwIP
d08f4773edd0182b7910fc8f046eed82ffcd67c9 use NO_SYS/IPv4 on native Clang.
The read-only mqtt_layout.c probe reports mqtt_settings_t alignment2, ip offset0,
network_settings_t.mqtt offset98 and ip_addr_t alignment4. The embedded address
therefore has offset modulo alignment2. It prints type/offset facts only.

Original STM32H7 enet.c54 and STM32F4 enet.c50 hold network_settings_t ethernet,
network; their connect paths pass &network.mqtt. ESP32 wifi.c68/329 does likewise.
MQTT mqtt.c do_connect casts &cfg->ip to ip_addr_t* for mqtt_client_connect.
Drivers store the binary IPv4 representation using set_addr/memcpy(H7 enet.c430),
despite CORE's char[16] declaration; do not substitute a textual IP string.
This is a native C/lwIP alignment contract gap, not a proven physical-device fault.

Before host callback integration, establish a supported address-storage/transport
contract with maintainers. An ordinary aligned local address copied from stored
bytes is one potential production repair; no source edit is made here. Do not add
padding/packing/type aliases, pass a specially aligned standalone settings object,
rewrite driver logic or inject callback contexts to conceal the actual caller
layout. Connect return/retry and subscription-context semantics also remain
unclassified until normal integration is available. Original MQTT message engine,
RTOS/IPv6, actual lwIP client/broker/transport and hardware remain untested.
