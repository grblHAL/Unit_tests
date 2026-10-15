#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    st2_motor_t *other = st2_motor_init(Y_AXIS, false);
    CHECK(other != NULL);
    CHECK(st2_motor_move(motor, 20, 100, Stepper2_Steps));
    CHECK(st2_motor_move(other, -30, 100, Stepper2_Steps));
    for(unsigned i = 0; i < 1000 && (st2_motor_running(motor) || st2_motor_running(other)); i++) {
        motor_clock += 1000000;
        st2_motor_run(motor);
        st2_motor_run(other);
    }
    CHECK(!st2_motor_running(motor) && !st2_motor_running(other));
    CHECK(st2_get_position(motor) == 20);
    CHECK(st2_get_position(other) == -30);
    CHECK(motor_pulses == 50);
    return EXIT_SUCCESS;
}
