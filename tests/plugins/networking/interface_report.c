#include "net_host.h"
int main(void)
{
    net_prepare();
    net_add(0, (network_status_t){.flags.interface_up = On});
    net_add(1, (network_status_t){.flags.interface_up = On});
    CHECK(net_command() == Status_OK);
    CHECK(strstr(net_output, "IF=eth0 IP=192.168.1.20 MAC=02:00:00:01:02:03 Listening=67,23,81"));
    CHECK(strstr(net_output, "IF=wlan0 IP=192.168.1.21 MAC=02:00:00:04:05:06 Listening=81"));
    net_clear();
    net_add(0, (network_status_t){0});
    CHECK(net_command() == Status_OK && !strstr(net_output, "eth0") && strstr(net_output, "wlan0"));
    return 0;
}
