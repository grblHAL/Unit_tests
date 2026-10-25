#include "msp_host.h"
int main(void)
{
    msp_start();
    for (unsigned batch = 0; batch < 5; batch++)
    {
        for (unsigned i = 0; i < 20; i++)
            msp_receive('A' + i % 20);
        for (unsigned i = 0; i < 20; i++)
            CHECK(msp_stream->read() == (int32_t)('A' + i % 20));
        CHECK(msp_stream->get_rx_buffer_free() == 31);
    }
    return 0;
}
