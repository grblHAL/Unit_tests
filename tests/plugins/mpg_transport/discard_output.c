#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    proxy.write("old");
    proxy.write("stale");
    uint8_t old_seq = sent[0].data[1];
    CHECK(proxy.get_tx_buffer_count() == 8);
    unsigned before = chains;
    proxy.reset_write_buffer();
    CHECK(chains == before + 1 && proxy.get_tx_buffer_count() == 0);
    now += 1000;
    mpg_poll();
    CHECK(packets == 1);
    proxy.write("new");
    CHECK(packets == 2 && sent[1].data[1] != old_seq && sent[1].data[3] == 3 &&
          memcmp(sent[1].data + 4, "new", 3) == 0);
    mpg_ack(0);
    CHECK(proxy.get_tx_buffer_count() == 3);
    mpg_ack(1);
    CHECK(proxy.get_tx_buffer_count() == 0);
    return 0;
}
