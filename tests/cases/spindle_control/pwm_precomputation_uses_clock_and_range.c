#include "support/spindle_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_pwm();
    compute_spindle_pwm();
    CHECK(pwm_data.period == 1000 && pwm_data.min_value == 100 && pwm_data.max_value == 900);
    CHECK(pwm_spindle.cap.variable && pwm_spindle.cap.rpm_range_locked);
    NEAR(pwm_data.pwm_gradient, 0.1f);
    CHECK(pwm_spindle.context.pwm == &pwm_data);
    return EXIT_SUCCESS;
}
