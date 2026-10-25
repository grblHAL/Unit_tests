#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    proxy.write("old");
    proxy.write("queued");
    CHECK(proxy.get_tx_buffer_count() == 9);
    grbl.on_reset();
    CHECK(resets == 1 && proxy.get_tx_buffer_count() == 0);
    proxy.write("new");
    CHECK(packets == 2 && memcmp(sent[1].data + 4, "new", 3) == 0);
    return 0;
}
