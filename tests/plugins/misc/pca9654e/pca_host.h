#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/plugins.h"
#include "grbl/ioports.h"
extern io_digital_t outputs;
extern bool bus_ok, device_present;
extern unsigned starts, probes, writes, registrations, enumerations;
extern uint8_t register_values[4], pin_base;
void start_expander(void);
