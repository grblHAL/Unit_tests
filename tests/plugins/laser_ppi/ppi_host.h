#pragma once
#include "check.h"
#include "driver.h"
#include "grbl/task.h"
extern spindle_ptrs_t *ppi_motor;
extern bool ppi_core_handles;
extern unsigned ppi_pulses, ppi_steps, ppi_wakes, ppi_updates, ppi_selected, ppi_parser_inits,
    ppi_completions, ppi_previous_reports, ppi_fallback_checks, ppi_fallback_validates,
    ppi_fallback_executes;
extern uint_fast16_t ppi_width, ppi_core_rate, ppi_core_width;
extern unsigned ppi_locations[64];
void ppi_init(void);
void ppi_prepare(bool pwm, bool capability);
void ppi_command(user_mcode_t code, float value, sys_state_t state);
void ppi_move(unsigned steps, float steps_per_mm);
