#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    settings.axis[3].steps_per_mm = 80.5f;
    settings.axis[Y_AXIS].max_rate = 900;
    settings.axis[Y_AXIS].acceleration = 120;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(settings_callbacks == 1);
    NEAR(settings.axis[3].steps_per_mm, 80.5f);
    NEAR(settings.axis[3].max_rate, 900);
    NEAR(settings.axis[3].acceleration, 120);
    return EXIT_SUCCESS;
}
