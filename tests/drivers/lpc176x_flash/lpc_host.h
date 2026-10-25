#pragma once
#include "chip.h"
#include "grbl/hal.h"
#include "check.h"
#include <string.h>
#define LPC_FLASH_ADDRESS 0x78000U
extern uint32_t lpc_source[1024];
extern unsigned lpc_stage, lpc_fail_at, lpc_prepares, lpc_erases, lpc_copies, lpc_disables,
    lpc_enables, lpc_copied;
extern bool lpc_irqs_disabled;
void lpc_prepare(unsigned size);
bool memcpy_from_flash(uint8_t *dest);
bool memcpy_to_flash(uint8_t *source);
void lpc_check_copy(void);
