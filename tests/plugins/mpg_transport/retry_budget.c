#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    proxy.write("ok\n");
    for (unsigned i = 0; i < 4; i++)
    {
        now += 1000;
        mpg_poll();
    }
    CHECK(packets == 4 && proxy.get_tx_buffer_count() == 0);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "link=down") &&
          strstr(output, "linkdown=1"));
    return 0;
}
