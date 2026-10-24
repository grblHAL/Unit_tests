#pragma once
#include "driver.h"
#include "check.h"
#include "grbl/task.h"
void flexgpio_init(void);
void flex_prepare(void);
void flex_start(void);
void flex_run(void);
void flex_irq(uint32_t bits);
xbar_t flex_pin(io_port_direction_t dir, uint8_t port);
extern io_digital_t bank;
extern bool start_ok, probe_ok, send_ok, receive_ok, claim_ok;
extern unsigned sends, receives, alarms, warnings, saved, chains, events;
extern uint8_t event_port;
extern bool event_value;
extern uint32_t input_bits;
extern uint8_t last_packet[8];
extern size_t last_size;
void flex_event(uint8_t port, bool state);

extern bool inject_inputs;
extern uint32_t delay_bits;
