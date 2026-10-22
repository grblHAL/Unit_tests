#include "support/autosquare_homing_host.h"

int main(void)
{
    squared_axis_index = Y_AXIS;
    prepare_autosquare_homing();
    settings.axis[Y_AXIS].dual_axis_offset = 0.25f;
    char command[] = "$HY";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.mask == Y_AXIS_BIT && homing_success && completed_calls == 1);
    CHECK(squared_primary == 70 && squared_secondary == 90);
    CHECK(!primary_disabled && !secondary_disabled);
    CHECK(state_get() == STATE_IDLE && !sys.abort);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(axis != Y_AXIS) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
