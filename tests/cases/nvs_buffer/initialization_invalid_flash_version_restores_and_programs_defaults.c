#include "support/nvs_defaults_host.h"
int main(void)
{
    prepare_defaults_storage(NVS_Flash);
    CHECK(nvs_buffer_init());
    check_restored_storage_defaults();
    CHECK(defaults_imports == 1 && defaults_writes > 0 && defaults_failures == 1);
    CHECK(defaults_flash[0] == SETTINGS_VERSION);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
