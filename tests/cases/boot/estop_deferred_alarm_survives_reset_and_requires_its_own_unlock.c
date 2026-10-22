#include "support/boot_host.h"
static bool released, restart_seen, deferred_seen, rejection_seen, unlock_seen;
static void service_deferred_alarm(void)
{
    if(!released) {
        CHECK(state_get() == STATE_ESTOP && sys.alarm == Alarm_EStop);
        system_raise_alarm(Alarm_ProbeProtect);
        CHECK(sys.alarm == Alarm_EStop && sys.alarm_pending == Alarm_ProbeProtect);
        boot_control_signals.e_stop = false;
        released = true;
    } else if(boot_reads == strlen("\x18") && !restart_seen) {
        CHECK(state_get() == STATE_ALARM && sys.alarm_pending == Alarm_ProbeProtect);
        restart_seen = true;
    } else if(boot_reads == strlen("\x18$X\n") && !deferred_seen) {
        CHECK(state_get() == STATE_ALARM && sys.alarm == Alarm_ProbeProtect);
        CHECK(sys.alarm_pending == Alarm_None);
        deferred_seen = true;
    } else if(boot_reads == strlen("\x18$X\nG91\n") && !rejection_seen) {
        CHECK(state_get() == STATE_ALARM && !gc_state.modal.distance_incremental);
        CHECK(strstr(engine_output, "error:9") != NULL);
        rejection_seen = true;
    } else if(boot_reads == strlen("\x18$X\nG91\n$X\n") && !unlock_seen) {
        CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
        unlock_seen = true;
    }
}
int main(void)
{
    boot_control_signals.e_stop = true;
    boot_before_read = service_deferred_alarm;
    boot_program = "\x18$X\nG91\n$X\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(released && restart_seen && deferred_seen && rejection_seen && unlock_seen);
    CHECK(sys.alarm_pending == Alarm_None && state_get() == STATE_IDLE);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == 0);
    return EXIT_SUCCESS;
}
