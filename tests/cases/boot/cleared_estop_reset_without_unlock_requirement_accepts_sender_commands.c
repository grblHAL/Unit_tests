#include "support/boot_host.h"

static bool released, reset_seen, command_seen;
static void configure_estop_policy(settings_t *current)
{
    CHECK(current == &settings && hal.signals_cap.e_stop);
    char disabled[] = "0";
    CHECK(settings_store_setting(Setting_UnlockAfterEStop, disabled) == Status_OK);
    CHECK(settings.flags.no_unlock_after_estop);
}
static void service_estop_policy(void)
{
    if(!released) {
        CHECK(state_get() == STATE_ESTOP && sys.alarm == Alarm_EStop);
        boot_control_signals.e_stop = false;
        released = true;
    } else if(boot_reads == strlen("\x18") && !reset_seen) {
        CHECK(settings.flags.no_unlock_after_estop);
        CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
        reset_seen = true;
    } else if(boot_reads == strlen("\x18G91\n") && !command_seen) {
        CHECK(state_get() == STATE_IDLE && gc_state.modal.distance_incremental);
        CHECK(strstr(engine_output, "error:") == NULL);
        command_seen = true;
    }
}
int main(void)
{
    boot_control_signals.e_stop = true;
    boot_during_setup = configure_estop_policy;
    boot_before_read = service_estop_policy;
    boot_program = "\x18G91\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(released && reset_seen && command_seen);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(gc_state.modal.distance_incremental);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
