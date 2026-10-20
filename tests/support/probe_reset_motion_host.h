#pragma once
#include "support/probe_motion_host.h"

static unsigned driver_resets, probe_starts;
static bool reset_sent;
static void stop_coolant(coolant_state_t state) { CHECK(state.mask == 0); }
static void reset_driver(void) { driver_resets++; }
static bool observe_probe_start(axes_signals_t axes, float *target, plan_line_data_t *data)
{
    (void)axes; (void)target; (void)data;
    probe_starts++;
    return true;
}
static void reset_after_ten_pulses(sys_state_t state)
{
    execute_foreground(state);
    if(!reset_sent && axis_pulses[X_AXIS] >= 10) {
        reset_sent = true;
        mc_reset();
    }
}
static inline void prepare_probe_reset_motion(void)
{
    prepare_probe_motion();
    hal.coolant.set_state = stop_coolant;
    hal.driver_reset = reset_driver;
    grbl.on_execute_realtime = reset_after_ten_pulses;
    grbl.on_probe_start = observe_probe_start;
}
