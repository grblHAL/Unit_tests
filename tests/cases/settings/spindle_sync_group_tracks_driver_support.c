#include "support/settings_host.h"
int main(void)
{
    prepare_settings_store();
    CHECK(!settings_is_group_available(Group_Spindle_Sync));
    hal.driver_cap.spindle_sync = true;
    CHECK(settings_is_group_available(Group_Spindle_Sync));
    CHECK(setting_get_details(Setting_PositionPGain, NULL) != NULL);
    return EXIT_SUCCESS;
}
