#include "support/secondary_timer_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_timer_motor();
    st2_motor_register_stopped_callback(motor, motor_stopped);
    CHECK(st2_motor_move(motor, 0, 100, Stepper2_InfiniteSteps));
    for(unsigned i = 0; i < 1000 && !st2_motor_cruising(motor); i++) fire_motor_timer();
    CHECK(st2_motor_cruising(motor));
    CHECK(st2_motor_stop(motor));
    for(unsigned i = 0; i < 1000 && st2_motor_running(motor); i++) fire_motor_timer();
    CHECK(!st2_motor_running(motor));
    CHECK(timer_stops == 1 && stopped_calls == 0);
    engine_ticks += 3;
    engine_execute_tasks(STATE_IDLE);
    CHECK(stopped_calls == 1 && stopped_motor == motor);
    return EXIT_SUCCESS;
}
