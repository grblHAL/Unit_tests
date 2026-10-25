#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_triplex_prepare();
    USART_TypeDef *devices[] = {USART3, USART6, USART1};
    const uint32_t divider[] = {2083, 2083, 2083};
    const serial_parity_t parity[] = {Serial_ParityEven, Serial_ParityOdd, Serial_ParityNone};
    const uint32_t expected[] = {USART_CR1_M0 | USART_CR1_PCE,
                                 USART_CR1_M0 | USART_CR1_PCE | USART_CR1_PS, 0};
    for (unsigned n = 0; n < 3; n++)
    {
        CHECK(stmh7_port_stream[n]->set_baud_rate(57600) && devices[n]->BRR == divider[n]);
        for (unsigned i = 0; i < 3; i++)
        {
            serial_format_t format = {
                .width = Serial_8bit, .stopbits = Serial_StopBits1, .parity = parity[i]};
            CHECK(stmh7_port_stream[n]->set_format(format));
            CHECK((devices[n]->CR1 & (USART_CR1_M0 | USART_CR1_PCE | USART_CR1_PS)) == expected[i]);
            CHECK(stream_get_uart_status(n)->format.parity == parity[i]);
        }
    }
    return 0;
}
