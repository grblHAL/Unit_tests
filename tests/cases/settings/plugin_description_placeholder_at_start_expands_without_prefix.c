#include "support/settings_registry_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_registry();
    registry_descriptions[0].description = "? calibration";
    CHECK(strcmp(setting_get_description((setting_id_t)1005), "5 calibration") == 0);
    CHECK(strcmp(registry_descriptions[0].description, "? calibration") == 0);
    return EXIT_SUCCESS;
}
