#include "support/settings_host.h"
#include "check.h"
static unsigned configure_calls;
static probe_state_t probe_state(void) { return (probe_state_t){0}; }
static void configure_probe(bool away, bool probing) { CHECK(!away && !probing); configure_calls++; }
int main(void)
{
    prepare_settings_store();
    hal.probe.get_state = probe_state;
    hal.probe.configure = configure_probe;
    CHECK(store_setting(Setting_InvertProbePin, "1") == Status_OK);
    CHECK(settings.probe.invert_probe_pin);
    CHECK(configure_calls == 1 && change_callbacks == 1);
    return EXIT_SUCCESS;
}
