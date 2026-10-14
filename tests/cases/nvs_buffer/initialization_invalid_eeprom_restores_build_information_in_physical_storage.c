#include "support/nvs_defaults_host.h"
int main(void)
{
    prepare_defaults_storage(NVS_EEPROM);
    stored_line_t previous = "old controller configuration";
    settings_write_build_info(previous);
    defaults_physical.put_byte(0, 0);
    CHECK(nvs_buffer_init());
    nvs_buffer_free(); hal.nvs = defaults_physical;
    stored_line_t result;
    CHECK(settings_read_build_info(result)); CHECK(strcmp(result, BUILD_INFO) == 0);
    return EXIT_SUCCESS;
}
