#include "support/spindle_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_pwm();
    pwm_spindle.cap.pwm_invert = true;
    pwm_settings.invert.pwm = true;
    compute_spindle_pwm();
    CHECK(pwm_data.compute_value(&pwm_data, 0, false) == 1000);
    CHECK(pwm_data.compute_value(&pwm_data, 1000, false) == 900);
    CHECK(pwm_data.compute_value(&pwm_data, 9000, false) == 100);
    return EXIT_SUCCESS;
}
