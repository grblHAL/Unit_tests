#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_STA);
    at_start();
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN);
    const char message[] = "WIFI DISCONNECT\r\n";
    for (unsigned i = 0; i < sizeof(message) - 1; i++)
        CHECK(at_uart_handler(message[i]));
    CHECK(at_pending() == 1);
    at_step(0);
    CHECK(hal.stream.type == StreamType_Serial && at_pending() == 1);
    CHECK(!at_command_seen("AT+CWQIF\n"));
    return 0;
}
