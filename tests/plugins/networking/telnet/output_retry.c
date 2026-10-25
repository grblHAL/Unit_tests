#include "telnet_host.h"
int main(void)
{
    telnet_connect();
    hal.stream.write("error:1\n");
    tcp_write_result = ERR_CONN;
    telnetd_poll();
    CHECK(tcp_length == 0 && tcp_outputs == 0);
    tcp_write_result = ERR_OK;
    telnetd_poll();
    CHECK(tcp_length == 8 && !memcmp(tcp_bytes, "error:1\n", 8) && tcp_outputs == 1);
    telnet_finish();
    return 0;
}
