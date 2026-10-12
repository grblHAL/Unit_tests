#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    settings.axis[3].steps_per_mm = 82;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(settings_callbacks == 1);
    NEAR(settings.axis[3].steps_per_mm, 80);
    CHECK(strstr(engine_output, "Ganged axis step/mm is out of range") != NULL);
    return EXIT_SUCCESS;
}
