#include "support/settings_registry_host.h"
static bool channel_present;
static bool channel_available(const setting_detail_t *setting, uint_fast16_t offset)
{ CHECK(setting == &registry_setting[0] && offset == 0); return channel_present; }
int main(void)
{
    registry_setting[0].is_available = channel_available;
    prepare_settings_registry();
    CHECK(!settings_is_group_available((setting_group_t)1000));
    CHECK(store_setting((setting_id_t)1001, "42") == Status_SettingDisabled);
    CHECK(registry_value == 0);
    channel_present = true;
    CHECK(settings_is_group_available((setting_group_t)1000));
    CHECK(store_setting((setting_id_t)1001, "42") == Status_OK);
    CHECK(registry_value == 42);
    return EXIT_SUCCESS;
}
