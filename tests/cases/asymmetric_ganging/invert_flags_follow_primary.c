#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    settings.steppers.enable_invert.bits = 1u << Y_AXIS;
    settings.steppers.dir_invert.bits = 1u << Y_AXIS;
    settings.steppers.step_invert.bits = 1u << Y_AXIS;
    settings.steppers.energize.bits = 1u << Y_AXIS;
    settings.homing.dir_mask.bits = 1u << Y_AXIS;
    settings.steppers.is_rotary.bits = 1u << 3;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    unsigned expected = (1u << Y_AXIS) | (1u << 3);
    CHECK(settings.steppers.enable_invert.bits == expected);
    CHECK(settings.steppers.dir_invert.bits == expected);
    CHECK(settings.steppers.step_invert.bits == expected);
    CHECK(settings.steppers.energize.bits == expected);
    CHECK(settings.homing.dir_mask.bits == expected);
    CHECK(settings.steppers.is_rotary.bits == 0);
    return EXIT_SUCCESS;
}
