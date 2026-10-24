#pragma once
#include "grbl/hal.h"
#include "check.h"
#include "tiva.h"
#include "serial.h"
#include "grbl/task.h"
void uart_start(void);
void uart_receive(uint8_t value);
void uart_drain(void);
extern const io_stream_t *uart_stream;
extern unsigned pins, clocks, rt_calls, block_calls, tx_count;
extern bool tx_ready, allow_blocking, rts;
extern uint8_t tx_data[4096];
extern uint32_t irq_mask;
