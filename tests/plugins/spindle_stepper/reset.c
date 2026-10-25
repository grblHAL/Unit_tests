#include "stepper_host.h"
int main(void)
{
    stepper_prepare();
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 60);
    stepper_cruise(s);
    stepper_poll(20);
    CHECK(grbl.on_reset);
    grbl.on_reset();
    unsigned pulses = stepper_pulses;
    stepper_poll(20);
    CHECK(stepper_pulses == pulses);
    return 0;
}
