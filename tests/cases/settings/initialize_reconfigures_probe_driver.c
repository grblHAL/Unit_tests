#include "support/settings_initialized_host.h"
#include "check.h"
static unsigned configure_calls;
static void configure_probe(bool away, bool probing) { CHECK(!away && !probing); configure_calls++; }
int main(void)
{
    prepare_initialized_settings(2.0f);
    hal.probe.configure = configure_probe;
    settings_init();
    CHECK(configure_calls == 1);
    return EXIT_SUCCESS;
}
