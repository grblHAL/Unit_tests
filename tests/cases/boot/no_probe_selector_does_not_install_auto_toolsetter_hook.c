#include "support/boot_toolsetter_callbacks_host.h"

static void setup_without_selector(settings_t *s)
{
    install_toolsetter(s);
    hal.probe.select = NULL;
}

int main(void)
{
    boot_during_setup = setup_without_selector;
    CHECK(grbl_enter() == 0);
    CHECK(grbl.on_probe_toolsetter == NULL);
    CHECK(probe_select_calls == 0);
    return EXIT_SUCCESS;
}
