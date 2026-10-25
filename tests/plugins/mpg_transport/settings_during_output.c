#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    proxy.write("first");
    proxy.write("second");
    CHECK(packets == 1 && proxy.get_tx_buffer_count() == 11);
    *(uint8_t *)registered_settings->settings[2].value = 8;
    *(uint16_t *)registered_settings->settings[3].value = 500;
    registered_settings->on_changed(&settings, (settings_changed_flags_t){0});
    CHECK(warnings == 0 && packets == 1 && proxy.get_tx_buffer_count() == 11);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "link=up") &&
          strstr(output, "acktmo=500") && strstr(output, "maxtx=8"));
    now = 499;
    mpg_poll();
    CHECK(packets == 1);
    now = 500;
    mpg_poll();
    CHECK(packets == 2 && sent[0].size == sent[1].size &&
          memcmp(sent[0].data, sent[1].data, sent[0].size) == 0);
    mpg_ack(1);
    CHECK(packets == 3 && sent[2].data[3] == 6 && memcmp(sent[2].data + 4, "second", 6) == 0);
    mpg_ack(2);
    CHECK(proxy.get_tx_buffer_count() == 0);
    return 0;
}
