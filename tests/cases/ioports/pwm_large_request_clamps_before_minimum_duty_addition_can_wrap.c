#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
#include <stdint.h>
int main(void)
{
    engine_prepare();
    pwm_config_t config = {.freq_hz = 1000, .min = 10, .max = 110,
        .min_value = 10, .max_value = 90};
    ioports_pwm_t pwm = {0};
    CHECK(ioports_precompute_pwm_values(&config, &pwm, 10000000));
    CHECK(pwm.period == 10000 && pwm.min_value == 1000 && pwm.max_value == 9000);
    CHECK(ioports_compute_pwm_value(&pwm, 110) == 9000);
    uint_fast16_t result = ioports_compute_pwm_value(&pwm, 828);
    fprintf(stderr, "PWM fast integer bytes=%u, request=828 result=%lu expected=9000\n",
        (unsigned)sizeof(uint_fast16_t), (unsigned long)result);
    CHECK(result == 9000);
    return EXIT_SUCCESS;
}
