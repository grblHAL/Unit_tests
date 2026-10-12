#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings(true);
    CHECK(secondary_pwm_store(Setting_Spindle_PWMPort, "1") == Status_OK);
    analog_pins[Port_Output][0].cap.pwm = false;
    unsigned changes = secondary_pwm_changes;
    CHECK(secondary_pwm_store(Setting_Spindle_PWMPort, "0") == Status_SettingValueOutOfRange);
    CHECK(secondary_pwm_settings->port_pwm == 1);
    CHECK(secondary_pwm_changes == changes);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
