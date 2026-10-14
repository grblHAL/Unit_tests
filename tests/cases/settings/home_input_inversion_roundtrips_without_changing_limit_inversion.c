#include "support/home_input_settings_host.h"

int main(void)
{
    prepare_settings_store();
    hal.home_cap.a.mask = AXES_BITMASK;
    hal.homing.get_state = dedicated_home_inputs;
    settings.limits.invert.mask = 3;
    CHECK(store_setting(Setting_HomePinsInvertMask, "5") == Status_OK);
    const setting_detail_t *detail = setting_get_details(Setting_HomePinsInvertMask, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 5);
    CHECK(settings.home_invert.mask == 5 && settings.limits.invert.mask == 3);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
