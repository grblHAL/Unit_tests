#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_prepare();
    const uint8_t binary[] = {0, 0x80, 0xff};
    stmh7_stream->write("ok\n");
    stmh7_stream->write_n(binary, sizeof(binary));
    CHECK(stmh7_stream->get_tx_buffer_count() == 6 && (USART3->CR1 & USART_CR1_TXEIE));
    stmh7_drain();
    CHECK(stmh7_sent_count == 6 && !memcmp(stmh7_sent, "ok\n", 3) &&
          !memcmp(stmh7_sent + 3, binary, 3));
    stmh7_stream->write("discard");
    stmh7_stream->reset_write_buffer();
    CHECK(stmh7_stream->get_tx_buffer_count() == 0 && !(USART3->CR1 & USART_CR1_TXEIE));
    CHECK(stmh7_stream->write_char('Z'));
    stmh7_drain();
    CHECK(stmh7_sent_count == 7 && stmh7_sent[6] == 'Z');
    return 0;
}
