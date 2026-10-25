#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_start();
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN);
    for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
        CHECK(at_uart_handler('a' + i % 20));
    CHECK(at_uart_handler('z'));
    for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
        CHECK(hal.stream.read() == (int)('a' + i % 20));
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(at_uart_handler('2') && hal.stream.read() == '2');
    return 0;
}
