#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Settings_RotaryAxes, "31") == Status_OK);
    CHECK(settings.steppers.is_rotary.mask == 248);
    CHECK(!(settings.steppers.is_rotary.mask & 7));
    const setting_detail_t *detail = setting_get_details(Settings_RotaryAxes, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 31);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
