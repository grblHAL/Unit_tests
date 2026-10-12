#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    CHECK(store_setting(Setting_AxisJerk,"2.5")==Status_OK);
    NEAR(settings.axis[X_AXIS].jerk,540000);
    setting_details_t *owner=NULL; const setting_detail_t *detail=setting_get_details(Setting_AxisJerk,&owner); CHECK(detail!=NULL);
    NEAR(setting_get_float_value(detail,0),2.5f);
    return EXIT_SUCCESS;
}
