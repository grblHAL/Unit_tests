#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    settings.spindle.on_delay = 1000;
    CHECK(store_setting(Setting_SpindleOnDelay, "0") == Status_OK);
    CHECK(settings.spindle.on_delay == 0);
    return EXIT_SUCCESS;
}
