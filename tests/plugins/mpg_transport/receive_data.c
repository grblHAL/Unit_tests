#include "mpg_host.h"
int main(void)
{
    mpg_start();
    const uint8_t data[] = {'G', '1', '!', 'X', '\n'};
    mpg_receive(1, MpgFrame_Dat, data, sizeof(data));
    CHECK(rt_calls == 5 && proxy.get_rx_buffer_count() == 4 && packets == 0);
    CHECK(proxy.read() == 'G' && proxy.read() == '1' && proxy.read() == 'X' &&
          proxy.read() == '\n' && proxy.read() == SERIAL_NO_DATA);
    mpg_poll();
    CHECK(packets == 1 && sent[0].data[2] == MpgFrame_Ack && sent[0].data[1] == 1);
    return 0;
}
