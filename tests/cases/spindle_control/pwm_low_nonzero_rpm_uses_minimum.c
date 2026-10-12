#include "support/spindle_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_pwm();
    compute_spindle_pwm();
    CHECK(pwm_data.compute_value(&pwm_data, 500, false) == 100);
    CHECK(pwm_data.compute_value(&pwm_data, 1000, false) == 100);
    return EXIT_SUCCESS;
}
