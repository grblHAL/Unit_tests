#pragma once
#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>
static inline float read_named_parameter(const char *text)
{
    char name[32];
    float value;
    CHECK(strlen(text) < sizeof(name));
    strcpy(name, text);
    CHECK(ngc_named_param_get(name, &value));
    return value;
}
static inline status_code_t named_parameter_block(const char *text)
{
    char block[96];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
