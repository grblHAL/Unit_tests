#pragma once
#include "driver.h"
#include "check.h"
#include "nvs_buffer.h"
#include "task.h"
extern grbl_t grbl;
extern settings_t settings;
extern system_t sys;
extern bool ovd_initial_select;
extern unsigned ovd_resets, ovd_completions, ovd_selected, ovd_settings, ovd_reports, ovd_plugins,
    ovd_checks, ovd_validates, ovd_executes;
void ovd_prepare(void);
status_code_t ovd_command(float percent, bool execute);
void laser_ovd_init(void);
