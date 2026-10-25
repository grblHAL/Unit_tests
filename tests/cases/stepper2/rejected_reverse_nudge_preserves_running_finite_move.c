#include "support/secondary_stepper_host.h"
static void observe_forward_step(axes_signals_t axes, axes_signals_t direction)
{
    fprintf(stderr, "Accepted forward move: direction=%u pulse=%u\n",
        (unsigned)direction.mask, motor_pulses + 1);
    CHECK(direction.mask == 0);
    capture_motor_step(axes, direction);
}
int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    hal.stepper.output_step = observe_forward_step;
    CHECK(st2_motor_move(motor, 20, 100, Stepper2_Steps));
    tick_motor(motor);
    CHECK(motor_pulses == 1 && st2_get_position(motor) == 1);
    CHECK(!st2_motor_move(motor, -1, 100, Stepper2_Steps));
    CHECK(motor_pulses == 1 && st2_get_position(motor) == 1);
    finish_motor(motor);
    CHECK(motor_pulses == 20 && st2_get_position(motor) == 20);
    CHECK(!st2_motor_running(motor));
    return EXIT_SUCCESS;
}
