#pragma once
#include "virtual_inputs.h"
#include "check.h"
#include "grbl/task.h"
void vi_prepare(bool chain);
void vi_start(bool chain);
status_code_t vi_command(const char *args);
void vi_configure(bool away, bool probing);
void vi_physical(probe_id_t id, bool contact);
void vi_select(probe_id_t id);
extern char output[512];
extern unsigned warnings, resets, unknown_calls, option_calls, registrations;
extern bool unknown_result;
extern sys_commands_t *registered_commands;
