#include "stm7_serial_host.h"
int main(void)
{
    stm7_triplex_prepare();
    CHECK(stm7_port_stream[1]->disable_rx(true) && !(USART6->CR1 & USART_CR1_RXNEIE));
    CHECK((USART3->CR1 & USART_CR1_RXNEIE) && (USART1->CR1 & USART_CR1_RXNEIE));
    stm7_receive_port(0, 'A');
    stm7_receive_port(2, 'C');
    stm7_port_stream[1]->write("ok\n");
    stm7_drain_port(1);
    CHECK(stm7_port_stream[1]->disable_rx(false));
    stm7_receive_port(1, 'B');
    for (unsigned n = 0; n < 3; n++)
        CHECK(stm7_port_stream[n]->read() == 'A' + (int)n);
    CHECK(stm7_port_sent_count[1] == 3 && !memcmp(stm7_port_sent[1], "ok\n", 3));
    return 0;
}
