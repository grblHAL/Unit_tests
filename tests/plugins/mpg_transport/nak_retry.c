#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    proxy.write("ok\n");
    uint8_t type = MpgFrame_Dat;
    mpg_receive(sent[0].data[1], MpgFrame_Nak, &type, 1);
    mpg_poll();
    CHECK(packets == 2 && memcmp(sent[0].data, sent[1].data, sent[0].size) == 0);
    return 0;
}
