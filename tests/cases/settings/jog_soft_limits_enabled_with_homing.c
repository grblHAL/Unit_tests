#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.homing.flags.enabled = true;
    CHECK(store_setting(Setting_JogSoftLimited, "1") == Status_OK);
    CHECK(settings.limits.flags.jog_soft_limited && change_callbacks == 1);
    return EXIT_SUCCESS;
}
