#include "support/spindle_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_pwm();
    pwm_settings.pwm_off_value = 5;
    compute_spindle_pwm();
    CHECK(pwm_data.flags.always_on && pwm_data.off_value == 50);
    CHECK(pwm_data.compute_value(&pwm_data, 0, false) == 50);
    return EXIT_SUCCESS;
}
