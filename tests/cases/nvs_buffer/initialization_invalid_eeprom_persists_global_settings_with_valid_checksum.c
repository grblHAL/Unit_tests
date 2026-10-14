#include "support/nvs_defaults_host.h"
int main(void)
{
    prepare_defaults_storage(NVS_EEPROM);
    defaults_physical.put_byte(0, 0);
    CHECK(nvs_buffer_init());
    settings_t persisted;
    CHECK(defaults_physical.memcpy_from_nvs((uint8_t *)&persisted, NVS_ADDR_GLOBAL, sizeof(persisted), true));
    NEAR(persisted.arc_tolerance, DEFAULT_ARC_TOLERANCE);
    CHECK(persisted.version.id == SETTINGS_VERSION);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
