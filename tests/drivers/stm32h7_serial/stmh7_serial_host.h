#pragma once
#include "driver.h"
#include "serial.h"
#include "grbl/task.h"
#include "check.h"
#include <string.h>
void stmh7_prepare(void);
extern const io_stream_t *stmh7_stream;
extern unsigned stmh7_gpio_calls, stmh7_irq_calls;
extern GPIO_InitTypeDef stmh7_gpio_config;
extern GPIO_TypeDef *stmh7_gpio_port;

void stmh7_receive(uint8_t data);
void stmh7_transmit(void);
void stmh7_drain(void);
extern unsigned stmh7_rt_calls, stmh7_block_calls;
extern bool stmh7_allow_blocking;
extern uint8_t stmh7_sent[1024];
extern size_t stmh7_sent_count;

void stmh7_triplex_prepare(void);
void stmh7_receive_port(unsigned instance, uint8_t data);
void stmh7_transmit_port(unsigned instance);
void stmh7_drain_port(unsigned instance);
extern const io_stream_t *stmh7_port_stream[3];
extern GPIO_InitTypeDef stmh7_gpio_configs[3];
extern GPIO_TypeDef *stmh7_gpio_ports[3];
extern periph_pin_t stmh7_registered_pins[6];
extern unsigned stmh7_pin_count;
extern uint8_t stmh7_port_sent[3][1024];
extern size_t stmh7_port_sent_count[3];
