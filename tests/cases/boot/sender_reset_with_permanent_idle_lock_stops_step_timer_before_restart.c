#include "support/boot_tool_position_reset_host.h"

static on_reset_ptr previous_reset;
static bool motion_stop_observed;
static unsigned stopped_pulses[N_AXIS];
static int32_t stopped_position[N_AXIS];

static void observe_sender_reset(void)
{
    if(state_get() == STATE_CYCLE && !motion_stop_observed) {
        CHECK(settings.steppers.idle_lock_time == 255);
        CHECK(!boot_homing_timer_running && sys.rt_exec_alarm == Alarm_AbortCycle);
        CHECK(boot_enabled_axes.mask == AXES_BITMASK);
        CHECK(sys.steppers_deenergize);
        memcpy(stopped_pulses, boot_motor_pulses, sizeof(stopped_pulses));
        memcpy(stopped_position, boot_motor_position, sizeof(stopped_position));
        motion_stop_observed = true;
    }
    if(previous_reset) previous_reset();
}
static void install_idle_locked_motion(void)
{
    install_boot_tool_positioning();
    previous_reset = grbl.on_reset;
    grbl.on_reset = observe_sender_reset;
}
int main(void)
{
    prepare_boot_tool_position_reset();
    boot_idle_lock_time = 255;
    boot_reset_ordinary_motion = true;
    boot_during_init = install_idle_locked_motion;
    boot_program = "$H\nG0X-2Y-3Z-1\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(motion_stop_observed && boot_tool_reset_sent && boot_tool_restart_observed);
    CHECK(!boot_homing_timer_running && !boot_tool_positioning);
    CHECK(settings.steppers.idle_lock_time == 255);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(boot_motor_pulses[axis] == stopped_pulses[axis]);
        CHECK(boot_motor_position[axis] == stopped_position[axis]);
        CHECK(sys.position[axis] == boot_motor_position[axis] - boot_tool_home_offset[axis]);
    }
    CHECK(plan_get_current_block() == NULL);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
