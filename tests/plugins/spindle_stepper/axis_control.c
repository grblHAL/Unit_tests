#include "stepper_host.h"
int main(void)
{
    settings.stepper_spindle_flags.allow_axis_control = On;
    stepper_prepare();
    CHECK(!stepper_claimed);
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 60);
    stepper_cruise(s);
    CHECK(stepper_claimed);
    stepper_stop(s);
    CHECK(!stepper_claimed);
    return 0;
}
