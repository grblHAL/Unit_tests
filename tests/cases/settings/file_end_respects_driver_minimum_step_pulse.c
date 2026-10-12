#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    settings.steppers.pulse_microseconds = 1;
    grbl.on_file_demarcate(false);
    NEAR(settings.steppers.pulse_microseconds, 2.0f);
    CHECK(file_callback_calls == 1);
    CHECK(file_callback_start[0] == false);
    return EXIT_SUCCESS;
}
