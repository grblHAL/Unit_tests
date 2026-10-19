#include "support/settings_file_host.h"
int main(void)
{
    prepare_settings_file();
    CHECK(store_setting(Settings_RotaryAxes, "1") == Status_OK);
    hal.max_step_rate = 1000;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        settings.axis[axis].steps_per_mm = 100;
        settings.axis[axis].max_rate = 1200;
    }
    grbl.on_file_demarcate(false);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        NEAR(settings.axis[axis].max_rate, axis == A_AXIS ? 1200 : 600);
    CHECK(settings.steppers.is_rotary.mask == (1u << A_AXIS));
    CHECK(file_callback_calls == 1 && !file_callback_start[0]);
    return EXIT_SUCCESS;
}
