#include "mpg_host.h"
int main(void)
{
    mpg_start();
    uint8_t data[] = {'G', '1'};
    mpg_bytes(data, 2);
    proxy.cancel_read_buffer();
    CHECK(proxy.read() == ASCII_CAN && proxy.read() == SERIAL_NO_DATA);
    mpg_bytes(data, 2);
    proxy.reset_read_buffer();
    CHECK(proxy.read() == SERIAL_NO_DATA && proxy.get_rx_buffer_free() == 255);
    return 0;
}
