#pragma once
#include "driver.h"
#include "check.h"
#include "serial.h"
#include "grbl/task.h"
void msp_start(void);
void msp_map(void);
void msp_receive(uint8_t value);
void msp_transmit(void);
void msp_drain(void);
void msp_busy(bool busy);
void EUSCIA0_IRQHandler(void);
extern const io_stream_t *msp_stream;
extern unsigned pins, rt_calls, blocks, sent_count, irq_enables, irq_disables;
extern bool allow_blocking, cpu_enabled;
extern uint8_t sent[2048];
extern uint32_t now;
