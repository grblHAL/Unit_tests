#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    pwm_config_t config = {.freq_hz = 1000, .min = 10, .max = 110, .min_value = 10, .max_value = 90};
    ioports_pwm_t pwm = {0};
    CHECK(ioports_precompute_pwm_values(&config, &pwm, 1000000));
    CHECK(pwm.period == 1000);
    CHECK(pwm.min_value == 100);
    CHECK(pwm.max_value == 900);
    NEAR(pwm.pwm_gradient, 8);
    return EXIT_SUCCESS;
}
