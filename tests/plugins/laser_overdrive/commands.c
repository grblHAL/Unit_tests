#include "overdrive_host.h"
int main(void)
{
    ovd_prepare();
    spindle_ptrs_t *s = spindle_get(0);
    CHECK(ovd_command(25, true) == Status_OK && s->context.pwm->flags.laser_off_overdrive);
    CHECK(s->get_pwm(s, 5000) == 500 && s->context.pwm->pwm_overdrive == 625);
    CHECK(s->get_pwm(s, 9000) == 900 && s->context.pwm->pwm_overdrive == 1000);
    CHECK(ovd_command(0, true) == Status_OK && !s->context.pwm->flags.laser_off_overdrive);
    NEAR(s->context.pwm->off_overdrive_pct, 0);
    return 0;
}
