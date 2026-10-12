#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    hal.driver_cap.littlefs = true;
    CHECK(store_setting(Setting_SubroutineOptions, "1") == Status_OK);
    CHECK(settings.flags.m98_prescan_enable);
    CHECK(store_setting(Setting_SubroutineOptions, "0") == Status_OK);
    CHECK(!settings.flags.m98_prescan_enable);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
