#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    CHECK(stm1_stream->set_baud_rate(57600) && USART1->BRR == 1250);
    CHECK(stream_get_uart_status(0)->baud_rate == 57600);
    CHECK((USART1->CR1 & (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE)) ==
          (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE));
    stm1_receive('G');
    CHECK(stm1_stream->read() == 'G');
    return 0;
}
