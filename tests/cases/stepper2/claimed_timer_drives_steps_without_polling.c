#include "support/secondary_timer_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_timer_motor();
    CHECK(timer_claims == 1 && !st2_motor_poll(motor));
    CHECK(captured_timer.context == motor && !captured_timer.single_shot);
    CHECK(st2_motor_move(motor, 0, 100, Stepper2_InfiniteSteps));
    CHECK(timer_starts == 1 && timer_period > 0);
    motor_clock += 1000000;
    CHECK(st2_motor_run(motor));
    CHECK(motor_pulses == 0);
    fire_motor_timer();
    CHECK(motor_pulses == 1 && st2_get_position(motor) == 1);
    CHECK(timer_starts == 2 && timer_stops == 0);
    return EXIT_SUCCESS;
}
