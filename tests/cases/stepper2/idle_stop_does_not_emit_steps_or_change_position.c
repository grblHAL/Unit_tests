#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_set_position(motor, 123));
    CHECK(!st2_motor_stop(motor));
    CHECK(!st2_motor_run(motor));
    CHECK(motor_pulses == 0 && st2_get_position(motor) == 123);
    NEAR(st2_get_speed(motor), 0);
    return EXIT_SUCCESS;
}
