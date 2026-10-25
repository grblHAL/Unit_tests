#include "pwm_host.h"
int main(void)
{
    const uint8_t pins[] = {2, 4, 6, 8, 10};
    for (unsigned i = 0; i < 5; i++)
    {
        CHECK(pwm_is_available(NULL, pins[i]));
        const pwm_signal_t *p = pwm_claim(NULL, pins[i]);
        CHECK(p && !pwm_is_available(NULL, pins[i]) && pwm_enable(p));
    }
    CHECK(!pwm_claim(NULL, 2));
    return 0;
}
