#include "mpg_host.h"
int main(void)
{
    mpg_start();
    uint8_t a = 'A', b = 'B';
    mpg_receive(1, MpgFrame_Dat, &a, 1);
    mpg_receive(1, MpgFrame_Rlt, &b, 1);
    CHECK(proxy.read() == 'A' && proxy.read() == 'B');
    mpg_poll();
    CHECK(packets == 2 && sent[0].data[4] == MpgFrame_Dat && sent[1].data[4] == MpgFrame_Rlt);
    return 0;
}
