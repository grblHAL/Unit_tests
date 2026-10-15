#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(!st2_motor_move(motor, 0, 100, Stepper2_mm));
    CHECK(!st2_motor_running(motor));
    tick_motor(motor);
    CHECK(motor_pulses == 0);
    CHECK(st2_get_position(motor) == 0);
    return EXIT_SUCCESS;
}
