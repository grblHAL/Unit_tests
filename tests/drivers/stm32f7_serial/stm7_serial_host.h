#pragma once
#include "driver.h"
#include "serial.h"
#include "grbl/task.h"
#include "check.h"
#include <string.h>
void stm7_prepare(void);
extern const io_stream_t *stm7_stream;
extern unsigned stm7_gpio_calls, stm7_irq_calls;
extern GPIO_InitTypeDef stm7_gpio_config;
extern GPIO_TypeDef *stm7_gpio_port;

void stm7_receive(uint8_t data);
void stm7_transmit(void);
void stm7_drain(void);
extern unsigned stm7_rt_calls, stm7_block_calls;
extern bool stm7_allow_blocking;
extern uint8_t stm7_sent[1024];
extern size_t stm7_sent_count;

void stm7_triplex_prepare(void);
void stm7_receive_port(unsigned instance, uint8_t data);
void stm7_transmit_port(unsigned instance);
void stm7_drain_port(unsigned instance);
extern const io_stream_t *stm7_port_stream[3];
extern GPIO_InitTypeDef stm7_gpio_configs[3];
extern GPIO_TypeDef *stm7_gpio_ports[3];
extern periph_pin_t stm7_registered_pins[6];
extern unsigned stm7_pin_count;
extern uint8_t stm7_port_sent[3][1024];
extern size_t stm7_port_sent_count[3];
