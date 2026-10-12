#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_InvertProbePin, "1") == Status_SettingDisabled);
    CHECK(!settings.probe.invert_probe_pin);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
