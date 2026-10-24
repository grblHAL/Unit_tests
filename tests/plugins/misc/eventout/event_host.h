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

extern uint8_t claimed_mask, missing_mask;
void prepare_events(void);
void run_event_startup(void);

extern unsigned pending_tasks, control_calls;
void run_event_tasks(void);
