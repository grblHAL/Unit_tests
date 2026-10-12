#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    for(unsigned i=0;i<N_AXIS;i++) settings.axis[i].jerk=100;
    queue_motion_program("G1X10F100"); CHECK(plan_get_current_block()->condition.jerk);
    execute_motion_program();
    CHECK(physical_position[X_AXIS]==800); CHECK(physical_position[Y_AXIS]==0); CHECK(physical_position[Z_AXIS]==0);
    CHECK(axis_pulses[X_AXIS]==800); CHECK(axis_pulses[Y_AXIS]==0); CHECK(axis_pulses[Z_AXIS]==0);
    CHECK(sys.position[X_AXIS]==800); CHECK(sys.position[Y_AXIS]==0);
    return EXIT_SUCCESS;
}
