#pragma once
#include "main.h"
#include "grbl/hal.h"
#include "check.h"
#include <string.h>
extern uint16_t f3_source[1024];
extern unsigned f3_unlocks, f3_locks, f3_erases, f3_programs, f3_fail_program;
extern bool f3_unlock_ok, f3_erase_ok;
extern uintptr_t f3_address;
void f3_prepare(unsigned kb, unsigned size);
void f3_check_copy(void);
bool memcpy_from_flash(uint8_t *dest);
bool memcpy_to_flash(uint8_t *source);
