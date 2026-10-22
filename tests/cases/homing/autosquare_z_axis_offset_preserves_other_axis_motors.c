#include "support/autosquare_homing_host.h"

int main(void)
{
    squared_axis_index = Z_AXIS;
    prepare_autosquare_homing();
    settings.axis[Z_AXIS].dual_axis_offset = -0.25f;
    char command[] = "$HZ";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.mask == Z_AXIS_BIT && homing_success && completed_calls == 1);
    CHECK(squared_primary == 50 && squared_secondary == 110);
    CHECK(!primary_disabled && !secondary_disabled);
    CHECK(state_get() == STATE_IDLE && !sys.abort);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(axis != Z_AXIS) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
