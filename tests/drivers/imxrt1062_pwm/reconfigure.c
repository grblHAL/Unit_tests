#include "pwm_host.h"
int main(void)
{
    pwm_prepare();
    const pwm_signal_t *x = pwm_claim(NULL, 0), *a = pwm_claim(NULL, 4), *b = pwm_claim(NULL, 7),
                       *q = pwm_claim(NULL, 10);
    CHECK(x && a && b && q);
    const unsigned periods[] = {1000, 4000, 2000};
    const unsigned prescalers[] = {0, 3, 1};
    for (unsigned i = 0; i < 3; i++)
    {
        bool inverted = i == 1;
        CHECK(pwm_config(x, prescalers[i], periods[i], inverted) &&
              pwm_config(a, prescalers[i], periods[i], inverted) &&
              pwm_config(b, prescalers[i], periods[i], inverted) &&
              pwm_config(q, prescalers[i], periods[i], inverted));
        CHECK(IMXRT_FLEXPWM1.SM[1].VAL1 == periods[i] && IMXRT_FLEXPWM2.SM[0].VAL1 == periods[i] &&
              IMXRT_FLEXPWM1.SM[3].VAL1 == periods[i] && IMXRT_TMR1.CH[0].COMP1 == periods[i]);
        CHECK((IMXRT_FLEXPWM1.SM[1].CTRL & FLEXPWM_SMCTRL_PRSC(7)) ==
                  FLEXPWM_SMCTRL_PRSC(prescalers[i]) &&
              (IMXRT_TMR1.CH[0].CTRL & TMR_CTRL_PCS(15)) == TMR_CTRL_PCS(prescalers[i]));
        CHECK(IMXRT_FLEXPWM1.SM[1].OCTRL == (inverted ? FLEXPWM_SMOCTRL_POLX : 0) &&
              IMXRT_FLEXPWM2.SM[0].OCTRL == (inverted ? FLEXPWM_SMOCTRL_POLA : 0) &&
              IMXRT_FLEXPWM1.SM[3].OCTRL == (inverted ? FLEXPWM_SMOCTRL_POLB : 0));
        CHECK(!!(IMXRT_TMR1.CH[0].SCTRL & TMR_SCTRL_OPS) == inverted);
        unsigned duty = periods[i] / 4;
        CHECK(pwm_out(x, duty) && pwm_out(a, duty) && pwm_out(b, duty) && pwm_out(q, duty));
        CHECK(IMXRT_FLEXPWM1.SM[1].VAL0 == periods[i] - duty && IMXRT_FLEXPWM2.SM[0].VAL3 == duty &&
              IMXRT_FLEXPWM1.SM[3].VAL5 == duty && IMXRT_TMR1.CH[0].COMP2 == duty &&
              IMXRT_TMR1.CH[0].CMPLD1 == periods[i] - duty);
    }
    CHECK(pwm_mux[0] == 4 && pwm_mux[4] == 1 && pwm_mux[7] == 6 && pwm_mux[10] == 1);
    return 0;
}
