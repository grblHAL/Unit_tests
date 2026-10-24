#include "uart_host.h"
int main(void)
{
    uart_start();
    tx_ready = false;
    for (unsigned i = 0; i < 31; i++)
        CHECK(uart_stream->write_char('A' + i % 20));
    CHECK(!uart_stream->write_char('Z'));
    CHECK(block_calls == 1 && uart_stream->get_tx_buffer_count() == 31);
    uart_drain();
    CHECK(tx_count == 31);
    for (unsigned i = 0; i < 31; i++)
        CHECK(tx_data[i] == 'A' + i % 20);
    return 0;
}
