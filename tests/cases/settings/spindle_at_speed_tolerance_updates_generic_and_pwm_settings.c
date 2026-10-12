#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    hal.driver_cap.spindle_encoder = true;
    CHECK(store_setting(Setting_SpindleAtSpeedTolerance, "2.5") == Status_OK);
    NEAR(settings.spindle.at_speed_tolerance, 2.5f);
    NEAR(settings.pwm_spindle.at_speed_tolerance, 2.5f);
    NEAR(setting_get_float_value(setting_get_details(Setting_SpindleAtSpeedTolerance, NULL), 0), 2.5f);
    return EXIT_SUCCESS;
}
