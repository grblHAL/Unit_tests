#include "telnet_host.h"
int main(void)
{
    telnet_connect();
    const uint8_t binary[] = {0, 0x80, 0xff};
    hal.stream.write("ok\n");
    hal.stream.write_n(binary, sizeof(binary));
    CHECK(hal.stream.get_tx_buffer_count() == 6 && tcp_length == 0);
    telnetd_poll();
    CHECK(tcp_length == 6 && !memcmp(tcp_bytes, "ok\n", 3) && !memcmp(tcp_bytes + 3, binary, 3));
    CHECK(hal.stream.get_tx_buffer_count() == 0 && tcp_outputs == 1);
    telnetd_poll();
    CHECK(tcp_length == 6 && tcp_outputs == 1);
    telnet_finish();
    return 0;
}
