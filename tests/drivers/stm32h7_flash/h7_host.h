#pragma once
#include "driver.h"
#include "flash.h"
#include "check.h"
#include <string.h>
extern uint32_t h7_flash_words[64];
extern uint8_t *h7_source;
extern unsigned h7_unlocks, h7_locks, h7_erases, h7_programs, h7_fail_program;
extern bool h7_unlock_ok, h7_erase_ok;
void h7_prepare(unsigned size);
void h7_check_copy(void);
void h7_close(void);
