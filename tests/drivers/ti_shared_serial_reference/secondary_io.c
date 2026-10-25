#include "reference_host.h"
int main(void)
{
    uart_start();
    uart2_start();
    CHECK(!uart2_stream->write && !uart2_stream->write_char && !uart2_stream->suspend_read);
    CHECK(uart2_stream->disable_rx(false));
    uart_receive('G');
    uart_receive('1');
    uart2_event(UART_INT_RX, 'X');
    uart2_event(UART_INT_RT, '2');
    CHECK(uart_stream->read() == 'G' && uart_stream->read() == '1' &&
          uart_stream->read() == SERIAL_NO_DATA);
    CHECK(uart2_stream->read() == 'X' && uart2_stream->read() == '2' &&
          uart2_stream->read() == SERIAL_NO_DATA);
    uart_receive('Y');
    uart2_event(UART_INT_RX, 'Z');
    uart2_stream->cancel_read_buffer();
    CHECK(uart2_stream->read() == ASCII_CAN && uart2_stream->read() == SERIAL_NO_DATA);
    CHECK(uart_stream->read() == 'Y');
    uart2_event(UART_INT_RX, 'A');
    uart2_stream->reset_read_buffer();
    CHECK(uart2_stream->read() == SERIAL_NO_DATA && uart2_stream->get_rx_buffer_free() == 1023);
    return 0;
}
