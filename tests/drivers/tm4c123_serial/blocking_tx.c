#include "uart_host.h"
int main(void)
{
    uart_start();
    tx_ready = false;
    allow_blocking = true;
    for (unsigned i = 0; i < 70; i++)
        CHECK(uart_stream->write_char('A' + i % 20));
    uart_drain();
    CHECK(block_calls > 0 && tx_count == 70);
    for (unsigned i = 0; i < 70; i++)
        CHECK(tx_data[i] == 'A' + i % 20);
    return 0;
}
