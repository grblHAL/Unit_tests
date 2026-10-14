#include "support/spindle_caps_host.h"
int main(void)
{
    spindle_ptrs_t *configured = prepare_spindle_caps(false);
    pwm_data.flags.ramp_pwm = true;
    pwm_settings.flags.ignore_delays = true;
    settings.spindle.on_delay = 100;
    settings.spindle.off_delay = 0;
    spindle_update_caps(configured,&pwm_data);
    spindle_param_t *param = spindle_get(0)->param;
    CHECK(param->option.ramp_up && !param->option.ramp_down && !param->option.ignore_delays);
    return EXIT_SUCCESS;
}
