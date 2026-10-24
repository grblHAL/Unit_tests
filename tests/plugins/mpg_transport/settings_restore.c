#include "mpg_host.h"
int main(void)
{
    mpg_start();
    mpg_up();
    CHECK(mpg_command(NULL) == Status_OK);
    char initial[4096];
    strcpy(initial, output);
    *(uint8_t *)registered_settings->settings[1].value = 2;
    *(uint8_t *)registered_settings->settings[2].value = 8;
    *(uint16_t *)registered_settings->settings[3].value = 700;
    registered_settings->on_changed(&settings, (settings_changed_flags_t){0});
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "attempts=2,maxtx=8") &&
          strstr(output, "acktmo=700"));
    unsigned before = saves;
    registered_settings->restore();
    CHECK(saves == before + 1 && warnings == 0);
    CHECK(mpg_command(NULL) == Status_OK && strcmp(initial, output) == 0);
    registered_settings->load();
    CHECK(claims == 1 && registrations == 1 && saves == before + 1);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "link=down") &&
          strstr(output, "attempts=4,maxtx=128"));
    return 0;
}
