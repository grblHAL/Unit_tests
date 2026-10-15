#include "support/secondary_stepper_host.h"
int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_motor_move(motor, 0, 5000, Stepper2_InfiniteSteps));
    cruise_motor(motor);
    CHECK(fabsf(st2_get_speed(motor) - settings.axis[X_AXIS].max_rate) < 0.1f);
    CHECK(motor_pulses > 0 && st2_get_position(motor) == motor_pulses);
    CHECK(st2_motor_stop(motor)); finish_motor(motor);
    return EXIT_SUCCESS;
}
