#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G90G91.1G3X1Y1J1F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80 && sys.position[Y_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 80);
    CHECK(sys.position[Z_AXIS] == 0 && !gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
