#pragma once
#include "support/engine_host.h"
#include "ngc_expr.h"
#include "check.h"
#include <string.h>
static inline float evaluate_complete_expression(const char *source)
{
    char text[96]; CHECK(strlen(source) < sizeof(text)); strcpy(text, source);
    uint_fast8_t pos = 0; float value = 0;
    CHECK(ngc_eval_expression(text, &pos, &value) == Status_OK);
    CHECK(pos == strlen(text)); return value;
}
static inline void reject_expression(const char *source, status_code_t expected)
{
    char text[96]; CHECK(strlen(source) < sizeof(text)); strcpy(text, source);
    uint_fast8_t pos = 0; float value = 0;
    CHECK(ngc_eval_expression(text, &pos, &value) == expected);
}
