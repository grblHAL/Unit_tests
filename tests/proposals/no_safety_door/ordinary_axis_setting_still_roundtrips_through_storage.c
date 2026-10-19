#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2);
    CHECK(store_setting(Setting_AxisAcceleration + Y_AXIS, "2.5") == Status_OK);
    NEAR(settings.axis[Y_AXIS].acceleration, 9000);
    settings.axis[Y_AXIS].acceleration = 1;
    settings_init();
    NEAR(settings.axis[Y_AXIS].acceleration, 9000);
    const setting_detail_t *detail = setting_get_details(Setting_AxisAcceleration + Y_AXIS, NULL);
    CHECK(detail != NULL);
    NEAR(setting_get_float_value(detail, Y_AXIS), 2.5f);
    return EXIT_SUCCESS;
}
