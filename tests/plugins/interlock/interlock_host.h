#pragma once
#include "driver.h"
#include "check.h"
#include "grbl/task.h"
#include "grbl/nvs_buffer.h"
void spindle_interlock_init(void);
void il_prepare(void);
void il_start(void);
status_code_t il_float(unsigned id, float value);
void il_int(unsigned id, uint_fast16_t value);
float il_read_float(unsigned id);
uint32_t il_read_int(unsigned id);
void il_command(bool on);
extern setting_details_t *registered_settings;
extern spindle_ptrs_t spindle;
extern unsigned input_count, output_count, hardware_spindles, hardware_outputs;
extern unsigned warnings, resets, chains, saves, startup_warnings;
extern bool alloc_ok, select_ok, output_value;
extern float levels[2][4];
extern char warning[256];
