#include "support/secondary_spindle_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_spindle_motor();
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(settings_calls == 1 && spindle_motor_pulses == 0);
    CHECK(!st2_motor_running(motor));
    CHECK(st2_motor_bind_spindle(A_AXIS, &settings.axis[A_AXIS]));
    NEAR(st2_motor_set_speed(motor, 60), 200);
    char resolution[] = "400";
    CHECK(settings_store_setting(Setting_AxisStepsPerMM + A_AXIS, resolution) == Status_OK);
    CHECK(settings_calls == 2 && spindle_motor_pulses == 0);
    NEAR(st2_motor_set_speed(motor, 60), 400);
    CHECK(st2_motor_move(motor, 1, 60, Stepper2_Steps));
    CHECK(spindle_motor_pulses == 1 && spindle_motor_axis.mask == (1U << A_AXIS));
    CHECK(st2_get_position(motor) == 1);
    return EXIT_SUCCESS;
}
