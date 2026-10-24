#include "sam_host.h"
int main(void)
{
    sam_prepare();
    const serial_parity_t parity[] = {Serial_ParityEven, Serial_ParityOdd, Serial_ParityNone};
    const uint32_t bits[] = {US_MR_PAR_EVEN, US_MR_PAR_ODD, US_MR_PAR_NO};
    for (unsigned instance = 0; instance < 2; instance++)
    {
        uint32_t before;
#if SERIAL_PORT < 0
        if (!instance)
            before = UART->UART_MR;
        else
#endif
            before = (instance ? USART2 : USART1)->US_MR;
        for (unsigned i = 0; i < 3; i++)
        {
            serial_format_t format = {
                .width = Serial_8bit, .stopbits = Serial_StopBits1, .parity = parity[i]};
            CHECK(sam_stream[instance]->set_format(format));
            const io_stream_status_t *status = stream_get_uart_status(instance);
            CHECK(status->format.width == Serial_8bit &&
                  status->format.stopbits == Serial_StopBits1 &&
                  status->format.parity == parity[i]);
            uint32_t mode;
#if SERIAL_PORT < 0
            if (!instance)
                mode = UART->UART_MR;
            else
#endif
                mode = (instance ? USART2 : USART1)->US_MR;
            CHECK((mode & US_MR_PAR_Msk) == bits[i] &&
                  (mode & ~US_MR_PAR_Msk) == (before & ~US_MR_PAR_Msk));
        }
    }
    return 0;
}
