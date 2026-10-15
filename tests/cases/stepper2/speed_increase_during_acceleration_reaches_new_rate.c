#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_motor_move(motor, 0, 100, Stepper2_InfiniteSteps));
    tick_motor(motor);
    CHECK(!st2_motor_cruising(motor));
    st2_motor_set_speed(motor, 200);
    cruise_motor(motor);
    CHECK(fabsf(st2_get_speed(motor) - 200) < 0.2f);
    CHECK(st2_motor_stop(motor));
    finish_motor(motor);
    CHECK(st2_get_position(motor) == motor_pulses);
    return EXIT_SUCCESS;
}
