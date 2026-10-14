#include "support/nvs_defaults_host.h"
int main(void)
{
    prepare_defaults_storage(NVS_EEPROM);
    defaults_physical.put_byte(0, 0);
    CHECK(nvs_buffer_init());
    nvs_buffer_free(); hal.nvs = defaults_physical;
    stored_line_t line;
    CHECK(settings_read_startup_line(0, line)); CHECK(line[0] == 0);
    CHECK(settings_read_startup_line(1, line)); CHECK(line[0] == 0);
    return EXIT_SUCCESS;
}
