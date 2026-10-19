#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    char previous[] = "G20G91G18G93G99";
    CHECK(gc_execute_block(previous) == Status_OK);
    char header[] = "G17G21G40G49G54G80G90G94G98G61";
    CHECK(gc_execute_block(header) == Status_OK);
    CHECK(plan_get_current_block() == NULL);
    CHECK(wake_calls == 0);
    queue_motion_program("G1X10Y5F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 800);
    CHECK(sys.position[Y_AXIS] == 400);
    CHECK(sys.position[Z_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 800 && axis_pulses[Y_AXIS] == 400);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    return EXIT_SUCCESS;
}
