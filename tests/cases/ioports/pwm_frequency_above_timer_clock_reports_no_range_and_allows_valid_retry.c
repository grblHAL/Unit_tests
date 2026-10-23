#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
int main(void)
{
    engine_prepare();
    pwm_config_t config = {.freq_hz = 2000000, .min = 0, .max = 100,
        .min_value = 10, .max_value = 90};
    ioports_pwm_t pwm = {0};
    bool ready = ioports_precompute_pwm_values(&config, &pwm, 1000000);
    fprintf(stderr, "PWM above timer clock: ready=%u period=%lu min=%lu max=%lu\n",
        ready, (unsigned long)pwm.period, (unsigned long)pwm.min_value, (unsigned long)pwm.max_value);
    CHECK(!ready); /* No timer ticks means no PWM range; driver must use on/off fallback. */
    config.freq_hz = 1000;
    CHECK(ioports_precompute_pwm_values(&config, &pwm, 1000000));
    CHECK(pwm.period == 1000 && pwm.min_value == 100 && pwm.max_value == 900);
    CHECK(ioports_compute_pwm_value(&pwm, 50) == 500);
    CHECK(ioports_compute_pwm_value(&pwm, 150) == 900);
    return EXIT_SUCCESS;
}
