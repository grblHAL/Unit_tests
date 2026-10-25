#include "uart_host.h"
int main(void)
{
    uart_start();
    uart_stream->write("G1");
    uint8_t bytes[] = {0, 0xFF, 'X'};
    uart_stream->write_n(bytes, 3);
    CHECK(tx_count == 5 && memcmp(tx_data, "G1", 2) == 0 && memcmp(tx_data + 2, bytes, 3) == 0);
    CHECK(uart_stream->get_tx_buffer_count() == 0);
    return 0;
}
