#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    uint8_t data[200];
    for (unsigned i = 0; i < 200; i++)
        data[i] = (uint8_t)i;
    proxy.write_n(data, 200);
    CHECK(packets == 1 && sent[0].data[3] == 128 && proxy.get_tx_buffer_count() == 200);
    mpg_ack(0);
    CHECK(packets == 2 && sent[1].data[3] == 72 && memcmp(sent[0].data + 4, data, 128) == 0 &&
          memcmp(sent[1].data + 4, data + 128, 72) == 0);
    mpg_ack(1);
    CHECK(proxy.get_tx_buffer_count() == 0);
    return 0;
}
