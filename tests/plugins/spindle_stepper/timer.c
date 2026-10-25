#include "stepper_host.h"
int main(void)
{
    stepper_timer_available = true;
    stepper_clock_ok = false;
    stepper_timer_32bit = TEST_TIMER_BITS == 32;
    stepper_prepare();
    CHECK(stepper_settings && stepper_timer_claims == (TEST_TIMER_BITS == 32 ? 1 : 2));
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 60);
    unsigned pulses = stepper_pulses;
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(stepper_pulses == pulses);
    stepper_cruise(s);
    stepper_poll(100);
    CHECK(stepper_timer_period == 5000 && stepper_forward > 100 && !stepper_reverse);
    CHECK(stepper_timer_starts > 100);
    stepper_stop(s);
    CHECK(stepper_timer_stops == 1);
    pulses = stepper_pulses;
    stepper_poll(10);
    CHECK(stepper_pulses == pulses);
    s->set_state(s, (spindle_state_t){.on = On, .ccw = On}, 60);
    stepper_cruise(s);
    stepper_poll(20);
    CHECK(stepper_reverse > 20);
    stepper_stop(s);
    CHECK(stepper_timer_stops == 2);
    return 0;
}
