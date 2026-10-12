#include "support/settings_registry_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_registry();
    setting_details_t *owner = NULL;
    const setting_detail_t *setting = setting_get_details((setting_id_t)1005, &owner);
    CHECK(setting == &registry_setting[0]);
    CHECK(setting->id == (setting_id_t)1001);
    CHECK(owner == &registry_details);
    CHECK(setting_get_details((setting_id_t)1020, &owner) == NULL);
    CHECK(owner == NULL);
    return EXIT_SUCCESS;
}
