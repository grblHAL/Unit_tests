#include "stepper_host.h"
int main(void)
{
    stepper_timer_available = true;
    stepper_clock_ok = false;
    stepper_prepare();
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 60);
    stepper_cruise(s);
    CHECK(stepper_timer_period == 5000);
    unsigned pulses = stepper_forward;
    s->update_rpm(s, 120);
    stepper_cruise(s);
    stepper_poll(20);
    CHECK(stepper_timer_period == 2500 && stepper_forward > pulses);
    CHECK(!stepper_reverse && s->get_state(s).on);
    NEAR(s->get_data(SpindleData_RPM)->rpm, 120);
    s->update_rpm(s, 30);
    stepper_cruise(s);
    stepper_poll(20);
    CHECK(stepper_timer_period == 10000);
    NEAR(s->get_data(SpindleData_RPM)->rpm, 30);
    stepper_stop(s);
    CHECK(stepper_timer_stops == 1);
    return 0;
}
