#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    hal.driver_cap.control_pull_up = true;
    hal.signals_cap.reset = true;
    CHECK(store_setting(Setting_ControlPullUpDisableMask, "3") == Status_OK);
    CHECK(settings.control_disable_pullup.reset);
    CHECK(!settings.control_disable_pullup.feed_hold);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
