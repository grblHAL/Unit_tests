#include "support/probe_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_settings(); hal.driver_cap.toolsetter = hal.driver_cap.probe2 = true;
    settings.probe.invert_probe_pin = settings.probe.invert_toolsetter_input = false;
    settings.probe.invert_probe2_input = true;
    CHECK(setting_get_int_value(setting_get_details(Setting_InvertProbePin, NULL), 0) == 4);
    return EXIT_SUCCESS;
}
