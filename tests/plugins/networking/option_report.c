#include "net_host.h"
int main(void)
{
    net_prepare();
    net_add(0, (network_status_t){.flags.interface_up = On});
    net_add(1, (network_status_t){.flags.interface_up = On});
    grbl.on_report_options(true);
    CHECK(!strcmp(net_output, ",ETH,mDNS") && net_previous_reports == 1);
    net_clear();
    grbl.on_report_options(false);
    CHECK(strstr(net_output, "[MAC:02:00:00:01:02:03]") &&
          strstr(net_output, "[STA IP:192.168.1.21]") &&
          strstr(net_output, "[HOSTNAME:mill.local]"));
    char *host = strstr(net_output, "[HOSTNAME:");
    CHECK(host && !strstr(host + 1, "[HOSTNAME:") && net_previous_reports == 2);
    return 0;
}
