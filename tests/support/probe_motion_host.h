#pragma once
#include "support/motion_program_host.h"
#include "probe.h"
#include "report.h"
static int32_t contact_steps = 40;
static bool away_contact;
static unsigned realtime_calls, completed_calls;
static bool connected(void) { return true; }
static control_signals_t controls(void) { return (control_signals_t){0}; }
static bool sensor_input(void *context)
{
    CHECK(context == &contact_steps);
    bool contact = sys.position[X_AXIS] >= contact_steps;
    return away_contact ? !contact : contact;
}
static void execute_foreground(sys_state_t state)
{
    CHECK(++realtime_calls < 100000);
    if(state == STATE_CYCLE || state == STATE_HOLD)
        stepper_driver_interrupt_handler();
}
static void completed(void)
{
    completed_calls++;
    CHECK(sys.probing_state == Probing_Off);
    CHECK(!hal.probe.get_state().is_probing);
}
static inline void prepare_probe_motion(void)
{
    prepare_motion_program();
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        settings.axis[axis].acceleration = 36000;
    hal.control.get_state = controls;
    hal.stream.is_connected = connected;
    report_init_fns();
    report_init();
    grbl.on_execute_realtime = execute_foreground;
    grbl.on_probe_completed = completed;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &contact_steps, sensor_input));
}
static inline gc_probe_t probe_to_one_mm(gc_parser_flags_t flags)
{
    float target[N_AXIS] = {1, 0, 0};
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    data.condition.target_validated = data.condition.target_valid = true;
    return mc_probe_cycle(target, &data, flags);
}
