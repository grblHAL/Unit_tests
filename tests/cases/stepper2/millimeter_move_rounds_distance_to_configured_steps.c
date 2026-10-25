#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_motor_move(motor, 1.01f, 100, Stepper2_mm));
    finish_motor(motor);
    CHECK(motor_pulses == 81);
    CHECK(st2_get_position(motor) == 81);
    const float one_step_mm = 1.0f / settings.axis[X_AXIS].steps_per_mm;
    CHECK(st2_motor_move(motor, one_step_mm, 100, Stepper2_mm));
    CHECK(motor_pulses == 81); // Distance-mode moves wait for motor service.
    finish_motor(motor);
    CHECK(motor_pulses == 82 && st2_get_position(motor) == 82);
    CHECK(st2_motor_move(motor, -one_step_mm, 100, Stepper2_mm));
    CHECK(motor_pulses == 82);
    finish_motor(motor);
    CHECK(motor_pulses == 83 && st2_get_position(motor) == 81);
    return EXIT_SUCCESS;
}

