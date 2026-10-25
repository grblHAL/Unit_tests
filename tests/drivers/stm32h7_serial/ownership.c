#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_prepare();
    CHECK(stream_close(stmh7_stream) && !stream_close(stmh7_stream));
    const io_stream_t *next = stream_open_instance(0, 57600, NULL, NULL);
    CHECK(next == stmh7_stream && stmh7_gpio_calls == 1 && stmh7_irq_calls == 1);
    CHECK(stream_get_uart_status(0)->baud_rate == 57600 && USART3->BRR == 2083);
    CHECK(!stream_open_instance(0, 9600, NULL, NULL));
    return 0;
}
