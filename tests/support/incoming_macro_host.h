#pragma once
#include "support/incoming_gcode_host.h"
static unsigned macro_calls;
static macro_id_t incoming_called_macro;
static float incoming_arguments[33];
static status_code_t incoming_capture_macro(macro_id_t id, line_number_t line,
    parameter_words_t words, uint32_t repeats)
{
    (void)line; (void)words; (void)repeats;
    macro_calls++; incoming_called_macro = id;
    for(unsigned i = 0; i < 33; i++) CHECK(ngc_param_get(i + 1, &incoming_arguments[i]));
    return Status_OK;
}
static inline void prepare_incoming_macro(void)
{ prepare_incoming_parser(); grbl.on_macro_execute = incoming_capture_macro; }
