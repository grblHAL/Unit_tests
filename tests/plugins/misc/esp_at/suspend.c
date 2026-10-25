#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_start();
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN);
    CHECK(at_uart_handler('G') && at_uart_handler('1'));
    CHECK(hal.stream.suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    CHECK(at_uart_handler(CMD_TOOL_ACK));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    CHECK(at_uart_handler('X') && hal.stream.read() == 'X');
    CHECK(hal.stream.suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off);
    CHECK(hal.stream.read() == 'G' && hal.stream.read() == '1' &&
          hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
