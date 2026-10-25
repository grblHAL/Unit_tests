#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/plugins.h"
#include "grbl/ioports.h"
extern io_digital_t bank;
extern bool bus_ok, probe_ok;
extern unsigned starts, probes, writes, registrations;
extern uint16_t gpio;
extern uint8_t pin_base;
void start_mcp(void);
