#include "sam_host.h"
int main(void)
{
    sam_prepare();
    CHECK(sam_pins == 4 && sam_clocks == 4 && sam_irqs == 2);
    CHECK(sam_stream[0]->get_rx_buffer_free() == RX_BUFFER_SIZE - 1 &&
          sam_stream[0]->read() == SERIAL_NO_DATA);
    CHECK(stream_get_uart_status(0)->baud_rate == 115200 &&
          stream_get_uart_status(1)->baud_rate == 57600);
    CHECK(!stream_open_instance(0, 115200, NULL, NULL));
    return 0;
}
