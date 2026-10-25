#include "pwm_host.h"
int main(void)
{
    pwm_prepare();
    const pwm_signal_t *a = pwm_claim(NULL, 2), *b = pwm_claim(NULL, 3);
    CHECK(a && b && pwm_config(a, 2, 2000, false) && pwm_config(b, 2, 2000, false));
    CHECK(pwm_out(a, 500) && pwm_out(b, 1500));
    CHECK(IMXRT_FLEXPWM4.SM[2].VAL3 == 500 && IMXRT_FLEXPWM4.SM[2].VAL5 == 1500);
    CHECK((IMXRT_FLEXPWM4.OUTEN & (FLEXPWM_OUTEN_PWMA_EN(4) | FLEXPWM_OUTEN_PWMB_EN(4))) ==
          (FLEXPWM_OUTEN_PWMA_EN(4) | FLEXPWM_OUTEN_PWMB_EN(4)));
    return 0;
}
