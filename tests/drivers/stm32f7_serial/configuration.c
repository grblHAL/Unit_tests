#include "stm7_serial_host.h"
int main(void)
{
    stm7_prepare();
    CHECK(stm7_stream->set_baud_rate(57600) && USART3->BRR == 938);
    CHECK(stream_get_uart_status(0)->baud_rate == 57600);
    const serial_parity_t parity[] = {Serial_ParityEven, Serial_ParityOdd, Serial_ParityNone};
    const uint32_t expected[] = {USART_CR1_M0 | USART_CR1_PCE,
                                 USART_CR1_M0 | USART_CR1_PCE | USART_CR1_PS, 0};
    const uint32_t mask = USART_CR1_M0 | USART_CR1_PCE | USART_CR1_PS;
    uint32_t control = USART3->CR1 & ~mask;
    for (unsigned i = 0; i < 3; i++)
    {
        serial_format_t format = {
            .width = Serial_8bit, .stopbits = Serial_StopBits1, .parity = parity[i]};
        CHECK(stm7_stream->set_format(format));
        CHECK((USART3->CR1 & mask) == expected[i] && (USART3->CR1 & ~mask) == control);
        CHECK(stream_get_uart_status(0)->format.parity == parity[i]);
    }
    return 0;
}
