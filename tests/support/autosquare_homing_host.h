#pragma once
#include "support/homing_host.h"
static uint_fast8_t squared_axis_index = X_AXIS;
static int32_t squared_primary, squared_secondary;
static int32_t primary_switch_steps = 80, secondary_switch_steps = 120;
static bool primary_disabled, secondary_disabled;
static unsigned squared_disable_calls, primary_stops, secondary_stops;
static axes_signals_t squared_axis(bool auto_squared)
{
    CHECK(auto_squared);
    return (axes_signals_t){.mask = (1u << squared_axis_index)};
}
static void disable_squared_motor(axes_signals_t axes, squaring_mode_t mode)
{
    CHECK(axes.mask == 0 || axes.mask == (1u << squared_axis_index));
    squared_disable_calls++;
    primary_disabled = (axes.mask & (1u << squared_axis_index)) && mode != SquaringMode_B;
    secondary_disabled = (axes.mask & (1u << squared_axis_index)) && mode != SquaringMode_A;
    if(primary_disabled) primary_stops++;
    if(secondary_disabled) secondary_stops++;
}
static void squared_pulse(stepper_t *stepper)
{
    if(stepper->step_out.mask & (1u << squared_axis_index)) {
        int delta = stepper->dir_out.mask & (1u << squared_axis_index) ? -1 : 1;
        if(!primary_disabled) squared_primary += delta;
        if(!secondary_disabled) squared_secondary += delta;
    }
    pulse_driver(stepper);
}
static home_signals_t squared_switches(void)
{
    bool negative = (settings.homing.dir_mask.value & (1u << squared_axis_index)) != 0;
    bool primary = negative ? squared_primary <= -primary_switch_steps : squared_primary >= primary_switch_steps;
    bool secondary = negative ? squared_secondary <= -secondary_switch_steps : squared_secondary >= secondary_switch_steps;
    return (home_signals_t){.a = {.mask = primary ? (1u << squared_axis_index) : 0},
                            .b = {.mask = secondary ? (1u << squared_axis_index) : 0}};
}
static inline void prepare_autosquare_homing(void)
{
    prepare_homing();
    hal.stepper.get_ganged = squared_axis;
    hal.stepper.disable_motors = disable_squared_motor;
    hal.stepper.pulse_start = squared_pulse;
    hal.homing.get_state = squared_switches;
    settings.homing.dual_axis.fail_length_percent = 20;
    settings.homing.dual_axis.fail_distance_min = 2;
    settings.homing.dual_axis.fail_distance_max = 5;
}
