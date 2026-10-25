#pragma once
#include "driver.h"
#include "serial.h"
#include "grbl/task.h"
#include "check.h"
#include <string.h>
void stm1_prepare(void);
void stm1_receive(uint8_t data);
void stm1_transmit(void);
void stm1_drain(void);
extern const io_stream_t *stm1_stream;
extern unsigned stm1_gpio_calls, stm1_irq_calls, stm1_block_calls, stm1_rt_calls;
extern GPIO_InitTypeDef stm1_gpio_config;
extern GPIO_TypeDef *stm1_gpio_port;
extern bool stm1_allow_blocking;
extern uint8_t stm1_sent[1024];
extern size_t stm1_sent_count;

extern GPIO_InitTypeDef stm1_gpio_configs[2];
