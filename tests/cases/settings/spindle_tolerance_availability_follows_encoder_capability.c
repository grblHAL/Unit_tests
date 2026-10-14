#include "support/settings_host.h"

int main(void)
{
    prepare_settings_store();
    hal.driver_cap.spindle_encoder = false;
    CHECK(setting_get_details(Setting_SpindleAtSpeedTolerance, NULL) == NULL);
    hal.driver_cap.spindle_encoder = true;
    CHECK(setting_get_details(Setting_SpindleAtSpeedTolerance, NULL) != NULL);
    hal.driver_cap.spindle_encoder = false;
    CHECK(setting_get_details(Setting_SpindleAtSpeedTolerance, NULL) == NULL);
    return EXIT_SUCCESS;
}
