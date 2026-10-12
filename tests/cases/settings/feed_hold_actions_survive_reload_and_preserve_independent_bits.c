#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2.0f);
    CHECK(store_setting(Setting_HoldActions, "5") == Status_OK);
    CHECK(settings.flags.disable_laser_during_hold);
    CHECK(!settings.flags.restore_after_feed_hold);
    CHECK(settings.flags.set_rpm_0_during_hold);
    settings.flags.disable_laser_during_hold = false;
    settings.flags.restore_after_feed_hold = true;
    settings.flags.set_rpm_0_during_hold = false;
    settings_init();
    CHECK(settings.flags.disable_laser_during_hold);
    CHECK(!settings.flags.restore_after_feed_hold);
    CHECK(settings.flags.set_rpm_0_during_hold);
    const setting_detail_t *detail = setting_get_details(Setting_HoldActions, NULL);
    CHECK(detail != NULL);
    CHECK(strcmp(setting_get_value(detail, 0), "5") == 0);
    CHECK(store_setting(Setting_HoldActions, "2") == Status_OK);
    CHECK(!settings.flags.disable_laser_during_hold);
    CHECK(settings.flags.restore_after_feed_hold);
    CHECK(!settings.flags.set_rpm_0_during_hold);
    return EXIT_SUCCESS;
}
