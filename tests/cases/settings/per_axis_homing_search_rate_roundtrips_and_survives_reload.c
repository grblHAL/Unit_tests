#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2); settings.homing.flags.per_axis_feedrates=true;
    settings.axis[X_AXIS].homing_seek_rate=30; CHECK(store_setting(Setting_AxisHomingSeekRate+Z_AXIS,"700")==Status_OK);
    NEAR(settings.axis[Z_AXIS].homing_seek_rate,700); NEAR(settings.axis[X_AXIS].homing_seek_rate,30);
    const setting_detail_t *detail=setting_get_details(Setting_AxisHomingSeekRate+Z_AXIS,NULL); CHECK(detail!=NULL); CHECK(detail->id==Setting_AxisHomingSeekRate);
    NEAR(setting_get_float_value(detail,Z_AXIS),700); CHECK(change_callbacks==1);
    settings.axis[Z_AXIS].homing_seek_rate=1; settings_init(); NEAR(settings.axis[Z_AXIS].homing_seek_rate,700); NEAR(settings.axis[X_AXIS].homing_seek_rate,30);
    NEAR(setting_get_float_value(detail,Z_AXIS),700);
    return EXIT_SUCCESS;
}
