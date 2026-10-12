#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2.0f);
    CHECK(store_setting(Setting_HoldActions, "5") == Status_OK);
    unsigned callbacks = change_callbacks;
    CHECK(store_setting(Setting_HoldActions, "8") == Status_SettingValueOutOfRange);
    CHECK(settings.flags.disable_laser_during_hold);
    CHECK(!settings.flags.restore_after_feed_hold);
    CHECK(settings.flags.set_rpm_0_during_hold);
    CHECK(change_callbacks == callbacks);
    return EXIT_SUCCESS;
}
