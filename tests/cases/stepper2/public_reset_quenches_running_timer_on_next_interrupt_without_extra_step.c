#include "support/secondary_timer_host.h"
#include "motion_control.h"
#include "state_machine.h"
static control_signals_t timer_reset_controls(void) { return (control_signals_t){0}; }
int main(void)
{
    st2_motor_t *motor = prepare_timer_motor();
    hal.control.get_state = timer_reset_controls;
    state_set(STATE_IDLE);
    CHECK(st2_motor_move(motor, 0, 100, Stepper2_InfiniteSteps));
    for(unsigned i = 0; i < 3; i++) fire_motor_timer();
    CHECK(st2_motor_running(motor) && motor_pulses == 3);
    CHECK(timer_stops == 0);
    unsigned starts = timer_starts;
    int64_t position = st2_get_position(motor);
    mc_reset();
    CHECK(sys.rt_exec_state & EXEC_RESET);
    CHECK(!st2_motor_running(motor));
    NEAR(st2_get_speed(motor), 0);
    CHECK(st2_get_position(motor) == position);
    /* Reset clears the profile; the already-running timer reaches its next tick. */
    fire_motor_timer();
    CHECK(motor_pulses == 3 && st2_get_position(motor) == position);
    CHECK(timer_stops == 1 && timer_starts == starts);
    CHECK(!st2_motor_run(motor) && motor_pulses == 3);
    return EXIT_SUCCESS;
}
