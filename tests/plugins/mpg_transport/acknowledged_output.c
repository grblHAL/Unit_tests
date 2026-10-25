#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    proxy.write("ok\n");
    CHECK(packets == 1 && proxy.get_tx_buffer_count() == 3);
    mpg_ack(0);
    CHECK(proxy.get_tx_buffer_count() == 0);
    now += 1000;
    mpg_poll();
    CHECK(packets == 1);
    return 0;
}
