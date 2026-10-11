#pragma once
#include "support/settings_host.h"
#include "spindle_control.h"
static spindle_ptrs_t primary_pwm_driver;
static bool primary_pwm_config(spindle_ptrs_t *spindle) { CHECK(spindle->id == 0); return true; }
static void primary_pwm_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm) { (void)spindle; (void)state; (void)rpm; }
static spindle_state_t primary_pwm_input(spindle_ptrs_t *spindle) { (void)spindle; return (spindle_state_t){0}; }
static inline void prepare_primary_pwm_settings(bool can_invert)
{
    engine_prepare();
    sys.cold_start = true;
    primary_pwm_driver = (spindle_ptrs_t){.type = SpindleType_PWM, .ref_id = 10,
        .rpm_min = 1000, .rpm_max = 12000,
        .cap = {.enable = true, .direction = true, .variable = true, .laser = true,
                .pwm_invert = can_invert, .gpio_controlled = true, .rpm_range_locked = true},
        .config = primary_pwm_config, .set_state = primary_pwm_output, .get_state = primary_pwm_input};
    CHECK(spindle_register(&primary_pwm_driver, "PWM") == 0);
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++)
        settings_write_coord_data((coord_system_id_t)i, &coordinates);
    CHECK(spindle_select(0));
    gc_init(false);
    grbl.on_settings_changed = changed_settings;
}
