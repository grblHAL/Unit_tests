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
