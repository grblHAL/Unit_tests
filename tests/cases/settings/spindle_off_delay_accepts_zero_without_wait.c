#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    settings.spindle.off_delay = 1000;
    CHECK(store_setting(Setting_SpindleOffDelay, "0") == Status_OK);
    CHECK(settings.spindle.off_delay == 0);
    return EXIT_SUCCESS;
}
