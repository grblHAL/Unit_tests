#include "support/settings_registry_host.h"
#include "check.h"
static bool available_offset(const setting_detail_t *setting, uint_fast16_t offset) { CHECK(setting == &registry_setting[0]); return offset != 2; }
int main(void)
{
    registry_setting[0].is_available = available_offset;
    prepare_settings_registry();
    setting_details_t *owner = &registry_details;
    CHECK(setting_get_details((setting_id_t)1003, &owner) == NULL);
    CHECK(owner == NULL);
    CHECK(setting_get_details((setting_id_t)1005, &owner) == &registry_setting[0]);
    CHECK(owner == &registry_details);
    return EXIT_SUCCESS;
}
