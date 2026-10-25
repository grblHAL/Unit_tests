#include "mpg_host.h"
int main(void)
{
    mpg_start();
    uint8_t data = 'G';
    mpg_receive(1, MpgFrame_Dat, &data, 1);
    mpg_receive(1, MpgFrame_Dat, &data, 1);
    CHECK(rt_calls == 1 && proxy.get_rx_buffer_count() == 1);
    mpg_poll();
    CHECK(packets == 2);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "rxdup=1"));
    return 0;
}
