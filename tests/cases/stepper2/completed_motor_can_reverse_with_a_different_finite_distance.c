#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_motor_move(motor, 20, 100, Stepper2_Steps));
    finish_motor(motor);
    CHECK(st2_get_position(motor) == 20);
    CHECK(st2_motor_move(motor, -30, 50, Stepper2_Steps));
    finish_motor(motor);
    CHECK(st2_get_position(motor) == -10);
    CHECK(motor_pulses == 50);
    return EXIT_SUCCESS;
}
