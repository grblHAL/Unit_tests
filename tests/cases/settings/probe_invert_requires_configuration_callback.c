#include "support/settings_host.h"
#include "check.h"
static probe_state_t probe_state(void) { return (probe_state_t){0}; }
int main(void)
{
    prepare_settings_store();
    hal.probe.get_state = probe_state;
    CHECK(store_setting(Setting_InvertProbePin, "1") == Status_SettingDisabled);
    CHECK(!settings.probe.invert_probe_pin && change_callbacks == 0);
    return EXIT_SUCCESS;
}
