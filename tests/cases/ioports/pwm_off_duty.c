#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    pwm_config_t config = {.freq_hz = 1000, .min = 10, .max = 110, .min_value = 10, .max_value = 90};
    ioports_pwm_t pwm = {0};
    config.off_value = 25;
    CHECK(ioports_precompute_pwm_values(&config, &pwm, 1000000));
    CHECK(pwm.always_on);
    CHECK(ioports_compute_pwm_value(&pwm, 0) == 250);
    pwm.invert_pwm = true;
    config.invert = true;
    CHECK(ioports_precompute_pwm_values(&config, &pwm, 1000000));
    CHECK(pwm.always_on && pwm.period == 1000);
    CHECK(ioports_compute_pwm_value(&pwm, 0) == 749);
    CHECK(ioports_compute_pwm_value(&pwm, 10) == 899);
    CHECK(ioports_compute_pwm_value(&pwm, 60) == 499);
    CHECK(ioports_compute_pwm_value(&pwm, 110) == 99);
    return EXIT_SUCCESS;
}
