#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.steppers.pulse_delay_microseconds = 3.0f;
    CHECK(store_setting(Setting_PulseDelayMicroseconds, "20.1") == Status_SettingValueOutOfRange);
    NEAR(settings.steppers.pulse_delay_microseconds, 3.0f);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
