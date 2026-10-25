#include "stm_serial_host.h"
int main(void)
{
    stm_triplex_prepare();
    USART_TypeDef *devices[] = {USART1, USART3, USART6};
    const uint32_t divider[] = {1458, 729, 1458};
    const serial_parity_t parity[] = {Serial_ParityEven, Serial_ParityOdd, Serial_ParityNone};
    const uint32_t expected[] = {USART_CR1_M | USART_CR1_PCE,
                                 USART_CR1_M | USART_CR1_PCE | USART_CR1_PS, 0};
    for (unsigned n = 0; n < 3; n++)
    {
        CHECK(stm_port_stream[n]->set_baud_rate(57600) && devices[n]->BRR == divider[n]);
        for (unsigned i = 0; i < 3; i++)
        {
            serial_format_t format = {
                .width = Serial_8bit, .stopbits = Serial_StopBits1, .parity = parity[i]};
            CHECK(stm_port_stream[n]->set_format(format));
            CHECK((devices[n]->CR1 & (USART_CR1_M | USART_CR1_PCE | USART_CR1_PS)) == expected[i]);
            CHECK(stream_get_uart_status(n)->format.parity == parity[i]);
        }
    }
    return 0;
}
