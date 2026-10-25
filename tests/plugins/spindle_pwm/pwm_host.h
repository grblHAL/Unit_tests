#pragma once
#include "eeprom_host.h"
#include "ioports.h"
#include "nvs_buffer.h"
extern grbl_t grbl;
extern settings_t settings;
extern system_t sys;
extern setting_details_t *pwm_settings;
extern unsigned pwm_warnings, pwm_writes, pwm_ports;
extern bool pwm_storage, pwm_outputs[4];
void pwm_prepare(unsigned ports);
void pwm_load(void);
void pwm_spindle_init(void);
status_code_t pwm_set(setting_id_t id, float value);
float pwm_get(setting_id_t id);
#include "task.h"

extern bool pwm_analog_available, pwm_capable, pwm_config_ok;
extern unsigned pwm_config_calls, pwm_analog_calls;
extern float pwm_value;
extern pwm_config_t pwm_captured;
const setting_detail_t *pwm_detail(setting_id_t id);
