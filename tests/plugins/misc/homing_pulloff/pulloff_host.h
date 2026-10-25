#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/nvs_buffer.h"
#include "grbl/machine_limits.h"
extern setting_details_t *details;
extern bool allocation_ok, registration_ok;
extern unsigned saves, updates, chained_changes, options, reports;
extern settings_changed_flags_t last_flags;
extern coord_data_t requested;
void prepare_pulloff(void);
void initialize_pulloff(void);
void load_pulloff(void);
void set_pulloff(unsigned axis, float value);
float get_pulloff(unsigned axis);
