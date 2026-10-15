#pragma once
#include "support/spindle_slot_settings_host.h"
static spindle_ptrs_t pair_descriptors[2];
static spindle_pwm_t pair_pwm[2];
static spindle_pwm_settings_t pair_settings[2];
static uint_fast16_t pair_output[2], pair_log[2][128];
static unsigned pair_calls[2];
static uint_fast16_t pair_get_pwm(spindle_ptrs_t *spindle, float rpm)
{ return spindle->context.pwm->compute_value(spindle->context.pwm, rpm, false); }
static void pair_update_pwm(spindle_ptrs_t *spindle, uint_fast16_t pwm)
{
    CHECK(spindle->id >= 0 && spindle->id < 2);
    unsigned id = (unsigned)spindle->id;
    CHECK(pair_calls[id] < 128);
    pair_output[id] = pwm;
    pair_log[id][pair_calls[id]++] = pwm;
}
static void pair_set_state(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    spindle_output(spindle, state, rpm);
    pair_update_pwm(spindle, pair_get_pwm(spindle, state.on ? rpm : 0));
}
static inline void prepare_paired_pwm_program(void)
{
    engine_prepare();
    sys.cold_start = true;
    settings.spindle.on_delay = settings.spindle.off_delay = 500;
    for(unsigned id = 0; id < 2; id++) {
        pair_settings[id] = (spindle_pwm_settings_t){.rpm_min = 0, .rpm_max = 10000,
            .pwm_freq = 1000, .pwm_max_value = 100, .flags = {.pwm_ramped = true}};
        pair_descriptors[id] = (spindle_ptrs_t){.type = SpindleType_PWM,
            .ref_id = (uint8_t)(10 * (id + 1)), .cap = {.direction = true, .rpm_range_locked = true},
            .config = spindle_configure, .get_state = spindle_input, .set_state = pair_set_state,
            .get_pwm = pair_get_pwm, .update_pwm = pair_update_pwm};
        CHECK(spindle_precompute_pwm_values(&pair_descriptors[id], &pair_pwm[id], &pair_settings[id], 1000000));
        spindle_update_caps(&pair_descriptors[id], &pair_pwm[id]);
        CHECK(spindle_register(&pair_descriptors[id], id ? "Secondary PWM" : "Primary PWM") == (spindle_id_t)id);
    }
    settings.spindle.ref_id = 10;
    CHECK(settings_register(&spindle_slot_details));
    CHECK(spindle_select(0));
    CHECK(spindle_enable(1) == 1);
    CHECK(spindle_get(0)->param->option.ramp_up && spindle_get(1)->param->option.ramp_up);
    coord_system_data_t coordinates = {0};
    for(unsigned id = 0; id < N_CoordinateSystems; id++)
        settings_write_coord_data((coord_system_id_t)id, &coordinates);
    gc_init(false);
    CHECK(plan_reset());
    limits_init();
    hal.control.get_state = spindle_controls;
    hal.stream.is_connected = spindle_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;
    pair_calls[0] = pair_calls[1] = 0;
}
