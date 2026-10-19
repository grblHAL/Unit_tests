#include "support/boot_host.h"
static bool homing_alarm_seen, reset_alarm_seen;
static void observe_homing_lock_reconfiguration(void)
{
    if(boot_reads == 0) {
        CHECK(sys.alarm == Alarm_HomingRequired);
        homing_alarm_seen = true;
    } else if(boot_reads == sizeof("$22=0\n\x18") - 1) {
        CHECK(state_get() == STATE_ALARM && sys.alarm == Alarm_None);
        reset_alarm_seen = true;
        boot_before_read = NULL;
    }
}
int main(void)
{
    boot_homing_required = true;
    boot_before_read = observe_homing_lock_reconfiguration;
    boot_program = "$22=0\n\x18$X\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(homing_alarm_seen && reset_alarm_seen);
    CHECK(!settings.homing.flags.enabled);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(strstr(engine_output, "ALARM:11") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == 0);
    return EXIT_SUCCESS;
}
