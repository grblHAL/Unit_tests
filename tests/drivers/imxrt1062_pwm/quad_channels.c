#include "pwm_host.h"
int main(void)
{
    pwm_prepare();
    const pwm_signal_t *p0 = pwm_claim(NULL, 10), *p1 = pwm_claim(NULL, 12),
                       *p2 = pwm_claim(NULL, 11);
    CHECK(p0 && p1 && p2 && pwm_config(p0, 1, 1000, false) && pwm_config(p1, 2, 2000, true) &&
          pwm_config(p2, 3, 4000, false));
    CHECK(pwm_out(p0, 250) && pwm_out(p1, 1000) && pwm_out(p2, 3000));
    CHECK((IMXRT_TMR1.ENBL & 7) == 7);
    const unsigned period[] = {1000, 2000, 4000}, duty[] = {250, 1000, 3000};
    for (unsigned channel = 0; channel < 3; channel++)
    {
        CHECK(IMXRT_TMR1.CH[channel].COMP1 == period[channel] &&
              IMXRT_TMR1.CH[channel].COMP2 == duty[channel] &&
              IMXRT_TMR1.CH[channel].CMPLD1 == period[channel] - duty[channel]);
        CHECK(!!(IMXRT_TMR1.CH[channel].SCTRL & TMR_SCTRL_OPS) == (channel == 1));
    }
    CHECK(pwm_config(p1, 0, 3000, false) && pwm_out(p1, 1500));
    CHECK(IMXRT_TMR1.CH[1].COMP1 == 3000 && IMXRT_TMR1.CH[1].COMP2 == 1500 &&
          !(IMXRT_TMR1.CH[1].SCTRL & TMR_SCTRL_OPS));
    CHECK(IMXRT_TMR1.CH[0].COMP1 == 1000 && IMXRT_TMR1.CH[0].COMP2 == 250 &&
          IMXRT_TMR1.CH[2].COMP1 == 4000 && IMXRT_TMR1.CH[2].COMP2 == 3000);
    return 0;
}
