#include "support/stepper_idle_host.h"

int main(void)
{
    prepare_stepper_idle();
    settings.steppers.idle_lock_time = 80;
    st_go_idle();
    CHECK(sys.steppers_deenergize);
    st_wake_up();
    CHECK(!sys.steppers_deenergize);
    unsigned before = motor_enable_calls;
    engine_ticks = 80; engine_execute_tasks(STATE_IDLE);
    CHECK(motor_enable_calls == before);
    CHECK(wake_calls == 1);
    return EXIT_SUCCESS;
}
