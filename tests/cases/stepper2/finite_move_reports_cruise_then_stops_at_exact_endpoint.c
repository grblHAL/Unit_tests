#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(!st2_motor_cruising(motor));
    CHECK(st2_motor_move(motor, 1000, 100, Stepper2_Steps));
    CHECK(st2_motor_running(motor) && !st2_motor_cruising(motor));
    cruise_motor(motor);
    CHECK(motor_pulses > 0 && motor_pulses < 1000);
    CHECK(st2_motor_running(motor));
    CHECK(fabsf(st2_get_speed(motor) - 100) < 0.1f);
    finish_motor(motor);
    CHECK(!st2_motor_cruising(motor));
    CHECK(motor_pulses == 1000 && st2_get_position(motor) == 1000);
    tick_motor(motor);
    CHECK(motor_pulses == 1000);
    return EXIT_SUCCESS;
}
