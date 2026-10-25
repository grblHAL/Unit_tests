#include "eeprom_host.h"
#include "nvs_buffer.h"
nvs_io_t *nvs_buffer_get_physical(void) { return &hal.nvs; }
