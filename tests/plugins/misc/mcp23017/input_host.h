#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/plugins.h"
#include "grbl/ioports.h"
#include "grbl/task.h"
#if MCP23017_ENABLE == 1
#define INPUT_COUNT 8
#define INPUT_REGISTER 0x13
#else
#define INPUT_COUNT 16
#define INPUT_REGISTER 0x12
#endif
extern io_digital_t ports;
extern unsigned reads, sends, irq_claims;
extern uint16_t sample, output_value;
extern uint8_t device_registers[22];
void start_inputs(void);
