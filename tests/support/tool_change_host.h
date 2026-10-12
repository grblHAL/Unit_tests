#pragma once
#include "support/motion_program_host.h"
#include "tool_change.h"
#include "report.h"
static unsigned select_calls, reset_calls, homing_calls;
static bool selected_next, homing_success;
static tool_data_t *selected_tool;
static axes_signals_t homing_axes;
static atc_status_t no_atc(void) { return ATC_None; }
static bool suspend_tool_stream(bool value) { return value; }
static void original_select(tool_data_t *tool, bool next)
{
    selected_tool = tool;
    selected_next = next;
    select_calls++;
}
static void original_reset(void) { reset_calls++; }
static void original_homing(axes_signals_t axes, bool success)
{
    homing_axes = axes;
    homing_success = success;
    homing_calls++;
}
static control_signals_t tool_control_state(void) { return (control_signals_t){0}; }
static inline void prepare_tool_change(void)
{
    prepare_motion_program();
    hal.tool.atc_get_state = no_atc;
    hal.tool.select = original_select;
    hal.stream.suspend_read = suspend_tool_stream;
    hal.driver_reset = original_reset;
    hal.control.get_state = tool_control_state;
    grbl.on_homing_completed = original_homing;
    settings.tool_change.mode = ToolChange_Manual;
    tc_init();
    CHECK(hal.tool.change != NULL);
}

static enqueue_realtime_command_ptr tool_stream_handler;
static unsigned forwarded_bytes, forwarded_controls, stream_handler_changes;
static uint8_t forwarded_byte;
static control_signals_t forwarded_signals;
static bool original_enqueue(uint8_t byte)
{
    forwarded_byte = byte;
    forwarded_bytes++;
    return byte == CMD_STATUS_REPORT;
}
static enqueue_realtime_command_ptr tool_set_handler(enqueue_realtime_command_ptr handler)
{
    enqueue_realtime_command_ptr previous = tool_stream_handler;
    tool_stream_handler = handler;
    stream_handler_changes++;
    return previous;
}
static void original_control(control_signals_t signals)
{
    forwarded_signals = signals;
    forwarded_controls++;
}
static void tool_coolant_off(coolant_state_t coolant) { CHECK(coolant.value == 0); }
static coolant_state_t tool_coolant_state(void) { return (coolant_state_t){0}; }
static bool tool_stream_connected(void) { return true; }
static inline void start_manual_change(void)
{
    static tool_data_t next = {.tool_id = 3};
    hal.coolant.set_state = tool_coolant_off;
    hal.coolant.get_state = tool_coolant_state;
    hal.stream.is_connected = tool_stream_connected;
    hal.stream.set_enqueue_rt_handler = tool_set_handler;
    tool_stream_handler = original_enqueue;
    hal.control.interrupt_callback = original_control;
    report_init_fns();
    report_init();
    sys.driver_started = true;
    sys.homed.mask |= Z_AXIS_BIT;
    hal.tool.select(&next, true);
    CHECK(hal.tool.change(&gc_state) == Status_OK);
    CHECK(gc_state.tool_change);
    CHECK(state_get() == STATE_TOOL_CHANGE);
}

static unsigned tool_realtime_calls;
static void tool_motion_foreground(sys_state_t state)
{
    CHECK(++tool_realtime_calls < 100000);
    if(state == STATE_CYCLE || state == STATE_HOLD)
        stepper_driver_interrupt_handler();
}
static inline void prepare_tool_change_motion(void)
{
    prepare_tool_change();
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        settings.axis[axis].acceleration = 36000;
    grbl.on_execute_realtime = tool_motion_foreground;
    sys.position[X_AXIS] = physical_position[X_AXIS] = 160;
    sys.position[Y_AXIS] = physical_position[Y_AXIS] = 240;
    sys.position[Z_AXIS] = physical_position[Z_AXIS] = -80;
    sync_position();
}

static inline void resume_manual_change(void)
{
    coord_system_data_t coordinates = {0};
    grbl.on_wco_saved(gc_state.modal.g5x_offset.id, &coordinates);
    grbl.on_toolchange_ack();
    CHECK(tool_stream_handler(CMD_CYCLE_START));
    engine_execute_tasks(STATE_TOOL_CHANGE);
}
