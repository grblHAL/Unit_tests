#pragma once
#include "support/engine_host.h"
#include "stepper2.h"
#include "check.h"
static uint64_t motor_clock;
static unsigned motor_pulses, stopped_calls, settings_calls;
static void *stopped_motor;
static uint64_t motor_micros(void) { return motor_clock; }
static void capture_motor_step(axes_signals_t axes, axes_signals_t direction)
{
    CHECK(axes.mask == X_AXIS_BIT || axes.mask == Y_AXIS_BIT);
    CHECK(direction.mask == 0 || direction.mask == axes.mask);
    motor_pulses++;
}
static void changed_motor_settings(settings_t *current, settings_changed_flags_t changed)
{
    CHECK(current == &settings);
    (void)changed;
    settings_calls++;
}
static inline void motor_stopped(void *data) { stopped_motor = data; stopped_calls++; }
static inline st2_motor_t *prepare_secondary_motor(void)
{
    engine_prepare();
    for(unsigned axis = 0; axis < N_AXIS; axis++) settings.axis[axis].acceleration = 36000;
    hal.get_micros = motor_micros;
    hal.stepper.output_step = capture_motor_step;
    grbl.on_settings_changed = changed_motor_settings;
    st2_motor_t *motor = st2_motor_init(X_AXIS, false);
    CHECK(motor != NULL);
    return motor;
}
static inline void tick_motor(st2_motor_t *motor)
{
    motor_clock += 1000000;
    st2_motor_run(motor);
}
static inline void cruise_motor(st2_motor_t *motor)
{
    for(unsigned i = 0; i < 1000 && !st2_motor_cruising(motor); i++) tick_motor(motor);
    CHECK(st2_motor_cruising(motor));
}
static inline void finish_motor(st2_motor_t *motor)
{
    for(unsigned i = 0; i < 1000 && st2_motor_running(motor); i++) tick_motor(motor);
    CHECK(!st2_motor_running(motor));
}
