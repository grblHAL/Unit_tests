#include "telnet_host.h"
int main(void)
{
    telnet_prepare();
    tcp_bind_ok = false;
    CHECK(!telnetd_init(2323) && !listener_accept);
    CHECK(hal.stream.type == StreamType_Serial);
    telnetd_stop();
    CHECK(tcp_closes == 0 && tcp_aborts == 0);
    return 0;
}
