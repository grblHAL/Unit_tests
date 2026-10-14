#pragma once
#include "support/engine_host.h"
#include "nvs_buffer.h"
#include "nvs.h"
#include "report.h"
#include "check.h"
#include <stddef.h>
void *__real_malloc(size_t size);
static unsigned fail_buffer_allocations;
void *__wrap_malloc(size_t size)
{
    if(size == NVS_SIZE && fail_buffer_allocations) { fail_buffer_allocations--; return NULL; }
    return __real_malloc(size);
}
static bool allocation_stream_connected(void) { return true; }
static inline void prepare_allocation_nvs(void)
{
    engine_prepare(); hal.nvs.type = NVS_EEPROM;
    hal.nvs.size = GRBL_NVS_SIZE;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    report_init_fns(); hal.stream.is_connected = allocation_stream_connected;
}
