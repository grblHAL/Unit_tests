#include "support/rtcp_host.h"

int main(void)
{
    prepare_rtcp();
    char low[] = "0.009", high[] = "1.001", valid[] = "0.010";
    CHECK(settings_store_setting(Setting_Kinematics6, low) == Status_SettingValueOutOfRange);
    CHECK(settings_store_setting(Setting_Kinematics6, high) == Status_SettingValueOutOfRange);
    NEAR(setting_get_float_value(setting_get_details(Setting_Kinematics6, NULL), 0), .5f);
    CHECK(settings_store_setting(Setting_Kinematics6, valid) == Status_OK);
    NEAR(setting_get_float_value(setting_get_details(Setting_Kinematics6, NULL), 0), .01f);
    return EXIT_SUCCESS;
}
