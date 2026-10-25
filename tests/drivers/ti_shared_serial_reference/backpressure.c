#include "reference_host.h"
int main(void)
{
    uart_start();
    tx_ready = false;
    for (unsigned i = 0; i < TX_BUFFER_SIZE - 1; i++)
        CHECK(uart_stream->write_char('A'));
    CHECK(!uart_stream->write_char('Z') && block_calls == 1 && tx_count == 0);
    tx_ready = true;
    uart_event(UART_INT_TX, 0);
    CHECK(tx_count == TX_BUFFER_SIZE - 1 && !(irq_mask & UART_INT_TX));
    for (unsigned i = 0; i < tx_count; i++)
        CHECK(tx_data[i] == 'A');
    CHECK(uart_stream->write_char('R') && tx_count == TX_BUFFER_SIZE &&
          tx_data[TX_BUFFER_SIZE - 1] == 'R');
    return 0;
}
