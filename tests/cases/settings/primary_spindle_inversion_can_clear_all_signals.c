#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    settings.pwm_spindle.invert.mask = 7;
    CHECK(store_setting(Setting_SpindleInvertMask, "0") == Status_OK);
    CHECK(settings.pwm_spindle.invert.mask == 0);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
