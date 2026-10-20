#include "support/settings_host.h"
int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_HomingDirMask, "5") == Status_OK);
    const setting_detail_t *detail = setting_get_details(Setting_HomingDirMask, NULL);
    CHECK(detail && setting_get_int_value(detail, 0) == (X_AXIS_BIT | Z_AXIS_BIT));
    CHECK(strcmp(setting_get_value(detail, 0), "5") == 0);
    return EXIT_SUCCESS;
}
