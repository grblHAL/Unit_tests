#include "pwm_host.h"
int main(void)
{
    pwm_prepare(2);
    pwm_load();
    CHECK(spindle_select(0));
    spindle_ptrs_t *s = spindle_get(0);
    s->set_state(s, (spindle_state_t){.on = On}, 600);
    const setting_detail_t *d = pwm_detail(Setting_RpmMax1);
    CHECK(d->datatype == Format_Decimal);
    *(float *)d->value = 18000;
    d = pwm_detail(Setting_PWMFreq1);
    *(float *)d->value = 1000;
    unsigned count = pwm_config_calls;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    CHECK(pwm_config_calls == count + 1 && pwm_value == 0);
    NEAR(pwm_captured.max, 18000);
    NEAR(pwm_captured.freq_hz, 1000);
    NEAR(s->rpm_max, 18000);
    CHECK(!s->get_state(s).on);
    return 0;
}
