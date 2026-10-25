#pragma once
#include "driver.h"
#include "serial.h"
#include "grbl/task.h"
#include "check.h"
#include <string.h>
void stm3_prepare(void);
void stm3_receive(uint8_t data);
void stm3_transmit(void);
void stm3_drain(void);
extern const io_stream_t *stm3_stream;
extern unsigned stm3_gpio_calls, stm3_irq_calls, stm3_block_calls, stm3_rt_calls;
extern GPIO_InitTypeDef stm3_gpio_config;
extern GPIO_TypeDef *stm3_gpio_port;
extern bool stm3_allow_blocking;
extern uint8_t stm3_sent[1024];
extern size_t stm3_sent_count;
