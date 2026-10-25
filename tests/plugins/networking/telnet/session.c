#include "telnet_host.h"
int main(void)
{
    telnet_connect();
    CHECK(hal.stream.read() == SERIAL_NO_DATA &&
          hal.stream.get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    CHECK(telnet_client.recv && telnet_client.sent && telnet_client.errf && telnet_client.poll);
    telnet_finish();
    CHECK(tcp_aborts == 1 && tcp_closes == 1);
    CHECK(!telnet_client.recv && !telnet_client.sent && !telnet_client.errf && !telnet_client.poll);
    return 0;
}
