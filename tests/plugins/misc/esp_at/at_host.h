#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/plugins.h"
#include "grbl/task.h"
#include "grbl/nvs_buffer.h"
extern setting_details_t *at_settings;
extern bool at_uart_available, at_storage_available, at_existing_server;
extern bool at_prompt;
extern const char *at_fail_command;
extern unsigned at_fail_remaining, at_warnings, at_welcomes, at_reports, at_claims;
extern char at_commands[4096], at_output[4096], at_tx[512];
extern size_t at_tx_length;
extern enqueue_realtime_command_ptr at_uart_handler;
void at_prepare(void);
void at_load(grbl_wifi_mode_t mode);
void at_step(uint32_t delay);
unsigned at_pending(void);
void at_start(void);
void at_connect(void);
void at_modem_data(const char *text);
void at_controls(bool both);
extern unsigned at_control_writes;
extern uint8_t at_control_ports[8];
extern bool at_control_levels[8];
void at_ready(void);
#if ETHERNET_ENABLE
#include "networking/networking.h"
network_flags_t at_network_info(network_info_t *info);
status_code_t at_netif(void);
#endif
const setting_detail_t *at_setting(setting_id_t id);
void at_setting_string(setting_id_t id, const char *text);
bool at_command_seen(const char *text);
