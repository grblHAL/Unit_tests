#include "support/backlash_settings_host.h"
int main(void)
{
    prepare_motion_program();
    CHECK(store_backlash("0.125") == Status_OK);
    char value[] = "0.25";
    CHECK(settings_store_setting(Setting_AxisBacklash + Y_AXIS, value) == Status_OK);
    const setting_detail_t *x = setting_get_details(Setting_AxisBacklash, NULL);
    const setting_detail_t *y = setting_get_details(Setting_AxisBacklash + Y_AXIS, NULL);
    CHECK(x && y);
    NEAR(setting_get_float_value(x, X_AXIS), .125f);
    NEAR(setting_get_float_value(y, Y_AXIS), .25f);
    NEAR(settings.axis[Z_AXIS].backlash, 0);
    return EXIT_SUCCESS;
}
