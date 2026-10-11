#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_SubroutineOptions, "1") == Status_SettingDisabled);
    CHECK(!settings.flags.m98_prescan_enable);
    return EXIT_SUCCESS;
}
