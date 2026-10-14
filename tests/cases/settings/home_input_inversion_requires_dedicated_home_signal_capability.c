#include "support/home_input_settings_host.h"

int main(void)
{
    prepare_settings_store();
    hal.homing.get_state = dedicated_home_inputs;
    hal.home_cap.a.mask = 0;
    CHECK(setting_get_details(Setting_HomePinsInvertMask, NULL) == NULL);
    return EXIT_SUCCESS;
}
