#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    stm1_stream->write("ok\n");
    uint32_t before = USART1->CR1;
    CHECK(stm1_stream->disable_rx(true));
    CHECK(USART1->CR1 == (before & ~USART_CR1_RXNEIE));
    stm1_drain();
    CHECK(stm1_sent_count == 3 && !memcmp(stm1_sent, "ok\n", 3));
    CHECK(stm1_stream->disable_rx(false) && (USART1->CR1 & USART_CR1_RXNEIE));
    stm1_receive('G');
    CHECK(stm1_stream->read() == 'G');
    return 0;
}
