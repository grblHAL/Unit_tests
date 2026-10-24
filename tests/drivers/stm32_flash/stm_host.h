#pragma once
#include "driver.h"
#include "grbl/hal.h"
#include "check.h"
#include <string.h>
extern uint32_t stm_flash_words[32];
extern uint16_t stm_source[64];
extern unsigned stm_unlocks, stm_locks, stm_erases, stm_programs, stm_erase_failures,
    stm_program_fail;
extern bool stm_unlock_ok;
void stm_prepare(unsigned size);
bool memcpy_from_flash(uint8_t *dest);
bool memcpy_to_flash(uint8_t *source);
void stm_check_copy(void);
