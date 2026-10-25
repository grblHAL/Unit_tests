#include "psoc_host.h"
int main(void)
{
    psoc_start();
    const uint8_t data[] = "G1X1";
    psoc_receive(data, sizeof(data) - 1);
    psoc_stream->reset_read_buffer();
    CHECK(clears == 1 && psoc_stream->read() == SERIAL_NO_DATA);
    psoc_receive(data, sizeof(data) - 1);
    psoc_stream->cancel_read_buffer();
    CHECK(clears == 2 && psoc_stream->read() == CMD_RESET && psoc_stream->read() == SERIAL_NO_DATA);
    return 0;
}
