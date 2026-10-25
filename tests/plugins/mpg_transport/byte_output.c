#include "mpg_host.h"
int main(void)
{
    mpg_start();
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 1
    mpg_up();
#endif
    CHECK(proxy.write_char('G') && proxy.write_char('1') && proxy.write_char('\n'));
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
    CHECK(packets == 3);
    CHECK(sent[0].size == 1 && sent[0].data[0] == 'G' && sent[1].size == 1 &&
          sent[1].data[0] == '1' && sent[2].size == 1 && sent[2].data[0] == '\n');
#else
    CHECK(packets == 1 && sent[0].data[3] == 1 && sent[0].data[4] == 'G' &&
          proxy.get_tx_buffer_count() == 3);
    mpg_ack(0);
    CHECK(packets == 2 && sent[1].data[3] == 2 && memcmp(sent[1].data + 4, "1\n", 2) == 0);
    mpg_ack(1);
#endif
    CHECK(proxy.get_tx_buffer_count() == 0);
    return 0;
}
