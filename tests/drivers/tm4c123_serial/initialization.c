#include "uart_host.h"
int main(void)
{
    uart_start();
    CHECK(pins == 2 && clocks == 2 &&
          (irq_mask & (UART_INT_RX | UART_INT_RT)) == (UART_INT_RX | UART_INT_RT));
    CHECK(uart_stream->get_rx_buffer_free() == 1023 && uart_stream->read() == SERIAL_NO_DATA);
    return 0;
}
