#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_start();
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN);
    for (unsigned round = 0; round < 3; round++)
    {
        for (unsigned i = 0; i < 24; i++)
            CHECK(at_uart_handler('a' + i % 20));
        for (unsigned i = 0; i < 24; i++)
            CHECK(hal.stream.read() == (int)('a' + i % 20));
    }
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(at_uart_handler('G') && at_uart_handler('1'));
    hal.stream.cancel_read_buffer();
    CHECK(hal.stream.read() == ASCII_CAN && hal.stream.read() == SERIAL_NO_DATA);
    CHECK(at_uart_handler('M'));
    hal.stream.reset_read_buffer();
    CHECK(hal.stream.read() == SERIAL_NO_DATA && at_uart_handler('2') && hal.stream.read() == '2');
    return 0;
}
