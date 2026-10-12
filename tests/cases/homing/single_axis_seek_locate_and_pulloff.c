#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    char command[] = "$HX";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.bits == 1);
    CHECK(sys.position[X_AXIS] == -10);
    CHECK(physical_position[X_AXIS] == 70);
    CHECK(physical_position[Y_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 110);
    CHECK(state_get() == STATE_IDLE);
    CHECK(completed_calls == 1);
    CHECK(limit_enable_calls == 2);
    return EXIT_SUCCESS;
}
