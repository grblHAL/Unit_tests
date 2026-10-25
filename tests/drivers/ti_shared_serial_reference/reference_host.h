#pragma once
#include "uart_host.h"
extern io_stream_details_t *reference_streams;
#include "grbl/protocol.h"

#ifdef SERIAL2_MOD
extern const io_stream_t *uart2_stream;
extern uint32_t irq_mask2;
void uart2_start(void);
void uart2_event(uint32_t flags, uint8_t value);
#endif
