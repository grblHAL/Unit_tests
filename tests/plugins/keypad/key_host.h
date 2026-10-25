#pragma once
#include "check.h"
#include "driver.h"
#include "grbl/crc.h"
#include "grbl/nvs_buffer.h"
#include "grbl/override.h"
#include "grbl/plugins.h"
#include "grbl/state_machine.h"
#include "grbl/task.h"
#include "keypad.h"
extern setting_details_t *key_settings;
extern sys_state_t key_state;
extern bool key_bus_ok, key_probe_ok, key_irq_ok, key_storage_ok, key_uart_ok, key_gcode_ok,
    key_preview;
extern unsigned key_gcodes, key_systems, key_reports, key_modes, key_data_changes,
    key_realtime_count, key_previous_reports;
extern char key_gcode[64], key_system[16], key_version[64];
extern uint8_t key_realtime[64], key_memory[1024];
extern jogdata_t key_data;
bool keypad_init(void);
void key_prepare(void);
void key_load(void);
void key_enqueue(uint8_t code);
void key_release(void);
void key_run(void);
void key_press(uint8_t code);
void key_setting(setting_id_t id, float value);
