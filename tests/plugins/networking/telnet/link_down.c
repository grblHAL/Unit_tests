#include "telnet_host.h"
int main(void)
{
    telnet_connect();
    network_status_t status = {0};
    status.changed.link_up = true;
    networking.event("eth0", status);
    CHECK(network_events == 1 && hal.stream.type == StreamType_Serial && tcp_closes == 1);
    CHECK(!telnet_client.recv);
    telnet_finish();
    return 0;
}
