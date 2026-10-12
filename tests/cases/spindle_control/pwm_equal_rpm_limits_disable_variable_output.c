#include "support/spindle_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_pwm();
    pwm_settings.rpm_max = pwm_settings.rpm_min;
    CHECK(!spindle_precompute_pwm_values(&pwm_spindle, &pwm_data, &pwm_settings, 1000000));
    CHECK(!pwm_spindle.cap.variable);
    CHECK(pwm_data.compute_value(&pwm_data, 5000, false) == 0);
    return EXIT_SUCCESS;
}
