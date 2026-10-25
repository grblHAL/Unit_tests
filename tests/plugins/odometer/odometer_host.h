#pragma once
#include "eeprom_host.h"
#include "stepper.h"
#include "task.h"
void odometer_init(void);
void odometer_prepare(void);
status_code_t odometer_query(char *args);
void odometer_move(uint32_t x, uint32_t y, uint32_t z, uint32_t duration);
void odometer_run_tasks(void);
extern uint32_t odometer_ticks;
extern unsigned odometer_pulse_counts[N_AXIS], odometer_state_calls, odometer_spindle_calls, odometer_settings_calls, odometer_selected_calls, odometer_task_count, odometer_warnings;
extern bool odometer_replace_pulse;
extern unsigned odometer_alternate_calls;
extern char odometer_output[2048];
extern sys_commands_t *odometer_commands;
void odometer_clear_output(void);
void odometer_driver_spindle(spindle_ptrs_t *spindle, spindle_state_t state, float rpm);
