#include "reference_host.h"
int main(void)
{
    uart_start();
    tx_ready = false;
    CHECK(uart_stream->write_char('A'));
    CHECK(uart_stream->disable_rx(true));
    CHECK(!(irq_mask & (UART_INT_RX | UART_INT_RT)) && (irq_mask & UART_INT_TX));
    tx_ready = true;
    uart_event(UART_INT_TX, 0);
    CHECK(tx_count == 1 && tx_data[0] == 'A' && !(irq_mask & UART_INT_TX));
    CHECK(uart_stream->disable_rx(false));
    uart_receive('G');
    CHECK(uart_stream->read() == 'G' && uart_stream->read() == SERIAL_NO_DATA);
    return 0;
}
