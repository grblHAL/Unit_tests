#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_motor_move(motor, -1, 100, Stepper2_InfiniteSteps));
    cruise_motor(motor);
    CHECK(motor_pulses > 1);
    CHECK(st2_get_position(motor) == -(int64_t)motor_pulses);
    CHECK(st2_motor_stop(motor));
    finish_motor(motor);
    CHECK(st2_get_position(motor) == -(int64_t)motor_pulses);
    return EXIT_SUCCESS;
}
