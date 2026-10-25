#include "stm_serial_host.h"
int main(void)
{
    stm_serial_prepare();
    CHECK(stream_close(stm_stream) && !stream_close(stm_stream));
    const io_stream_t *next = stream_open_instance(0, 57600, NULL, NULL);
    CHECK(next == stm_stream && stm_gpio_calls == 1 && stm_irq_calls == 1);
    CHECK(stream_get_uart_status(0)->baud_rate == 57600 && USART1->BRR == 1458);
    CHECK(!stream_open_instance(0, 9600, NULL, NULL));
    return 0;
}
