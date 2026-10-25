#include "stepper_host.h"
int main(void)
{
    stepper_prepare();
    spindle_ptrs_t *s = spindle_get(0);
    hal.stepper.enable((axes_signals_t){.mask = 3}, false);
    s->set_state(s, (spindle_state_t){.on = On}, 60);
    stepper_cruise(s);
    CHECK(stepper_enabled == 11);
    hal.stepper.enable((axes_signals_t){.mask = 1}, false);
    CHECK(stepper_enabled == 9);
    stepper_stop(s);
    CHECK(stepper_enabled == 1);
    return 0;
}
