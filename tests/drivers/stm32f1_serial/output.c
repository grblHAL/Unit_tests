#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    const uint8_t binary[] = {0, 0x80, 0xff};
    stm1_stream->write("ok\n");
    stm1_stream->write_n(binary, sizeof(binary));
    CHECK(stm1_stream->get_tx_buffer_count() == 6 && (USART1->CR1 & USART_CR1_TXEIE));
    stm1_drain();
    CHECK(stm1_sent_count == 6 && !memcmp(stm1_sent, "ok\n", 3) &&
          !memcmp(stm1_sent + 3, binary, 3));
    stm1_stream->write("discard");
    stm1_stream->reset_write_buffer();
    CHECK(stm1_stream->get_tx_buffer_count() == 0 && !(USART1->CR1 & USART_CR1_TXEIE));
    CHECK(stm1_stream->write_char('Z'));
    stm1_drain();
    CHECK(stm1_sent_count == 7 && stm1_sent[6] == 'Z');
    return 0;
}
