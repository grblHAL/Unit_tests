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
    CHECK(store_setting(Setting_ProbePullUpDisable, "1") == Status_OK);
    CHECK(settings.probe.disable_probe_pullup);
    CHECK(change_callbacks == 1 && configure_calls == 0);
    return EXIT_SUCCESS;
}
