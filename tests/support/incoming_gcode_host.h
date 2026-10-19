#pragma once
#include "support/engine_host.h"
#include "protocol.h"
#include "state_machine.h"
#include "report.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>
static inline control_signals_t incoming_controls(void) { return (control_signals_t){0}; }
static inline bool incoming_connected(void) { return true; }
static inline coord_system_data_t read_saved_coordinate(coord_system_id_t id)
{
    coord_system_data_t data;
    CHECK(settings_read_coord_data(id, &data));
    return data;
}
static inline macro_id_t active_modal_macro(void)
{ return gc_state.g66_args ? (macro_id_t)gc_state.g66_args->values.p : 0; }
static inline float incoming_macro_argument(uint16_t id)
{ float value; CHECK(ngc_param_get(id, &value)); return value; }
static inline status_code_t incoming_block(const char *text)
{ char block[160]; CHECK(strlen(text) < sizeof(block)); strcpy(block, text); return gc_execute_block(block); }
static inline void prepare_incoming_parser(void)
{ engine_parser_prepare(); settings.arc_tolerance = 0.002f; }
