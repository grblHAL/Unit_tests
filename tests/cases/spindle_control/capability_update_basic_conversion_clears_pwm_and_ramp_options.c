#include "support/spindle_caps_host.h"
int main(void)
{
    spindle_ptrs_t *configured = prepare_spindle_caps(false);
    pwm_data.flags.ramp_pwm = true;
    settings.spindle.on_delay = settings.spindle.off_delay = 100;
    spindle_update_caps(configured,&pwm_data);
    CHECK(spindle_get(0)->param->option.ramp_up);
    spindle_update_caps(configured,NULL);
    spindle_ptrs_t *active = spindle_get(0);
    CHECK(active->type == SpindleType_Basic && active->pwm_off_value == 0 && !active->cap.laser);
    CHECK(!active->param->option.ramp_up && !active->param->option.ramp_down && !active->param->option.ignore_delays);
    return EXIT_SUCCESS;
}
