#include "stm7_serial_host.h"
int main(void)
{
    stm7_prepare();
    stm7_stream->write("ok\n");
    uint32_t before = USART3->CR1;
    CHECK(stm7_stream->disable_rx(true));
    CHECK(USART3->CR1 == (before & ~USART_CR1_RXNEIE));
    stm7_drain();
    CHECK(stm7_sent_count == 3 && !memcmp(stm7_sent, "ok\n", 3));
    CHECK(stm7_stream->disable_rx(false) && (USART3->CR1 & USART_CR1_RXNEIE));
    stm7_receive('G');
    CHECK(stm7_stream->read() == 'G');
    return 0;
}
