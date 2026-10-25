#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    proxy.write("ok\n");
    now += 1000;
    mpg_poll();
    CHECK(packets == 2 && sent[0].size == sent[1].size &&
          memcmp(sent[0].data, sent[1].data, sent[0].size) == 0);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "txretry=1"));
    return 0;
}
