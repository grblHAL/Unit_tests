#include "net_host.h"
int main(void)
{
    net_prepare();
    net_infos[1].wifi_mode = WiFiMode_AP;
    net_add(1, (network_status_t){.flags = {.interface_up = On, .ap_started = On}});
    grbl.on_report_options(true);
    CHECK(!strcmp(net_output, ",WIFI,mDNS"));
    net_clear();
    grbl.on_report_options(false);
    CHECK(strstr(net_output, "[WIFI AP MAC:") && strstr(net_output, "[AP IP:192.168.1.21]"));
    return 0;
}
