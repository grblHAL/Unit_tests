#include "uart_host.h"
int main(void)
{
    uart_start();
    tx_ready = false;
    uart_stream->write("ok\n");
    CHECK(uart_stream->get_tx_buffer_count() == 3 && tx_count == 0 && (irq_mask & UART_INT_TX));
    tx_ready = true;
    uart_event(UART_INT_TX | UART_INT_RX, 'G');
    CHECK(tx_count == 3 && memcmp(tx_data, "ok\n", 3) == 0 &&
          uart_stream->get_tx_buffer_count() == 0 && !(irq_mask & UART_INT_TX));
    CHECK((irq_mask & (UART_INT_RX | UART_INT_RT)) == (UART_INT_RX | UART_INT_RT));
    uart_event(UART_INT_RT, '1');
    CHECK(uart_stream->read() == 'G' && uart_stream->read() == '1' &&
          uart_stream->read() == SERIAL_NO_DATA);
    CHECK(uart_stream->write_char('!') && tx_count == 4 && tx_data[3] == '!');
    CHECK(uart_stream->get_rx_buffer_free() == 1023 && block_calls == 0);
    return 0;
}
