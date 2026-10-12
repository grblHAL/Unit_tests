#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2); settings.homing.flags.per_axis_feedrates=false;
    settings.axis[Z_AXIS].homing_seek_rate=30; CHECK(setting_get_details(Setting_AxisHomingSeekRate+Z_AXIS,NULL)==NULL);
    CHECK(store_setting(Setting_AxisHomingSeekRate+Z_AXIS,"700")==Status_SettingDisabled);
    NEAR(settings.axis[Z_AXIS].homing_seek_rate,30); CHECK(change_callbacks==0);
    return EXIT_SUCCESS;
}
