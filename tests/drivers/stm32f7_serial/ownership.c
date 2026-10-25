#include "stm7_serial_host.h"
int main(void)
{
    stm7_prepare();
    CHECK(stream_close(stm7_stream) && !stream_close(stm7_stream));
    const io_stream_t *next = stream_open_instance(0, 57600, NULL, NULL);
    CHECK(next == stm7_stream && stm7_gpio_calls == 1 && stm7_irq_calls == 1);
    CHECK(stream_get_uart_status(0)->baud_rate == 57600 && USART3->BRR == 938);
    CHECK(!stream_open_instance(0, 9600, NULL, NULL));
    return 0;
}
