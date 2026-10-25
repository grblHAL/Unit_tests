#include "pwm_host.h"
int main(void)
{
    pwm_prepare();
    const pwm_signal_t *p = pwm_claim(NULL, 10);
    CHECK(p && pwm_config(p, 2, 1000, false));
    CHECK(pwm_mux[10] == 1 && IMXRT_TMR1.CH[0].COMP1 == 1000 && IMXRT_TMR1.CH[0].LOAD == 0 &&
          (IMXRT_TMR1.ENBL & 1));
    CHECK(pwm_out(p, 250));
    CHECK(IMXRT_TMR1.CH[0].COMP2 == 250 && IMXRT_TMR1.CH[0].CMPLD1 == 750);
    return 0;
}
