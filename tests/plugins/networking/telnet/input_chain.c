#include "telnet_host.h"
int main(void)
{
    telnet_connect();
    telnet_receive("G1X", "10F200\n");
    CHECK(tcp_acks == 10 && tcp_frees == 1 && rt_calls == 10);
    const char *expected = "G1X10F200\n";
    for (const char *s = expected; *s; s++)
        CHECK(hal.stream.read() == *s);
    CHECK(hal.stream.read() == SERIAL_NO_DATA &&
          hal.stream.get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    telnet_finish();
    return 0;
}
