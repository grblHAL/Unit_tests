#pragma once
#include "driver.h"
#include "check.h"
#include "grbl/task.h"
void status_light_init(void);
void rgb_prepare(void);
void rgb_start(void);
void rgb_run_next(void);
void rgb_state(sys_state_t state);
void rgb_expect(unsigned strip, unsigned r, unsigned g, unsigned b);
status_code_t rgb_command(float zone, float mode, float intensity, bool execute);
extern rgb_color_t pixels[2][32];
extern unsigned counts[2], writes[2], chains, warnings, messages;
extern uint8_t brightness[2];
extern bool bus_busy;
extern uint32_t now, last_delay;
extern unsigned pending;
extern sys_state_t machine_state;
