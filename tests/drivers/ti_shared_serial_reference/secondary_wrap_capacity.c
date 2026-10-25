#include "reference_host.h"
int main(void)
{
    uart_start();
    uart2_start();
    CHECK(uart2_stream->disable_rx(false));
    for (unsigned batch = 0; batch < 5; batch++)
    {
        for (unsigned i = 0; i < 300; i++)
            uart2_event(UART_INT_RX, 'A' + i % 20);
        for (unsigned i = 0; i < 300; i++)
            CHECK(uart2_stream->read() == (int16_t)('A' + i % 20));
    }
    for (unsigned i = 0; i < 1023; i++)
        uart2_event(UART_INT_RX, 'G');
    CHECK(uart2_stream->get_rx_buffer_free() == 0);
    unsigned before = rt_calls;
    uart2_event(UART_INT_RX, '!');
    CHECK(rt_calls == before + 1 && uart2_stream->get_rx_buffer_free() == 0);
    for (unsigned i = 0; i < 1023; i++)
        CHECK(uart2_stream->read() == 'G');
    CHECK(uart2_stream->read() == SERIAL_NO_DATA && uart_stream->get_rx_buffer_free() == 1023);
    return 0;
}
