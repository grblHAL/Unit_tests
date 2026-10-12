#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_motor_move(motor, 0, 100, Stepper2_InfiniteSteps));
    cruise_motor(motor);
    NEAR(st2_motor_set_speed(motor, 0), 0);
    CHECK(st2_motor_running(motor));
    finish_motor(motor);
    CHECK(!st2_motor_cruising(motor));
    NEAR(st2_get_speed(motor), 0);
    return EXIT_SUCCESS;
}
