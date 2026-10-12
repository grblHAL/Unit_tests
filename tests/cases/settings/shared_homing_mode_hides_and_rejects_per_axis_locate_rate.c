#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2); settings.homing.flags.per_axis_feedrates=false;
    settings.axis[Y_AXIS].homing_feed_rate=30; CHECK(setting_get_details(Setting_AxisHomingFeedRate+Y_AXIS,NULL)==NULL);
    CHECK(store_setting(Setting_AxisHomingFeedRate+Y_AXIS,"125")==Status_SettingDisabled);
    NEAR(settings.axis[Y_AXIS].homing_feed_rate,30); CHECK(change_callbacks==0);
    return EXIT_SUCCESS;
}
