#pragma once
#include "support/multi_spindle_host.h"
static spindle_pwm_t triple_pwm[3];
static spindle_pwm_settings_t triple_settings[3];
static uint_fast16_t triple_output[3];
static unsigned triple_calls[3];
static uint8_t triple_slots[] = {2, 3};
static const setting_detail_t triple_slot_settings[] = {
    {.id = (setting_id_t)(Setting_SpindleEnable0 + 1), .group = Group_Spindle,
     .name = "Second spindle", .type = Setting_NonCore, .datatype = Format_Int8, .value = &triple_slots[0]},
    {.id = (setting_id_t)(Setting_SpindleEnable0 + 2), .group = Group_Spindle,
     .name = "Third spindle", .type = Setting_NonCore, .datatype = Format_Int8, .value = &triple_slots[1]}
};
static void triple_persistence(void) {}
static setting_details_t triple_slot_details = {
    .n_settings = 2, .settings = triple_slot_settings,
    .load = triple_persistence, .restore = triple_persistence, .save = triple_persistence
};
static uint_fast16_t triple_get_pwm(spindle_ptrs_t *spindle, float rpm)
{ return spindle->context.pwm->compute_value(spindle->context.pwm, rpm, false); }
static void triple_update_pwm(spindle_ptrs_t *spindle, uint_fast16_t pwm)
{
    CHECK(spindle->id >= 0 && spindle->id < 3);
    triple_output[spindle->id] = pwm;
    triple_calls[spindle->id]++;
}
static void triple_set_state(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    spindle_output(spindle, state, rpm);
    triple_update_pwm(spindle, triple_get_pwm(spindle, state.on ? rpm : 0));
}
static inline void prepare_three_pwm_program(void)
{
    engine_prepare();
    sys.cold_start = true;
    settings.mode = Mode_Standard;
    settings.spindle.on_delay = settings.spindle.off_delay = 500;
    const char *names[] = {"Primary PWM", "Second PWM", "Third PWM"};
    for(unsigned id = 0; id < 3; id++) {
        triple_settings[id] = (spindle_pwm_settings_t){.rpm_min = 0, .rpm_max = 10000,
            .pwm_freq = 1000, .pwm_max_value = 100, .flags = {.pwm_ramped = true}};
        registered_spindles[id] = (spindle_ptrs_t){.type = SpindleType_PWM,
            .ref_id = (uint8_t)(10 * (id + 1)), .cap = {.direction = true, .rpm_range_locked = true},
            .config = spindle_configure, .get_state = spindle_input, .set_state = triple_set_state,
            .get_pwm = triple_get_pwm, .update_pwm = triple_update_pwm};
        CHECK(spindle_precompute_pwm_values(&registered_spindles[id], &triple_pwm[id], &triple_settings[id], 1000000));
        spindle_update_caps(&registered_spindles[id], &triple_pwm[id]);
        CHECK(spindle_register(&registered_spindles[id], names[id]) == (spindle_id_t)id);
    }
    settings.spindle.ref_id = 10;
    CHECK(settings_register(&triple_slot_details));
    CHECK(spindle_select(0));
    CHECK(spindle_enable(1) == 1 && spindle_enable(2) == 2);
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
}
