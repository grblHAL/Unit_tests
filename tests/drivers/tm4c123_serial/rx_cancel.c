#include "uart_host.h"
int main(void)
{
    uart_start();
    uart_receive('G');
    uart_receive('1');
    uart_stream->cancel_read_buffer();
    CHECK(uart_stream->read() == ASCII_CAN && uart_stream->read() == SERIAL_NO_DATA);
    uart_receive('X');
    uart_stream->reset_read_buffer();
    CHECK(uart_stream->read() == SERIAL_NO_DATA && !rts);
    return 0;
}
