#pragma once
#include "support/secondary_stepper_host.h"
static unsigned spindle_motor_pulses;
static axes_signals_t spindle_motor_axis;
static void spindle_motor_step(axes_signals_t axes, axes_signals_t direction)
{
    CHECK(axes.mask == (1U << A_AXIS));
    CHECK(direction.mask == 0 || direction.mask == axes.mask);
    spindle_motor_axis = axes;
    spindle_motor_pulses++;
}
static const char *previous_axis_unit(setting_id_t id, uint_fast8_t axis)
{
    (void)id; (void)axis;
    return "original unit";
}
static const char *previous_axis_description(setting_id_t id)
{
    (void)id;
    return "original description";
}
static inline st2_motor_t *prepare_spindle_motor(void)
{
    engine_prepare();
    hal.get_micros = motor_micros;
    hal.stepper.output_step = spindle_motor_step;
    grbl.on_settings_changed = changed_motor_settings;
    grbl.on_set_axis_setting_unit = previous_axis_unit;
    grbl.on_setting_get_description = previous_axis_description;
    settings.axis[A_AXIS].steps_per_mm = 200;
    settings.axis[A_AXIS].acceleration = 36000;
    st2_motor_t *motor = st2_motor_init(0, true);
    CHECK(motor != NULL);
    return motor;
}
