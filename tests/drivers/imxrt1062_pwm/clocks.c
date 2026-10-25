#include "pwm_host.h"
int main(void)
{
    pwm_prepare();
    CCM_CCGR4 = 1;
    const uint8_t pins[] = {0, 4, 28, 2};
    for (unsigned i = 0; i < 4; i++)
    {
        const pwm_signal_t *p = pwm_claim(NULL, pins[i]);
        CHECK(p && pwm_config(p, 1, 1000, false));
    }
    uint32_t mask = CCM_CCGR4_PWM1(CCM_CCGR_ON) | CCM_CCGR4_PWM2(CCM_CCGR_ON) |
                    CCM_CCGR4_PWM3(CCM_CCGR_ON) | CCM_CCGR4_PWM4(CCM_CCGR_ON);
    CHECK((CCM_CCGR4 & mask) == mask && (CCM_CCGR4 & 1));
    return 0;
}
