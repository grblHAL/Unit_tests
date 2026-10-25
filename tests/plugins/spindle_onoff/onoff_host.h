#pragma once
#include "eeprom_host.h"
#include "ioports.h"
#include "nvs_buffer.h"
extern grbl_t grbl;
extern settings_t settings;
extern system_t sys;
extern setting_details_t *on_settings;
extern unsigned on_warnings, on_writes, on_ports;
extern bool on_storage, on_outputs[4];
void on_prepare(unsigned ports);
void on_load(void);
void onoff_spindle_init(void);
status_code_t on_set(setting_id_t id, float value);
float on_get(setting_id_t id);
#include "task.h"
