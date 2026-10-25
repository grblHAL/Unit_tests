#include "stm3_serial_host.h"
int main(void)
{
    stm3_prepare();
    stm3_stream->write("ok\n");
    const uint8_t data[] = {0, 0x80, 0xff};
    for (unsigned i = 0; i < sizeof(data); i++)
        CHECK(stm3_stream->write_char(data[i]));
    CHECK(USART3->CR1 & USART_CR1_TXEIE);
    stm3_drain();
    CHECK(stm3_sent_count == 6 && !memcmp(stm3_sent, "ok\n", 3) &&
          !memcmp(stm3_sent + 3, data, sizeof(data)));
    CHECK(!(USART3->CR1 & USART_CR1_TXEIE));
    return 0;
}
