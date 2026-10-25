#include "sam_host.h"
int main(void)
{
    sam_prepare();
    for (unsigned n = 0; n < 2; n++)
    {
        CHECK(sam_stream[n]->set_baud_rate(38400));
        CHECK(stream_get_uart_status(n)->baud_rate == 38400);
        serial_format_t format = {
            .width = Serial_8bit, .stopbits = Serial_StopBits1, .parity = Serial_ParityEven};
        CHECK(sam_stream[n]->set_format(format));
        CHECK(stream_get_uart_status(n)->format.parity == Serial_ParityEven);
#if SERIAL_PORT < 0
        if (!n)
        {
            CHECK(UART->UART_BRGR == 136 && (UART->UART_MR & UART_MR_PAR_Msk) == UART_MR_PAR_EVEN);
            continue;
        }
#endif
        Usart *u = n ? USART2 : USART1;
        CHECK(u->US_BRGR == 136 && (u->US_MR & US_MR_PAR_Msk) == US_MR_PAR_EVEN);
    }
    return 0;
}
