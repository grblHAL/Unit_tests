#include "support/spindle_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_pwm();
    compute_spindle_pwm();
    pwm_data.set_laser_overdrive(&pwm_data, 20);
    CHECK(!pwm_data.flags.laser_off_overdrive);
    CHECK(pwm_data.compute_value(&pwm_data, 5000, false) == 500);
    CHECK(pwm_data.pwm_overdrive == 0);
    return EXIT_SUCCESS;
}
