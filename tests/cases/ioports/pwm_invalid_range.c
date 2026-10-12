#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    pwm_config_t config = {.freq_hz = 1000, .min = 10, .max = 110, .min_value = 10, .max_value = 90};
    ioports_pwm_t pwm = {0};
    config.max = config.min;
    CHECK(!ioports_precompute_pwm_values(&config, &pwm, 1000000));
    config.max = config.min - 1;
    CHECK(!ioports_precompute_pwm_values(&config, &pwm, 1000000));
    return EXIT_SUCCESS;
}
