#include "pwm_host.h"
int main(void)
{
    pwm_prepare();
#ifdef ARDUINO_TEENSY40
    const uint8_t pin = 36;
    CHECK(!pwm_is_available(NULL, 40));
#elif defined(ARDUINO_TEENSY41)
    const uint8_t pin = 36;
    CHECK(pwm_is_available(NULL, 54) && !pwm_is_available(NULL, 55) && !pwm_is_available(NULL, 34));
#else
    const uint8_t pin = 40;
    CHECK(pwm_is_available(NULL, 45) && !pwm_is_available(NULL, 46) && !pwm_is_available(NULL, 42));
#endif
    pwm_mux[pin + 1] = 99;
    const pwm_signal_t *p = pwm_claim(NULL, pin);
    CHECK(p && pwm_config(p, 1, 2000, false) && pwm_out(p, 600));
    CHECK(pwm_mux[pin + 1] == 99);
#ifdef ARDUINO_TEENSY40
    CHECK(pwm_mux[pin] == 1 && IMXRT_FLEXPWM1.SM[0].VAL5 == 600);
#elif defined(ARDUINO_TEENSY41)
    CHECK(pwm_mux[pin] == 6 && IMXRT_FLEXPWM2.SM[3].VAL3 == 600);
#else
    CHECK(pwm_mux[pin] == 1 && IMXRT_TMR2.CH[1].COMP2 == 600);
#endif
    F_BUS_ACTUAL = 75000000;
    CHECK(pwm_get_clock_hz(p) == 75000000);
    return 0;
}
