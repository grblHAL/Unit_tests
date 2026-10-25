#include "pwm_host.h"
int main(void)
{
    CHECK(pwm_is_available(NULL, 2));
    CHECK(!pwm_is_available(NULL, 16) && !pwm_is_available(NULL, 255));
    const pwm_signal_t *pwm = pwm_claim(NULL, 2);
    CHECK(pwm && !pwm_is_available(NULL, 2) && !pwm_claim(NULL, 2));
    CHECK(pwm_enable(pwm) && pwm_get_clock_hz(pwm) == 150000000);
    return 0;
}
