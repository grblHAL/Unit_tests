#pragma once
#include "support/wall_host.h"
static unsigned wall_previous_options_calls;
static bool wall_previous_newopt;
static void wall_previous_options(bool newopt)
{ wall_previous_options_calls++; wall_previous_newopt = newopt; }
static inline void prepare_wall_options(void)
{
    engine_prepare(); hal.stream.is_connected = connected;
    grbl.on_settings_changed = settings_changed; grbl.on_report_options = wall_previous_options;
    wall_plotter_init(); grbl.on_settings_changed(&settings,(settings_changed_flags_t){0});
}
