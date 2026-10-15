#include "support/probe_settings_host.h"
int main(void)
{
    prepare_probe_settings();
    hal.driver_cap.toolsetter = hal.driver_cap.probe2 = true;
    CHECK(store_setting(Setting_InvertProbePin, "7") == Status_OK);
    CHECK(store_setting(Setting_InvertProbePin, "0") == Status_OK);
    CHECK(!settings.probe.invert_probe_pin && !settings.probe.invert_toolsetter_input && !settings.probe.invert_probe2_input);
    CHECK(probe_configure_calls == 2 && change_callbacks == 2);
    return EXIT_SUCCESS;
}
