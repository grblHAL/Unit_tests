#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2); CHECK(store_setting(Setting_AxisMaxTravel+Z_AXIS,"40")==Status_OK);
    const setting_detail_t *detail=setting_get_details(Setting_AxisMaxTravel+Z_AXIS,NULL); CHECK(detail!=NULL);
    NEAR(settings.axis[Z_AXIS].max_travel,-40); NEAR(setting_get_float_value(detail,Z_AXIS),40);
    settings.axis[Z_AXIS].max_travel=-1; settings_init(); NEAR(setting_get_float_value(detail,Z_AXIS),40);
    return EXIT_SUCCESS;
}
