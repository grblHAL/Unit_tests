#pragma once
#include "support/report_host.h"
static const alarm_detail_t primary_alarms[] = {
    {.id = Alarm_AbortCycle, .description = "third"},
    {.id = Alarm_HardLimit, .description = "first"}
};
static const alarm_detail_t secondary_alarms[] = {{.id = Alarm_SoftLimit}};
static alarm_details_t extra_alarms = {.n_alarms = 1, .alarms = secondary_alarms};
static alarm_details_t all_alarms = {.n_alarms = 2, .alarms = primary_alarms, .next = &extra_alarms};
static const status_detail_t primary_errors[] = {
    {.id = Status_InvalidStatement, .description = "third"},
    {.id = Status_ExpectedCommandLetter, .description = "first"}
};
static const status_detail_t secondary_errors[] = {{.id = Status_BadNumberFormat}};
static error_details_t extra_errors = {.n_errors = 1, .errors = secondary_errors};
static error_details_t all_errors = {.n_errors = 2, .errors = primary_errors, .next = &extra_errors};
static alarm_details_t *get_report_alarms(void) { return &all_alarms; }
static error_details_t *get_report_errors(void) { return &all_errors; }
static inline void prepare_catalog_report(void)
{
    prepare_report();
    grbl.on_get_alarms = get_report_alarms;
    grbl.on_get_errors = get_report_errors;
}
