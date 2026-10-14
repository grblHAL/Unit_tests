#pragma once
#include "support/engine_host.h"
#include "nvs_buffer.h"
#include "nvs.h"
#include "report.h"
#include "check.h"
#include <string.h>
static uint8_t flash_image[NVS_SIZE];
static unsigned flash_reads, flash_writes, flash_failures;
static bool read_flash_image(uint8_t *dest)
{ flash_reads++; memcpy(dest, flash_image, GRBL_NVS_SIZE); return true; }
static bool write_flash_image(uint8_t *source)
{
    flash_writes++;
    if(flash_failures) { flash_failures--; return false; }
    memcpy(flash_image, source, GRBL_NVS_SIZE); return true;
}
static bool flash_stream_connected(void) { return true; }
static inline void prepare_flash_nvs(void)
{
    engine_prepare(); report_init_fns();
    hal.stream.is_connected = flash_stream_connected;
    flash_image[0] = SETTINGS_VERSION;
    hal.nvs.type = NVS_Flash; hal.nvs.size = GRBL_NVS_SIZE;
    hal.nvs.memcpy_from_flash = read_flash_image;
    hal.nvs.memcpy_to_flash = write_flash_image;
    hal.nvs.memcpy_from_nvs = NULL; hal.nvs.memcpy_to_nvs = NULL;
    CHECK(nvs_buffer_alloc()); CHECK(nvs_buffer_init());
    CHECK(flash_reads == 1 && flash_writes == 0);
}
