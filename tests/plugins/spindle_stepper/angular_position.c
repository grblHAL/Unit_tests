#include "stepper_host.h"
int main(void)
{
    stepper_prepare();
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 60);
    stepper_cruise(s);
    stepper_poll(250);
    stepper_stop(s);
    CHECK(stepper_forward > 200 && !stepper_reverse);
    float revolutions = stepper_forward / 200.0f;
    CHECK(fabsf(s->get_data(SpindleData_AngularPosition)->angular_position - revolutions) <
          0.00001f);
    CHECK(s->get_data(SpindleData_Counters)->index_count == stepper_forward / 200);
    NEAR(s->get_data(SpindleData_RPM)->rpm, 0);
    return 0;
}
