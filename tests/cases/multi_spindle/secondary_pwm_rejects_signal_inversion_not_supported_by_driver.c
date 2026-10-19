#include "support/secondary_pwm_settings_host.h"

int main(void)
{
    prepare_secondary_pwm_settings_with_cap(false, (spindle_cap_t){.variable = true, .direction = true});
    CHECK(secondary_pwm_store(Setting_SpindleInvertMask1, "0") == Status_OK);
    /* Driver registration trims PWM from the public bitfield before validation. */
    unsigned changes = secondary_pwm_changes;
    CHECK(secondary_pwm_store(Setting_SpindleInvertMask1, "4") == Status_SettingValueOutOfRange);
    CHECK(!secondary_pwm_settings->cfg.invert.pwm);
    CHECK(secondary_pwm_changes == changes);
    CHECK(secondary_pwm_store(Setting_SpindleInvertMask1, "3") == Status_OK);
    CHECK(secondary_pwm_settings->cfg.invert.on && secondary_pwm_settings->cfg.invert.ccw);
    CHECK(!secondary_pwm_settings->cfg.invert.pwm);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
