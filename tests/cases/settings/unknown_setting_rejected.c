#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    const setting_detail_t *missing = setting_get_details((setting_id_t)65535, NULL);
    CHECK(missing == NULL);
    CHECK(setting_get_value(missing, 0) == NULL);
    CHECK(store_setting((setting_id_t)65535, "1") == Status_SettingDisabled);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
