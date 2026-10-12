#include "support/settings_initialized_host.h"
#include "check.h"
int main(void)
{
    prepare_initialized_settings(2.0f);
    float previous = settings.steppers.pulse_microseconds;
    status_code_t status = store_setting(Setting_PulseMicroseconds, "1.9");
    NEAR(settings.steppers.pulse_microseconds, previous);
    CHECK(change_callbacks == 0);
    fprintf(stderr, "pulse minimum status=%u, expected=%u\n", (unsigned)status, (unsigned)Status_SettingStepPulseMin);
    CHECK(status == Status_SettingStepPulseMin);
    return EXIT_SUCCESS;
}
