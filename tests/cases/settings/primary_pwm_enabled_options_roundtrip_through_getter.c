#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true); CHECK(store_setting(Setting_SpindlePWMOptions,"15")==Status_OK);
    const setting_detail_t *detail=setting_get_details(Setting_SpindlePWMOptions,NULL); CHECK(detail!=NULL);
    CHECK(setting_get_int_value(detail,0)==15); CHECK(change_callbacks==1);
    return EXIT_SUCCESS;
}
