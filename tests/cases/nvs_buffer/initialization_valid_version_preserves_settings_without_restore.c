#include "support/nvs_defaults_host.h"
int main(void)
{
    prepare_defaults_storage(NVS_EEPROM);
    defaults_physical.put_byte(0, SETTINGS_VERSION);
    CHECK(nvs_buffer_init());
    CHECK(change_callbacks == 0 && defaults_failures == 0 && defaults_writes == 0);
    NEAR(settings.arc_tolerance, 9);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
