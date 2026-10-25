#include "net_host.h"
int main(void)
{
    net_prepare();
    net_add(0, (network_status_t){.changed.ip_aquired = On,
                                  .flags = {.interface_up = On, .ip_aquired = On}});
    CHECK(strstr(net_output, "ETHERNET IP=192.168.1.20"));
    net_clear();
    net_add(1, (network_status_t){.changed.ip_aquired = On,
                                  .flags = {.interface_up = On, .ip_aquired = On}});
    CHECK(strstr(net_output, "WIFI STA IP=192.168.1.21"));
    net_clear();
    net_infos[1].wifi_mode = WiFiMode_AP;
    net_add(
        1,
        (network_status_t){
            .changed = {.ip_aquired = On, .ap_started = On, .ap_scan_completed = On},
            .flags = {
                .interface_up = On, .ip_aquired = On, .ap_started = On, .ap_scan_completed = On}});
    CHECK(strstr(net_output, "WIFI AP READY") && strstr(net_output, "WIFI AP IP=192.168.1.21") &&
          strstr(net_output, "WIFI AP SCAN COMPLETED"));
    return 0;
}
