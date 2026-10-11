#pragma once
#include "support/coolant_host.h"
#include "spindle_control.h"
#include <string.h>
static unsigned program_complete_calls, program_pause_calls, program_pallet_calls;
static program_flow_t program_completion;
static bool program_completion_check_mode;
static status_code_t program_pause_result = Status_Handled;
static void program_completed(program_flow_t flow, bool check_mode)
{
    program_complete_calls++;
    program_completion = flow;
    program_completion_check_mode = check_mode;
}
static status_code_t program_paused(program_flow_t flow, bool check_mode)
{
    (void)flow; (void)check_mode;
    program_pause_calls++;
    return program_pause_result;
}
static void program_pallet(void) { program_pallet_calls++; }
static inline void prepare_program_end(bool check_mode)
{
    prepare_coolant();
    grbl.on_program_completed = program_completed;
    grbl.on_program_paused = program_paused;
    hal.pallet_shuttle = program_pallet;
    settings.status_report.sync_on_wco_change = false;
    if(check_mode) state_set(STATE_CHECK_MODE);
}
static inline status_code_t program_block(const char *text)
{
    char block[96]; CHECK(strlen(text) < sizeof(block));
    strcpy(block, text); return gc_execute_block(block);
}
