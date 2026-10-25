#include "support/boot_homing_motion_host.h"
static bool reset_sent;
static void reset_before_homing_motion(sys_state_t state)
{
    boot_homing_foreground(state);
    if(!reset_sent && state == STATE_HOMING && boot_wake_calls == 0) {
        CHECK(!settings.status_report.when_homing);
        reset_sent = true;
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    }
}
static void install_reset_before_homing_motion(void)
{
    install_boot_homing_driver();
    settings.status_report.when_homing = false;
    settings_write_global();
    grbl.on_execute_delay = reset_before_homing_motion;
}
int main(void)
{
    prepare_boot_homing_motion();
    boot_during_init = install_reset_before_homing_motion;
    boot_on_realtime = reset_before_homing_motion;
    boot_program = "$HX\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(reset_sent && boot_wake_calls == 0 && !boot_homing_timer_running);
    CHECK(sys.homed.mask == 0 && plan_get_current_block() == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(boot_motor_pulses[axis] == 0 && boot_motor_position[axis] == 0);
        CHECK(sys.position[axis] == 0);
    }
    CHECK(strstr(engine_output, "[GC:") != NULL);
    CHECK(strstr(engine_output, "GrblHAL ") != NULL);
    return EXIT_SUCCESS;
}
