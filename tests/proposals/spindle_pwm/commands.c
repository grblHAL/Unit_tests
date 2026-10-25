#include "pwm_host.h"
int main(void)
{
    pwm_prepare(2);
    pwm_load();
    CHECK(!pwm_warnings && spindle_select(0));
    spindle_ptrs_t *s = spindle_get(0);
    CHECK(s && s->type == SpindleType_PWM && s->cap.direction == TEST_DIRECTION);
    CHECK(pwm_config_calls >= 1 && s->cap.rpm_range_locked);
    NEAR(pwm_captured.freq_hz, 5000);
    NEAR(pwm_captured.max, 1000);
    unsigned on = (unsigned)pwm_get(Setting_Spindle_OnPort);
    s->set_state(s, (spindle_state_t){.on = On, .ccw = On}, 600);
    CHECK(pwm_outputs[on] && pwm_value == 600);
#if TEST_DIRECTION
    unsigned dir = (unsigned)pwm_get(Setting_Spindle_DirPort);
    CHECK(dir != on && pwm_outputs[dir]);
#endif
    s->update_rpm(s, 800);
    CHECK(pwm_value == 800);
    s->set_state(s, (spindle_state_t){0}, 0);
    CHECK(!pwm_outputs[on] && pwm_value == 0 && !s->get_state(s).on);
    return 0;
}
