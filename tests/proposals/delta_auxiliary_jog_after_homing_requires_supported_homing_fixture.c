/* Unregistered: four-axis delta homing fails before the jog; see TODO. */
#include "support/boot_delta_homing_host.h"
#include "check.h"

static int32_t homed_position[N_AXIS];
static unsigned homed_pulses[N_AXIS];
static void snapshot_home(axes_signals_t cycle, bool success)
{
    observe_boot_delta_home(cycle, success);
    memcpy(homed_position, sys.position, sizeof(homed_position));
    memcpy(homed_pulses, boot_motor_pulses, sizeof(homed_pulses));
}
static void service_auxiliary_jog(sys_state_t state)
{
    boot_homing_foreground(state);
    if(boot_delta_home_events == 1 && boot_reads == strlen(boot_program) &&
       boot_motion_ack_count() == 3 && state == STATE_IDLE && !plan_get_current_block()) {
        boot_delta_home_finished = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
    }
}
static void install_auxiliary_homing(void)
{
    install_delta_homing_driver();
    grbl.on_homing_completed = snapshot_home;
    grbl.on_execute_delay = service_auxiliary_jog;
}
int main(void)
{
    prepare_boot_delta_homing(false);
    boot_during_init = install_auxiliary_homing;
    boot_on_realtime = service_auxiliary_jog;
    boot_program = "$H\n$20=1\n$J=G91A999F100\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_delta_home_finished && boot_delta_home_events == 1);
    CHECK(sys.homed.mask & A_AXIS_BIT);
    CHECK(sys.soft_limits.mask & A_AXIS_BIT);
    char expected[32];
    snprintf(expected, sizeof(expected), "error:%u", (unsigned)Status_TravelExceeded);
    CHECK(strstr(engine_output, expected) != NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == homed_position[axis]);
        CHECK(boot_motor_pulses[axis] == homed_pulses[axis]);
    }
    return EXIT_SUCCESS;
}
