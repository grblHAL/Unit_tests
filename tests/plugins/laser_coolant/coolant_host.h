#pragma once
#include "eeprom_host.h"
#include "ioports.h"
#include "nvs_buffer.h"
#include "task.h"
#include "ngc_params.h"
extern grbl_t grbl;
extern settings_t settings;
extern system_t sys;
extern setting_details_t *coolant_settings;
extern bool coolant_storage, coolant_signal;
extern int32_t coolant_temperature;
extern coolant_state_t coolant_output;
extern unsigned coolant_warnings, coolant_writes, coolant_irqs, coolant_reports, coolant_plugins,
    coolant_prior_reports, coolant_reads;
extern uint32_t coolant_delay;
extern char coolant_text[256];
void coolant_prepare(bool inputs);
void coolant_load(void);
void coolant_float(setting_id_t id, float value);
void coolant_run_delayed(void);
void coolant_edge(bool state);
float coolant_param(const char *name);
void laser_coolant_init(void);
