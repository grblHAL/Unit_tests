#pragma once
#include "driver.h"
#include "check.h"
void auxp_init(void);
void auxp_prepare(bool chained);
void auxp_report(bool all);
extern char output[256];
extern unsigned writes, resets, reports, options;
extern uint8_t last_port;
extern bool last_value;
