#include "uart_host.h"
int main(void)
{
    uart_start();
    for (unsigned i = 0; i < 1023; i++)
        uart_receive('G');
    unsigned before = rt_calls;
    uart_receive('!');
    CHECK(rt_calls == before + 1);
    CHECK(uart_stream->get_rx_buffer_free() == 0);
    return 0;
}
