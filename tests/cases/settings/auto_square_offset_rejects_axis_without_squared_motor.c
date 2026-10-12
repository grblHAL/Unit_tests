#include "support/settings_initialized_host.h"
#include "check.h"
static axes_signals_t squared_y(bool auto_squared) { (void)auto_squared; return (axes_signals_t){.y=true}; }
int main(void)
{
    prepare_initialized_settings(2); hal.stepper.get_ganged=squared_y;
    CHECK(setting_get_details(Setting_AxisAutoSquareOffset+X_AXIS,NULL)==NULL);
    CHECK(store_setting(Setting_AxisAutoSquareOffset+X_AXIS,"0.25")==Status_SettingDisabled);
    NEAR(settings.axis[X_AXIS].dual_axis_offset,0); CHECK(change_callbacks==0);
    return EXIT_SUCCESS;
}
