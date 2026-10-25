#pragma once
#include "serial.h"
#include "grbl/task.h"
#include "grbl/protocol.h"
#include "check.h"
#include <string.h>
extern const io_stream_t *sam_stream[2];
extern unsigned sam_clocks, sam_pins, sam_irqs;
void sam_prepare(void);
void sam_sync(void);
void sam_reg_write(const volatile uint32_t *reg, uint32_t value);

extern bool sam_mux_dirty, sam_allow_blocking;
extern unsigned sam_block_calls, sam_sent_count[2];
extern uint8_t sam_sent[2][2048];
void sam_receive(unsigned instance, uint8_t data);
void sam_busy(unsigned instance, bool busy);
void sam_transmit(unsigned instance);
void sam_drain(unsigned instance);
uint32_t sam_irq_mask(unsigned instance);
uint32_t sam_last_tx(unsigned instance);
void sam_mask_clear(unsigned instance);

extern periph_pin_t sam_registered_pins[4];
