#pragma once
#include "support/boot_host.h"
#include "probe.h"
static unsigned probe_select_calls;
static probe_id_t selected_probe;
static bool probe_selection_ok = true;
static bool select_probe(probe_id_t id)
{ probe_select_calls++; selected_probe = id; return probe_selection_ok; }
static inline void install_toolsetter(settings_t *s)
{
    hal.driver_cap.toolsetter = true;
    hal.probe.select = select_probe;
    s->probe.toolsetter_auto_select = true;
}
static inline void prepare_boot_toolsetter(void)
{
    boot_during_setup = install_toolsetter;
    CHECK(grbl_enter() == 0);
    CHECK(grbl.on_probe_toolsetter != NULL);
    probe_select_calls = 0;
}
