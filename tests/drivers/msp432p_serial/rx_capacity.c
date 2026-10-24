#include "msp_host.h"
int main(void)
{
    msp_start();
    for (unsigned i = 0; i < 31; i++)
        msp_receive('G');
    CHECK(msp_stream->get_rx_buffer_free() == 0);
    unsigned before = rt_calls;
    msp_receive('!');
    CHECK(rt_calls == before + 1);
    msp_receive('X');
    for (unsigned i = 0; i < 31; i++)
        CHECK(msp_stream->read() == 'G');
    CHECK(msp_stream->read() == SERIAL_NO_DATA && msp_stream->get_rx_buffer_free() == 31);
    return 0;
}
