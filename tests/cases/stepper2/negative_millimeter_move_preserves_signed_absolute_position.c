#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_set_position(motor, 100));
    CHECK(st2_motor_move(motor, -1.5f, 100, Stepper2_mm));
    finish_motor(motor);
    CHECK(motor_pulses == 120);
    CHECK(st2_get_position(motor) == -20);
    return EXIT_SUCCESS;
}
