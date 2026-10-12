#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    settings.homing.flags.force_set_origin = true;
    char command[] = "$HX";
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(sys.position[X_AXIS] == 0);
    CHECK(physical_position[X_AXIS] == 70);
    CHECK(sys.homed.bits == 1);
    return EXIT_SUCCESS;
}
