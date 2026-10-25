#include "telnet_host.h"
int main(void)
{
    telnet_connect();
    for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
        CHECK(hal.stream.write_char('A' + i % 26));
    CHECK(!hal.stream.write_char('z') && block_calls == 1);
    telnetd_poll();
    CHECK(tcp_length == TX_BUFFER_SIZE - 1);
    for (unsigned i = 0; i < tcp_length; i++)
        CHECK(tcp_bytes[i] == 'A' + i % 26);
    CHECK(hal.stream.write_char('Z'));
    telnetd_poll();
    CHECK(tcp_length == TX_BUFFER_SIZE && tcp_bytes[tcp_length - 1] == 'Z');
    telnet_finish();
    return 0;
}
