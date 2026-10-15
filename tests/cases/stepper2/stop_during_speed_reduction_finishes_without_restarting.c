#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_motor_move(motor, 0, 200, Stepper2_InfiniteSteps));
    cruise_motor(motor);
    st2_motor_set_speed(motor, 50);
    tick_motor(motor);
    CHECK(!st2_motor_cruising(motor));
    CHECK(st2_motor_stop(motor));
    finish_motor(motor);
    unsigned finished = motor_pulses;
    tick_motor(motor);
    CHECK(motor_pulses == finished);
    CHECK(st2_get_position(motor) == finished);
    CHECK(st2_get_speed(motor) == 0.0f);
    return EXIT_SUCCESS;
}
