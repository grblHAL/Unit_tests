#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2);
    CHECK(N_AXIS == 8);
    settings.homing.flags.per_axis_feedrates = true;
    float other = settings.axis[0].homing_feed_rate;
    CHECK(store_setting(Setting_AxisHomingFeedRate + 6, "125") == Status_OK);
    NEAR(settings.axis[6].homing_feed_rate, 125);
    NEAR(settings.axis[0].homing_feed_rate, other);
    const setting_detail_t *detail = setting_get_details(Setting_AxisHomingFeedRate + 6, NULL);
    CHECK(detail != NULL);
    NEAR(setting_get_float_value(detail, 6), 125);
    settings.axis[6].homing_feed_rate = 1;
    settings_init();
    CHECK(settings.homing.flags.per_axis_feedrates);
    NEAR(settings.axis[6].homing_feed_rate, 125);
    NEAR(settings.axis[0].homing_feed_rate, other);
    return EXIT_SUCCESS;
}
