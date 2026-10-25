#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_start();
    network_info_t info;
    network_flags_t flags = at_network_info(&info);
    CHECK(flags.interface_up && flags.ip_aquired && flags.ap_started);
    CHECK(!strcmp(info.status.ip, "192.168.5.1") && !strcmp(info.mac, "02:00:00:01:02:04"));
    CHECK(info.status.services.telnet && !info.is_ethernet);
    CHECK(strstr(at_output, "WIFI AP READY") && strstr(at_output, "WIFI AP IP=192.168.5.1"));
    CHECK(at_pending() == 1);
    return 0;
}
