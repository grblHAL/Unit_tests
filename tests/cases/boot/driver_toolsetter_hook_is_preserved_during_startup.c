#include "support/boot_toolsetter_callbacks_host.h"

static unsigned driver_toolsetter_calls;
static bool driver_toolsetter(tool_data_t *tool, coord_data_t *position, bool at_g59_3, bool on)
{
    CHECK(tool != NULL && position != NULL);
    CHECK(at_g59_3 && on);
    driver_toolsetter_calls++;
    return true;
}
static void setup_driver_toolsetter(settings_t *s)
{
    install_toolsetter(s);
    grbl.on_probe_toolsetter = driver_toolsetter;
}

int main(void)
{
    boot_during_setup = setup_driver_toolsetter;
    CHECK(grbl_enter() == 0);
    CHECK(grbl.on_probe_toolsetter == driver_toolsetter);
    tool_data_t tool = {0}; coord_data_t position = {0};
    CHECK(grbl.on_probe_toolsetter(&tool, &position, true, true));
    CHECK(driver_toolsetter_calls == 1 && probe_select_calls == 0);
    return EXIT_SUCCESS;
}
