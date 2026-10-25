#include "stepper_host.h"
int main(void)
{
    stepper_prepare();
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 60);
    stepper_cruise(s);
    stepper_poll(20);
    s->set_state(s, (spindle_state_t){.on = On, .ccw = On}, 60);
    stepper_cruise(s);
    stepper_poll(20);
    CHECK(stepper_forward > 20 && stepper_reverse > 20 && s->get_state(s).ccw);
    stepper_stop(s);
    return 0;
}
