#include "net_host.h"
int main(void)
{
    char list[NETWORK_SERVICES_LEN] = {0};
    network_services_t services = networking_get_services_list(list);
    CHECK(services.telnet && services.websocket && services.dns && services.mdns &&
          !services.http && !services.ftp);
    CHECK(!strcmp(list, "Telnet,Websocket,N/A,N/A,DNS,mDNS"));
    return 0;
}
