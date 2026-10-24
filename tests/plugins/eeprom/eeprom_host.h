#pragma once
#include "driver.h"
#include "eeprom.h"
#include "check.h"
extern bool start_ok, probe_ok;
extern unsigned starts, probes, transfers, delays, fail_transfer;
extern uint8_t memory[131072];
extern struct transaction { uint32_t address; unsigned count; bool read; } transactions[128];
void prepare_eeprom(void);
unsigned page_size(void);
