#pragma once
#include "driver.h"
#include "serial.h"
#include "grbl/task.h"
#include "check.h"
#include <string.h>
void stm_serial_prepare(void);
extern const io_stream_t *stm_stream;
extern unsigned stm_gpio_calls, stm_irq_calls;
extern GPIO_InitTypeDef stm_gpio_config;
extern GPIO_TypeDef *stm_gpio_port;

void stm_receive(uint8_t data);
void stm_transmit(void);
void stm_drain(void);
extern unsigned stm_rt_calls, stm_block_calls;
extern bool stm_allow_blocking;
extern uint8_t stm_sent[1024];
extern size_t stm_sent_count;

void stm_triplex_prepare(void);
void stm_receive_port(unsigned instance, uint8_t data);
void stm_transmit_port(unsigned instance);
void stm_drain_port(unsigned instance);
extern const io_stream_t *stm_port_stream[3];
extern GPIO_InitTypeDef stm_gpio_configs[3];
extern GPIO_TypeDef *stm_gpio_ports[3];
extern periph_pin_t stm_registered_pins[6];
extern unsigned stm_pin_count;
extern uint8_t stm_port_sent[3][1024];
extern size_t stm_port_sent_count[3];
