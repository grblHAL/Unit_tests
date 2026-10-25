#pragma once
#include "misc_host.h"
#include "fans.h"
#include "ioports.h"
#include "nvs_buffer.h"
#include "task.h"
void prepare_fans(void);
void load_fans(void);
const setting_detail_t *fan_setting(setting_id_t id);
extern setting_details_t *registered_settings;
extern unsigned available_ports, warnings, reset_calls, completed_calls, spindle_calls, output_calls, reports, saved;
extern bool alloc_ok, claims_ok, outputs[4];
extern char fan_output[256];
extern foreground_task_ptr delayed_task;
extern void *delayed_data;
extern uint32_t delayed_ms;
void run_delayed_fan(void);
