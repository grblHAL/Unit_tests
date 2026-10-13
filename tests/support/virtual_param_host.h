#pragma once
#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

static float virtual_sensor_value = 12.5f;
static unsigned virtual_writes;
static float read_virtual_sensor(void) { return virtual_sensor_value; }
static inline void write_virtual_sensor(float value)
{
    virtual_sensor_value = value;
    virtual_writes++;
}
static inline float read_virtual_name(const char *text)
{
    char name[32]; CHECK(strlen(text) < sizeof(name)); strcpy(name, text);
    float value;
    CHECK(ngc_named_param_get(name, &value));
    return value;
}
