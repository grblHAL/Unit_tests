#include "support/secondary_pwm_settings_host.h"
#include "check.h"
static bool unreadable_record(uint8_t *dest, uint32_t source, uint32_t size, bool checksum)
{
    CHECK(dest != NULL && source >= GRBL_NVS_SIZE);
    CHECK(size == sizeof(spindle1_pwm_settings_t) && checksum);
    return false;
}
int main(void)
{
    prepare_secondary_pwm_settings(false);
    spindle_pwm_settings_t defaults = secondary_pwm_settings->cfg;
    CHECK(secondary_pwm_store(Setting_RpmMax1, "12345") == Status_OK);
    memcpy_from_nvs_ptr normal_read = hal.nvs.memcpy_from_nvs;
    hal.nvs.memcpy_from_nvs = unreadable_record;
    secondary_pwm_owner->load();
    NEAR(secondary_pwm_settings->cfg.rpm_max, defaults.rpm_max);
    NEAR(secondary_pwm_settings->cfg.pwm_freq, defaults.pwm_freq);
    CHECK(secondary_pwm_settings->cfg.flags.value == defaults.flags.value);
    hal.nvs.memcpy_from_nvs = normal_read;
    secondary_pwm_settings->cfg.rpm_max = 1;
    secondary_pwm_owner->load();
    NEAR(secondary_pwm_settings->cfg.rpm_max, defaults.rpm_max);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
