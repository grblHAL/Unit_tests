#include "stm_serial_host.h"
int main(void)
{
    stm_serial_prepare();
    const uint8_t binary[] = {0, 0x80, 0xff};
    stm_stream->write("ok\n");
    stm_stream->write_n(binary, sizeof(binary));
    CHECK(stm_stream->get_tx_buffer_count() == 6 && (USART1->CR1 & USART_CR1_TXEIE));
    stm_drain();
    CHECK(stm_sent_count == 6 && !memcmp(stm_sent, "ok\n", 3) && !memcmp(stm_sent + 3, binary, 3));
    stm_stream->write("discard");
    stm_stream->reset_write_buffer();
    CHECK(stm_stream->get_tx_buffer_count() == 0 && !(USART1->CR1 & USART_CR1_TXEIE));
    CHECK(stm_stream->write_char('Z'));
    stm_drain();
    CHECK(stm_sent_count == 7 && stm_sent[6] == 'Z');
    return 0;
}
