#include "pwm_host.h"
int main(void)
{
    pwm_prepare();
    const pwm_signal_t *p = pwm_claim(NULL, 0);
    CHECK(p && pwm_config(p, 3, 1000, false));
    CHECK(pwm_mux[0] == 4 && IMXRT_FLEXPWM1.SM[1].VAL1 == 1000 &&
          (IMXRT_FLEXPWM1.SM[1].CTRL & 0x70) == 0x30);
    CHECK(pwm_out(p, 250));
    CHECK(IMXRT_FLEXPWM1.SM[1].VAL0 == 750 && (IMXRT_FLEXPWM1.OUTEN & FLEXPWM_OUTEN_PWMX_EN(2)));
    return 0;
}
