#include "uart_host.h"
int main(void)
{
    uart_start();
    for (unsigned block = 0; block < 5; block++)
    {
        for (unsigned i = 0; i < 300; i++)
            uart_receive((uint8_t)('A' + i % 20));
        for (unsigned i = 0; i < 300; i++)
            CHECK(uart_stream->read() == (int32_t)('A' + i % 20));
        CHECK(uart_stream->get_rx_buffer_free() == 1023);
    }
    return 0;
}
