#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    sys.abort = true;
    CHECK(!spindle_set_state(active,(spindle_state_t){.on=true},6000));
    CHECK(ramp_state_calls == 0 && ramp_pwm_calls == 0 && !ramp_hardware_state.on);
    NEAR(active->param->rpm,0);
    return EXIT_SUCCESS;
}
