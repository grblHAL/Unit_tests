#include "support/settings_initialized_host.h"
#include "check.h"
static axes_signals_t squared_y(bool auto_squared) { (void)auto_squared; return (axes_signals_t){.y=true}; }
int main(void)
{
    prepare_initialized_settings(2); hal.stepper.get_ganged=squared_y;
    settings.axis[X_AXIS].dual_axis_offset=0.1f;
    CHECK(store_setting(Setting_AxisAutoSquareOffset+Y_AXIS,"-0.25")==Status_OK);
    NEAR(settings.axis[Y_AXIS].dual_axis_offset,-0.25f); NEAR(settings.axis[X_AXIS].dual_axis_offset,0.1f);
    const setting_detail_t *detail=setting_get_details(Setting_AxisAutoSquareOffset+Y_AXIS,NULL); CHECK(detail!=NULL);
    NEAR(setting_get_float_value(detail,Y_AXIS),-0.25f); CHECK(change_callbacks==1);
    settings.axis[Y_AXIS].dual_axis_offset=0; settings_init(); NEAR(settings.axis[Y_AXIS].dual_axis_offset,-0.25f);
    return EXIT_SUCCESS;
}
