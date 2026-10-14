#include "support/motion_program_host.h"

int main(void)
{
    prepare_motion_program();
    queue_motion_program("G2I0.1P2F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 0 && sys.position[Y_AXIS] == 0);
    CHECK(physical_position[X_AXIS] == 0 && physical_position[Y_AXIS] == 0);
    /* At 80 steps/mm, one 0.1 mm-radius circle can emit at most 32 X
       pulses. More than that proves execution did not discard the extra turn. */
    CHECK(axis_pulses[X_AXIS] > 32 && axis_pulses[Y_AXIS] > 32);
    CHECK(sys.position[Z_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
