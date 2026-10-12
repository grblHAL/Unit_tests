#pragma once
#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "check.h"
#include <math.h>
void delta_robot_init(void);
static void settings_changed(settings_t *current, settings_changed_flags_t changed)
{
    CHECK(current == &settings);
    (void)changed;
}
static inline void prepare_delta_with_callbacks(void (*configure)(void))
{
    engine_prepare();
    hal.nvs.type = NVS_EEPROM;
    grbl.on_settings_changed = settings_changed;
    if(configure) configure();
    delta_robot_init();
    setting_details_t *details = NULL;
    CHECK(setting_get_details(Setting_Kinematics0, &details) != NULL);
    CHECK(details != NULL && details->restore && details->load && details->on_changed);
    details->restore();
    details->load();
    details->on_changed(&settings, (settings_changed_flags_t){0});
}

static inline void prepare_delta(void) { prepare_delta_with_callbacks(NULL); }
