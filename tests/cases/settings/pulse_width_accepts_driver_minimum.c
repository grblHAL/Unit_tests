#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2.0f);
    CHECK(store_setting(Setting_PulseMicroseconds, "2.0") == Status_OK);
    NEAR(settings.steppers.pulse_microseconds, 2.0f);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
