#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/plugins.h"
#include "grbl/ioports.h"
extern io_analog_t bank;
extern bool start_ok, probe_ok, send_ok;
extern unsigned starts, probes, sends, reads, registrations, native_enumerations;
extern uint16_t sample;
extern uint8_t packet[3];
void prepare_analog(void);
void initialize_analog(void);
#ifdef MCP4725_ENABLE
#define DEVICE_ADDRESS 0x60
#define DEVICE_DIRECTION Port_Output
#define DEVICE_FUNCTION Output_Analog_Aux0
#define DEVICE_GROUP PinGroup_AuxOutputAnalog
#else
#define DEVICE_ADDRESS 0x4d
#define DEVICE_DIRECTION Port_Input
#define DEVICE_FUNCTION Input_Analog_Aux0
#define DEVICE_GROUP PinGroup_AuxInputAnalog
#endif
