#include "overdrive_host.h"
int main(void)
{
    ovd_prepare();
    CHECK(ovd_command(25, true) == Status_OK);
    hal.driver_reset();
    spindle_ptrs_t *s = spindle_get(0);
    CHECK(ovd_resets == 1 && !s->context.pwm->flags.laser_off_overdrive);
    NEAR(s->context.pwm->off_overdrive_pct, 0);
    return 0;
}
