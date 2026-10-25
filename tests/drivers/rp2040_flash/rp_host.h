#pragma once
/* Host SDK boundary: omit board pin/PIO setup while compiling original flash.c. */
#define __DRIVER_H__
#include "check.h"
#include "grbl/hal.h"
#include "hardware/flash.h"
#include "hardware/regs/addressmap.h"
#include <string.h>
#define RP_OFFSET (2016 * 1024)
extern unsigned rp_erases, rp_programs, rp_irq_phase;
extern size_t rp_program_size;
extern bool rp_corrupt;
void __disable_irq(void);
void __enable_irq(void);
void rp_prepare(size_t size);
bool memcpy_to_flash(uint8_t *source);
bool memcpy_from_flash(uint8_t *dest);
