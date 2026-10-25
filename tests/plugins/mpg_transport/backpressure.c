#include "mpg_host.h"
int main(void)
{
    mpg_start();
    uint8_t data[128];
    memset(data, 'G', sizeof(data));
    mpg_receive(1, MpgFrame_Dat, data, 128);
    mpg_receive(2, MpgFrame_Dat, data, 128);
    CHECK(proxy.get_rx_buffer_count() == 128);
    mpg_poll();
    CHECK(packets == 2 && sent[1].data[2] == MpgFrame_Nak);
    for (unsigned i = 0; i < 128; i++)
        CHECK(proxy.read() == 'G');
    mpg_receive(2, MpgFrame_Dat, data, 128);
    CHECK(proxy.get_rx_buffer_count() == 128);
    mpg_poll();
    CHECK(sent[2].data[2] == MpgFrame_Ack);
    return 0;
}
