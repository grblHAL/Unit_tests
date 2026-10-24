#include "pwm_host.h"
int main(void)
{
    pwm_prepare();
    const pwm_signal_t *x = pwm_claim(NULL, 0), *a = pwm_claim(NULL, 2), *b = pwm_claim(NULL, 3),
                       *q = pwm_claim(NULL, 11);
    CHECK(x && a && b && q);
    CHECK(pwm_config(x, 0, 1000, true) && IMXRT_FLEXPWM1.SM[1].OCTRL == FLEXPWM_SMOCTRL_POLX);
    CHECK(pwm_config(a, 0, 1000, true) && IMXRT_FLEXPWM4.SM[2].OCTRL == FLEXPWM_SMOCTRL_POLA);
    CHECK(pwm_config(b, 0, 1000, true) && IMXRT_FLEXPWM4.SM[2].OCTRL == FLEXPWM_SMOCTRL_POLB);
    CHECK(pwm_config(q, 0, 1000, true) && (IMXRT_TMR1.CH[2].SCTRL & TMR_SCTRL_OPS));
    CHECK(pwm_config(q, 0, 1000, false) && !(IMXRT_TMR1.CH[2].SCTRL & TMR_SCTRL_OPS));
    return 0;
}
