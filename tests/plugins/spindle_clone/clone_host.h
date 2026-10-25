#pragma once
#include "eeprom_host.h"
#include "nvs_buffer.h"
#include "task.h"
extern grbl_t grbl;
extern settings_t settings;
extern system_t sys;
extern setting_details_t *clone_settings;
extern bool clone_storage;
extern unsigned clone_calls, clone_selected, clone_warnings;
extern spindle_state_t clone_output;
extern float clone_rpm;
extern uint_fast16_t clone_pwm;
void clone_prepare(void);
void clone_float(setting_id_t id, float value);
void cloned_spindle_init(void);
