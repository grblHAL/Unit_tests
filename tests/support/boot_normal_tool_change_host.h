#pragma once
#include "support/boot_stream_motion_host.h"
#include "stream.h"
static stream_rx_buffer_t normal_rx;
static enqueue_realtime_command_ptr normal_rt = protocol_enqueue_realtime_command;
static unsigned pending_polls, acknowledged_polls;
static bool acknowledged, resumed, normal_change_with_door;
static unsigned open_door_polls, closed_door_polls;
static bool door_closed, door_resume_sent;
static enqueue_realtime_command_ptr set_normal_rt(enqueue_realtime_command_ptr handler)
{
    enqueue_realtime_command_ptr previous = normal_rt;
    if(handler) boot_receive_realtime = normal_rt = handler;
    return previous;
}
static bool suspend_normal_rx(bool suspend) { return stream_rx_suspend(&normal_rx, suspend); }
static int32_t read_normal_sender(void)
{
    const char *next_move = strstr(boot_program, "G1X2");
    CHECK(next_move != NULL);
    if(boot_reads == (unsigned)(next_move - boot_program) &&
       (!resumed || HOST_PARSER_FLAGS.tool_change || state_get() != STATE_IDLE))
        return SERIAL_NO_DATA;
    return read_char();
}
static void service_normal_change(sys_state_t state)
{
    boot_motion_foreground(state);
    if(state == STATE_TOOL_CHANGE && !resumed) {
        CHECK(settings.tool_change.mode == ToolChange_Disabled && hal.tool.change == NULL);
        CHECK(HOST_PARSER_FLAGS.tool_change && gc_state.tool->tool_id == 0);
        CHECK(gc_state.tool_pending == 3 && plan_get_current_block() == NULL);
        CHECK(boot_motor_position[X_AXIS] == 80 && boot_motor_pulses[X_AXIS] == 80);
        CHECK(sys.position[X_AXIS] == 80);
        if(!acknowledged) {
            CHECK(stream_is_rx_suspended() == StreamSuspend_Pending);
            if(++pending_polls == 4) {
                if(normal_change_with_door) {
                    boot_control_signals.safety_door_ajar = true;
                    hal.control.interrupt_callback((control_signals_t){.safety_door_ajar = true});
                }
                CHECK(normal_rt(CMD_TOOL_ACK));
                CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
                acknowledged = true;
            }
        } else if(++acknowledged_polls == 4) {
            CHECK(normal_rt(CMD_CYCLE_START));
            resumed = true;
        }
    }
    if(normal_change_with_door && state == STATE_SAFETY_DOOR && !door_resume_sent) {
        CHECK(resumed && !HOST_PARSER_FLAGS.tool_change && gc_state.tool->tool_id == 3);
        CHECK(stream_is_rx_suspended() == StreamSuspend_Off);
        CHECK(sys.position[X_AXIS] == 80 && boot_motor_position[X_AXIS] == 80 && boot_motor_pulses[X_AXIS] == 80);
        if(!door_closed) {
            CHECK(boot_control_signals.safety_door_ajar);
            if(++open_door_polls == 4) {
                boot_control_signals.safety_door_ajar = false;
                hal.control.interrupt_callback((control_signals_t){.safety_door_ajar = true, .deasserted = true});
                door_closed = true;
            }
        } else {
            CHECK(!boot_control_signals.safety_door_ajar);
            if(++closed_door_polls == 4) {
                CHECK(normal_rt(CMD_CYCLE_START));
                door_resume_sent = true;
            }
        }
    }
}
static void install_normal_change_driver(void)
{
    install_boot_motion_driver();
    hal.signals_cap.safety_door_ajar = normal_change_with_door;
    hal.stream.suspend_read = suspend_normal_rx;
    hal.stream.set_enqueue_rt_handler = set_normal_rt;
    hal.stream.read = read_normal_sender;
    grbl.on_execute_delay = service_normal_change;
}
static inline void run_normal_m6_pause(bool with_door)
{
    normal_change_with_door = with_door;
    prepare_boot_stream_motion("$341=0\nG0X1\nT3M6\nG1X2F100\n$G\n");
    boot_during_init = install_normal_change_driver;
    boot_on_realtime = service_normal_change;
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(acknowledged && resumed && pending_polls == 4 && acknowledged_polls == 4);
    CHECK(gc_state.tool->tool_id == 3 && !HOST_PARSER_FLAGS.tool_change);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && normal_rt == protocol_enqueue_realtime_command);
    CHECK(boot_motor_position[X_AXIS] == 160 && sys.position[X_AXIS] == 160);
    CHECK(boot_motor_pulses[X_AXIS] == 160 && boot_motor_pulses[Y_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
    CHECK(door_closed == with_door && door_resume_sent == with_door);
    CHECK(open_door_polls == (with_door ? 4u : 0u) && closed_door_polls == (with_door ? 4u : 0u));
}
