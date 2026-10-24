#pragma once
#include "driver.h"
#include "check.h"
#include "grbl/task.h"
#include "grbl/nvs_buffer.h"
void pneumaseal_init(void);
void seal_prepare(void);
void seal_start(void);
void seal_state(sys_state_t state);
void seal_spindle(bool on);
void seal_expire(void);
void seal_setting(unsigned id, uint_fast16_t value);
extern setting_details_t *registered_settings;
extern unsigned available_ports, warnings, saves, claims, outputs, chains;
extern bool alloc_ok, claim_ok, solenoid, live_spindle;
extern uint8_t output_port;
extern uint32_t timer_ms;
extern foreground_task_ptr timer;
