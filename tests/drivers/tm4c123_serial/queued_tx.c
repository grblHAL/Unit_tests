#include "uart_host.h"
int main(void)
{
    uart_start();
    tx_ready = false;
    uart_stream->write("G1X10");
    CHECK(tx_count == 0 && uart_stream->get_tx_buffer_count() == 5 && (irq_mask & UART_INT_TX));
    uart_drain();
    CHECK(tx_count == 5 && memcmp(tx_data, "G1X10", 5) == 0 && !(irq_mask & UART_INT_TX));
    return 0;
}
