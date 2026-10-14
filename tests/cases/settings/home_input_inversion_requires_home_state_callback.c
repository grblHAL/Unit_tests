#include "support/home_input_settings_host.h"

int main(void)
{
    prepare_settings_store();
    hal.home_cap.a.mask = AXES_BITMASK;
    hal.homing.get_state = NULL;
    CHECK(setting_get_details(Setting_HomePinsInvertMask, NULL) == NULL);
    return EXIT_SUCCESS;
}
