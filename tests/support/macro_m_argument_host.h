#pragma once
#include "support/macro_parser_host.h"
static float macro_m_argument;
static status_code_t capture_m_argument(macro_id_t id, line_number_t line, parameter_words_t words, uint32_t repeats)
{
    status_code_t result = capture_macro(id, line, words, repeats);
    CHECK(ngc_param_get(13, &macro_m_argument));
    return result;
}
static inline void prepare_macro_m_argument(void)
{
    prepare_macro_parser();
    CHECK(ngc_param_set(13, 99));
    grbl.on_macro_execute = capture_m_argument;
}
