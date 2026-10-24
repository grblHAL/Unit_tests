#include "pwm_host.h"
int main(void)
{
    pwm_prepare();
    const pwm_signal_t *x = pwm_claim(NULL, 0), *a = pwm_claim(NULL, 4), *q = pwm_claim(NULL, 10);
    CHECK(x && a && q && pwm_config(x, 1, 2000, false) && pwm_config(a, 2, 4000, true) &&
          pwm_config(q, 3, 8000, false));
    CHECK(pwm_out(x, 500) && pwm_out(a, 2000) && pwm_out(q, 6000));
    CHECK(IMXRT_FLEXPWM1.SM[1].VAL0 == 1500 && IMXRT_FLEXPWM2.SM[0].VAL3 == 2000 &&
          IMXRT_TMR1.CH[0].COMP2 == 6000 && IMXRT_TMR1.CH[0].CMPLD1 == 2000);
    uint16_t a_control = IMXRT_FLEXPWM2.SM[0].CTRL, q_control = IMXRT_TMR1.CH[0].CTRL;
    CHECK(pwm_config(x, 0, 1000, true) && pwm_out(x, 1000));
    CHECK(IMXRT_FLEXPWM1.SM[1].VAL0 == 0 && IMXRT_FLEXPWM2.SM[0].CTRL == a_control &&
          IMXRT_FLEXPWM2.SM[0].VAL1 == 4000 && IMXRT_FLEXPWM2.SM[0].VAL3 == 2000 &&
          IMXRT_FLEXPWM2.SM[0].OCTRL == FLEXPWM_SMOCTRL_POLA &&
          IMXRT_TMR1.CH[0].CTRL == q_control && IMXRT_TMR1.CH[0].COMP1 == 8000 &&
          IMXRT_TMR1.CH[0].COMP2 == 6000 && IMXRT_TMR1.CH[0].CMPLD1 == 2000);
    CHECK(pwm_out(a, 0) && pwm_out(q, 0));
    CHECK(IMXRT_FLEXPWM1.SM[1].VAL0 == 0 && IMXRT_FLEXPWM2.SM[0].VAL3 == 0 &&
          IMXRT_TMR1.CH[0].COMP2 == 0 && IMXRT_TMR1.CH[0].CMPLD1 == 8000);
    return 0;
}
