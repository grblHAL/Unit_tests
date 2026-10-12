#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    settings.homing.cycle[0].bits = (1u << X_AXIS) | (1u << Y_AXIS);
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(settings.homing.cycle[0].bits == ((1u << X_AXIS) | (1u << Y_AXIS) | (1u << 3)));
    return EXIT_SUCCESS;
}
