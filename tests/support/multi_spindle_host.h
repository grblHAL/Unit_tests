#pragma once
#include "support/engine_host.h"
#include "spindle_control.h"
#include "state_machine.h"
#include "protocol.h"
#include "report.h"
#include "check.h"
#include <string.h>
static spindle_ptrs_t registered_spindles[3];
static spindle_state_t actual_spindle_states[3];
static float actual_spindle_rpm[3];
static unsigned spindle_config_calls[3], spindle_output_calls[3];
static bool spindle_configure(spindle_ptrs_t *spindle)
{
    CHECK(spindle->id >= 0 && spindle->id < 3);
    spindle_config_calls[spindle->id]++;
    return true;
}
static void spindle_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle->id >= 0 && spindle->id < 3);
    actual_spindle_states[spindle->id] = state;
    actual_spindle_rpm[spindle->id] = rpm;
    spindle_output_calls[spindle->id]++;
}
static spindle_state_t spindle_input(spindle_ptrs_t *spindle)
{
    CHECK(spindle->id >= 0 && spindle->id < 3);
    return actual_spindle_states[spindle->id];
}
static inline void prepare_multi_spindle(void)
{
    engine_prepare();
    sys.cold_start = true;
    const char *names[] = {"primary", "secondary", "auxiliary"};
    for(unsigned i = 0; i < 3; i++) {
        registered_spindles[i] = (spindle_ptrs_t){.type = SpindleType_Basic,
            .ref_id = (uint8_t)(10 * (i + 1)), .rpm_min = 1000, .rpm_max = 12000,
            .cap = {.direction = true, .rpm_range_locked = true},
            .config = spindle_configure, .set_state = spindle_output, .get_state = spindle_input};
        CHECK(spindle_register(&registered_spindles[i], names[i]) == (spindle_id_t)i);
    }
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++)
        settings_write_coord_data((coord_system_id_t)i, &coordinates);
    CHECK(spindle_select(0));
    gc_init(false);
    CHECK(plan_reset());
    limits_init();
    grbl.on_execute_realtime = protocol_execute_noop;
    state_set(STATE_CHECK_MODE);
}

static control_signals_t spindle_controls(void) { return (control_signals_t){0}; }
static bool spindle_connected(void) { return true; }
static inline void prepare_multi_spindle_program(void)
{
    prepare_multi_spindle();
    hal.control.get_state = spindle_controls;
    hal.stream.is_connected = spindle_connected;
    report_init_fns();
    report_init();
    state_set(STATE_IDLE);
}
static inline status_code_t spindle_program_block(const char *text)
{
    char block[96];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
