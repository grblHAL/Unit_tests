#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(false);
    settings.pwm_spindle.invert.mask = 0;
    CHECK(store_setting(Setting_SpindleInvertMask, "4") == Status_SettingDisabled);
    CHECK(!settings.pwm_spindle.invert.pwm);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
