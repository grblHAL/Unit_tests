#include "uart_host.h"
int main(void)
{
    uart_start();
    for (unsigned i = 0; i < 900; i++)
        uart_receive('G');
    CHECK(rts);
    for (unsigned i = 0; i < 601; i++)
        CHECK(uart_stream->read() == 'G');
    CHECK(!rts);
    uart_stream->reset_read_buffer();
    CHECK(uart_stream->get_rx_buffer_free() == 1023);
    return 0;
}
