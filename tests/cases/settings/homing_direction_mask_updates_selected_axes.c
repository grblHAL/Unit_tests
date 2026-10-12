#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_HomingDirMask, "5") == Status_OK);
    CHECK(settings.homing.dir_mask.value == (X_AXIS_BIT | Z_AXIS_BIT));
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
