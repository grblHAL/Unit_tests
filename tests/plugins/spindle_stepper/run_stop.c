#include "stepper_host.h"
int main(void)
{
    stepper_prepare();
    CHECK(stepper_settings && !stepper_warnings);
    spindle_ptrs_t *s = spindle_get(0);
    CHECK(s->type == SpindleType_Stepper);
    s->set_state(s, (spindle_state_t){.on = On}, 60);
    stepper_cruise(s);
    stepper_poll(100);
    CHECK(stepper_forward > 100 && !stepper_reverse && (stepper_enabled & 8));
    spindle_data_t *d = s->get_data(SpindleData_Counters);
    CHECK(d->pulse_count == stepper_pulses && d->index_count == stepper_pulses / 200);
    NEAR(s->get_data(SpindleData_RPM)->rpm, 60);
    CHECK(stepper_claimed);
    stepper_stop(s);
    CHECK(stepper_realtime > 100);
    grbl.on_execute_delay(STATE_IDLE);
    CHECK(stepper_delays == 1);
    unsigned pulses = stepper_pulses;
    stepper_poll(10);
    CHECK(stepper_pulses == pulses && !s->get_state(s).on);
    return 0;
}
