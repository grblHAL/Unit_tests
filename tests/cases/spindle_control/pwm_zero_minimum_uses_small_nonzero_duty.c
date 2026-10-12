#include "support/spindle_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_pwm();
    pwm_settings.pwm_min_value = 0;
    compute_spindle_pwm();
    CHECK(pwm_data.min_value == 3);
    CHECK(pwm_data.compute_value(&pwm_data, 1000, false) == 3);
    return EXIT_SUCCESS;
}
