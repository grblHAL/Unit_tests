#include "pwm_host.h"
int main(void)
{
    pwm_config_ok = false;
    pwm_prepare(2);
    pwm_load();
    CHECK(!pwm_warnings && spindle_select(0));
    spindle_ptrs_t *s = spindle_get(0);
    unsigned count = pwm_analog_calls;
    s->set_state(s, (spindle_state_t){.on = On}, 600);
    unsigned on = (unsigned)pwm_get(Setting_Spindle_OnPort);
    CHECK(pwm_outputs[on] && pwm_analog_calls == count);
    s->set_state(s, (spindle_state_t){0}, 0);
    CHECK(!pwm_outputs[on] && pwm_analog_calls == count);
    return 0;
}
