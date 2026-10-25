#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    proxy.write("ok\n");
    *(uint8_t *)registered_settings->settings[1].value = 2;
    registered_settings->on_changed(&settings, (settings_changed_flags_t){0});
    CHECK(proxy.get_tx_buffer_count() == 3 && packets == 1 && warnings == 0);
    now += 1000;
    mpg_poll();
    CHECK(packets == 2 && proxy.get_tx_buffer_count() == 3 && sent[0].size == sent[1].size &&
          memcmp(sent[0].data, sent[1].data, sent[0].size) == 0);
    now += 1000;
    mpg_poll();
    CHECK(packets == 2 && proxy.get_tx_buffer_count() == 0);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "link=down") &&
          strstr(output, "attempts=2") && strstr(output, "linkdown=1"));
    return 0;
}
