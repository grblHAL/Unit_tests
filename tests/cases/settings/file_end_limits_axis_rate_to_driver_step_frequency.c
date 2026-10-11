#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    hal.max_step_rate = 100;
    settings.axis[X_AXIS].max_rate = 1000;
    settings.axis[X_AXIS].steps_per_mm = 80;
    grbl.on_file_demarcate(false);
    NEAR(settings.axis[X_AXIS].max_rate, 75.0f);
    CHECK(file_callback_calls == 1);
    CHECK(file_callback_start[0] == false);
    return EXIT_SUCCESS;
}
