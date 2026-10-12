#pragma once
#include "support/motion_program_host.h"
#include "report.h"
static unsigned homing_calls, limit_enable_calls, completed_calls, reset_calls;
static bool homing_success, stuck_after_contact;
static rt_exec_t interrupt_request;
static void reset_driver(void) { reset_calls++; }
static void coolant_off(coolant_state_t state) { CHECK(state.bits == 0); }
static int32_t switch_position[N_AXIS] = {80, 120, 160};
static bool connected(void) { return true; }
static control_signals_t controls(void) { return (control_signals_t){0}; }
static coolant_state_t coolant_state(void) { return (coolant_state_t){0}; }
static void enable_limits(bool hard, axes_signals_t cycle)
{
    CHECK(!hard);
    (void)cycle;
    limit_enable_calls++;
}
static home_signals_t homing_switches(void)
{
    home_signals_t signals = {0};
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        bool negative = settings.homing.dir_mask.bits & (1u << axis);
        if((stuck_after_contact && axis_pulses[axis] >= (unsigned)switch_position[axis]) ||
           (negative ? physical_position[axis] <= -switch_position[axis] : physical_position[axis] >= switch_position[axis]))
            signals.a.bits |= 1u << axis;
    }
    return signals;
}
static void execute_foreground(sys_state_t state)
{
    CHECK(++homing_calls < 200000);
    if(homing_calls == 20 && interrupt_request)
        system_set_exec_state_flag(interrupt_request);
    if(state == STATE_HOMING || state == STATE_CYCLE)
        stepper_driver_interrupt_handler();
}
static void homing_completed(axes_signals_t cycle, bool success)
{
    CHECK(cycle.bits != 0);
    homing_success = success;
    completed_calls++;
}
static inline void prepare_homing(void)
{
    prepare_motion_program();
    hal.control.get_state = controls;
    hal.driver_reset = reset_driver;
    hal.coolant.set_state = coolant_off;
    hal.coolant.get_state = coolant_state;
    hal.homing.get_state = homing_switches;
    hal.limits.enable = enable_limits;
    hal.stream.is_connected = connected;
    report_init_fns();
    report_init();
    grbl.on_execute_realtime = execute_foreground;
    grbl.on_homing_completed = homing_completed;
    settings.homing.flags.enabled = true;
    settings.homing.flags.single_axis_commands = true;
    settings.homing.cycle[0].bits = 7;
    settings.homing.locate_cycles = 1;
    settings.homing.pulloff = .125f;
    settings.status_report.when_homing = true;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        settings.axis[axis].acceleration = 36000;
        settings.axis[axis].max_travel = -10;
        settings.axis[axis].homing_seek_rate = 100;
        settings.axis[axis].homing_feed_rate = 25;
    }
    limits_set_homing_axes();
    coord_data_t pulloff = {.x = .125f, .y = .125f, .z = .125f};
    limits_homing_pulloff(&pulloff);
}
