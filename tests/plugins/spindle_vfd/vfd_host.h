#pragma once
#include "eeprom_host.h"
#include "nvs_buffer.h"
#include "spindle/vfd/spindle.h"
extern setting_details_t *vfd_settings;
extern spindle_ptrs_t *vfd_motor;
extern unsigned vfd_requests, vfd_flushes, vfd_silences, vfd_alarms, vfd_previous_settings,
    vfd_previous_reports, vfd_previous_selected;
extern uint32_t vfd_ticks;
extern bool vfd_bus_up, vfd_storage_ok;
extern unsigned vfd_reject, vfd_exception;
extern uint16_t vfd_feedback;
extern modbus_message_t vfd_messages[64];
extern bool vfd_blocking[64];
void vfd_init(void);
void vfd_prepare(bool transport);
void vfd_start(void);
void vfd_run_tasks(void);
void vfd_clear_requests(void);
void vfd_word(setting_id_t id, uint16_t value);
void vfd_float(setting_id_t id, float value);
void vfd_expect(unsigned index, uint8_t function, uint16_t reg, uint16_t value, bool blocking);

extern uint16_t vfd_poles, vfd_min_frequency, vfd_max_frequency;
extern unsigned vfd_resets;
