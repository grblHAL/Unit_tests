#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
int main(void)
{
    engine_prepare();
    pwm_config_t config = {.freq_hz = 50, .min = 0, .max = 180,
        .min_value = 5, .max_value = 10, .servo_mode = true};
    ioports_pwm_t pwm = {0};
    CHECK(ioports_precompute_pwm_values(&config, &pwm, 1000000));
    CHECK(!pwm.always_on);
    CHECK(ioports_compute_pwm_value(&pwm, 0) == 0);
    // Fractional gradients may round down by one timer tick before inversion.
    fprintf(stderr, "servo midpoint=%u maximum=%u period=%u\n", (unsigned)ioports_compute_pwm_value(&pwm, 90), (unsigned)ioports_compute_pwm_value(&pwm, 180), (unsigned)pwm.period);
    CHECK(ioports_compute_pwm_value(&pwm, 90) >= 1499 && ioports_compute_pwm_value(&pwm, 90) <= 1500);
    CHECK(ioports_compute_pwm_value(&pwm, 180) >= 1999 && ioports_compute_pwm_value(&pwm, 180) <= 2000);
    return EXIT_SUCCESS;
}
