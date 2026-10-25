#pragma once
#include "driver.h"
#include "check.h"
#include "grbl/task.h"
#include "grbl/nvs_buffer.h"
void atci_init(void);
void atci_prepare(void);
void atci_start(void);
void atci_flags(uint8_t value);
void atci_bounds(float xmin, float ymin, float xmax, float ymax);
bool atci_check(float x, float y);
void atci_clip(float *target);
status_code_t atci_command(float value, sys_state_t state);
void atci_poll(void);
void atci_report(void);
extern setting_details_t *registered_settings;
extern float position[N_AXIS];
extern bool gpio[8], alloc_ok, previous_accept;
extern unsigned check_calls, clip_calls, chains, saves, messages;
extern char output[512], message[192];
extern uint32_t delay_ms;
