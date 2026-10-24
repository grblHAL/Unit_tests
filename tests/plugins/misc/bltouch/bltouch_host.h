#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/ioports.h"
#include "grbl/task.h"
extern bool claims_ok, probe_ok, native_probe;
extern float angle, last_delay;
extern unsigned outputs, delays, resets, starts, completed, selections, warnings;
extern probe_id_t selected_probe;
extern uint32_t delayed_ms;
void load_bltouch(void);
void run_bltouch_startup(void);
void run_bltouch_immediate(void);
void run_bltouch_delayed(void);
void command_bltouch(user_mcode_t command);
status_code_t system_bltouch(const char *command);
extern foreground_task_ptr delayed_task;

extern char bltouch_output[256];
status_code_t dispatch_bltouch(parser_block_t *block);
