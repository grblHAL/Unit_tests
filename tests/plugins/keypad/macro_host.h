#pragma once
#include "driver.h"
#include "keypad.h"
#include "../eeprom/eeprom_host.h"
#include "grbl/nvs_buffer.h"
#include "grbl/task.h"
extern bool macro_storage;
extern sys_state_t macro_state;
extern unsigned macro_resets, macro_statuses, macro_syncs, macro_warnings;
extern char macro_output[256];
extern setting_details_t *macro_settings;
void macro_prepare(void);
void macro_set_text(unsigned index, const char *text);
void macro_run_mcode(unsigned index);
void macro_read_text(char *buffer, size_t size);
int32_t macro_serial_read(void);
void macros_init(void);

#if MACROS_ENABLE & 1
extern unsigned macro_inputs, macro_realtime_count;
extern uint8_t macro_realtime[16];
extern bool macro_irq_ok;
void macro_pin(unsigned physical, bool high);
void macro_run_tasks(void);
void macro_action(unsigned index, unsigned action);
#endif
