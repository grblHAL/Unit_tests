#include "psoc_host.h"
int main(void)
{
    psoc_start();
    uint8_t data[32];
    memset(data, 'G', sizeof(data));
    psoc_receive(data, sizeof(data));
    CHECK(psoc_stream->get_rx_buffer_count() == 31);
    const uint8_t hold = '!';
    psoc_receive(&hold, 1);
    CHECK(rt_calls == 33 && psoc_stream->get_rx_buffer_count() == 31);
    for (unsigned i = 0; i < 31; i++)
        CHECK(psoc_stream->read() == 'G');
    CHECK(psoc_stream->read() == SERIAL_NO_DATA);
    return 0;
}
