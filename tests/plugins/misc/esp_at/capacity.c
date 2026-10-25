#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_start();
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN);
    CHECK(hal.stream.get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    return 0;
}
