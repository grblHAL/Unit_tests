#pragma once
#include "driver.h"
#include "check.h"
#include "grbl/task.h"
#include "grbl/nvs_buffer.h"
void thermistor_init(void);
void therm_prepare(void);
void therm_start(bool assigned);
void therm_report(bool all);
void therm_float(unsigned id, float value);
status_code_t therm_command(const char *name, sys_state_t state, const char *args);
extern setting_details_t *registered_settings;
extern sys_commands_t *registered_commands;
extern unsigned available_ports, warnings, saves, claims, reads, stops, reports, options;
extern bool alloc_ok, claim_ok;
extern int32_t adc;
extern char output[512];
