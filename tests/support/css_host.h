#pragma once
#include "support/engine_host.h"
#include "spindle_control.h"
#include "state_machine.h"
#include "check.h"
#include <string.h>
static spindle_ptrs_t css_driver;
static inline void css_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm) { (void)spindle; (void)rpm; CHECK(!state.on); }
static inline spindle_state_t css_input(spindle_ptrs_t *spindle) { (void)spindle; return (spindle_state_t){0}; }
static inline void prepare_css_parser(bool variable)
{
    engine_prepare();
    sys.cold_start = true;
    settings.mode = Mode_Lathe;
    css_driver = (spindle_ptrs_t){ .type = SpindleType_Basic, .ref_id = 1,
        .rpm_min = 1000, .rpm_max = 10000,
        .cap = { .variable = variable, .direction = true, .rpm_range_locked = true },
        .set_state = css_output, .get_state = css_input };
    CHECK(spindle_register(&css_driver, "variable") == 0);
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    CHECK(spindle_select(0));
    gc_init(false);
    CHECK(plan_reset());
    limits_init();
    state_set(STATE_CHECK_MODE);
}
static inline status_code_t css_block(const char *text) { char block[64]; CHECK(strlen(text) < sizeof(block)); strcpy(block, text); return gc_execute_block(block); }
