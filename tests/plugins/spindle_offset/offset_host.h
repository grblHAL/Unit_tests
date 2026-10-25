#pragma once
#include "eeprom_host.h"
#include "nvs_buffer.h"
#include "task.h"
#include "motion_control.h"
extern grbl_t grbl;
extern settings_t settings;
extern system_t sys;
extern setting_details_t *offset_settings;
extern bool offset_storage, offset_accept;
extern unsigned offset_moves, offset_syncs, offset_planner_syncs, offset_wco, offset_previous,
    offset_reports, offset_plugins, offset_saves;
extern float offset_target[N_AXIS];
void offset_prepare(void);
void offset_values(float x, float y);
void offset_option(bool enabled);
void spindle_offset_init(void);
