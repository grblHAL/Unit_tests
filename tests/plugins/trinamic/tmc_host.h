#pragma once
#include "eeprom_host.h"
#include "grbl/nvs_buffer.h"
#include "grbl/task.h"
#include "trinamic.h"
extern setting_details_t *tmc_settings;
extern const tmchal_t *tmc_drivers[3];
extern unsigned tmc_reads, tmc_writes, tmc_delays, tmc_warnings, tmc_previous_settings,
    tmc_previous_limits, tmc_previous_reports, tmc_previous_realtime, tmc_limit_irqs;
extern uint32_t tmc_registers[3][128];
extern uint8_t tmc_addresses[3];
extern bool tmc_bus_ok, tmc_storage_ok, tmc_setup_ok, tmc_custom_address;
extern char tmc_output[4096];
void tmc_prepare(void);
void tmc_load(void);
void tmc_start(void);
void tmc_axis_command(user_mcode_t code, unsigned axis, float value);
status_code_t tmc_set(setting_id_t base, unsigned axis, uint_fast16_t value);

extern sys_state_t tmc_state;
extern unsigned tmc_enable_calls, tmc_pulse_calls, tmc_holds, tmc_warn_reports;
void tmc_runtime_prepare(void);
void tmc_run_tasks(void);
void tmc_poll(void);
void tmc_block(unsigned axis);
void tmc_mask(setting_id_t id, uint8_t value);
void tmc_sensitivity(setting_id_t base, unsigned axis, float value);

status_code_t tmc_command(parser_block_t *block);

#if TRINAMIC_ENABLE == 2130 || TRINAMIC_ENABLE == 5160 ||                                          \
    (TRINAMIC_ENABLE == 2240 && !TRINAMIC_UART_ENABLE)
void tmc_spi_prepare(void);
#endif

#if TRINAMIC_ENABLE == 2660
void tmc_spi20_prepare(void);
#endif
extern unsigned tmc_retry_delays;

extern bool tmc_crc_ok;

extern unsigned tmc_unexpected_spi;
