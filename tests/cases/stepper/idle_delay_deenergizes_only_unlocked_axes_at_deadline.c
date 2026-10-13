#include "support/stepper_idle_host.h"

int main(void)
{
    prepare_stepper_idle();
    settings.steppers.idle_lock_time = 80;
    settings.steppers.energize.mask = 2;
    st_go_idle();
    CHECK(sys.steppers_deenergize);
    CHECK(motor_enable_calls == 0);
    engine_ticks = 79; engine_execute_tasks(STATE_IDLE);
    CHECK(motor_enable_calls == 0);
    engine_ticks = 80; engine_execute_tasks(STATE_IDLE);
    CHECK(motor_enable_calls == 1);
    CHECK(last_motor_enable.mask == 2 && last_motor_hold);
    CHECK(!sys.steppers_deenergize);
    return EXIT_SUCCESS;
}
