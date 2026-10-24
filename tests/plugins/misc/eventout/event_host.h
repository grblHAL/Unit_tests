#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/ioports.h"
#include "grbl/nvs_buffer.h"
#include "grbl/task.h"
extern setting_details_t *event_details;
extern bool levels[4];
extern unsigned writes, saves, state_calls, spindle_calls, speed_calls, coolant_calls, resets,
    reports, options;
void load_events(void);
void bind_event(unsigned slot, uint_fast16_t trigger);
