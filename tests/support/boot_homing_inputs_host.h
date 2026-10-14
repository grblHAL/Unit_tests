#pragma once
#include "support/boot_host.h"
#include "crossbar.h"
static bool use_limits;
static home_signals_t dedicated_home_switches(void)
{ return (home_signals_t){.a = {.mask = 2}, .b = {.mask = 4}}; }
static inline void install_home_switches(settings_t *s)
{
    hal.homing.get_state = dedicated_home_switches;
    s->homing.flags.use_limit_switches = use_limits;
}
