#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2); settings.homing.flags.per_axis_feedrates=true;
    settings.axis[X_AXIS].homing_feed_rate=30; CHECK(store_setting(Setting_AxisHomingFeedRate+Y_AXIS,"125")==Status_OK);
    NEAR(settings.axis[Y_AXIS].homing_feed_rate,125); NEAR(settings.axis[X_AXIS].homing_feed_rate,30);
    const setting_detail_t *detail=setting_get_details(Setting_AxisHomingFeedRate+Y_AXIS,NULL); CHECK(detail!=NULL); CHECK(detail->id==Setting_AxisHomingFeedRate);
    NEAR(setting_get_float_value(detail,Y_AXIS),125); CHECK(change_callbacks==1);
    settings.axis[Y_AXIS].homing_feed_rate=1; settings_init(); NEAR(settings.axis[Y_AXIS].homing_feed_rate,125); NEAR(settings.axis[X_AXIS].homing_feed_rate,30);
    NEAR(setting_get_float_value(detail,Y_AXIS),125);
    return EXIT_SUCCESS;
}
