#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    const setting_detail_t *detail = setting_get_details(Setting_InvertStepperEnable, NULL);
    CHECK(detail && detail->datatype == Format_Bool);
    CHECK(store_setting(Setting_InvertStepperEnable, "2") == Status_SettingValueOutOfRange);
    return EXIT_SUCCESS;
}
