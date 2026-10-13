#include "support/stepper_idle_host.h"

int main(void)
{
    prepare_stepper_idle();
    settings.steppers.idle_lock_time = 0;
    st_go_idle();
    CHECK(motor_enable_calls == 1);
    CHECK(last_motor_enable.mask == 0 && last_motor_hold);
    CHECK(!sys.steppers_deenergize);
    return EXIT_SUCCESS;
}
