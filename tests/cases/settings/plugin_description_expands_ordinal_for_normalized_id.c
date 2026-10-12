#include "support/settings_registry_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_registry();
    CHECK(strcmp(setting_get_description((setting_id_t)1005), "Channel 5 calibration") == 0);
    CHECK(strcmp(setting_get_description((setting_id_t)1011), "Channel 11 calibration") == 0);
    CHECK(strcmp(setting_get_description((setting_id_t)1001), "Channel 1 calibration") == 0);
    CHECK(strcmp(registry_descriptions[0].description, "Channel ? calibration") == 0);
    return EXIT_SUCCESS;
}
