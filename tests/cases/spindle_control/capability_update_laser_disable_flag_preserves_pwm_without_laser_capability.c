#include "support/spindle_caps_host.h"
int main(void)
{
    spindle_ptrs_t *configured = prepare_spindle_caps(true);
    pwm_data.flags.laser_mode_disable = true;
    spindle_update_caps(configured,&pwm_data);
    CHECK(!spindle_get(0)->cap.laser && !configured->cap.laser);
    CHECK(spindle_get(0)->type == SpindleType_PWM);
    return EXIT_SUCCESS;
}
