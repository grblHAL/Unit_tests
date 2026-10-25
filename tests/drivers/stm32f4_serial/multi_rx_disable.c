#include "stm_serial_host.h"
int main(void)
{
    stm_triplex_prepare();
    CHECK(stm_port_stream[1]->disable_rx(true) && !(USART3->CR1 & USART_CR1_RXNEIE));
    CHECK((USART1->CR1 & USART_CR1_RXNEIE) && (USART6->CR1 & USART_CR1_RXNEIE));
    stm_receive_port(0, 'A');
    stm_receive_port(2, 'C');
    stm_port_stream[1]->write("ok\n");
    stm_drain_port(1);
    CHECK(stm_port_stream[1]->disable_rx(false));
    stm_receive_port(1, 'B');
    for (unsigned n = 0; n < 3; n++)
        CHECK(stm_port_stream[n]->read() == 'A' + (int)n);
    CHECK(stm_port_sent_count[1] == 3 && !memcmp(stm_port_sent[1], "ok\n", 3));
    return 0;
}
