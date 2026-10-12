#pragma once
#include "support/settings_host.h"
#include "ngc_params.h"
static inline status_code_t builtin_macro_block(const char *text)
{
    char block[96];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
static inline float builtin_macro_result(const char *text)
{
    char name[32];
    float value;
    CHECK(strlen(text) < sizeof(name));
    strcpy(name, text);
    CHECK(ngc_named_param_get(name, &value));
    return value;
}
