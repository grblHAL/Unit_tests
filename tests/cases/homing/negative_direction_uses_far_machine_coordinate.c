#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    settings.homing.dir_mask.bits = 1;
    char command[] = "$HX";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.bits == 1);
    CHECK(sys.position[X_AXIS] == -790);
    CHECK(physical_position[X_AXIS] == -70);
    CHECK(axis_pulses[X_AXIS] == 110);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
