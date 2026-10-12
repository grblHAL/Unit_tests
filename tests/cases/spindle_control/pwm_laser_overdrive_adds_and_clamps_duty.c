#include "support/spindle_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_pwm();
    pwm_settings.flags.enable_rpm_controlled = true;
    compute_spindle_pwm();
    pwm_data.set_laser_overdrive(&pwm_data, 20);
    CHECK(pwm_data.flags.laser_off_overdrive);
    CHECK(pwm_data.compute_value(&pwm_data, 5000, false) == 500);
    CHECK(pwm_data.pwm_overdrive == 600);
    CHECK(pwm_data.compute_value(&pwm_data, 9000, false) == 900);
    CHECK(pwm_data.pwm_overdrive == 900);
    return EXIT_SUCCESS;
}
