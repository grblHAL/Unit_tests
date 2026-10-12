#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings_with_cap(false, (spindle_cap_t){.variable = true, .cloned = true});
    CHECK(setting_get_details(Setting_RpmMax1, NULL) != NULL);
    CHECK(setting_get_details(Setting_PWMFreq1, NULL) == NULL);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
