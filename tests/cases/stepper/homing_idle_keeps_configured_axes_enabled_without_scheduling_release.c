#include "support/stepper_idle_host.h"

int main(void)
{
    prepare_stepper_idle();
    settings.steppers.idle_lock_time = 80;
    settings.steppers.energize.mask = 1;
    state_set(STATE_HOMING);
    CHECK(sys.flags.is_homing);
    st_go_idle();
    CHECK(motor_enable_calls == 1);
    CHECK(last_motor_enable.mask == 1 && last_motor_hold);
    CHECK(!sys.steppers_deenergize);
    engine_ticks = 80; engine_execute_tasks(STATE_HOMING);
    CHECK(motor_enable_calls == 1);
    return EXIT_SUCCESS;
}
