#pragma once
#include "driver.h"
#include "check.h"
#include "grbl/task.h"
extern bool led_bus_ok, led_probe_ok, led_send_ok;
extern unsigned led_probes, led_warnings, led_writes, led_states, led_selects;
extern unsigned led_spindles, led_coolants, led_reports, led_plugins;
extern uint8_t led_bytes[32][2];
extern bool led_blocking[32];
extern spindle_ptrs_t led_spindle;
extern spindle_state_t led_spindle_state;
extern coolant_state_t led_coolant_state;
void led_prepare(void);
void display_init(void);
