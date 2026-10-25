#include "stepper_host.h"
int main(void)
{
    stepper_resolution = 200.5f;
    settings.stepper_spindle_flags.sync_position = On;
    settings.stepper_spindle_flags.allow_axis_control = On;
    sys.position[3] = 215;
    stepper_prepare();
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 60);
    stepper_cruise(s);
    stepper_poll(20);
    stepper_stop(s);
    double steps = 215.0 + stepper_forward - stepper_reverse;
    CHECK(sys.position[3] == (int32_t)lround(fmod(steps, 200.5)));
    CHECK(stepper_position_syncs == 1 && !stepper_claimed);
    CHECK(fabsf(gc_state.position[3] - sys.position[3] / 200.5f) < 0.00001f);
    return 0;
}
