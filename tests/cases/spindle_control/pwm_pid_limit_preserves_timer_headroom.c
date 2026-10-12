#include "support/spindle_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_pwm();
    compute_spindle_pwm();
    CHECK(pwm_data.compute_value(&pwm_data, 10000, true) == 999);
    CHECK(pwm_data.compute_value(&pwm_data, 10000, false) == 900);
    return EXIT_SUCCESS;
}
