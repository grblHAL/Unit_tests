#pragma once
#include "eeprom_host.h"
#include "encoders.h"
#include "task.h"
#include "nvs_buffer.h"
bool encoder_init(void);
void encoder_prepare(unsigned count, bool spindle_first);
void encoder_load(void);
void encoder_emit(unsigned index, int32_t position, uint32_t velocity, encoder_event_t event);
void encoder_run_tasks(void);
status_code_t encoder_set(setting_id_t setting, uint_fast16_t value);
uint32_t encoder_get(setting_id_t setting);
extern setting_details_t *encoder_settings;
extern unsigned encoder_claims, encoder_resets, encoder_configures, encoder_reports, encoder_previous_reports;
extern bool encoder_storage_ok;
extern uint8_t encoder_commands[64];
extern unsigned encoder_command_count;
extern char encoder_output[1024];
extern encoder_t encoder_devices[2];
extern encoder_cfg_t encoder_configs[2];
extern encoder_on_event_ptr encoder_handlers[2];
