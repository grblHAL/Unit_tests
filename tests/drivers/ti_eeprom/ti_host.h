#pragma once
#include "grbl/hal.h"
#include "grbl/crc.h"
#include "check.h"
#include "driverlib/eeprom.h"
void eeprom_init(void);
void ti_prepare(void);
void ti_seed(uint32_t address, const uint8_t *data, size_t size);
extern uint8_t memory[1024];
extern unsigned reads, writes, allocations;
extern bool fail_alloc, fail_program;
