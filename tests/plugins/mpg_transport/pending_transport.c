#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    proxy.write("ok\n");
    *(uint8_t *)registered_settings->settings[0].value = 0;
    registered_settings->on_changed(&settings, (settings_changed_flags_t){0});
    CHECK(warnings == 1 && claims == 1 && registrations == 1);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "transport=framed") &&
          strstr(output, "link=up"));
    grbl.on_reset();
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "transport=framed"));
    registered_settings->save();
    registered_settings->load();
    CHECK(claims == 1 && registrations == 1);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "transport=plain"));
    packets = 0;
    proxy.write("ready");
    CHECK(packets == 1 && sent[0].size == 5 && memcmp(sent[0].data, "ready", 5) == 0);
    return 0;
}
