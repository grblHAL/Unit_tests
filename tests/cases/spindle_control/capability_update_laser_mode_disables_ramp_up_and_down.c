#include "support/spindle_caps_host.h"
int main(void)
{
    spindle_ptrs_t *configured = prepare_spindle_caps(true);
    pwm_data.flags.ramp_pwm = true;
    settings.spindle.on_delay = settings.spindle.off_delay = 100;
    spindle_update_caps(configured,&pwm_data);
    spindle_ptrs_t *active = spindle_get(0);
    CHECK(active->cap.laser && configured->cap.laser);
    CHECK(!active->param->option.ramp_up && !active->param->option.ramp_down);
    return EXIT_SUCCESS;
}
