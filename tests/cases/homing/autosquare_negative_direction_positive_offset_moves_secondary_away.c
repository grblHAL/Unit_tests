#include "support/autosquare_homing_host.h"

int main(void)
{
    prepare_autosquare_homing();
    settings.homing.dir_mask.value = X_AXIS_BIT;
    settings.axis[X_AXIS].dual_axis_offset = 0.25f;
    char command[] = "$HX";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.mask == X_AXIS_BIT && homing_success);
    CHECK(squared_primary == -70 && squared_secondary == -90);
    CHECK(!primary_disabled && !secondary_disabled);
    return EXIT_SUCCESS;
}
