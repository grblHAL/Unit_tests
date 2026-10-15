#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    CHECK(st2_motor_move(motor, 1000, 200, Stepper2_Steps));
    tick_motor(motor);
    CHECK(st2_motor_running(motor) && !st2_motor_cruising(motor));
    CHECK(st2_motor_stop(motor));
    finish_motor(motor);
    CHECK(motor_pulses > 0 && motor_pulses < 1000);
    CHECK(st2_get_position(motor) == motor_pulses);
    unsigned finished = motor_pulses;
    tick_motor(motor);
    CHECK(motor_pulses == finished);
    return EXIT_SUCCESS;
}
