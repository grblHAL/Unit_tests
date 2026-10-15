#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_motor_move(motor, 0, 100, Stepper2_InfiniteSteps));
    cruise_motor(motor);
    unsigned before = motor_pulses;
    st2_motor_set_speed(motor, 100);
    CHECK(st2_motor_cruising(motor));
    tick_motor(motor);
    CHECK(motor_pulses == before + 1);
    CHECK(fabsf(st2_get_speed(motor) - 100) < 0.2f);
    CHECK(st2_motor_stop(motor));
    finish_motor(motor);
    return EXIT_SUCCESS;
}
