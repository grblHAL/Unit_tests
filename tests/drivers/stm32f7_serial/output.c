#include "stm7_serial_host.h"
int main(void)
{
    stm7_prepare();
    const uint8_t binary[] = {0, 0x80, 0xff};
    stm7_stream->write("ok\n");
    stm7_stream->write_n(binary, sizeof(binary));
    CHECK(stm7_stream->get_tx_buffer_count() == 6 && (USART3->CR1 & USART_CR1_TXEIE));
    stm7_drain();
    CHECK(stm7_sent_count == 6 && !memcmp(stm7_sent, "ok\n", 3) &&
          !memcmp(stm7_sent + 3, binary, 3));
    stm7_stream->write("discard");
    stm7_stream->reset_write_buffer();
    CHECK(stm7_stream->get_tx_buffer_count() == 0 && !(USART3->CR1 & USART_CR1_TXEIE));
    CHECK(stm7_stream->write_char('Z'));
    stm7_drain();
    CHECK(stm7_sent_count == 7 && stm7_sent[6] == 'Z');
    return 0;
}
