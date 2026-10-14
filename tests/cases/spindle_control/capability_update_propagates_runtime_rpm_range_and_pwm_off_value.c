#include "support/spindle_caps_host.h"
int main(void)
{
    spindle_ptrs_t *configured = prepare_spindle_caps(false);
    configured->rpm_min = 900;
    configured->rpm_max = 14000;
    pwm_data.off_value = 7;
    spindle_update_caps(configured,&pwm_data);
    spindle_ptrs_t *active = spindle_get(0);
    NEAR(active->rpm_min,900);
    NEAR(active->rpm_max,14000);
    CHECK(active->pwm_off_value == 7);
    CHECK(active->type == SpindleType_PWM && !active->cap.laser);
    return EXIT_SUCCESS;
}
