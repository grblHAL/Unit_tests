#include "pwm_host.h"
int main(void)
{
    pwm_prepare();
    const pwm_signal_t *x = pwm_claim(NULL, 0), *q = pwm_claim(NULL, 10);
    CHECK(x && q && pwm_config(x, 0, 1000, false) && pwm_config(q, 0, 1000, false));
    CHECK(pwm_out(x, 0) && IMXRT_FLEXPWM1.SM[1].VAL0 == 1000);
    CHECK(pwm_out(x, 1000) && IMXRT_FLEXPWM1.SM[1].VAL0 == 0);
    CHECK(pwm_out(q, 0) && IMXRT_TMR1.CH[0].CMPLD1 == 1000);
    CHECK(pwm_out(q, 1000) && IMXRT_TMR1.CH[0].COMP2 == 1000 && IMXRT_TMR1.CH[0].CMPLD1 == 0);
    return 0;
}
