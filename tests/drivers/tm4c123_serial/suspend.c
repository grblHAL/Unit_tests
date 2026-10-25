#include "uart_host.h"
int main(void)
{
    uart_start();
    CHECK(stream_connect(uart_stream));
    uart_receive('G');
    uart_receive('1');
    CHECK(uart_stream->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    uart_receive(CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    uart_receive('X');
    CHECK(hal.stream.read() == 'X');
    CHECK(uart_stream->suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && hal.stream.read() == 'G' &&
          hal.stream.read() == '1' && hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
