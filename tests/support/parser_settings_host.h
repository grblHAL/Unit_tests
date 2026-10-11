#pragma once
#include "support/engine_host.h"
#include "check.h"
#include "spindle_control.h"
static unsigned parser_settings_calls;
static settings_changed_flags_t parser_changed_flags;
static void parser_settings_changed(settings_t *current, settings_changed_flags_t changed)
{
    CHECK(current == &settings);
    parser_settings_calls++;
    parser_changed_flags = changed;
}
static inline void prepare_parser_settings(void)
{
    engine_prepare();
    grbl.on_settings_changed = parser_settings_changed;
    sys.cold_start = true;
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++)
        settings_write_coord_data((coord_system_id_t)i, &coordinates);
    CHECK(spindle_select(0));
    gc_init(false);
}
