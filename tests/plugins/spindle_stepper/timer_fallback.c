#include "stepper_host.h"
int main(void)
{
    stepper_timer_available = true;
    stepper_timer_claim_ok = false;
    stepper_prepare();
    CHECK(stepper_settings && stepper_timer_claims == 2);
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 60);
    stepper_cruise(s);
    stepper_poll(20);
    CHECK(stepper_forward > 20 && !stepper_timer_starts);
    stepper_stop(s);
    return 0;
}
