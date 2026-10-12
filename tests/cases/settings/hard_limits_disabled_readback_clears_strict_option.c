#include "support/settings_initialized_host.h"
#include "check.h"
static void readback_limits_enable(bool enabled, axes_signals_t axes) { (void)enabled; CHECK(axes.mask==0); }
int main(void)
{
    prepare_initialized_settings(2); hal.limits.enable=readback_limits_enable;
    CHECK(store_setting(Setting_HardLimitsEnable,"3")==Status_OK); CHECK(store_setting(Setting_HardLimitsEnable,"0")==Status_OK);
    const setting_detail_t *detail=setting_get_details(Setting_HardLimitsEnable,NULL); CHECK(detail!=NULL);
    CHECK(setting_get_int_value(detail,0)==0); CHECK(!settings.limits.flags.check_at_init); CHECK(sys.hard_limits.mask==0);
    return EXIT_SUCCESS;
}
