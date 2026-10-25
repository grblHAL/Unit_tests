#include "telnet_host.h"
int main(void)
{
    telnet_connect();
    telnet_receive("G1X5\n", NULL);
    hal.stream.write("ok\n");
    CHECK(telnet_client.recv(telnet_client.callback_arg, &telnet_client, NULL, ERR_OK) == ERR_OK);
    CHECK(hal.stream.type == StreamType_Serial && tcp_closes == 1 && tcp_frees == 1);
    CHECK(!telnet_client.recv && !telnet_client.sent && !telnet_client.errf);
    telnetd_poll();
    CHECK(tcp_length == 0);
    telnet_finish();
    CHECK(tcp_closes == 2 && tcp_aborts == 0);
    return 0;
}
