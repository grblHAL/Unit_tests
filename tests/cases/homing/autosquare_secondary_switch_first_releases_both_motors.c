#include "support/autosquare_homing_host.h"
int main(void)
{
    prepare_autosquare_homing();
    primary_switch_steps = 120;
    secondary_switch_steps = 80;
    settings.homing.dir_mask.mask = 0;
    settings.axis[X_AXIS].dual_axis_offset = 0.0f;
    char command[] = "$HX";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.mask == X_AXIS_BIT && homing_success);
    CHECK(completed_calls == 1);
    CHECK(squared_primary == 110 && squared_secondary == 70);
    CHECK(secondary_stops > 0 && squared_disable_calls > 0);
    CHECK(!primary_disabled && !secondary_disabled);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
