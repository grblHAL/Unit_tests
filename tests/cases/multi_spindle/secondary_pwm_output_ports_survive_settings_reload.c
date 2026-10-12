#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings(true);
    CHECK(secondary_pwm_store(Setting_Spindle_OnPort, "0") == Status_OK);
    CHECK(secondary_pwm_store(Setting_Spindle_DirPort, "-1") == Status_OK);
    CHECK(secondary_pwm_store(Setting_Spindle_PWMPort, "0") == Status_OK);
    secondary_pwm_settings->port_on = 255;
    secondary_pwm_settings->port_dir = 0;
    secondary_pwm_settings->port_pwm = 255;
    secondary_pwm_owner->load();
    CHECK(secondary_pwm_settings->port_on == 0);
    CHECK(secondary_pwm_settings->port_dir == IOPORT_UNASSIGNED);
    CHECK(secondary_pwm_settings->port_pwm == 0);
    NEAR(setting_get_float_value(setting_get_details(Setting_Spindle_DirPort, NULL), 0), -1);
    NEAR(setting_get_float_value(setting_get_details(Setting_Spindle_OnPort, NULL), 0), 0);
    NEAR(setting_get_float_value(setting_get_details(Setting_Spindle_PWMPort, NULL), 0), 0);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
