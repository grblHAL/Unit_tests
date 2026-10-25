#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_start();
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN);
    const char closed[] = "CLOSED\r\n";
    for (unsigned i = 0; i < sizeof(closed) - 1; i++)
        CHECK(at_uart_handler(closed[i]));
    CHECK(at_pending() == 1);
    at_step(0);
    CHECK(hal.stream.type == StreamType_Serial && hal.stream.instance == 0);
    CHECK(at_command_seen("AT+CWQIF\n") && at_pending() == 1);
    at_connect();
    CHECK(hal.stream.type == StreamType_Telnet && hal.stream.read() == ASCII_CAN);
    CHECK(at_uart_handler('M') && hal.stream.read() == 'M' && hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
