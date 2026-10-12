#include "support/probe_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_settings();
    hal.driver_cap.toolsetter = true; hal.driver_cap.probe2 = true;
    settings.probe.invert_probe_pin = settings.probe.invert_toolsetter_input = settings.probe.invert_probe2_input = true;
    const setting_detail_t *detail = setting_get_details(Setting_InvertProbePin, NULL); CHECK(detail != NULL);
    CHECK(setting_get_int_value(detail, 0) == 7);
    return EXIT_SUCCESS;
}
