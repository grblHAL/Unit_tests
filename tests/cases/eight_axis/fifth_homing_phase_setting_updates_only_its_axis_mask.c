#include "support/settings_host.h"

int main(void)
{
    prepare_settings_store();
    settings.homing.cycle[0].mask = 1; settings.homing.cycle[5].mask = 64;
    CHECK(store_setting(Setting_HomingCycle_5, "16") == Status_OK);
    CHECK(settings.homing.cycle[4].mask == 16);
    CHECK(settings.homing.cycle[0].mask == 1 && settings.homing.cycle[5].mask == 64);
    const setting_detail_t *detail = setting_get_details(Setting_HomingCycle_5, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 16);
    return EXIT_SUCCESS;
}
