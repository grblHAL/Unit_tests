#include "uart_host.h"
int main(void)
{
    uart_start();
    uart_receive('G');
    uart_receive('1');
    uart_receive('!');
    uart_receive('X');
    CHECK(rt_calls == 4 && uart_stream->get_rx_buffer_free() == 1020);
    CHECK(uart_stream->read() == 'G' && uart_stream->read() == '1' && uart_stream->read() == 'X' &&
          uart_stream->read() == SERIAL_NO_DATA);
    return 0;
}
