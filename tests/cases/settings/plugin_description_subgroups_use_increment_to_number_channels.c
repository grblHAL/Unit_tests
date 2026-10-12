#include "support/settings_registry_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_registry();
    registry_setting[0].flags.subgroups = true;
    CHECK(strcmp(setting_get_description((setting_id_t)1005), "Channel 3 calibration") == 0);
    CHECK(strcmp(setting_get_description((setting_id_t)1001), "Channel 1 calibration") == 0);
    return EXIT_SUCCESS;
}
