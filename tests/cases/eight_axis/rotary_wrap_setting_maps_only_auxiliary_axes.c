#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.steppers.is_rotary.mask = 8;
    CHECK(store_setting(Setting_RotaryWrap, "17") == Status_OK);
    CHECK(settings.steppers.rotary_wrap.mask == 136);
    CHECK(settings.steppers.is_rotary.mask == 8);
    const setting_detail_t *detail = setting_get_details(Setting_RotaryWrap, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 17);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
