#include "support/boot_host.h"
static bool estop_released, alarm_observed_before_unlock;
static void release_estop_and_observe_restart(void)
{
    if(!estop_released && boot_reads == strlen("$I\n")) {
        CHECK(state_get() == STATE_ESTOP && sys.alarm == Alarm_EStop);
        CHECK(strstr(engine_output, "[VER:") != NULL);
        CHECK(boot_control_signals.e_stop);
        boot_control_signals.e_stop = false;
        estop_released = true;
    } else if(estop_released && boot_reads == strlen("$I\n\x18")) {
        CHECK(state_get() == STATE_ALARM);
        alarm_observed_before_unlock = true;
        boot_before_read = NULL;
    }
}
int main(void)
{
    boot_control_signals.e_stop = true;
    boot_before_read = release_estop_and_observe_restart;
    boot_program = "$I\n\x18$X\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(estop_released && alarm_observed_before_unlock);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(strstr(engine_output, "ALARM:10") != NULL);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == 0);
    return EXIT_SUCCESS;
}
