#include "support/boot_toolsetter_callbacks_host.h"

static void setup_without_toolsetter(settings_t *s)
{
    install_toolsetter(s);
    hal.driver_cap.toolsetter = false;
}

int main(void)
{
    boot_during_setup = setup_without_toolsetter;
    CHECK(grbl_enter() == 0);
    CHECK(grbl.on_probe_toolsetter == NULL);
    CHECK(probe_select_calls == 0);
    return EXIT_SUCCESS;
}
