#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    settings.steppers.enable_invert.bits = 1u << 3;
    settings.steppers.dir_invert.bits = 1u << 3;
    settings.steppers.step_invert.bits = 1u << 3;
    settings.steppers.energize.bits = 1u << 3;
    settings.homing.dir_mask.bits = 1u << 3;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(settings.steppers.enable_invert.bits == 0);
    CHECK(settings.steppers.dir_invert.bits == 0);
    CHECK(settings.steppers.step_invert.bits == 0);
    CHECK(settings.steppers.energize.bits == 0);
    CHECK(settings.homing.dir_mask.bits == 0);
    return EXIT_SUCCESS;
}
