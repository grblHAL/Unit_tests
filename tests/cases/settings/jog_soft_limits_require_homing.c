#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.homing.flags.enabled = false;
    CHECK(store_setting(Setting_JogSoftLimited, "1") == Status_SoftLimitError);
    CHECK(!settings.limits.flags.jog_soft_limited && change_callbacks == 0);
    return EXIT_SUCCESS;
}
