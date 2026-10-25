#include "mpg_host.h"
int main(void)
{
    mpg_start();
    for (unsigned muted = 0; muted < 2; muted++)
    {
        CHECK(proxy.disable_rx(muted == 0));
        const uint8_t data[] = {'!', 'G'};
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
        mpg_bytes(data, sizeof(data));
#else
        mpg_receive(muted + 1, MpgFrame_Dat, data, sizeof(data));
        mpg_poll();
        CHECK(sent[muted].data[2] == MpgFrame_Ack);
#endif
        CHECK(proxy.get_rx_buffer_count() == 1 && proxy.read() == 'G' &&
              proxy.read() == SERIAL_NO_DATA);
    }
    CHECK(rt_calls == 4);
    return 0;
}
