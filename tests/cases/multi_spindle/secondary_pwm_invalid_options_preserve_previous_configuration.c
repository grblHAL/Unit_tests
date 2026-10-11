#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings(false);
    CHECK(secondary_pwm_store(Setting_SpindlePWMOptions1, "3") == Status_OK);
    uint8_t previous = secondary_pwm_settings->cfg.flags.value;
    unsigned changes = secondary_pwm_changes;
    CHECK(secondary_pwm_store(Setting_SpindlePWMOptions1, "33") == Status_SettingValueOutOfRange);
    CHECK(secondary_pwm_settings->cfg.flags.value == previous);
    CHECK(secondary_pwm_changes == changes);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
