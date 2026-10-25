#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    CHECK(!stream_open_instance(0, 9600, NULL, NULL));
    CHECK(stream_close(stm1_stream) && !stream_close(stm1_stream));
    CHECK(stream_open_instance(0, 57600, NULL, NULL) == stm1_stream);
    CHECK(stm1_gpio_calls == 2 && stm1_irq_calls == 1 && USART1->BRR == 1250);
    CHECK(stream_get_uart_status(0)->baud_rate == 57600);
    return 0;
}
