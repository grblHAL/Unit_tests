#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_triplex_prepare();
    CHECK(stmh7_port_stream[1]->disable_rx(true) && !(USART6->CR1 & USART_CR1_RXNEIE));
    CHECK((USART3->CR1 & USART_CR1_RXNEIE) && (USART1->CR1 & USART_CR1_RXNEIE));
    stmh7_receive_port(0, 'A');
    stmh7_receive_port(2, 'C');
    stmh7_port_stream[1]->write("ok\n");
    stmh7_drain_port(1);
    CHECK(stmh7_port_stream[1]->disable_rx(false));
    stmh7_receive_port(1, 'B');
    for (unsigned n = 0; n < 3; n++)
        CHECK(stmh7_port_stream[n]->read() == 'A' + (int)n);
    CHECK(stmh7_port_sent_count[1] == 3 && !memcmp(stmh7_port_sent[1], "ok\n", 3));
    return 0;
}
