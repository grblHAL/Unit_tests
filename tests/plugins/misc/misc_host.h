#pragma once
#include "driver.h"
#include "check.h"
void prepare_hooks(void);
void prepare_m220(void);
extern char reported_plugin[80];
extern unsigned override_calls, previous_checks, previous_validations, previous_executions, previous_reports, plugin_reports;
