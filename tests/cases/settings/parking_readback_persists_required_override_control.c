#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2); CHECK(store_setting(Setting_ParkingEnable,"3")==Status_OK);
    const setting_detail_t *detail=setting_get_details(Setting_ParkingEnable,NULL); CHECK(detail!=NULL);
    CHECK(setting_get_int_value(detail,0)==7); settings.parking.flags.value=0; settings_init();
    CHECK(setting_get_int_value(detail,0)==7); CHECK(settings.parking.flags.enabled); CHECK(settings.parking.flags.deactivate_upon_init); CHECK(settings.parking.flags.enable_override_control);
    return EXIT_SUCCESS;
}
