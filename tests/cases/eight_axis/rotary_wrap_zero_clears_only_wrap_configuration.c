#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.steppers.rotary_wrap.mask = 248;
    settings.steppers.is_rotary.mask = 8;
    CHECK(store_setting(Setting_RotaryWrap, "0") == Status_OK);
    CHECK(settings.steppers.rotary_wrap.mask == 0);
    CHECK(settings.steppers.is_rotary.mask == 8);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
