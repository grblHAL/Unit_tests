#pragma once
#include "eeprom_host.h"
#include "grbl/task.h"
#include "grbl/nvs_buffer.h"
#include "grbl/protocol.h"
extern setting_details_t *bt_settings;
extern bool bt_uart_ok, bt_storage_ok, bt_pin_high, bt_irq_ok;
extern unsigned bt_warnings, bt_commands, bt_fail_command, bt_timeout_command, bt_claims, bt_irqs,
    bt_welcomes, bt_prior_reports, bt_plugins, bt_base_disables;
extern uint32_t bt_baud[16];
extern unsigned bt_bauds;
extern char bt_output[2048], bt_command_log[256];
extern enqueue_realtime_command_ptr bt_base_handler, bt_uart_handler;
void bluetooth_init(void);
void bt_prepare(unsigned inputs, bool irq_capable);
void bt_load(void);
void bt_run(void);
void bt_edge(bool on);
const setting_detail_t *bt_setting(setting_id_t id);
uint32_t bt_enabled(void);
void bt_enable(bool on);
status_code_t bt_port(float port);
void bt_name(const char *name);
void bt_init_configured(void);
