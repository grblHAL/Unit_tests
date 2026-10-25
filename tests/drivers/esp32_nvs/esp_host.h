#pragma once
#include "check.h"
#include "esp_partition.h"
#include "grbl/hal.h"
#include <string.h>
extern uint8_t esp_memory[4096];
extern unsigned esp_reads, esp_writes, esp_erases, esp_handler_changes, esp_filter_checks;
extern bool esp_found, esp_read_ok, esp_write_ok, esp_erase_ok;
extern enqueue_realtime_command_ptr esp_handler;
void esp_prepare(void);
bool esp_original_handler(uint8_t c);
const esp_partition_t *nvsInit(void);
bool nvsRead(uint8_t *data);
bool nvsWrite(uint8_t *data);
