#include "uart_host.h"
int main(void)
{
    uart_start();
    uart_event(UART_INT_RT, '$');
    uart_event(UART_INT_RT, '!');
    CHECK(rt_calls == 2 && uart_stream->get_rx_buffer_free() == 1022);
    CHECK(uart_stream->read() == '$' && uart_stream->read() == SERIAL_NO_DATA);
    uart_receive('I');
    uart_event(UART_INT_RT, '\n');
    CHECK(uart_stream->read() == 'I' && uart_stream->read() == '\n' &&
          uart_stream->read() == SERIAL_NO_DATA && uart_stream->get_rx_buffer_free() == 1023);
    CHECK(rt_calls == 4 && (irq_mask & (UART_INT_RX | UART_INT_RT)) == (UART_INT_RX | UART_INT_RT));
    return 0;
}
