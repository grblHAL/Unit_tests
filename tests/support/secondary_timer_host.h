#pragma once
#include "support/secondary_stepper_host.h"
static int timer_token;
static bool timer_claim_fails;
static unsigned timer_claims, timer_starts, timer_stops;
static uint32_t timer_period;
static timer_cfg_t captured_timer;
static hal_timer_t claim_motor_timer(timer_cap_t cap, uint32_t timebase)
{
    CHECK(!cap.periodic && timebase == 1000);
    timer_claims++;
    return timer_claim_fails ? NULL : &timer_token;
}
static bool configure_motor_timer(hal_timer_t timer, timer_cfg_t *cfg)
{
    CHECK(timer == &timer_token && cfg->timeout_callback != NULL);
    captured_timer = *cfg;
    return true;
}
static bool start_motor_timer(hal_timer_t timer, uint32_t period)
{
    CHECK(timer == &timer_token && period > 0);
    timer_period = period;
    timer_starts++;
    return true;
}
static bool stop_motor_timer(hal_timer_t timer)
{
    CHECK(timer == &timer_token);
    timer_stops++;
    return true;
}
static inline st2_motor_t *prepare_timer_motor(void)
{
    engine_prepare();
    settings.axis[X_AXIS].acceleration = 36000;
    hal.get_micros = motor_micros;
    hal.stepper.output_step = capture_motor_step;
    grbl.on_settings_changed = changed_motor_settings;
    hal.timer.claim = claim_motor_timer;
    hal.timer.configure = configure_motor_timer;
    hal.timer.start = start_motor_timer;
    hal.timer.stop = stop_motor_timer;
    st2_motor_t *motor = st2_motor_init(X_AXIS, false);
    CHECK(motor != NULL);
    return motor;
}
static inline void fire_motor_timer(void)
{
    CHECK(captured_timer.context != NULL);
    captured_timer.timeout_callback(captured_timer.context);
}
