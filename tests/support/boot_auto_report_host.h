#pragma once
#include "support/boot_host.h"
static inline void configure_auto_reports(settings_t *s) { s->report_interval = 100; }
static inline void prepare_auto_reports(void)
{
    boot_during_setup = configure_auto_reports;
    CHECK(grbl_enter() == 0);
    CHECK(settings.report_interval == 100 && sys.flags.auto_reporting);
    sys.rt_exec_state = 0;
}
static inline void advance_report_time(uint32_t ms)
{
    engine_ticks += ms;
    engine_execute_tasks(STATE_IDLE);
}
