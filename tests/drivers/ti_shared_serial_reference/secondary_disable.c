#include "reference_host.h"
int main(void)
{
    uart_start();
    uart2_start();
    CHECK(uart2_stream->disable_rx(false));
    uint32_t primary_mask = irq_mask;
    CHECK((irq_mask2 & (UART_INT_RX | UART_INT_RT)) == (UART_INT_RX | UART_INT_RT));
    CHECK(uart2_stream->disable_rx(true) && irq_mask2 == 0 && irq_mask == primary_mask);
    uart_receive('G');
    CHECK(uart_stream->read() == 'G');
    CHECK(uart2_stream->disable_rx(false));
    uart2_event(UART_INT_RT, 'X');
    CHECK(uart2_stream->read() == 'X' && uart2_stream->read() == SERIAL_NO_DATA &&
          irq_mask == primary_mask);
    return 0;
}
