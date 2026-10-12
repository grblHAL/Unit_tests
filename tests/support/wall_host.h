#pragma once
#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "check.h"
void wall_plotter_init(void);
static void settings_changed(settings_t *current, settings_changed_flags_t changed)
{
    CHECK(current == &settings);
    (void)changed;
}
static bool connected(void) { return true; }
static inline void prepare_wall(void)
{
    engine_prepare();
    hal.stream.is_connected = connected;
    grbl.on_settings_changed = settings_changed;
    wall_plotter_init();
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
}
