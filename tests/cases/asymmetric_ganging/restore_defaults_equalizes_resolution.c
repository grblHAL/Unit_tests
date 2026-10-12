#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    settings.axis[3].steps_per_mm = 80.5f;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.restore_defaults = true});
    NEAR(settings.axis[3].steps_per_mm, 80);
    CHECK(settings_callbacks == 1);
    CHECK(engine_output[0] == 0);
    return EXIT_SUCCESS;
}
