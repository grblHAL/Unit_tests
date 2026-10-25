#include "stm_serial_host.h"
int main(void)
{
    stm_serial_prepare();
    stm_stream->write("ok\n");
    uint32_t before = USART1->CR1;
    CHECK(stm_stream->disable_rx(true));
    CHECK(USART1->CR1 == (before & ~USART_CR1_RXNEIE));
    stm_drain();
    CHECK(stm_sent_count == 3 && !memcmp(stm_sent, "ok\n", 3));
    CHECK(stm_stream->disable_rx(false) && (USART1->CR1 & USART_CR1_RXNEIE));
    stm_receive('G');
    CHECK(stm_stream->read() == 'G');
    return 0;
}
