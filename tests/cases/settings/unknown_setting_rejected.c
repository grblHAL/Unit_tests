#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting((setting_id_t)65535, "1") == Status_SettingDisabled);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
