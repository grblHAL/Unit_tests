#pragma once
#include "support/report_host.h"
#include "stream.h"
#include "state_machine.h"
static unsigned rt_input_calls, rt_report_calls;
static uint8_t rt_input_byte;
static bool rt_accept = true;
static bool rt_report_input(uint8_t byte) { rt_input_calls++; rt_input_byte = byte; return rt_accept; }
static void rt_report_added(report_tracking_flags_t flags)
{ CHECK(flags.cycle_start); rt_report_calls++; }
static inline void prepare_rt_reporting(void)
{
    prepare_report(); state_set(STATE_IDLE); settings.status_report.pin_state = true;
    hal.stream.report.flags.value = 0; hal.stream.enqueue_rt_command = rt_report_input;
    grbl.on_rt_reports_added = rt_report_added;
}
