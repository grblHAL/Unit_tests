#pragma once
#include "support/backlash_host.h"
static inline status_code_t store_backlash(const char *source)
{
    char text[32]; CHECK(strlen(source) < sizeof(text)); strcpy(text, source);
    return settings_store_setting(Setting_AxisBacklash, text);
}
