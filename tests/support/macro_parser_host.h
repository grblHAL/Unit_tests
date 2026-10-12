#pragma once
#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>
static unsigned macro_calls;
static macro_id_t called_macro;
static line_number_t macro_line;
static parameter_words_t macro_words;
static uint32_t macro_repeats;
static float macro_x, macro_y, macro_z;
static int32_t macro_scope;
static status_code_t macro_result = Status_OK;
static status_code_t capture_macro(macro_id_t id, line_number_t line, parameter_words_t words, uint32_t repeats)
{
    macro_calls++;
    called_macro = id;
    macro_line = line;
    macro_words = words;
    macro_repeats = repeats;
    macro_scope = ngc_call_level();
    CHECK(ngc_param_get(24, &macro_x));
    CHECK(ngc_param_get(25, &macro_y));
    CHECK(ngc_param_get(26, &macro_z));
    return macro_result;
}
static inline void prepare_macro_parser(void)
{
    engine_parser_prepare();
    grbl.on_macro_execute = capture_macro;
}
static inline status_code_t macro_block(const char *text)
{
    char block[96];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
