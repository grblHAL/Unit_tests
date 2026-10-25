#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_STA);
    at_start();
    network_info_t info;
    network_flags_t flags = at_network_info(&info);
    CHECK(flags.interface_up && flags.ip_aquired && !flags.ap_started);
    CHECK(!strcmp(info.status.ip, "192.168.5.20") && strstr(at_output, "WIFI STA IP=192.168.5.20"));
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN);
    const char closed[] = "CLOSED\r\n";
    for (unsigned i = 0; i < sizeof(closed) - 1; i++)
        CHECK(at_uart_handler(closed[i]));
    at_step(0);
    at_ready();
    flags = at_network_info(&info);
    CHECK(flags.interface_up && !flags.ip_aquired && hal.stream.type == StreamType_Serial);
    CHECK(at_pending() == 1);
    return 0;
}
