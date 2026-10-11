#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings(false);
    CHECK(setting_get_details(Setting_Spindle_OnPort, NULL) == NULL);
    CHECK(setting_get_details(Setting_Spindle_DirPort, NULL) == NULL);
    CHECK(setting_get_details(Setting_Spindle_PWMPort, NULL) == NULL);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
