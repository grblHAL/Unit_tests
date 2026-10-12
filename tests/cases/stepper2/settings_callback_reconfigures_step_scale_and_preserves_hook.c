#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    NEAR(st2_motor_set_speed(motor, 60), 80);
    settings.axis[X_AXIS].steps_per_mm = 160;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(settings_calls == 1);
    NEAR(st2_motor_set_speed(motor, 60), 160);
    CHECK(motor_pulses == 0);
    return EXIT_SUCCESS;
}
