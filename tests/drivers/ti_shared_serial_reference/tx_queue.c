#include "reference_host.h"
int main(void)
{
    uart_start();
    tx_ready = false;
    uart_stream->write("G1X10\n");
    CHECK(tx_count == 0 && (irq_mask & UART_INT_TX));
    tx_ready = true;
    uart_event(UART_INT_TX, 0);
    CHECK(tx_count == 6 && memcmp(tx_data, "G1X10\n", 6) == 0 && !(irq_mask & UART_INT_TX));
    CHECK(uart_stream->write_char('!') && tx_count == 7 && tx_data[6] == '!');
    return 0;
}
