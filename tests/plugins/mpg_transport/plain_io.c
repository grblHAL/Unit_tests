#include "mpg_host.h"
int main(void)
{
    mpg_start();
    uint8_t input[] = {'G', '1', '!'};
    mpg_bytes(input, 3);
    CHECK(proxy.read() == 'G' && proxy.read() == '1' && proxy.read() == SERIAL_NO_DATA &&
          rt_calls == 3);
    proxy.write("ok");
    CHECK(packets == 1 && sent[0].size == 2 && memcmp(sent[0].data, "ok", 2) == 0);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "transport=plain,link=n/a"));
    return 0;
}
