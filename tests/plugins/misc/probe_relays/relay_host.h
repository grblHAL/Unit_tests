#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/ioports.h"
#include "grbl/nvs_buffer.h"
#include "grbl/task.h"
extern setting_details_t *relay_details;
extern bool alloc_ok, claims_ok, native_toolsetter, native_probe2, levels[2];
extern unsigned available, saves, warnings, writes, delays, selections, reports, options;
void prepare_relays(void);
void initialize_relays(void);
void load_relays(void);
const setting_detail_t *relay_setting(setting_id_t id);
void set_relay_port(setting_id_t id, float port);
float get_relay_port(setting_id_t id);
