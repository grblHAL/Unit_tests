#pragma once
#include "support/spindle_slot_settings_host.h"
#include "ngc_params.h"
static unsigned modal_rpm_update_calls[3];
static bool modal_spindle_direction[3] = {true, true, true};
static bool modal_secondary_enabled = true;
static void modal_update_rpm(spindle_ptrs_t *spindle, float rpm)
{
    CHECK(spindle->id >= 0 && spindle->id < 3);
    actual_spindle_rpm[spindle->id] = rpm;
    modal_rpm_update_calls[spindle->id]++;
}
static inline void prepare_multi_spindle_modal_program(void)
{
    engine_prepare(); sys.cold_start = true;
    const char *names[] = {"Primary", "Secondary", "Auxiliary"};
    for(unsigned id = 0; id < 3; id++) {
        registered_spindles[id] = (spindle_ptrs_t){.type = SpindleType_Basic,
            .ref_id = (uint8_t)(10 * (id + 1)), .rpm_min = 1000, .rpm_max = 12000,
            .cap = {.direction = modal_spindle_direction[id], .variable = true, .rpm_range_locked = true},
            .config = spindle_configure, .set_state = spindle_output, .get_state = spindle_input,
            .update_rpm = modal_update_rpm};
        CHECK(spindle_register(&registered_spindles[id], names[id]) == (spindle_id_t)id);
    }
    settings.spindle.ref_id = 10;
    secondary_spindle_setting = modal_secondary_enabled ? 2 : 0;
    CHECK(settings_register(&spindle_slot_details));
    CHECK(spindle_select(0));
    if(modal_secondary_enabled) CHECK(spindle_enable(1) == 1);
    coord_system_data_t coordinates = {0};
    for(unsigned id = 0; id < N_CoordinateSystems; id++)
        settings_write_coord_data((coord_system_id_t)id, &coordinates);
    gc_init(false); CHECK(plan_reset()); limits_init();
    hal.control.get_state = spindle_controls; hal.stream.is_connected = spindle_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;
}
static inline void start_two_modal_spindles(void)
{
    CHECK(spindle_program_block("M3S3000$0") == Status_OK);
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
}
