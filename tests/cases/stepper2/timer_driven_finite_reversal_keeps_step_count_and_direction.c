#include "support/secondary_timer_host.h"

static int64_t emitted_position;
static unsigned forward_pulses, reverse_pulses;
static void observe_timer_step(axes_signals_t axes, axes_signals_t direction)
{
    capture_motor_step(axes, direction);
    CHECK(axes.mask == X_AXIS_BIT);
    if(direction.mask) {
        reverse_pulses++;
        emitted_position--;
    } else {
        forward_pulses++;
        emitted_position++;
    }
}

int main(void)
{
    st2_motor_t *motor = prepare_timer_motor();
    hal.stepper.output_step = observe_timer_step;
    CHECK(!st2_motor_poll(motor));
    CHECK(st2_motor_move(motor, -20, 100, Stepper2_Steps));
    for(unsigned i = 0; i < 1000 && st2_motor_running(motor); i++) fire_motor_timer();
    CHECK(!st2_motor_running(motor) && timer_stops == 1);
    CHECK(motor_pulses == 20 && reverse_pulses == 20 && forward_pulses == 0);
    CHECK(st2_get_position(motor) == -20 && emitted_position == -20);
    CHECK(st2_motor_move(motor, 30, 50, Stepper2_Steps));
    for(unsigned i = 0; i < 1000 && st2_motor_running(motor); i++) fire_motor_timer();
    CHECK(!st2_motor_running(motor) && timer_stops == 2 && timer_claims == 1);
    CHECK(motor_pulses == 50 && reverse_pulses == 20 && forward_pulses == 30);
    CHECK(st2_get_position(motor) == 10 && emitted_position == 10);
    CHECK(!st2_motor_run(motor) && motor_pulses == 50);
    return EXIT_SUCCESS;
}
