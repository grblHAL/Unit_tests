#pragma once
#include "support/boot_tool_position_reset_host.h"
static bool g30_y_aligned, g30_pose_observed;
static void (*g30_original_pulse)(stepper_t *stepper);
static void observe_g30_aligned_pulse(stepper_t *stepper)
{
    if(boot_tool_positioning) {
        CHECK(!(stepper->step_out.mask & X_AXIS_BIT));
        if(g30_y_aligned) CHECK(!(stepper->step_out.mask & Y_AXIS_BIT));
    }
    g30_original_pulse(stepper);
    if(boot_tool_positioning && boot_tool_frame_valid &&
       boot_motor_position[X_AXIS] - boot_tool_home_offset[X_AXIS] == -320 &&
       boot_motor_position[Y_AXIS] - boot_tool_home_offset[Y_AXIS] == -400 &&
       boot_motor_position[Z_AXIS] - boot_tool_home_offset[Z_AXIS] == -40)
        g30_pose_observed = true;
}
static void install_g30_aligned_tool_change(void)
{
    install_boot_tool_positioning();
    g30_original_pulse = hal.stepper.pulse_start;
    CHECK(g30_original_pulse != NULL);
    hal.stepper.pulse_start = observe_g30_aligned_pulse;
}
static inline void run_g30_aligned_tool_change(bool y_aligned)
{
    prepare_boot_streamed_manual_change(true);
    boot_tool_plain_manual = false;
    g30_y_aligned = y_aligned;
    boot_during_init = install_g30_aligned_tool_change;
    char program[128];
    int length = snprintf(program, sizeof(program),
        "$H\nG0X-4Y%dZ-1\nT3M6\n" "\xA3\x81" "G10L2P1Z0\n" "\x81" "$G\n",
        y_aligned ? -5 : -3);
    CHECK(length > 0 && (size_t)length < sizeof(program));
    boot_program = program;
    CHECK(grbl_enter() == 0);
    CHECK(g30_pose_observed && boot_tool_exit_sent && !boot_tool_reset_sent);
    CHECK(!HOST_PARSER_FLAGS.tool_change && gc_state.tool->tool_id == 3);
    CHECK(sys.position[X_AXIS] == -320 && sys.position[Y_AXIS] == (y_aligned ? -400 : -240));
    CHECK(sys.position[Z_AXIS] == -80);
    CHECK(boot_tool_rt_handler == protocol_enqueue_realtime_command);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(sys.position[axis] == boot_motor_position[axis] - boot_tool_home_offset[axis]);
    CHECK(strstr(engine_output, "error:") == NULL);
}
