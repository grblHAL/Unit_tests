#pragma once
#include "support/engine_host.h"
#include "nvs_buffer.h"
#include "nvs.h"
#include "report.h"
#include "check.h"
#include <string.h>
static bool debug_connected = true;
static bool debug_stream_connected(void) { return debug_connected; }
static inline void prepare_nvs_debug(void)
{
    engine_prepare(); report_init_fns(); hal.stream.is_connected = debug_stream_connected;
    hal.nvs.type = NVS_EEPROM; hal.nvs.size = GRBL_NVS_SIZE;
}
static inline void check_map_record(const char *name, unsigned address, unsigned size)
{
    char expected[96];
    snprintf(expected, sizeof(expected), "%s: %u %u %u", name, address, size, address + size);
    CHECK(strstr(engine_output, expected) != NULL);
}
static inline void check_core_memory_map(void)
{
    CHECK(strstr(engine_output, "NVS Area: addr size end") != NULL);
    check_map_record("Global", NVS_ADDR_GLOBAL, sizeof(settings_t) + NVS_CRC_BYTES);
    check_map_record("Parameters", NVS_ADDR_PARAMETERS, NVS_SIZE_PARAMETERS);
    check_map_record("Startup block", NVS_ADDR_STARTUP_BLOCK, NVS_SIZE_STARTUP_BLOCK);
    check_map_record("Build info", NVS_ADDR_BUILD_INFO, NVS_SIZE_BUILD_INFO);
    check_map_record("Tool table", NVS_ADDR_TOOL_TABLE, N_TOOLS * (sizeof(tool_data_t) + NVS_CRC_BYTES));
}
