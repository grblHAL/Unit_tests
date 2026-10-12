#include "support/secondary_spindle_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_spindle_motor();
    CHECK(st2_motor_bind_spindle(A_AXIS, &settings.axis[A_AXIS]));
    NEAR(st2_motor_set_speed(motor, 60), 200);
    CHECK(st2_motor_move(motor, 1, 60, Stepper2_Steps));
    CHECK(spindle_motor_pulses == 1 && spindle_motor_axis.mask == (1U << A_AXIS));
    CHECK(st2_get_position(motor) == 1);
    return EXIT_SUCCESS;
}
