#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/plugins.h"
#include "grbl/ioports.h"
extern io_digital_t bank;
extern bool start_ok, select_ok;
extern unsigned starts, selections, deselections, transfers, registrations;
extern uint32_t shifted;
void start_hc595(void);
