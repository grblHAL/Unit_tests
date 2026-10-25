#include "stm3_serial_host.h"
int main(void)
{
    stm3_prepare();
    CHECK(serialInit(115200) == NULL);
    CHECK(stream_close(stm3_stream) && !stream_close(stm3_stream));
    CHECK(stream_open_instance(0, 9600, NULL, NULL) == NULL);
    CHECK(!stream_get_uart_status(0)->flags.claimed);
    CHECK(serialInit(57600) == NULL);
    const io_stream_t *next = stream_open_instance(0, 115200, NULL, NULL);
    CHECK(next == stm3_stream && stm3_gpio_calls == 1 && stm3_irq_calls == 1);
    CHECK(!stm3_stream->write_n && !stm3_stream->get_tx_buffer_count &&
          !stm3_stream->get_rx_buffer_count && !stm3_stream->disable_rx);
    return 0;
}
