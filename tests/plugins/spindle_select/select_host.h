#pragma once
#include "eeprom_host.h"
#include "nvs_buffer.h"
#include "task.h"
extern grbl_t grbl;
extern settings_t settings;
extern system_t sys;
extern setting_details_t *select_settings;
extern bool select_storage, select_setup_ok, select_load_image;
extern unsigned select_warnings, select_previous_tools, select_previous_checks,
    select_previous_validates, select_previous_executes;
extern char select_output[256];
void select_prepare(void);
status_code_t select_binding(unsigned slot, unsigned value);
status_code_t select_tool_start(unsigned slot, unsigned value);
status_code_t select_command(bool p, float value, bool execute);
int8_t spindle_select_get_binding(spindle_id_t id);
void spindle_select_init(void);
