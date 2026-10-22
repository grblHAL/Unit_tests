#pragma once
#include "support/boot_homing_motion_host.h"
#include "stream.h"
static bool boot_tool_positioning, boot_tool_reset_sent;
static unsigned boot_tool_resets;
static unsigned boot_tool_resets_before_change;
static bool boot_tool_restart_observed;
static unsigned boot_tool_resets_after_restart;
static bool boot_tool_frame_valid;
static int32_t boot_tool_home_offset[N_AXIS];
static bool boot_reset_ordinary_motion;
static int32_t boot_tool_reset_z;
static bool boot_tool_exit_sent;
static bool boot_tool_skip_reset, boot_tool_plain_manual;
static bool boot_tool_no_return;
static bool boot_tool_gate_sender;
static int32_t boot_tool_entry_position[N_AXIS];
static stream_rx_buffer_t boot_tool_receive_buffer;
static int32_t boot_tool_read(void)
{
    if(boot_tool_gate_sender) {
        const char *ack = strchr(boot_program, CMD_TOOL_ACK);
        const char *query = strstr(boot_program, "$G");
        if(ack && boot_reads == (unsigned)(ack - boot_program) &&
           (state_get() != STATE_TOOL_CHANGE || !HOST_PARSER_FLAGS.tool_change))
            return SERIAL_NO_DATA;
        if(query && boot_reads == (unsigned)(query - boot_program) &&
           (HOST_PARSER_FLAGS.tool_change || state_get() != STATE_IDLE || plan_get_current_block() != NULL))
            return SERIAL_NO_DATA;
        if(!boot_tool_plain_manual && strncmp(boot_program + boot_reads, "G10", 3) == 0 &&
           (state_get() != STATE_TOOL_CHANGE || plan_get_current_block() != NULL ||
            sys.position[X_AXIS] != boot_tool_entry_position[X_AXIS] ||
            sys.position[Y_AXIS] != boot_tool_entry_position[Y_AXIS]))
            return SERIAL_NO_DATA;
    }
    return read_char();
}
static tool_change_ptr boot_original_tool_change;
static void (*boot_previous_driver_reset)(void);
static enqueue_realtime_command_ptr boot_tool_rt_handler = protocol_enqueue_realtime_command;
static enqueue_realtime_command_ptr boot_tool_set_rt(enqueue_realtime_command_ptr handler)
{
    enqueue_realtime_command_ptr previous = boot_tool_rt_handler;
    if(handler) boot_receive_realtime = boot_tool_rt_handler = handler;
    return previous;
}
static bool boot_tool_suspend(bool suspend) { return stream_rx_suspend(&boot_tool_receive_buffer, suspend); }
static void boot_tool_reset_driver(void)
{
    boot_tool_resets++;
    boot_previous_driver_reset();
}
static status_code_t boot_track_tool_change(parser_state_t *parser)
{
    boot_tool_positioning = true;
    memcpy(boot_tool_entry_position, sys.position, sizeof(boot_tool_entry_position));
    boot_tool_resets_before_change = boot_tool_resets;
    return boot_original_tool_change(parser);
}
static void boot_wrap_tool_change(void)
{
    if(!boot_tool_frame_valid && (sys.homed.mask & AXES_BITMASK) == AXES_BITMASK) {
        for(unsigned axis = 0; axis < N_AXIS; axis++)
            boot_tool_home_offset[axis] = boot_motor_position[axis] - sys.position[axis];
        boot_tool_frame_valid = true;
    }
    const char *welcome = strstr(engine_output, "GrblHAL");
    bool restarted = welcome && strstr(welcome + 1, "GrblHAL") != NULL;
    if(boot_tool_reset_sent && restarted && !sys.abort && !boot_tool_restart_observed) {
        boot_tool_restart_observed = true;
        boot_tool_resets_after_restart = boot_tool_resets;
    }
    if(hal.tool.change && hal.tool.change != boot_track_tool_change) {
        boot_original_tool_change = hal.tool.change;
        hal.tool.change = boot_track_tool_change;
    }
}
static void boot_reset_during_tool_retract(sys_state_t state)
{
    boot_homing_foreground(state);
    if(boot_tool_gate_sender && state == STATE_TOOL_CHANGE &&
       stream_is_rx_suspended() == StreamSuspend_Pending &&
       (uint8_t)boot_program[boot_reads] == CMD_TOOL_ACK) {
        boot_reads++;
        CHECK(boot_tool_rt_handler(CMD_TOOL_ACK));
    }
    int32_t z = boot_motor_position[Z_AXIS] - boot_tool_home_offset[Z_AXIS];
    if(!boot_tool_skip_reset && (boot_tool_positioning || (boot_reset_ordinary_motion && state == STATE_CYCLE)) && boot_tool_frame_valid && !boot_tool_reset_sent && z >= -40 && z < 0) {
        boot_tool_reset_sent = true;
        boot_tool_reset_z = z;
        boot_tool_resets_before_change = boot_tool_resets;
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    }
    if((boot_tool_restart_observed || (boot_tool_skip_reset && !HOST_PARSER_FLAGS.tool_change && state == STATE_IDLE)) && !boot_tool_exit_sent &&
       boot_reads == strlen(boot_program) && strstr(engine_output, "[GC:") != NULL) {
        boot_tool_exit_sent = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
    }
}
static void install_boot_tool_positioning(void)
{
    install_boot_homing_driver();
    settings.tool_change.mode = ToolChange_Manual;
    settings.flags.tool_change_at_g30 = !boot_tool_plain_manual;
    settings.flags.no_restore_position_after_M6 = boot_tool_no_return;
    settings_write_global();
    coord_system_data_t g30 = {.coord = {.x = -4, .y = -5, .z = -0.5f}};
    settings_write_coord_data(CoordinateSystem_G30, &g30);
    hal.stream.suspend_read = boot_tool_suspend;
    hal.stream.read = boot_tool_read;
    hal.stream.set_enqueue_rt_handler = boot_tool_set_rt;
    boot_previous_driver_reset = hal.driver_reset;
    hal.driver_reset = boot_tool_reset_driver;
    grbl.on_execute_delay = boot_reset_during_tool_retract;
}
static inline void prepare_boot_tool_position_reset(void)
{
    boot_homing_required = true;
    boot_during_init = install_boot_tool_positioning;
    boot_on_realtime = boot_reset_during_tool_retract;
    boot_before_read = boot_wrap_tool_change;
    boot_read_limit = 100000;
    boot_observe_fault_loop = true;
    boot_program = "$H\nG0X-2Y-3Z-1\nT3M6\n$G\n";
}
static inline void prepare_boot_streamed_manual_change(bool restore_position)
{
    prepare_boot_tool_position_reset();
    boot_tool_skip_reset = boot_tool_plain_manual = boot_tool_gate_sender = true;
    boot_tool_no_return = !restore_position;
    boot_program = "$H\nG0X-2Y-3Z-1\nT3M6\n" "\xA3" "G10L2P1Z0\n" "\x81" "$G\n";
}
