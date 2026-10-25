#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_prepare();
    stmh7_stream->write("ok\n");
    uint32_t before = USART3->CR1;
    CHECK(stmh7_stream->disable_rx(true));
    CHECK(USART3->CR1 == (before & ~USART_CR1_RXNEIE));
    stmh7_drain();
    CHECK(stmh7_sent_count == 3 && !memcmp(stmh7_sent, "ok\n", 3));
    CHECK(stmh7_stream->disable_rx(false) && (USART3->CR1 & USART_CR1_RXNEIE));
    stmh7_receive('G');
    CHECK(stmh7_stream->read() == 'G');
    return 0;
}
