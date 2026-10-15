#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_motor_move(motor, 2, .1f, Stepper2_Steps));
    motor_clock = 1000000;
    CHECK(st2_motor_run(motor));
    CHECK(motor_pulses == 0);
    finish_motor(motor);
    CHECK(motor_pulses == 2);
    CHECK(st2_get_position(motor) == 2);
    CHECK(st2_get_speed(motor) == 0.0f);
    return EXIT_SUCCESS;
}
