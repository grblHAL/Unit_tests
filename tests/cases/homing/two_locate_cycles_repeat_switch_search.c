#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    settings.homing.locate_cycles = 2;
    char command[] = "$HX";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.homed.bits == 1);
    CHECK(physical_position[X_AXIS] == 70);
    CHECK(axis_pulses[X_AXIS] == 130);
    return EXIT_SUCCESS;
}
