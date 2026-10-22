#include "support/system_command_host.h"
#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    float steps = settings.axis[X_AXIS].steps_per_mm;
    state_set(STATE_CYCLE);
    CHECK(state_get() == STATE_CYCLE && wake_calls == 1);
    CHECK(system_command("$100=160") == Status_IdleError);
    NEAR(settings.axis[X_AXIS].steps_per_mm, steps);
    CHECK(plan_get_current_block() == first && state_get() == STATE_CYCLE);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80 && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
