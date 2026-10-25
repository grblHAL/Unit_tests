#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_triplex_prepare();
    CHECK(stream_close(stmh7_port_stream[1]) && !stream_close(stmh7_port_stream[1]));
    CHECK(stream_get_uart_status(0)->flags.claimed && !stream_get_uart_status(1)->flags.claimed &&
          stream_get_uart_status(2)->flags.claimed);
    CHECK(stream_open_instance(1, 19200, NULL, NULL) == stmh7_port_stream[1]);
    CHECK(stmh7_gpio_calls == 3 && stmh7_irq_calls == 3 &&
          stream_get_uart_status(1)->baud_rate == 19200);
    CHECK(!stream_open_instance(2, 9600, NULL, NULL));
    return 0;
}
