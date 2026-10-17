#pragma once
#include "support/boot_delta_stream_motion_host.h"
#include "kinematics/interface.h"
static bool delta_sender_cancelled;
static unsigned delta_input_cancels;
static bool delta_cancel_after_ack;
static unsigned delta_cancel_ack_count;
static void cancel_delta_input(void) { delta_input_cancels++; }
static void cancel_delta_jog(sys_state_t state);
static void install_cancellable_delta_driver(void)
{
    install_delta_motion_driver();
    hal.stream.cancel_read_buffer = cancel_delta_input;
    grbl.on_execute_delay = cancel_delta_jog;
}
static void cancel_delta_jog(sys_state_t state)
{
    boot_motion_foreground(state);
    if(state == STATE_JOG && !delta_sender_cancelled && boot_motor_pulses[X_AXIS] >= 20 && (!delta_cancel_after_ack || boot_motion_ack_count() > 0)) {
        delta_sender_cancelled = true;
        delta_cancel_ack_count = boot_motion_ack_count();
        if(!delta_cancel_after_ack) CHECK(plan_check_full_buffer());
        CHECK(grbl.on_jog_cancel != NULL);
        CHECK(protocol_enqueue_realtime_command(CMD_JOG_CANCEL));
    }
}
static inline void run_delta_jog_cancel(bool after_ack)
{
    delta_cancel_after_ack = after_ack;
    prepare_boot_delta_stream_motion("$J=G91Z-50F100\n");
    boot_during_init = install_cancellable_delta_driver;
    boot_on_realtime = cancel_delta_jog;
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(delta_sender_cancelled && delta_input_cancels > 0);
    CHECK(after_ack ? delta_cancel_ack_count == 1 : delta_cancel_ack_count == 0);
    CHECK(boot_motor_pulses[X_AXIS] > 0);
    for(unsigned axis = 0; axis < 3; axis++) {
        CHECK(sys.position[axis] == boot_motor_position[axis]);
        CHECK(boot_motor_pulses[axis] == boot_motor_pulses[X_AXIS]);
    }
    CHECK(fabsf(gc_state.position[X_AXIS]) < .03f && fabsf(gc_state.position[Y_AXIS]) < .03f);
    mpos_t joints;
    coord_data_t actual;
    memcpy(joints.values, sys.position, sizeof(joints.values));
    kinematics.transform_steps_to_cartesian(&actual, &joints);
    CHECK(actual.z < delta_zero_angle_height() - 1);
    CHECK(actual.z > delta_zero_angle_height() - 50);
    if(!after_ack) CHECK(actual.z > delta_zero_angle_height() - 49);
    CHECK(fabsf(gc_state.position[Z_AXIS] - actual.z) < .03f);
    CHECK(gc_state.position[Z_AXIS] < delta_zero_angle_height());
    CHECK(gc_state.position[Z_AXIS] > delta_zero_angle_height() - 50);
}

